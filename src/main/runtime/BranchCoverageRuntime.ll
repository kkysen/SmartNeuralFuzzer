; ModuleID = 'BranchCoverageRuntime.cpp'
source_filename = "BranchCoverageRuntime.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }
%"class.std::basic_ostream" = type { i32 (...)**, %"class.std::basic_ios" }
%"class.std::basic_ios" = type { %"class.std::ios_base", %"class.std::basic_ostream"*, i8, i8, %"class.std::basic_streambuf"*, %"class.std::ctype"*, %"class.std::num_put"*, %"class.std::num_get"* }
%"class.std::ios_base" = type { i32 (...)**, i64, i64, i32, i32, i32, %"struct.std::ios_base::_Callback_list"*, %"struct.std::ios_base::_Words", [8 x %"struct.std::ios_base::_Words"], i32, %"struct.std::ios_base::_Words"*, %"class.std::locale" }
%"struct.std::ios_base::_Callback_list" = type { %"struct.std::ios_base::_Callback_list"*, void (i32, %"class.std::ios_base"*, i32)*, i32, i32 }
%"struct.std::ios_base::_Words" = type { i8*, i64 }
%"class.std::locale" = type { %"class.std::locale::_Impl"* }
%"class.std::locale::_Impl" = type { i32, %"class.std::locale::facet"**, i64, %"class.std::locale::facet"**, i8** }
%"class.std::locale::facet" = type <{ i32 (...)**, i32, [4 x i8] }>
%"class.std::basic_streambuf" = type { i32 (...)**, i8*, i8*, i8*, i8*, i8*, i8*, %"class.std::locale" }
%"class.std::ctype" = type <{ %"class.std::locale::facet.base", [4 x i8], %struct.__locale_struct*, i8, [7 x i8], i32*, i32*, i16*, i8, [256 x i8], [256 x i8], i8, [6 x i8] }>
%"class.std::locale::facet.base" = type <{ i32 (...)**, i32 }>
%struct.__locale_struct = type { [13 x %struct.__locale_data*], i16*, i32*, i32*, [13 x i8*] }
%struct.__locale_data = type opaque
%"class.std::num_put" = type { %"class.std::locale::facet.base", [4 x i8] }
%"class.std::num_get" = type { %"class.std::locale::facet.base", [4 x i8] }
%"class.debug::Indentation" = type { i64, %"class.std::__cxx11::basic_string" }
%"class.std::__cxx11::basic_string" = type { %"struct.std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Alloc_hider", i64, %union.anon }
%"struct.std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Alloc_hider" = type { i8* }
%union.anon = type { i64, [8 x i8] }
%"class.(anonymous namespace)::BranchCoverageRuntime" = type { %"struct.(anonymous namespace)::BranchCoverageRuntime::Branches", %"class.(anonymous namespace)::BranchCoverageRuntime::Counts" }
%"struct.(anonymous namespace)::BranchCoverageRuntime::Branches" = type { %"class.(anonymous namespace)::BranchCoverageRuntime::SingleBranches", %"class.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches" }
%"class.(anonymous namespace)::BranchCoverageRuntime::SingleBranches" = type <{ %"struct.std::array", i32, i32, %"class.(anonymous namespace)::BranchCoverageRuntime::Write", [4 x i8] }>
%"struct.std::array" = type { [512 x i64] }
%"class.(anonymous namespace)::BranchCoverageRuntime::Write" = type { i32 }
%"class.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches" = type <{ %"struct.std::array.0", i64, %"class.(anonymous namespace)::BranchCoverageRuntime::Write", [4 x i8] }>
%"struct.std::array.0" = type { [1024 x %"struct.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches::Record"] }
%"struct.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches::Record" = type { i32, i32, i32 }
%"class.(anonymous namespace)::BranchCoverageRuntime::Counts" = type <{ %union.anon.1, %"class.(anonymous namespace)::BranchCoverageRuntime::Write", [4 x i8] }>
%union.anon.1 = type { %struct.anon }
%struct.anon = type { i64, i64, i64 }
%class.LazilyConstructed = type { %"class.std::unique_ptr" }
%"class.std::unique_ptr" = type { %"class.std::__uniq_ptr_impl" }
%"class.std::__uniq_ptr_impl" = type { %"class.std::tuple" }
%"class.std::tuple" = type { %"struct.std::_Tuple_impl" }
%"struct.std::_Tuple_impl" = type { %"struct.std::_Head_base.4" }
%"struct.std::_Head_base.4" = type { %"class.(anonymous namespace)::BranchCoverageRuntime"* }
%"class.(anonymous namespace)::BranchCoverageRuntime::Output" = type { %"class.std::experimental::filesystem::v1::__cxx11::path"*, i32, i32, %struct.anon.8 }
%"class.std::experimental::filesystem::v1::__cxx11::path" = type <{ %"class.std::__cxx11::basic_string", %"class.std::vector", i8, [7 x i8] }>
%"class.std::vector" = type { %"struct.std::_Vector_base" }
%"struct.std::_Vector_base" = type { %"struct.std::_Vector_base<std::experimental::filesystem::v1::__cxx11::path::_Cmpt, std::allocator<std::experimental::filesystem::v1::__cxx11::path::_Cmpt> >::_Vector_impl" }
%"struct.std::_Vector_base<std::experimental::filesystem::v1::__cxx11::path::_Cmpt, std::allocator<std::experimental::filesystem::v1::__cxx11::path::_Cmpt> >::_Vector_impl" = type { %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* }
%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt" = type { %"class.std::experimental::filesystem::v1::__cxx11::path.base", i64 }
%"class.std::experimental::filesystem::v1::__cxx11::path.base" = type <{ %"class.std::__cxx11::basic_string", %"class.std::vector", i8 }>
%struct.anon.8 = type { i32, i32 }
%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error" = type { %"class.std::system_error", %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::__cxx11::basic_string" }
%"class.std::system_error" = type { %"class.std::runtime_error", %"struct.std::error_code" }
%"class.std::runtime_error" = type { %"class.std::exception", %"struct.std::__cow_string" }
%"class.std::exception" = type { i32 (...)** }
%"struct.std::__cow_string" = type { %union.anon.9 }
%union.anon.9 = type { i8* }
%"struct.std::error_code" = type { i32, %"class.std::_V2::error_category"* }
%"class.std::_V2::error_category" = type { i32 (...)** }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

$_ZN5debug11IndentationD2Ev = comdat any

$__clang_call_terminate = comdat any

$_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev = comdat any

$_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev = comdat any

$_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_ = comdat any

$_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_ = comdat any

$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm = comdat any

$_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm = comdat any

$_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z = comdat any

$_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code = comdat any

$_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE = comdat any

$_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv = comdat any

$_ZNSt12experimental10filesystem2v17__cxx114pathC2INSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES3_EERKT_ = comdat any

$_ZNSt12experimental10filesystem2v17__cxx114pathC2ERKS3_ = comdat any

$_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EEC2ERKS7_ = comdat any

$_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPKNSt12experimental10filesystem2v17__cxx114path5_CmptESt6vectorIS9_SaIS9_EEEEPS9_EET0_T_SI_SH_ = comdat any

$_ZNSt12experimental10filesystem2v17__cxx114path9_M_appendERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE = comdat any

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external hidden global i8
@_ZN5debug4modeE = local_unnamed_addr global i8 1, align 1
@_ZSt4cout = external global %"class.std::basic_ostream", align 8
@_ZN5debug3outE = local_unnamed_addr global %"class.std::basic_ostream"* @_ZSt4cout, align 8
@_ZN5debug8reversedE = local_unnamed_addr global i8 0, align 1
@_ZN5debug11Indentation11defaultCharE = local_unnamed_addr global i8 32, align 1
@_ZN5debug11Indentation13defaultIndentE = local_unnamed_addr global i64 4, align 8
@_ZN5debug11indentationE = global %"class.debug::Indentation" zeroinitializer, align 8
@.str = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@_ZN3fseL8pageSizeE = internal global i64 0, align 8
@_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE = internal global { { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } } zeroinitializer, align 8
@.str.5 = private unnamed_addr constant [30 x i8] c"BranchCoverage: onBranch: %s\0A\00", align 1
@.str.6 = private unnamed_addr constant [38 x i8] c"BranchCoverage: onMultiBranch: %d/%d\0A\00", align 1
@.str.7 = private unnamed_addr constant [38 x i8] c"BranchCoverage: onInfiniteBranch: %p\0A\00", align 1
@.str.8 = private unnamed_addr constant [20 x i8] c"coverage.branch.out\00", align 1
@.str.9 = private unnamed_addr constant [42 x i8] c"basic_string::_M_construct null not valid\00", align 1
@.str.10 = private unnamed_addr constant [24 x i8] c"basic_string::_M_create\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.12 = private unnamed_addr constant [4 x i8] c"dir\00", align 1
@.str.13 = private unnamed_addr constant [21 x i8] c"basic_string::append\00", align 1
@.str.15 = private unnamed_addr constant [25 x i8] c"basic_string::_M_replace\00", align 1
@.str.17 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.18 = private unnamed_addr constant [7 x i8] c"counts\00", align 1
@.str.19 = private unnamed_addr constant [7 x i8] c"single\00", align 1
@.str.20 = private unnamed_addr constant [10 x i8] c"nonSingle\00", align 1
@.str.21 = private unnamed_addr constant [15 x i8] c"createDir:open\00", align 1
@_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE = external constant i8*
@_ZTVNSt12experimental10filesystem2v17__cxx1116filesystem_errorE = external unnamed_addr constant { [5 x i8*] }
@.str.22 = private unnamed_addr constant [3 x i8] c": \00", align 1
@_ZTVSt12system_error = external unnamed_addr constant { [5 x i8*] }, align 8
@.str.23 = private unnamed_addr constant [19 x i8] c"filesystem error: \00", align 1
@.str.24 = private unnamed_addr constant [3 x i8] c" [\00", align 1
@.str.25 = private unnamed_addr constant [29 x i8] c"basic_string::_M_replace_aux\00", align 1
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_BranchCoverageRuntime.cpp, i8* null }]

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) unnamed_addr #0

; Function Attrs: nounwind
declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) unnamed_addr #1

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) local_unnamed_addr #2

; Function Attrs: inlinehint nounwind uwtable
define linkonce_odr void @_ZN5debug11IndentationD2Ev(%"class.debug::Indentation"*) unnamed_addr #3 comdat align 2 personality i32 (...)* @__gxx_personality_v0 {
  %2 = getelementptr inbounds %"class.debug::Indentation", %"class.debug::Indentation"* %0, i64 0, i32 1, i32 0, i32 0
  %3 = load i8*, i8** %2, align 8, !tbaa !2
  %4 = getelementptr inbounds %"class.debug::Indentation", %"class.debug::Indentation"* %0, i64 0, i32 1, i32 2
  %5 = bitcast %union.anon* %4 to i8*
  %6 = icmp eq i8* %3, %5
  br i1 %6, label %8, label %7

; <label>:7:                                      ; preds = %1
  tail call void @_ZdlPv(i8* %3) #2
  br label %8

; <label>:8:                                      ; preds = %1, %7
  ret void
}

; Function Attrs: uwtable
define nonnull dereferenceable(272) %"class.std::basic_ostream"* @_ZlsRSob(%"class.std::basic_ostream"* returned dereferenceable(272), i1 zeroext) local_unnamed_addr #4 {
  %3 = select i1 %1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0)
  %4 = select i1 %1, i64 4, i64 5
  %5 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(%"class.std::basic_ostream"* nonnull dereferenceable(272) %0, i8* nonnull %3, i64 %4)
  ret %"class.std::basic_ostream"* %0
}

; Function Attrs: nounwind
declare i64 @sysconf(i32) local_unnamed_addr #1

; Function Attrs: argmemonly nounwind
declare {}* @llvm.invariant.start.p0i8(i64, i8* nocapture) #5

; Function Attrs: inlinehint nounwind uwtable
define internal void @_ZN17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEED2Ev(%class.LazilyConstructed* nocapture) unnamed_addr #3 align 2 personality i32 (...)* @__gxx_personality_v0 {
  %2 = getelementptr inbounds %class.LazilyConstructed, %class.LazilyConstructed* %0, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0
  %3 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** %2, align 8, !tbaa !9
  %4 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, null
  br i1 %4, label %6, label %5

; <label>:5:                                      ; preds = %1
  tail call fastcc void @_ZNKSt14default_deleteIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEPS1_(%"class.(anonymous namespace)::BranchCoverageRuntime"* nonnull %3) #2
  br label %6

; <label>:6:                                      ; preds = %1, %5
  store %"class.(anonymous namespace)::BranchCoverageRuntime"* null, %"class.(anonymous namespace)::BranchCoverageRuntime"** %2, align 8, !tbaa !9
  ret void
}

; Function Attrs: uwtable
define void @__BranchCoverage_onSingleBranch(i1 zeroext) local_unnamed_addr #4 personality i32 (...)* @__gxx_personality_v0 {
  %2 = select i1 %0, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0)
  %3 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i64 0, i64 0), i8* %2)
  %4 = tail call fastcc dereferenceable(16448) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZNK17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEv()
  %5 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 1, i32 0, i32 0, i32 0
  %6 = load i64, i64* %5, align 8, !tbaa !10
  %7 = add i64 %6, 1
  store i64 %7, i64* %5, align 8, !tbaa !10
  %8 = zext i1 %0 to i64
  %9 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 0, i32 1
  %10 = load i32, i32* %9, align 8, !tbaa !11
  %11 = and i32 %10, 63
  %12 = zext i32 %11 to i64
  %13 = shl i64 %8, %12
  %14 = lshr i32 %10, 6
  %15 = zext i32 %14 to i64
  %16 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 0, i32 0, i32 0, i64 %15
  %17 = load i64, i64* %16, align 8, !tbaa !16
  %18 = or i64 %13, %17
  store i64 %18, i64* %16, align 8, !tbaa !16
  %19 = add i32 %10, 1
  store i32 %19, i32* %9, align 8, !tbaa !11
  %20 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 0, i32 2
  %21 = load i32, i32* %20, align 4, !tbaa !17
  %22 = add i32 %21, 1
  store i32 %22, i32* %20, align 4, !tbaa !17
  %23 = and i32 %19, -64
  %24 = icmp eq i32 %23, 32768
  br i1 %24, label %25, label %34

; <label>:25:                                     ; preds = %1
  %26 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime"* %4 to i8*
  %27 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 0, i32 3, i32 0
  %28 = load i32, i32* %27, align 4, !tbaa !18
  %29 = invoke i64 @write(i32 %28, i8* nonnull %26, i64 4096)
          to label %33 unwind label %30

; <label>:30:                                     ; preds = %25
  %31 = landingpad { i8*, i32 }
          catch i8* null
  %32 = extractvalue { i8*, i32 } %31, 0
  tail call void @__clang_call_terminate(i8* %32) #15
  unreachable

; <label>:33:                                     ; preds = %25
  store i32 0, i32* %9, align 8, !tbaa !11
  br label %34

; <label>:34:                                     ; preds = %1, %33
  ret void
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #1

; Function Attrs: uwtable
define internal fastcc dereferenceable(16448) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZNK17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEv() unnamed_addr #4 align 2 personality i32 (...)* @__gxx_personality_v0 {
  %1 = alloca %"class.std::__cxx11::basic_string", align 8
  %2 = alloca %"class.std::__cxx11::basic_string", align 8
  %3 = alloca %"class.std::__cxx11::basic_string", align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  %5 = alloca %"class.std::__cxx11::basic_string", align 8
  %6 = alloca %"class.(anonymous namespace)::BranchCoverageRuntime::Output", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = alloca %"class.std::__cxx11::basic_string", align 8
  %9 = alloca %"class.std::__cxx11::basic_string", align 8
  %10 = alloca %"class.std::__cxx11::basic_string", align 8
  %11 = alloca %"class.std::__cxx11::basic_string", align 8
  %12 = alloca %"class.std::experimental::filesystem::v1::__cxx11::path", align 8
  %13 = alloca %"class.std::__cxx11::basic_string", align 8
  %14 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds ({ { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }, { { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE, i64 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !9
  %15 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %14, null
  br i1 %15, label %16, label %668

; <label>:16:                                     ; preds = %0
  %17 = tail call i8* @_Znwm(i64 16448) #16, !noalias !19
  %18 = bitcast %"class.std::__cxx11::basic_string"* %13 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %18) #2, !noalias !19
  %19 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %13, i64 0, i32 2
  %20 = bitcast %"class.std::__cxx11::basic_string"* %13 to %union.anon**
  store %union.anon* %19, %union.anon** %20, align 8, !tbaa !22, !noalias !19
  %21 = bitcast %union.anon* %19 to i8*
  %22 = invoke i8* @_Znwm(i64 20)
          to label %23 unwind label %644, !noalias !19

; <label>:23:                                     ; preds = %16
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %13, i64 0, i32 0, i32 0
  store i8* %22, i8** %24, align 8, !tbaa !2, !noalias !19
  %25 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %13, i64 0, i32 2, i32 0
  store i64 19, i64* %25, align 8, !tbaa !10, !noalias !19
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %22, i8* nonnull getelementptr inbounds ([20 x i8], [20 x i8]* @.str.8, i64 0, i64 0), i64 19, i32 1, i1 false) #2, !noalias !19
  %26 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %13, i64 0, i32 1
  store i64 19, i64* %26, align 8, !tbaa !23, !noalias !19
  %27 = getelementptr inbounds i8, i8* %22, i64 19
  store i8 0, i8* %27, align 1, !tbaa !10, !noalias !19
  %28 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %12 to i8*
  call void @llvm.lifetime.start.p0i8(i64 64, i8* nonnull %28) #2, !noalias !19
  %29 = call i8* @getenv(i8* nonnull %22) #2, !noalias !24
  %30 = icmp eq i8* %29, null
  br i1 %30, label %63, label %31

; <label>:31:                                     ; preds = %23
  %32 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2
  %33 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %12 to %union.anon**
  store %union.anon* %32, %union.anon** %33, align 8, !tbaa !22, !alias.scope !27, !noalias !19
  %34 = bitcast %union.anon* %32 to i8*
  %35 = call i64 @strlen(i8* nonnull %29) #2, !noalias !30
  %36 = icmp ugt i64 %35, 15
  br i1 %36, label %37, label %47

; <label>:37:                                     ; preds = %31
  %38 = icmp slt i64 %35, 0
  br i1 %38, label %39, label %41

; <label>:39:                                     ; preds = %37
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %40 unwind label %648, !noalias !19

; <label>:40:                                     ; preds = %39
  unreachable

; <label>:41:                                     ; preds = %37
  %42 = add i64 %35, 1
  %43 = invoke i8* @_Znwm(i64 %42)
          to label %44 unwind label %648, !noalias !19

; <label>:44:                                     ; preds = %41
  %45 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 0, i32 0
  store i8* %43, i8** %45, align 8, !tbaa !2, !alias.scope !27, !noalias !19
  %46 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2, i32 0
  store i64 %35, i64* %46, align 8, !tbaa !10, !alias.scope !27, !noalias !19
  br label %47

; <label>:47:                                     ; preds = %44, %31
  %48 = phi i8* [ %43, %44 ], [ %34, %31 ]
  switch i64 %35, label %51 [
    i64 1, label %49
    i64 0, label %52
  ]

; <label>:49:                                     ; preds = %47
  %50 = load i8, i8* %29, align 1, !tbaa !10, !noalias !30
  store i8 %50, i8* %48, align 1, !tbaa !10, !noalias !19
  br label %52

; <label>:51:                                     ; preds = %47
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %48, i8* nonnull %29, i64 %35, i32 1, i1 false) #2, !noalias !19
  br label %52

; <label>:52:                                     ; preds = %51, %49, %47
  %53 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 1
  store i64 %35, i64* %53, align 8, !tbaa !23, !alias.scope !27, !noalias !19
  %54 = getelementptr inbounds i8, i8* %48, i64 %35
  store i8 0, i8* %54, align 1, !tbaa !10, !noalias !19
  %55 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1
  %56 = bitcast %"class.std::vector"* %55 to i8*
  call void @llvm.memset.p0i8.i64(i8* nonnull %56, i8 0, i64 25, i32 8, i1 false), !alias.scope !31, !noalias !19
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %12)
          to label %379 unwind label %57, !noalias !19

; <label>:57:                                     ; preds = %52
  %58 = landingpad { i8*, i32 }
          cleanup
  call void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"class.std::vector"* nonnull %55) #2, !noalias !19
  %59 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 0, i32 0
  %60 = load i8*, i8** %59, align 8, !tbaa !2, !alias.scope !31, !noalias !19
  %61 = icmp eq i8* %60, %34
  br i1 %61, label %650, label %62

; <label>:62:                                     ; preds = %57
  call void @_ZdlPv(i8* %60) #2, !noalias !19
  br label %650

; <label>:63:                                     ; preds = %23
  %64 = bitcast %"class.std::__cxx11::basic_string"* %11 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %64) #2, !noalias !24
  %65 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %65) #2, !noalias !32
  %66 = bitcast %"class.std::__cxx11::basic_string"* %8 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %66) #2, !noalias !32
  %67 = bitcast %"class.std::__cxx11::basic_string"* %9 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %67) #2, !noalias !32
  invoke void @_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_(%"class.std::__cxx11::basic_string"* nonnull sret %9, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %13, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0))
          to label %68 unwind label %648, !noalias !19

; <label>:68:                                     ; preds = %63
  %69 = bitcast %"class.std::__cxx11::basic_string"* %10 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %69) #2, !noalias !32
  %70 = call i32 @getpid() #2, !noalias !35
  invoke void (%"class.std::__cxx11::basic_string"*, i32 (i8*, i64, i8*, %struct.__va_list_tag*)*, i64, i8*, ...) @_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z(%"class.std::__cxx11::basic_string"* nonnull sret %10, i32 (i8*, i64, i8*, %struct.__va_list_tag*)* nonnull @vsnprintf, i64 16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i64 0, i64 0), i32 %70)
          to label %71 unwind label %291, !noalias !35

; <label>:71:                                     ; preds = %68
  %72 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 1
  %73 = load i64, i64* %72, align 8, !tbaa !23, !noalias !36
  %74 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 1
  %75 = load i64, i64* %74, align 8, !tbaa !23, !noalias !36
  %76 = add i64 %75, %73
  %77 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 0, i32 0
  %78 = load i8*, i8** %77, align 8, !tbaa !2, !noalias !36
  %79 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 2
  %80 = bitcast %union.anon* %79 to i8*
  %81 = icmp eq i8* %78, %80
  %82 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 2, i32 0
  %83 = load i64, i64* %82, align 8, !noalias !36
  %84 = select i1 %81, i64 15, i64 %83
  %85 = icmp ugt i64 %76, %84
  %86 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 0, i32 0
  %87 = load i8*, i8** %86, align 8, !tbaa !2, !noalias !36
  br i1 %85, label %88, label %102

; <label>:88:                                     ; preds = %71
  %89 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2
  %90 = bitcast %union.anon* %89 to i8*
  %91 = icmp eq i8* %87, %90
  %92 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2, i32 0
  %93 = load i64, i64* %92, align 8, !noalias !36
  %94 = select i1 %91, i64 15, i64 %93
  %95 = icmp ugt i64 %76, %94
  br i1 %95, label %110, label %96

; <label>:96:                                     ; preds = %88
  %97 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %10, i64 0, i64 0, i8* %78, i64 %73)
          to label %98 unwind label %298, !noalias !19

; <label>:98:                                     ; preds = %96
  %99 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %97, i64 0, i32 0, i32 0
  %100 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %97, i64 0, i32 2
  %101 = bitcast %union.anon* %100 to i8*
  br label %148

; <label>:102:                                    ; preds = %71
  %103 = icmp eq i64 %75, 0
  br i1 %103, label %145, label %104

; <label>:104:                                    ; preds = %102
  %105 = getelementptr inbounds i8, i8* %78, i64 %73
  %106 = icmp eq i64 %75, 1
  br i1 %106, label %107, label %109

; <label>:107:                                    ; preds = %104
  %108 = load i8, i8* %87, align 1, !tbaa !10, !noalias !19
  store i8 %108, i8* %105, align 1, !tbaa !10, !noalias !19
  br label %145

; <label>:109:                                    ; preds = %104
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %105, i8* %87, i64 %75, i32 1, i1 false) #2, !noalias !19
  br label %145

; <label>:110:                                    ; preds = %88
  %111 = icmp slt i64 %76, 0
  br i1 %111, label %112, label %114

; <label>:112:                                    ; preds = %110
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %113 unwind label %298, !noalias !19

; <label>:113:                                    ; preds = %112
  unreachable

; <label>:114:                                    ; preds = %110
  %115 = shl i64 %84, 1
  %116 = icmp ult i64 %76, %115
  %117 = icmp ult i64 %115, 9223372036854775807
  %118 = select i1 %117, i64 %115, i64 9223372036854775807
  %119 = select i1 %116, i64 %118, i64 %76
  %120 = add i64 %119, 1
  %121 = invoke i8* @_Znwm(i64 %120)
          to label %122 unwind label %298, !noalias !19

; <label>:122:                                    ; preds = %114
  %123 = icmp eq i64 %73, 0
  br i1 %123, label %130, label %124

; <label>:124:                                    ; preds = %122
  %125 = load i8*, i8** %77, align 8, !tbaa !2, !noalias !32
  %126 = icmp eq i64 %73, 1
  br i1 %126, label %127, label %129

; <label>:127:                                    ; preds = %124
  %128 = load i8, i8* %125, align 1, !tbaa !10, !noalias !19
  store i8 %128, i8* %121, align 1, !tbaa !10, !noalias !32
  br label %130

; <label>:129:                                    ; preds = %124
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %121, i8* %125, i64 %73, i32 1, i1 false) #2, !noalias !19
  br label %130

; <label>:130:                                    ; preds = %129, %127, %122
  %131 = icmp ne i8* %87, null
  %132 = icmp ne i64 %75, 0
  %133 = and i1 %132, %131
  br i1 %133, label %134, label %140

