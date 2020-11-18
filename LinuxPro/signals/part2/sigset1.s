	.file	"sigset1.c"
	.section	.rodata
.LC0:
	.string	"\n %s: \n"
.LC1:
	.string	" I am in sighandler %d \n"
	.text
	.globl	sighand
	.type	sighand, @function
sighand:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	$__func__.2630, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	sighand, .-sighand
	.section	.rodata
.LC2:
	.string	"pid %d\n"
.LC3:
	.string	"sig1"
.LC4:
	.string	"sig4"
.LC5:
	.string	"sigmask"
	.align 8
.LC6:
	.string	" Send me signal one and see the effect now "
.LC7:
	.string	" Now signals are unblocked "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	$sighand, %esi
	movl	$62, %edi
	call	signal
	movl	$sighand, %esi
	movl	$4, %edi
	call	signal
	movl	$0, %eax
	call	getpid
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leaq	-128(%rbp), %rax
	movq	%rax, %rdi
	call	sigemptyset
	leaq	-128(%rbp), %rax
	movl	$62, %esi
	movq	%rax, %rdi
	call	sigaddset
	movl	$.LC3, %edi
	call	perror
	leaq	-128(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	sigaddset
	movl	$.LC4, %edi
	call	perror
	leaq	-128(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$2, %edi
	call	sigprocmask
	movl	$.LC5, %edi
	call	perror
	movl	$.LC6, %edi
	call	puts
	call	getchar
	leaq	-128(%rbp), %rax
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$1, %edi
	call	sigprocmask
	movl	$.LC7, %edi
	call	puts
.L3:
	jmp	.L3
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.type	__func__.2630, @object
	.size	__func__.2630, 8
__func__.2630:
	.string	"sighand"
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
