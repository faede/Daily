# printf() 

### source  of printf explaination

http://blog.hostilefork.com/where-printf-rubber-meets-road/

### First Steps

We'll of course start with the prototype for `printf`, which is defined in the file [libc/libio/stdio.h](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/stdio.h;h=85542b1cfdbd50941d288dde8e22e678b10b1333;hb=HEAD)

```C
extern int printf (__const char *__restrict __format, ...);
```

You won't find the source code for a function called `printf`, however. Instead, in the file [/libc/stdio-common/printf.c](http://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/printf.c;h=4c8f3a2a0c38ab27a2eed4d2ff3b804980aa8f9f;hb=HEAD) you'll find a little bit of code associated with a function called `__printf`:

```C
int __printf (const char *format, ...)
{
    va_list arg;
    int done;

    va_start (arg, format);
    done = vfprintf (stdout, format, arg);
    va_end (arg);

    return done;
}
```

A macro in the same file sets up an association so that this function is defined as an alias for the non-underscored `printf`:

```C
ldbl_strong_alias (__printf, printf);
```

It makes sense that `printf` would be a thin layer that calls `vfprintf` with `stdout`. Indeed, the meat of the formatting work is done in `vfprintf`, which you'll find in [libc/stdio-common/vfprintf.c](http://sourceware.org/git/?p=glibc.git;a=blob;f=stdio-common/vprintf.c;h=5c9cac494a6db796a8263401f98964ae4b6a63a2;hb=HEAD). It's quite a lengthy function, but you can see that it's still all in C!

### Deeper Down the Rabbit Hole...

`vfprintf` mysteriously calls `outchar` and `outstring`, which are weird macros defined in the same file:

```C
#define outchar(Ch) \
   do \
   { \
       register const INT_T outc = (Ch); \
       if (PUTC (outc, s) == EOF || done == INT_MAX) \
       { \
            done = -1; \
            goto all_done; \
       } \
       ++done; \
   } \
   while (0)
```

Sidestepping the question of why it's so weird, we see that it's dependent on the enigmatic `PUTC`, also in the same file:

```C
#define PUTC(C, F) IO_putwc_unlocked (C, F)
```

When you get to the definition of `IO_putwc_unlocked` in [libc/libio/libio.h](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/libio.h;h=3c9f2bd3e847429dcb14eb37d3b8369998bd19ee;hb=HEAD), you might start thinking that you no longer care how `printf` works:

```C
#define _IO_putwc_unlocked(_wch, _fp) \
   (_IO_BE ((_fp)->_wide_data->_IO_write_ptr \
        >= (_fp)->_wide_data->_IO_write_end, 0) \
        ? __woverflow (_fp, _wch) \
        : (_IO_wint_t) (*(_fp)->_wide_data->_IO_write_ptr++ = (_wch)))
```

But despite being a little hard to read, it's just doing buffered output. If there's enough room in the file pointer's buffer, then it will just stick the character into it...but if not, it calls `__woverflow`. Since the only option when you've run out of buffer is to flush to the screen (or whatever device your file pointer represents), we can hope to find the magic incantation there.

### Vtables in C?

If you guessed that we're going to hop through another frustrating level of indirection, you'd be right. Look in [libc/libio/wgenops.c](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/wgenops.c;h=e2adedd6d4d07c9f66b870de644d6c3d84848063;hb=HEADp) and you'll find the definition of `__woverflow`:

```C
wint_t 
__woverflow (f, wch)
    _IO_FILE *f;
    wint_t wch;
{
    if (f->_mode == 0)
        _IO_fwide (f, 1);
    return _IO_OVERFLOW (f, wch);
}
```

Basically, file pointers are implemented in the GNU standard library as objects. They have data members but also function members which you can call with variations of the `JUMP` macro. In the file [libc/libio/libioP.h](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/libioP.h;h=854f049291c945b6ec2c552daefe901f23f95a4b;hb=HEAD) you'll find a little documentation of this technique:

