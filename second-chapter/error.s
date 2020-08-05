	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_err_ret                ## -- Begin function err_ret
	.p2align	4, 0x90
_err_ret:                               ## @err_ret
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$400, %rsp              ## imm = 0x190
	testb	%al, %al
	movaps	%xmm7, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -352(%rbp)       ## 16-byte Spill
	movq	%r9, -360(%rbp)         ## 8-byte Spill
	movq	%r8, -368(%rbp)         ## 8-byte Spill
	movq	%rcx, -376(%rbp)        ## 8-byte Spill
	movq	%rdx, -384(%rbp)        ## 8-byte Spill
	movq	%rsi, -392(%rbp)        ## 8-byte Spill
	movq	%rdi, -400(%rbp)        ## 8-byte Spill
	je	LBB0_4
## %bb.3:
	movaps	-352(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -176(%rbp)
	movaps	-336(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -160(%rbp)
	movaps	-320(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -144(%rbp)
	movaps	-304(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -128(%rbp)
	movaps	-288(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -112(%rbp)
	movaps	-272(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -96(%rbp)
	movaps	-256(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -80(%rbp)
	movaps	-240(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -64(%rbp)
LBB0_4:
	movq	-360(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -184(%rbp)
	movq	-368(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -192(%rbp)
	movq	-376(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -200(%rbp)
	movq	-384(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -208(%rbp)
	movq	-392(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -216(%rbp)
	leaq	-32(%rbp), %r8
	movq	___stack_chk_guard@GOTPCREL(%rip), %r9
	movq	(%r9), %r9
	movq	%r9, -8(%rbp)
	movq	-400(%rbp), %r9         ## 8-byte Reload
	movq	%r9, -40(%rbp)
	leaq	-224(%rbp), %r10
	movq	%r10, 16(%r8)
	leaq	16(%rbp), %r10
	movq	%r10, 8(%r8)
	movl	$48, 4(%r8)
	movl	$8, (%r8)
	callq	___error
	leaq	-32(%rbp), %rcx
	movl	(%rax), %esi
	movq	-40(%rbp), %rdx
	movl	$1, %edi
	callq	_err_doit
	leaq	-32(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	LBB0_2
## %bb.1:
	addq	$400, %rsp              ## imm = 0x190
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.p2align	4, 0x90         ## -- Begin function err_doit
_err_doit:                              ## @err_doit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$4192, %eax             ## imm = 0x1060
	callq	____chkstk_darwin
	subq	%rax, %rsp
	xorl	%eax, %eax
	leaq	-4112(%rbp), %r8
	movq	___stack_chk_guard@GOTPCREL(%rip), %r9
	movq	(%r9), %r9
	movq	%r9, -8(%rbp)
	movl	%edi, -4116(%rbp)
	movl	%esi, -4120(%rbp)
	movq	%rdx, -4128(%rbp)
	movq	%rcx, -4136(%rbp)
	movq	-4128(%rbp), %rcx
	movq	-4136(%rbp), %r9
	movq	%r8, %rdi
	movl	$4095, %esi             ## imm = 0xFFF
	movl	%eax, %edx
	movl	$4096, %r8d             ## imm = 0x1000
	movq	%rcx, -4144(%rbp)       ## 8-byte Spill
	movq	%r8, %rcx
	movq	-4144(%rbp), %r8        ## 8-byte Reload
	callq	___vsnprintf_chk
	cmpl	$0, -4116(%rbp)
	je	LBB1_2
## %bb.1:
	leaq	-4112(%rbp), %rax
	movq	%rax, %rdi
	movq	%rax, -4152(%rbp)       ## 8-byte Spill
	callq	_strlen
	movq	-4152(%rbp), %rcx       ## 8-byte Reload
	addq	%rax, %rcx
	movq	-4152(%rbp), %rdi       ## 8-byte Reload
	movq	%rcx, -4160(%rbp)       ## 8-byte Spill
	callq	_strlen
	movl	$4096, %ecx             ## imm = 0x1000
	subq	%rax, %rcx
	subq	$1, %rcx
	movl	-4120(%rbp), %edi
	movq	%rcx, -4168(%rbp)       ## 8-byte Spill
	callq	_strerror
	xorl	%edx, %edx
	movq	-4160(%rbp), %rdi       ## 8-byte Reload
	movq	-4168(%rbp), %rsi       ## 8-byte Reload
	movq	$-1, %rcx
	leaq	L_.str(%rip), %r8
	movq	%rax, %r9
	movb	$0, %al
	callq	___snprintf_chk
LBB1_2:
	leaq	-4112(%rbp), %rdi
	leaq	L_.str.1(%rip), %rsi
	movl	$4096, %edx             ## imm = 0x1000
	callq	___strcat_chk
	movq	___stdoutp@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rdi
	movq	%rax, -4176(%rbp)       ## 8-byte Spill
	callq	_fflush
	movq	___stderrp@GOTPCREL(%rip), %rcx
	leaq	-4112(%rbp), %rdi
	movq	(%rcx), %rsi
	movl	%eax, -4180(%rbp)       ## 4-byte Spill
	callq	_fputs
	xorl	%r8d, %r8d
	movl	%r8d, %edi
	movl	%eax, -4184(%rbp)       ## 4-byte Spill
	callq	_fflush
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	LBB1_4
## %bb.3:
	addq	$4192, %rsp             ## imm = 0x1060
	popq	%rbp
	retq
LBB1_4:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_err_sys                ## -- Begin function err_sys
	.p2align	4, 0x90
_err_sys:                               ## @err_sys
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$400, %rsp              ## imm = 0x190
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%r9, -344(%rbp)         ## 8-byte Spill
	movq	%r8, -352(%rbp)         ## 8-byte Spill
	movq	%rcx, -360(%rbp)        ## 8-byte Spill
	movq	%rdx, -368(%rbp)        ## 8-byte Spill
	movq	%rsi, -376(%rbp)        ## 8-byte Spill
	movq	%rdi, -384(%rbp)        ## 8-byte Spill
	je	LBB2_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB2_2:
	movq	-344(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-352(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-360(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-368(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-376(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-384(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r9
	movq	%r9, -16(%rbp)
	leaq	16(%rbp), %r9
	movq	%r9, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	callq	___error
	movl	(%rax), %esi
	movq	-8(%rbp), %rdx
	movl	$1, %r10d
	leaq	-32(%rbp), %rcx
	movl	%r10d, %edi
	movl	%r10d, -388(%rbp)       ## 4-byte Spill
	callq	_err_doit
	movl	-388(%rbp), %edi        ## 4-byte Reload
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_err_cont               ## -- Begin function err_cont
	.p2align	4, 0x90
_err_cont:                              ## @err_cont
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$416, %rsp              ## imm = 0x1A0
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	testb	%al, %al
	movaps	%xmm7, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -352(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -368(%rbp)       ## 16-byte Spill
	movq	%r9, -376(%rbp)         ## 8-byte Spill
	movq	%r8, -384(%rbp)         ## 8-byte Spill
	movq	%rcx, -392(%rbp)        ## 8-byte Spill
	movq	%rdx, -400(%rbp)        ## 8-byte Spill
	movq	%rsi, -408(%rbp)        ## 8-byte Spill
	movl	%edi, -412(%rbp)        ## 4-byte Spill
	je	LBB3_4
## %bb.3:
	movaps	-368(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -192(%rbp)
	movaps	-352(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -176(%rbp)
	movaps	-336(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -160(%rbp)
	movaps	-320(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -144(%rbp)
	movaps	-304(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -128(%rbp)
	movaps	-288(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -112(%rbp)
	movaps	-272(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -96(%rbp)
	movaps	-256(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -80(%rbp)
LBB3_4:
	movq	-376(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -200(%rbp)
	movq	-384(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -208(%rbp)
	movq	-392(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -216(%rbp)
	movq	-400(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -224(%rbp)
	leaq	-48(%rbp), %rdi
	movq	___stack_chk_guard@GOTPCREL(%rip), %r8
	movq	(%r8), %r8
	movq	%r8, -24(%rbp)
	movl	-412(%rbp), %r9d        ## 4-byte Reload
	movl	%r9d, -52(%rbp)
	movq	-408(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -64(%rbp)
	movq	%rdi, %r10
	leaq	-240(%rbp), %r11
	movq	%r11, 16(%r10)
	leaq	16(%rbp), %r11
	movq	%r11, 8(%r10)
	movl	$48, 4(%r10)
	movl	$16, (%r10)
	movl	-52(%rbp), %ebx
	movq	-64(%rbp), %rdx
	movl	$1, %r14d
	movq	%rdi, -424(%rbp)        ## 8-byte Spill
	movl	%r14d, %edi
	movl	%ebx, %esi
	movq	-424(%rbp), %rcx        ## 8-byte Reload
	callq	_err_doit
	leaq	-48(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-24(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	LBB3_2
## %bb.1:
	addq	$416, %rsp              ## imm = 0x1A0
	popq	%rbx
	popq	%r14
	popq	%rbp
	retq
LBB3_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_err_exit               ## -- Begin function err_exit
	.p2align	4, 0x90
_err_exit:                              ## @err_exit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$400, %rsp              ## imm = 0x190
	testb	%al, %al
	movaps	%xmm7, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -352(%rbp)       ## 16-byte Spill
	movq	%r9, -360(%rbp)         ## 8-byte Spill
	movq	%r8, -368(%rbp)         ## 8-byte Spill
	movq	%rcx, -376(%rbp)        ## 8-byte Spill
	movq	%rdx, -384(%rbp)        ## 8-byte Spill
	movq	%rsi, -392(%rbp)        ## 8-byte Spill
	movl	%edi, -396(%rbp)        ## 4-byte Spill
	je	LBB4_2
## %bb.1:
	movaps	-352(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -176(%rbp)
	movaps	-336(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -160(%rbp)
	movaps	-320(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -144(%rbp)
	movaps	-304(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -128(%rbp)
	movaps	-288(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -112(%rbp)
	movaps	-272(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -96(%rbp)
	movaps	-256(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -80(%rbp)
	movaps	-240(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -64(%rbp)
LBB4_2:
	movq	-360(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -184(%rbp)
	movq	-368(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -192(%rbp)
	movq	-376(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -200(%rbp)
	movq	-384(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -208(%rbp)
	movl	-396(%rbp), %edi        ## 4-byte Reload
	movl	%edi, -4(%rbp)
	movq	-392(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -16(%rbp)
	leaq	-224(%rbp), %r9
	movq	%r9, -32(%rbp)
	leaq	16(%rbp), %r9
	movq	%r9, -40(%rbp)
	movl	$48, -44(%rbp)
	movl	$16, -48(%rbp)
	movl	-4(%rbp), %r10d
	movq	-16(%rbp), %rdx
	movl	$1, %r11d
	leaq	-48(%rbp), %rcx
	movl	%r11d, %edi
	movl	%r10d, %esi
	movl	%r11d, -400(%rbp)       ## 4-byte Spill
	callq	_err_doit
	movl	-400(%rbp), %edi        ## 4-byte Reload
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.globl	_err_dump               ## -- Begin function err_dump
	.p2align	4, 0x90
_err_dump:                              ## @err_dump
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$384, %rsp              ## imm = 0x180
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%r9, -344(%rbp)         ## 8-byte Spill
	movq	%r8, -352(%rbp)         ## 8-byte Spill
	movq	%rcx, -360(%rbp)        ## 8-byte Spill
	movq	%rdx, -368(%rbp)        ## 8-byte Spill
	movq	%rsi, -376(%rbp)        ## 8-byte Spill
	movq	%rdi, -384(%rbp)        ## 8-byte Spill
	je	LBB5_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB5_2:
	movq	-344(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-352(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-360(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-368(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-376(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-384(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r9
	movq	%r9, -16(%rbp)
	leaq	16(%rbp), %r9
	movq	%r9, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	callq	___error
	movl	(%rax), %esi
	movq	-8(%rbp), %rdx
	movl	$1, %edi
	leaq	-32(%rbp), %rcx
	callq	_err_doit
	callq	_abort
	.cfi_endproc
                                        ## -- End function
	.globl	_err_msg                ## -- Begin function err_msg
	.p2align	4, 0x90
_err_msg:                               ## @err_msg
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$408, %rsp              ## imm = 0x198
	.cfi_offset %rbx, -24
	testb	%al, %al
	movaps	%xmm7, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -336(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -352(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -368(%rbp)       ## 16-byte Spill
	movq	%r9, -376(%rbp)         ## 8-byte Spill
	movq	%r8, -384(%rbp)         ## 8-byte Spill
	movq	%rcx, -392(%rbp)        ## 8-byte Spill
	movq	%rdx, -400(%rbp)        ## 8-byte Spill
	movq	%rsi, -408(%rbp)        ## 8-byte Spill
	movq	%rdi, -416(%rbp)        ## 8-byte Spill
	je	LBB6_4
## %bb.3:
	movaps	-368(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -192(%rbp)
	movaps	-352(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -176(%rbp)
	movaps	-336(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -160(%rbp)
	movaps	-320(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -144(%rbp)
	movaps	-304(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -128(%rbp)
	movaps	-288(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -112(%rbp)
	movaps	-272(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -96(%rbp)
	movaps	-256(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -80(%rbp)
LBB6_4:
	movq	-376(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -200(%rbp)
	movq	-384(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -208(%rbp)
	movq	-392(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -216(%rbp)
	movq	-400(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -224(%rbp)
	movq	-408(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -232(%rbp)
	xorl	%r8d, %r8d
	leaq	-48(%rbp), %r9
	movq	___stack_chk_guard@GOTPCREL(%rip), %r10
	movq	(%r10), %r10
	movq	%r10, -16(%rbp)
	movq	-416(%rbp), %r10        ## 8-byte Reload
	movq	%r10, -56(%rbp)
	movq	%r9, %r11
	leaq	-240(%rbp), %rbx
	movq	%rbx, 16(%r11)
	leaq	16(%rbp), %rbx
	movq	%rbx, 8(%r11)
	movl	$48, 4(%r11)
	movl	$8, (%r11)
	movq	-56(%rbp), %rdx
	movl	%r8d, %edi
	movl	%r8d, %esi
	movq	%r9, %rcx
	callq	_err_doit
	leaq	-48(%rbp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-16(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	LBB6_2
## %bb.1:
	addq	$408, %rsp              ## imm = 0x198
	popq	%rbx
	popq	%rbp
	retq
LBB6_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_err_quit               ## -- Begin function err_quit
	.p2align	4, 0x90
_err_quit:                              ## @err_quit
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$384, %rsp              ## imm = 0x180
	testb	%al, %al
	movaps	%xmm7, -224(%rbp)       ## 16-byte Spill
	movaps	%xmm6, -240(%rbp)       ## 16-byte Spill
	movaps	%xmm5, -256(%rbp)       ## 16-byte Spill
	movaps	%xmm4, -272(%rbp)       ## 16-byte Spill
	movaps	%xmm3, -288(%rbp)       ## 16-byte Spill
	movaps	%xmm2, -304(%rbp)       ## 16-byte Spill
	movaps	%xmm1, -320(%rbp)       ## 16-byte Spill
	movaps	%xmm0, -336(%rbp)       ## 16-byte Spill
	movq	%r9, -344(%rbp)         ## 8-byte Spill
	movq	%r8, -352(%rbp)         ## 8-byte Spill
	movq	%rcx, -360(%rbp)        ## 8-byte Spill
	movq	%rdx, -368(%rbp)        ## 8-byte Spill
	movq	%rsi, -376(%rbp)        ## 8-byte Spill
	movq	%rdi, -384(%rbp)        ## 8-byte Spill
	je	LBB7_2
## %bb.1:
	movaps	-336(%rbp), %xmm0       ## 16-byte Reload
	movaps	%xmm0, -160(%rbp)
	movaps	-320(%rbp), %xmm1       ## 16-byte Reload
	movaps	%xmm1, -144(%rbp)
	movaps	-304(%rbp), %xmm2       ## 16-byte Reload
	movaps	%xmm2, -128(%rbp)
	movaps	-288(%rbp), %xmm3       ## 16-byte Reload
	movaps	%xmm3, -112(%rbp)
	movaps	-272(%rbp), %xmm4       ## 16-byte Reload
	movaps	%xmm4, -96(%rbp)
	movaps	-256(%rbp), %xmm5       ## 16-byte Reload
	movaps	%xmm5, -80(%rbp)
	movaps	-240(%rbp), %xmm6       ## 16-byte Reload
	movaps	%xmm6, -64(%rbp)
	movaps	-224(%rbp), %xmm7       ## 16-byte Reload
	movaps	%xmm7, -48(%rbp)
LBB7_2:
	movq	-344(%rbp), %rax        ## 8-byte Reload
	movq	%rax, -168(%rbp)
	movq	-352(%rbp), %rcx        ## 8-byte Reload
	movq	%rcx, -176(%rbp)
	movq	-360(%rbp), %rdx        ## 8-byte Reload
	movq	%rdx, -184(%rbp)
	movq	-368(%rbp), %rsi        ## 8-byte Reload
	movq	%rsi, -192(%rbp)
	movq	-376(%rbp), %rdi        ## 8-byte Reload
	movq	%rdi, -200(%rbp)
	movq	-384(%rbp), %r8         ## 8-byte Reload
	movq	%r8, -8(%rbp)
	leaq	-208(%rbp), %r9
	movq	%r9, -16(%rbp)
	leaq	16(%rbp), %r9
	movq	%r9, -24(%rbp)
	movl	$48, -28(%rbp)
	movl	$8, -32(%rbp)
	movq	-8(%rbp), %rdx
	xorl	%r10d, %r10d
	leaq	-32(%rbp), %rcx
	movl	%r10d, %edi
	movl	%r10d, %esi
	callq	_err_doit
	movl	$1, %edi
	callq	_exit
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	": %s"

L_.str.1:                               ## @.str.1
	.asciz	"\n"


.subsections_via_symbols