; <label>:134:                                    ; preds = %130
  %135 = getelementptr inbounds i8, i8* %121, i64 %73
  %136 = icmp eq i64 %75, 1
  br i1 %136, label %137, label %139

; <label>:137:                                    ; preds = %134
  %138 = load i8, i8* %87, align 1, !tbaa !10, !noalias !19
  store i8 %138, i8* %135, align 1, !tbaa !10, !noalias !32
  br label %140

; <label>:139:                                    ; preds = %134
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %135, i8* nonnull %87, i64 %75, i32 1, i1 false) #2, !noalias !19
  br label %140

; <label>:140:                                    ; preds = %139, %137, %130
  %141 = load i8*, i8** %77, align 8, !tbaa !2, !noalias !32
  %142 = icmp eq i8* %141, %80
  br i1 %142, label %144, label %143

; <label>:143:                                    ; preds = %140
  call void @_ZdlPv(i8* %141) #2, !noalias !19
  br label %144

; <label>:144:                                    ; preds = %143, %140
  store i8* %121, i8** %77, align 8, !tbaa !2, !noalias !32
  store i64 %119, i64* %82, align 8, !tbaa !10, !noalias !32
  br label %145

; <label>:145:                                    ; preds = %144, %109, %107, %102
  store i64 %76, i64* %72, align 8, !tbaa !23, !noalias !36
  %146 = load i8*, i8** %77, align 8, !tbaa !2, !noalias !36
  %147 = getelementptr inbounds i8, i8* %146, i64 %76
  store i8 0, i8* %147, align 1, !tbaa !10, !noalias !19
  br label %148

; <label>:148:                                    ; preds = %145, %98
  %149 = phi i8* [ %80, %145 ], [ %101, %98 ]
  %150 = phi %union.anon* [ %79, %145 ], [ %100, %98 ]
  %151 = phi i8** [ %77, %145 ], [ %99, %98 ]
  %152 = phi %"class.std::__cxx11::basic_string"* [ %9, %145 ], [ %97, %98 ]
  %153 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2
  %154 = bitcast %"class.std::__cxx11::basic_string"* %8 to %union.anon**
  store %union.anon* %153, %union.anon** %154, align 8, !tbaa !22, !alias.scope !39, !noalias !32
  %155 = load i8*, i8** %151, align 8, !tbaa !2, !noalias !35
  %156 = icmp eq i8* %155, %149
  br i1 %156, label %157, label %159

; <label>:157:                                    ; preds = %148
  %158 = bitcast %union.anon* %153 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %158, i8* nonnull %149, i64 16, i32 1, i1 false) #2, !noalias !19
  br label %164

; <label>:159:                                    ; preds = %148
  %160 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  store i8* %155, i8** %160, align 8, !tbaa !2, !alias.scope !39, !noalias !32
  %161 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %152, i64 0, i32 2, i32 0
  %162 = load i64, i64* %161, align 8, !tbaa !10, !noalias !19
  %163 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2, i32 0
  store i64 %162, i64* %163, align 8, !tbaa !10, !alias.scope !39, !noalias !32
  br label %164

; <label>:164:                                    ; preds = %159, %157
  %165 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %152, i64 0, i32 1
  %166 = load i64, i64* %165, align 8, !tbaa !23, !noalias !35
  %167 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 1
  store i64 %166, i64* %167, align 8, !tbaa !23, !alias.scope !39, !noalias !32
  %168 = bitcast %"class.std::__cxx11::basic_string"* %152 to %union.anon**
  store %union.anon* %150, %union.anon** %168, align 8, !tbaa !2, !noalias !35
  store i64 0, i64* %165, align 8, !tbaa !23, !noalias !35
  store i8 0, i8* %149, align 1, !tbaa !10, !noalias !35
  %169 = load i64, i64* %167, align 8, !tbaa !23, !noalias !40
  %170 = icmp eq i64 %169, 9223372036854775807
  br i1 %170, label %171, label %173

; <label>:171:                                    ; preds = %164
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i64 0, i64 0)) #17
          to label %172 unwind label %302, !noalias !19

; <label>:172:                                    ; preds = %171
  unreachable

; <label>:173:                                    ; preds = %164
  %174 = add i64 %169, 1
  %175 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %176 = load i8*, i8** %175, align 8, !tbaa !2, !noalias !40
  %177 = bitcast %union.anon* %153 to i8*
  %178 = icmp eq i8* %176, %177
  %179 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2, i32 0
  %180 = load i64, i64* %179, align 8, !noalias !40
  %181 = select i1 %178, i64 15, i64 %180
  %182 = icmp ugt i64 %174, %181
  br i1 %182, label %186, label %183

; <label>:183:                                    ; preds = %173
  %184 = getelementptr inbounds i8, i8* %176, i64 %169
  store i8 46, i8* %184, align 1, !tbaa !10, !noalias !19
  %185 = load i8*, i8** %175, align 8, !tbaa !2, !noalias !40
  br label %208

; <label>:186:                                    ; preds = %173
  %187 = icmp slt i64 %174, 0
  br i1 %187, label %188, label %190

; <label>:188:                                    ; preds = %186
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %189 unwind label %302, !noalias !19

; <label>:189:                                    ; preds = %188
  unreachable

; <label>:190:                                    ; preds = %186
  %191 = shl i64 %181, 1
  %192 = icmp ult i64 %174, %191
  %193 = icmp ult i64 %191, 9223372036854775807
  %194 = select i1 %193, i64 %191, i64 9223372036854775807
  %195 = select i1 %192, i64 %194, i64 %174
  %196 = add i64 %195, 1
  %197 = invoke i8* @_Znwm(i64 %196)
          to label %198 unwind label %302, !noalias !19

; <label>:198:                                    ; preds = %190
  %199 = load i8*, i8** %175, align 8, !tbaa !2, !noalias !32
  switch i64 %169, label %202 [
    i64 0, label %203
    i64 1, label %200
  ]

; <label>:200:                                    ; preds = %198
  %201 = load i8, i8* %199, align 1, !tbaa !10, !noalias !19
  store i8 %201, i8* %197, align 1, !tbaa !10, !noalias !32
  br label %203

; <label>:202:                                    ; preds = %198
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %197, i8* %199, i64 %169, i32 1, i1 false) #2, !noalias !19
  br label %203

; <label>:203:                                    ; preds = %202, %200, %198
  %204 = getelementptr inbounds i8, i8* %197, i64 %169
  store i8 46, i8* %204, align 1, !tbaa !10, !noalias !32
  %205 = icmp eq i8* %199, %177
  br i1 %205, label %207, label %206

; <label>:206:                                    ; preds = %203
  call void @_ZdlPv(i8* %199) #2, !noalias !19
  br label %207

; <label>:207:                                    ; preds = %206, %203
  store i8* %197, i8** %175, align 8, !tbaa !2, !noalias !32
  store i64 %195, i64* %179, align 8, !tbaa !10, !noalias !32
  br label %208

; <label>:208:                                    ; preds = %207, %183
  %209 = phi i8* [ %197, %207 ], [ %185, %183 ]
  store i64 %174, i64* %167, align 8, !tbaa !23, !noalias !40
  %210 = getelementptr inbounds i8, i8* %209, i64 %174
  store i8 0, i8* %210, align 1, !tbaa !10, !noalias !43
  %211 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %212 = bitcast %"class.std::__cxx11::basic_string"* %7 to %union.anon**
  store %union.anon* %211, %union.anon** %212, align 8, !tbaa !22, !alias.scope !44, !noalias !32
  %213 = load i8*, i8** %175, align 8, !tbaa !2, !noalias !40
  %214 = icmp eq i8* %213, %177
  %215 = bitcast %union.anon* %211 to i8*
  br i1 %214, label %216, label %217

; <label>:216:                                    ; preds = %208
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %215, i8* nonnull %177, i64 16, i32 8, i1 false) #2, !noalias !32
  br label %221

; <label>:217:                                    ; preds = %208
  %218 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  store i8* %213, i8** %218, align 8, !tbaa !2, !alias.scope !44, !noalias !32
  %219 = load i64, i64* %179, align 8, !tbaa !10, !noalias !40
  %220 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  store i64 %219, i64* %220, align 8, !tbaa !10, !alias.scope !44, !noalias !32
  br label %221

; <label>:221:                                    ; preds = %217, %216
  %222 = phi i8* [ %213, %217 ], [ %215, %216 ]
  %223 = load i64, i64* %167, align 8, !tbaa !23, !noalias !40
  %224 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 1
  store i64 %223, i64* %224, align 8, !tbaa !23, !alias.scope !44, !noalias !32
  store %union.anon* %153, %union.anon** %154, align 8, !tbaa !2, !noalias !40
  store i64 0, i64* %167, align 8, !tbaa !23, !noalias !40
  store i8 0, i8* %177, align 8, !tbaa !10, !noalias !40
  %225 = sub i64 9223372036854775807, %223
  %226 = icmp ult i64 %225, 3
  br i1 %226, label %227, label %229

; <label>:227:                                    ; preds = %221
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i64 0, i64 0)) #17
          to label %228 unwind label %308, !noalias !19

; <label>:228:                                    ; preds = %227
  unreachable

; <label>:229:                                    ; preds = %221
  %230 = add i64 %223, 3
  %231 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %232 = icmp eq i8* %222, %215
  %233 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  %234 = load i64, i64* %233, align 8, !noalias !45
  %235 = select i1 %232, i64 15, i64 %234
  %236 = icmp ugt i64 %230, %235
  br i1 %236, label %240, label %237

; <label>:237:                                    ; preds = %229
  %238 = getelementptr inbounds i8, i8* %222, i64 %223
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %238, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i64 0, i64 0), i64 3, i32 1, i1 false) #2, !noalias !19
  %239 = load i8*, i8** %231, align 8, !tbaa !2, !noalias !45
  br label %262

; <label>:240:                                    ; preds = %229
  %241 = icmp slt i64 %230, 0
  br i1 %241, label %242, label %244

; <label>:242:                                    ; preds = %240
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %243 unwind label %308, !noalias !19

; <label>:243:                                    ; preds = %242
  unreachable

; <label>:244:                                    ; preds = %240
  %245 = shl i64 %235, 1
  %246 = icmp ult i64 %230, %245
  %247 = icmp ult i64 %245, 9223372036854775807
  %248 = select i1 %247, i64 %245, i64 9223372036854775807
  %249 = select i1 %246, i64 %248, i64 %230
  %250 = add i64 %249, 1
  %251 = invoke i8* @_Znwm(i64 %250)
          to label %252 unwind label %308, !noalias !19

; <label>:252:                                    ; preds = %244
  %253 = load i8*, i8** %231, align 8, !tbaa !2, !noalias !32
  switch i64 %223, label %256 [
    i64 0, label %257
    i64 1, label %254
  ]

; <label>:254:                                    ; preds = %252
  %255 = load i8, i8* %253, align 1, !tbaa !10, !noalias !19
  store i8 %255, i8* %251, align 1, !tbaa !10, !noalias !32
  br label %257

; <label>:256:                                    ; preds = %252
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %251, i8* %253, i64 %223, i32 1, i1 false) #2, !noalias !19
  br label %257

; <label>:257:                                    ; preds = %256, %254, %252
  %258 = getelementptr inbounds i8, i8* %251, i64 %223
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %258, i8* nonnull getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i64 0, i64 0), i64 3, i32 1, i1 false) #2, !noalias !19
  %259 = icmp eq i8* %253, %215
  br i1 %259, label %261, label %260

; <label>:260:                                    ; preds = %257
  call void @_ZdlPv(i8* %253) #2, !noalias !19
  br label %261

; <label>:261:                                    ; preds = %260, %257
  store i8* %251, i8** %231, align 8, !tbaa !2, !noalias !32
  store i64 %249, i64* %233, align 8, !tbaa !10, !noalias !32
  br label %262

; <label>:262:                                    ; preds = %261, %237
  %263 = phi i8* [ %251, %261 ], [ %239, %237 ]
  store i64 %230, i64* %224, align 8, !tbaa !23, !noalias !45
  %264 = getelementptr inbounds i8, i8* %263, i64 %230
  store i8 0, i8* %264, align 1, !tbaa !10, !noalias !48
  %265 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 2
  %266 = bitcast %"class.std::__cxx11::basic_string"* %11 to %union.anon**
  store %union.anon* %265, %union.anon** %266, align 8, !tbaa !22, !alias.scope !49, !noalias !24
  %267 = load i8*, i8** %231, align 8, !tbaa !2, !noalias !45
  %268 = icmp eq i8* %267, %215
  br i1 %268, label %269, label %271

; <label>:269:                                    ; preds = %262
  %270 = bitcast %union.anon* %265 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %270, i8* nonnull %215, i64 16, i32 8, i1 false) #2, !noalias !24
  br label %275

; <label>:271:                                    ; preds = %262
  %272 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  store i8* %267, i8** %272, align 8, !tbaa !2, !alias.scope !49, !noalias !24
  %273 = load i64, i64* %233, align 8, !tbaa !10, !noalias !45
  %274 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 2, i32 0
  store i64 %273, i64* %274, align 8, !tbaa !10, !alias.scope !49, !noalias !24
  br label %275

; <label>:275:                                    ; preds = %271, %269
  %276 = load i64, i64* %224, align 8, !tbaa !23, !noalias !45
  %277 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 1
  store i64 %276, i64* %277, align 8, !tbaa !23, !alias.scope !49, !noalias !24
  store %union.anon* %211, %union.anon** %212, align 8, !tbaa !2, !noalias !45
  store i64 0, i64* %224, align 8, !tbaa !23, !noalias !45
  store i8 0, i8* %215, align 8, !tbaa !10, !noalias !45
  %278 = load i8*, i8** %175, align 8, !tbaa !2, !noalias !32
  %279 = icmp eq i8* %278, %177
  br i1 %279, label %281, label %280

; <label>:280:                                    ; preds = %275
  call void @_ZdlPv(i8* %278) #2, !noalias !19
  br label %281

; <label>:281:                                    ; preds = %280, %275
  %282 = load i8*, i8** %86, align 8, !tbaa !2, !noalias !32
  %283 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2
  %284 = bitcast %union.anon* %283 to i8*
  %285 = icmp eq i8* %282, %284
  br i1 %285, label %287, label %286

; <label>:286:                                    ; preds = %281
  call void @_ZdlPv(i8* %282) #2, !noalias !19
  br label %287

; <label>:287:                                    ; preds = %286, %281
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %69) #2, !noalias !32
  %288 = load i8*, i8** %77, align 8, !tbaa !2, !noalias !32
  %289 = icmp eq i8* %288, %80
  br i1 %289, label %343, label %290

; <label>:290:                                    ; preds = %287
  call void @_ZdlPv(i8* %288) #2, !noalias !19
  br label %343

; <label>:291:                                    ; preds = %68
  %292 = landingpad { i8*, i32 }
          cleanup
  %293 = extractvalue { i8*, i32 } %292, 0
  %294 = extractvalue { i8*, i32 } %292, 1
  %295 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 0, i32 0
  %296 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 2
  %297 = bitcast %union.anon* %296 to i8*
  br label %332

; <label>:298:                                    ; preds = %114, %112, %96
  %299 = landingpad { i8*, i32 }
          cleanup
  %300 = extractvalue { i8*, i32 } %299, 0
  %301 = extractvalue { i8*, i32 } %299, 1
  br label %324

; <label>:302:                                    ; preds = %190, %188, %171
  %303 = landingpad { i8*, i32 }
          cleanup
  %304 = extractvalue { i8*, i32 } %303, 0
  %305 = extractvalue { i8*, i32 } %303, 1
  %306 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %307 = bitcast %union.anon* %153 to i8*
  br label %316

; <label>:308:                                    ; preds = %244, %242, %227
  %309 = landingpad { i8*, i32 }
          cleanup
  %310 = extractvalue { i8*, i32 } %309, 0
  %311 = extractvalue { i8*, i32 } %309, 1
  %312 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %313 = load i8*, i8** %312, align 8, !tbaa !2, !noalias !32
  %314 = icmp eq i8* %313, %215
  br i1 %314, label %316, label %315

; <label>:315:                                    ; preds = %308
  call void @_ZdlPv(i8* %313) #2, !noalias !19
  br label %316

; <label>:316:                                    ; preds = %315, %308, %302
  %317 = phi i8* [ %177, %315 ], [ %177, %308 ], [ %307, %302 ]
  %318 = phi i8** [ %175, %315 ], [ %175, %308 ], [ %306, %302 ]
  %319 = phi i8* [ %310, %315 ], [ %310, %308 ], [ %304, %302 ]
  %320 = phi i32 [ %311, %315 ], [ %311, %308 ], [ %305, %302 ]
  %321 = load i8*, i8** %318, align 8, !tbaa !2, !noalias !32
  %322 = icmp eq i8* %321, %317
  br i1 %322, label %324, label %323

; <label>:323:                                    ; preds = %316
  call void @_ZdlPv(i8* %321) #2, !noalias !19
  br label %324

; <label>:324:                                    ; preds = %323, %316, %298
  %325 = phi i8* [ %300, %298 ], [ %319, %316 ], [ %319, %323 ]
  %326 = phi i32 [ %301, %298 ], [ %320, %316 ], [ %320, %323 ]
  %327 = load i8*, i8** %86, align 8, !tbaa !2, !noalias !32
  %328 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2
  %329 = bitcast %union.anon* %328 to i8*
  %330 = icmp eq i8* %327, %329
  br i1 %330, label %332, label %331

; <label>:331:                                    ; preds = %324
  call void @_ZdlPv(i8* %327) #2, !noalias !19
  br label %332

; <label>:332:                                    ; preds = %331, %324, %291
  %333 = phi i8* [ %80, %331 ], [ %80, %324 ], [ %297, %291 ]
  %334 = phi i8** [ %77, %331 ], [ %77, %324 ], [ %295, %291 ]
  %335 = phi i8* [ %325, %331 ], [ %325, %324 ], [ %293, %291 ]
  %336 = phi i32 [ %326, %331 ], [ %326, %324 ], [ %294, %291 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %69) #2, !noalias !32
  %337 = load i8*, i8** %334, align 8, !tbaa !2, !noalias !32
  %338 = icmp eq i8* %337, %333
  br i1 %338, label %340, label %339

; <label>:339:                                    ; preds = %332
  call void @_ZdlPv(i8* %337) #2, !noalias !19
  br label %340

; <label>:340:                                    ; preds = %339, %332
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %67) #2, !noalias !32
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %66) #2, !noalias !32
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %65) #2, !noalias !32
  %341 = insertvalue { i8*, i32 } undef, i8* %335, 0
  %342 = insertvalue { i8*, i32 } %341, i32 %336, 1
  br label %650

; <label>:343:                                    ; preds = %290, %287
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %67) #2, !noalias !32
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %66) #2, !noalias !32
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %65) #2, !noalias !32
  %344 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2
  %345 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %12 to %union.anon**
  store %union.anon* %344, %union.anon** %345, align 8, !tbaa !22, !alias.scope !31, !noalias !19
  %346 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  %347 = load i8*, i8** %346, align 8, !tbaa !2, !noalias !24
  %348 = bitcast %union.anon* %265 to i8*
  %349 = icmp eq i8* %347, %348
  br i1 %349, label %350, label %352

; <label>:350:                                    ; preds = %343
  %351 = bitcast %union.anon* %344 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %351, i8* nonnull %348, i64 16, i32 8, i1 false) #2, !noalias !19
  br label %357

; <label>:352:                                    ; preds = %343
  %353 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 0, i32 0
  store i8* %347, i8** %353, align 8, !tbaa !2, !alias.scope !31, !noalias !19
  %354 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 2, i32 0
  %355 = load i64, i64* %354, align 8, !tbaa !10, !noalias !24
  %356 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2, i32 0
  store i64 %355, i64* %356, align 8, !tbaa !10, !alias.scope !31, !noalias !19
  br label %357

; <label>:357:                                    ; preds = %352, %350
  %358 = load i64, i64* %277, align 8, !tbaa !23, !noalias !24
  %359 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 1
  store i64 %358, i64* %359, align 8, !tbaa !23, !alias.scope !31, !noalias !19
  store %union.anon* %265, %union.anon** %266, align 8, !tbaa !2, !noalias !24
  store i64 0, i64* %277, align 8, !tbaa !23, !noalias !24
  store i8 0, i8* %348, align 8, !tbaa !10, !noalias !24
  %360 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1
  %361 = bitcast %"class.std::vector"* %360 to i8*
  call void @llvm.memset.p0i8.i64(i8* nonnull %361, i8 0, i64 25, i32 8, i1 false), !alias.scope !31, !noalias !19
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %12)
          to label %369 unwind label %362, !noalias !19

; <label>:362:                                    ; preds = %357
  %363 = landingpad { i8*, i32 }
          cleanup
  call void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"class.std::vector"* nonnull %360) #2, !noalias !19
  %364 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 0, i32 0
  %365 = load i8*, i8** %364, align 8, !tbaa !2, !alias.scope !31, !noalias !19
  %366 = bitcast %union.anon* %344 to i8*
  %367 = icmp eq i8* %365, %366
  br i1 %367, label %374, label %368

; <label>:368:                                    ; preds = %362
  call void @_ZdlPv(i8* %365) #2, !noalias !19
  br label %374

; <label>:369:                                    ; preds = %357
  %370 = load i8*, i8** %346, align 8, !tbaa !2, !noalias !24
  %371 = icmp eq i8* %370, %348
  br i1 %371, label %373, label %372

; <label>:372:                                    ; preds = %369
  call void @_ZdlPv(i8* %370) #2, !noalias !19
  br label %373

; <label>:373:                                    ; preds = %372, %369
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %64) #2, !noalias !24
  br label %379

; <label>:374:                                    ; preds = %368, %362
  %375 = load i8*, i8** %346, align 8, !tbaa !2, !noalias !24
  %376 = icmp eq i8* %375, %348
  br i1 %376, label %378, label %377

; <label>:377:                                    ; preds = %374
  call void @_ZdlPv(i8* %375) #2, !noalias !19
  br label %378

; <label>:378:                                    ; preds = %377, %374
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %64) #2, !noalias !24
  br label %650

; <label>:379:                                    ; preds = %373, %52
  %380 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 24, i8* nonnull %380) #2, !noalias !19
  %381 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6, i64 0, i32 0
  store %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, %"class.std::experimental::filesystem::v1::__cxx11::path"** %381, align 8, !tbaa !9, !noalias !19
  %382 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6, i64 0, i32 1
  %383 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 0, i32 0
  %384 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !19
  %385 = call i32 @mkdir(i8* %384, i32 493) #2, !noalias !19
  %386 = icmp eq i32 %385, -1
  br i1 %386, label %387, label %442

; <label>:387:                                    ; preds = %379
  %388 = tail call i32* @__errno_location() #18
  %389 = load i32, i32* %388, align 4, !tbaa !50, !noalias !19
  %390 = icmp eq i32 %389, 17
  br i1 %390, label %442, label %391

; <label>:391:                                    ; preds = %387
  %392 = bitcast %"class.std::__cxx11::basic_string"* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %392) #2, !noalias !19
  %393 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 2
  %394 = bitcast %"class.std::__cxx11::basic_string"* %1 to %union.anon**
  store %union.anon* %393, %union.anon** %394, align 8, !tbaa !22, !alias.scope !51, !noalias !19
  %395 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !54
  %396 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 1
  %397 = load i64, i64* %396, align 8, !tbaa !23, !noalias !54
  %398 = icmp ne i8* %395, null
  %399 = icmp eq i64 %397, 0
  %400 = or i1 %398, %399
  br i1 %400, label %403, label %401

; <label>:401:                                    ; preds = %391
  invoke void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
          to label %402 unwind label %614, !noalias !19

; <label>:402:                                    ; preds = %401
  unreachable

; <label>:403:                                    ; preds = %391
  %404 = bitcast %union.anon* %393 to i8*
  %405 = icmp ugt i64 %397, 15
  br i1 %405, label %406, label %416

; <label>:406:                                    ; preds = %403
  %407 = icmp slt i64 %397, 0
  br i1 %407, label %408, label %410

; <label>:408:                                    ; preds = %406
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %409 unwind label %614, !noalias !19

; <label>:409:                                    ; preds = %408
  unreachable

; <label>:410:                                    ; preds = %406
  %411 = add i64 %397, 1
  %412 = invoke i8* @_Znwm(i64 %411)
          to label %413 unwind label %614, !noalias !19

; <label>:413:                                    ; preds = %410
  %414 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  store i8* %412, i8** %414, align 8, !tbaa !2, !alias.scope !51, !noalias !19
  %415 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 2, i32 0
  store i64 %397, i64* %415, align 8, !tbaa !10, !alias.scope !51, !noalias !19
  br label %416

; <label>:416:                                    ; preds = %413, %403
  %417 = phi i8* [ %412, %413 ], [ %404, %403 ]
  switch i64 %397, label %420 [
    i64 1, label %418
    i64 0, label %421
  ]

; <label>:418:                                    ; preds = %416
  %419 = load i8, i8* %395, align 1, !tbaa !10, !noalias !19
  store i8 %419, i8* %417, align 1, !tbaa !10, !noalias !19
  br label %421

; <label>:420:                                    ; preds = %416
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %417, i8* %395, i64 %397, i32 1, i1 false) #2, !noalias !19
  br label %421

; <label>:421:                                    ; preds = %420, %418, %416
  %422 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  store i64 %397, i64* %422, align 8, !tbaa !23, !alias.scope !51, !noalias !19
  %423 = getelementptr inbounds i8, i8* %417, i64 %397
  store i8 0, i8* %423, align 1, !tbaa !10, !noalias !19
  %424 = call i8* @__cxa_allocate_exception(i64 192) #2, !noalias !19
  %425 = bitcast i8* %424 to %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*
  %426 = tail call dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() #18
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %425, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %1, i32 0, %"class.std::_V2::error_category"* nonnull %426)
          to label %427 unwind label %429, !noalias !19

; <label>:427:                                    ; preds = %421
  invoke void @__cxa_throw(i8* %424, i8* bitcast (i8** @_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE to i8*), i8* bitcast (void (%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*)* @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev to i8*)) #17
          to label %428 unwind label %431, !noalias !19

