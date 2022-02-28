	.file	"deneme.c"
	.text
	.globl	hengirmen
	.type	hengirmen, @function
hengirmen:
.LFB23:
	.cfi_startproc
	cmpl	$64, %edi
	je	.L4
	movl	$3, x(%rip)
	ret
.L4:
	movl	$2, x(%rip)
	ret
	.cfi_endproc
.LFE23:
	.size	hengirmen, .-hengirmen
	.globl	input
	.type	input, @function
input:
.LFB24:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	gets@PLT
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L8
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
	.size	input, .-input
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"x=%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$0, %eax
	call	input
	movl	x(%rip), %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
