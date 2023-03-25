	.file	"bill.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"bill: IAM DYNAMIC LIB we passed %s\n"
	.text
	.globl	bill
	.type	bill, @function
bill:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	bill, .-bill
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