; <label>:428:                                    ; preds = %427
  unreachable

; <label>:429:                                    ; preds = %421
  %430 = landingpad { i8*, i32 }
          cleanup
  call void @__cxa_free_exception(i8* %424) #2, !noalias !19
  br label %433

; <label>:431:                                    ; preds = %427
  %432 = landingpad { i8*, i32 }
          cleanup
  br label %433

; <label>:433:                                    ; preds = %431, %429
  %434 = phi { i8*, i32 } [ %432, %431 ], [ %430, %429 ]
  %435 = extractvalue { i8*, i32 } %434, 0
  %436 = extractvalue { i8*, i32 } %434, 1
  %437 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %438 = load i8*, i8** %437, align 8, !tbaa !2, !noalias !19
  %439 = icmp eq i8* %438, %404
  br i1 %439, label %441, label %440

; <label>:440:                                    ; preds = %433
  call void @_ZdlPv(i8* %438) #2, !noalias !19
  br label %441

; <label>:441:                                    ; preds = %440, %433
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %392) #2, !noalias !19
  br label %498

; <label>:442:                                    ; preds = %387, %379
  %443 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !19
  %444 = invoke i32 (i8*, i32, ...) @open(i8* %443, i32 2162688)
          to label %445 unwind label %614, !noalias !19

; <label>:445:                                    ; preds = %442
  %446 = icmp eq i32 %444, -1
  br i1 %446, label %447, label %503

; <label>:447:                                    ; preds = %445
  call void @perror(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.21, i64 0, i64 0)) #19, !noalias !19
  %448 = bitcast %"class.std::__cxx11::basic_string"* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %448) #2, !noalias !19
  %449 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 2
  %450 = bitcast %"class.std::__cxx11::basic_string"* %2 to %union.anon**
  store %union.anon* %449, %union.anon** %450, align 8, !tbaa !22, !alias.scope !55, !noalias !19
  %451 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !58
  %452 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 1
  %453 = load i64, i64* %452, align 8, !tbaa !23, !noalias !58
  %454 = icmp ne i8* %451, null
  %455 = icmp eq i64 %453, 0
  %456 = or i1 %454, %455
  br i1 %456, label %459, label %457

; <label>:457:                                    ; preds = %447
  invoke void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
          to label %458 unwind label %614, !noalias !19

; <label>:458:                                    ; preds = %457
  unreachable

; <label>:459:                                    ; preds = %447
  %460 = bitcast %union.anon* %449 to i8*
  %461 = icmp ugt i64 %453, 15
  br i1 %461, label %462, label %472

; <label>:462:                                    ; preds = %459
  %463 = icmp slt i64 %453, 0
  br i1 %463, label %464, label %466

; <label>:464:                                    ; preds = %462
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %465 unwind label %614, !noalias !19

; <label>:465:                                    ; preds = %464
  unreachable

; <label>:466:                                    ; preds = %462
  %467 = add i64 %453, 1
  %468 = invoke i8* @_Znwm(i64 %467)
          to label %469 unwind label %614, !noalias !19

; <label>:469:                                    ; preds = %466
  %470 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 0, i32 0
  store i8* %468, i8** %470, align 8, !tbaa !2, !alias.scope !55, !noalias !19
  %471 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 2, i32 0
  store i64 %453, i64* %471, align 8, !tbaa !10, !alias.scope !55, !noalias !19
  br label %472

; <label>:472:                                    ; preds = %469, %459
  %473 = phi i8* [ %468, %469 ], [ %460, %459 ]
  switch i64 %453, label %476 [
    i64 1, label %474
    i64 0, label %477
  ]

; <label>:474:                                    ; preds = %472
  %475 = load i8, i8* %451, align 1, !tbaa !10, !noalias !19
  store i8 %475, i8* %473, align 1, !tbaa !10, !noalias !19
  br label %477

; <label>:476:                                    ; preds = %472
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %473, i8* %451, i64 %453, i32 1, i1 false) #2, !noalias !19
  br label %477

; <label>:477:                                    ; preds = %476, %474, %472
  %478 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 1
  store i64 %453, i64* %478, align 8, !tbaa !23, !alias.scope !55, !noalias !19
  %479 = getelementptr inbounds i8, i8* %473, i64 %453
  store i8 0, i8* %479, align 1, !tbaa !10, !noalias !19
  %480 = call i8* @__cxa_allocate_exception(i64 192) #2, !noalias !19
  %481 = bitcast i8* %480 to %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*
  %482 = tail call dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() #18
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %481, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %2, i32 0, %"class.std::_V2::error_category"* nonnull %482)
          to label %483 unwind label %485, !noalias !19

; <label>:483:                                    ; preds = %477
  invoke void @__cxa_throw(i8* %480, i8* bitcast (i8** @_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE to i8*), i8* bitcast (void (%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*)* @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev to i8*)) #17
          to label %484 unwind label %487, !noalias !19

; <label>:484:                                    ; preds = %483
  unreachable

; <label>:485:                                    ; preds = %477
  %486 = landingpad { i8*, i32 }
          cleanup
  call void @__cxa_free_exception(i8* %480) #2, !noalias !19
  br label %489

; <label>:487:                                    ; preds = %483
  %488 = landingpad { i8*, i32 }
          cleanup
  br label %489

; <label>:489:                                    ; preds = %487, %485
  %490 = phi { i8*, i32 } [ %488, %487 ], [ %486, %485 ]
  %491 = extractvalue { i8*, i32 } %490, 0
  %492 = extractvalue { i8*, i32 } %490, 1
  %493 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 0, i32 0
  %494 = load i8*, i8** %493, align 8, !tbaa !2, !noalias !19
  %495 = icmp eq i8* %494, %460
  br i1 %495, label %497, label %496

; <label>:496:                                    ; preds = %489
  call void @_ZdlPv(i8* %494) #2, !noalias !19
  br label %497

; <label>:497:                                    ; preds = %496, %489
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %448) #2, !noalias !19
  br label %498

; <label>:498:                                    ; preds = %497, %441
  %499 = phi i32 [ %492, %497 ], [ %436, %441 ]
  %500 = phi i8* [ %491, %497 ], [ %435, %441 ]
  %501 = insertvalue { i8*, i32 } undef, i8* %500, 0
  %502 = insertvalue { i8*, i32 } %501, i32 %499, 1
  br label %616

; <label>:503:                                    ; preds = %445
  store i32 %444, i32* %382, align 8, !tbaa !59, !noalias !19
  %504 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6, i64 0, i32 2
  %505 = bitcast %"class.std::__cxx11::basic_string"* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %505) #2, !noalias !19
  %506 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 2
  %507 = bitcast %"class.std::__cxx11::basic_string"* %3 to %union.anon**
  store %union.anon* %506, %union.anon** %507, align 8, !tbaa !22, !noalias !19
  %508 = bitcast %union.anon* %506 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %508, i8* nonnull getelementptr inbounds ([7 x i8], [7 x i8]* @.str.18, i64 0, i64 0), i64 6, i32 1, i1 false) #2, !noalias !19
  %509 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 1
  store i64 6, i64* %509, align 8, !tbaa !23, !noalias !19
  %510 = getelementptr inbounds i8, i8* %508, i64 6
  store i8 0, i8* %510, align 2, !tbaa !10, !noalias !19
  %511 = invoke fastcc i32 @_ZN12_GLOBAL__N_121BranchCoverageRuntime6Output11createAtDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.(anonymous namespace)::BranchCoverageRuntime::Output"* nonnull %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %3)
          to label %512 unwind label %545, !noalias !19

; <label>:512:                                    ; preds = %503
  %513 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 0, i32 0
  %514 = load i8*, i8** %513, align 8, !tbaa !2, !noalias !19
  %515 = icmp eq i8* %514, %508
  br i1 %515, label %517, label %516

; <label>:516:                                    ; preds = %512
  call void @_ZdlPv(i8* %514) #2, !noalias !19
  br label %517

; <label>:517:                                    ; preds = %516, %512
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %505) #2, !noalias !19
  store i32 %511, i32* %504, align 4, !tbaa !62, !noalias !19
  %518 = bitcast %"class.std::__cxx11::basic_string"* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %518) #2, !noalias !19
  %519 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2
  %520 = bitcast %"class.std::__cxx11::basic_string"* %4 to %union.anon**
  store %union.anon* %519, %union.anon** %520, align 8, !tbaa !22, !noalias !19
  %521 = bitcast %union.anon* %519 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %521, i8* nonnull getelementptr inbounds ([7 x i8], [7 x i8]* @.str.19, i64 0, i64 0), i64 6, i32 1, i1 false) #2, !noalias !19
  %522 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 1
  store i64 6, i64* %522, align 8, !tbaa !23, !noalias !19
  %523 = getelementptr inbounds i8, i8* %521, i64 6
  store i8 0, i8* %523, align 2, !tbaa !10, !noalias !19
  %524 = invoke fastcc i32 @_ZN12_GLOBAL__N_121BranchCoverageRuntime6Output11createAtDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.(anonymous namespace)::BranchCoverageRuntime::Output"* nonnull %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %4)
          to label %525 unwind label %554, !noalias !19

; <label>:525:                                    ; preds = %517
  %526 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6, i64 0, i32 3, i32 0
  store i32 %524, i32* %526, align 8, !tbaa !63, !noalias !19
  %527 = bitcast %"class.std::__cxx11::basic_string"* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %527) #2, !noalias !19
  %528 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2
  %529 = bitcast %"class.std::__cxx11::basic_string"* %5 to %union.anon**
  store %union.anon* %528, %union.anon** %529, align 8, !tbaa !22, !noalias !19
  %530 = bitcast %union.anon* %528 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %530, i8* nonnull getelementptr inbounds ([10 x i8], [10 x i8]* @.str.20, i64 0, i64 0), i64 9, i32 1, i1 false) #2, !noalias !19
  %531 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 1
  store i64 9, i64* %531, align 8, !tbaa !23, !noalias !19
  %532 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2, i32 1, i64 1
  store i8 0, i8* %532, align 1, !tbaa !10, !noalias !19
  %533 = invoke fastcc i32 @_ZN12_GLOBAL__N_121BranchCoverageRuntime6Output11createAtDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.(anonymous namespace)::BranchCoverageRuntime::Output"* nonnull %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %5)
          to label %534 unwind label %558, !noalias !19

; <label>:534:                                    ; preds = %525
  %535 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %6, i64 0, i32 3, i32 1
  store i32 %533, i32* %535, align 4, !tbaa !64, !noalias !19
  %536 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %537 = load i8*, i8** %536, align 8, !tbaa !2, !noalias !19
  %538 = icmp eq i8* %537, %530
  br i1 %538, label %540, label %539

; <label>:539:                                    ; preds = %534
  call void @_ZdlPv(i8* %537) #2, !noalias !19
  br label %540

; <label>:540:                                    ; preds = %539, %534
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %527) #2, !noalias !19
  %541 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  %542 = load i8*, i8** %541, align 8, !tbaa !2, !noalias !19
  %543 = icmp eq i8* %542, %521
  br i1 %543, label %580, label %544

; <label>:544:                                    ; preds = %540
  call void @_ZdlPv(i8* %542) #2, !noalias !19
  br label %580

; <label>:545:                                    ; preds = %503
  %546 = landingpad { i8*, i32 }
          cleanup
  %547 = extractvalue { i8*, i32 } %546, 0
  %548 = extractvalue { i8*, i32 } %546, 1
  %549 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 0, i32 0
  %550 = load i8*, i8** %549, align 8, !tbaa !2, !noalias !19
  %551 = icmp eq i8* %550, %508
  br i1 %551, label %553, label %552

; <label>:552:                                    ; preds = %545
  call void @_ZdlPv(i8* %550) #2, !noalias !19
  br label %553

; <label>:553:                                    ; preds = %552, %545
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %505) #2, !noalias !19
  br label %575

; <label>:554:                                    ; preds = %517
  %555 = landingpad { i8*, i32 }
          cleanup
  %556 = extractvalue { i8*, i32 } %555, 0
  %557 = extractvalue { i8*, i32 } %555, 1
  br label %567

; <label>:558:                                    ; preds = %525
  %559 = landingpad { i8*, i32 }
          cleanup
  %560 = extractvalue { i8*, i32 } %559, 0
  %561 = extractvalue { i8*, i32 } %559, 1
  %562 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %563 = load i8*, i8** %562, align 8, !tbaa !2, !noalias !19
  %564 = icmp eq i8* %563, %530
  br i1 %564, label %566, label %565

; <label>:565:                                    ; preds = %558
  call void @_ZdlPv(i8* %563) #2, !noalias !19
  br label %566

; <label>:566:                                    ; preds = %565, %558
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %527) #2, !noalias !19
  br label %567

; <label>:567:                                    ; preds = %566, %554
  %568 = phi i8* [ %560, %566 ], [ %556, %554 ]
  %569 = phi i32 [ %561, %566 ], [ %557, %554 ]
  %570 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  %571 = load i8*, i8** %570, align 8, !tbaa !2, !noalias !19
  %572 = icmp eq i8* %571, %521
  br i1 %572, label %574, label %573

; <label>:573:                                    ; preds = %567
  call void @_ZdlPv(i8* %571) #2, !noalias !19
  br label %574

; <label>:574:                                    ; preds = %573, %567
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %518) #2, !noalias !19
  br label %575

; <label>:575:                                    ; preds = %574, %553
  %576 = phi i8* [ %568, %574 ], [ %547, %553 ]
  %577 = phi i32 [ %569, %574 ], [ %548, %553 ]
  %578 = insertvalue { i8*, i32 } undef, i8* %576, 0
  %579 = insertvalue { i8*, i32 } %578, i32 %577, 1
  br label %616

; <label>:580:                                    ; preds = %544, %540
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %518) #2, !noalias !19
  call void @llvm.memset.p0i8.i64(i8* nonnull %17, i8 0, i64 4104, i32 8, i1 false) #2, !noalias !19
  %581 = getelementptr inbounds i8, i8* %17, i64 4104
  %582 = bitcast i8* %581 to i32*
  store i32 %524, i32* %582, align 4, !tbaa !18, !noalias !19
  %583 = getelementptr inbounds i8, i8* %17, i64 4112
  call void @llvm.memset.p0i8.i64(i8* nonnull %583, i8 0, i64 12296, i32 8, i1 false) #2, !noalias !19
  %584 = getelementptr inbounds i8, i8* %17, i64 16408
  %585 = bitcast i8* %584 to i32*
  store i32 %533, i32* %585, align 4, !tbaa !18, !noalias !19
  %586 = getelementptr inbounds i8, i8* %17, i64 16416
  call void @llvm.memset.p0i8.i64(i8* nonnull %586, i8 0, i64 24, i32 8, i1 false) #2, !noalias !19
  %587 = getelementptr inbounds i8, i8* %17, i64 16440
  %588 = bitcast i8* %587 to i32*
  store i32 %511, i32* %588, align 4, !tbaa !18, !noalias !19
  %589 = invoke i32 @close(i32 %444)
          to label %593 unwind label %590, !noalias !19

; <label>:590:                                    ; preds = %580
  %591 = landingpad { i8*, i32 }
          catch i8* null
  %592 = extractvalue { i8*, i32 } %591, 0
  call void @__clang_call_terminate(i8* %592) #15, !noalias !19
  unreachable

; <label>:593:                                    ; preds = %580
  call void @llvm.lifetime.end.p0i8(i64 24, i8* nonnull %380) #2, !noalias !19
  %594 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1
  %595 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %594, i64 0, i32 0, i32 0, i32 0
  %596 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %595, align 8, !tbaa !65, !noalias !19
  %597 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1, i32 0, i32 0, i32 1
  %598 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %597, align 8, !tbaa !68, !noalias !19
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %596, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %598)
          to label %599 unwind label %604, !noalias !19

; <label>:599:                                    ; preds = %593
  %600 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %595, align 8, !tbaa !65, !noalias !19
  %601 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %600, null
  br i1 %601, label %608, label %602

; <label>:602:                                    ; preds = %599
  %603 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %600 to i8*
  call void @_ZdlPv(i8* %603) #2, !noalias !19
  br label %608

; <label>:604:                                    ; preds = %593
  %605 = landingpad { i8*, i32 }
          catch i8* null
  %606 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %594, i64 0, i32 0
  %607 = extractvalue { i8*, i32 } %605, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %606) #2, !noalias !19
  call void @__clang_call_terminate(i8* %607) #15, !noalias !19
  unreachable

; <label>:608:                                    ; preds = %602, %599
  %609 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !19
  %610 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2
  %611 = bitcast %union.anon* %610 to i8*
  %612 = icmp eq i8* %609, %611
  br i1 %612, label %639, label %613

; <label>:613:                                    ; preds = %608
  call void @_ZdlPv(i8* %609) #2, !noalias !19
  br label %639

; <label>:614:                                    ; preds = %466, %464, %457, %442, %410, %408, %401
  %615 = landingpad { i8*, i32 }
          cleanup
  br label %616

; <label>:616:                                    ; preds = %614, %575, %498
  %617 = phi { i8*, i32 } [ %615, %614 ], [ %502, %498 ], [ %579, %575 ]
  %618 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1
  %619 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %618, i64 0, i32 0, i32 0, i32 0
  %620 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %619, align 8, !tbaa !65, !noalias !19
  %621 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 1, i32 0, i32 0, i32 1
  %622 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %621, align 8, !tbaa !68, !noalias !19
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %620, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %622)
          to label %623 unwind label %628, !noalias !19

; <label>:623:                                    ; preds = %616
  %624 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %619, align 8, !tbaa !65, !noalias !19
  %625 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %624, null
  br i1 %625, label %632, label %626

; <label>:626:                                    ; preds = %623
  %627 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %624 to i8*
  call void @_ZdlPv(i8* %627) #2, !noalias !19
  br label %632

; <label>:628:                                    ; preds = %616
  %629 = landingpad { i8*, i32 }
          catch i8* null
  %630 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %618, i64 0, i32 0
  %631 = extractvalue { i8*, i32 } %629, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %630) #2, !noalias !19
  call void @__clang_call_terminate(i8* %631) #15, !noalias !19
  unreachable

; <label>:632:                                    ; preds = %626, %623
  %633 = load i8*, i8** %383, align 8, !tbaa !2, !noalias !19
  %634 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %12, i64 0, i32 0, i32 2
  %635 = bitcast %union.anon* %634 to i8*
  %636 = icmp eq i8* %633, %635
  br i1 %636, label %638, label %637

; <label>:637:                                    ; preds = %632
  call void @_ZdlPv(i8* %633) #2, !noalias !19
  br label %638

; <label>:638:                                    ; preds = %637, %632
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %28) #2, !noalias !19
  br label %650

; <label>:639:                                    ; preds = %613, %608
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %28) #2, !noalias !19
  %640 = ptrtoint i8* %17 to i64
  %641 = load i8*, i8** %24, align 8, !tbaa !2, !noalias !19
  %642 = icmp eq i8* %641, %21
  br i1 %642, label %662, label %643

; <label>:643:                                    ; preds = %639
  call void @_ZdlPv(i8* %641) #2, !noalias !19
  br label %662

; <label>:644:                                    ; preds = %16
  %645 = landingpad { i8*, i32 }
          cleanup
  %646 = extractvalue { i8*, i32 } %645, 0
  %647 = extractvalue { i8*, i32 } %645, 1
  br label %657

; <label>:648:                                    ; preds = %63, %41, %39
  %649 = landingpad { i8*, i32 }
          cleanup
  br label %650

; <label>:650:                                    ; preds = %648, %638, %378, %340, %62, %57
  %651 = phi { i8*, i32 } [ %649, %648 ], [ %342, %340 ], [ %363, %378 ], [ %617, %638 ], [ %58, %62 ], [ %58, %57 ]
  %652 = extractvalue { i8*, i32 } %651, 0
  %653 = extractvalue { i8*, i32 } %651, 1
  %654 = load i8*, i8** %24, align 8, !tbaa !2, !noalias !19
  %655 = icmp eq i8* %654, %21
  br i1 %655, label %657, label %656

; <label>:656:                                    ; preds = %650
  call void @_ZdlPv(i8* %654) #2, !noalias !19
  br label %657

; <label>:657:                                    ; preds = %656, %650, %644
  %658 = phi i8* [ %646, %644 ], [ %652, %650 ], [ %652, %656 ]
  %659 = phi i32 [ %647, %644 ], [ %653, %650 ], [ %653, %656 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %18) #2, !noalias !19
  call void @_ZdlPv(i8* nonnull %17) #20, !noalias !19
  %660 = insertvalue { i8*, i32 } undef, i8* %658, 0
  %661 = insertvalue { i8*, i32 } %660, i32 %659, 1
  resume { i8*, i32 } %661

; <label>:662:                                    ; preds = %639, %643
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %18) #2, !noalias !19
  %663 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds ({ { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }, { { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE, i64 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !9
  store i64 %640, i64* bitcast ({ { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE to i64*), align 8, !tbaa !9
  %664 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %663, null
  %665 = bitcast i8* %17 to %"class.(anonymous namespace)::BranchCoverageRuntime"*
  br i1 %664, label %668, label %666

; <label>:666:                                    ; preds = %662
  call fastcc void @_ZNKSt14default_deleteIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEPS1_(%"class.(anonymous namespace)::BranchCoverageRuntime"* nonnull %663) #2
  %667 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds ({ { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }, { { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE, i64 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !9
  br label %668

; <label>:668:                                    ; preds = %0, %662, %666
  %669 = phi %"class.(anonymous namespace)::BranchCoverageRuntime"* [ %14, %0 ], [ %665, %662 ], [ %667, %666 ]
  ret %"class.(anonymous namespace)::BranchCoverageRuntime"* %669
}

; Function Attrs: uwtable
define void @__BranchCoverage_onMultiBranch(i32, i32) local_unnamed_addr #4 personality i32 (...)* @__gxx_personality_v0 {
  %3 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.6, i64 0, i64 0), i32 %0, i32 %1)
  %4 = tail call fastcc dereferenceable(16448) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZNK17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEv()
  %5 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 1
  %6 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 1, i32 0, i32 0, i32 1
  %7 = load i64, i64* %6, align 8, !tbaa !10
  %8 = add i64 %7, 1
  store i64 %8, i64* %6, align 8, !tbaa !10
  %9 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 0, i32 2
  %10 = load i32, i32* %9, align 4, !tbaa !17
  store i32 0, i32* %9, align 4, !tbaa !17
  %11 = or i32 %10, -2147483648
  %12 = zext i32 %11 to i64
  %13 = zext i32 %0 to i64
  %14 = shl nuw i64 %13, 32
  %15 = or i64 %14, %12
  %16 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 1, i32 1
  %17 = load i64, i64* %16, align 8, !tbaa !69
  %18 = add i64 %17, 1
  store i64 %18, i64* %16, align 8, !tbaa !69
  %19 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 1, i32 0, i32 0, i64 %17
  %20 = bitcast %"struct.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches::Record"* %19 to i64*
  store i64 %15, i64* %20, align 4
  %21 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 1, i32 0, i32 0, i64 %17, i32 2
  store i32 %1, i32* %21, align 4
  %22 = load i64, i64* %16, align 8, !tbaa !69
  %23 = icmp eq i64 %22, 1024
  br i1 %23, label %24, label %34

; <label>:24:                                     ; preds = %2
  %25 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 1
  %26 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches"* %25 to i8*
  %27 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 0, i32 1, i32 2, i32 0
  %28 = load i32, i32* %27, align 4, !tbaa !18
  %29 = invoke i64 @write(i32 %28, i8* nonnull %26, i64 12288)
          to label %33 unwind label %30

; <label>:30:                                     ; preds = %24
  %31 = landingpad { i8*, i32 }
          catch i8* null
  %32 = extractvalue { i8*, i32 } %31, 0
  tail call void @__clang_call_terminate(i8* %32) #15
  unreachable

; <label>:33:                                     ; preds = %24
  store i64 0, i64* %16, align 8, !tbaa !69
  br label %34

; <label>:34:                                     ; preds = %33, %2
  %35 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::Counts"* %5 to i8*
  %36 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %4, i64 0, i32 1, i32 1, i32 0
  %37 = load i32, i32* %36, align 4, !tbaa !18
  %38 = invoke i64 @pwrite(i32 %37, i8* nonnull %35, i64 24, i64 0)
          to label %42 unwind label %39

; <label>:39:                                     ; preds = %34
  %40 = landingpad { i8*, i32 }
          catch i8* null
  %41 = extractvalue { i8*, i32 } %40, 0
  tail call void @__clang_call_terminate(i8* %41) #15
  unreachable

; <label>:42:                                     ; preds = %34
  ret void
}

; Function Attrs: uwtable
define void @__BranchCoverage_onInfiniteBranch(i8*) local_unnamed_addr #4 personality i32 (...)* @__gxx_personality_v0 {
  %2 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.7, i64 0, i64 0), i8* %0)
  %3 = tail call fastcc dereferenceable(16448) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZNK17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEv()
  %4 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 1
  %5 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 1, i32 0, i32 0, i32 2
  %6 = load i64, i64* %5, align 8, !tbaa !10
  %7 = add i64 %6, 1
  store i64 %7, i64* %5, align 8, !tbaa !10
  %8 = ptrtoint i8* %0 to i64
  %9 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 0, i32 2
  %10 = load i32, i32* %9, align 4, !tbaa !17
  store i32 0, i32* %9, align 4, !tbaa !17
  %11 = shl i64 %8, 32
  %12 = and i32 %10, 2147483647
  %13 = zext i32 %12 to i64
  %14 = or i64 %11, %13
  %15 = lshr i64 %8, 32
  %16 = trunc i64 %15 to i32
  %17 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 1, i32 1
  %18 = load i64, i64* %17, align 8, !tbaa !69
  %19 = add i64 %18, 1
  store i64 %19, i64* %17, align 8, !tbaa !69
  %20 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 1, i32 0, i32 0, i64 %18
  %21 = bitcast %"struct.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches::Record"* %20 to i64*
  store i64 %14, i64* %21, align 4
  %22 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 1, i32 0, i32 0, i64 %18, i32 2
  store i32 %16, i32* %22, align 4
  %23 = load i64, i64* %17, align 8, !tbaa !69
  %24 = icmp eq i64 %23, 1024
  br i1 %24, label %25, label %35

; <label>:25:                                     ; preds = %1
  %26 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 1
  %27 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches"* %26 to i8*
  %28 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 1, i32 2, i32 0
  %29 = load i32, i32* %28, align 4, !tbaa !18
  %30 = invoke i64 @write(i32 %29, i8* nonnull %27, i64 12288)
          to label %34 unwind label %31

; <label>:31:                                     ; preds = %25
  %32 = landingpad { i8*, i32 }
          catch i8* null
  %33 = extractvalue { i8*, i32 } %32, 0
  tail call void @__clang_call_terminate(i8* %33) #15
  unreachable

; <label>:34:                                     ; preds = %25
  store i64 0, i64* %17, align 8, !tbaa !69
  br label %35

; <label>:35:                                     ; preds = %34, %1
  %36 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::Counts"* %4 to i8*
  %37 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 1, i32 1, i32 0
  %38 = load i32, i32* %37, align 4, !tbaa !18
  %39 = invoke i64 @pwrite(i32 %38, i8* nonnull %36, i64 24, i64 0)
          to label %43 unwind label %40

; <label>:40:                                     ; preds = %35
  %41 = landingpad { i8*, i32 }
          catch i8* null
  %42 = extractvalue { i8*, i32 } %41, 0
  tail call void @__clang_call_terminate(i8* %42) #15
  unreachable

; <label>:43:                                     ; preds = %35
  ret void
}

declare i32 @__gxx_personality_v0(...)

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8*) local_unnamed_addr #6 comdat {
  %2 = tail call i8* @__cxa_begin_catch(i8* %0) #2
  tail call void @_ZSt9terminatev() #15
  unreachable
}

declare i8* @__cxa_begin_catch(i8*) local_unnamed_addr

declare void @_ZSt9terminatev() local_unnamed_addr

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #5

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) local_unnamed_addr #7

