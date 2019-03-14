	.text
	.file	"main.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movabsq	$_ZStL8__ioinit, %rdi
	callq	_ZNSt8ios_base4InitC1Ev
	movabsq	$_ZNSt8ios_base4InitD1Ev, %rdi
	movabsq	$_ZStL8__ioinit, %rsi
	movabsq	$__dso_handle, %rdx
	callq	__cxa_atexit
	movl	%eax, -4(%rbp)          # 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	__BranchCoverage_onBranch # -- Begin function __BranchCoverage_onBranch
	.p2align	4, 0x90
	.type	__BranchCoverage_onBranch,@function
__BranchCoverage_onBranch:              # @__BranchCoverage_onBranch
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movb	%dil, %al
	andb	$1, %al
	movb	%al, -1(%rbp)
	movb	-1(%rbp), %al
	testb	$1, %al
	movabsq	$.L.str.1, %rcx
	movabsq	$.L.str.2, %rdx
	cmovneq	%rcx, %rdx
	movabsq	$.L.str, %rdi
	movq	%rdx, %rsi
	movb	$0, %al
	callq	printf
	movl	%eax, -8(%rbp)          # 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	__BranchCoverage_onBranch, .Lfunc_end1-__BranchCoverage_onBranch
	.cfi_endproc
                                        # -- End function
	.globl	__BranchCoverage_onMultiBranch # -- Begin function __BranchCoverage_onMultiBranch
	.p2align	4, 0x90
	.type	__BranchCoverage_onMultiBranch,@function
__BranchCoverage_onMultiBranch:         # @__BranchCoverage_onMultiBranch
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %esi
	movl	-8(%rbp), %edx
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -12(%rbp)         # 4-byte Spill
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	__BranchCoverage_onMultiBranch, .Lfunc_end2-__BranchCoverage_onMultiBranch
	.cfi_endproc
                                        # -- End function
	.globl	testSwitch              # -- Begin function testSwitch
	.p2align	4, 0x90
	.type	testSwitch,@function
testSwitch:                             # @testSwitch
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	%edi, -8(%rbp)
	movl	-8(%rbp), %edi
	movl	%edi, %eax
	movq	%rax, %rcx
	subq	$5, %rcx
	movq	%rax, -16(%rbp)         # 8-byte Spill
	movq	%rcx, -24(%rbp)         # 8-byte Spill
	ja	.LBB3_5
# %bb.7:
	movq	-16(%rbp), %rax         # 8-byte Reload
	movq	.LJTI3_0(,%rax,8), %rcx
	jmpq	*%rcx
.LBB3_1:
	movl	$1, %edi
	movl	$5, %esi
	callq	__BranchCoverage_onMultiBranch
	movl	$1, -4(%rbp)
	jmp	.LBB3_6
.LBB3_2:
	movl	$2, %edi
	movl	$5, %esi
	callq	__BranchCoverage_onMultiBranch
	movl	$2, -4(%rbp)
	jmp	.LBB3_6
.LBB3_3:
	movl	$3, %edi
	movl	$5, %esi
	callq	__BranchCoverage_onMultiBranch
	movl	$3, -4(%rbp)
	jmp	.LBB3_6
.LBB3_4:
	movl	$4, %edi
	movl	$5, %esi
	callq	__BranchCoverage_onMultiBranch
	movl	$100, -4(%rbp)
	jmp	.LBB3_6
.LBB3_5:
	xorl	%edi, %edi
	movl	$5, %esi
	callq	__BranchCoverage_onMultiBranch
	movl	$0, -4(%rbp)
.LBB3_6:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end3:
	.size	testSwitch, .Lfunc_end3-testSwitch
	.cfi_endproc
	.section	.rodata,"a",@progbits
	.p2align	3
.LJTI3_0:
	.quad	.LBB3_1
	.quad	.LBB3_2
	.quad	.LBB3_3
	.quad	.LBB3_5
	.quad	.LBB3_5
	.quad	.LBB3_4
                                        # -- End function
	.text
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	-8(%rbp), %edi
	callq	testSwitch
	movabsq	$.L.str.4, %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	printf
	cmpl	$1, -8(%rbp)
	sete	%cl
	movzbl	%cl, %esi
	andl	$1, %esi
	movl	%esi, %edi
	movl	%eax, -20(%rbp)         # 4-byte Spill
	movb	%cl, -21(%rbp)          # 1-byte Spill
	callq	__BranchCoverage_onBranch
	movb	-21(%rbp), %cl          # 1-byte Reload
	testb	$1, %cl
	jne	.LBB4_1
	jmp	.LBB4_2
.LBB4_1:
	movl	$0, -4(%rbp)
	jmp	.LBB4_5
.LBB4_2:
	cmpl	$2, -8(%rbp)
	sete	%al
	movzbl	%al, %ecx
	andl	$1, %ecx
	movl	%ecx, %edi
	movb	%al, -22(%rbp)          # 1-byte Spill
	callq	__BranchCoverage_onBranch
	movb	-22(%rbp), %al          # 1-byte Reload
	testb	$1, %al
	jne	.LBB4_3
	jmp	.LBB4_4
.LBB4_3:
	movl	$1, -4(%rbp)
	jmp	.LBB4_5
.LBB4_4:
	movl	$2, -4(%rbp)
.LBB4_5:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end4:
	.size	main, .Lfunc_end4-main
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_main.cpp
	.type	_GLOBAL__sub_I_main.cpp,@function
_GLOBAL__sub_I_main.cpp:                # @_GLOBAL__sub_I_main.cpp
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	callq	__cxx_global_var_init
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end5:
	.size	_GLOBAL__sub_I_main.cpp, .Lfunc_end5-_GLOBAL__sub_I_main.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"onBranch: %s\n"
	.size	.L.str, 14

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"true"
	.size	.L.str.1, 5

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"false"
	.size	.L.str.2, 6

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"onMultiBranch: %d/%d\n"
	.size	.L.str.3, 22

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"%d\n"
	.size	.L.str.4, 4

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_main.cpp

	.ident	"clang version 7.0.1 (tags/RELEASE_701/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __cxx_global_var_init
	.addrsig_sym __cxa_atexit
	.addrsig_sym __BranchCoverage_onBranch
	.addrsig_sym printf
	.addrsig_sym __BranchCoverage_onMultiBranch
	.addrsig_sym testSwitch
	.addrsig_sym main
	.addrsig_sym _GLOBAL__sub_I_main.cpp
	.addrsig_sym __BranchCoverage_onInfiniteBranch
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
