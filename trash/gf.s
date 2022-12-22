	.file	"gf.c"
	.text
	.globl	gf_iszero
	.type	gf_iszero, @function
gf_iszero:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movw	%ax, -20(%rbp)
	movzwl	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	subl	$1, -4(%rbp)
	shrl	$19, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	gf_iszero, .-gf_iszero
	.globl	gf_add
	.type	gf_add, @function
gf_add:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-4(%rbp), %eax
	xorw	-8(%rbp), %ax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	gf_add, .-gf_add
	.globl	gf_mul
	.type	gf_mul, @function
gf_mul:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -52(%rbp)
	movw	%ax, -56(%rbp)
	movzwl	-52(%rbp), %eax
	movq	%rax, -24(%rbp)
	movzwl	-56(%rbp), %eax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	andl	$1, %eax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	imulq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	movl	$1, %edx
	movl	%eax, %ecx
	sall	%cl, %edx
	movl	%edx, %eax
	cltq
	andq	-32(%rbp), %rax
	imulq	-24(%rbp), %rax
	xorq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L6:
	cmpl	$12, -4(%rbp)
	jle	.L7
	movq	-16(%rbp), %rax
	andl	$33488896, %eax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	shrq	$9, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$10, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$12, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$13, %rax
	xorq	%rdx, %rax
	xorq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	andl	$57344, %eax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	shrq	$9, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$10, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$12, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$13, %rax
	xorq	%rdx, %rax
	xorq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	andw	$8191, %ax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	gf_mul, .-gf_mul
	.type	gf_sq2, @function
gf_sq2:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movw	%ax, -68(%rbp)
	movabsq	$561850441793536, %rax
	movq	%rax, -64(%rbp)
	movabsq	$1097364144128, %rax
	movq	%rax, -56(%rbp)
	movq	$2143289344, -48(%rbp)
	movq	$4186112, -40(%rbp)
	movzwl	-68(%rbp), %eax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	salq	$24, %rax
	orq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	24+B.0(%rip), %rax
	andq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	salq	$12, %rax
	orq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	16+B.0(%rip), %rax
	andq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	salq	$6, %rax
	orq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	8+B.0(%rip), %rax
	andq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	salq	$3, %rax
	orq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	B.0(%rip), %rax
	andq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movl	-4(%rbp), %eax
	cltq
	movq	-64(%rbp,%rax,8), %rax
	andq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	shrq	$9, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	shrq	$10, %rax
	xorq	%rax, %rdx
	movq	-24(%rbp), %rax
	shrq	$12, %rax
	xorq	%rax, %rdx
	movq	-24(%rbp), %rax
	shrq	$13, %rax
	xorq	%rdx, %rax
	xorq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L10:
	cmpl	$3, -4(%rbp)
	jle	.L11
	movq	-16(%rbp), %rax
	andw	$8191, %ax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	gf_sq2, .-gf_sq2
	.type	gf_sqmul, @function
gf_sqmul:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -68(%rbp)
	movw	%ax, -72(%rbp)
	movabsq	$137170518016, %rax
	movq	%rax, -64(%rbp)
	movq	$267911168, -56(%rbp)
	movq	$516096, -48(%rbp)
	movzwl	-68(%rbp), %eax
	movq	%rax, -24(%rbp)
	movzwl	-72(%rbp), %eax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	salq	$6, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	andl	$64, %eax
	imulq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	salq	$7, %rax
	xorq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	andl	$16385, %eax
	imulq	-32(%rbp), %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$32770, %eax
	imulq	-32(%rbp), %rax
	addq	%rax, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$65540, %eax
	imulq	-32(%rbp), %rax
	salq	$2, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$131080, %eax
	imulq	-32(%rbp), %rax
	salq	$3, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$262160, %eax
	imulq	-32(%rbp), %rax
	salq	$4, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$524320, %eax
	imulq	-32(%rbp), %rax
	salq	$5, %rax
	xorq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L14
.L15:
	movl	-4(%rbp), %eax
	cltq
	movq	-64(%rbp,%rax,8), %rax
	andq	-16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	shrq	$9, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$10, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$12, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$13, %rax
	xorq	%rdx, %rax
	xorq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L14:
	cmpl	$2, -4(%rbp)
	jle	.L15
	movq	-16(%rbp), %rax
	andw	$8191, %ax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	gf_sqmul, .-gf_sqmul
	.type	gf_sq2mul, @function