; Function Attrs: nounwind uwtable
define internal fastcc void @_ZNKSt14default_deleteIN12_GLOBAL__N_121BranchCoverageRuntimeEEclEPS1_(%"class.(anonymous namespace)::BranchCoverageRuntime"*) unnamed_addr #8 align 2 personality i32 (...)* @__gxx_personality_v0 {
  %2 = alloca i8, align 1
  %3 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, null
  br i1 %3, label %75, label %4

; <label>:4:                                      ; preds = %1
  %5 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 1
  %6 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::Counts"* %5 to i8*
  %7 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 1, i32 1, i32 0
  %8 = load i32, i32* %7, align 4, !tbaa !18
  %9 = invoke i64 @pwrite(i32 %8, i8* nonnull %6, i64 24, i64 0)
          to label %13 unwind label %10

; <label>:10:                                     ; preds = %4
  %11 = landingpad { i8*, i32 }
          catch i8* null
  %12 = extractvalue { i8*, i32 } %11, 0
  tail call void @__clang_call_terminate(i8* %12) #15
  unreachable

; <label>:13:                                     ; preds = %4
  %14 = load i32, i32* %7, align 4, !tbaa !18
  %15 = icmp sgt i32 %14, -1
  br i1 %15, label %16, label %21

; <label>:16:                                     ; preds = %13
  %17 = invoke i32 @close(i32 %14)
          to label %21 unwind label %18

; <label>:18:                                     ; preds = %16
  %19 = landingpad { i8*, i32 }
          catch i8* null
  %20 = extractvalue { i8*, i32 } %19, 0
  tail call void @__clang_call_terminate(i8* %20) #15
  unreachable

; <label>:21:                                     ; preds = %16, %13
  %22 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 0, i32 1
  %23 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 0, i32 1, i32 1
  %24 = load i64, i64* %23, align 8, !tbaa !69
  %25 = mul i64 %24, 12
  %26 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime::NonSingleBranches"* %22 to i8*
  %27 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 0, i32 1, i32 2, i32 0
  %28 = load i32, i32* %27, align 4, !tbaa !18
  %29 = invoke i64 @write(i32 %28, i8* nonnull %26, i64 %25)
          to label %33 unwind label %30

; <label>:30:                                     ; preds = %21
  %31 = landingpad { i8*, i32 }
          catch i8* null
  %32 = extractvalue { i8*, i32 } %31, 0
  tail call void @__clang_call_terminate(i8* %32) #15
  unreachable

; <label>:33:                                     ; preds = %21
  %34 = load i32, i32* %27, align 4, !tbaa !18
  %35 = icmp sgt i32 %34, -1
  br i1 %35, label %36, label %41

; <label>:36:                                     ; preds = %33
  %37 = invoke i32 @close(i32 %34)
          to label %41 unwind label %38

; <label>:38:                                     ; preds = %36
  %39 = landingpad { i8*, i32 }
          catch i8* null
  %40 = extractvalue { i8*, i32 } %39, 0
  tail call void @__clang_call_terminate(i8* %40) #15
  unreachable

; <label>:41:                                     ; preds = %36, %33
  %42 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 0, i32 0, i32 1
  %43 = load i32, i32* %42, align 8, !tbaa !11
  %44 = zext i32 %43 to i64
  %45 = lshr i64 %44, 3
  %46 = and i64 %44, 7
  %47 = icmp eq i64 %46, 0
  %48 = zext i1 %47 to i64
  %49 = add nuw nsw i64 %45, %48
  %50 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime"* %0 to i8*
  %51 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 0, i32 0, i32 3, i32 0
  %52 = load i32, i32* %51, align 4, !tbaa !18
  %53 = invoke i64 @write(i32 %52, i8* %50, i64 %49)
          to label %57 unwind label %54

; <label>:54:                                     ; preds = %41
  %55 = landingpad { i8*, i32 }
          catch i8* null
  %56 = extractvalue { i8*, i32 } %55, 0
  tail call void @__clang_call_terminate(i8* %56) #15
  unreachable

; <label>:57:                                     ; preds = %41
  call void @llvm.lifetime.start.p0i8(i64 1, i8* nonnull %2) #2
  %58 = load i32, i32* %42, align 8, !tbaa !11
  %59 = trunc i32 %58 to i8
  %60 = and i8 %59, 7
  store i8 %60, i8* %2, align 1, !tbaa !10
  %61 = load i32, i32* %51, align 4, !tbaa !18
  %62 = invoke i64 @write(i32 %61, i8* nonnull %2, i64 1)
          to label %66 unwind label %63

; <label>:63:                                     ; preds = %57
  %64 = landingpad { i8*, i32 }
          catch i8* null
  %65 = extractvalue { i8*, i32 } %64, 0
  tail call void @__clang_call_terminate(i8* %65) #15
  unreachable

; <label>:66:                                     ; preds = %57
  call void @llvm.lifetime.end.p0i8(i64 1, i8* nonnull %2) #2
  %67 = load i32, i32* %51, align 4, !tbaa !18
  %68 = icmp sgt i32 %67, -1
  br i1 %68, label %69, label %74

; <label>:69:                                     ; preds = %66
  %70 = invoke i32 @close(i32 %67)
          to label %74 unwind label %71

; <label>:71:                                     ; preds = %69
  %72 = landingpad { i8*, i32 }
          catch i8* null
  %73 = extractvalue { i8*, i32 } %72, 0
  tail call void @__clang_call_terminate(i8* %73) #15
  unreachable

; <label>:74:                                     ; preds = %66, %69
  tail call void @_ZdlPv(i8* nonnull %50) #20
  br label %75

; <label>:75:                                     ; preds = %74, %1
  ret void
}

declare i64 @pwrite(i32, i8* nocapture readonly, i64, i64) local_unnamed_addr #0

declare i32 @close(i32) local_unnamed_addr #0

declare i64 @write(i32, i8* nocapture readonly, i64) local_unnamed_addr #0

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #5

declare dereferenceable(272) %"class.std::basic_ostream"* @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(%"class.std::basic_ostream"* dereferenceable(272), i8*, i64) local_unnamed_addr #0

; Function Attrs: argmemonly nounwind readonly
declare i64 @strlen(i8* nocapture) local_unnamed_addr #9

; Function Attrs: nobuiltin
declare noalias nonnull i8* @_Znwm(i64) local_unnamed_addr #10

; Function Attrs: noreturn
declare void @_ZSt19__throw_logic_errorPKc(i8*) local_unnamed_addr #11

declare void @__cxa_rethrow() local_unnamed_addr

declare void @__cxa_end_catch() local_unnamed_addr

; Function Attrs: noreturn
declare void @_ZSt20__throw_length_errorPKc(i8*) local_unnamed_addr #11

; Function Attrs: noreturn
declare void @_ZSt17__throw_bad_allocv() local_unnamed_addr #11

; Function Attrs: nounwind readonly
declare i8* @getenv(i8* nocapture) local_unnamed_addr #12

declare void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"*) local_unnamed_addr #0

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"class.std::vector"*) unnamed_addr #8 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %0, i64 0, i32 0, i32 0, i32 0
  %3 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %2, align 8, !tbaa !65
  %4 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %0, i64 0, i32 0, i32 0, i32 1
  %5 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %4, align 8, !tbaa !68
  %6 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %3, %5
  br i1 %6, label %36, label %7

; <label>:7:                                      ; preds = %1
  br label %8

; <label>:8:                                      ; preds = %7, %31
  %9 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %32, %31 ], [ %3, %7 ]
  %10 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, i64 0, i32 0, i32 1
  %11 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %10, i64 0, i32 0, i32 0, i32 0
  %12 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %11, align 8, !tbaa !65
  %13 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, i64 0, i32 0, i32 1, i32 0, i32 0, i32 1
  %14 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %13, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %12, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %14)
          to label %15 unwind label %20

; <label>:15:                                     ; preds = %8
  %16 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %11, align 8, !tbaa !65
  %17 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %16, null
  br i1 %17, label %24, label %18

; <label>:18:                                     ; preds = %15
  %19 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %16 to i8*
  tail call void @_ZdlPv(i8* %19) #2
  br label %24

; <label>:20:                                     ; preds = %8
  %21 = landingpad { i8*, i32 }
          catch i8* null
  %22 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %10, i64 0, i32 0
  %23 = extractvalue { i8*, i32 } %21, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %22) #2
  tail call void @__clang_call_terminate(i8* %23) #15
  unreachable

; <label>:24:                                     ; preds = %18, %15
  %25 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, i64 0, i32 0, i32 0, i32 0, i32 0
  %26 = load i8*, i8** %25, align 8, !tbaa !2
  %27 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, i64 0, i32 0, i32 0, i32 2
  %28 = bitcast %union.anon* %27 to i8*
  %29 = icmp eq i8* %26, %28
  br i1 %29, label %31, label %30

; <label>:30:                                     ; preds = %24
  tail call void @_ZdlPv(i8* %26) #2
  br label %31

; <label>:31:                                     ; preds = %24, %30
  %32 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, i64 1
  %33 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %32, %5
  br i1 %33, label %34, label %8

; <label>:34:                                     ; preds = %31
  %35 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %2, align 8, !tbaa !65
  br label %36

; <label>:36:                                     ; preds = %34, %1
  %37 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %35, %34 ], [ %3, %1 ]
  %38 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %37, null
  br i1 %38, label %41, label %39

; <label>:39:                                     ; preds = %36
  %40 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %37 to i8*
  tail call void @_ZdlPv(i8* %40) #2
  br label %41

; <label>:41:                                     ; preds = %36, %39
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"*) unnamed_addr #8 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = getelementptr inbounds %"struct.std::_Vector_base", %"struct.std::_Vector_base"* %0, i64 0, i32 0, i32 0
  %3 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %2, align 8, !tbaa !65
  %4 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %3, null
  br i1 %4, label %7, label %5

; <label>:5:                                      ; preds = %1
  %6 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %3 to i8*
  tail call void @_ZdlPv(i8* %6) #2
  br label %7

; <label>:7:                                      ; preds = %5, %1
  ret void
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*) local_unnamed_addr #4 comdat align 2 personality i32 (...)* @__gxx_personality_v0 {
  %3 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %0, %1
  br i1 %3, label %31, label %4

; <label>:4:                                      ; preds = %2
  br label %5

; <label>:5:                                      ; preds = %4, %28
  %6 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %29, %28 ], [ %0, %4 ]
  %7 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 1
  %8 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %7, i64 0, i32 0, i32 0, i32 0
  %9 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %8, align 8, !tbaa !65
  %10 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 1, i32 0, i32 0, i32 1
  %11 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %10, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %11)
          to label %12 unwind label %17

; <label>:12:                                     ; preds = %5
  %13 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %8, align 8, !tbaa !65
  %14 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %13, null
  br i1 %14, label %21, label %15

; <label>:15:                                     ; preds = %12
  %16 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %13 to i8*
  tail call void @_ZdlPv(i8* %16) #2
  br label %21

; <label>:17:                                     ; preds = %5
  %18 = landingpad { i8*, i32 }
          catch i8* null
  %19 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %7, i64 0, i32 0
  %20 = extractvalue { i8*, i32 } %18, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %19) #2
  tail call void @__clang_call_terminate(i8* %20) #15
  unreachable

; <label>:21:                                     ; preds = %15, %12
  %22 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 0, i32 0, i32 0
  %23 = load i8*, i8** %22, align 8, !tbaa !2
  %24 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 0, i32 2
  %25 = bitcast %union.anon* %24 to i8*
  %26 = icmp eq i8* %23, %25
  br i1 %26, label %28, label %27

; <label>:27:                                     ; preds = %21
  tail call void @_ZdlPv(i8* %23) #2
  br label %28

; <label>:28:                                     ; preds = %21, %27
  %29 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 1
  %30 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %29, %1
  br i1 %30, label %31, label %5

; <label>:31:                                     ; preds = %28, %2
  ret void
}

; Function Attrs: inlinehint uwtable
define linkonce_odr void @_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_(%"class.std::__cxx11::basic_string"* noalias sret, %"class.std::__cxx11::basic_string"* dereferenceable(32), i8*) local_unnamed_addr #13 comdat personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %5 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %4, %union.anon** %5, align 8, !tbaa !22
  %6 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %7 = load i8*, i8** %6, align 8, !tbaa !2
  %8 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  %9 = load i64, i64* %8, align 8, !tbaa !23
  %10 = icmp ne i8* %7, null
  %11 = icmp eq i64 %9, 0
  %12 = or i1 %10, %11
  br i1 %12, label %14, label %13

; <label>:13:                                     ; preds = %3
  tail call void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
  unreachable

; <label>:14:                                     ; preds = %3
  %15 = bitcast %union.anon* %4 to i8*
  %16 = icmp ugt i64 %9, 15
  br i1 %16, label %17, label %25

; <label>:17:                                     ; preds = %14
  %18 = icmp slt i64 %9, 0
  br i1 %18, label %19, label %20

; <label>:19:                                     ; preds = %17
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
  unreachable

; <label>:20:                                     ; preds = %17
  %21 = add i64 %9, 1
  %22 = tail call i8* @_Znwm(i64 %21)
  %23 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %22, i8** %23, align 8, !tbaa !2
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %9, i64* %24, align 8, !tbaa !10
  br label %25

; <label>:25:                                     ; preds = %20, %14
  %26 = phi i8* [ %22, %20 ], [ %15, %14 ]
  switch i64 %9, label %29 [
    i64 1, label %27
    i64 0, label %30
  ]

; <label>:27:                                     ; preds = %25
  %28 = load i8, i8* %7, align 1, !tbaa !10
  store i8 %28, i8* %26, align 1, !tbaa !10
  br label %30

; <label>:29:                                     ; preds = %25
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* %7, i64 %9, i32 1, i1 false) #2
  br label %30

; <label>:30:                                     ; preds = %25, %27, %29
  %31 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 %9, i64* %31, align 8, !tbaa !23
  %32 = getelementptr inbounds i8, i8* %26, i64 %9
  store i8 0, i8* %32, align 1, !tbaa !10
  %33 = tail call i64 @strlen(i8* %2) #2
  %34 = load i64, i64* %31, align 8, !tbaa !23
  %35 = sub i64 9223372036854775807, %34
  %36 = icmp ult i64 %35, %33
  br i1 %36, label %37, label %39

; <label>:37:                                     ; preds = %30
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i64 0, i64 0)) #17
          to label %38 unwind label %57

; <label>:38:                                     ; preds = %37
  unreachable

; <label>:39:                                     ; preds = %30
  %40 = add i64 %34, %33
  %41 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  %42 = load i8*, i8** %41, align 8, !tbaa !2
  %43 = icmp eq i8* %42, %15
  %44 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  %45 = load i64, i64* %44, align 8
  %46 = select i1 %43, i64 15, i64 %45
  %47 = icmp ugt i64 %40, %46
  br i1 %47, label %56, label %48

; <label>:48:                                     ; preds = %39
  %49 = icmp eq i64 %33, 0
  br i1 %49, label %64, label %50

; <label>:50:                                     ; preds = %48
  %51 = getelementptr inbounds i8, i8* %42, i64 %34
  %52 = icmp eq i64 %33, 1
  br i1 %52, label %53, label %55

; <label>:53:                                     ; preds = %50
  %54 = load i8, i8* %2, align 1, !tbaa !10
  store i8 %54, i8* %51, align 1, !tbaa !10
  br label %64

; <label>:55:                                     ; preds = %50
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %51, i8* %2, i64 %33, i32 1, i1 false) #2
  br label %64

; <label>:56:                                     ; preds = %39
  invoke void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i64 %34, i64 0, i8* %2, i64 %33)
          to label %64 unwind label %57

; <label>:57:                                     ; preds = %56, %37
  %58 = landingpad { i8*, i32 }
          cleanup
  %59 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  %60 = load i8*, i8** %59, align 8, !tbaa !2
  %61 = icmp eq i8* %60, %15
  br i1 %61, label %63, label %62

; <label>:62:                                     ; preds = %57
  tail call void @_ZdlPv(i8* %60) #2
  br label %63

; <label>:63:                                     ; preds = %57, %62
  resume { i8*, i32 } %58

; <label>:64:                                     ; preds = %55, %53, %48, %56
  store i64 %40, i64* %31, align 8, !tbaa !23
  %65 = load i8*, i8** %41, align 8, !tbaa !2
  %66 = getelementptr inbounds i8, i8* %65, i64 %40
  store i8 0, i8* %66, align 1, !tbaa !10
  ret void
}

; Function Attrs: nounwind
declare i32 @getpid() local_unnamed_addr #1

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"*, i64, i64, i8*, i64) local_unnamed_addr #4 comdat align 2 personality i32 (...)* @__gxx_personality_v0 {
  %6 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  %7 = load i64, i64* %6, align 8, !tbaa !23
  %8 = sub i64 %7, %1
  %9 = sub i64 %8, %2
  %10 = sub i64 %4, %2
  %11 = add i64 %10, %7
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  %13 = load i8*, i8** %12, align 8, !tbaa !2
  %14 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %15 = bitcast %union.anon* %14 to i8*
  %16 = icmp eq i8* %13, %15
  br i1 %16, label %20, label %17

; <label>:17:                                     ; preds = %5
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  %19 = load i64, i64* %18, align 8, !tbaa !10
  br label %20

; <label>:20:                                     ; preds = %5, %17
  %21 = phi i64 [ %19, %17 ], [ 15, %5 ]
  %22 = icmp slt i64 %11, 0
  br i1 %22, label %23, label %24

; <label>:23:                                     ; preds = %20
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
  unreachable

; <label>:24:                                     ; preds = %20
  %25 = icmp ugt i64 %11, %21
  br i1 %25, label %26, label %32

; <label>:26:                                     ; preds = %24
  %27 = shl i64 %21, 1
  %28 = icmp ult i64 %11, %27
  br i1 %28, label %29, label %32

; <label>:29:                                     ; preds = %26
  %30 = icmp ult i64 %27, 9223372036854775807
  %31 = select i1 %30, i64 %27, i64 9223372036854775807
  br label %32

; <label>:32:                                     ; preds = %24, %26, %29
  %33 = phi i64 [ %31, %29 ], [ %11, %26 ], [ %11, %24 ]
  %34 = add i64 %33, 1
  %35 = tail call i8* @_Znwm(i64 %34)
  %36 = icmp eq i64 %1, 0
  br i1 %36, label %43, label %37

; <label>:37:                                     ; preds = %32
  %38 = load i8*, i8** %12, align 8, !tbaa !2
  %39 = icmp eq i64 %1, 1
  br i1 %39, label %40, label %42

; <label>:40:                                     ; preds = %37
  %41 = load i8, i8* %38, align 1, !tbaa !10
  store i8 %41, i8* %35, align 1, !tbaa !10
  br label %43

; <label>:42:                                     ; preds = %37
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %35, i8* %38, i64 %1, i32 1, i1 false) #2
  br label %43

; <label>:43:                                     ; preds = %42, %40, %32
  %44 = icmp ne i8* %3, null
  %45 = icmp ne i64 %4, 0
  %46 = and i1 %44, %45
  br i1 %46, label %47, label %53

; <label>:47:                                     ; preds = %43
  %48 = getelementptr inbounds i8, i8* %35, i64 %1
  %49 = icmp eq i64 %4, 1
  br i1 %49, label %50, label %52

; <label>:50:                                     ; preds = %47
  %51 = load i8, i8* %3, align 1, !tbaa !10
  store i8 %51, i8* %48, align 1, !tbaa !10
  br label %53

; <label>:52:                                     ; preds = %47
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %48, i8* nonnull %3, i64 %4, i32 1, i1 false) #2
  br label %53

; <label>:53:                                     ; preds = %52, %50, %43
  %54 = icmp eq i64 %9, 0
  br i1 %54, label %55, label %57

; <label>:55:                                     ; preds = %53
  %56 = load i8*, i8** %12, align 8, !tbaa !2
  br label %67

; <label>:57:                                     ; preds = %53
  %58 = getelementptr inbounds i8, i8* %35, i64 %1
  %59 = getelementptr inbounds i8, i8* %58, i64 %4
  %60 = load i8*, i8** %12, align 8, !tbaa !2
  %61 = getelementptr inbounds i8, i8* %60, i64 %1
  %62 = getelementptr inbounds i8, i8* %61, i64 %2
  %63 = icmp eq i64 %9, 1
  br i1 %63, label %64, label %66

; <label>:64:                                     ; preds = %57
  %65 = load i8, i8* %62, align 1, !tbaa !10
  store i8 %65, i8* %59, align 1, !tbaa !10
  br label %67

; <label>:66:                                     ; preds = %57
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %59, i8* %62, i64 %9, i32 1, i1 false) #2
  br label %67

; <label>:67:                                     ; preds = %55, %66, %64
  %68 = phi i8* [ %56, %55 ], [ %60, %66 ], [ %60, %64 ]
  %69 = icmp eq i8* %68, %15
  br i1 %69, label %71, label %70

; <label>:70:                                     ; preds = %67
  tail call void @_ZdlPv(i8* %68) #2
  br label %71

; <label>:71:                                     ; preds = %67, %70
  store i8* %35, i8** %12, align 8, !tbaa !2
  %72 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %33, i64* %72, align 8, !tbaa !10
  ret void
}

; Function Attrs: uwtable
define linkonce_odr dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"*, i64, i64, i8*, i64) local_unnamed_addr #4 comdat align 2 personality i32 (...)* @__gxx_personality_v0 {
  %6 = sub i64 0, %2
  %7 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  %8 = load i64, i64* %7, align 8, !tbaa !23
  %9 = add i64 %2, 9223372036854775807
  %10 = sub i64 %9, %8
  %11 = icmp ult i64 %10, %4
  br i1 %11, label %12, label %13

; <label>:12:                                     ; preds = %5
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.15, i64 0, i64 0)) #17
  unreachable

; <label>:13:                                     ; preds = %5
  %14 = sub i64 %4, %2
  %15 = add i64 %14, %8
  %16 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  %17 = load i8*, i8** %16, align 8, !tbaa !2
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %19 = bitcast %union.anon* %18 to i8*
  %20 = icmp eq i8* %17, %19
  br i1 %20, label %24, label %21

; <label>:21:                                     ; preds = %13
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  %23 = load i64, i64* %22, align 8, !tbaa !10
  br label %24

; <label>:24:                                     ; preds = %13, %21
  %25 = phi i64 [ %23, %21 ], [ 15, %13 ]
  %26 = icmp ugt i64 %15, %25
  br i1 %26, label %102, label %27

; <label>:27:                                     ; preds = %24
  %28 = getelementptr inbounds i8, i8* %17, i64 %1
  %29 = sub i64 %8, %1
  %30 = sub i64 %29, %2
  %31 = icmp ugt i8* %17, %3
  %32 = getelementptr inbounds i8, i8* %17, i64 %8
  %33 = icmp ult i8* %32, %3
  %34 = or i1 %31, %33
  br i1 %34, label %35, label %50

; <label>:35:                                     ; preds = %27
  %36 = icmp eq i64 %30, 0
  %37 = icmp eq i64 %4, %2
  %38 = or i1 %37, %36
  br i1 %38, label %46, label %39

; <label>:39:                                     ; preds = %35
  %40 = getelementptr inbounds i8, i8* %28, i64 %4
  %41 = getelementptr inbounds i8, i8* %28, i64 %2
  %42 = icmp eq i64 %30, 1
  br i1 %42, label %43, label %45

; <label>:43:                                     ; preds = %39
  %44 = load i8, i8* %41, align 1, !tbaa !10
  store i8 %44, i8* %40, align 1, !tbaa !10
  br label %46

; <label>:45:                                     ; preds = %39
  tail call void @llvm.memmove.p0i8.p0i8.i64(i8* %40, i8* %41, i64 %30, i32 1, i1 false) #2
  br label %46

; <label>:46:                                     ; preds = %45, %43, %35
  switch i64 %4, label %49 [
    i64 0, label %103
    i64 1, label %47
  ]

