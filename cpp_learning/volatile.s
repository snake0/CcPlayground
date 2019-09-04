	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
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
	subq	$48, %rsp
	xorl	%eax, %eax
	movl	$8, %ecx
	movl	%ecx, %edx
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	leaq	-24(%rbp), %rsi
	movq	%rsi, %rdi
	movl	%eax, %esi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	callq	_memset
	movl	$1, -4(%rbp)
	movl	$3, -16(%rbp)
	movl	$4, -20(%rbp)
	leaq	-4(%rbp), %rdx
	movq	%rdx, -32(%rbp)
	movq	-32(%rbp), %rdx
	movl	$2, (%rdx)
	leaq	-8(%rbp), %rdx
	movq	%rdx, -40(%rbp)
	movl	-44(%rbp), %eax         ## 4-byte Reload
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
