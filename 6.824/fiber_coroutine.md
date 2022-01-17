[What is the difference between a fiber and a thread?](https://www.quora.com/What-is-the-difference-between-a-fiber-and-a-thread)

**Threads** are a kernel-space construct. They are the unit of execution in a process: Each thread has a virtualized processor, a stack, and program state. While a process represents a running binary, a thread is the smallest entity schedulable by the operating system's process scheduler. As such, threads are scheduled as you'd expect processes to be scheduled: by your operating system, preemptively multitasked among all of the other running threads on your system. (See my answer to [What is the difference between a process and a thread](https://www.quora.com/What-is-the-difference-between-a-process-and-a-thread/answer/Robert-Love-1)[?](https://www.quora.com/What-is-the-difference-between-a-process-and-a-thread/answer/Robert-Love-1) for more on threads.)**Fibers** are a user-space construct. Like threads, they enable multiple flows of execution to coexist inside of your process. Unlike threads, that execution isn't managed by the kernel. In fact, fibers aren't managed by anyone. They are cooperative in every sense of the word, including cooperatively scheduled: That is, your system executes one fiber in lieu of another only when the first fiber explicitly *yields* control.As an example, consider the subroutine, e.g. a function in C or C++. When you invoke a subroutine, that subroutine runs until it returns and the invoking code is blocked until that return. Imagine now that whenever you invoke a subroutine, the invoking code *wasn't* blocked waiting for return. Instead, imagine that we ran the invoked subroutine, but it was able to *yield* control back to the invoking code—without needing to return. That describes **fibers**. With fibers, you have cooperative concurrency in that multiple subroutines may execute without blocking their invokers. Conversely, if both subroutines ran, potentially in parallel, preemptively scheduled by your operating system, we'd have **threading**.**Threads** are about both concurrency and parallelism. That is, threads are both a way to manage flow of control in a program and a way to improve performance through parallel execution.**Fibers** are just about concurrency. That is, fibers are a way to manage the flow of control in a program but they do not allow you to realize true parallelism.Some bonus terms: **Coroutines** and **fibers** generally refer to the same thing; the former when a programming language construct and the latter when a system construct. We can define **subroutines** as coroutines that never yield. **Go routines** are coroutines that run in parallel. **User-level threads** act like threads but as with fibers are implemented mostly in user-space. They can be scheduled preemptively or cooperatively.(I cover threads, fibers, and more in [Linux System Programming](http://www.amazon.com/dp/1449339530/ref=as_li_ss_til?tag=roblov-20&camp=0&creative=0&linkCode=as4&creativeASIN=1449339530&adid=08EAHYTMFA0W997ME45V).)





**Coroutines** are [computer program](https://en.wikipedia.org/wiki/Computer_program) components that generalize [subroutines](https://en.wikipedia.org/wiki/Subroutine) for [non-preemptive multitasking](https://en.wikipedia.org/wiki/Non-preemptive_multitasking), by allowing execution to be suspended and resumed. Coroutines are well-suited for implementing familiar program components such as [cooperative tasks](https://en.wikipedia.org/wiki/Cooperative_multitasking), [exceptions](https://en.wikipedia.org/wiki/Exception_handling), [event loops](https://en.wikipedia.org/wiki/Event_loop), [iterators](https://en.wikipedia.org/wiki/Iterator), [infinite lists](https://en.wikipedia.org/wiki/Lazy_evaluation) and [pipes](https://en.wikipedia.org/wiki/Pipeline_(software)).

According to [Donald Knuth](https://en.wikipedia.org/wiki/Donald_Knuth), [Melvin Conway](https://en.wikipedia.org/wiki/Melvin_Conway) coined the term *coroutine* in 1958 when he applied it to the construction of an [assembly program](https://en.wikipedia.org/wiki/Assembly_language).[[1\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-KnuthVol1_1_4_5-1) The first published explanation of the coroutine appeared later, in 1963.[[2\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-Conway1963-2)



### Subroutines[[edit](https://en.wikipedia.org/w/index.php?title=Coroutine&action=edit&section=2)]

Subroutines are special cases of coroutines.[[3\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-KnuthVol1_1_4_2-3) When subroutines are invoked, execution begins at the start, and once a subroutine exits, it is finished; an instance of a subroutine only returns once, and does not hold state between invocations. By contrast, coroutines can exit by calling other coroutines, which may later return to the point where they were invoked in the original coroutine; from the coroutine's point of view, it is not exiting but calling another coroutine.[[3\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-KnuthVol1_1_4_2-3) Thus, a coroutine instance holds state, and varies between invocations; there can be multiple instances of a given coroutine at once. The difference between calling another coroutine by means of ["yielding"](https://en.wikipedia.org/wiki/Yield_(multithreading)) to it and simply calling another routine (which then, also, would return to the original point), is that the relationship between two coroutines which yield to each other is not that of caller-callee, but instead symmetric.

Any subroutine can be translated to a coroutine which does not call *yield*.[[4\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-Perlis1982_6-4)

Here is a simple example of how coroutines can be useful. Suppose you have a consumer-producer relationship where one routine creates items and adds them to a queue and another removes items from the queue and uses them. For reasons of efficiency, you want to add and remove several items at once. The code might look like this:

```
var q := new queue

coroutine produce
    loop
        while q is not full
            create some new items
            add the items to q
        yield to consume

coroutine consume
    loop
        while q is not empty
            remove some items from q
            use the items
        yield to produce

call produce
```

The queue is then completely filled or emptied before yielding control to the other coroutine using the *yield* command. The further coroutines calls are starting right after the *yield*, in the outer coroutine loop.

Although this example is often used as an introduction to [multithreading](https://en.wikipedia.org/wiki/Thread_(computing)), two threads are not needed for this: the *yield* statement can be implemented by a jump directly from one routine into the other.

### Threads[[edit](https://en.wikipedia.org/w/index.php?title=Coroutine&action=edit&section=3)]

Coroutines are very similar to [threads](https://en.wikipedia.org/wiki/Thread_(computing)). However, coroutines are [cooperatively](https://en.wikipedia.org/wiki/Cooperative_multitasking) multitasked, whereas threads are typically [preemptively](https://en.wikipedia.org/wiki/Preemptive_multitasking) [multitasked](https://en.wikipedia.org/wiki/Computer_multitasking). Coroutines provide [concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)) but not [parallelism](https://en.wikipedia.org/wiki/Parallel_computing). The advantages of coroutines over threads are that they may be used in a [hard-realtime](https://en.wikipedia.org/wiki/Hard_realtime) context ([switching](https://en.wikipedia.org/wiki/Context_switch) between coroutines need not involve any [system calls](https://en.wikipedia.org/wiki/System_calls) or any [blocking](https://en.wikipedia.org/wiki/Blocking_(computing)) calls whatsoever), there is no need for synchronization primitives such as [mutexes](https://en.wikipedia.org/wiki/Mutex), semaphores, etc. in order to guard [critical sections](https://en.wikipedia.org/wiki/Critical_sections), and there is no need for support from the operating system.

It is possible to implement coroutines using preemptively-scheduled threads, in a way that will be transparent to the calling code, but some of the advantages (particularly the suitability for hard-realtime operation and relative cheapness of switching between them) will be lost.

### Generators[[edit](https://en.wikipedia.org/w/index.php?title=Coroutine&action=edit&section=4)]

Main article: [Generator (computer programming)](https://en.wikipedia.org/wiki/Generator_(computer_programming))

Generators, also known as semicoroutines,[[5\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-Ralston2000-5) are a subset of coroutines. Specifically, while both can yield multiple times, suspending their execution and allowing re-entry at multiple entry points, they differ in coroutines' ability to control where execution continues immediately after they yield, while generators cannot, instead transferring control back to the generator's caller.[[6\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-6) That is, since generators are primarily used to simplify the writing of [iterators](https://en.wikipedia.org/wiki/Iterator), the `yield` statement in a generator does not specify a coroutine to jump to, but rather passes a value back to a parent routine.

However, it is still possible to implement coroutines on top of a generator facility, with the aid of a top-level dispatcher routine (a [trampoline](https://en.wikipedia.org/wiki/Trampoline_(computing)), essentially) that passes control explicitly to child generators identified by tokens passed back from the generators:

```
var q := new queue

generator produce
    loop
        while q is not full
            create some new items
            add the items to q
        yield consume

generator consume
    loop
        while q is not empty
            remove some items from q
            use the items
        yield produce

subroutine dispatcher
    var d := new dictionary(generator → iterator)
    d[produce] := start produce
    d[consume] := start consume
    var current := produce
    loop
        call current
        current := next d[current]

call dispatcher
```

A number of implementations of coroutines for languages with generator support but no native coroutines (e.g. Python[[7\]](https://en.wikipedia.org/wiki/Coroutine#cite_note-MertzIBM-7) before 2.5) use this or a similar model.

### Mutual recursion[[edit](https://en.wikipedia.org/w/index.php?title=Coroutine&action=edit&section=5)]

Further information: [Mutual recursion](https://en.wikipedia.org/wiki/Mutual_recursion)

Using coroutines for state machines or concurrency is similar to using [mutual recursion](https://en.wikipedia.org/wiki/Mutual_recursion) with [tail calls](https://en.wikipedia.org/wiki/Tail_call), as in both cases the control changes to a different one of a set of routines. However, coroutines are more flexible and generally more efficient. Since coroutines yield rather than return, and then resume execution rather than restarting from the beginning, they are able to hold state, both variables (as in a closure) and execution point, and yields are not limited to being in tail position; mutually recursive subroutines must either use shared variables or pass state as parameters. Further, each mutually recursive call of a subroutine requires a new stack frame (unless [tail call elimination](https://en.wikipedia.org/wiki/Tail_call_elimination) is implemented), while passing control between coroutines uses the existing contexts and can be implemented simply by a jump.

## Common uses[[edit](https://en.wikipedia.org/w/index.php?title=Coroutine&action=edit&section=6)]

Coroutines are useful to implement the following:

- [State machines](https://en.wikipedia.org/wiki/State_machine) within a single subroutine, where the state is determined by the current entry/exit point of the procedure; this can result in more readable code compared to use of [goto](https://en.wikipedia.org/wiki/Goto), and may also be implemented via [mutual recursion](https://en.wikipedia.org/wiki/Mutual_recursion) with [tail calls](https://en.wikipedia.org/wiki/Tail_call).
- [Actor model](https://en.wikipedia.org/wiki/Actor_model) of concurrency, for instance in [video games](https://en.wikipedia.org/wiki/Video_game). Each actor has its own procedures (this again logically separates the code), but they voluntarily give up control to central scheduler, which executes them sequentially (this is a form of [cooperative multitasking](https://en.wikipedia.org/wiki/Cooperative_multitasking)).
- [Generators](https://en.wikipedia.org/wiki/Generator_(computer_programming)), and these are useful for [streams](https://en.wikipedia.org/wiki/Stream_(computing)) – particularly input/output – and for generic traversal of data structures.
- [Communicating sequential processes](https://en.wikipedia.org/wiki/Communicating_sequential_processes) where each sub-process is a coroutine. Channel inputs/outputs and blocking operations yield coroutines and a scheduler unblocks them on completion events. Alternatively, each sub-process may be the parent of the one following it in the data pipeline (or preceding it, in which case the pattern can be expressed as nested generators).
- Reverse communication, commonly used in mathematical software, wherein a procedure such as a solver, integral evaluator, ... needs the using process to make a computation, such as evaluating an equation or integrand.







You could take a look at [boost.coroutine2](http://www.boost.org/doc/libs/1_64_0/libs/coroutine2/doc/html/index.html) and [boost.fiber](http://www.boost.org/doc/libs/1_64_0/libs/fiber/doc/html/index.html) (C++ libraries) - both use the same context switching mechanism ([callcc()/continuation](http://www.boost.org/doc/libs/1_64_0/libs/context/doc/html/context/cc.html)) from [boost.context](http://www.boost.org/doc/libs/1_64_0/libs/context/doc/html/index.html).

In short - the difference between coroutines and fibers is, that the context switch between fibers is managed by a scheduler (selects the next fiber ...). Coroutines don't have a concept of a scheduler.

A more detailed explanation of the difference between coroutines and fibers can be read in [N4024: Distinguishing coroutines and fibers](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4024.pdf).