; <label>:47:                                     ; preds = %46
  %48 = load i8, i8* %3, align 1, !tbaa !10
  store i8 %48, i8* %28, align 1, !tbaa !10
  br label %103

; <label>:49:                                     ; preds = %46
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* %3, i64 %4, i32 1, i1 false) #2
  br label %103

; <label>:50:                                     ; preds = %27
  %51 = icmp ugt i64 %4, %2
  %52 = add i64 %4, -1
  %53 = icmp ult i64 %52, %2
  br i1 %53, label %54, label %59

; <label>:54:                                     ; preds = %50
  %55 = icmp eq i64 %4, 1
  br i1 %55, label %56, label %58

; <label>:56:                                     ; preds = %54
  %57 = load i8, i8* %3, align 1, !tbaa !10
  store i8 %57, i8* %28, align 1, !tbaa !10
  br label %59

; <label>:58:                                     ; preds = %54
  tail call void @llvm.memmove.p0i8.p0i8.i64(i8* %28, i8* %3, i64 %4, i32 1, i1 false) #2
  br label %59

; <label>:59:                                     ; preds = %50, %58, %56
  %60 = icmp eq i64 %30, 0
  %61 = icmp eq i64 %4, %2
  %62 = or i1 %61, %60
  br i1 %62, label %70, label %63

; <label>:63:                                     ; preds = %59
  %64 = getelementptr inbounds i8, i8* %28, i64 %4
  %65 = getelementptr inbounds i8, i8* %28, i64 %2
  %66 = icmp eq i64 %30, 1
  br i1 %66, label %67, label %69

; <label>:67:                                     ; preds = %63
  %68 = load i8, i8* %65, align 1, !tbaa !10
  store i8 %68, i8* %64, align 1, !tbaa !10
  br label %70

; <label>:69:                                     ; preds = %63
  tail call void @llvm.memmove.p0i8.p0i8.i64(i8* %64, i8* %65, i64 %30, i32 1, i1 false) #2
  br label %70

; <label>:70:                                     ; preds = %69, %67, %59
  br i1 %51, label %71, label %103

; <label>:71:                                     ; preds = %70
  %72 = getelementptr inbounds i8, i8* %3, i64 %4
  %73 = getelementptr inbounds i8, i8* %28, i64 %2
  %74 = icmp ugt i8* %72, %73
  br i1 %74, label %80, label %75

; <label>:75:                                     ; preds = %71
  %76 = icmp eq i64 %4, 1
  br i1 %76, label %77, label %79

; <label>:77:                                     ; preds = %75
  %78 = load i8, i8* %3, align 1, !tbaa !10
  store i8 %78, i8* %28, align 1, !tbaa !10
  br label %103

; <label>:79:                                     ; preds = %75
  tail call void @llvm.memmove.p0i8.p0i8.i64(i8* %28, i8* %3, i64 %4, i32 1, i1 false) #2
  br label %103

; <label>:80:                                     ; preds = %71
  %81 = icmp ugt i8* %73, %3
  br i1 %81, label %88, label %82

; <label>:82:                                     ; preds = %80
  %83 = getelementptr inbounds i8, i8* %72, i64 %6
  %84 = icmp eq i64 %4, 1
  br i1 %84, label %85, label %87

; <label>:85:                                     ; preds = %82
  %86 = load i8, i8* %83, align 1, !tbaa !10
  store i8 %86, i8* %28, align 1, !tbaa !10
  br label %103

; <label>:87:                                     ; preds = %82
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* %83, i64 %4, i32 1, i1 false) #2
  br label %103

; <label>:88:                                     ; preds = %80
  %89 = ptrtoint i8* %73 to i64
  %90 = ptrtoint i8* %3 to i64
  %91 = sub i64 %89, %90
  switch i64 %91, label %94 [
    i64 1, label %92
    i64 0, label %95
  ]

; <label>:92:                                     ; preds = %88
  %93 = load i8, i8* %3, align 1, !tbaa !10
  store i8 %93, i8* %28, align 1, !tbaa !10
  br label %95

; <label>:94:                                     ; preds = %88
  tail call void @llvm.memmove.p0i8.p0i8.i64(i8* %28, i8* %3, i64 %91, i32 1, i1 false) #2
  br label %95

; <label>:95:                                     ; preds = %88, %92, %94
  %96 = getelementptr inbounds i8, i8* %28, i64 %91
  %97 = getelementptr inbounds i8, i8* %28, i64 %4
  %98 = sub i64 %4, %91
  switch i64 %98, label %101 [
    i64 1, label %99
    i64 0, label %103
  ]

; <label>:99:                                     ; preds = %95
  %100 = load i8, i8* %97, align 1, !tbaa !10
  store i8 %100, i8* %96, align 1, !tbaa !10
  br label %103

; <label>:101:                                    ; preds = %95
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %96, i8* %97, i64 %98, i32 1, i1 false) #2
  br label %103

; <label>:102:                                    ; preds = %24
  tail call void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i64 %1, i64 %2, i8* %3, i64 %4)
  br label %103

; <label>:103:                                    ; preds = %46, %101, %99, %95, %87, %85, %79, %77, %49, %47, %70, %102
  store i64 %15, i64* %7, align 8, !tbaa !23
  %104 = load i8*, i8** %16, align 8, !tbaa !2
  %105 = getelementptr inbounds i8, i8* %104, i64 %15
  store i8 0, i8* %105, align 1, !tbaa !10
  ret %"class.std::__cxx11::basic_string"* %0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: uwtable
define linkonce_odr void @_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z(%"class.std::__cxx11::basic_string"* noalias sret, i32 (i8*, i64, i8*, %struct.__va_list_tag*)*, i64, i8*, ...) local_unnamed_addr #4 comdat personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = alloca [1 x %struct.__va_list_tag], align 16
  %6 = alloca i8, i64 %2, align 16
  %7 = bitcast [1 x %struct.__va_list_tag]* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 24, i8* nonnull %7) #2
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  call void @llvm.va_start(i8* nonnull %7)
  %9 = call i32 %1(i8* nonnull %6, i64 %2, i8* %3, %struct.__va_list_tag* nonnull %8)
  call void @llvm.va_end(i8* nonnull %7)
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %12 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %11, %union.anon** %12, align 8, !tbaa !22
  %13 = bitcast %union.anon* %11 to i8*
  %14 = icmp ugt i32 %9, 15
  br i1 %14, label %15, label %25

; <label>:15:                                     ; preds = %4
  %16 = icmp slt i32 %9, 0
  br i1 %16, label %17, label %19

; <label>:17:                                     ; preds = %15
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %18 unwind label %33

; <label>:18:                                     ; preds = %17
  unreachable

; <label>:19:                                     ; preds = %15
  %20 = add nsw i64 %10, 1
  %21 = invoke i8* @_Znwm(i64 %20)
          to label %22 unwind label %33

; <label>:22:                                     ; preds = %19
  %23 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %21, i8** %23, align 8, !tbaa !2
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %10, i64* %24, align 8, !tbaa !10
  br label %25

; <label>:25:                                     ; preds = %22, %4
  %26 = phi i8* [ %21, %22 ], [ %13, %4 ]
  switch i64 %10, label %29 [
    i64 1, label %27
    i64 0, label %30
  ]

; <label>:27:                                     ; preds = %25
  %28 = load i8, i8* %6, align 16, !tbaa !10
  store i8 %28, i8* %26, align 1, !tbaa !10
  br label %30

; <label>:29:                                     ; preds = %25
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %26, i8* nonnull %6, i64 %10, i32 1, i1 false) #2
  br label %30

; <label>:30:                                     ; preds = %29, %27, %25
  %31 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 %10, i64* %31, align 8, !tbaa !23
  %32 = getelementptr inbounds i8, i8* %26, i64 %10
  store i8 0, i8* %32, align 1, !tbaa !10
  call void @llvm.lifetime.end.p0i8(i64 24, i8* nonnull %7) #2
  ret void

; <label>:33:                                     ; preds = %19, %17
  %34 = landingpad { i8*, i32 }
          cleanup
  call void @llvm.lifetime.end.p0i8(i64 24, i8* nonnull %7) #2
  resume { i8*, i32 } %34
}

; Function Attrs: nounwind
declare i32 @vsnprintf(i8* nocapture, i64, i8* nocapture readonly, %struct.__va_list_tag*) #1

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

; Function Attrs: uwtable
define internal fastcc i32 @_ZN12_GLOBAL__N_121BranchCoverageRuntime6Output11createAtDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.(anonymous namespace)::BranchCoverageRuntime::Output"* nocapture readonly, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::experimental::filesystem::v1::__cxx11::path", align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  %5 = alloca %"class.std::experimental::filesystem::v1::__cxx11::path", align 8
  %6 = alloca %"class.std::experimental::filesystem::v1::__cxx11::path", align 8
  %7 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %0, i64 0, i32 1
  %8 = load i32, i32* %7, align 8, !tbaa !59
  %9 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %10 = load i8*, i8** %9, align 8, !tbaa !2
  %11 = tail call i32 (i32, i8*, i32, ...) @openat(i32 %8, i8* %10, i32 577, i32 420)
  %12 = icmp eq i32 %11, -1
  br i1 %12, label %13, label %178

; <label>:13:                                     ; preds = %2
  %14 = bitcast %"class.std::__cxx11::basic_string"* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %14) #2
  %15 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime::Output", %"class.(anonymous namespace)::BranchCoverageRuntime::Output"* %0, i64 0, i32 0
  %16 = load %"class.std::experimental::filesystem::v1::__cxx11::path"*, %"class.std::experimental::filesystem::v1::__cxx11::path"** %15, align 8, !tbaa !72
  %17 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 64, i8* nonnull %17) #2
  call void @_ZNSt12experimental10filesystem2v17__cxx114pathC2INSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES3_EERKT_(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %1)
  %18 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 64, i8* nonnull %18)
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114pathC2ERKS3_(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %3, %"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull dereferenceable(64) %16)
          to label %19 unwind label %108

; <label>:19:                                     ; preds = %13
  %20 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %6, i64 0, i32 0
  %21 = invoke dereferenceable(64) %"class.std::experimental::filesystem::v1::__cxx11::path"* @_ZNSt12experimental10filesystem2v17__cxx114path9_M_appendERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %3, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %20)
          to label %22 unwind label %23, !noalias !73

; <label>:22:                                     ; preds = %19
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114pathC2ERKS3_(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %5, %"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull dereferenceable(64) %21)
          to label %46 unwind label %23

; <label>:23:                                     ; preds = %22, %19
  %24 = landingpad { i8*, i32 }
          cleanup
  %25 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 1
  %26 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %25, i64 0, i32 0, i32 0, i32 0
  %27 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %26, align 8, !tbaa !65
  %28 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 1, i32 0, i32 0, i32 1
  %29 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %28, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %27, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %29)
          to label %30 unwind label %35

; <label>:30:                                     ; preds = %23
  %31 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %26, align 8, !tbaa !65
  %32 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %31, null
  br i1 %32, label %39, label %33

; <label>:33:                                     ; preds = %30
  %34 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %31 to i8*
  call void @_ZdlPv(i8* %34) #2
  br label %39

; <label>:35:                                     ; preds = %23
  %36 = landingpad { i8*, i32 }
          catch i8* null
  %37 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %25, i64 0, i32 0
  %38 = extractvalue { i8*, i32 } %36, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %37) #2
  call void @__clang_call_terminate(i8* %38) #15
  unreachable

; <label>:39:                                     ; preds = %33, %30
  %40 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 0, i32 0, i32 0
  %41 = load i8*, i8** %40, align 8, !tbaa !2
  %42 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 0, i32 2
  %43 = bitcast %union.anon* %42 to i8*
  %44 = icmp eq i8* %41, %43
  br i1 %44, label %110, label %45

; <label>:45:                                     ; preds = %39
  call void @_ZdlPv(i8* %41) #2
  br label %110

; <label>:46:                                     ; preds = %22
  %47 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 1
  %48 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %47, i64 0, i32 0, i32 0, i32 0
  %49 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %48, align 8, !tbaa !65
  %50 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 1, i32 0, i32 0, i32 1
  %51 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %50, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %49, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %51)
          to label %52 unwind label %57

; <label>:52:                                     ; preds = %46
  %53 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %48, align 8, !tbaa !65
  %54 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %53, null
  br i1 %54, label %61, label %55

; <label>:55:                                     ; preds = %52
  %56 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %53 to i8*
  call void @_ZdlPv(i8* %56) #2
  br label %61

; <label>:57:                                     ; preds = %46
  %58 = landingpad { i8*, i32 }
          catch i8* null
  %59 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %47, i64 0, i32 0
  %60 = extractvalue { i8*, i32 } %58, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %59) #2
  call void @__clang_call_terminate(i8* %60) #15
  unreachable

; <label>:61:                                     ; preds = %55, %52
  %62 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 0, i32 0, i32 0
  %63 = load i8*, i8** %62, align 8, !tbaa !2
  %64 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %3, i64 0, i32 0, i32 2
  %65 = bitcast %union.anon* %64 to i8*
  %66 = icmp eq i8* %63, %65
  br i1 %66, label %68, label %67

; <label>:67:                                     ; preds = %61
  call void @_ZdlPv(i8* %63) #2
  br label %68

; <label>:68:                                     ; preds = %67, %61
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %18)
  %69 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2
  %70 = bitcast %"class.std::__cxx11::basic_string"* %4 to %union.anon**
  store %union.anon* %69, %union.anon** %70, align 8, !tbaa !22, !alias.scope !76
  %71 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %5, i64 0, i32 0, i32 0, i32 0
  %72 = load i8*, i8** %71, align 8, !tbaa !2, !noalias !76
  %73 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %5, i64 0, i32 0, i32 1
  %74 = load i64, i64* %73, align 8, !tbaa !23, !noalias !76
  %75 = icmp ne i8* %72, null
  %76 = icmp eq i64 %74, 0
  %77 = or i1 %75, %76
  br i1 %77, label %80, label %78

; <label>:78:                                     ; preds = %68
  invoke void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
          to label %79 unwind label %114

; <label>:79:                                     ; preds = %78
  unreachable

; <label>:80:                                     ; preds = %68
  %81 = bitcast %union.anon* %69 to i8*
  %82 = icmp ugt i64 %74, 15
  br i1 %82, label %83, label %93

; <label>:83:                                     ; preds = %80
  %84 = icmp slt i64 %74, 0
  br i1 %84, label %85, label %87

; <label>:85:                                     ; preds = %83
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %86 unwind label %114

; <label>:86:                                     ; preds = %85
  unreachable

; <label>:87:                                     ; preds = %83
  %88 = add i64 %74, 1
  %89 = invoke i8* @_Znwm(i64 %88)
          to label %90 unwind label %114

; <label>:90:                                     ; preds = %87
  %91 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  store i8* %89, i8** %91, align 8, !tbaa !2, !alias.scope !76
  %92 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2, i32 0
  store i64 %74, i64* %92, align 8, !tbaa !10, !alias.scope !76
  br label %93

; <label>:93:                                     ; preds = %90, %80
  %94 = phi i8* [ %89, %90 ], [ %81, %80 ]
  switch i64 %74, label %97 [
    i64 1, label %95
    i64 0, label %98
  ]

; <label>:95:                                     ; preds = %93
  %96 = load i8, i8* %72, align 1, !tbaa !10
  store i8 %96, i8* %94, align 1, !tbaa !10
  br label %98

; <label>:97:                                     ; preds = %93
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %94, i8* %72, i64 %74, i32 1, i1 false) #2
  br label %98

; <label>:98:                                     ; preds = %97, %95, %93
  %99 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 1
  store i64 %74, i64* %99, align 8, !tbaa !23, !alias.scope !76
  %100 = getelementptr inbounds i8, i8* %94, i64 %74
  store i8 0, i8* %100, align 1, !tbaa !10
  %101 = call i8* @__cxa_allocate_exception(i64 192) #2
  %102 = bitcast i8* %101 to %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*
  %103 = tail call dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() #18
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %102, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %4, i32 0, %"class.std::_V2::error_category"* nonnull %103)
          to label %104 unwind label %106

; <label>:104:                                    ; preds = %98
  invoke void @__cxa_throw(i8* %101, i8* bitcast (i8** @_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE to i8*), i8* bitcast (void (%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*)* @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev to i8*)) #17
          to label %105 unwind label %118

; <label>:105:                                    ; preds = %104
  unreachable

; <label>:106:                                    ; preds = %98
  %107 = landingpad { i8*, i32 }
          cleanup
  call void @__cxa_free_exception(i8* %101) #2
  br label %120

; <label>:108:                                    ; preds = %13
  %109 = landingpad { i8*, i32 }
          cleanup
  br label %110

; <label>:110:                                    ; preds = %45, %39, %108
  %111 = phi { i8*, i32 } [ %109, %108 ], [ %24, %39 ], [ %24, %45 ]
  %112 = extractvalue { i8*, i32 } %111, 0
  %113 = extractvalue { i8*, i32 } %111, 1
  br label %151

; <label>:114:                                    ; preds = %87, %85, %78
  %115 = landingpad { i8*, i32 }
          cleanup
  %116 = extractvalue { i8*, i32 } %115, 0
  %117 = extractvalue { i8*, i32 } %115, 1
  br label %128

; <label>:118:                                    ; preds = %104
  %119 = landingpad { i8*, i32 }
          cleanup
  br label %120

; <label>:120:                                    ; preds = %106, %118
  %121 = phi { i8*, i32 } [ %119, %118 ], [ %107, %106 ]
  %122 = extractvalue { i8*, i32 } %121, 0
  %123 = extractvalue { i8*, i32 } %121, 1
  %124 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  %125 = load i8*, i8** %124, align 8, !tbaa !2
  %126 = icmp eq i8* %125, %81
  br i1 %126, label %128, label %127

; <label>:127:                                    ; preds = %120
  call void @_ZdlPv(i8* %125) #2
  br label %128

; <label>:128:                                    ; preds = %127, %120, %114
  %129 = phi i8* [ %116, %114 ], [ %122, %120 ], [ %122, %127 ]
  %130 = phi i32 [ %117, %114 ], [ %123, %120 ], [ %123, %127 ]
  %131 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %5, i64 0, i32 1
  %132 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %131, i64 0, i32 0, i32 0, i32 0
  %133 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %132, align 8, !tbaa !65
  %134 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %5, i64 0, i32 1, i32 0, i32 0, i32 1
  %135 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %134, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %133, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %135)
          to label %136 unwind label %141

; <label>:136:                                    ; preds = %128
  %137 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %132, align 8, !tbaa !65
  %138 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %137, null
  br i1 %138, label %145, label %139

; <label>:139:                                    ; preds = %136
  %140 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %137 to i8*
  call void @_ZdlPv(i8* %140) #2
  br label %145

; <label>:141:                                    ; preds = %128
  %142 = landingpad { i8*, i32 }
          catch i8* null
  %143 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %131, i64 0, i32 0
  %144 = extractvalue { i8*, i32 } %142, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %143) #2
  call void @__clang_call_terminate(i8* %144) #15
  unreachable

; <label>:145:                                    ; preds = %139, %136
  %146 = load i8*, i8** %71, align 8, !tbaa !2
  %147 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %5, i64 0, i32 0, i32 2
  %148 = bitcast %union.anon* %147 to i8*
  %149 = icmp eq i8* %146, %148
  br i1 %149, label %151, label %150

; <label>:150:                                    ; preds = %145
  call void @_ZdlPv(i8* %146) #2
  br label %151

; <label>:151:                                    ; preds = %150, %145, %110
  %152 = phi i8* [ %112, %110 ], [ %129, %145 ], [ %129, %150 ]
  %153 = phi i32 [ %113, %110 ], [ %130, %145 ], [ %130, %150 ]
  %154 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %6, i64 0, i32 1
  %155 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %154, i64 0, i32 0, i32 0, i32 0
  %156 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %155, align 8, !tbaa !65
  %157 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %6, i64 0, i32 1, i32 0, i32 0, i32 1
  %158 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %157, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %156, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %158)
          to label %159 unwind label %164

; <label>:159:                                    ; preds = %151
  %160 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %155, align 8, !tbaa !65
  %161 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %160, null
  br i1 %161, label %168, label %162

; <label>:162:                                    ; preds = %159
  %163 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %160 to i8*
  call void @_ZdlPv(i8* %163) #2
  br label %168

; <label>:164:                                    ; preds = %151
  %165 = landingpad { i8*, i32 }
          catch i8* null
  %166 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %154, i64 0, i32 0
  %167 = extractvalue { i8*, i32 } %165, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %166) #2
  call void @__clang_call_terminate(i8* %167) #15
  unreachable

; <label>:168:                                    ; preds = %162, %159
  %169 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %6, i64 0, i32 0, i32 0, i32 0
  %170 = load i8*, i8** %169, align 8, !tbaa !2
  %171 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %6, i64 0, i32 0, i32 2
  %172 = bitcast %union.anon* %171 to i8*
  %173 = icmp eq i8* %170, %172
  br i1 %173, label %175, label %174

; <label>:174:                                    ; preds = %168
  call void @_ZdlPv(i8* %170) #2
  br label %175

; <label>:175:                                    ; preds = %168, %174
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %17) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %14) #2
  %176 = insertvalue { i8*, i32 } undef, i8* %152, 0
  %177 = insertvalue { i8*, i32 } %176, i32 %153, 1
  resume { i8*, i32 } %177

; <label>:178:                                    ; preds = %2
  ret i32 %11
}

; Function Attrs: nounwind
declare i32 @mkdir(i8* nocapture readonly, i32) local_unnamed_addr #1

; Function Attrs: nounwind readnone
declare i32* @__errno_location() local_unnamed_addr #14

declare i32 @open(i8* nocapture readonly, i32, ...) local_unnamed_addr #0

; Function Attrs: nounwind
declare void @perror(i8* nocapture readonly) local_unnamed_addr #1

declare i8* @__cxa_allocate_exception(i64) local_unnamed_addr

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*, %"class.std::__cxx11::basic_string"* dereferenceable(32), i32, %"class.std::_V2::error_category"*) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 0
  tail call void @_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::system_error"* %5, i32 %2, %"class.std::_V2::error_category"* %3, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %1)
  %6 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 0, i32 0, i32 0, i32 0
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTVNSt12experimental10filesystem2v17__cxx1116filesystem_errorE, i64 0, inrange i32 0, i64 2) to i32 (...)**), i32 (...)*** %6, align 8, !tbaa !79
  %7 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1
  %8 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 0, i32 2
  %9 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %7 to %union.anon**
  store %union.anon* %8, %union.anon** %9, align 8, !tbaa !22
  %10 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 0, i32 1
  store i64 0, i64* %10, align 8, !tbaa !23
  %11 = bitcast %union.anon* %8 to i8*
  store i8 0, i8* %11, align 1, !tbaa !10
  %12 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 1
  %13 = bitcast %"class.std::vector"* %12 to i8*
  tail call void @llvm.memset.p0i8.i64(i8* nonnull %13, i8 0, i64 25, i32 8, i1 false) #2
  %14 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2
  %15 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 0, i32 2
  %16 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %14 to %union.anon**
  store %union.anon* %15, %union.anon** %16, align 8, !tbaa !22
  %17 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 0, i32 1
  store i64 0, i64* %17, align 8, !tbaa !23
  %18 = bitcast %union.anon* %15 to i8*
  store i8 0, i8* %18, align 1, !tbaa !10
  %19 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 1
  %20 = bitcast %"class.std::vector"* %19 to i8*
  tail call void @llvm.memset.p0i8.i64(i8* nonnull %20, i8 0, i64 25, i32 8, i1 false) #2
  %21 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 3
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv(%"class.std::__cxx11::basic_string"* nonnull sret %21, %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0)
          to label %22 unwind label %23

; <label>:22:                                     ; preds = %4
  ret void

; <label>:23:                                     ; preds = %4
  %24 = landingpad { i8*, i32 }
          cleanup
  %25 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %19, i64 0, i32 0, i32 0, i32 0
  %26 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %25, align 8, !tbaa !65
  %27 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 1, i32 0, i32 0, i32 1
  %28 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %27, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %26, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %28)
          to label %29 unwind label %34

; <label>:29:                                     ; preds = %23
  %30 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %25, align 8, !tbaa !65
  %31 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %30, null
  br i1 %31, label %38, label %32

; <label>:32:                                     ; preds = %29
  %33 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %30 to i8*
  tail call void @_ZdlPv(i8* %33) #2
  br label %38

; <label>:34:                                     ; preds = %23
  %35 = landingpad { i8*, i32 }
          catch i8* null
  %36 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %19, i64 0, i32 0
  %37 = extractvalue { i8*, i32 } %35, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %36) #2
  tail call void @__clang_call_terminate(i8* %37) #15
  unreachable

; <label>:38:                                     ; preds = %32, %29
  %39 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %14, i64 0, i32 0, i32 0, i32 0
  %40 = load i8*, i8** %39, align 8, !tbaa !2
  %41 = icmp eq i8* %40, %18
  br i1 %41, label %43, label %42

; <label>:42:                                     ; preds = %38
  tail call void @_ZdlPv(i8* %40) #2
  br label %43

; <label>:43:                                     ; preds = %38, %42
  %44 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %12, i64 0, i32 0, i32 0, i32 0
  %45 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %44, align 8, !tbaa !65
  %46 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 1, i32 0, i32 0, i32 1
  %47 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %46, align 8, !tbaa !68
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %47)
          to label %48 unwind label %53

; <label>:48:                                     ; preds = %43
  %49 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %44, align 8, !tbaa !65
  %50 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %49, null
  br i1 %50, label %57, label %51

; <label>:51:                                     ; preds = %48
  %52 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %49 to i8*
  tail call void @_ZdlPv(i8* %52) #2
  br label %57

; <label>:53:                                     ; preds = %43
  %54 = landingpad { i8*, i32 }
          catch i8* null
  %55 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %12, i64 0, i32 0
  %56 = extractvalue { i8*, i32 } %54, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %55) #2
  tail call void @__clang_call_terminate(i8* %56) #15
  unreachable