```C
/* THE JUMPTABLE FUNCTIONS.

 * The _IO_FILE type is used to implement the FILE type in GNU libc,
 * as well as the streambuf class in GNU iostreams for C++.
 * These are all the same, just used differently.
 * An _IO_FILE (or FILE) object is allows followed by a pointer to
 * a jump table (of pointers to functions).  The pointer is accessed
 * with the _IO_JUMPS macro.  The jump table has a eccentric format,
 * so as to be compatible with the layout of a C++ virtual function table.
 * (as implemented by g++).  When a pointer to a streambuf object is
 * coerced to an (_IO_FILE*), then _IO_JUMPS on the result just
 * happens to point to the virtual function table of the streambuf.
 * Thus the _IO_JUMPS function table used for C stdio/libio does
 * double duty as the virtual function table for C++ streambuf.
 *
 * The entries in the _IO_JUMPS function table (and hence also the
 * virtual functions of a streambuf) are described below.
 * The first parameter of each function entry is the _IO_FILE/streambuf
 * object being acted on (i.e. the 'this' parameter).
 */
```

So when we find `IO_OVERFLOW` in [libc/libio/genops.c](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/genops.c;h=481fbc52b0c0f7f0d4cabaa6676c48f92b84a093;hb=HEAD), we find it's a macro which calls a "1-parameter" `__overflow` method on the file pointer:

```C
#define IO_OVERFLOW(FP, CH) JUMP1 (__overflow, FP, CH)
```