gf_sq2mul:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -100(%rbp)
	movw	%ax, -104(%rbp)
	movabsq	$2301339409586323456, %rax
	movq	%rax, -96(%rbp)
	movabsq	$4494803534348288, %rax
	movq	%rax, -88(%rbp)
	movabsq	$8778913153024, %rax
	movq	%rax, -80(%rbp)
	movabsq	$17146314752, %rax
	movq	%rax, -72(%rbp)
	movq	$33423360, -64(%rbp)
	movq	$122880, -56(%rbp)
	movzwl	-100(%rbp), %eax
	movq	%rax, -24(%rbp)
	movzwl	-104(%rbp), %eax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	salq	$18, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	andl	$64, %eax
	imulq	%rdx, %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	salq	$21, %rax
	xorq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	andl	$268435457, %eax
	imulq	-32(%rbp), %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$536870914, %eax
	imulq	-32(%rbp), %rax
	salq	$3, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$1073741828, %eax
	imulq	-32(%rbp), %rax
	salq	$6, %rax
	xorq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	andl	$2147483656, %eax
	imulq	-32(%rbp), %rax
	salq	$9, %rax
	xorq	%rax, -16(%rbp)
	movabsq	$4294967312, %rax
	andq	-24(%rbp), %rax
	imulq	-32(%rbp), %rax
	salq	$12, %rax
	xorq	%rax, -16(%rbp)
	movabsq	$8589934624, %rax
	andq	-24(%rbp), %rax
	imulq	-32(%rbp), %rax
	salq	$15, %rax
	xorq	%rax, -16(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L18
.L19:
	movl	-4(%rbp), %eax
	cltq
	movq	-96(%rbp,%rax,8), %rax
	andq	-16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	shrq	$9, %rax
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$10, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$12, %rax
	xorq	%rax, %rdx
	movq	-40(%rbp), %rax
	shrq	$13, %rax
	xorq	%rdx, %rax
	xorq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L18:
	cmpl	$5, -4(%rbp)
	jle	.L19
	movq	-16(%rbp), %rax
	andw	$8191, %ax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	gf_sq2mul, .-gf_sq2mul
	.globl	gf_frac
	.type	gf_frac, @function
gf_frac:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -20(%rbp)
	movw	%ax, -24(%rbp)
	movzwl	-20(%rbp), %edx
	movzwl	-20(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_sqmul
	movw	%ax, -2(%rbp)
	movzwl	-2(%rbp), %edx
	movzwl	-2(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_sq2mul
	movw	%ax, -4(%rbp)
	movzwl	-4(%rbp), %eax
	movl	%eax, %edi
	call	gf_sq2
	movw	%ax, -6(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-6(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_sq2mul
	movw	%ax, -6(%rbp)
	movzwl	-6(%rbp), %eax
	movl	%eax, %edi
	call	gf_sq2
	movw	%ax, -6(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-6(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_sq2mul
	movw	%ax, -6(%rbp)
	movzwl	-24(%rbp), %edx
	movzwl	-6(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_sqmul
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	gf_frac, .-gf_frac
	.globl	gf_inv
	.type	gf_inv, @function
gf_inv:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movl	%edi, %eax
	movw	%ax, -4(%rbp)
	movzwl	-4(%rbp), %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	gf_frac
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	gf_inv, .-gf_inv
	.globl	GF_mul
	.type	GF_mul, @function
GF_mul:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$552, %rsp
	movq	%rdi, -536(%rbp)
	movq	%rsi, -544(%rbp)
	movq	%rdx, -552(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L26
.L27:
	movl	-4(%rbp), %eax
	cltq
	movw	$0, -528(%rbp,%rax,2)
	addl	$1, -4(%rbp)
.L26:
	cmpl	$254, -4(%rbp)
	jle	.L27
	movl	$0, -4(%rbp)
	jmp	.L28
.L31:
	movl	$0, -8(%rbp)
	jmp	.L29
.L30:
	movl	-8(%rbp), %eax
	cltq
	leaq	(%rax,%rax), %rdx
	movq	-552(%rbp), %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	(%rax,%rax), %rcx
	movq	-544(%rbp), %rax
	addq	%rcx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	gf_mul
	movl	%eax, %edx
	movl	-4(%rbp), %ecx
	movl	-8(%rbp), %eax
	addl	%ecx, %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %ecx
	movl	-4(%rbp), %esi
	movl	-8(%rbp), %eax
	addl	%esi, %eax
	xorl	%ecx, %edx
	cltq
	movw	%dx, -528(%rbp,%rax,2)
	addl	$1, -8(%rbp)
.L29:
	cmpl	$127, -8(%rbp)
	jle	.L30
	addl	$1, -4(%rbp)
.L28:
	cmpl	$127, -4(%rbp)
	jle	.L31
	movl	$254, -4(%rbp)
	jmp	.L32
.L33:
	movl	-4(%rbp), %eax
	subl	$121, %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %ecx
	movl	-4(%rbp), %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %edx
	movl	-4(%rbp), %eax
	subl	$121, %eax
	xorl	%ecx, %edx
	cltq
	movw	%dx, -528(%rbp,%rax,2)
	movl	-4(%rbp), %eax
	subl	$126, %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %ecx
	movl	-4(%rbp), %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %edx
	movl	-4(%rbp), %eax
	subl	$126, %eax
	xorl	%ecx, %edx
	cltq
	movw	%dx, -528(%rbp,%rax,2)
	movl	-4(%rbp), %eax
	subl	$127, %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %ecx
	movl	-4(%rbp), %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %edx
	movl	-4(%rbp), %eax
	subl	$127, %eax
	xorl	%ecx, %edx
	cltq
	movw	%dx, -528(%rbp,%rax,2)
	movl	-4(%rbp), %eax
	addl	$-128, %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %ecx
	movl	-4(%rbp), %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %edx
	movl	-4(%rbp), %eax
	addl	$-128, %eax
	xorl	%ecx, %edx
	cltq
	movw	%dx, -528(%rbp,%rax,2)
	subl	$1, -4(%rbp)
.L32:
	cmpl	$127, -4(%rbp)
	jg	.L33
	movl	$0, -4(%rbp)
	jmp	.L34
.L35:
	movl	-4(%rbp), %eax
	cltq
	leaq	(%rax,%rax), %rdx
	movq	-536(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	movzwl	-528(%rbp,%rax,2), %eax
	movw	%ax, (%rdx)
	addl	$1, -4(%rbp)
.L34:
	cmpl	$127, -4(%rbp)
	jle	.L35
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	GF_mul, .-GF_mul
	.section	.rodata
	.align 32
	.type	B.0, @object
	.size	B.0, 32
B.0:
	.quad	1229782938247303441
	.quad	217020518514230019
	.quad	4222189076152335
	.quad	1095216660735
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