; <label>:57:                                     ; preds = %51, %48
  %58 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %7, i64 0, i32 0, i32 0, i32 0
  %59 = load i8*, i8** %58, align 8, !tbaa !2
  %60 = icmp eq i8* %59, %11
  br i1 %60, label %62, label %61

; <label>:61:                                     ; preds = %57
  tail call void @_ZdlPv(i8* %59) #2
  br label %62

; <label>:62:                                     ; preds = %57, %61
  tail call void @_ZNSt12system_errorD2Ev(%"class.std::system_error"* nonnull %5) #2
  resume { i8*, i32 } %24
}

declare void @__cxa_free_exception(i8*) local_unnamed_addr

; Function Attrs: nounwind
declare void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*) unnamed_addr #1

declare void @__cxa_throw(i8*, i8*, i8*) local_unnamed_addr

; Function Attrs: nounwind readnone
declare dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() local_unnamed_addr #14

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::system_error"*, i32, %"class.std::_V2::error_category"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = alloca %"class.std::__cxx11::basic_string", align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 0
  %9 = bitcast %"class.std::__cxx11::basic_string"* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %9) #2
  %10 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %10) #2
  call void @_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_(%"class.std::__cxx11::basic_string"* nonnull sret %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %3, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.22, i64 0, i64 0))
  %11 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %11) #2
  %12 = bitcast %"class.std::_V2::error_category"* %2 to void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)***
  %13 = load void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)**, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*** %12, align 8, !tbaa !79, !noalias !81
  %14 = getelementptr inbounds void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)** %13, i64 4
  %15 = load void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)** %14, align 8, !noalias !81
  invoke void %15(%"class.std::__cxx11::basic_string"* nonnull sret %7, %"class.std::_V2::error_category"* nonnull %2, i32 %1)
          to label %16 unwind label %134

; <label>:16:                                     ; preds = %4
  %17 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  %18 = load i64, i64* %17, align 8, !tbaa !23, !noalias !84
  %19 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 1
  %20 = load i64, i64* %19, align 8, !tbaa !23, !noalias !84
  %21 = add i64 %20, %18
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  %23 = load i8*, i8** %22, align 8, !tbaa !2, !noalias !84
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %25 = bitcast %union.anon* %24 to i8*
  %26 = icmp eq i8* %23, %25
  %27 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  %28 = load i64, i64* %27, align 8, !noalias !84
  %29 = select i1 %26, i64 15, i64 %28
  %30 = icmp ugt i64 %21, %29
  %31 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %32 = load i8*, i8** %31, align 8, !tbaa !2, !noalias !84
  br i1 %30, label %33, label %47

; <label>:33:                                     ; preds = %16
  %34 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %35 = bitcast %union.anon* %34 to i8*
  %36 = icmp eq i8* %32, %35
  %37 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  %38 = load i64, i64* %37, align 8, !noalias !84
  %39 = select i1 %36, i64 15, i64 %38
  %40 = icmp ugt i64 %21, %39
  br i1 %40, label %55, label %41

; <label>:41:                                     ; preds = %33
  %42 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %7, i64 0, i64 0, i8* %23, i64 %18)
          to label %43 unwind label %141

; <label>:43:                                     ; preds = %41
  %44 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %42, i64 0, i32 0, i32 0
  %45 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %42, i64 0, i32 2
  %46 = bitcast %union.anon* %45 to i8*
  br label %93

; <label>:47:                                     ; preds = %16
  %48 = icmp eq i64 %20, 0
  br i1 %48, label %90, label %49

; <label>:49:                                     ; preds = %47
  %50 = getelementptr inbounds i8, i8* %23, i64 %18
  %51 = icmp eq i64 %20, 1
  br i1 %51, label %52, label %54

; <label>:52:                                     ; preds = %49
  %53 = load i8, i8* %32, align 1, !tbaa !10
  store i8 %53, i8* %50, align 1, !tbaa !10
  br label %90

; <label>:54:                                     ; preds = %49
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %50, i8* %32, i64 %20, i32 1, i1 false) #2
  br label %90

; <label>:55:                                     ; preds = %33
  %56 = icmp slt i64 %21, 0
  br i1 %56, label %57, label %59

; <label>:57:                                     ; preds = %55
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %58 unwind label %141

; <label>:58:                                     ; preds = %57
  unreachable

; <label>:59:                                     ; preds = %55
  %60 = shl i64 %29, 1
  %61 = icmp ult i64 %21, %60
  %62 = icmp ult i64 %60, 9223372036854775807
  %63 = select i1 %62, i64 %60, i64 9223372036854775807
  %64 = select i1 %61, i64 %63, i64 %21
  %65 = add i64 %64, 1
  %66 = invoke i8* @_Znwm(i64 %65)
          to label %67 unwind label %141

; <label>:67:                                     ; preds = %59
  %68 = icmp eq i64 %18, 0
  br i1 %68, label %75, label %69

; <label>:69:                                     ; preds = %67
  %70 = load i8*, i8** %22, align 8, !tbaa !2
  %71 = icmp eq i64 %18, 1
  br i1 %71, label %72, label %74

; <label>:72:                                     ; preds = %69
  %73 = load i8, i8* %70, align 1, !tbaa !10
  store i8 %73, i8* %66, align 1, !tbaa !10
  br label %75

; <label>:74:                                     ; preds = %69
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %66, i8* %70, i64 %18, i32 1, i1 false) #2
  br label %75

; <label>:75:                                     ; preds = %74, %72, %67
  %76 = icmp ne i8* %32, null
  %77 = icmp ne i64 %20, 0
  %78 = and i1 %77, %76
  br i1 %78, label %79, label %85

; <label>:79:                                     ; preds = %75
  %80 = getelementptr inbounds i8, i8* %66, i64 %18
  %81 = icmp eq i64 %20, 1
  br i1 %81, label %82, label %84

; <label>:82:                                     ; preds = %79
  %83 = load i8, i8* %32, align 1, !tbaa !10
  store i8 %83, i8* %80, align 1, !tbaa !10
  br label %85

; <label>:84:                                     ; preds = %79
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %80, i8* nonnull %32, i64 %20, i32 1, i1 false) #2
  br label %85

; <label>:85:                                     ; preds = %84, %82, %75
  %86 = load i8*, i8** %22, align 8, !tbaa !2
  %87 = icmp eq i8* %86, %25
  br i1 %87, label %89, label %88

; <label>:88:                                     ; preds = %85
  call void @_ZdlPv(i8* %86) #2
  br label %89

; <label>:89:                                     ; preds = %88, %85
  store i8* %66, i8** %22, align 8, !tbaa !2
  store i64 %64, i64* %27, align 8, !tbaa !10
  br label %90

; <label>:90:                                     ; preds = %89, %54, %52, %47
  store i64 %21, i64* %17, align 8, !tbaa !23, !noalias !84
  %91 = load i8*, i8** %22, align 8, !tbaa !2, !noalias !84
  %92 = getelementptr inbounds i8, i8* %91, i64 %21
  store i8 0, i8* %92, align 1, !tbaa !10
  br label %93

; <label>:93:                                     ; preds = %90, %43
  %94 = phi i8* [ %25, %90 ], [ %46, %43 ]
  %95 = phi %union.anon* [ %24, %90 ], [ %45, %43 ]
  %96 = phi i8** [ %22, %90 ], [ %44, %43 ]
  %97 = phi %"class.std::__cxx11::basic_string"* [ %6, %90 ], [ %42, %43 ]
  %98 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2
  %99 = bitcast %"class.std::__cxx11::basic_string"* %5 to %union.anon**
  store %union.anon* %98, %union.anon** %99, align 8, !tbaa !22, !alias.scope !84
  %100 = load i8*, i8** %96, align 8, !tbaa !2
  %101 = icmp eq i8* %100, %94
  br i1 %101, label %102, label %104

; <label>:102:                                    ; preds = %93
  %103 = bitcast %union.anon* %98 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %103, i8* nonnull %94, i64 16, i32 1, i1 false) #2
  br label %109

; <label>:104:                                    ; preds = %93
  %105 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  store i8* %100, i8** %105, align 8, !tbaa !2, !alias.scope !84
  %106 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %97, i64 0, i32 2, i32 0
  %107 = load i64, i64* %106, align 8, !tbaa !10
  %108 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2, i32 0
  store i64 %107, i64* %108, align 8, !tbaa !10, !alias.scope !84
  br label %109

; <label>:109:                                    ; preds = %104, %102
  %110 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %97, i64 0, i32 1
  %111 = load i64, i64* %110, align 8, !tbaa !23
  %112 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 1
  store i64 %111, i64* %112, align 8, !tbaa !23, !alias.scope !84
  %113 = bitcast %"class.std::__cxx11::basic_string"* %97 to %union.anon**
  store %union.anon* %95, %union.anon** %113, align 8, !tbaa !2
  store i64 0, i64* %110, align 8, !tbaa !23
  store i8 0, i8* %94, align 1, !tbaa !10
  invoke void @_ZNSt13runtime_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::runtime_error"* %8, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %5)
          to label %114 unwind label %145

; <label>:114:                                    ; preds = %109
  %115 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %116 = load i8*, i8** %115, align 8, !tbaa !2
  %117 = bitcast %union.anon* %98 to i8*
  %118 = icmp eq i8* %116, %117
  br i1 %118, label %120, label %119

; <label>:119:                                    ; preds = %114
  call void @_ZdlPv(i8* %116) #2
  br label %120

; <label>:120:                                    ; preds = %114, %119
  %121 = load i8*, i8** %31, align 8, !tbaa !2
  %122 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %123 = bitcast %union.anon* %122 to i8*
  %124 = icmp eq i8* %121, %123
  br i1 %124, label %126, label %125

; <label>:125:                                    ; preds = %120
  call void @_ZdlPv(i8* %121) #2
  br label %126

; <label>:126:                                    ; preds = %120, %125
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #2
  %127 = load i8*, i8** %22, align 8, !tbaa !2
  %128 = icmp eq i8* %127, %25
  br i1 %128, label %130, label %129

; <label>:129:                                    ; preds = %126
  call void @_ZdlPv(i8* %127) #2
  br label %130

; <label>:130:                                    ; preds = %126, %129
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %10) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %9) #2
  %131 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 0, i32 0, i32 0
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTVSt12system_error, i64 0, inrange i32 0, i64 2) to i32 (...)**), i32 (...)*** %131, align 8, !tbaa !79
  %132 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 1, i32 0
  store i32 %1, i32* %132, align 8
  %133 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 1, i32 1
  store %"class.std::_V2::error_category"* %2, %"class.std::_V2::error_category"** %133, align 8
  ret void

; <label>:134:                                    ; preds = %4
  %135 = landingpad { i8*, i32 }
          cleanup
  %136 = extractvalue { i8*, i32 } %135, 0
  %137 = extractvalue { i8*, i32 } %135, 1
  %138 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  %139 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %140 = bitcast %union.anon* %139 to i8*
  br label %162

; <label>:141:                                    ; preds = %59, %57, %41
  %142 = landingpad { i8*, i32 }
          cleanup
  %143 = extractvalue { i8*, i32 } %142, 0
  %144 = extractvalue { i8*, i32 } %142, 1
  br label %154

; <label>:145:                                    ; preds = %109
  %146 = landingpad { i8*, i32 }
          cleanup
  %147 = extractvalue { i8*, i32 } %146, 0
  %148 = extractvalue { i8*, i32 } %146, 1
  %149 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %150 = load i8*, i8** %149, align 8, !tbaa !2
  %151 = bitcast %union.anon* %98 to i8*
  %152 = icmp eq i8* %150, %151
  br i1 %152, label %154, label %153

; <label>:153:                                    ; preds = %145
  call void @_ZdlPv(i8* %150) #2
  br label %154

; <label>:154:                                    ; preds = %153, %145, %141
  %155 = phi i8* [ %143, %141 ], [ %147, %145 ], [ %147, %153 ]
  %156 = phi i32 [ %144, %141 ], [ %148, %145 ], [ %148, %153 ]
  %157 = load i8*, i8** %31, align 8, !tbaa !2
  %158 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %159 = bitcast %union.anon* %158 to i8*
  %160 = icmp eq i8* %157, %159
  br i1 %160, label %162, label %161

; <label>:161:                                    ; preds = %154
  call void @_ZdlPv(i8* %157) #2
  br label %162

; <label>:162:                                    ; preds = %161, %154, %134
  %163 = phi i8* [ %25, %161 ], [ %25, %154 ], [ %140, %134 ]
  %164 = phi i8** [ %22, %161 ], [ %22, %154 ], [ %138, %134 ]
  %165 = phi i8* [ %155, %161 ], [ %155, %154 ], [ %136, %134 ]
  %166 = phi i32 [ %156, %161 ], [ %156, %154 ], [ %137, %134 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #2
  %167 = load i8*, i8** %164, align 8, !tbaa !2
  %168 = icmp eq i8* %167, %163
  br i1 %168, label %170, label %169

; <label>:169:                                    ; preds = %162
  call void @_ZdlPv(i8* %167) #2
  br label %170

; <label>:170:                                    ; preds = %162, %169
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %10) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %9) #2
  %171 = insertvalue { i8*, i32 } undef, i8* %165, 0
  %172 = insertvalue { i8*, i32 } %171, i32 %166, 1
  resume { i8*, i32 } %172
}

; Function Attrs: inlinehint uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv(%"class.std::__cxx11::basic_string"* noalias sret, %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*) local_unnamed_addr #13 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__cxx11::basic_string", align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  %5 = alloca %"class.std::__cxx11::basic_string", align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = alloca %"class.std::__cxx11::basic_string", align 8
  %9 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %10 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %9, %union.anon** %10, align 8, !tbaa !22
  %11 = bitcast %union.anon* %9 to i8*
  %12 = invoke i8* @_Znwm(i64 19)
          to label %13 unwind label %187

; <label>:13:                                     ; preds = %2
  %14 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %12, i8** %14, align 8, !tbaa !2
  %15 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 18, i64* %15, align 8, !tbaa !10
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %12, i8* nonnull getelementptr inbounds ([19 x i8], [19 x i8]* @.str.23, i64 0, i64 0), i64 18, i32 1, i1 false) #2
  %16 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 18, i64* %16, align 8, !tbaa !23
  %17 = getelementptr inbounds i8, i8* %12, i64 18
  store i8 0, i8* %17, align 1, !tbaa !10
  %18 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 0, i32 0
  %19 = tail call i8* @_ZNKSt13runtime_error4whatEv(%"class.std::runtime_error"* %18) #2
  %20 = tail call i64 @strlen(i8* %19) #2
  %21 = load i64, i64* %16, align 8, !tbaa !23
  %22 = sub i64 9223372036854775807, %21
  %23 = icmp ult i64 %22, %20
  br i1 %23, label %24, label %26

; <label>:24:                                     ; preds = %13
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i64 0, i64 0)) #17
          to label %25 unwind label %191

; <label>:25:                                     ; preds = %24
  unreachable

; <label>:26:                                     ; preds = %13
  %27 = add i64 %21, %20
  %28 = load i8*, i8** %14, align 8, !tbaa !2
  %29 = icmp eq i8* %28, %11
  %30 = load i64, i64* %15, align 8
  %31 = select i1 %29, i64 15, i64 %30
  %32 = icmp ugt i64 %27, %31
  br i1 %32, label %41, label %33

; <label>:33:                                     ; preds = %26
  %34 = icmp eq i64 %20, 0
  br i1 %34, label %42, label %35

; <label>:35:                                     ; preds = %33
  %36 = getelementptr inbounds i8, i8* %28, i64 %21
  %37 = icmp eq i64 %20, 1
  br i1 %37, label %38, label %40

; <label>:38:                                     ; preds = %35
  %39 = load i8, i8* %19, align 1, !tbaa !10
  store i8 %39, i8* %36, align 1, !tbaa !10
  br label %42

; <label>:40:                                     ; preds = %35
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %36, i8* %19, i64 %20, i32 1, i1 false) #2
  br label %42

; <label>:41:                                     ; preds = %26
  invoke void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i64 %21, i64 0, i8* %19, i64 %20)
          to label %42 unwind label %191

; <label>:42:                                     ; preds = %40, %38, %33, %41
  store i64 %27, i64* %16, align 8, !tbaa !23
  %43 = load i8*, i8** %14, align 8, !tbaa !2
  %44 = getelementptr inbounds i8, i8* %43, i64 %27
  store i8 0, i8* %44, align 1, !tbaa !10
  %45 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 1, i32 0, i32 1
  %46 = load i64, i64* %45, align 8, !tbaa !23
  %47 = icmp eq i64 %46, 0
  br i1 %47, label %234, label %48

; <label>:48:                                     ; preds = %42
  %49 = bitcast %"class.std::__cxx11::basic_string"* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %49) #2
  %50 = bitcast %"class.std::__cxx11::basic_string"* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %50) #2
  %51 = bitcast %"class.std::__cxx11::basic_string"* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %51) #2
  %52 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 1, i32 0, i32 0, i32 0
  %53 = load i8*, i8** %52, align 8, !tbaa !2, !noalias !87
  %54 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2
  %55 = bitcast %"class.std::__cxx11::basic_string"* %5 to %union.anon**
  store %union.anon* %54, %union.anon** %55, align 8, !tbaa !22, !alias.scope !87
  %56 = icmp ugt i64 %46, 15
  %57 = bitcast %union.anon* %54 to i8*
  br i1 %56, label %58, label %68

; <label>:58:                                     ; preds = %48
  %59 = icmp slt i64 %46, 0
  br i1 %59, label %60, label %62

; <label>:60:                                     ; preds = %58
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %61 unwind label %195

; <label>:61:                                     ; preds = %60
  unreachable

; <label>:62:                                     ; preds = %58
  %63 = add i64 %46, 1
  %64 = invoke i8* @_Znwm(i64 %63)
          to label %65 unwind label %195

; <label>:65:                                     ; preds = %62
  %66 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  store i8* %64, i8** %66, align 8, !tbaa !2, !alias.scope !87
  %67 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2, i32 0
  store i64 %46, i64* %67, align 8, !tbaa !10, !alias.scope !87
  br label %72

; <label>:68:                                     ; preds = %48
  %69 = icmp eq i64 %46, 1
  br i1 %69, label %70, label %72

; <label>:70:                                     ; preds = %68
  %71 = load i8, i8* %53, align 1, !tbaa !10
  store i8 %71, i8* %57, align 8, !tbaa !10
  br label %74

; <label>:72:                                     ; preds = %65, %68
  %73 = phi i8* [ %64, %65 ], [ %57, %68 ]
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %73, i8* %53, i64 %46, i32 1, i1 false) #2
  br label %74

; <label>:74:                                     ; preds = %72, %70
  %75 = phi i8* [ %73, %72 ], [ %57, %70 ]
  %76 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 1
  store i64 %46, i64* %76, align 8, !tbaa !23, !alias.scope !87
  %77 = getelementptr inbounds i8, i8* %75, i64 %46
  store i8 0, i8* %77, align 1, !tbaa !10
  %78 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %5, i64 0, i64 0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0), i64 2)
          to label %79 unwind label %199

; <label>:79:                                     ; preds = %74
  %80 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2
  %81 = bitcast %"class.std::__cxx11::basic_string"* %4 to %union.anon**
  store %union.anon* %80, %union.anon** %81, align 8, !tbaa !22, !alias.scope !92
  %82 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %78, i64 0, i32 0, i32 0
  %83 = load i8*, i8** %82, align 8, !tbaa !2
  %84 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %78, i64 0, i32 2
  %85 = bitcast %union.anon* %84 to i8*
  %86 = icmp eq i8* %83, %85
  br i1 %86, label %87, label %89

; <label>:87:                                     ; preds = %79
  %88 = bitcast %union.anon* %80 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %88, i8* nonnull %83, i64 16, i32 1, i1 false) #2
  br label %94

; <label>:89:                                     ; preds = %79
  %90 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  store i8* %83, i8** %90, align 8, !tbaa !2, !alias.scope !92
  %91 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %78, i64 0, i32 2, i32 0
  %92 = load i64, i64* %91, align 8, !tbaa !10
  %93 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2, i32 0
  store i64 %92, i64* %93, align 8, !tbaa !10, !alias.scope !92
  br label %94

; <label>:94:                                     ; preds = %89, %87
  %95 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %78, i64 0, i32 1
  %96 = load i64, i64* %95, align 8, !tbaa !23
  %97 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 1
  store i64 %96, i64* %97, align 8, !tbaa !23, !alias.scope !92
  %98 = bitcast %"class.std::__cxx11::basic_string"* %78 to %union.anon**
  store %union.anon* %84, %union.anon** %98, align 8, !tbaa !2
  store i64 0, i64* %95, align 8, !tbaa !23
  store i8 0, i8* %85, align 1, !tbaa !10
  %99 = load i64, i64* %97, align 8, !tbaa !23, !noalias !95
  %100 = icmp eq i64 %99, 9223372036854775807
  br i1 %100, label %101, label %103

; <label>:101:                                    ; preds = %94
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.25, i64 0, i64 0)) #17
          to label %102 unwind label %203

; <label>:102:                                    ; preds = %101
  unreachable

; <label>:103:                                    ; preds = %94
  %104 = add i64 %99, 1
  %105 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  %106 = load i8*, i8** %105, align 8, !tbaa !2, !noalias !95
  %107 = bitcast %union.anon* %80 to i8*
  %108 = icmp eq i8* %106, %107
  %109 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 2, i32 0
  %110 = load i64, i64* %109, align 8, !noalias !95
  %111 = select i1 %108, i64 15, i64 %110
  %112 = icmp ugt i64 %104, %111
  br i1 %112, label %113, label %134

; <label>:113:                                    ; preds = %103
  %114 = icmp slt i64 %104, 0
  br i1 %114, label %115, label %117

; <label>:115:                                    ; preds = %113
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %116 unwind label %203

; <label>:116:                                    ; preds = %115
  unreachable

; <label>:117:                                    ; preds = %113
  %118 = shl i64 %111, 1
  %119 = icmp ult i64 %104, %118
  %120 = icmp ult i64 %118, 9223372036854775807
  %121 = select i1 %120, i64 %118, i64 9223372036854775807
  %122 = select i1 %119, i64 %121, i64 %104
  %123 = add i64 %122, 1
  %124 = invoke i8* @_Znwm(i64 %123)
          to label %125 unwind label %203

; <label>:125:                                    ; preds = %117
  %126 = load i8*, i8** %105, align 8, !tbaa !2, !noalias !95
  switch i64 %99, label %129 [
    i64 0, label %130
    i64 1, label %127
  ]

; <label>:127:                                    ; preds = %125
  %128 = load i8, i8* %126, align 1, !tbaa !10
  store i8 %128, i8* %124, align 1, !tbaa !10, !noalias !95
  br label %130

; <label>:129:                                    ; preds = %125
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %124, i8* %126, i64 %99, i32 1, i1 false) #2
  br label %130

; <label>:130:                                    ; preds = %129, %127, %125
  %131 = icmp eq i8* %126, %107
  br i1 %131, label %133, label %132

; <label>:132:                                    ; preds = %130
  call void @_ZdlPv(i8* %126) #2
  br label %133

; <label>:133:                                    ; preds = %132, %130
  store i8* %124, i8** %105, align 8, !tbaa !2, !noalias !95
  store i64 %122, i64* %109, align 8, !tbaa !10, !noalias !95
  br label %134

; <label>:134:                                    ; preds = %133, %103
  %135 = phi i8* [ %106, %103 ], [ %124, %133 ]
  %136 = getelementptr inbounds i8, i8* %135, i64 %99
  store i8 93, i8* %136, align 1, !tbaa !10, !noalias !95
  store i64 %104, i64* %97, align 8, !tbaa !23, !noalias !95
  %137 = load i8*, i8** %105, align 8, !tbaa !2, !noalias !95
  %138 = getelementptr inbounds i8, i8* %137, i64 %104
  store i8 0, i8* %138, align 1, !tbaa !10, !noalias !95
  %139 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 2
  %140 = bitcast %"class.std::__cxx11::basic_string"* %3 to %union.anon**
  store %union.anon* %139, %union.anon** %140, align 8, !tbaa !22, !alias.scope !95
  %141 = load i8*, i8** %105, align 8, !tbaa !2, !noalias !95
  %142 = icmp eq i8* %141, %107
  %143 = bitcast %union.anon* %139 to i8*
  br i1 %142, label %144, label %146

; <label>:144:                                    ; preds = %134
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %143, i8* nonnull %107, i64 16, i32 8, i1 false) #2
  %145 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 0, i32 0
  br label %150

; <label>:146:                                    ; preds = %134
  %147 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 0, i32 0
  store i8* %141, i8** %147, align 8, !tbaa !2, !alias.scope !95
  %148 = load i64, i64* %109, align 8, !tbaa !10, !noalias !95
  %149 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 2, i32 0
  store i64 %148, i64* %149, align 8, !tbaa !10, !alias.scope !95
  br label %150

; <label>:150:                                    ; preds = %146, %144
  %151 = phi i8** [ %147, %146 ], [ %145, %144 ]
  %152 = phi i8* [ %141, %146 ], [ %143, %144 ]
  %153 = load i64, i64* %97, align 8, !tbaa !23, !noalias !95
  %154 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %3, i64 0, i32 1
  store i64 %153, i64* %154, align 8, !tbaa !23, !alias.scope !95
  store %union.anon* %80, %union.anon** %81, align 8, !tbaa !2, !noalias !95
  store i64 0, i64* %97, align 8, !tbaa !23, !noalias !95
  store i8 0, i8* %107, align 8, !tbaa !10, !noalias !95
  %155 = load i64, i64* %16, align 8, !tbaa !23
  %156 = add i64 %155, %153
  %157 = load i8*, i8** %14, align 8, !tbaa !2
  %158 = icmp eq i8* %157, %11
  %159 = load i64, i64* %15, align 8
  %160 = select i1 %158, i64 15, i64 %159
  %161 = icmp ugt i64 %156, %160
  br i1 %161, label %170, label %162

; <label>:162:                                    ; preds = %150
  %163 = icmp eq i64 %153, 0
  br i1 %163, label %171, label %164

