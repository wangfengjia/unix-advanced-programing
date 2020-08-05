	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
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
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	cmpl	$2, -4(%rbp)
	je	LBB0_2
## %bb.1:
	leaq	L_.str(%rip), %rdi
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	callq	_err_quit
LBB0_2:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rsi
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.2(%rip), %rdi
	movl	$262144, %esi           ## imm = 0x40000
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	L_.str.3(%rip), %rdi
	movl	$1, %esi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_pr_sysconf
	leaq	L_.str.4(%rip), %rdi
	movl	$1024, %esi             ## imm = 0x400
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rcx
	movq	8(%rcx), %rsi
	leaq	L_.str.5(%rip), %rdi
	movl	$2, %edx
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pr_pathconf
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function pr_sysconf
_pr_sysconf:                            ## @pr_sysconf
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rax), %rsi
	callq	_fputs
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	___error
	movl	$0, (%rax)
	movl	-12(%rbp), %edi
	callq	_sysconf
	movq	%rax, -24(%rbp)
	cmpq	$0, %rax
	jge	LBB1_8
## %bb.1:
	callq	___error
	cmpl	$0, (%rax)
	je	LBB1_6
## %bb.2:
	callq	___error
	cmpl	$22, (%rax)
	jne	LBB1_4
## %bb.3:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	leaq	L_.str.6(%rip), %rdi
	callq	_fputs
	jmp	LBB1_5
LBB1_4:
	leaq	L_.str.7(%rip), %rdi
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	callq	_err_sys
LBB1_5:
	jmp	LBB1_7
LBB1_6:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	leaq	L_.str.8(%rip), %rdi
	callq	_fputs
LBB1_7:
	jmp	LBB1_9
LBB1_8:
	movq	-24(%rbp), %rsi
	leaq	L_.str.9(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB1_9:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function pr_pathconf
_pr_pathconf:                           ## @pr_pathconf
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rdi
	movq	(%rax), %rsi
	callq	_fputs
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	callq	___error
	movl	$0, (%rax)
	movq	-16(%rbp), %rdi
	movl	-20(%rbp), %esi
	callq	_pathconf
	movq	%rax, -32(%rbp)
	cmpq	$0, %rax
	jge	LBB2_8
## %bb.1:
	callq	___error
	cmpl	$0, (%rax)
	je	LBB2_6
## %bb.2:
	callq	___error
	cmpl	$22, (%rax)
	jne	LBB2_4
## %bb.3:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	leaq	L_.str.6(%rip), %rdi
	callq	_fputs
	jmp	LBB2_5
LBB2_4:
	movq	-16(%rbp), %rsi
	leaq	L_.str.10(%rip), %rdi
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	callq	_err_sys
LBB2_5:
	jmp	LBB2_7
LBB2_6:
	movq	___stdoutp@GOTPCREL(%rip), %rax
	movq	(%rax), %rsi
	leaq	L_.str.11(%rip), %rdi
	callq	_fputs
LBB2_7:
	jmp	LBB2_9
LBB2_8:
	movq	-32(%rbp), %rsi
	leaq	L_.str.9(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB2_9:
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"usage: a.out <dirname>"

L_.str.1:                               ## @.str.1
	.asciz	"dir name: %s\n"

L_.str.2:                               ## @.str.2
	.asciz	"ARG_MAX defined to be %ld\n"

L_.str.3:                               ## @.str.3
	.asciz	"ARG_MAX = "

L_.str.4:                               ## @.str.4
	.asciz	"MAX_CANON defined to be %ld\n"

L_.str.5:                               ## @.str.5
	.asciz	"MAX_CANNON = "

L_.str.6:                               ## @.str.6
	.asciz	" (not supported)\n"

L_.str.7:                               ## @.str.7
	.asciz	"sysconf error"

L_.str.8:                               ## @.str.8
	.asciz	" (no limits)\n"

L_.str.9:                               ## @.str.9
	.asciz	" %ld\n"

L_.str.10:                              ## @.str.10
	.asciz	"pathconf error, path=%s\n"

L_.str.11:                              ## @.str.11
	.asciz	" (no limit)\n"


.subsections_via_symbols