The jump tables for the various file pointer types are in [libc/libio/fileops.c](http://sourceware.org/git/?p=glibc.git;a=blob;f=libio/fileops.c;h=4698953f7ae1d37b4e0911bf2e28cc72d7a1519e;hb=HEAD)

```C
const struct _IO_jump_t _IO_file_jumps =
{
  JUMP_INIT_DUMMY,
  JUMP_INIT(finish, INTUSE(_IO_file_finish)),
  JUMP_INIT(overflow, INTUSE(_IO_file_overflow)),
  JUMP_INIT(underflow, INTUSE(_IO_file_underflow)),
  JUMP_INIT(uflow, INTUSE(_IO_default_uflow)),
  JUMP_INIT(pbackfail, INTUSE(_IO_default_pbackfail)),
  JUMP_INIT(xsputn, INTUSE(_IO_file_xsputn)),
  JUMP_INIT(xsgetn, INTUSE(_IO_file_xsgetn)),
  JUMP_INIT(seekoff, _IO_new_file_seekoff),
  JUMP_INIT(seekpos, _IO_default_seekpos),
  JUMP_INIT(setbuf, _IO_new_file_setbuf),
  JUMP_INIT(sync, _IO_new_file_sync),
  JUMP_INIT(doallocate, INTUSE(_IO_file_doallocate)),
  JUMP_INIT(read, INTUSE(_IO_file_read)),
  JUMP_INIT(write, _IO_new_file_write),
  JUMP_INIT(seek, INTUSE(_IO_file_seek)),
  JUMP_INIT(close, INTUSE(_IO_file_close)),
  JUMP_INIT(stat, INTUSE(_IO_file_stat)),
  JUMP_INIT(showmanyc, _IO_default_showmanyc),
  JUMP_INIT(imbue, _IO_default_imbue)
};
libc_hidden_data_def (_IO_file_jumps)
```

There's also a #define which equates `_IO_new_file_overflow` with `_IO_file_overflow`, and the former is defined in the same source file.

Note `INTUSE` is just a macro which marks functions that are for internal use, it doesn't mean anything like "this function uses an interrupt")

### Are we there yet?!

The source code for `_IO_new_file_overflow` does a bunch more buffer manipulation, but it does call `_IO_do_flush`:

```C
#define _IO_do_flush(_f) \
    INTUSE(_IO_do_write)(_f, (_f)->_IO_write_base, \
        (_f)->_IO_write_ptr-(_f)->_IO_write_base)
```

We're now at a point where `_IO_do_write` is probably where the rubber actually meets the road: an *unbuffered*, *actual*, *direct* write to an I/O device. At least we can hope! It is mapped by a macro to `_IO_new_do_write` and we have this:

```C
static
_IO_size_t
new_do_write (fp, data, to_do)
     _IO_FILE *fp;
     const char *data;
     _IO_size_t to_do;
{
  _IO_size_t count;
  if (fp->_flags & _IO_IS_APPENDING)
    /* On a system without a proper O_APPEND implementation,
       you would need to sys_seek(0, SEEK_END) here, but is
       is not needed nor desirable for Unix- or Posix-like systems.
       Instead, just indicate that offset (before and after) is
       unpredictable. */
    fp->_offset = _IO_pos_BAD;
  else if (fp->_IO_read_end != fp->_IO_write_base)
    {
      _IO_off64_t new_pos
    = _IO_SYSSEEK (fp, fp->_IO_write_base - fp->_IO_read_end, 1);
      if (new_pos == _IO_pos_BAD)
  return 0;
      fp->_offset = new_pos;
    }
  count = _IO_SYSWRITE (fp, data, to_do);
  if (fp->_cur_column && count)
    fp->_cur_column = INTUSE(_IO_adjust_column) (fp->_cur_column - 1, data,
            - count) + 1;
  _IO_setg (fp, fp->_IO_buf_base, fp->_IO_buf_base, fp->_IO_buf_base);
  fp->_IO_write_base = fp->_IO_write_ptr = fp->_IO_buf_base;
  fp->_IO_write_end = (fp->_mode <= 0
           && (fp->_flags & (_IO_LINE_BUF+_IO_UNBUFFERED))
           ? fp->_IO_buf_base : fp->_IO_buf_end);
  return count;
}
```

Sadly we're stuck again... `_IO_SYSWRITE` is doing the work:

```C
/* The 'syswrite' hook is used to write data from an existing buffer
   to an external file.  It generalizes the Unix write(2) function.
   It matches the streambuf::sys_write virtual function, which is
   specific to this implementation. */
typedef _IO_ssize_t (*_IO_write_t) (_IO_FILE *, const void *, _IO_ssize_t);
#define _IO_SYSWRITE(FP, DATA, LEN) JUMP2 (__write, FP, DATA, LEN)
#define _IO_WSYSWRITE(FP, DATA, LEN) WJUMP2 (__write, FP, DATA, LEN)
```

So inside of the `do_write` we call the `write` method on the file pointer. We know from our jump table above that is mapped to `_IO_new_file_write`, so what's that do?

```C
_IO_ssize_t
_IO_new_file_write (f, data, n)
     _IO_FILE *f;
     const void *data;
     _IO_ssize_t n;
{
  _IO_ssize_t to_do = n;
  while (to_do > 0)
    {
      _IO_ssize_t count = (__builtin_expect (f->_flags2
         & _IO_FLAGS2_NOTCANCEL, 0)
         ? write_not_cancel (f->_fileno, data, to_do)
         : write (f->_fileno, data, to_do));
      if (count < 0)
      {
        f->_flags |= _IO_ERR_SEEN;
        break;
      }
      to_do -= count;
      data = (void *) ((char *) data + count);
    }
  n -= to_do;
  if (f->_offset >= 0)
    f->_offset += n;
  return n;
}
```

Now it just calls `write`! Well where is the implementation for that? You'll find `write` in [libc/posix/unistd.h](http://sourceware.org/git/?p=glibc.git;a=blob;f=posix/unistd.h;h=f8b84e3cb35643264a4bfa42b8714c46976cf77c;hb=HEAD):

```C
/* Write N bytes of BUF to FD.  Return the number written, or -1.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern ssize_t write (int __fd, __const void *__buf, size_t __n) __wur;
```

Note `__wur` is a macro for `__attribute__ ((__warn_unused_result__))`

### Functions Generated From a Table

That's only a prototype for `write`. You won't find a write.c file for Linux in the GNU standard library. Instead, you'll find platform-specific methods of connecting to the OS write function in various ways, all in the [libc/sysdeps/](http://sourceware.org/git/?p=glibc.git;a=tree;f=sysdeps;h=f1c8a1febcebabaf9f7b1529c7ca7c5a85ba98de;hb=HEAD) directory.

We'll keep following along with how Linux does it. There is a file called [sysdeps/unix/syscalls.list](http://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/syscalls.list;h=04ed63c4d75451b978fd9488e102fe0d058b0295;hb=HEAD) which is used to generate the `write` function automatically. The relevant data from the table is:

- **File name:** write
- **Caller:** "-" *(i.e. Not Applicable)*
- **Syscall name:** write
- **Args:** Ci:ibn
- **Strong name:** _*libc*write
- **Weak names:** __write, write

Not all that mysterious, except for the **Ci:ibn**. The C means "cancellable". The colon separates the return type from the argument types, and if you want a deeper explanation of what they mean then you can see the comment in the shell script which generates the code, [libc/sysdeps/unix/make-syscalls.sh](http://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/make-syscalls.sh;h=a8b8a262a7cd20ee9fd4618ddc94120d283a813e;hb=HEAD).

So now we're expecting to be able to link against a function called `__libc_write` which is generated by this shell script. But what's being generated? Some C code which implements write via a macro called `SYS_ify`, which you'll find in [sysdeps/unix/sysdep.h](http://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/sysdep.h;h=11e5317dfffdffd9ebc5ca2091d701b99be98b31;hb=HEAD)

```C
#define SYS_ify(syscall_name) __NR_##syscall_name
```

Ah, good old token-pasting :P. So basically, the implementation of this `__libc_write` becomes nothing more than a proxy invocation of the `syscall` function with a parameter named `__NR_write`, and the other arguments.

### Where The Sidewalk Ends...

I know this has been a fascinating journey, but now we're at the end of GNU libc. That number `__NR_write` is defined by Linux. For 32-bit X86 architectures it will get you to [linux/arch/x86/include/asm/unistd_32.h](http://www.cs.fsu.edu/~baker/devices/lxr/http/source/linux/include/asm-x86/unistd_32.h?v=2.6.25#L12):

```C
#define __NR_write 4
```

This is the final step where the "rubber meets the road", but how it is done is system-dependent. That would make an article in itself, but we've found where the rubber meets the road. What you want to read up on to go further is this thing called ["syscall"](http://en.wikipedia.org/wiki/System_call).



# vfprintf

### Overview

1. set argument and check

2. lock stream

3.  Process whole format string.  

4. find a format specifier

   width

   precision

   format

5. process argument

6. if correct find next format specifier

7. unlock

8. call outstring

### source code



`https://code.woboq.org/userspace/glibc/stdio-common/vfprintf-internal.c.html#jump_table`

process_arg 

```c
process_arg(fspec)                                                      \
      /* Start real work.  We know about all flags and modifiers and              \
         now process the wanted format specifier.  */
```



 printf_unknown

```c
/* Handle an unknown format specifier.  This prints out a canonicalized
   representation of the format spec itself.  */
static int
printf_unknown (FILE *s, const struct printf_info *info,
                const void *const *args)

```



outstring

```c

#define outstring(String, Len)                                                      \
  do                                                                              \
    {                                                                              \
      assert ((size_t) done <= (size_t) INT_MAX);                              \
      if ((size_t) PUT (s, (String), (Len)) != (size_t) (Len))                      \
        {                                                                      \
          done = -1;                                                              \
          goto all_done;                                                      \
        }                                                                      \
      if (__glibc_unlikely (INT_MAX - done < (Len)))                              \
      {                                                                              \
        done = -1;                                                              \
         __set_errno (EOVERFLOW);                                              \
        goto all_done;                                                              \
      }                                                                              \
      done += (Len);                                                              \
    }                                                                              \
  while (0)

```





```c
int
vfprintf (FILE *s, const CHAR_T *format, va_list ap, unsigned int mode_flags)
{
  /* The character used as thousands separator.  */
  THOUSANDS_SEP_T thousands_sep = 0;
  /* The string describing the size of groups of digits.  */
  const char *grouping;
  /* Place to accumulate the result.  */
  int done;
  /* Current character in format string.  */
  const UCHAR_T *f;
  /* End of leading constant string.  */
  const UCHAR_T *lead_str_end;
  /* Points to next format specifier.  */
  const UCHAR_T *end_of_spec;
  /* Buffer intermediate results.  */
  CHAR_T work_buffer[WORK_BUFFER_SIZE];
  CHAR_T *workstart = NULL;
  CHAR_T *workend;
  /* We have to save the original argument pointer.  */
  va_list ap_save;
  /* Count number of specifiers we already processed.  */
  int nspecs_done;
  /* For the %m format we may need the current `errno' value.  */
  int save_errno = errno;
  /* 1 if format is in read-only memory, -1 if it is in writable memory,
     0 if unknown.  */
  int readonly_format = 0;
  /* Orient the stream.  */
#ifdef ORIENT
  ORIENT;
#endif
  /* Sanity check of arguments.  */
  ARGCHECK (s, format);
#ifdef ORIENT
  /* Check for correct orientation.  */
  if (_IO_vtable_offset (s) == 0
      && _IO_fwide (s, sizeof (CHAR_T) == 1 ? -1 : 1)
      != (sizeof (CHAR_T) == 1 ? -1 : 1))
    /* The stream is already oriented otherwise.  */
    return EOF;
#endif
  if (UNBUFFERED_P (s))
    /* Use a helper function which will allocate a local temporary buffer
       for the stream and then call us again.  */
    return buffered_vfprintf (s, format, ap, mode_flags);
  /* Initialize local variables.  */
  done = 0;
  grouping = (const char *) -1;
#ifdef __va_copy
  /* This macro will be available soon in gcc's <stdarg.h>.  We need it
     since on some systems `va_list' is not an integral type.  */
  __va_copy (ap_save, ap);
#else
  ap_save = ap;
#endif
  nspecs_done = 0;
#ifdef COMPILE_WPRINTF
  /* Find the first format specifier.  */
  f = lead_str_end = __find_specwc ((const UCHAR_T *) format);
#else
  /* Find the first format specifier.  */
  f = lead_str_end = __find_specmb ((const UCHAR_T *) format);
#endif
  /* Lock stream.  */
  _IO_cleanup_region_start ((void (*) (void *)) &_IO_funlockfile, s);
  _IO_flockfile (s);
  /* Write the literal text before the first format.  */
  outstring ((const UCHAR_T *) format,
             lead_str_end - (const UCHAR_T *) format);
  /* If we only have to print a simple string, return now.  */
  if (*f == L_('\0'))
    goto all_done;
  /* Use the slow path in case any printf handler is registered.  */
  if (__glibc_unlikely (__printf_function_table != NULL
                        || __printf_modifier_table != NULL
                        || __printf_va_arg_table != NULL))
    goto do_positional;
  /* Process whole format string.  */
  do
    {
      STEP0_3_TABLE;
      STEP4_TABLE;
      union printf_arg *args_value;        /* This is not used here but ... */
      int is_negative;        /* Flag for negative number.  */
      union
      {
        unsigned long long int longlong;
        unsigned long int word;
      } number;
      int base;
      union printf_arg the_arg;
      CHAR_T *string;        /* Pointer to argument string.  */
      int alt = 0;        /* Alternate format.  */
      int space = 0;        /* Use space prefix if no sign is needed.  */
      int left = 0;        /* Left-justify output.  */
      int showsign = 0;        /* Always begin with plus or minus sign.  */
      int group = 0;        /* Print numbers according grouping rules.  */
      int is_long_double = 0; /* Argument is long double/ long long int.  */
      int is_short = 0;        /* Argument is short int.  */
      int is_long = 0;        /* Argument is long int.  */
      int is_char = 0;        /* Argument is promoted (unsigned) char.  */
      int width = 0;        /* Width of output; 0 means none specified.  */
      int prec = -1;        /* Precision of output; -1 means none specified.  */
      /* This flag is set by the 'I' modifier and selects the use of the
         `outdigits' as determined by the current locale.  */
      int use_outdigits = 0;
      UCHAR_T pad = L_(' ');/* Padding character.  */
      CHAR_T spec;
      workstart = NULL;
      workend = work_buffer + WORK_BUFFER_SIZE;
      /* Get current character in format string.  */
      JUMP (*++f, step0_jumps);
      /* ' ' flag.  */
    LABEL (flag_space):
      space = 1;
      JUMP (*++f, step0_jumps);
      /* '+' flag.  */
    LABEL (flag_plus):
      showsign = 1;
      JUMP (*++f, step0_jumps);
      /* The '-' flag.  */
    LABEL (flag_minus):
      left = 1;
      pad = L_(' ');
      JUMP (*++f, step0_jumps);
      /* The '#' flag.  */
    LABEL (flag_hash):
      alt = 1;
      JUMP (*++f, step0_jumps);
      /* The '0' flag.  */
    LABEL (flag_zero):
      if (!left)
        pad = L_('0');
      JUMP (*++f, step0_jumps);
      /* The '\'' flag.  */
    LABEL (flag_quote):
      group = 1;
      if (grouping == (const char *) -1)
        {
#ifdef COMPILE_WPRINTF
          thousands_sep = _NL_CURRENT_WORD (LC_NUMERIC,
                                            _NL_NUMERIC_THOUSANDS_SEP_WC);
#else
          thousands_sep = _NL_CURRENT (LC_NUMERIC, THOUSANDS_SEP);
#endif
          grouping = _NL_CURRENT (LC_NUMERIC, GROUPING);
          if (*grouping == '\0' || *grouping == CHAR_MAX
#ifdef COMPILE_WPRINTF
              || thousands_sep == L'\0'
#else
              || *thousands_sep == '\0'
#endif
              )
            grouping = NULL;
        }
      JUMP (*++f, step0_jumps);
    LABEL (flag_i18n):
      use_outdigits = 1;
      JUMP (*++f, step0_jumps);
      /* Get width from argument.  */
    LABEL (width_asterics):
      {
        const UCHAR_T *tmp;        /* Temporary value.  */
        tmp = ++f;
        if (ISDIGIT (*tmp))
          {
            int pos = read_int (&tmp);
            if (pos == -1)
              {
                __set_errno (EOVERFLOW);
                done = -1;
                goto all_done;
              }
            if (pos && *tmp == L_('$'))
              /* The width comes from a positional parameter.  */
              goto do_positional;
          }
        width = va_arg (ap, int);
        /* Negative width means left justified.  */
        if (width < 0)
          {
            width = -width;
            pad = L_(' ');
            left = 1;
          }
        if (__glibc_unlikely (width >= INT_MAX / sizeof (CHAR_T) - EXTSIZ))
          {
            __set_errno (EOVERFLOW);
            done = -1;
            goto all_done;
          }
        if (width >= WORK_BUFFER_SIZE - EXTSIZ)
          {
            /* We have to use a special buffer.  */
            size_t needed = ((size_t) width + EXTSIZ) * sizeof (CHAR_T);
            if (__libc_use_alloca (needed))
              workend = (CHAR_T *) alloca (needed) + width + EXTSIZ;
            else
              {
                workstart = (CHAR_T *) malloc (needed);
                if (workstart == NULL)
                  {
                    done = -1;
                    goto all_done;
                  }
                workend = workstart + width + EXTSIZ;
              }
          }
      }
      JUMP (*f, step1_jumps);
      /* Given width in format string.  */
    LABEL (width):
      width = read_int (&f);
      if (__glibc_unlikely (width == -1
                            || width >= INT_MAX / sizeof (CHAR_T) - EXTSIZ))
        {
          __set_errno (EOVERFLOW);
          done = -1;
          goto all_done;
        }
      if (width >= WORK_BUFFER_SIZE - EXTSIZ)
        {
          /* We have to use a special buffer.  */
          size_t needed = ((size_t) width + EXTSIZ) * sizeof (CHAR_T);
          if (__libc_use_alloca (needed))
            workend = (CHAR_T *) alloca (needed) + width + EXTSIZ;
          else
            {
              workstart = (CHAR_T *) malloc (needed);
              if (workstart == NULL)
                {
                  done = -1;
                  goto all_done;
                }
              workend = workstart + width + EXTSIZ;
            }
        }
      if (*f == L_('$'))
        /* Oh, oh.  The argument comes from a positional parameter.  */
        goto do_positional;
      JUMP (*f, step1_jumps);
    LABEL (precision):
      ++f;
      if (*f == L_('*'))
        {
          const UCHAR_T *tmp;        /* Temporary value.  */
          tmp = ++f;
          if (ISDIGIT (*tmp))
            {
              int pos = read_int (&tmp);
              if (pos == -1)
                {
                  __set_errno (EOVERFLOW);
                  done = -1;
                  goto all_done;
                }
              if (pos && *tmp == L_('$'))
                /* The precision comes from a positional parameter.  */
                goto do_positional;
            }
          prec = va_arg (ap, int);
          /* If the precision is negative the precision is omitted.  */
          if (prec < 0)
            prec = -1;
        }
      else if (ISDIGIT (*f))
        {
          prec = read_int (&f);
          /* The precision was specified in this case as an extremely
             large positive value.  */
          if (prec == -1)
            {
              __set_errno (EOVERFLOW);
              done = -1;
              goto all_done;
            }
        }
      else
        prec = 0;
      if (prec > width && prec > WORK_BUFFER_SIZE - EXTSIZ)
        {
          /* Deallocate any previously allocated buffer because it is
             too small.  */
          if (__glibc_unlikely (workstart != NULL))
            free (workstart);
          workstart = NULL;
          if (__glibc_unlikely (prec >= INT_MAX / sizeof (CHAR_T) - EXTSIZ))
            {
              __set_errno (EOVERFLOW);
              done = -1;
              goto all_done;
            }
          size_t needed = ((size_t) prec + EXTSIZ) * sizeof (CHAR_T);
          if (__libc_use_alloca (needed))
            workend = (CHAR_T *) alloca (needed) + prec + EXTSIZ;
          else
            {
              workstart = (CHAR_T *) malloc (needed);
              if (workstart == NULL)
                {
                  done = -1;
                  goto all_done;
                }
              workend = workstart + prec + EXTSIZ;
            }
        }
      JUMP (*f, step2_jumps);
      /* Process 'h' modifier.  There might another 'h' following.  */
    LABEL (mod_half):
      is_short = 1;
      JUMP (*++f, step3a_jumps);
      /* Process 'hh' modifier.  */
    LABEL (mod_halfhalf):
      is_short = 0;
      is_char = 1;
      JUMP (*++f, step4_jumps);
      /* Process 'l' modifier.  There might another 'l' following.  */
    LABEL (mod_long):
      is_long = 1;
      JUMP (*++f, step3b_jumps);
      /* Process 'L', 'q', or 'll' modifier.  No other modifier is
         allowed to follow.  */
    LABEL (mod_longlong):
      is_long_double = 1;
      is_long = 1;
      JUMP (*++f, step4_jumps);
    LABEL (mod_size_t):
      is_long_double = sizeof (size_t) > sizeof (unsigned long int);
      is_long = sizeof (size_t) > sizeof (unsigned int);
      JUMP (*++f, step4_jumps);
    LABEL (mod_ptrdiff_t):
      is_long_double = sizeof (ptrdiff_t) > sizeof (unsigned long int);
      is_long = sizeof (ptrdiff_t) > sizeof (unsigned int);
      JUMP (*++f, step4_jumps);
    LABEL (mod_intmax_t):
      is_long_double = sizeof (intmax_t) > sizeof (unsigned long int);
      is_long = sizeof (intmax_t) > sizeof (unsigned int);
      JUMP (*++f, step4_jumps);
      /* Process current format.  */
      while (1)
        {
          process_arg (((struct printf_spec *) NULL));
          process_string_arg (((struct printf_spec *) NULL));
        LABEL (form_unknown):
          if (spec == L_('\0'))
            {
              /* The format string ended before the specifier is complete.  */
              __set_errno (EINVAL);
              done = -1;
              goto all_done;
            }
          /* If we are in the fast loop force entering the complicated
             one.  */
          goto do_positional;
        }
      /* The format is correctly handled.  */
      ++nspecs_done;
      if (__glibc_unlikely (workstart != NULL))
        free (workstart);
      workstart = NULL;
      /* Look for next format specifier.  */
#ifdef COMPILE_WPRINTF
      f = __find_specwc ((end_of_spec = ++f));
#else
      f = __find_specmb ((end_of_spec = ++f));
#endif
      /* Write the following constant string.  */
      outstring (end_of_spec, f - end_of_spec);
    }
  while (*f != L_('\0'));
  /* Unlock stream and return.  */
  goto all_done;
  /* Hand off processing for positional parameters.  */
do_positional:
  if (__glibc_unlikely (workstart != NULL))
    {
      free (workstart);
      workstart = NULL;
    }
  done = printf_positional (s, format, readonly_format, ap, &ap_save,
                            done, nspecs_done, lead_str_end, work_buffer,
                            save_errno, grouping, thousands_sep, mode_flags);
 all_done:
  if (__glibc_unlikely (workstart != NULL))
    free (workstart);
  /* Unlock the stream.  */
  _IO_funlockfile (s);
  _IO_cleanup_region_end (0);
  return done;
}

```



# global view

.a achieve , combine .o

.o ----> .a  [--->.out]



(R, G , B , light)

0-255, 0-255, 0-255, 0-255



cpu --->buffer --> screen

or

cpu --> gpu --> screen

## IOControl

 



## DRM 

### What Is Digital Rights Management?

Digital rights management (DRM) is the use of technology to control and manage access to copyrighted material. Another DRM meaning is taking control of digital content away from the person who possesses it and handing it to a computer program. DRM aims to protect the copyright holder’s rights and prevents content from unauthorized distribution and modification.

DRM is increasingly important as digital content spreads through peer-to-peer file exchanges, torrent sites, and online piracy. It helps[ entertainment and media](https://www.fortinet.com/solutions/industries/media-entertainment) companies protect themselves from the cybersecurity challenges that all organizations face, such as protecting customer data, ensuring and demonstrating compliance, enhancing operational efficiency, and preventing downtime.

DRM enables authors, musicians, moviemakers, and other content creators to clarify and control what people can and cannot do with their content. It also allows them to protect their copyrighted material, safeguard the creative and financial investment they put into their work, and make it impossible for their media to be stolen or shared illegally. For example, they can prevent users from accessing specific assets, so they can avoid any legal issues that could come from unauthorized usage. This is crucial to protecting copyright and intellectual property.

### How DRM Works?

The unauthorized distribution, sharing, and modification of digital content are covered by copyright laws, but monitoring the internet to prevent illegal activity is a challenging task. DRM addresses this by putting barriers in place to prevent digital content from being stolen.

DRM typically involves the use of codes that prohibit content copying or limit the number of devices a product can be accessed from. Content creators can also use applications to restrict what users can do with their material or encrypt digital media, which can then only be accessed by anyone with the decryption key.

This enables content creators and copyright holders to: 

1. Prevent or restrict users from editing or saving, sharing or forwarding, printing, or taking screenshots or screengrabs of their content or products
2. Set expiry dates on media, which prevents access to users beyond that date or limits the number of times they can access it
3. Limit media access to specific devices, Internet Protocol (IP) addresses, or locations, such as limiting content to people in the U.S. only
4. Watermark documents and images to assert ownership and identity of content

## drive



Graphics card 

 HAL 

/dev/dri





​																				printf()

--------------------------------------------------

​																				SHELL

-------------------------

​																    stdin, stdout, stdrr

--------------------------------------------------

​																				HAL

-------------------------

​																	keyboard, terminal

-------------------------





## UART

A **universal asynchronous receiver-transmitter** (**UART** [/ˈjuːɑːrt/](https://en.wikipedia.org/wiki/Help:IPA/English)) is a [computer hardware](https://en.wikipedia.org/wiki/Computer_hardware) device for [asynchronous serial communication](https://en.wikipedia.org/wiki/Asynchronous_serial_communication) in which the data format and transmission speeds are configurable. It sends data [bits](https://en.wikipedia.org/wiki/Bit) one by one, from the least significant to the most significant, framed by start and stop bits so that precise timing is handled by the communication channel. The electric signaling levels are handled by a driver circuit external to the UART. Two common signal levels are [RS-232](https://en.wikipedia.org/wiki/RS-232), a 12-[volt](https://en.wikipedia.org/wiki/Volt) system, and [RS-485](https://en.wikipedia.org/wiki/RS-485), a 5-volt system. Early teletypewriters used [current loops](https://en.wikipedia.org/wiki/Digital_current_loop_interface).

It was one of the earliest computer communication devices, used to attach [teletypewriters](https://en.wikipedia.org/wiki/Teletypewriter) for an [operator console](https://en.wikipedia.org/wiki/Command_line_interface). It was also an early hardware system for the [Internet](https://en.wikipedia.org/wiki/SLIP).

A UART is usually an individual (or part of an) [integrated circuit](https://en.wikipedia.org/wiki/Integrated_circuit) (IC) used for [serial communications](https://en.wikipedia.org/wiki/Serial_communications) over a computer or peripheral device [serial port](https://en.wikipedia.org/wiki/Serial_port). One or more UART peripherals are commonly integrated in [microcontroller](https://en.wikipedia.org/wiki/Microcontroller) chips. Specialised UARTs are used for [automobiles](https://en.wikipedia.org/wiki/Local_Interconnect_Network), [smart cards](https://en.wikipedia.org/wiki/Smart_card) and [SIMs](https://en.wikipedia.org/wiki/SIM_card).

A related device, the [universal synchronous and asynchronous receiver-transmitter](https://en.wikipedia.org/wiki/Universal_synchronous_and_asynchronous_receiver-transmitter) (USART) also supports synchronous operation.





# C++

```c++
template<typename _CharT, typename _Traits>
    streamsize
    basic_streambuf<_CharT, _Traits>::
    xsputn(const char_type* __s, streamsize __n)
    {
      streamsize __ret = 0;
      while (__ret < __n)
        {
          const streamsize __buf_len = this->epptr() - this->pptr();
          if (__buf_len)
            {
              const streamsize __remaining = __n - __ret;
              const streamsize __len = std::min(__buf_len, __remaining);
              traits_type::copy(this->pptr(), __s, __len);
              __ret += __len;
              __s += __len;
              this->__safe_pbump(__len);
            }
          if (__ret < __n)
            {
              int_type __c = this->overflow(traits_type::to_int_type(*__s));
              if (!traits_type::eq_int_type(__c, traits_type::eof()))
                {
                  ++__ret;
                  ++__s;
                }
              else
                break;
            }
        }
      return __ret;
    }

```