; <label>:164:                                    ; preds = %162
  %165 = getelementptr inbounds i8, i8* %157, i64 %155
  %166 = icmp eq i64 %153, 1
  br i1 %166, label %167, label %169

; <label>:167:                                    ; preds = %164
  %168 = load i8, i8* %152, align 1, !tbaa !10
  store i8 %168, i8* %165, align 1, !tbaa !10
  br label %171

; <label>:169:                                    ; preds = %164
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %165, i8* %152, i64 %153, i32 1, i1 false) #2
  br label %171

; <label>:170:                                    ; preds = %150
  invoke void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i64 %155, i64 0, i8* %152, i64 %153)
          to label %171 unwind label %209

; <label>:171:                                    ; preds = %169, %167, %162, %170
  store i64 %156, i64* %16, align 8, !tbaa !23
  %172 = load i8*, i8** %14, align 8, !tbaa !2
  %173 = getelementptr inbounds i8, i8* %172, i64 %156
  store i8 0, i8* %173, align 1, !tbaa !10
  %174 = load i8*, i8** %151, align 8, !tbaa !2
  %175 = icmp eq i8* %174, %143
  br i1 %175, label %177, label %176

; <label>:176:                                    ; preds = %171
  call void @_ZdlPv(i8* %174) #2
  br label %177

; <label>:177:                                    ; preds = %171, %176
  %178 = load i8*, i8** %105, align 8, !tbaa !2
  %179 = icmp eq i8* %178, %107
  br i1 %179, label %181, label %180

; <label>:180:                                    ; preds = %177
  call void @_ZdlPv(i8* %178) #2
  br label %181

; <label>:181:                                    ; preds = %177, %180
  %182 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %183 = load i8*, i8** %182, align 8, !tbaa !2
  %184 = icmp eq i8* %183, %57
  br i1 %184, label %186, label %185

; <label>:185:                                    ; preds = %181
  call void @_ZdlPv(i8* %183) #2
  br label %186

; <label>:186:                                    ; preds = %181, %185
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %51) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %50) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %49) #2
  br label %234

; <label>:187:                                    ; preds = %2
  %188 = landingpad { i8*, i32 }
          cleanup
  %189 = extractvalue { i8*, i32 } %188, 0
  %190 = extractvalue { i8*, i32 } %188, 1
  br label %423

; <label>:191:                                    ; preds = %41, %24
  %192 = landingpad { i8*, i32 }
          cleanup
  %193 = extractvalue { i8*, i32 } %192, 0
  %194 = extractvalue { i8*, i32 } %192, 1
  br label %417

; <label>:195:                                    ; preds = %62, %60
  %196 = landingpad { i8*, i32 }
          cleanup
  %197 = extractvalue { i8*, i32 } %196, 0
  %198 = extractvalue { i8*, i32 } %196, 1
  br label %231

; <label>:199:                                    ; preds = %74
  %200 = landingpad { i8*, i32 }
          cleanup
  %201 = extractvalue { i8*, i32 } %200, 0
  %202 = extractvalue { i8*, i32 } %200, 1
  br label %224

; <label>:203:                                    ; preds = %117, %115, %101
  %204 = landingpad { i8*, i32 }
          cleanup
  %205 = extractvalue { i8*, i32 } %204, 0
  %206 = extractvalue { i8*, i32 } %204, 1
  %207 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %4, i64 0, i32 0, i32 0
  %208 = bitcast %union.anon* %80 to i8*
  br label %216

; <label>:209:                                    ; preds = %170
  %210 = landingpad { i8*, i32 }
          cleanup
  %211 = extractvalue { i8*, i32 } %210, 0
  %212 = extractvalue { i8*, i32 } %210, 1
  %213 = load i8*, i8** %151, align 8, !tbaa !2
  %214 = icmp eq i8* %213, %143
  br i1 %214, label %216, label %215

; <label>:215:                                    ; preds = %209
  call void @_ZdlPv(i8* %213) #2
  br label %216

; <label>:216:                                    ; preds = %215, %209, %203
  %217 = phi i8* [ %107, %215 ], [ %107, %209 ], [ %208, %203 ]
  %218 = phi i8** [ %105, %215 ], [ %105, %209 ], [ %207, %203 ]
  %219 = phi i8* [ %211, %215 ], [ %211, %209 ], [ %205, %203 ]
  %220 = phi i32 [ %212, %215 ], [ %212, %209 ], [ %206, %203 ]
  %221 = load i8*, i8** %218, align 8, !tbaa !2
  %222 = icmp eq i8* %221, %217
  br i1 %222, label %224, label %223

; <label>:223:                                    ; preds = %216
  call void @_ZdlPv(i8* %221) #2
  br label %224

; <label>:224:                                    ; preds = %223, %216, %199
  %225 = phi i8* [ %201, %199 ], [ %219, %216 ], [ %219, %223 ]
  %226 = phi i32 [ %202, %199 ], [ %220, %216 ], [ %220, %223 ]
  %227 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %228 = load i8*, i8** %227, align 8, !tbaa !2
  %229 = icmp eq i8* %228, %57
  br i1 %229, label %231, label %230

; <label>:230:                                    ; preds = %224
  call void @_ZdlPv(i8* %228) #2
  br label %231

; <label>:231:                                    ; preds = %230, %224, %195
  %232 = phi i8* [ %197, %195 ], [ %225, %224 ], [ %225, %230 ]
  %233 = phi i32 [ %198, %195 ], [ %226, %224 ], [ %226, %230 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %51) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %50) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %49) #2
  br label %417

; <label>:234:                                    ; preds = %186, %42
  %235 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 2, i32 0, i32 1
  %236 = load i64, i64* %235, align 8, !tbaa !23
  %237 = icmp eq i64 %236, 0
  br i1 %237, label %416, label %238

; <label>:238:                                    ; preds = %234
  %239 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %239) #2
  %240 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %240) #2
  %241 = bitcast %"class.std::__cxx11::basic_string"* %8 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %241) #2
  %242 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 2, i32 0, i32 0, i32 0
  %243 = load i8*, i8** %242, align 8, !tbaa !2, !noalias !98
  %244 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2
  %245 = bitcast %"class.std::__cxx11::basic_string"* %8 to %union.anon**
  store %union.anon* %244, %union.anon** %245, align 8, !tbaa !22, !alias.scope !98
  %246 = icmp ugt i64 %236, 15
  %247 = bitcast %union.anon* %244 to i8*
  br i1 %246, label %248, label %258

; <label>:248:                                    ; preds = %238
  %249 = icmp slt i64 %236, 0
  br i1 %249, label %250, label %252

; <label>:250:                                    ; preds = %248
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %251 unwind label %377

; <label>:251:                                    ; preds = %250
  unreachable

; <label>:252:                                    ; preds = %248
  %253 = add i64 %236, 1
  %254 = invoke i8* @_Znwm(i64 %253)
          to label %255 unwind label %377

; <label>:255:                                    ; preds = %252
  %256 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  store i8* %254, i8** %256, align 8, !tbaa !2, !alias.scope !98
  %257 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2, i32 0
  store i64 %236, i64* %257, align 8, !tbaa !10, !alias.scope !98
  br label %262

; <label>:258:                                    ; preds = %238
  %259 = icmp eq i64 %236, 1
  br i1 %259, label %260, label %262

; <label>:260:                                    ; preds = %258
  %261 = load i8, i8* %243, align 1, !tbaa !10
  store i8 %261, i8* %247, align 8, !tbaa !10
  br label %264

; <label>:262:                                    ; preds = %255, %258
  %263 = phi i8* [ %254, %255 ], [ %247, %258 ]
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %263, i8* %243, i64 %236, i32 1, i1 false) #2
  br label %264

; <label>:264:                                    ; preds = %262, %260
  %265 = phi i8* [ %263, %262 ], [ %247, %260 ]
  %266 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 1
  store i64 %236, i64* %266, align 8, !tbaa !23, !alias.scope !98
  %267 = getelementptr inbounds i8, i8* %265, i64 %236
  store i8 0, i8* %267, align 1, !tbaa !10
  %268 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %8, i64 0, i64 0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.24, i64 0, i64 0), i64 2)
          to label %269 unwind label %381

; <label>:269:                                    ; preds = %264
  %270 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %271 = bitcast %"class.std::__cxx11::basic_string"* %7 to %union.anon**
  store %union.anon* %270, %union.anon** %271, align 8, !tbaa !22, !alias.scope !103
  %272 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %268, i64 0, i32 0, i32 0
  %273 = load i8*, i8** %272, align 8, !tbaa !2
  %274 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %268, i64 0, i32 2
  %275 = bitcast %union.anon* %274 to i8*
  %276 = icmp eq i8* %273, %275
  br i1 %276, label %277, label %279

; <label>:277:                                    ; preds = %269
  %278 = bitcast %union.anon* %270 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %278, i8* nonnull %273, i64 16, i32 1, i1 false) #2
  br label %284

; <label>:279:                                    ; preds = %269
  %280 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  store i8* %273, i8** %280, align 8, !tbaa !2, !alias.scope !103
  %281 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %268, i64 0, i32 2, i32 0
  %282 = load i64, i64* %281, align 8, !tbaa !10
  %283 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  store i64 %282, i64* %283, align 8, !tbaa !10, !alias.scope !103
  br label %284

; <label>:284:                                    ; preds = %279, %277
  %285 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %268, i64 0, i32 1
  %286 = load i64, i64* %285, align 8, !tbaa !23
  %287 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 1
  store i64 %286, i64* %287, align 8, !tbaa !23, !alias.scope !103
  %288 = bitcast %"class.std::__cxx11::basic_string"* %268 to %union.anon**
  store %union.anon* %274, %union.anon** %288, align 8, !tbaa !2
  store i64 0, i64* %285, align 8, !tbaa !23
  store i8 0, i8* %275, align 1, !tbaa !10
  %289 = load i64, i64* %287, align 8, !tbaa !23, !noalias !106
  %290 = icmp eq i64 %289, 9223372036854775807
  br i1 %290, label %291, label %293

; <label>:291:                                    ; preds = %284
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.25, i64 0, i64 0)) #17
          to label %292 unwind label %385

; <label>:292:                                    ; preds = %291
  unreachable

; <label>:293:                                    ; preds = %284
  %294 = add i64 %289, 1
  %295 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %296 = load i8*, i8** %295, align 8, !tbaa !2, !noalias !106
  %297 = bitcast %union.anon* %270 to i8*
  %298 = icmp eq i8* %296, %297
  %299 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  %300 = load i64, i64* %299, align 8, !noalias !106
  %301 = select i1 %298, i64 15, i64 %300
  %302 = icmp ugt i64 %294, %301
  br i1 %302, label %303, label %324

; <label>:303:                                    ; preds = %293
  %304 = icmp slt i64 %294, 0
  br i1 %304, label %305, label %307

; <label>:305:                                    ; preds = %303
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
          to label %306 unwind label %385

; <label>:306:                                    ; preds = %305
  unreachable

; <label>:307:                                    ; preds = %303
  %308 = shl i64 %301, 1
  %309 = icmp ult i64 %294, %308
  %310 = icmp ult i64 %308, 9223372036854775807
  %311 = select i1 %310, i64 %308, i64 9223372036854775807
  %312 = select i1 %309, i64 %311, i64 %294
  %313 = add i64 %312, 1
  %314 = invoke i8* @_Znwm(i64 %313)
          to label %315 unwind label %385

; <label>:315:                                    ; preds = %307
  %316 = load i8*, i8** %295, align 8, !tbaa !2, !noalias !106
  switch i64 %289, label %319 [
    i64 0, label %320
    i64 1, label %317
  ]

; <label>:317:                                    ; preds = %315
  %318 = load i8, i8* %316, align 1, !tbaa !10
  store i8 %318, i8* %314, align 1, !tbaa !10, !noalias !106
  br label %320

; <label>:319:                                    ; preds = %315
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %314, i8* %316, i64 %289, i32 1, i1 false) #2
  br label %320

; <label>:320:                                    ; preds = %319, %317, %315
  %321 = icmp eq i8* %316, %297
  br i1 %321, label %323, label %322

; <label>:322:                                    ; preds = %320
  call void @_ZdlPv(i8* %316) #2
  br label %323

; <label>:323:                                    ; preds = %322, %320
  store i8* %314, i8** %295, align 8, !tbaa !2, !noalias !106
  store i64 %312, i64* %299, align 8, !tbaa !10, !noalias !106
  br label %324

; <label>:324:                                    ; preds = %323, %293
  %325 = phi i8* [ %296, %293 ], [ %314, %323 ]
  %326 = getelementptr inbounds i8, i8* %325, i64 %289
  store i8 93, i8* %326, align 1, !tbaa !10, !noalias !106
  store i64 %294, i64* %287, align 8, !tbaa !23, !noalias !106
  %327 = load i8*, i8** %295, align 8, !tbaa !2, !noalias !106
  %328 = getelementptr inbounds i8, i8* %327, i64 %294
  store i8 0, i8* %328, align 1, !tbaa !10, !noalias !106
  %329 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %330 = bitcast %"class.std::__cxx11::basic_string"* %6 to %union.anon**
  store %union.anon* %329, %union.anon** %330, align 8, !tbaa !22, !alias.scope !106
  %331 = load i8*, i8** %295, align 8, !tbaa !2, !noalias !106
  %332 = icmp eq i8* %331, %297
  %333 = bitcast %union.anon* %329 to i8*
  br i1 %332, label %334, label %336

; <label>:334:                                    ; preds = %324
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %333, i8* nonnull %297, i64 16, i32 8, i1 false) #2
  %335 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  br label %340

; <label>:336:                                    ; preds = %324
  %337 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  store i8* %331, i8** %337, align 8, !tbaa !2, !alias.scope !106
  %338 = load i64, i64* %299, align 8, !tbaa !10, !noalias !106
  %339 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  store i64 %338, i64* %339, align 8, !tbaa !10, !alias.scope !106
  br label %340

; <label>:340:                                    ; preds = %336, %334
  %341 = phi i8** [ %337, %336 ], [ %335, %334 ]
  %342 = phi i8* [ %331, %336 ], [ %333, %334 ]
  %343 = load i64, i64* %287, align 8, !tbaa !23, !noalias !106
  %344 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  store i64 %343, i64* %344, align 8, !tbaa !23, !alias.scope !106
  store %union.anon* %270, %union.anon** %271, align 8, !tbaa !2, !noalias !106
  store i64 0, i64* %287, align 8, !tbaa !23, !noalias !106
  store i8 0, i8* %297, align 8, !tbaa !10, !noalias !106
  %345 = load i64, i64* %16, align 8, !tbaa !23
  %346 = add i64 %345, %343
  %347 = load i8*, i8** %14, align 8, !tbaa !2
  %348 = icmp eq i8* %347, %11
  %349 = load i64, i64* %15, align 8
  %350 = select i1 %348, i64 15, i64 %349
  %351 = icmp ugt i64 %346, %350
  br i1 %351, label %360, label %352

; <label>:352:                                    ; preds = %340
  %353 = icmp eq i64 %343, 0
  br i1 %353, label %361, label %354

; <label>:354:                                    ; preds = %352
  %355 = getelementptr inbounds i8, i8* %347, i64 %345
  %356 = icmp eq i64 %343, 1
  br i1 %356, label %357, label %359

; <label>:357:                                    ; preds = %354
  %358 = load i8, i8* %342, align 1, !tbaa !10
  store i8 %358, i8* %355, align 1, !tbaa !10
  br label %361

; <label>:359:                                    ; preds = %354
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %355, i8* %342, i64 %343, i32 1, i1 false) #2
  br label %361

; <label>:360:                                    ; preds = %340
  invoke void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i64 %345, i64 0, i8* %342, i64 %343)
          to label %361 unwind label %391

; <label>:361:                                    ; preds = %359, %357, %352, %360
  store i64 %346, i64* %16, align 8, !tbaa !23
  %362 = load i8*, i8** %14, align 8, !tbaa !2
  %363 = getelementptr inbounds i8, i8* %362, i64 %346
  store i8 0, i8* %363, align 1, !tbaa !10
  %364 = load i8*, i8** %341, align 8, !tbaa !2
  %365 = icmp eq i8* %364, %333
  br i1 %365, label %367, label %366

; <label>:366:                                    ; preds = %361
  call void @_ZdlPv(i8* %364) #2
  br label %367

; <label>:367:                                    ; preds = %361, %366
  %368 = load i8*, i8** %295, align 8, !tbaa !2
  %369 = icmp eq i8* %368, %297
  br i1 %369, label %371, label %370

; <label>:370:                                    ; preds = %367
  call void @_ZdlPv(i8* %368) #2
  br label %371

; <label>:371:                                    ; preds = %367, %370
  %372 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %373 = load i8*, i8** %372, align 8, !tbaa !2
  %374 = icmp eq i8* %373, %247
  br i1 %374, label %376, label %375

; <label>:375:                                    ; preds = %371
  call void @_ZdlPv(i8* %373) #2
  br label %376

; <label>:376:                                    ; preds = %371, %375
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %241) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %240) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %239) #2
  br label %416

; <label>:377:                                    ; preds = %252, %250
  %378 = landingpad { i8*, i32 }
          cleanup
  %379 = extractvalue { i8*, i32 } %378, 0
  %380 = extractvalue { i8*, i32 } %378, 1
  br label %413

; <label>:381:                                    ; preds = %264
  %382 = landingpad { i8*, i32 }
          cleanup
  %383 = extractvalue { i8*, i32 } %382, 0
  %384 = extractvalue { i8*, i32 } %382, 1
  br label %406

; <label>:385:                                    ; preds = %307, %305, %291
  %386 = landingpad { i8*, i32 }
          cleanup
  %387 = extractvalue { i8*, i32 } %386, 0
  %388 = extractvalue { i8*, i32 } %386, 1
  %389 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %390 = bitcast %union.anon* %270 to i8*
  br label %398

; <label>:391:                                    ; preds = %360
  %392 = landingpad { i8*, i32 }
          cleanup
  %393 = extractvalue { i8*, i32 } %392, 0
  %394 = extractvalue { i8*, i32 } %392, 1
  %395 = load i8*, i8** %341, align 8, !tbaa !2
  %396 = icmp eq i8* %395, %333
  br i1 %396, label %398, label %397

; <label>:397:                                    ; preds = %391
  call void @_ZdlPv(i8* %395) #2
  br label %398

; <label>:398:                                    ; preds = %397, %391, %385
  %399 = phi i8* [ %297, %397 ], [ %297, %391 ], [ %390, %385 ]
  %400 = phi i8** [ %295, %397 ], [ %295, %391 ], [ %389, %385 ]
  %401 = phi i8* [ %393, %397 ], [ %393, %391 ], [ %387, %385 ]
  %402 = phi i32 [ %394, %397 ], [ %394, %391 ], [ %388, %385 ]
  %403 = load i8*, i8** %400, align 8, !tbaa !2
  %404 = icmp eq i8* %403, %399
  br i1 %404, label %406, label %405

; <label>:405:                                    ; preds = %398
  call void @_ZdlPv(i8* %403) #2
  br label %406

; <label>:406:                                    ; preds = %405, %398, %381
  %407 = phi i8* [ %383, %381 ], [ %401, %398 ], [ %401, %405 ]
  %408 = phi i32 [ %384, %381 ], [ %402, %398 ], [ %402, %405 ]
  %409 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %410 = load i8*, i8** %409, align 8, !tbaa !2
  %411 = icmp eq i8* %410, %247
  br i1 %411, label %413, label %412

; <label>:412:                                    ; preds = %406
  call void @_ZdlPv(i8* %410) #2
  br label %413

; <label>:413:                                    ; preds = %412, %406, %377
  %414 = phi i8* [ %379, %377 ], [ %407, %406 ], [ %407, %412 ]
  %415 = phi i32 [ %380, %377 ], [ %408, %406 ], [ %408, %412 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %241) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %240) #2
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %239) #2
  br label %417

; <label>:416:                                    ; preds = %234, %376
  ret void

; <label>:417:                                    ; preds = %413, %231, %191
  %418 = phi i8* [ %414, %413 ], [ %232, %231 ], [ %193, %191 ]
  %419 = phi i32 [ %415, %413 ], [ %233, %231 ], [ %194, %191 ]
  %420 = load i8*, i8** %14, align 8, !tbaa !2
  %421 = icmp eq i8* %420, %11
  br i1 %421, label %423, label %422

; <label>:422:                                    ; preds = %417
  call void @_ZdlPv(i8* %420) #2
  br label %423

; <label>:423:                                    ; preds = %422, %417, %187
  %424 = phi i8* [ %189, %187 ], [ %418, %417 ], [ %418, %422 ]
  %425 = phi i32 [ %190, %187 ], [ %419, %417 ], [ %419, %422 ]
  %426 = insertvalue { i8*, i32 } undef, i8* %424, 0
  %427 = insertvalue { i8*, i32 } %426, i32 %425, 1
  resume { i8*, i32 } %427
}

; Function Attrs: nounwind
declare void @_ZNSt12system_errorD2Ev(%"class.std::system_error"*) unnamed_addr #1

declare void @_ZNSt13runtime_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::runtime_error"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #0

; Function Attrs: nounwind
declare i8* @_ZNKSt13runtime_error4whatEv(%"class.std::runtime_error"*) unnamed_addr #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #5

declare i32 @openat(i32, i8*, i32, ...) local_unnamed_addr #0

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx114pathC2INSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES3_EERKT_(%"class.std::experimental::filesystem::v1::__cxx11::path"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %4 = load i8*, i8** %3, align 8, !tbaa !2
  %5 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  %6 = load i64, i64* %5, align 8, !tbaa !23
  %7 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2
  %8 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %0 to %union.anon**
  store %union.anon* %7, %union.anon** %8, align 8, !tbaa !22, !alias.scope !109
  %9 = icmp ne i8* %4, null
  %10 = icmp eq i64 %6, 0
  %11 = or i1 %9, %10
  br i1 %11, label %13, label %12

; <label>:12:                                     ; preds = %2
  tail call void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
  unreachable

; <label>:13:                                     ; preds = %2
  %14 = bitcast %union.anon* %7 to i8*
  %15 = icmp ugt i64 %6, 15
  br i1 %15, label %16, label %24

; <label>:16:                                     ; preds = %13
  %17 = icmp slt i64 %6, 0
  br i1 %17, label %18, label %19

; <label>:18:                                     ; preds = %16
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
  unreachable

; <label>:19:                                     ; preds = %16
  %20 = add i64 %6, 1
  %21 = tail call i8* @_Znwm(i64 %20)
  %22 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  store i8* %21, i8** %22, align 8, !tbaa !2, !alias.scope !109
  %23 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  store i64 %6, i64* %23, align 8, !tbaa !10, !alias.scope !109
  br label %24

; <label>:24:                                     ; preds = %19, %13
  %25 = phi i8* [ %21, %19 ], [ %14, %13 ]
  switch i64 %6, label %28 [
    i64 1, label %26
    i64 0, label %29
  ]

; <label>:26:                                     ; preds = %24
  %27 = load i8, i8* %4, align 1, !tbaa !10, !noalias !109
  store i8 %27, i8* %25, align 1, !tbaa !10
  br label %29

; <label>:28:                                     ; preds = %24
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %25, i8* %4, i64 %6, i32 1, i1 false) #2
  br label %29

; <label>:29:                                     ; preds = %24, %26, %28
  %30 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 1
  store i64 %6, i64* %30, align 8, !tbaa !23, !alias.scope !109
  %31 = getelementptr inbounds i8, i8* %25, i64 %6
  store i8 0, i8* %31, align 1, !tbaa !10
  %32 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 1
  %33 = bitcast %"class.std::vector"* %32 to i8*
  call void @llvm.memset.p0i8.i64(i8* nonnull %33, i8 0, i64 25, i32 8, i1 false)
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %0)
          to label %34 unwind label %35

; <label>:34:                                     ; preds = %29
  ret void

; <label>:35:                                     ; preds = %29
  %36 = landingpad { i8*, i32 }
          cleanup
  tail call void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"class.std::vector"* nonnull %32) #2
  %37 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  %38 = load i8*, i8** %37, align 8, !tbaa !2
  %39 = icmp eq i8* %38, %14
  br i1 %39, label %41, label %40

; <label>:40:                                     ; preds = %35
  tail call void @_ZdlPv(i8* %38) #2
  br label %41

; <label>:41:                                     ; preds = %35, %40
  resume { i8*, i32 } %36
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx114pathC2ERKS3_(%"class.std::experimental::filesystem::v1::__cxx11::path"*, %"class.std::experimental::filesystem::v1::__cxx11::path"* dereferenceable(64)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2
  %4 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %0 to %union.anon**
  store %union.anon* %3, %union.anon** %4, align 8, !tbaa !22
  %5 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %1, i64 0, i32 0, i32 0, i32 0
  %6 = load i8*, i8** %5, align 8, !tbaa !2
  %7 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %1, i64 0, i32 0, i32 1
  %8 = load i64, i64* %7, align 8, !tbaa !23
  %9 = icmp ne i8* %6, null
  %10 = icmp eq i64 %8, 0
  %11 = or i1 %9, %10
  br i1 %11, label %13, label %12

; <label>:12:                                     ; preds = %2
  tail call void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.9, i64 0, i64 0)) #17
  unreachable

; <label>:13:                                     ; preds = %2
  %14 = bitcast %union.anon* %3 to i8*
  %15 = icmp ugt i64 %8, 15
  br i1 %15, label %16, label %24

; <label>:16:                                     ; preds = %13
  %17 = icmp slt i64 %8, 0
  br i1 %17, label %18, label %19

; <label>:18:                                     ; preds = %16
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
  unreachable

; <label>:19:                                     ; preds = %16
  %20 = add i64 %8, 1
  %21 = tail call i8* @_Znwm(i64 %20)
  %22 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  store i8* %21, i8** %22, align 8, !tbaa !2
  %23 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  store i64 %8, i64* %23, align 8, !tbaa !10
  br label %24

; <label>:24:                                     ; preds = %19, %13
  %25 = phi i8* [ %21, %19 ], [ %14, %13 ]
  switch i64 %8, label %28 [
    i64 1, label %26
    i64 0, label %29
  ]

