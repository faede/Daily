	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	__Z4proclPliPisPscPc    ## -- Begin function _Z4proclPliPisPscPc
	.p2align	4, 0x90
__Z4proclPliPisPscPc:                   ## @_Z4proclPliPisPscPc
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	.cfi_offset %rbx, -24
                                        ## kill: def $r8w killed $r8w killed $r8d
	movq	24(%rbp), %rax
	movb	16(%rbp), %r10b
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movq	%rcx, -40(%rbp)
	movw	%r8w, -42(%rbp)
	movq	%r9, -56(%rbp)
	movq	-16(%rbp), %rcx
	movq	-24(%rbp), %rsi
	addq	(%rsi), %rcx
	movq	%rcx, (%rsi)
	movl	-28(%rbp), %edx
	movq	-40(%rbp), %rcx
	addl	(%rcx), %edx
	movl	%edx, (%rcx)
	movswl	-42(%rbp), %edx
	movq	-56(%rbp), %rcx
	movswl	(%rcx), %r11d
	addl	%edx, %r11d
                                        ## kill: def $r11w killed $r11w killed $r11d
	movw	%r11w, (%rcx)
	movsbl	16(%rbp), %edx
	movq	24(%rbp), %rcx
	movsbl	(%rcx), %ebx
	addl	%edx, %ebx
                                        ## kill: def $bl killed $bl killed $ebx
	movb	%bl, (%rcx)
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	movl	$0, -4(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