; <label>:26:                                     ; preds = %24
  %27 = load i8, i8* %6, align 1, !tbaa !10
  store i8 %27, i8* %25, align 1, !tbaa !10
  br label %29

; <label>:28:                                     ; preds = %24
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %25, i8* %6, i64 %8, i32 1, i1 false) #2
  br label %29

; <label>:29:                                     ; preds = %24, %26, %28
  %30 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 1
  store i64 %8, i64* %30, align 8, !tbaa !23
  %31 = getelementptr inbounds i8, i8* %25, i64 %8
  store i8 0, i8* %31, align 1, !tbaa !10
  %32 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 1
  %33 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %1, i64 0, i32 1
  invoke void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EEC2ERKS7_(%"class.std::vector"* nonnull %32, %"class.std::vector"* nonnull dereferenceable(24) %33)
          to label %34 unwind label %38

; <label>:34:                                     ; preds = %29
  %35 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 2
  %36 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %1, i64 0, i32 2
  %37 = load i8, i8* %36, align 8, !tbaa !114
  store i8 %37, i8* %35, align 8, !tbaa !114
  ret void

; <label>:38:                                     ; preds = %29
  %39 = landingpad { i8*, i32 }
          cleanup
  %40 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  %41 = load i8*, i8** %40, align 8, !tbaa !2
  %42 = icmp eq i8* %41, %14
  br i1 %42, label %44, label %43

; <label>:43:                                     ; preds = %38
  tail call void @_ZdlPv(i8* %41) #2
  br label %44

; <label>:44:                                     ; preds = %38, %43
  resume { i8*, i32 } %39
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EEC2ERKS7_(%"class.std::vector"*, %"class.std::vector"* dereferenceable(24)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %1, i64 0, i32 0, i32 0, i32 1
  %4 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %3 to i64*
  %5 = load i64, i64* %4, align 8, !tbaa !68
  %6 = bitcast %"class.std::vector"* %1 to i64*
  %7 = load i64, i64* %6, align 8, !tbaa !65
  %8 = sub i64 %5, %7
  %9 = sdiv exact i64 %8, 72
  %10 = bitcast %"class.std::vector"* %0 to i8*
  tail call void @llvm.memset.p0i8.i64(i8* %10, i8 0, i64 24, i32 8, i1 false) #2
  %11 = icmp eq i64 %8, 0
  br i1 %11, label %20, label %12

; <label>:12:                                     ; preds = %2
  %13 = icmp ugt i64 %9, 256204778801521550
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %12
  invoke void @_ZSt17__throw_bad_allocv() #17
          to label %15 unwind label %31

; <label>:15:                                     ; preds = %14
  unreachable

; <label>:16:                                     ; preds = %12
  %17 = invoke i8* @_Znwm(i64 %8)
          to label %18 unwind label %31

; <label>:18:                                     ; preds = %16
  %19 = bitcast i8* %17 to %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*
  br label %20

; <label>:20:                                     ; preds = %18, %2
  %21 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %19, %18 ], [ null, %2 ]
  %22 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %0, i64 0, i32 0, i32 0, i32 0
  store %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %21, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %22, align 8, !tbaa !65
  %23 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %0, i64 0, i32 0, i32 0, i32 1
  store %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %21, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %23, align 8, !tbaa !68
  %24 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %21, i64 %9
  %25 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %0, i64 0, i32 0, i32 0, i32 2
  store %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %24, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %25, align 8, !tbaa !118
  %26 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %1, i64 0, i32 0, i32 0, i32 0
  %27 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %26, align 8, !tbaa !65
  %28 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %3, align 8, !tbaa !68
  %29 = invoke %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* @_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPKNSt12experimental10filesystem2v17__cxx114path5_CmptESt6vectorIS9_SaIS9_EEEEPS9_EET0_T_SI_SH_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %27, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %28, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %21)
          to label %30 unwind label %35

; <label>:30:                                     ; preds = %20
  store %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %29, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %23, align 8, !tbaa !68
  ret void

; <label>:31:                                     ; preds = %16, %14
  %32 = landingpad { i8*, i32 }
          cleanup
  %33 = extractvalue { i8*, i32 } %32, 0
  %34 = extractvalue { i8*, i32 } %32, 1
  br label %43

; <label>:35:                                     ; preds = %20
  %36 = landingpad { i8*, i32 }
          cleanup
  %37 = extractvalue { i8*, i32 } %36, 0
  %38 = extractvalue { i8*, i32 } %36, 1
  %39 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %22, align 8, !tbaa !65
  %40 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %39, null
  br i1 %40, label %43, label %41

; <label>:41:                                     ; preds = %35
  %42 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %39 to i8*
  tail call void @_ZdlPv(i8* %42) #2
  br label %43

; <label>:43:                                     ; preds = %41, %35, %31
  %44 = phi i32 [ %34, %31 ], [ %38, %35 ], [ %38, %41 ]
  %45 = phi i8* [ %33, %31 ], [ %37, %35 ], [ %37, %41 ]
  %46 = insertvalue { i8*, i32 } undef, i8* %45, 0
  %47 = insertvalue { i8*, i32 } %46, i32 %44, 1
  resume { i8*, i32 } %47
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* @_ZNSt20__uninitialized_copyILb0EE13__uninit_copyIN9__gnu_cxx17__normal_iteratorIPKNSt12experimental10filesystem2v17__cxx114path5_CmptESt6vectorIS9_SaIS9_EEEEPS9_EET0_T_SI_SH_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*) local_unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %0, %1
  br i1 %4, label %37, label %5

; <label>:5:                                      ; preds = %3
  br label %6

; <label>:6:                                      ; preds = %5, %11
  %7 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %16, %11 ], [ %2, %5 ]
  %8 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %15, %11 ], [ %0, %5 ]
  %9 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %7 to %"class.std::experimental::filesystem::v1::__cxx11::path"*
  %10 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %8 to %"class.std::experimental::filesystem::v1::__cxx11::path"*
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114pathC2ERKS3_(%"class.std::experimental::filesystem::v1::__cxx11::path"* %9, %"class.std::experimental::filesystem::v1::__cxx11::path"* dereferenceable(64) %10)
          to label %11 unwind label %18

; <label>:11:                                     ; preds = %6
  %12 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %7, i64 0, i32 1
  %13 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %8, i64 0, i32 1
  %14 = load i64, i64* %13, align 8, !tbaa !119
  store i64 %14, i64* %12, align 8, !tbaa !119
  %15 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %8, i64 1
  %16 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %7, i64 1
  %17 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %15, %1
  br i1 %17, label %37, label %6

; <label>:18:                                     ; preds = %6
  %19 = landingpad { i8*, i32 }
          catch i8* null
  %20 = extractvalue { i8*, i32 } %19, 0
  %21 = tail call i8* @__cxa_begin_catch(i8* %20) #2
  %22 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %7, %2
  br i1 %22, label %36, label %23

; <label>:23:                                     ; preds = %18
  br label %24

; <label>:24:                                     ; preds = %23, %33
  %25 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %34, %33 ], [ %2, %23 ]
  %26 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %25, i64 0, i32 0, i32 1
  tail call void @_ZNSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"class.std::vector"* nonnull %26) #2
  %27 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %25, i64 0, i32 0, i32 0, i32 0, i32 0
  %28 = load i8*, i8** %27, align 8, !tbaa !2
  %29 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %25, i64 0, i32 0, i32 0, i32 2
  %30 = bitcast %union.anon* %29 to i8*
  %31 = icmp eq i8* %28, %30
  br i1 %31, label %33, label %32

; <label>:32:                                     ; preds = %24
  tail call void @_ZdlPv(i8* %28) #2
  br label %33

; <label>:33:                                     ; preds = %32, %24
  %34 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %25, i64 1
  %35 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %34, %7
  br i1 %35, label %36, label %24

; <label>:36:                                     ; preds = %33, %18
  invoke void @__cxa_rethrow() #17
          to label %45 unwind label %39

; <label>:37:                                     ; preds = %11, %3
  %38 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %2, %3 ], [ %16, %11 ]
  ret %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %38

; <label>:39:                                     ; preds = %36
  %40 = landingpad { i8*, i32 }
          cleanup
  invoke void @__cxa_end_catch()
          to label %41 unwind label %42

; <label>:41:                                     ; preds = %39
  resume { i8*, i32 } %40

; <label>:42:                                     ; preds = %39
  %43 = landingpad { i8*, i32 }
          catch i8* null
  %44 = extractvalue { i8*, i32 } %43, 0
  tail call void @__clang_call_terminate(i8* %44) #15
  unreachable

; <label>:45:                                     ; preds = %36
  unreachable
}

; Function Attrs: uwtable
define linkonce_odr dereferenceable(64) %"class.std::experimental::filesystem::v1::__cxx11::path"* @_ZNSt12experimental10filesystem2v17__cxx114path9_M_appendERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::experimental::filesystem::v1::__cxx11::path"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) local_unnamed_addr #4 comdat align 2 personality i32 (...)* @__gxx_personality_v0 {
  %3 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0
  %4 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 1
  %5 = load i64, i64* %4, align 8, !tbaa !23
  %6 = icmp eq i64 %5, 0
  br i1 %6, label %7, label %9

; <label>:7:                                      ; preds = %2
  %8 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  br label %72

; <label>:9:                                      ; preds = %2
  %10 = add i64 %5, -1
  %11 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  %12 = load i8*, i8** %11, align 8, !tbaa !2
  %13 = getelementptr inbounds i8, i8* %12, i64 %10
  %14 = load i8, i8* %13, align 1, !tbaa !10
  %15 = icmp eq i8 %14, 47
  br i1 %15, label %72, label %16

; <label>:16:                                     ; preds = %9
  %17 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  %18 = load i64, i64* %17, align 8, !tbaa !23
  %19 = icmp eq i64 %18, 0
  br i1 %19, label %72, label %20

; <label>:20:                                     ; preds = %16
  %21 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %22 = load i8*, i8** %21, align 8, !tbaa !2
  %23 = load i8, i8* %22, align 1, !tbaa !10
  %24 = icmp eq i8 %23, 47
  br i1 %24, label %72, label %25

; <label>:25:                                     ; preds = %20
  %26 = add i64 %5, 1
  %27 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2
  %28 = bitcast %union.anon* %27 to i8*
  %29 = icmp eq i8* %12, %28
  br i1 %29, label %33, label %30

; <label>:30:                                     ; preds = %25
  %31 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  %32 = load i64, i64* %31, align 8, !tbaa !10
  br label %33

; <label>:33:                                     ; preds = %30, %25
  %34 = phi i64 [ %32, %30 ], [ 15, %25 ]
  %35 = icmp ugt i64 %26, %34
  br i1 %35, label %36, label %66

; <label>:36:                                     ; preds = %33
  br i1 %29, label %40, label %37

; <label>:37:                                     ; preds = %36
  %38 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  %39 = load i64, i64* %38, align 8, !tbaa !10
  br label %40

; <label>:40:                                     ; preds = %37, %36
  %41 = phi i64 [ %39, %37 ], [ 15, %36 ]
  %42 = icmp slt i64 %26, 0
  br i1 %42, label %43, label %44

; <label>:43:                                     ; preds = %40
  tail call void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.10, i64 0, i64 0)) #17
  unreachable

; <label>:44:                                     ; preds = %40
  %45 = icmp ugt i64 %26, %41
  br i1 %45, label %46, label %52

; <label>:46:                                     ; preds = %44
  %47 = shl i64 %41, 1
  %48 = icmp ult i64 %26, %47
  br i1 %48, label %49, label %52

; <label>:49:                                     ; preds = %46
  %50 = icmp ult i64 %47, 9223372036854775807
  %51 = select i1 %50, i64 %47, i64 9223372036854775807
  br label %52

; <label>:52:                                     ; preds = %44, %46, %49
  %53 = phi i64 [ %51, %49 ], [ %26, %46 ], [ %26, %44 ]
  %54 = add i64 %53, 1
  %55 = tail call i8* @_Znwm(i64 %54)
  %56 = load i8*, i8** %11, align 8, !tbaa !2
  %57 = icmp eq i64 %5, 1
  br i1 %57, label %58, label %60

; <label>:58:                                     ; preds = %52
  %59 = load i8, i8* %56, align 1, !tbaa !10
  store i8 %59, i8* %55, align 1, !tbaa !10
  br label %61

; <label>:60:                                     ; preds = %52
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %55, i8* %56, i64 %5, i32 1, i1 false) #2
  br label %61

; <label>:61:                                     ; preds = %60, %58
  %62 = icmp eq i8* %56, %28
  br i1 %62, label %64, label %63

; <label>:63:                                     ; preds = %61
  tail call void @_ZdlPv(i8* %56) #2
  br label %64

; <label>:64:                                     ; preds = %61, %63
  store i8* %55, i8** %11, align 8, !tbaa !2
  %65 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  store i64 %53, i64* %65, align 8, !tbaa !10
  br label %66

; <label>:66:                                     ; preds = %33, %64
  %67 = phi i8* [ %55, %64 ], [ %12, %33 ]
  %68 = getelementptr inbounds i8, i8* %67, i64 %5
  store i8 47, i8* %68, align 1, !tbaa !10
  store i64 %26, i64* %4, align 8, !tbaa !23
  %69 = load i8*, i8** %11, align 8, !tbaa !2
  %70 = getelementptr inbounds i8, i8* %69, i64 %26
  store i8 0, i8* %70, align 1, !tbaa !10
  %71 = load i64, i64* %4, align 8, !tbaa !23
  br label %72

; <label>:72:                                     ; preds = %7, %66, %20, %16, %9
  %73 = phi i8** [ %8, %7 ], [ %11, %66 ], [ %11, %20 ], [ %11, %16 ], [ %11, %9 ]
  %74 = phi i64 [ 0, %7 ], [ %71, %66 ], [ %5, %20 ], [ %5, %16 ], [ %5, %9 ]
  %75 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %76 = load i8*, i8** %75, align 8, !tbaa !2
  %77 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  %78 = load i64, i64* %77, align 8, !tbaa !23
  %79 = add i64 %74, %78
  %80 = load i8*, i8** %73, align 8, !tbaa !2
  %81 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2
  %82 = bitcast %union.anon* %81 to i8*
  %83 = icmp eq i8* %80, %82
  br i1 %83, label %87, label %84

; <label>:84:                                     ; preds = %72
  %85 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  %86 = load i64, i64* %85, align 8, !tbaa !10
  br label %87

; <label>:87:                                     ; preds = %84, %72
  %88 = phi i64 [ %86, %84 ], [ 15, %72 ]
  %89 = icmp ugt i64 %79, %88
  br i1 %89, label %98, label %90

; <label>:90:                                     ; preds = %87
  %91 = icmp eq i64 %78, 0
  br i1 %91, label %99, label %92

; <label>:92:                                     ; preds = %90
  %93 = getelementptr inbounds i8, i8* %80, i64 %74
  %94 = icmp eq i64 %78, 1
  br i1 %94, label %95, label %97

; <label>:95:                                     ; preds = %92
  %96 = load i8, i8* %76, align 1, !tbaa !10
  store i8 %96, i8* %93, align 1, !tbaa !10
  br label %99

; <label>:97:                                     ; preds = %92
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* %93, i8* %76, i64 %78, i32 1, i1 false) #2
  br label %99

; <label>:98:                                     ; preds = %87
  tail call void @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %3, i64 %74, i64 0, i8* %76, i64 %78)
  br label %99

; <label>:99:                                     ; preds = %90, %95, %97, %98
  store i64 %79, i64* %4, align 8, !tbaa !23
  %100 = load i8*, i8** %73, align 8, !tbaa !2
  %101 = getelementptr inbounds i8, i8* %100, i64 %79
  store i8 0, i8* %101, align 1, !tbaa !10
  tail call void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %0)
  ret %"class.std::experimental::filesystem::v1::__cxx11::path"* %0
}

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_BranchCoverageRuntime.cpp() #4 section ".text.startup" personality i32 (...)* @__gxx_personality_v0 {
  tail call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* nonnull @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i64 0, i32 0), i8* nonnull @__dso_handle) #2
  store i64 0, i64* getelementptr inbounds (%"class.debug::Indentation", %"class.debug::Indentation"* @_ZN5debug11indentationE, i64 0, i32 0), align 8, !tbaa !121
  store %union.anon* getelementptr inbounds (%"class.debug::Indentation", %"class.debug::Indentation"* @_ZN5debug11indentationE, i64 0, i32 1, i32 2), %union.anon** bitcast (%"class.std::__cxx11::basic_string"* getelementptr inbounds (%"class.debug::Indentation", %"class.debug::Indentation"* @_ZN5debug11indentationE, i64 0, i32 1) to %union.anon**), align 8, !tbaa !22
  store i64 0, i64* getelementptr inbounds (%"class.debug::Indentation", %"class.debug::Indentation"* @_ZN5debug11indentationE, i64 0, i32 1, i32 1), align 8, !tbaa !23
  store i8 0, i8* bitcast (%union.anon* getelementptr inbounds (%"class.debug::Indentation", %"class.debug::Indentation"* @_ZN5debug11indentationE, i64 0, i32 1, i32 2) to i8*), align 8, !tbaa !10
  %2 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.debug::Indentation"*)* @_ZN5debug11IndentationD2Ev to void (i8*)*), i8* bitcast (%"class.debug::Indentation"* @_ZN5debug11indentationE to i8*), i8* nonnull @__dso_handle) #2
  %3 = tail call i64 @sysconf(i32 30) #2
  store i64 %3, i64* @_ZN3fseL8pageSizeE, align 8, !tbaa !16
  %4 = tail call {}* @llvm.invariant.start.p0i8(i64 8, i8* bitcast (i64* @_ZN3fseL8pageSizeE to i8*)) #2
  %5 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%class.LazilyConstructed*)* @_ZN17LazilyConstructedIN12_GLOBAL__N_121BranchCoverageRuntimeEED2Ev to void (i8*)*), i8* bitcast ({ { { { %"class.(anonymous namespace)::BranchCoverageRuntime"* } } } }* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceE to i8*), i8* nonnull @__dso_handle) #2
  ret void
}

attributes #0 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }
attributes #3 = { inlinehint nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { noinline noreturn nounwind }
attributes #7 = { nobuiltin nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { argmemonly nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #10 = { nobuiltin "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #11 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #12 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #13 = { inlinehint uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #14 = { nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #15 = { noreturn nounwind }
attributes #16 = { builtin }
attributes #17 = { noreturn }
attributes #18 = { nounwind readnone }
attributes #19 = { cold }
attributes #20 = { builtin nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20181018153226.114 (branches/release_60)"}
!2 = !{!3, !5, i64 0}
!3 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE", !4, i64 0, !8, i64 8, !6, i64 16}
!4 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderE", !5, i64 0}
!5 = !{!"any pointer", !6, i64 0}
!6 = !{!"omnipotent char", !7, i64 0}
!7 = !{!"Simple C++ TBAA"}
!8 = !{!"long", !6, i64 0}
!9 = !{!5, !5, i64 0}
!10 = !{!6, !6, i64 0}
!11 = !{!12, !14, i64 4096}
!12 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime14SingleBranchesE", !13, i64 0, !14, i64 4096, !14, i64 4100, !15, i64 4104}
!13 = !{!"_ZTSSt5arrayImLm512EE", !6, i64 0}
!14 = !{!"int", !6, i64 0}
!15 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime5WriteE", !14, i64 0}
!16 = !{!8, !8, i64 0}
!17 = !{!12, !14, i64 4100}
!18 = !{!15, !14, i64 0}
!19 = !{!20}
!20 = distinct !{!20, !21, !"_ZSt11make_uniqueIN12_GLOBAL__N_121BranchCoverageRuntimeEJEENSt9_MakeUniqIT_E15__single_objectEDpOT0_: argument 0"}
!21 = distinct !{!21, !"_ZSt11make_uniqueIN12_GLOBAL__N_121BranchCoverageRuntimeEJEENSt9_MakeUniqIT_E15__single_objectEDpOT0_"}
!22 = !{!4, !5, i64 0}
!23 = !{!3, !8, i64 8}
!24 = !{!25, !20}
!25 = distinct !{!25, !26, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime27getOutputDirFromEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE: argument 0"}
!26 = distinct !{!26, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime27getOutputDirFromEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"}
!27 = !{!28, !25}
!28 = distinct !{!28, !29, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertEPKcNS3_17__null_terminatedE: argument 0"}
!29 = distinct !{!29, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertEPKcNS3_17__null_terminatedE"}
!30 = !{!28, !20}
!31 = !{!25}
!32 = !{!33, !25, !20}
!33 = distinct !{!33, !34, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime16defaultOutputDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE: argument 0"}
!34 = distinct !{!34, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime16defaultOutputDirERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"}
!35 = !{!33, !20}
!36 = !{!37, !33, !25, !20}
!37 = distinct !{!37, !38, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_: argument 0"}
!38 = distinct !{!38, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_"}
!39 = !{!37}
!40 = !{!41, !33, !25, !20}
!41 = distinct !{!41, !42, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_PKS5_: argument 0"}
!42 = distinct !{!42, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_PKS5_"}
!43 = !{!41, !33, !20}
!44 = !{!41}
!45 = !{!46, !33, !25, !20}
!46 = distinct !{!46, !47, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_PKS5_: argument 0"}
!47 = distinct !{!47, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_PKS5_"}
!48 = !{!46, !33, !20}
!49 = !{!46, !33}
!50 = !{!14, !14, i64 0}
!51 = !{!52}
!52 = distinct !{!52, !53, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv: argument 0"}
!53 = distinct !{!53, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv"}
!54 = !{!52, !20}
!55 = !{!56}
!56 = distinct !{!56, !57, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv: argument 0"}
!57 = distinct !{!57, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv"}
!58 = !{!56, !20}
!59 = !{!60, !14, i64 8}
!60 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime6OutputE", !5, i64 0, !14, i64 8, !14, i64 12, !61, i64 16}
!61 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime6Output3$_0E", !14, i64 0, !14, i64 4}
!62 = !{!60, !14, i64 12}
!63 = !{!61, !14, i64 0}
!64 = !{!61, !14, i64 4}
!65 = !{!66, !5, i64 0}
!66 = !{!"_ZTSSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EE", !67, i64 0}
!67 = !{!"_ZTSNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EE12_Vector_implE", !5, i64 0, !5, i64 8, !5, i64 16}
!68 = !{!66, !5, i64 8}
!69 = !{!70, !8, i64 12288}
!70 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime17NonSingleBranchesE", !71, i64 0, !8, i64 12288, !15, i64 12296}
!71 = !{!"_ZTSSt5arrayIN12_GLOBAL__N_121BranchCoverageRuntime17NonSingleBranches6RecordELm1024EE", !6, i64 0}
!72 = !{!60, !5, i64 0}
!73 = !{!74}
!74 = distinct !{!74, !75, !"_ZNSt12experimental10filesystem2v17__cxx11dvERKNS2_4pathES5_: argument 0"}
!75 = distinct !{!75, !"_ZNSt12experimental10filesystem2v17__cxx11dvERKNS2_4pathES5_"}
!76 = !{!77}
!77 = distinct !{!77, !78, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv: argument 0"}
!78 = distinct !{!78, !"_ZNKSt12experimental10filesystem2v17__cxx114pathcvNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEEv"}
!79 = !{!80, !80, i64 0}
!80 = !{!"vtable pointer", !7, i64 0}
!81 = !{!82}
!82 = distinct !{!82, !83, !"_ZNKSt10error_code7messageB5cxx11Ev: argument 0"}
!83 = distinct !{!83, !"_ZNKSt10error_code7messageB5cxx11Ev"}
!84 = !{!85}
!85 = distinct !{!85, !86, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_: argument 0"}
!86 = distinct !{!86, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_"}
!87 = !{!88, !90}
!88 = distinct !{!88, !89, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_: argument 0"}
!89 = distinct !{!89, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_"}
!90 = distinct !{!90, !91, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv: argument 0"}
!91 = distinct !{!91, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv"}
!92 = !{!93}
!93 = distinct !{!93, !94, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_: argument 0"}
!94 = distinct !{!94, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_"}
!95 = !{!96}
!96 = distinct !{!96, !97, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_: argument 0"}
!97 = distinct !{!97, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_"}
!98 = !{!99, !101}
!99 = distinct !{!99, !100, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_: argument 0"}
!100 = distinct !{!100, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_"}
!101 = distinct !{!101, !102, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv: argument 0"}
!102 = distinct !{!102, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv"}
!103 = !{!104}
!104 = distinct !{!104, !105, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_: argument 0"}
!105 = distinct !{!105, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_"}
!106 = !{!107}
!107 = distinct !{!107, !108, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_: argument 0"}
!108 = distinct !{!108, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_"}
!109 = !{!110, !112}
!110 = distinct !{!110, !111, !"_ZNSt12experimental10filesystem2v17__cxx114path4_CvtIcE10_S_convertIPKcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEET_SF_: argument 0"}
!111 = distinct !{!111, !"_ZNSt12experimental10filesystem2v17__cxx114path4_CvtIcE10_S_convertIPKcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEET_SF_"}
!112 = distinct !{!112, !113, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertIPKcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEET_SD_: argument 0"}
!113 = distinct !{!113, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertIPKcEENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEET_SD_"}
!114 = !{!115, !117, i64 56}
!115 = !{!"_ZTSNSt12experimental10filesystem2v17__cxx114pathE", !3, i64 0, !116, i64 32, !117, i64 56}
!116 = !{!"_ZTSSt6vectorINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EE"}
!117 = !{!"_ZTSNSt12experimental10filesystem2v17__cxx114path5_TypeE", !6, i64 0}
!118 = !{!66, !5, i64 16}
!119 = !{!120, !8, i64 64}
!120 = !{!"_ZTSNSt12experimental10filesystem2v17__cxx114path5_CmptE", !8, i64 64}
!121 = !{!122, !8, i64 0}
!122 = !{!"_ZTSN5debug11IndentationE", !8, i64 0, !3, i64 8}
