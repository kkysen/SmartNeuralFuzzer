; ModuleID = 'BranchCoverageRuntime.cpp'
source_filename = "BranchCoverageRuntime.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%"class.std::unique_ptr" = type { %"class.std::__uniq_ptr_impl" }
%"class.std::__uniq_ptr_impl" = type { %"class.std::tuple" }
%"class.std::tuple" = type { %"struct.std::_Tuple_impl" }
%"struct.std::_Tuple_impl" = type { %"struct.std::_Head_base.1" }
%"struct.std::_Head_base.1" = type { %"class.(anonymous namespace)::BranchCoverageRuntime"* }
%"class.(anonymous namespace)::BranchCoverageRuntime" = type { %"union.(anonymous namespace)::BranchCoverageRuntime::Counts", %"struct.(anonymous namespace)::BranchCoverageRuntime::Indices", %"class.(anonymous namespace)::BranchCoverageRuntime::MMapOutput" }
%"union.(anonymous namespace)::BranchCoverageRuntime::Counts" = type { %struct.anon }
%struct.anon = type { i64, i64, i64 }
%"struct.(anonymous namespace)::BranchCoverageRuntime::Indices" = type { i8, i16, i64, i64 }
%"class.(anonymous namespace)::BranchCoverageRuntime::MMapOutput" = type { i32, i8*, i64, i8*, i8*, i8* }
%"class.std::__cxx11::basic_string" = type { %"struct.std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Alloc_hider", i64, %union.anon }
%"struct.std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Alloc_hider" = type { i8* }
%union.anon = type { i64, [8 x i8] }
%"class.std::experimental::filesystem::v1::__cxx11::path" = type <{ %"class.std::__cxx11::basic_string", %"class.std::vector", i8, [7 x i8] }>
%"class.std::vector" = type { %"struct.std::_Vector_base" }
%"struct.std::_Vector_base" = type { %"struct.std::_Vector_base<std::experimental::filesystem::v1::__cxx11::path::_Cmpt, std::allocator<std::experimental::filesystem::v1::__cxx11::path::_Cmpt> >::_Vector_impl" }
%"struct.std::_Vector_base<std::experimental::filesystem::v1::__cxx11::path::_Cmpt, std::allocator<std::experimental::filesystem::v1::__cxx11::path::_Cmpt> >::_Vector_impl" = type { %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* }
%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt" = type { %"class.std::experimental::filesystem::v1::__cxx11::path.base", i64 }
%"class.std::experimental::filesystem::v1::__cxx11::path.base" = type <{ %"class.std::__cxx11::basic_string", %"class.std::vector", i8 }>
%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error" = type { %"class.std::system_error", %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::__cxx11::basic_string" }
%"class.std::system_error" = type { %"class.std::runtime_error", %"struct.std::error_code" }
%"class.std::runtime_error" = type { %"class.std::exception", %"struct.std::__cow_string" }
%"class.std::exception" = type { i32 (...)** }
%"struct.std::__cow_string" = type { %union.anon.5 }
%union.anon.5 = type { i8* }
%"struct.std::error_code" = type { i32, %"class.std::_V2::error_category"* }
%"class.std::_V2::error_category" = type { i32 (...)** }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

$__clang_call_terminate = comdat any

$_ZNSt12experimental10filesystem2v17__cxx114pathC2IPcS3_EERKT_ = comdat any

$_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev = comdat any

$_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_ = comdat any

$_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code = comdat any

$_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE = comdat any

$_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv = comdat any

$_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_ = comdat any

$_ZN3fse4mmapIhEEPT_iiimm = comdat any

$_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z = comdat any

@_ZN3fseL8pageSizeE = internal global i64 0, align 8
@_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE = internal global i64 0, align 8
@_ZN12_GLOBAL__N_121BranchCoverageRuntime8pageSizeE = internal global i64 0, align 8
@_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE = internal global %"class.std::unique_ptr" zeroinitializer, align 8
@__dso_handle = external hidden global i8
@.str = private unnamed_addr constant [20 x i8] c"coverage.branch.out\00", align 1
@.str.4 = private unnamed_addr constant [42 x i8] c"basic_string::_M_construct null not valid\00", align 1
@_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE = external constant i8*
@_ZTVNSt12experimental10filesystem2v17__cxx1116filesystem_errorE = external unnamed_addr constant { [5 x i8*] }
@.str.5 = private unnamed_addr constant [3 x i8] c": \00", align 1
@_ZTVSt12system_error = external unnamed_addr constant { [5 x i8*] }, align 8
@.str.8 = private unnamed_addr constant [21 x i8] c"basic_string::append\00", align 1
@.str.9 = private unnamed_addr constant [19 x i8] c"filesystem error: \00", align 1
@.str.10 = private unnamed_addr constant [3 x i8] c" [\00", align 1
@.str.11 = private unnamed_addr constant [22 x i8] c"mmap failed for fd = \00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE = internal global i64 0, align 8
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_BranchCoverageRuntime.cpp, i8* null }]

; Function Attrs: nounwind
declare i64 @sysconf(i32) local_unnamed_addr #0

; Function Attrs: argmemonly nounwind
declare {}* @llvm.invariant.start.p0i8(i64, i8* nocapture) #1

; Function Attrs: nounwind uwtable
define internal void @_ZNSt10unique_ptrIN12_GLOBAL__N_121BranchCoverageRuntimeESt14default_deleteIS1_EED2Ev(%"class.std::unique_ptr"* nocapture) unnamed_addr #2 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = getelementptr inbounds %"class.std::unique_ptr", %"class.std::unique_ptr"* %0, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0
  %3 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** %2, align 8, !tbaa !2
  %4 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, null
  br i1 %4, label %18, label %5

; <label>:5:                                      ; preds = %1
  %6 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 2, i32 1
  %7 = load i8*, i8** %6, align 8, !tbaa !6
  %8 = tail call i32 @munmap(i8* %7, i64 24) #3
  %9 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 2, i32 3
  %10 = load i8*, i8** %9, align 8, !tbaa !10
  %11 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %12 = tail call i32 @munmap(i8* %10, i64 %11) #3
  %13 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 2, i32 4
  %14 = load i8*, i8** %13, align 8, !tbaa !12
  %15 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %16 = tail call i32 @munmap(i8* %14, i64 %15) #3
  %17 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime"* %3 to i8*
  tail call void @_ZdlPv(i8* %17) #14
  br label %18

; <label>:18:                                     ; preds = %1, %5
  store %"class.(anonymous namespace)::BranchCoverageRuntime"* null, %"class.(anonymous namespace)::BranchCoverageRuntime"** %2, align 8, !tbaa !2
  ret void
}

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) local_unnamed_addr #3

; Function Attrs: uwtable
define void @__BranchCoverage_onSingleBranch(i1 zeroext) local_unnamed_addr #4 personality i32 (...)* @__gxx_personality_v0 {
  %2 = tail call fastcc dereferenceable(96) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceEv()
  %3 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 0, i32 0, i32 0
  %4 = load i64, i64* %3, align 8, !tbaa !13
  %5 = add i64 %4, 1
  store i64 %5, i64* %3, align 8, !tbaa !13
  %6 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 1, i32 2
  %7 = load i64, i64* %6, align 8, !tbaa !14
  %8 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 1, i32 3
  %9 = load i64, i64* %8, align 8, !tbaa !17
  %10 = icmp eq i64 %7, %9
  %11 = zext i1 %10 to i64
  %12 = shl nuw nsw i64 %11, 1
  %13 = add i64 %12, %7
  store i64 %13, i64* %6, align 8, !tbaa !14
  %14 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 1, i32 0
  %15 = load i8, i8* %14, align 8, !tbaa !18
  %16 = zext i8 %15 to i32
  %17 = shl i32 1, %16
  %18 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 5
  %19 = load i8*, i8** %18, align 8, !tbaa !20
  %20 = getelementptr inbounds i8, i8* %19, i64 %13
  %21 = load i8, i8* %20, align 1, !tbaa !13
  %22 = trunc i32 %17 to i8
  %23 = or i8 %21, %22
  store i8 %23, i8* %20, align 1, !tbaa !13
  %24 = load i8, i8* %14, align 8, !tbaa !18
  %25 = and i8 %24, 7
  store i8 %25, i8* %14, align 8, !tbaa !18
  %26 = icmp eq i8 %25, 1
  %27 = load i64, i64* %6, align 8, !tbaa !21
  br i1 %26, label %28, label %30

; <label>:28:                                     ; preds = %1
  %29 = add i64 %27, 1
  store i64 %29, i64* %6, align 8, !tbaa !21
  br label %30

; <label>:30:                                     ; preds = %28, %1
  %31 = phi i64 [ %29, %28 ], [ %27, %1 ]
  %32 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 1, i32 1
  %33 = load i16, i16* %32, align 2, !tbaa !22
  %34 = add i16 %33, 1
  store i16 %34, i16* %32, align 2, !tbaa !22
  %35 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE, align 8, !tbaa !11
  %36 = icmp eq i64 %31, %35
  %37 = icmp eq i8 %25, 0
  %38 = and i1 %37, %36
  br i1 %38, label %39, label %113

; <label>:39:                                     ; preds = %30
  %40 = load i64, i64* %8, align 8, !tbaa !23
  %41 = trunc i16 %34 to i8
  %42 = shl i8 %41, 1
  %43 = or i8 %42, 1
  %44 = load i8*, i8** %18, align 8, !tbaa !24
  %45 = getelementptr inbounds i8, i8* %44, i64 %40
  store i8 %43, i8* %45, align 1, !tbaa !13
  %46 = lshr i16 %34, 7
  %47 = trunc i16 %46 to i8
  %48 = load i8*, i8** %18, align 8, !tbaa !24
  %49 = add i64 %40, 1
  %50 = getelementptr inbounds i8, i8* %48, i64 %49
  store i8 %47, i8* %50, align 1, !tbaa !13
  %51 = load i64, i64* %6, align 8, !tbaa !21
  %52 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE, align 8, !tbaa !11
  %53 = icmp eq i64 %51, %52
  %54 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 3
  %55 = load i8*, i8** %54, align 8, !tbaa !10
  %56 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %57 = tail call i32 @munmap(i8* %55, i64 %56) #3
  %58 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 4
  %59 = bitcast i8** %58 to i64*
  %60 = load i64, i64* %59, align 8, !tbaa !12
  %61 = bitcast i8** %54 to i64*
  store i64 %60, i64* %61, align 8, !tbaa !10
  %62 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 0
  %63 = load i32, i32* %62, align 8, !tbaa !25
  %64 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %65 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 2
  %66 = load i64, i64* %65, align 8, !tbaa !26
  %67 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %63, i32 2, i32 1, i64 %64, i64 %66)
  store i8* %67, i8** %58, align 8, !tbaa !12
  %68 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %69 = load i64, i64* %65, align 8, !tbaa !26
  %70 = add i64 %69, %68
  store i64 %70, i64* %65, align 8, !tbaa !26
  %71 = load i64, i64* %61, align 8, !tbaa !10
  %72 = bitcast i8** %18 to i64*
  store i64 %71, i64* %72, align 8, !tbaa !24
  %73 = bitcast i64* %6 to <2 x i64>*
  %74 = load <2 x i64>, <2 x i64>* %73, align 8, !tbaa !11
  %75 = insertelement <2 x i64> undef, i64 %68, i32 0
  %76 = shufflevector <2 x i64> %75, <2 x i64> undef, <2 x i32> zeroinitializer
  %77 = sub <2 x i64> %74, %76
  %78 = bitcast i64* %6 to <2 x i64>*
  store <2 x i64> %77, <2 x i64>* %78, align 8, !tbaa !11
  %79 = extractelement <2 x i64> %77, i32 0
  br i1 %53, label %80, label %99

; <label>:80:                                     ; preds = %39
  %81 = inttoptr i64 %71 to i8*
  %82 = tail call i32 @munmap(i8* %81, i64 %68) #3
  %83 = load i64, i64* %59, align 8, !tbaa !12
  store i64 %83, i64* %61, align 8, !tbaa !10
  %84 = load i32, i32* %62, align 8, !tbaa !25
  %85 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %86 = load i64, i64* %65, align 8, !tbaa !26
  %87 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %84, i32 2, i32 1, i64 %85, i64 %86)
  store i8* %87, i8** %58, align 8, !tbaa !12
  %88 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %89 = load i64, i64* %65, align 8, !tbaa !26
  %90 = add i64 %89, %88
  store i64 %90, i64* %65, align 8, !tbaa !26
  %91 = load i64, i64* %61, align 8, !tbaa !10
  store i64 %91, i64* %72, align 8, !tbaa !24
  %92 = bitcast i64* %6 to <2 x i64>*
  %93 = load <2 x i64>, <2 x i64>* %92, align 8, !tbaa !11
  %94 = insertelement <2 x i64> undef, i64 %88, i32 0
  %95 = shufflevector <2 x i64> %94, <2 x i64> undef, <2 x i32> zeroinitializer
  %96 = sub <2 x i64> %93, %95
  %97 = bitcast i64* %6 to <2 x i64>*
  store <2 x i64> %96, <2 x i64>* %97, align 8, !tbaa !11
  %98 = extractelement <2 x i64> %96, i32 0
  br label %99

; <label>:99:                                     ; preds = %80, %39
  %100 = phi i64 [ %79, %39 ], [ %98, %80 ]
  store i64 %100, i64* %8, align 8, !tbaa !17
  store i16 0, i16* %32, align 2, !tbaa !27
  %101 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 2, i32 1
  %102 = load i8*, i8** %101, align 8, !tbaa !28
  %103 = load i64, i64* %3, align 8, !tbaa !11
  %104 = trunc i64 %103 to i8
  store i8 %104, i8* %102, align 1, !tbaa !13
  %105 = getelementptr inbounds i64, i64* %3, i64 1
  %106 = getelementptr inbounds i8, i8* %102, i64 1
  %107 = load i64, i64* %105, align 8, !tbaa !11
  %108 = trunc i64 %107 to i8
  store i8 %108, i8* %106, align 1, !tbaa !13
  %109 = getelementptr inbounds i64, i64* %3, i64 2
  %110 = getelementptr inbounds i8, i8* %102, i64 2
  %111 = load i64, i64* %109, align 8, !tbaa !11
  %112 = trunc i64 %111 to i8
  store i8 %112, i8* %110, align 1, !tbaa !13
  br label %113

; <label>:113:                                    ; preds = %30, %99
  ret void
}

; Function Attrs: uwtable
define internal fastcc dereferenceable(96) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceEv() unnamed_addr #4 align 2 personality i32 (...)* @__gxx_personality_v0 {
  %1 = alloca i64, align 8
  %2 = alloca %"class.std::__cxx11::basic_string", align 8
  %3 = alloca i8*, align 8
  %4 = alloca %"class.std::experimental::filesystem::v1::__cxx11::path", align 8
  %5 = alloca i64, align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds (%"class.std::unique_ptr", %"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !2
  %8 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %7, null
  br i1 %8, label %9, label %211

; <label>:9:                                      ; preds = %0
  %10 = tail call i8* @_Znwm(i64 96) #15, !noalias !29
  %11 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %11) #3, !noalias !29
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %13 = bitcast %"class.std::__cxx11::basic_string"* %6 to %union.anon**
  store %union.anon* %12, %union.anon** %13, align 8, !tbaa !32, !noalias !29
  %14 = bitcast %union.anon* %12 to i8*
  %15 = bitcast i64* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %15) #3, !noalias !29
  store i64 19, i64* %5, align 8, !tbaa !11, !noalias !29
  %16 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %6, i64* nonnull dereferenceable(8) %5, i64 0)
          to label %17 unwind label %175, !noalias !29

; <label>:17:                                     ; preds = %9
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  store i8* %16, i8** %18, align 8, !tbaa !34, !noalias !29
  %19 = load i64, i64* %5, align 8, !tbaa !11, !noalias !29
  %20 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  store i64 %19, i64* %20, align 8, !tbaa !13, !noalias !29
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* nonnull getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i64 0, i64 0), i64 19, i32 1, i1 false) #3, !noalias !29
  %21 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  store i64 %19, i64* %21, align 8, !tbaa !36, !noalias !29
  %22 = load i8*, i8** %18, align 8, !tbaa !34, !noalias !29
  %23 = getelementptr inbounds i8, i8* %22, i64 %19
  store i8 0, i8* %23, align 1, !tbaa !13, !noalias !29
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %15) #3, !noalias !29
  %24 = load i8*, i8** %18, align 8, !tbaa !34, !noalias !29
  %25 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 64, i8* nonnull %25) #3, !noalias !29
  %26 = bitcast i8** %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %26) #3, !noalias !37
  %27 = call i8* @getenv(i8* %24) #3, !noalias !37
  store i8* %27, i8** %3, align 8, !tbaa !2, !noalias !37
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114pathC2IPcS3_EERKT_(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %4, i8** nonnull dereferenceable(8) %3)
          to label %28 unwind label %179, !noalias !29

; <label>:28:                                     ; preds = %17
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %26) #3, !noalias !37
  %29 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 0, i32 0, i32 0
  %30 = load i8*, i8** %29, align 8, !tbaa !34, !noalias !29
  %31 = invoke i32 @creat(i8* %30, i32 420)
          to label %32 unwind label %145, !noalias !29

; <label>:32:                                     ; preds = %28
  %33 = icmp eq i32 %31, -1
  br i1 %33, label %34, label %91

; <label>:34:                                     ; preds = %32
  %35 = call i8* @__cxa_allocate_exception(i64 192) #3, !noalias !29
  %36 = bitcast %"class.std::__cxx11::basic_string"* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %36) #3, !noalias !29
  %37 = load i8*, i8** %29, align 8, !tbaa !34, !noalias !40
  %38 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 0, i32 1
  %39 = load i64, i64* %38, align 8, !tbaa !36, !noalias !40
  %40 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 2
  %41 = bitcast %"class.std::__cxx11::basic_string"* %2 to %union.anon**
  store %union.anon* %40, %union.anon** %41, align 8, !tbaa !32, !alias.scope !45, !noalias !29
  %42 = bitcast i64* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %42) #3, !noalias !40
  store i64 %39, i64* %1, align 8, !tbaa !11, !noalias !40
  %43 = icmp ugt i64 %39, 15
  br i1 %43, label %47, label %44

; <label>:44:                                     ; preds = %34
  %45 = bitcast %union.anon* %40 to i8*
  %46 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 0, i32 0
  br label %53

; <label>:47:                                     ; preds = %34
  %48 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %2, i64* nonnull dereferenceable(8) %1, i64 0)
          to label %49 unwind label %67, !noalias !29

; <label>:49:                                     ; preds = %47
  %50 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 0, i32 0
  store i8* %48, i8** %50, align 8, !tbaa !34, !alias.scope !45, !noalias !29
  %51 = load i64, i64* %1, align 8, !tbaa !11, !noalias !40
  %52 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 2, i32 0
  store i64 %51, i64* %52, align 8, !tbaa !13, !alias.scope !45, !noalias !29
  br label %53

; <label>:53:                                     ; preds = %49, %44
  %54 = phi i8** [ %46, %44 ], [ %50, %49 ]
  %55 = phi i8* [ %45, %44 ], [ %48, %49 ]
  switch i64 %39, label %58 [
    i64 1, label %56
    i64 0, label %59
  ]

; <label>:56:                                     ; preds = %53
  %57 = load i8, i8* %37, align 1, !tbaa !13, !noalias !29
  store i8 %57, i8* %55, align 1, !tbaa !13, !noalias !29
  br label %59

; <label>:58:                                     ; preds = %53
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %55, i8* %37, i64 %39, i32 1, i1 false) #3, !noalias !29
  br label %59

; <label>:59:                                     ; preds = %58, %56, %53
  %60 = load i64, i64* %1, align 8, !tbaa !11, !noalias !40
  %61 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 1
  store i64 %60, i64* %61, align 8, !tbaa !36, !alias.scope !45, !noalias !29
  %62 = load i8*, i8** %54, align 8, !tbaa !34, !alias.scope !45, !noalias !29
  %63 = getelementptr inbounds i8, i8* %62, i64 %60
  store i8 0, i8* %63, align 1, !tbaa !13, !noalias !29
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %42) #3, !noalias !40
  %64 = bitcast i8* %35 to %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*
  %65 = tail call dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() #16
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %64, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %2, i32 0, %"class.std::_V2::error_category"* nonnull %65)
          to label %66 unwind label %71, !noalias !29

; <label>:66:                                     ; preds = %59
  invoke void @__cxa_throw(i8* %35, i8* bitcast (i8** @_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE to i8*), i8* bitcast (void (%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*)* @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev to i8*)) #17
          to label %90 unwind label %71, !noalias !29

; <label>:67:                                     ; preds = %47
  %68 = landingpad { i8*, i32 }
          cleanup
  %69 = extractvalue { i8*, i32 } %68, 0
  %70 = extractvalue { i8*, i32 } %68, 1
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %36) #3, !noalias !29
  br label %82

; <label>:71:                                     ; preds = %66, %59
  %72 = phi i1 [ false, %66 ], [ true, %59 ]
  %73 = landingpad { i8*, i32 }
          cleanup
  %74 = extractvalue { i8*, i32 } %73, 0
  %75 = extractvalue { i8*, i32 } %73, 1
  %76 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %2, i64 0, i32 0, i32 0
  %77 = load i8*, i8** %76, align 8, !tbaa !34, !noalias !29
  %78 = bitcast %union.anon* %40 to i8*
  %79 = icmp eq i8* %77, %78
  br i1 %79, label %81, label %80

; <label>:80:                                     ; preds = %71
  call void @_ZdlPv(i8* %77) #3, !noalias !29
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %36) #3, !noalias !29
  br i1 %72, label %82, label %85

; <label>:81:                                     ; preds = %71
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %36) #3, !noalias !29
  br i1 %72, label %82, label %85

; <label>:82:                                     ; preds = %81, %80, %67
  %83 = phi i32 [ %70, %67 ], [ %75, %81 ], [ %75, %80 ]
  %84 = phi i8* [ %69, %67 ], [ %74, %81 ], [ %74, %80 ]
  call void @__cxa_free_exception(i8* %35) #3, !noalias !29
  br label %85

; <label>:85:                                     ; preds = %82, %81, %80
  %86 = phi i32 [ %83, %82 ], [ %75, %81 ], [ %75, %80 ]
  %87 = phi i8* [ %84, %82 ], [ %74, %81 ], [ %74, %80 ]
  %88 = insertvalue { i8*, i32 } undef, i8* %87, 0
  %89 = insertvalue { i8*, i32 } %88, i32 %86, 1
  br label %147

; <label>:90:                                     ; preds = %66
  unreachable

; <label>:91:                                     ; preds = %32
  %92 = getelementptr inbounds i8, i8* %10, i64 26
  %93 = bitcast i8* %92 to i16*
  store i16 0, i16* %93, align 2, !tbaa !27, !noalias !29
  %94 = getelementptr inbounds i8, i8* %10, i64 32
  %95 = getelementptr inbounds i8, i8* %10, i64 48
  %96 = bitcast i8* %95 to i32*
  call void @llvm.memset.p0i8.i64(i8* nonnull %10, i8 0, i64 25, i32 8, i1 false), !noalias !29
  call void @llvm.memset.p0i8.i64(i8* nonnull %94, i8 0, i64 16, i32 8, i1 false), !noalias !29
  store i32 %31, i32* %96, align 8, !tbaa !25, !noalias !29
  %97 = invoke i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %31, i32 2, i32 1, i64 24, i64 0)
          to label %98 unwind label %145, !noalias !29

; <label>:98:                                     ; preds = %91
  %99 = getelementptr inbounds i8, i8* %10, i64 56
  %100 = bitcast i8* %99 to i8**
  store i8* %97, i8** %100, align 8, !tbaa !6, !noalias !29
  %101 = getelementptr inbounds i8, i8* %10, i64 64
  %102 = bitcast i8* %101 to i64*
  %103 = getelementptr inbounds i8, i8* %10, i64 80
  %104 = bitcast i8* %103 to i8**
  %105 = getelementptr inbounds i8, i8* %10, i64 88
  call void @llvm.memset.p0i8.i64(i8* nonnull %101, i8 0, i64 32, i32 8, i1 false), !noalias !29
  %106 = load i32, i32* %96, align 8, !tbaa !25, !noalias !29
  %107 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11, !noalias !29
  %108 = invoke i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %106, i32 2, i32 1, i64 %107, i64 0)
          to label %109 unwind label %145, !noalias !29

; <label>:109:                                    ; preds = %98
  %110 = getelementptr inbounds i8, i8* %10, i64 72
  store i8* %108, i8** %104, align 8, !tbaa !12, !noalias !29
  %111 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11, !noalias !29
  %112 = load i64, i64* %102, align 8, !tbaa !26, !noalias !29
  %113 = add i64 %112, %111
  store i64 %113, i64* %102, align 8, !tbaa !26, !noalias !29
  %114 = ptrtoint i8* %108 to i64
  %115 = bitcast i8* %110 to i64*
  store i64 %114, i64* %115, align 8, !tbaa !10, !noalias !29
  %116 = load i32, i32* %96, align 8, !tbaa !25, !noalias !29
  %117 = invoke i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %116, i32 2, i32 1, i64 %111, i64 %113)
          to label %118 unwind label %145, !noalias !29

; <label>:118:                                    ; preds = %109
  store i8* %117, i8** %104, align 8, !tbaa !12, !noalias !29
  %119 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11, !noalias !29
  %120 = load i64, i64* %102, align 8, !tbaa !26, !noalias !29
  %121 = add i64 %120, %119
  store i64 %121, i64* %102, align 8, !tbaa !26, !noalias !29
  %122 = load i64, i64* %115, align 8, !tbaa !10, !noalias !29
  %123 = bitcast i8* %105 to i64*
  store i64 %122, i64* %123, align 8, !tbaa !24, !noalias !29
  %124 = bitcast i8* %94 to <2 x i64>*
  store <2 x i64> <i64 3, i64 3>, <2 x i64>* %124, align 8, !tbaa !11, !noalias !29
  %125 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 1
  %126 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %125, i64 0, i32 0, i32 0, i32 0
  %127 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %126, align 8, !tbaa !46, !noalias !29
  %128 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 1, i32 0, i32 0, i32 1
  %129 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %128, align 8, !tbaa !49, !noalias !29
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %127, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %129)
          to label %130 unwind label %135, !noalias !29

; <label>:130:                                    ; preds = %118
  %131 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %126, align 8, !tbaa !46, !noalias !29
  %132 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %131, null
  br i1 %132, label %139, label %133

; <label>:133:                                    ; preds = %130
  %134 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %131 to i8*
  call void @_ZdlPv(i8* %134) #3, !noalias !29
  br label %139

; <label>:135:                                    ; preds = %118
  %136 = landingpad { i8*, i32 }
          catch i8* null
  %137 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %125, i64 0, i32 0
  %138 = extractvalue { i8*, i32 } %136, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %137) #3, !noalias !29
  call void @__clang_call_terminate(i8* %138) #18, !noalias !29
  unreachable

; <label>:139:                                    ; preds = %133, %130
  %140 = load i8*, i8** %29, align 8, !tbaa !34, !noalias !29
  %141 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 0, i32 2
  %142 = bitcast %union.anon* %141 to i8*
  %143 = icmp eq i8* %140, %142
  br i1 %143, label %170, label %144

; <label>:144:                                    ; preds = %139
  call void @_ZdlPv(i8* %140) #3, !noalias !29
  br label %170

; <label>:145:                                    ; preds = %109, %98, %91, %28
  %146 = landingpad { i8*, i32 }
          cleanup
  br label %147

; <label>:147:                                    ; preds = %145, %85
  %148 = phi { i8*, i32 } [ %146, %145 ], [ %89, %85 ]
  %149 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 1
  %150 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %149, i64 0, i32 0, i32 0, i32 0
  %151 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %150, align 8, !tbaa !46, !noalias !29
  %152 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 1, i32 0, i32 0, i32 1
  %153 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %152, align 8, !tbaa !49, !noalias !29
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %151, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %153)
          to label %154 unwind label %159, !noalias !29

; <label>:154:                                    ; preds = %147
  %155 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %150, align 8, !tbaa !46, !noalias !29
  %156 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %155, null
  br i1 %156, label %163, label %157

; <label>:157:                                    ; preds = %154
  %158 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %155 to i8*
  call void @_ZdlPv(i8* %158) #3, !noalias !29
  br label %163

; <label>:159:                                    ; preds = %147
  %160 = landingpad { i8*, i32 }
          catch i8* null
  %161 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %149, i64 0, i32 0
  %162 = extractvalue { i8*, i32 } %160, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %161) #3, !noalias !29
  call void @__clang_call_terminate(i8* %162) #18, !noalias !29
  unreachable

; <label>:163:                                    ; preds = %157, %154
  %164 = load i8*, i8** %29, align 8, !tbaa !34, !noalias !29
  %165 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %4, i64 0, i32 0, i32 2
  %166 = bitcast %union.anon* %165 to i8*
  %167 = icmp eq i8* %164, %166
  br i1 %167, label %169, label %168

; <label>:168:                                    ; preds = %163
  call void @_ZdlPv(i8* %164) #3, !noalias !29
  br label %169

; <label>:169:                                    ; preds = %168, %163
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %25) #3, !noalias !29
  br label %181

; <label>:170:                                    ; preds = %144, %139
  call void @llvm.lifetime.end.p0i8(i64 64, i8* nonnull %25) #3, !noalias !29
  %171 = ptrtoint i8* %10 to i64
  %172 = load i8*, i8** %18, align 8, !tbaa !34, !noalias !29
  %173 = icmp eq i8* %172, %14
  br i1 %173, label %193, label %174

; <label>:174:                                    ; preds = %170
  call void @_ZdlPv(i8* %172) #3, !noalias !29
  br label %193

; <label>:175:                                    ; preds = %9
  %176 = landingpad { i8*, i32 }
          cleanup
  %177 = extractvalue { i8*, i32 } %176, 0
  %178 = extractvalue { i8*, i32 } %176, 1
  br label %188

; <label>:179:                                    ; preds = %17
  %180 = landingpad { i8*, i32 }
          cleanup
  br label %181

; <label>:181:                                    ; preds = %179, %169
  %182 = phi { i8*, i32 } [ %180, %179 ], [ %148, %169 ]
  %183 = extractvalue { i8*, i32 } %182, 0
  %184 = extractvalue { i8*, i32 } %182, 1
  %185 = load i8*, i8** %18, align 8, !tbaa !34, !noalias !29
  %186 = icmp eq i8* %185, %14
  br i1 %186, label %188, label %187

; <label>:187:                                    ; preds = %181
  call void @_ZdlPv(i8* %185) #3, !noalias !29
  br label %188

; <label>:188:                                    ; preds = %187, %181, %175
  %189 = phi i8* [ %177, %175 ], [ %183, %181 ], [ %183, %187 ]
  %190 = phi i32 [ %178, %175 ], [ %184, %181 ], [ %184, %187 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #3, !noalias !29
  call void @_ZdlPv(i8* nonnull %10) #14, !noalias !29
  %191 = insertvalue { i8*, i32 } undef, i8* %189, 0
  %192 = insertvalue { i8*, i32 } %191, i32 %190, 1
  resume { i8*, i32 } %192

; <label>:193:                                    ; preds = %170, %174
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #3, !noalias !29
  %194 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds (%"class.std::unique_ptr", %"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !2
  store i64 %171, i64* bitcast (%"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE to i64*), align 8, !tbaa !2
  %195 = icmp eq %"class.(anonymous namespace)::BranchCoverageRuntime"* %194, null
  %196 = bitcast i8* %10 to %"class.(anonymous namespace)::BranchCoverageRuntime"*
  br i1 %195, label %211, label %197

; <label>:197:                                    ; preds = %193
  %198 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %194, i64 0, i32 2, i32 1
  %199 = load i8*, i8** %198, align 8, !tbaa !6
  %200 = call i32 @munmap(i8* %199, i64 24) #3
  %201 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %194, i64 0, i32 2, i32 3
  %202 = load i8*, i8** %201, align 8, !tbaa !10
  %203 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %204 = call i32 @munmap(i8* %202, i64 %203) #3
  %205 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %194, i64 0, i32 2, i32 4
  %206 = load i8*, i8** %205, align 8, !tbaa !12
  %207 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %208 = call i32 @munmap(i8* %206, i64 %207) #3
  %209 = bitcast %"class.(anonymous namespace)::BranchCoverageRuntime"* %194 to i8*
  call void @_ZdlPv(i8* %209) #14
  %210 = load %"class.(anonymous namespace)::BranchCoverageRuntime"*, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds (%"class.std::unique_ptr", %"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !2
  br label %211

; <label>:211:                                    ; preds = %193, %197, %0
  %212 = phi %"class.(anonymous namespace)::BranchCoverageRuntime"* [ %7, %0 ], [ %210, %197 ], [ %196, %193 ]
  ret %"class.(anonymous namespace)::BranchCoverageRuntime"* %212
}

; Function Attrs: uwtable
define void @__BranchCoverage_onMultiBranch(i32, i32) local_unnamed_addr #4 {
  %3 = tail call fastcc dereferenceable(96) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceEv()
  %4 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %3, i64 0, i32 0, i32 0, i32 1
  %5 = load i64, i64* %4, align 8, !tbaa !13
  %6 = add i64 %5, 1
  store i64 %6, i64* %4, align 8, !tbaa !13
  %7 = shl i32 %0, 1
  %8 = or i32 %7, 1
  %9 = zext i32 %8 to i64
  %10 = zext i32 %1 to i64
  %11 = shl i64 %10, 34
  %12 = or i64 %11, %9
  tail call fastcc void @_ZN12_GLOBAL__N_121BranchCoverageRuntime17onNonSingleBranchEm(%"class.(anonymous namespace)::BranchCoverageRuntime"* nonnull %3, i64 %12)
  ret void
}

; Function Attrs: uwtable
define void @__BranchCoverage_onInfiniteBranch(i64) local_unnamed_addr #4 {
  %2 = tail call fastcc dereferenceable(96) %"class.(anonymous namespace)::BranchCoverageRuntime"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8instanceEv()
  %3 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %2, i64 0, i32 0, i32 0, i32 2
  %4 = load i64, i64* %3, align 8, !tbaa !13
  %5 = add i64 %4, 1
  store i64 %5, i64* %3, align 8, !tbaa !13
  %6 = shl i64 %0, 2
  tail call fastcc void @_ZN12_GLOBAL__N_121BranchCoverageRuntime17onNonSingleBranchEm(%"class.(anonymous namespace)::BranchCoverageRuntime"* nonnull %2, i64 %6)
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

declare i32 @__gxx_personality_v0(...)

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8*) local_unnamed_addr #5 comdat {
  %2 = tail call i8* @__cxa_begin_catch(i8* %0) #3
  tail call void @_ZSt9terminatev() #18
  unreachable
}

declare i8* @__cxa_begin_catch(i8*) local_unnamed_addr

declare void @_ZSt9terminatev() local_unnamed_addr

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

; Function Attrs: nobuiltin
declare noalias nonnull i8* @_Znwm(i64) local_unnamed_addr #6

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) local_unnamed_addr #7

; Function Attrs: noreturn
declare void @_ZSt19__throw_logic_errorPKc(i8*) local_unnamed_addr #8

declare i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"*, i64* dereferenceable(8), i64) local_unnamed_addr #9

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: argmemonly nounwind readonly
declare i64 @strlen(i8* nocapture) local_unnamed_addr #10

; Function Attrs: nounwind readonly
declare i8* @getenv(i8* nocapture) local_unnamed_addr #11

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx114pathC2IPcS3_EERKT_(%"class.std::experimental::filesystem::v1::__cxx11::path"*, i8** dereferenceable(8)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca i64, align 8
  %4 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0
  %5 = load i8*, i8** %1, align 8, !tbaa !2
  %6 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2
  %7 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %0 to %union.anon**
  store %union.anon* %6, %union.anon** %7, align 8, !tbaa !32, !alias.scope !50
  %8 = icmp eq i8* %5, null
  %9 = bitcast %union.anon* %6 to i8*
  br i1 %8, label %14, label %10

; <label>:10:                                     ; preds = %2
  %11 = tail call i64 @strlen(i8* nonnull %5) #3, !noalias !50
  %12 = bitcast i64* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %12) #3, !noalias !50
  store i64 %11, i64* %3, align 8, !tbaa !11, !noalias !50
  %13 = icmp ugt i64 %11, 15
  br i1 %13, label %17, label %15

; <label>:14:                                     ; preds = %2
  tail call void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.4, i64 0, i64 0)) #17
  unreachable

; <label>:15:                                     ; preds = %10
  %16 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  br label %22

; <label>:17:                                     ; preds = %10
  %18 = call i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %4, i64* nonnull dereferenceable(8) %3, i64 0)
  %19 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  store i8* %18, i8** %19, align 8, !tbaa !34, !alias.scope !50
  %20 = load i64, i64* %3, align 8, !tbaa !11, !noalias !50
  %21 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 2, i32 0
  store i64 %20, i64* %21, align 8, !tbaa !13, !alias.scope !50
  br label %22

; <label>:22:                                     ; preds = %17, %15
  %23 = phi i8** [ %16, %15 ], [ %19, %17 ]
  %24 = phi i8* [ %9, %15 ], [ %18, %17 ]
  switch i64 %11, label %27 [
    i64 1, label %25
    i64 0, label %28
  ]

; <label>:25:                                     ; preds = %22
  %26 = load i8, i8* %5, align 1, !tbaa !13, !noalias !50
  store i8 %26, i8* %24, align 1, !tbaa !13
  br label %28

; <label>:27:                                     ; preds = %22
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* nonnull %5, i64 %11, i32 1, i1 false) #3
  br label %28

; <label>:28:                                     ; preds = %22, %25, %27
  %29 = load i64, i64* %3, align 8, !tbaa !11, !noalias !50
  %30 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 1
  store i64 %29, i64* %30, align 8, !tbaa !36, !alias.scope !50
  %31 = load i8*, i8** %23, align 8, !tbaa !34, !alias.scope !50
  %32 = getelementptr inbounds i8, i8* %31, i64 %29
  store i8 0, i8* %32, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %12) #3, !noalias !50
  %33 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 1
  %34 = bitcast %"class.std::vector"* %33 to i8*
  call void @llvm.memset.p0i8.i64(i8* nonnull %34, i8 0, i64 25, i32 8, i1 false)
  invoke void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"* nonnull %0)
          to label %35 unwind label %36

; <label>:35:                                     ; preds = %28
  ret void

; <label>:36:                                     ; preds = %28
  %37 = landingpad { i8*, i32 }
          cleanup
  %38 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %33, i64 0, i32 0, i32 0, i32 0
  %39 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %38, align 8, !tbaa !46
  %40 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 1, i32 0, i32 0, i32 1
  %41 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %40, align 8, !tbaa !49
  %42 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %39, %41
  br i1 %42, label %72, label %43

; <label>:43:                                     ; preds = %36
  br label %44

; <label>:44:                                     ; preds = %43, %67
  %45 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %68, %67 ], [ %39, %43 ]
  %46 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, i64 0, i32 0, i32 1
  %47 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %46, i64 0, i32 0, i32 0, i32 0
  %48 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %47, align 8, !tbaa !46
  %49 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, i64 0, i32 0, i32 1, i32 0, i32 0, i32 1
  %50 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %49, align 8, !tbaa !49
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %48, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %50)
          to label %51 unwind label %56

; <label>:51:                                     ; preds = %44
  %52 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %47, align 8, !tbaa !46
  %53 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %52, null
  br i1 %53, label %60, label %54

; <label>:54:                                     ; preds = %51
  %55 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %52 to i8*
  call void @_ZdlPv(i8* %55) #3
  br label %60

; <label>:56:                                     ; preds = %44
  %57 = landingpad { i8*, i32 }
          catch i8* null
  %58 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %46, i64 0, i32 0
  %59 = extractvalue { i8*, i32 } %57, 0
  call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %58) #3
  call void @__clang_call_terminate(i8* %59) #18
  unreachable

; <label>:60:                                     ; preds = %54, %51
  %61 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, i64 0, i32 0, i32 0, i32 0, i32 0
  %62 = load i8*, i8** %61, align 8, !tbaa !34
  %63 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, i64 0, i32 0, i32 0, i32 2
  %64 = bitcast %union.anon* %63 to i8*
  %65 = icmp eq i8* %62, %64
  br i1 %65, label %67, label %66

; <label>:66:                                     ; preds = %60
  call void @_ZdlPv(i8* %62) #3
  br label %67

; <label>:67:                                     ; preds = %60, %66
  %68 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, i64 1
  %69 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %68, %41
  br i1 %69, label %70, label %44

; <label>:70:                                     ; preds = %67
  %71 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %38, align 8, !tbaa !46
  br label %72

; <label>:72:                                     ; preds = %70, %36
  %73 = phi %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* [ %71, %70 ], [ %39, %36 ]
  %74 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %73, null
  br i1 %74, label %77, label %75

; <label>:75:                                     ; preds = %72
  %76 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %73 to i8*
  call void @_ZdlPv(i8* %76) #3
  br label %77

; <label>:77:                                     ; preds = %72, %75
  %78 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %0, i64 0, i32 0, i32 0, i32 0
  %79 = load i8*, i8** %78, align 8, !tbaa !34
  %80 = icmp eq i8* %79, %9
  br i1 %80, label %82, label %81

; <label>:81:                                     ; preds = %77
  call void @_ZdlPv(i8* %79) #3
  br label %82

; <label>:82:                                     ; preds = %77, %81
  resume { i8*, i32 } %37
}

declare void @_ZNSt12experimental10filesystem2v17__cxx114path14_M_split_cmptsEv(%"class.std::experimental::filesystem::v1::__cxx11::path"*) local_unnamed_addr #9

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"*) unnamed_addr #2 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = getelementptr inbounds %"struct.std::_Vector_base", %"struct.std::_Vector_base"* %0, i64 0, i32 0, i32 0
  %3 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %2, align 8, !tbaa !46
  %4 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %3, null
  br i1 %4, label %7, label %5

; <label>:5:                                      ; preds = %1
  %6 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %3 to i8*
  tail call void @_ZdlPv(i8* %6) #3
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
  %9 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %8, align 8, !tbaa !46
  %10 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 1, i32 0, i32 0, i32 1
  %11 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %10, align 8, !tbaa !49
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %9, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %11)
          to label %12 unwind label %17

; <label>:12:                                     ; preds = %5
  %13 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %8, align 8, !tbaa !46
  %14 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %13, null
  br i1 %14, label %21, label %15

; <label>:15:                                     ; preds = %12
  %16 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %13 to i8*
  tail call void @_ZdlPv(i8* %16) #3
  br label %21

; <label>:17:                                     ; preds = %5
  %18 = landingpad { i8*, i32 }
          catch i8* null
  %19 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %7, i64 0, i32 0
  %20 = extractvalue { i8*, i32 } %18, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %19) #3
  tail call void @__clang_call_terminate(i8* %20) #18
  unreachable

; <label>:21:                                     ; preds = %15, %12
  %22 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 0, i32 0, i32 0
  %23 = load i8*, i8** %22, align 8, !tbaa !34
  %24 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 0, i32 0, i32 0, i32 2
  %25 = bitcast %union.anon* %24 to i8*
  %26 = icmp eq i8* %23, %25
  br i1 %26, label %28, label %27

; <label>:27:                                     ; preds = %21
  tail call void @_ZdlPv(i8* %23) #3
  br label %28

; <label>:28:                                     ; preds = %21, %27
  %29 = getelementptr inbounds %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt", %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %6, i64 1
  %30 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %29, %1
  br i1 %30, label %31, label %5

; <label>:31:                                     ; preds = %28, %2
  ret void
}

declare i32 @creat(i8*, i32) local_unnamed_addr #9

declare i8* @__cxa_allocate_exception(i64) local_unnamed_addr

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*, %"class.std::__cxx11::basic_string"* dereferenceable(32), i32, %"class.std::_V2::error_category"*) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 0
  tail call void @_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::system_error"* %5, i32 %2, %"class.std::_V2::error_category"* %3, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %1)
  %6 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 0, i32 0, i32 0, i32 0
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTVNSt12experimental10filesystem2v17__cxx1116filesystem_errorE, i64 0, inrange i32 0, i64 2) to i32 (...)**), i32 (...)*** %6, align 8, !tbaa !53
  %7 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1
  %8 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 0, i32 2
  %9 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %7 to %union.anon**
  store %union.anon* %8, %union.anon** %9, align 8, !tbaa !32
  %10 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 0, i32 1
  store i64 0, i64* %10, align 8, !tbaa !36
  %11 = bitcast %union.anon* %8 to i8*
  store i8 0, i8* %11, align 1, !tbaa !13
  %12 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 1
  %13 = bitcast %"class.std::vector"* %12 to i8*
  tail call void @llvm.memset.p0i8.i64(i8* nonnull %13, i8 0, i64 25, i32 8, i1 false) #3
  %14 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2
  %15 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 0, i32 2
  %16 = bitcast %"class.std::experimental::filesystem::v1::__cxx11::path"* %14 to %union.anon**
  store %union.anon* %15, %union.anon** %16, align 8, !tbaa !32
  %17 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 0, i32 1
  store i64 0, i64* %17, align 8, !tbaa !36
  %18 = bitcast %union.anon* %15 to i8*
  store i8 0, i8* %18, align 1, !tbaa !13
  %19 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 1
  %20 = bitcast %"class.std::vector"* %19 to i8*
  tail call void @llvm.memset.p0i8.i64(i8* nonnull %20, i8 0, i64 25, i32 8, i1 false) #3
  %21 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 3
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv(%"class.std::__cxx11::basic_string"* nonnull sret %21, %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0)
          to label %22 unwind label %23

; <label>:22:                                     ; preds = %4
  ret void

; <label>:23:                                     ; preds = %4
  %24 = landingpad { i8*, i32 }
          cleanup
  %25 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %19, i64 0, i32 0, i32 0, i32 0
  %26 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %25, align 8, !tbaa !46
  %27 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 2, i32 1, i32 0, i32 0, i32 1
  %28 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %27, align 8, !tbaa !49
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %26, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %28)
          to label %29 unwind label %34

; <label>:29:                                     ; preds = %23
  %30 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %25, align 8, !tbaa !46
  %31 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %30, null
  br i1 %31, label %38, label %32

; <label>:32:                                     ; preds = %29
  %33 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %30 to i8*
  tail call void @_ZdlPv(i8* %33) #3
  br label %38

; <label>:34:                                     ; preds = %23
  %35 = landingpad { i8*, i32 }
          catch i8* null
  %36 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %19, i64 0, i32 0
  %37 = extractvalue { i8*, i32 } %35, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %36) #3
  tail call void @__clang_call_terminate(i8* %37) #18
  unreachable

; <label>:38:                                     ; preds = %32, %29
  %39 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %14, i64 0, i32 0, i32 0, i32 0
  %40 = load i8*, i8** %39, align 8, !tbaa !34
  %41 = icmp eq i8* %40, %18
  br i1 %41, label %43, label %42

; <label>:42:                                     ; preds = %38
  tail call void @_ZdlPv(i8* %40) #3
  br label %43

; <label>:43:                                     ; preds = %38, %42
  %44 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %12, i64 0, i32 0, i32 0, i32 0
  %45 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %44, align 8, !tbaa !46
  %46 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %0, i64 0, i32 1, i32 1, i32 0, i32 0, i32 1
  %47 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %46, align 8, !tbaa !49
  invoke void @_ZNSt12_Destroy_auxILb0EE9__destroyIPNSt12experimental10filesystem2v17__cxx114path5_CmptEEEvT_S9_(%"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %45, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %47)
          to label %48 unwind label %53

; <label>:48:                                     ; preds = %43
  %49 = load %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"*, %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"** %44, align 8, !tbaa !46
  %50 = icmp eq %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %49, null
  br i1 %50, label %57, label %51

; <label>:51:                                     ; preds = %48
  %52 = bitcast %"struct.std::experimental::filesystem::v1::__cxx11::path::_Cmpt"* %49 to i8*
  tail call void @_ZdlPv(i8* %52) #3
  br label %57

; <label>:53:                                     ; preds = %43
  %54 = landingpad { i8*, i32 }
          catch i8* null
  %55 = getelementptr inbounds %"class.std::vector", %"class.std::vector"* %12, i64 0, i32 0
  %56 = extractvalue { i8*, i32 } %54, 0
  tail call void @_ZNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EED2Ev(%"struct.std::_Vector_base"* nonnull %55) #3
  tail call void @__clang_call_terminate(i8* %56) #18
  unreachable

; <label>:57:                                     ; preds = %51, %48
  %58 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::path", %"class.std::experimental::filesystem::v1::__cxx11::path"* %7, i64 0, i32 0, i32 0, i32 0
  %59 = load i8*, i8** %58, align 8, !tbaa !34
  %60 = icmp eq i8* %59, %11
  br i1 %60, label %62, label %61

; <label>:61:                                     ; preds = %57
  tail call void @_ZdlPv(i8* %59) #3
  br label %62

; <label>:62:                                     ; preds = %57, %61
  tail call void @_ZNSt12system_errorD2Ev(%"class.std::system_error"* nonnull %5) #3
  resume { i8*, i32 } %24
}

; Function Attrs: nounwind
declare void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*) unnamed_addr #0

declare void @__cxa_throw(i8*, i8*, i8*) local_unnamed_addr

declare void @__cxa_free_exception(i8*) local_unnamed_addr

; Function Attrs: nounwind readnone
declare dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() local_unnamed_addr #12

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt12system_errorC2ESt10error_codeRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::system_error"*, i32, %"class.std::_V2::error_category"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #4 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = alloca %"class.std::__cxx11::basic_string", align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 0
  %9 = bitcast %"class.std::__cxx11::basic_string"* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %9) #3
  %10 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %10) #3
  call void @_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_(%"class.std::__cxx11::basic_string"* nonnull sret %6, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %3, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i64 0, i64 0))
  %11 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %11) #3
  %12 = bitcast %"class.std::_V2::error_category"* %2 to void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)***
  %13 = load void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)**, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*** %12, align 8, !tbaa !53, !noalias !55
  %14 = getelementptr inbounds void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)** %13, i64 4
  %15 = load void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)*, void (%"class.std::__cxx11::basic_string"*, %"class.std::_V2::error_category"*, i32)** %14, align 8, !noalias !55
  invoke void %15(%"class.std::__cxx11::basic_string"* nonnull sret %7, %"class.std::_V2::error_category"* nonnull %2, i32 %1)
          to label %16 unwind label %86

; <label>:16:                                     ; preds = %4
  %17 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  %18 = load i64, i64* %17, align 8, !tbaa !36, !noalias !58
  %19 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 1
  %20 = load i64, i64* %19, align 8, !tbaa !36, !noalias !58
  %21 = add i64 %20, %18
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  %23 = load i8*, i8** %22, align 8, !tbaa !34, !noalias !58
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %25 = bitcast %union.anon* %24 to i8*
  %26 = icmp eq i8* %23, %25
  %27 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  %28 = load i64, i64* %27, align 8, !noalias !58
  %29 = select i1 %26, i64 15, i64 %28
  %30 = icmp ugt i64 %21, %29
  %31 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %32 = load i8*, i8** %31, align 8, !tbaa !34, !noalias !58
  br i1 %30, label %33, label %43

; <label>:33:                                     ; preds = %16
  %34 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %35 = bitcast %union.anon* %34 to i8*
  %36 = icmp eq i8* %32, %35
  %37 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  %38 = load i64, i64* %37, align 8, !noalias !58
  %39 = select i1 %36, i64 15, i64 %38
  %40 = icmp ugt i64 %21, %39
  br i1 %40, label %43, label %41

; <label>:41:                                     ; preds = %33
  %42 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %7, i64 0, i64 0, i8* %23, i64 %18)
          to label %45 unwind label %93

; <label>:43:                                     ; preds = %33, %16
  %44 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"* nonnull %6, i8* %32, i64 %20)
          to label %45 unwind label %93

; <label>:45:                                     ; preds = %43, %41
  %46 = phi %"class.std::__cxx11::basic_string"* [ %42, %41 ], [ %44, %43 ]
  %47 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2
  %48 = bitcast %"class.std::__cxx11::basic_string"* %5 to %union.anon**
  store %union.anon* %47, %union.anon** %48, align 8, !tbaa !32, !alias.scope !58
  %49 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %46, i64 0, i32 0, i32 0
  %50 = load i8*, i8** %49, align 8, !tbaa !34
  %51 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %46, i64 0, i32 2
  %52 = bitcast %union.anon* %51 to i8*
  %53 = icmp eq i8* %50, %52
  br i1 %53, label %54, label %56

; <label>:54:                                     ; preds = %45
  %55 = bitcast %union.anon* %47 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %55, i8* nonnull %50, i64 16, i32 1, i1 false) #3
  br label %61

; <label>:56:                                     ; preds = %45
  %57 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  store i8* %50, i8** %57, align 8, !tbaa !34, !alias.scope !58
  %58 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %46, i64 0, i32 2, i32 0
  %59 = load i64, i64* %58, align 8, !tbaa !13
  %60 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 2, i32 0
  store i64 %59, i64* %60, align 8, !tbaa !13, !alias.scope !58
  br label %61

; <label>:61:                                     ; preds = %56, %54
  %62 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %46, i64 0, i32 1
  %63 = load i64, i64* %62, align 8, !tbaa !36
  %64 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 1
  store i64 %63, i64* %64, align 8, !tbaa !36, !alias.scope !58
  %65 = bitcast %"class.std::__cxx11::basic_string"* %46 to %union.anon**
  store %union.anon* %51, %union.anon** %65, align 8, !tbaa !34
  store i64 0, i64* %62, align 8, !tbaa !36
  store i8 0, i8* %52, align 1, !tbaa !13
  invoke void @_ZNSt13runtime_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::runtime_error"* %8, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %5)
          to label %66 unwind label %97

; <label>:66:                                     ; preds = %61
  %67 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %68 = load i8*, i8** %67, align 8, !tbaa !34
  %69 = bitcast %union.anon* %47 to i8*
  %70 = icmp eq i8* %68, %69
  br i1 %70, label %72, label %71

; <label>:71:                                     ; preds = %66
  call void @_ZdlPv(i8* %68) #3
  br label %72

; <label>:72:                                     ; preds = %66, %71
  %73 = load i8*, i8** %31, align 8, !tbaa !34
  %74 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %75 = bitcast %union.anon* %74 to i8*
  %76 = icmp eq i8* %73, %75
  br i1 %76, label %78, label %77

; <label>:77:                                     ; preds = %72
  call void @_ZdlPv(i8* %73) #3
  br label %78

; <label>:78:                                     ; preds = %72, %77
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #3
  %79 = load i8*, i8** %22, align 8, !tbaa !34
  %80 = icmp eq i8* %79, %25
  br i1 %80, label %82, label %81

; <label>:81:                                     ; preds = %78
  call void @_ZdlPv(i8* %79) #3
  br label %82

; <label>:82:                                     ; preds = %78, %81
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %10) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %9) #3
  %83 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 0, i32 0, i32 0
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [5 x i8*] }, { [5 x i8*] }* @_ZTVSt12system_error, i64 0, inrange i32 0, i64 2) to i32 (...)**), i32 (...)*** %83, align 8, !tbaa !53
  %84 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 1, i32 0
  store i32 %1, i32* %84, align 8
  %85 = getelementptr inbounds %"class.std::system_error", %"class.std::system_error"* %0, i64 0, i32 1, i32 1
  store %"class.std::_V2::error_category"* %2, %"class.std::_V2::error_category"** %85, align 8
  ret void

; <label>:86:                                     ; preds = %4
  %87 = landingpad { i8*, i32 }
          cleanup
  %88 = extractvalue { i8*, i32 } %87, 0
  %89 = extractvalue { i8*, i32 } %87, 1
  %90 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  %91 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %92 = bitcast %union.anon* %91 to i8*
  br label %114

; <label>:93:                                     ; preds = %43, %41
  %94 = landingpad { i8*, i32 }
          cleanup
  %95 = extractvalue { i8*, i32 } %94, 0
  %96 = extractvalue { i8*, i32 } %94, 1
  br label %106

; <label>:97:                                     ; preds = %61
  %98 = landingpad { i8*, i32 }
          cleanup
  %99 = extractvalue { i8*, i32 } %98, 0
  %100 = extractvalue { i8*, i32 } %98, 1
  %101 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %5, i64 0, i32 0, i32 0
  %102 = load i8*, i8** %101, align 8, !tbaa !34
  %103 = bitcast %union.anon* %47 to i8*
  %104 = icmp eq i8* %102, %103
  br i1 %104, label %106, label %105

; <label>:105:                                    ; preds = %97
  call void @_ZdlPv(i8* %102) #3
  br label %106

; <label>:106:                                    ; preds = %105, %97, %93
  %107 = phi i8* [ %95, %93 ], [ %99, %97 ], [ %99, %105 ]
  %108 = phi i32 [ %96, %93 ], [ %100, %97 ], [ %100, %105 ]
  %109 = load i8*, i8** %31, align 8, !tbaa !34
  %110 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %111 = bitcast %union.anon* %110 to i8*
  %112 = icmp eq i8* %109, %111
  br i1 %112, label %114, label %113

; <label>:113:                                    ; preds = %106
  call void @_ZdlPv(i8* %109) #3
  br label %114

; <label>:114:                                    ; preds = %113, %106, %86
  %115 = phi i8* [ %25, %113 ], [ %25, %106 ], [ %92, %86 ]
  %116 = phi i8** [ %22, %113 ], [ %22, %106 ], [ %90, %86 ]
  %117 = phi i8* [ %107, %113 ], [ %107, %106 ], [ %88, %86 ]
  %118 = phi i32 [ %108, %113 ], [ %108, %106 ], [ %89, %86 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %11) #3
  %119 = load i8*, i8** %116, align 8, !tbaa !34
  %120 = icmp eq i8* %119, %115
  br i1 %120, label %122, label %121

; <label>:121:                                    ; preds = %114
  call void @_ZdlPv(i8* %119) #3
  br label %122

; <label>:122:                                    ; preds = %114, %121
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %10) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %9) #3
  %123 = insertvalue { i8*, i32 } undef, i8* %117, 0
  %124 = insertvalue { i8*, i32 } %123, i32 %118, 1
  resume { i8*, i32 } %124
}

; Function Attrs: inlinehint uwtable
define linkonce_odr void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_error11_M_gen_whatEv(%"class.std::__cxx11::basic_string"* noalias sret, %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*) local_unnamed_addr #13 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = alloca %"class.std::__cxx11::basic_string", align 8
  %9 = alloca %"class.std::__cxx11::basic_string", align 8
  %10 = alloca %"class.std::__cxx11::basic_string", align 8
  %11 = alloca %"class.std::__cxx11::basic_string", align 8
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %13 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %12, %union.anon** %13, align 8, !tbaa !32
  %14 = bitcast %union.anon* %12 to i8*
  %15 = bitcast i64* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %15) #3
  store i64 18, i64* %5, align 8, !tbaa !11
  %16 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %0, i64* nonnull dereferenceable(8) %5, i64 0)
          to label %17 unwind label %135

; <label>:17:                                     ; preds = %2
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %16, i8** %18, align 8, !tbaa !34
  %19 = load i64, i64* %5, align 8, !tbaa !11
  %20 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %19, i64* %20, align 8, !tbaa !13
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* nonnull getelementptr inbounds ([19 x i8], [19 x i8]* @.str.9, i64 0, i64 0), i64 18, i32 1, i1 false) #3
  %21 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 %19, i64* %21, align 8, !tbaa !36
  %22 = load i8*, i8** %18, align 8, !tbaa !34
  %23 = getelementptr inbounds i8, i8* %22, i64 %19
  store i8 0, i8* %23, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %15) #3
  %24 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 0, i32 0
  %25 = call i8* @_ZNKSt13runtime_error4whatEv(%"class.std::runtime_error"* %24) #3
  %26 = call i64 @strlen(i8* %25) #3
  %27 = load i64, i64* %21, align 8, !tbaa !36
  %28 = sub i64 9223372036854775807, %27
  %29 = icmp ult i64 %28, %26
  br i1 %29, label %30, label %32

; <label>:30:                                     ; preds = %17
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i64 0, i64 0)) #17
          to label %31 unwind label %139

; <label>:31:                                     ; preds = %30
  unreachable

; <label>:32:                                     ; preds = %17
  %33 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i8* %25, i64 %26)
          to label %34 unwind label %139

; <label>:34:                                     ; preds = %32
  %35 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 1, i32 0, i32 1
  %36 = load i64, i64* %35, align 8, !tbaa !36
  %37 = icmp eq i64 %36, 0
  br i1 %37, label %182, label %38

; <label>:38:                                     ; preds = %34
  %39 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %39) #3
  %40 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %40) #3
  %41 = bitcast %"class.std::__cxx11::basic_string"* %8 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %41) #3
  %42 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 1, i32 0, i32 0, i32 0
  %43 = load i8*, i8** %42, align 8, !tbaa !34, !noalias !61
  %44 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2
  %45 = bitcast %"class.std::__cxx11::basic_string"* %8 to %union.anon**
  store %union.anon* %44, %union.anon** %45, align 8, !tbaa !32, !alias.scope !61
  %46 = bitcast i64* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %46) #3, !noalias !61
  store i64 %36, i64* %4, align 8, !tbaa !11, !noalias !61
  %47 = icmp ugt i64 %36, 15
  br i1 %47, label %48, label %54

; <label>:48:                                     ; preds = %38
  %49 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %8, i64* nonnull dereferenceable(8) %4, i64 0)
          to label %50 unwind label %143

; <label>:50:                                     ; preds = %48
  %51 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  store i8* %49, i8** %51, align 8, !tbaa !34, !alias.scope !61
  %52 = load i64, i64* %4, align 8, !tbaa !11, !noalias !61
  %53 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 2, i32 0
  store i64 %52, i64* %53, align 8, !tbaa !13, !alias.scope !61
  br label %60

; <label>:54:                                     ; preds = %38
  %55 = bitcast %union.anon* %44 to i8*
  %56 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %57 = icmp eq i64 %36, 1
  br i1 %57, label %58, label %60

; <label>:58:                                     ; preds = %54
  %59 = load i8, i8* %43, align 1, !tbaa !13
  store i8 %59, i8* %55, align 8, !tbaa !13
  br label %63

; <label>:60:                                     ; preds = %50, %54
  %61 = phi i8* [ %49, %50 ], [ %55, %54 ]
  %62 = phi i8** [ %51, %50 ], [ %56, %54 ]
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %61, i8* %43, i64 %36, i32 1, i1 false) #3
  br label %63

; <label>:63:                                     ; preds = %60, %58
  %64 = phi i8** [ %62, %60 ], [ %56, %58 ]
  %65 = load i64, i64* %4, align 8, !tbaa !11, !noalias !61
  %66 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 1
  store i64 %65, i64* %66, align 8, !tbaa !36, !alias.scope !61
  %67 = load i8*, i8** %64, align 8, !tbaa !34, !alias.scope !61
  %68 = getelementptr inbounds i8, i8* %67, i64 %65
  store i8 0, i8* %68, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %46) #3, !noalias !61
  %69 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %8, i64 0, i64 0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i64 0, i64 0), i64 2)
          to label %70 unwind label %147

; <label>:70:                                     ; preds = %63
  %71 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %72 = bitcast %"class.std::__cxx11::basic_string"* %7 to %union.anon**
  store %union.anon* %71, %union.anon** %72, align 8, !tbaa !32, !alias.scope !66
  %73 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %69, i64 0, i32 0, i32 0
  %74 = load i8*, i8** %73, align 8, !tbaa !34
  %75 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %69, i64 0, i32 2
  %76 = bitcast %union.anon* %75 to i8*
  %77 = icmp eq i8* %74, %76
  br i1 %77, label %78, label %80

; <label>:78:                                     ; preds = %70
  %79 = bitcast %union.anon* %71 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %79, i8* nonnull %74, i64 16, i32 1, i1 false) #3
  br label %85

; <label>:80:                                     ; preds = %70
  %81 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  store i8* %74, i8** %81, align 8, !tbaa !34, !alias.scope !66
  %82 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %69, i64 0, i32 2, i32 0
  %83 = load i64, i64* %82, align 8, !tbaa !13
  %84 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2, i32 0
  store i64 %83, i64* %84, align 8, !tbaa !13, !alias.scope !66
  br label %85

; <label>:85:                                     ; preds = %80, %78
  %86 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %69, i64 0, i32 1
  %87 = load i64, i64* %86, align 8, !tbaa !36
  %88 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 1
  store i64 %87, i64* %88, align 8, !tbaa !36, !alias.scope !66
  %89 = bitcast %"class.std::__cxx11::basic_string"* %69 to %union.anon**
  store %union.anon* %75, %union.anon** %89, align 8, !tbaa !34
  store i64 0, i64* %86, align 8, !tbaa !36
  store i8 0, i8* %76, align 1, !tbaa !13
  %90 = load i64, i64* %88, align 8, !tbaa !36, !noalias !69
  %91 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEmmmc(%"class.std::__cxx11::basic_string"* nonnull %7, i64 %90, i64 0, i64 1, i8 signext 93)
          to label %92 unwind label %151

; <label>:92:                                     ; preds = %85
  %93 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %94 = bitcast %"class.std::__cxx11::basic_string"* %6 to %union.anon**
  store %union.anon* %93, %union.anon** %94, align 8, !tbaa !32, !alias.scope !69
  %95 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %91, i64 0, i32 0, i32 0
  %96 = load i8*, i8** %95, align 8, !tbaa !34
  %97 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %91, i64 0, i32 2
  %98 = bitcast %union.anon* %97 to i8*
  %99 = icmp eq i8* %96, %98
  br i1 %99, label %100, label %103

; <label>:100:                                    ; preds = %92
  %101 = bitcast %union.anon* %93 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %101, i8* nonnull %96, i64 16, i32 1, i1 false) #3
  %102 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  br label %108

; <label>:103:                                    ; preds = %92
  %104 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  store i8* %96, i8** %104, align 8, !tbaa !34, !alias.scope !69
  %105 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %91, i64 0, i32 2, i32 0
  %106 = load i64, i64* %105, align 8, !tbaa !13
  %107 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  store i64 %106, i64* %107, align 8, !tbaa !13, !alias.scope !69
  br label %108

; <label>:108:                                    ; preds = %103, %100
  %109 = phi i8** [ %104, %103 ], [ %102, %100 ]
  %110 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %91, i64 0, i32 1
  %111 = load i64, i64* %110, align 8, !tbaa !36
  %112 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  store i64 %111, i64* %112, align 8, !tbaa !36, !alias.scope !69
  %113 = bitcast %"class.std::__cxx11::basic_string"* %91 to %union.anon**
  store %union.anon* %97, %union.anon** %113, align 8, !tbaa !34
  store i64 0, i64* %110, align 8, !tbaa !36
  store i8 0, i8* %98, align 1, !tbaa !13
  %114 = load i8*, i8** %109, align 8, !tbaa !34
  %115 = load i64, i64* %112, align 8, !tbaa !36
  %116 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i8* %114, i64 %115)
          to label %117 unwind label %155

; <label>:117:                                    ; preds = %108
  %118 = load i8*, i8** %109, align 8, !tbaa !34
  %119 = bitcast %union.anon* %93 to i8*
  %120 = icmp eq i8* %118, %119
  br i1 %120, label %122, label %121

; <label>:121:                                    ; preds = %117
  call void @_ZdlPv(i8* %118) #3
  br label %122

; <label>:122:                                    ; preds = %117, %121
  %123 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %124 = load i8*, i8** %123, align 8, !tbaa !34
  %125 = bitcast %union.anon* %71 to i8*
  %126 = icmp eq i8* %124, %125
  br i1 %126, label %128, label %127

; <label>:127:                                    ; preds = %122
  call void @_ZdlPv(i8* %124) #3
  br label %128

; <label>:128:                                    ; preds = %122, %127
  %129 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %130 = load i8*, i8** %129, align 8, !tbaa !34
  %131 = bitcast %union.anon* %44 to i8*
  %132 = icmp eq i8* %130, %131
  br i1 %132, label %134, label %133

; <label>:133:                                    ; preds = %128
  call void @_ZdlPv(i8* %130) #3
  br label %134

; <label>:134:                                    ; preds = %128, %133
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %41) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %40) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %39) #3
  br label %182

; <label>:135:                                    ; preds = %2
  %136 = landingpad { i8*, i32 }
          cleanup
  %137 = extractvalue { i8*, i32 } %136, 0
  %138 = extractvalue { i8*, i32 } %136, 1
  br label %329

; <label>:139:                                    ; preds = %32, %30
  %140 = landingpad { i8*, i32 }
          cleanup
  %141 = extractvalue { i8*, i32 } %140, 0
  %142 = extractvalue { i8*, i32 } %140, 1
  br label %323

; <label>:143:                                    ; preds = %48
  %144 = landingpad { i8*, i32 }
          cleanup
  %145 = extractvalue { i8*, i32 } %144, 0
  %146 = extractvalue { i8*, i32 } %144, 1
  br label %179

; <label>:147:                                    ; preds = %63
  %148 = landingpad { i8*, i32 }
          cleanup
  %149 = extractvalue { i8*, i32 } %148, 0
  %150 = extractvalue { i8*, i32 } %148, 1
  br label %171

; <label>:151:                                    ; preds = %85
  %152 = landingpad { i8*, i32 }
          cleanup
  %153 = extractvalue { i8*, i32 } %152, 0
  %154 = extractvalue { i8*, i32 } %152, 1
  br label %163

; <label>:155:                                    ; preds = %108
  %156 = landingpad { i8*, i32 }
          cleanup
  %157 = extractvalue { i8*, i32 } %156, 0
  %158 = extractvalue { i8*, i32 } %156, 1
  %159 = load i8*, i8** %109, align 8, !tbaa !34
  %160 = bitcast %union.anon* %93 to i8*
  %161 = icmp eq i8* %159, %160
  br i1 %161, label %163, label %162

; <label>:162:                                    ; preds = %155
  call void @_ZdlPv(i8* %159) #3
  br label %163

; <label>:163:                                    ; preds = %162, %155, %151
  %164 = phi i8* [ %153, %151 ], [ %157, %155 ], [ %157, %162 ]
  %165 = phi i32 [ %154, %151 ], [ %158, %155 ], [ %158, %162 ]
  %166 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %167 = load i8*, i8** %166, align 8, !tbaa !34
  %168 = bitcast %union.anon* %71 to i8*
  %169 = icmp eq i8* %167, %168
  br i1 %169, label %171, label %170

; <label>:170:                                    ; preds = %163
  call void @_ZdlPv(i8* %167) #3
  br label %171

; <label>:171:                                    ; preds = %170, %163, %147
  %172 = phi i8* [ %149, %147 ], [ %164, %163 ], [ %164, %170 ]
  %173 = phi i32 [ %150, %147 ], [ %165, %163 ], [ %165, %170 ]
  %174 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %8, i64 0, i32 0, i32 0
  %175 = load i8*, i8** %174, align 8, !tbaa !34
  %176 = bitcast %union.anon* %44 to i8*
  %177 = icmp eq i8* %175, %176
  br i1 %177, label %179, label %178

; <label>:178:                                    ; preds = %171
  call void @_ZdlPv(i8* %175) #3
  br label %179

; <label>:179:                                    ; preds = %178, %171, %143
  %180 = phi i8* [ %145, %143 ], [ %172, %171 ], [ %172, %178 ]
  %181 = phi i32 [ %146, %143 ], [ %173, %171 ], [ %173, %178 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %41) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %40) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %39) #3
  br label %323

; <label>:182:                                    ; preds = %134, %34
  %183 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 2, i32 0, i32 1
  %184 = load i64, i64* %183, align 8, !tbaa !36
  %185 = icmp eq i64 %184, 0
  br i1 %185, label %322, label %186

; <label>:186:                                    ; preds = %182
  %187 = bitcast %"class.std::__cxx11::basic_string"* %9 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %187) #3
  %188 = bitcast %"class.std::__cxx11::basic_string"* %10 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %188) #3
  %189 = bitcast %"class.std::__cxx11::basic_string"* %11 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %189) #3
  %190 = getelementptr inbounds %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error", %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %1, i64 0, i32 2, i32 0, i32 0, i32 0
  %191 = load i8*, i8** %190, align 8, !tbaa !34, !noalias !72
  %192 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 2
  %193 = bitcast %"class.std::__cxx11::basic_string"* %11 to %union.anon**
  store %union.anon* %192, %union.anon** %193, align 8, !tbaa !32, !alias.scope !72
  %194 = bitcast i64* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %194) #3, !noalias !72
  store i64 %184, i64* %3, align 8, !tbaa !11, !noalias !72
  %195 = icmp ugt i64 %184, 15
  br i1 %195, label %196, label %202

; <label>:196:                                    ; preds = %186
  %197 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %11, i64* nonnull dereferenceable(8) %3, i64 0)
          to label %198 unwind label %283

; <label>:198:                                    ; preds = %196
  %199 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  store i8* %197, i8** %199, align 8, !tbaa !34, !alias.scope !72
  %200 = load i64, i64* %3, align 8, !tbaa !11, !noalias !72
  %201 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 2, i32 0
  store i64 %200, i64* %201, align 8, !tbaa !13, !alias.scope !72
  br label %208

; <label>:202:                                    ; preds = %186
  %203 = bitcast %union.anon* %192 to i8*
  %204 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  %205 = icmp eq i64 %184, 1
  br i1 %205, label %206, label %208

; <label>:206:                                    ; preds = %202
  %207 = load i8, i8* %191, align 1, !tbaa !13
  store i8 %207, i8* %203, align 8, !tbaa !13
  br label %211

; <label>:208:                                    ; preds = %198, %202
  %209 = phi i8* [ %197, %198 ], [ %203, %202 ]
  %210 = phi i8** [ %199, %198 ], [ %204, %202 ]
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %209, i8* %191, i64 %184, i32 1, i1 false) #3
  br label %211

; <label>:211:                                    ; preds = %208, %206
  %212 = phi i8** [ %210, %208 ], [ %204, %206 ]
  %213 = load i64, i64* %3, align 8, !tbaa !11, !noalias !72
  %214 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 1
  store i64 %213, i64* %214, align 8, !tbaa !36, !alias.scope !72
  %215 = load i8*, i8** %212, align 8, !tbaa !34, !alias.scope !72
  %216 = getelementptr inbounds i8, i8* %215, i64 %213
  store i8 0, i8* %216, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %194) #3, !noalias !72
  %217 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %11, i64 0, i64 0, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i64 0, i64 0), i64 2)
          to label %218 unwind label %287

; <label>:218:                                    ; preds = %211
  %219 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2
  %220 = bitcast %"class.std::__cxx11::basic_string"* %10 to %union.anon**
  store %union.anon* %219, %union.anon** %220, align 8, !tbaa !32, !alias.scope !77
  %221 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %217, i64 0, i32 0, i32 0
  %222 = load i8*, i8** %221, align 8, !tbaa !34
  %223 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %217, i64 0, i32 2
  %224 = bitcast %union.anon* %223 to i8*
  %225 = icmp eq i8* %222, %224
  br i1 %225, label %226, label %228

; <label>:226:                                    ; preds = %218
  %227 = bitcast %union.anon* %219 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %227, i8* nonnull %222, i64 16, i32 1, i1 false) #3
  br label %233

; <label>:228:                                    ; preds = %218
  %229 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 0, i32 0
  store i8* %222, i8** %229, align 8, !tbaa !34, !alias.scope !77
  %230 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %217, i64 0, i32 2, i32 0
  %231 = load i64, i64* %230, align 8, !tbaa !13
  %232 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 2, i32 0
  store i64 %231, i64* %232, align 8, !tbaa !13, !alias.scope !77
  br label %233

; <label>:233:                                    ; preds = %228, %226
  %234 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %217, i64 0, i32 1
  %235 = load i64, i64* %234, align 8, !tbaa !36
  %236 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 1
  store i64 %235, i64* %236, align 8, !tbaa !36, !alias.scope !77
  %237 = bitcast %"class.std::__cxx11::basic_string"* %217 to %union.anon**
  store %union.anon* %223, %union.anon** %237, align 8, !tbaa !34
  store i64 0, i64* %234, align 8, !tbaa !36
  store i8 0, i8* %224, align 1, !tbaa !13
  %238 = load i64, i64* %236, align 8, !tbaa !36, !noalias !80
  %239 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEmmmc(%"class.std::__cxx11::basic_string"* nonnull %10, i64 %238, i64 0, i64 1, i8 signext 93)
          to label %240 unwind label %291

; <label>:240:                                    ; preds = %233
  %241 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 2
  %242 = bitcast %"class.std::__cxx11::basic_string"* %9 to %union.anon**
  store %union.anon* %241, %union.anon** %242, align 8, !tbaa !32, !alias.scope !80
  %243 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %239, i64 0, i32 0, i32 0
  %244 = load i8*, i8** %243, align 8, !tbaa !34
  %245 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %239, i64 0, i32 2
  %246 = bitcast %union.anon* %245 to i8*
  %247 = icmp eq i8* %244, %246
  br i1 %247, label %248, label %251

; <label>:248:                                    ; preds = %240
  %249 = bitcast %union.anon* %241 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %249, i8* nonnull %244, i64 16, i32 1, i1 false) #3
  %250 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 0, i32 0
  br label %256

; <label>:251:                                    ; preds = %240
  %252 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 0, i32 0
  store i8* %244, i8** %252, align 8, !tbaa !34, !alias.scope !80
  %253 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %239, i64 0, i32 2, i32 0
  %254 = load i64, i64* %253, align 8, !tbaa !13
  %255 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 2, i32 0
  store i64 %254, i64* %255, align 8, !tbaa !13, !alias.scope !80
  br label %256

; <label>:256:                                    ; preds = %251, %248
  %257 = phi i8** [ %252, %251 ], [ %250, %248 ]
  %258 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %239, i64 0, i32 1
  %259 = load i64, i64* %258, align 8, !tbaa !36
  %260 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %9, i64 0, i32 1
  store i64 %259, i64* %260, align 8, !tbaa !36, !alias.scope !80
  %261 = bitcast %"class.std::__cxx11::basic_string"* %239 to %union.anon**
  store %union.anon* %245, %union.anon** %261, align 8, !tbaa !34
  store i64 0, i64* %258, align 8, !tbaa !36
  store i8 0, i8* %246, align 1, !tbaa !13
  %262 = load i8*, i8** %257, align 8, !tbaa !34
  %263 = load i64, i64* %260, align 8, !tbaa !36
  %264 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i8* %262, i64 %263)
          to label %265 unwind label %295

; <label>:265:                                    ; preds = %256
  %266 = load i8*, i8** %257, align 8, !tbaa !34
  %267 = bitcast %union.anon* %241 to i8*
  %268 = icmp eq i8* %266, %267
  br i1 %268, label %270, label %269

; <label>:269:                                    ; preds = %265
  call void @_ZdlPv(i8* %266) #3
  br label %270

; <label>:270:                                    ; preds = %265, %269
  %271 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 0, i32 0
  %272 = load i8*, i8** %271, align 8, !tbaa !34
  %273 = bitcast %union.anon* %219 to i8*
  %274 = icmp eq i8* %272, %273
  br i1 %274, label %276, label %275

; <label>:275:                                    ; preds = %270
  call void @_ZdlPv(i8* %272) #3
  br label %276

; <label>:276:                                    ; preds = %270, %275
  %277 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  %278 = load i8*, i8** %277, align 8, !tbaa !34
  %279 = bitcast %union.anon* %192 to i8*
  %280 = icmp eq i8* %278, %279
  br i1 %280, label %282, label %281

; <label>:281:                                    ; preds = %276
  call void @_ZdlPv(i8* %278) #3
  br label %282

; <label>:282:                                    ; preds = %276, %281
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %189) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %188) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %187) #3
  br label %322

; <label>:283:                                    ; preds = %196
  %284 = landingpad { i8*, i32 }
          cleanup
  %285 = extractvalue { i8*, i32 } %284, 0
  %286 = extractvalue { i8*, i32 } %284, 1
  br label %319

; <label>:287:                                    ; preds = %211
  %288 = landingpad { i8*, i32 }
          cleanup
  %289 = extractvalue { i8*, i32 } %288, 0
  %290 = extractvalue { i8*, i32 } %288, 1
  br label %311

; <label>:291:                                    ; preds = %233
  %292 = landingpad { i8*, i32 }
          cleanup
  %293 = extractvalue { i8*, i32 } %292, 0
  %294 = extractvalue { i8*, i32 } %292, 1
  br label %303

; <label>:295:                                    ; preds = %256
  %296 = landingpad { i8*, i32 }
          cleanup
  %297 = extractvalue { i8*, i32 } %296, 0
  %298 = extractvalue { i8*, i32 } %296, 1
  %299 = load i8*, i8** %257, align 8, !tbaa !34
  %300 = bitcast %union.anon* %241 to i8*
  %301 = icmp eq i8* %299, %300
  br i1 %301, label %303, label %302

; <label>:302:                                    ; preds = %295
  call void @_ZdlPv(i8* %299) #3
  br label %303

; <label>:303:                                    ; preds = %302, %295, %291
  %304 = phi i8* [ %293, %291 ], [ %297, %295 ], [ %297, %302 ]
  %305 = phi i32 [ %294, %291 ], [ %298, %295 ], [ %298, %302 ]
  %306 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %10, i64 0, i32 0, i32 0
  %307 = load i8*, i8** %306, align 8, !tbaa !34
  %308 = bitcast %union.anon* %219 to i8*
  %309 = icmp eq i8* %307, %308
  br i1 %309, label %311, label %310

; <label>:310:                                    ; preds = %303
  call void @_ZdlPv(i8* %307) #3
  br label %311

; <label>:311:                                    ; preds = %310, %303, %287
  %312 = phi i8* [ %289, %287 ], [ %304, %303 ], [ %304, %310 ]
  %313 = phi i32 [ %290, %287 ], [ %305, %303 ], [ %305, %310 ]
  %314 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %11, i64 0, i32 0, i32 0
  %315 = load i8*, i8** %314, align 8, !tbaa !34
  %316 = bitcast %union.anon* %192 to i8*
  %317 = icmp eq i8* %315, %316
  br i1 %317, label %319, label %318

; <label>:318:                                    ; preds = %311
  call void @_ZdlPv(i8* %315) #3
  br label %319

; <label>:319:                                    ; preds = %318, %311, %283
  %320 = phi i8* [ %285, %283 ], [ %312, %311 ], [ %312, %318 ]
  %321 = phi i32 [ %286, %283 ], [ %313, %311 ], [ %313, %318 ]
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %189) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %188) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %187) #3
  br label %323

; <label>:322:                                    ; preds = %182, %282
  ret void

; <label>:323:                                    ; preds = %319, %179, %139
  %324 = phi i8* [ %320, %319 ], [ %180, %179 ], [ %141, %139 ]
  %325 = phi i32 [ %321, %319 ], [ %181, %179 ], [ %142, %139 ]
  %326 = load i8*, i8** %18, align 8, !tbaa !34
  %327 = icmp eq i8* %326, %14
  br i1 %327, label %329, label %328

; <label>:328:                                    ; preds = %323
  call void @_ZdlPv(i8* %326) #3
  br label %329

; <label>:329:                                    ; preds = %328, %323, %135
  %330 = phi i8* [ %137, %135 ], [ %324, %323 ], [ %324, %328 ]
  %331 = phi i32 [ %138, %135 ], [ %325, %323 ], [ %325, %328 ]
  %332 = insertvalue { i8*, i32 } undef, i8* %330, 0
  %333 = insertvalue { i8*, i32 } %332, i32 %331, 1
  resume { i8*, i32 } %333
}

; Function Attrs: nounwind
declare void @_ZNSt12system_errorD2Ev(%"class.std::system_error"*) unnamed_addr #0

; Function Attrs: inlinehint uwtable
define linkonce_odr void @_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EERKS8_PKS5_(%"class.std::__cxx11::basic_string"* noalias sret, %"class.std::__cxx11::basic_string"* dereferenceable(32), i8*) local_unnamed_addr #13 comdat personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca i64, align 8
  %5 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %6 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %5, %union.anon** %6, align 8, !tbaa !32
  %7 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 0, i32 0
  %8 = load i8*, i8** %7, align 8, !tbaa !34
  %9 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %1, i64 0, i32 1
  %10 = load i64, i64* %9, align 8, !tbaa !36
  %11 = icmp ne i8* %8, null
  %12 = icmp eq i64 %10, 0
  %13 = or i1 %11, %12
  %14 = bitcast %union.anon* %5 to i8*
  br i1 %13, label %16, label %15

; <label>:15:                                     ; preds = %3
  tail call void @_ZSt19__throw_logic_errorPKc(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.4, i64 0, i64 0)) #17
  unreachable

; <label>:16:                                     ; preds = %3
  %17 = bitcast i64* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %17) #3
  store i64 %10, i64* %4, align 8, !tbaa !11
  %18 = icmp ugt i64 %10, 15
  br i1 %18, label %21, label %19

; <label>:19:                                     ; preds = %16
  %20 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  br label %26

; <label>:21:                                     ; preds = %16
  %22 = call i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %0, i64* nonnull dereferenceable(8) %4, i64 0)
  %23 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %22, i8** %23, align 8, !tbaa !34
  %24 = load i64, i64* %4, align 8, !tbaa !11
  %25 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %24, i64* %25, align 8, !tbaa !13
  br label %26

; <label>:26:                                     ; preds = %21, %19
  %27 = phi i8** [ %20, %19 ], [ %23, %21 ]
  %28 = phi i8* [ %14, %19 ], [ %22, %21 ]
  switch i64 %10, label %31 [
    i64 1, label %29
    i64 0, label %32
  ]

; <label>:29:                                     ; preds = %26
  %30 = load i8, i8* %8, align 1, !tbaa !13
  store i8 %30, i8* %28, align 1, !tbaa !13
  br label %32

; <label>:31:                                     ; preds = %26
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* %8, i64 %10, i32 1, i1 false) #3
  br label %32

; <label>:32:                                     ; preds = %26, %29, %31
  %33 = load i64, i64* %4, align 8, !tbaa !11
  %34 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 %33, i64* %34, align 8, !tbaa !36
  %35 = load i8*, i8** %27, align 8, !tbaa !34
  %36 = getelementptr inbounds i8, i8* %35, i64 %33
  store i8 0, i8* %36, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %17) #3
  %37 = call i64 @strlen(i8* %2) #3
  %38 = load i64, i64* %34, align 8, !tbaa !36
  %39 = sub i64 9223372036854775807, %38
  %40 = icmp ult i64 %39, %37
  br i1 %40, label %41, label %43

; <label>:41:                                     ; preds = %32
  invoke void @_ZSt20__throw_length_errorPKc(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i64 0, i64 0)) #17
          to label %42 unwind label %45

; <label>:42:                                     ; preds = %41
  unreachable

; <label>:43:                                     ; preds = %32
  %44 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"* nonnull %0, i8* %2, i64 %37)
          to label %52 unwind label %45

; <label>:45:                                     ; preds = %43, %41
  %46 = landingpad { i8*, i32 }
          cleanup
  %47 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  %48 = load i8*, i8** %47, align 8, !tbaa !34
  %49 = icmp eq i8* %48, %14
  br i1 %49, label %51, label %50

; <label>:50:                                     ; preds = %45
  call void @_ZdlPv(i8* %48) #3
  br label %51

; <label>:51:                                     ; preds = %45, %50
  resume { i8*, i32 } %46

; <label>:52:                                     ; preds = %43
  ret void
}

declare void @_ZNSt13runtime_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE(%"class.std::runtime_error"*, %"class.std::__cxx11::basic_string"* dereferenceable(32)) unnamed_addr #9

; Function Attrs: nounwind
declare i8* @_ZNKSt13runtime_error4whatEv(%"class.std::runtime_error"*) unnamed_addr #0

declare dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"*, i64, i64, i8*, i64) local_unnamed_addr #9

declare dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_appendEPKcm(%"class.std::__cxx11::basic_string"*, i8*, i64) local_unnamed_addr #9

; Function Attrs: noreturn
declare void @_ZSt20__throw_length_errorPKc(i8*) local_unnamed_addr #8

declare dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEmmmc(%"class.std::__cxx11::basic_string"*, i64, i64, i64, i8 signext) local_unnamed_addr #9

; Function Attrs: uwtable
define linkonce_odr i8* @_ZN3fse4mmapIhEEPT_iiimm(i32, i32, i32, i64, i64) local_unnamed_addr #4 comdat personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = tail call i8* @mmap(i8* null, i64 %3, i32 %1, i32 %2, i32 %0, i64 %4) #3
  %9 = icmp eq i8* %8, null
  br i1 %9, label %10, label %76

; <label>:10:                                     ; preds = %5
  %11 = tail call i8* @__cxa_allocate_exception(i64 192) #3
  %12 = bitcast i8* %11 to %"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*
  %13 = bitcast %"class.std::__cxx11::basic_string"* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %13) #3
  %14 = bitcast %"class.std::__cxx11::basic_string"* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 32, i8* nonnull %14) #3
  invoke void (%"class.std::__cxx11::basic_string"*, i32 (i8*, i64, i8*, %struct.__va_list_tag*)*, i64, i8*, ...) @_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z(%"class.std::__cxx11::basic_string"* nonnull sret %7, i32 (i8*, i64, i8*, %struct.__va_list_tag*)* nonnull @vsnprintf, i64 16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i64 0, i64 0), i32 %0)
          to label %15 unwind label %39

; <label>:15:                                     ; preds = %10
  %16 = invoke dereferenceable(32) %"class.std::__cxx11::basic_string"* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm(%"class.std::__cxx11::basic_string"* nonnull %7, i64 0, i64 0, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.11, i64 0, i64 0), i64 21)
          to label %17 unwind label %43

; <label>:17:                                     ; preds = %15
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2
  %19 = bitcast %"class.std::__cxx11::basic_string"* %6 to %union.anon**
  store %union.anon* %18, %union.anon** %19, align 8, !tbaa !32, !alias.scope !83
  %20 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %16, i64 0, i32 0, i32 0
  %21 = load i8*, i8** %20, align 8, !tbaa !34
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %16, i64 0, i32 2
  %23 = bitcast %union.anon* %22 to i8*
  %24 = icmp eq i8* %21, %23
  br i1 %24, label %25, label %27

; <label>:25:                                     ; preds = %17
  %26 = bitcast %union.anon* %18 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull %26, i8* nonnull %21, i64 16, i32 1, i1 false) #3
  br label %32

; <label>:27:                                     ; preds = %17
  %28 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  store i8* %21, i8** %28, align 8, !tbaa !34, !alias.scope !83
  %29 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %16, i64 0, i32 2, i32 0
  %30 = load i64, i64* %29, align 8, !tbaa !13
  %31 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 2, i32 0
  store i64 %30, i64* %31, align 8, !tbaa !13, !alias.scope !83
  br label %32

; <label>:32:                                     ; preds = %27, %25
  %33 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %16, i64 0, i32 1
  %34 = load i64, i64* %33, align 8, !tbaa !36
  %35 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 1
  store i64 %34, i64* %35, align 8, !tbaa !36, !alias.scope !83
  %36 = bitcast %"class.std::__cxx11::basic_string"* %16 to %union.anon**
  store %union.anon* %22, %union.anon** %36, align 8, !tbaa !34
  store i64 0, i64* %33, align 8, !tbaa !36
  store i8 0, i8* %23, align 1, !tbaa !13
  %37 = tail call dereferenceable(8) %"class.std::_V2::error_category"* @_ZNSt3_V215system_categoryEv() #16
  invoke void @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorC2ERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESt10error_code(%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"* %12, %"class.std::__cxx11::basic_string"* nonnull dereferenceable(32) %6, i32 0, %"class.std::_V2::error_category"* nonnull %37)
          to label %38 unwind label %47

; <label>:38:                                     ; preds = %32
  invoke void @__cxa_throw(i8* %11, i8* bitcast (i8** @_ZTINSt12experimental10filesystem2v17__cxx1116filesystem_errorE to i8*), i8* bitcast (void (%"class.std::experimental::filesystem::v1::__cxx11::filesystem_error"*)* @_ZNSt12experimental10filesystem2v17__cxx1116filesystem_errorD1Ev to i8*)) #17
          to label %77 unwind label %47

; <label>:39:                                     ; preds = %10
  %40 = landingpad { i8*, i32 }
          cleanup
  %41 = extractvalue { i8*, i32 } %40, 0
  %42 = extractvalue { i8*, i32 } %40, 1
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %14) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %13) #3
  br label %68

; <label>:43:                                     ; preds = %15
  %44 = landingpad { i8*, i32 }
          cleanup
  %45 = extractvalue { i8*, i32 } %44, 0
  %46 = extractvalue { i8*, i32 } %44, 1
  br label %57

; <label>:47:                                     ; preds = %38, %32
  %48 = phi i1 [ false, %38 ], [ true, %32 ]
  %49 = landingpad { i8*, i32 }
          cleanup
  %50 = extractvalue { i8*, i32 } %49, 0
  %51 = extractvalue { i8*, i32 } %49, 1
  %52 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %6, i64 0, i32 0, i32 0
  %53 = load i8*, i8** %52, align 8, !tbaa !34
  %54 = bitcast %union.anon* %18 to i8*
  %55 = icmp eq i8* %53, %54
  br i1 %55, label %57, label %56

; <label>:56:                                     ; preds = %47
  call void @_ZdlPv(i8* %53) #3
  br label %57

; <label>:57:                                     ; preds = %56, %47, %43
  %58 = phi i8* [ %45, %43 ], [ %50, %47 ], [ %50, %56 ]
  %59 = phi i32 [ %46, %43 ], [ %51, %47 ], [ %51, %56 ]
  %60 = phi i1 [ true, %43 ], [ %48, %47 ], [ %48, %56 ]
  %61 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 0, i32 0
  %62 = load i8*, i8** %61, align 8, !tbaa !34
  %63 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %7, i64 0, i32 2
  %64 = bitcast %union.anon* %63 to i8*
  %65 = icmp eq i8* %62, %64
  br i1 %65, label %67, label %66

; <label>:66:                                     ; preds = %57
  call void @_ZdlPv(i8* %62) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %14) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %13) #3
  br i1 %60, label %68, label %71

; <label>:67:                                     ; preds = %57
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %14) #3
  call void @llvm.lifetime.end.p0i8(i64 32, i8* nonnull %13) #3
  br i1 %60, label %68, label %71

; <label>:68:                                     ; preds = %66, %39, %67
  %69 = phi i32 [ %42, %39 ], [ %59, %67 ], [ %59, %66 ]
  %70 = phi i8* [ %41, %39 ], [ %58, %67 ], [ %58, %66 ]
  call void @__cxa_free_exception(i8* %11) #3
  br label %71

; <label>:71:                                     ; preds = %66, %68, %67
  %72 = phi i32 [ %69, %68 ], [ %59, %67 ], [ %59, %66 ]
  %73 = phi i8* [ %70, %68 ], [ %58, %67 ], [ %58, %66 ]
  %74 = insertvalue { i8*, i32 } undef, i8* %73, 0
  %75 = insertvalue { i8*, i32 } %74, i32 %72, 1
  resume { i8*, i32 } %75

; <label>:76:                                     ; preds = %5
  ret i8* %8

; <label>:77:                                     ; preds = %38
  unreachable
}

; Function Attrs: nounwind
declare i8* @mmap(i8*, i64, i32, i32, i32, i64) local_unnamed_addr #0

; Function Attrs: uwtable
define linkonce_odr void @_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z(%"class.std::__cxx11::basic_string"* noalias sret, i32 (i8*, i64, i8*, %struct.__va_list_tag*)*, i64, i8*, ...) local_unnamed_addr #4 comdat personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %5 = alloca i64, align 8
  %6 = alloca [1 x %struct.__va_list_tag], align 16
  %7 = alloca i8, i64 %2, align 16
  %8 = bitcast [1 x %struct.__va_list_tag]* %6 to i8*
  call void @llvm.lifetime.start.p0i8(i64 24, i8* nonnull %8) #3
  %9 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %6, i64 0, i64 0
  call void @llvm.va_start(i8* nonnull %8)
  %10 = call i32 %1(i8* nonnull %7, i64 %2, i8* %3, %struct.__va_list_tag* nonnull %9)
  call void @llvm.va_end(i8* nonnull %8)
  %11 = sext i32 %10 to i64
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2
  %13 = bitcast %"class.std::__cxx11::basic_string"* %0 to %union.anon**
  store %union.anon* %12, %union.anon** %13, align 8, !tbaa !32
  %14 = bitcast i64* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %14) #3
  store i64 %11, i64* %5, align 8, !tbaa !11
  %15 = icmp ugt i32 %10, 15
  br i1 %15, label %19, label %16

; <label>:16:                                     ; preds = %4
  %17 = bitcast %union.anon* %12 to i8*
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  br label %25

; <label>:19:                                     ; preds = %4
  %20 = invoke i8* @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(%"class.std::__cxx11::basic_string"* nonnull %0, i64* nonnull dereferenceable(8) %5, i64 0)
          to label %21 unwind label %36

; <label>:21:                                     ; preds = %19
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 0, i32 0
  store i8* %20, i8** %22, align 8, !tbaa !34
  %23 = load i64, i64* %5, align 8, !tbaa !11
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 2, i32 0
  store i64 %23, i64* %24, align 8, !tbaa !13
  br label %25

; <label>:25:                                     ; preds = %21, %16
  %26 = phi i8** [ %18, %16 ], [ %22, %21 ]
  %27 = phi i8* [ %17, %16 ], [ %20, %21 ]
  switch i64 %11, label %30 [
    i64 1, label %28
    i64 0, label %31
  ]

; <label>:28:                                     ; preds = %25
  %29 = load i8, i8* %7, align 16, !tbaa !13
  store i8 %29, i8* %27, align 1, !tbaa !13
  br label %31

; <label>:30:                                     ; preds = %25
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %27, i8* nonnull %7, i64 %11, i32 1, i1 false) #3
  br label %31

; <label>:31:                                     ; preds = %30, %28, %25
  %32 = load i64, i64* %5, align 8, !tbaa !11
  %33 = getelementptr inbounds %"class.std::__cxx11::basic_string", %"class.std::__cxx11::basic_string"* %0, i64 0, i32 1
  store i64 %32, i64* %33, align 8, !tbaa !36
  %34 = load i8*, i8** %26, align 8, !tbaa !34
  %35 = getelementptr inbounds i8, i8* %34, i64 %32
  store i8 0, i8* %35, align 1, !tbaa !13
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %14) #3
  call void @llvm.lifetime.end.p0i8(i64 24, i8* nonnull %8) #3
  ret void

; <label>:36:                                     ; preds = %19
  %37 = landingpad { i8*, i32 }
          cleanup
  call void @llvm.lifetime.end.p0i8(i64 24, i8* nonnull %8) #3
  resume { i8*, i32 } %37
}

; Function Attrs: nounwind
declare i32 @vsnprintf(i8* nocapture, i64, i8* nocapture readonly, %struct.__va_list_tag*) #0

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #3

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #3

; Function Attrs: nounwind
declare i32 @munmap(i8*, i64) local_unnamed_addr #0

; Function Attrs: uwtable
define internal fastcc void @_ZN12_GLOBAL__N_121BranchCoverageRuntime17onNonSingleBranchEm(%"class.(anonymous namespace)::BranchCoverageRuntime"* nocapture, i64) unnamed_addr #4 align 2 {
  %3 = getelementptr %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 1, i32 2
  %4 = load i64, i64* %3, align 8, !tbaa !21
  %5 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %6 = icmp ugt i64 %5, %4
  br i1 %6, label %7, label %10

; <label>:7:                                      ; preds = %2
  %8 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 5
  %9 = load i8*, i8** %8, align 8, !tbaa !24
  br label %60

; <label>:10:                                     ; preds = %2
  %11 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE, align 8, !tbaa !11
  %12 = icmp eq i64 %4, %11
  %13 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 3
  %14 = load i8*, i8** %13, align 8, !tbaa !10
  %15 = tail call i32 @munmap(i8* %14, i64 %5) #3
  %16 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 4
  %17 = bitcast i8** %16 to i64*
  %18 = load i64, i64* %17, align 8, !tbaa !12
  %19 = bitcast i8** %13 to i64*
  store i64 %18, i64* %19, align 8, !tbaa !10
  %20 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 0
  %21 = load i32, i32* %20, align 8, !tbaa !25
  %22 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %23 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 2
  %24 = load i64, i64* %23, align 8, !tbaa !26
  %25 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %21, i32 2, i32 1, i64 %22, i64 %24)
  store i8* %25, i8** %16, align 8, !tbaa !12
  %26 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %27 = load i64, i64* %23, align 8, !tbaa !26
  %28 = add i64 %27, %26
  store i64 %28, i64* %23, align 8, !tbaa !26
  %29 = load i64, i64* %19, align 8, !tbaa !10
  %30 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 5
  %31 = bitcast i8** %30 to i64*
  store i64 %29, i64* %31, align 8, !tbaa !24
  %32 = bitcast i64* %3 to <2 x i64>*
  %33 = load <2 x i64>, <2 x i64>* %32, align 8, !tbaa !11
  %34 = insertelement <2 x i64> undef, i64 %26, i32 0
  %35 = shufflevector <2 x i64> %34, <2 x i64> undef, <2 x i32> zeroinitializer
  %36 = sub <2 x i64> %33, %35
  %37 = bitcast i64* %3 to <2 x i64>*
  store <2 x i64> %36, <2 x i64>* %37, align 8, !tbaa !11
  %38 = inttoptr i64 %29 to i8*
  %39 = extractelement <2 x i64> %36, i32 0
  br i1 %12, label %40, label %60

; <label>:40:                                     ; preds = %10
  %41 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %42 = tail call i32 @munmap(i8* %38, i64 %41) #3
  %43 = load i64, i64* %17, align 8, !tbaa !12
  store i64 %43, i64* %19, align 8, !tbaa !10
  %44 = load i32, i32* %20, align 8, !tbaa !25
  %45 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %46 = load i64, i64* %23, align 8, !tbaa !26
  %47 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %44, i32 2, i32 1, i64 %45, i64 %46)
  store i8* %47, i8** %16, align 8, !tbaa !12
  %48 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %49 = load i64, i64* %23, align 8, !tbaa !26
  %50 = add i64 %49, %48
  store i64 %50, i64* %23, align 8, !tbaa !26
  %51 = load i64, i64* %19, align 8, !tbaa !10
  store i64 %51, i64* %31, align 8, !tbaa !24
  %52 = bitcast i64* %3 to <2 x i64>*
  %53 = load <2 x i64>, <2 x i64>* %52, align 8, !tbaa !11
  %54 = insertelement <2 x i64> undef, i64 %48, i32 0
  %55 = shufflevector <2 x i64> %54, <2 x i64> undef, <2 x i32> zeroinitializer
  %56 = sub <2 x i64> %53, %55
  %57 = bitcast i64* %3 to <2 x i64>*
  store <2 x i64> %56, <2 x i64>* %57, align 8, !tbaa !11
  %58 = inttoptr i64 %51 to i8*
  %59 = extractelement <2 x i64> %56, i32 0
  br label %60

; <label>:60:                                     ; preds = %7, %10, %40
  %61 = phi i8** [ %8, %7 ], [ %30, %10 ], [ %30, %40 ]
  %62 = phi i8* [ %9, %7 ], [ %38, %10 ], [ %58, %40 ]
  %63 = phi i64 [ %4, %7 ], [ %39, %10 ], [ %59, %40 ]
  %64 = trunc i64 %1 to i8
  %65 = getelementptr inbounds i8, i8* %62, i64 %63
  store i8 %64, i8* %65, align 1, !tbaa !13
  %66 = lshr i64 %1, 8
  %67 = trunc i64 %66 to i8
  %68 = load i8*, i8** %61, align 8, !tbaa !24
  %69 = add i64 %63, 1
  %70 = getelementptr inbounds i8, i8* %68, i64 %69
  store i8 %67, i8* %70, align 1, !tbaa !13
  %71 = lshr i64 %1, 16
  %72 = trunc i64 %71 to i8
  %73 = load i8*, i8** %61, align 8, !tbaa !24
  %74 = add i64 %63, 2
  %75 = getelementptr inbounds i8, i8* %73, i64 %74
  store i8 %72, i8* %75, align 1, !tbaa !13
  %76 = lshr i64 %1, 24
  %77 = trunc i64 %76 to i8
  %78 = load i8*, i8** %61, align 8, !tbaa !24
  %79 = add i64 %63, 3
  %80 = getelementptr inbounds i8, i8* %78, i64 %79
  store i8 %77, i8* %80, align 1, !tbaa !13
  %81 = lshr i64 %1, 32
  %82 = trunc i64 %81 to i8
  %83 = load i8*, i8** %61, align 8, !tbaa !24
  %84 = add i64 %63, 4
  %85 = getelementptr inbounds i8, i8* %83, i64 %84
  store i8 %82, i8* %85, align 1, !tbaa !13
  %86 = lshr i64 %1, 40
  %87 = trunc i64 %86 to i8
  %88 = load i8*, i8** %61, align 8, !tbaa !24
  %89 = add i64 %63, 5
  %90 = getelementptr inbounds i8, i8* %88, i64 %89
  store i8 %87, i8* %90, align 1, !tbaa !13
  %91 = lshr i64 %1, 48
  %92 = trunc i64 %91 to i8
  %93 = load i8*, i8** %61, align 8, !tbaa !24
  %94 = add i64 %63, 6
  %95 = getelementptr inbounds i8, i8* %93, i64 %94
  store i8 %92, i8* %95, align 1, !tbaa !13
  %96 = lshr i64 %1, 56
  %97 = trunc i64 %96 to i8
  %98 = load i8*, i8** %61, align 8, !tbaa !24
  %99 = add i64 %63, 7
  %100 = getelementptr inbounds i8, i8* %98, i64 %99
  store i8 %97, i8* %100, align 1, !tbaa !13
  %101 = add i64 %63, 8
  store i64 %101, i64* %3, align 8, !tbaa !21
  %102 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %103 = icmp ugt i64 %102, %101
  br i1 %103, label %104, label %106

; <label>:104:                                    ; preds = %60
  %105 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 1, i32 3
  br label %155

; <label>:106:                                    ; preds = %60
  %107 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE, align 8, !tbaa !11
  %108 = icmp eq i64 %101, %107
  %109 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 3
  %110 = load i8*, i8** %109, align 8, !tbaa !10
  %111 = tail call i32 @munmap(i8* %110, i64 %102) #3
  %112 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 4
  %113 = bitcast i8** %112 to i64*
  %114 = load i64, i64* %113, align 8, !tbaa !12
  %115 = bitcast i8** %109 to i64*
  store i64 %114, i64* %115, align 8, !tbaa !10
  %116 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 0
  %117 = load i32, i32* %116, align 8, !tbaa !25
  %118 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %119 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 2, i32 2
  %120 = load i64, i64* %119, align 8, !tbaa !26
  %121 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %117, i32 2, i32 1, i64 %118, i64 %120)
  store i8* %121, i8** %112, align 8, !tbaa !12
  %122 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %123 = load i64, i64* %119, align 8, !tbaa !26
  %124 = add i64 %123, %122
  store i64 %124, i64* %119, align 8, !tbaa !26
  %125 = load i64, i64* %115, align 8, !tbaa !10
  %126 = bitcast i8** %61 to i64*
  store i64 %125, i64* %126, align 8, !tbaa !24
  %127 = getelementptr inbounds %"class.(anonymous namespace)::BranchCoverageRuntime", %"class.(anonymous namespace)::BranchCoverageRuntime"* %0, i64 0, i32 1, i32 3
  %128 = bitcast i64* %3 to <2 x i64>*
  %129 = load <2 x i64>, <2 x i64>* %128, align 8, !tbaa !11
  %130 = insertelement <2 x i64> undef, i64 %122, i32 0
  %131 = shufflevector <2 x i64> %130, <2 x i64> undef, <2 x i32> zeroinitializer
  %132 = sub <2 x i64> %129, %131
  %133 = bitcast i64* %3 to <2 x i64>*
  store <2 x i64> %132, <2 x i64>* %133, align 8, !tbaa !11
  %134 = extractelement <2 x i64> %132, i32 0
  br i1 %108, label %135, label %155

; <label>:135:                                    ; preds = %106
  %136 = inttoptr i64 %125 to i8*
  %137 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %138 = tail call i32 @munmap(i8* %136, i64 %137) #3
  %139 = load i64, i64* %113, align 8, !tbaa !12
  store i64 %139, i64* %115, align 8, !tbaa !10
  %140 = load i32, i32* %116, align 8, !tbaa !25
  %141 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %142 = load i64, i64* %119, align 8, !tbaa !26
  %143 = tail call i8* @_ZN3fse4mmapIhEEPT_iiimm(i32 %140, i32 2, i32 1, i64 %141, i64 %142)
  store i8* %143, i8** %112, align 8, !tbaa !12
  %144 = load i64, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %145 = load i64, i64* %119, align 8, !tbaa !26
  %146 = add i64 %145, %144
  store i64 %146, i64* %119, align 8, !tbaa !26
  %147 = load i64, i64* %115, align 8, !tbaa !10
  store i64 %147, i64* %126, align 8, !tbaa !24
  %148 = bitcast i64* %3 to <2 x i64>*
  %149 = load <2 x i64>, <2 x i64>* %148, align 8, !tbaa !11
  %150 = insertelement <2 x i64> undef, i64 %144, i32 0
  %151 = shufflevector <2 x i64> %150, <2 x i64> undef, <2 x i32> zeroinitializer
  %152 = sub <2 x i64> %149, %151
  %153 = bitcast i64* %3 to <2 x i64>*
  store <2 x i64> %152, <2 x i64>* %153, align 8, !tbaa !11
  %154 = extractelement <2 x i64> %152, i32 0
  br label %155

; <label>:155:                                    ; preds = %104, %106, %135
  %156 = phi i64* [ %105, %104 ], [ %127, %106 ], [ %127, %135 ]
  %157 = phi i64 [ %101, %104 ], [ %134, %106 ], [ %154, %135 ]
  store i64 %157, i64* %156, align 8, !tbaa !17
  ret void
}

; Function Attrs: nounwind uwtable
define internal void @_GLOBAL__sub_I_BranchCoverageRuntime.cpp() #2 section ".text.startup" personality i32 (...)* @__gxx_personality_v0 {
  %1 = tail call i64 @sysconf(i32 30) #3
  store i64 %1, i64* @_ZN3fseL8pageSizeE, align 8, !tbaa !11
  %2 = tail call {}* @llvm.invariant.start.p0i8(i64 8, i8* bitcast (i64* @_ZN3fseL8pageSizeE to i8*)) #3
  store i64 %1, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8pageSizeE, align 8, !tbaa !11
  %3 = tail call {}* @llvm.invariant.start.p0i8(i64 8, i8* bitcast (i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime8pageSizeE to i8*)) #3
  %4 = icmp ugt i64 %1, 4097
  br i1 %4, label %12, label %5

; <label>:5:                                      ; preds = %0
  br label %6

; <label>:6:                                      ; preds = %5, %6
  %7 = phi i64 [ %9, %6 ], [ 4097, %5 ]
  %8 = phi i64 [ %10, %6 ], [ %1, %5 ]
  %9 = sub i64 %7, %1
  %10 = add i64 %8, %1
  %11 = icmp ult i64 %9, %1
  br i1 %11, label %12, label %6

; <label>:12:                                     ; preds = %6, %0
  %13 = phi i64 [ %1, %0 ], [ %10, %6 ]
  store i64 %13, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE, align 8, !tbaa !11
  %14 = tail call {}* @llvm.invariant.start.p0i8(i64 8, i8* bitcast (i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime13pageChunkSizeE to i8*)) #3
  %15 = shl i64 %13, 1
  store i64 %15, i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE, align 8, !tbaa !11
  %16 = tail call {}* @llvm.invariant.start.p0i8(i64 8, i8* bitcast (i64* @_ZN12_GLOBAL__N_121BranchCoverageRuntime10bufferSizeE to i8*)) #3
  store %"class.(anonymous namespace)::BranchCoverageRuntime"* null, %"class.(anonymous namespace)::BranchCoverageRuntime"** getelementptr inbounds (%"class.std::unique_ptr", %"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE, i64 0, i32 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !86
  %17 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::unique_ptr"*)* @_ZNSt10unique_ptrIN12_GLOBAL__N_121BranchCoverageRuntimeESt14default_deleteIS1_EED2Ev to void (i8*)*), i8* bitcast (%"class.std::unique_ptr"* @_ZN12_GLOBAL__N_121BranchCoverageRuntime9_instanceE to i8*), i8* nonnull @__dso_handle) #3
  ret void
}

attributes #0 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noinline noreturn nounwind }
attributes #6 = { nobuiltin "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nobuiltin nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #10 = { argmemonly nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #11 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #12 = { nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #13 = { inlinehint uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #14 = { builtin nounwind }
attributes #15 = { builtin }
attributes #16 = { nounwind readnone }
attributes #17 = { noreturn }
attributes #18 = { noreturn nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20181018153226.114 (branches/release_60)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"any pointer", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C++ TBAA"}
!6 = !{!7, !3, i64 8}
!7 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime10MMapOutputE", !8, i64 0, !3, i64 8, !9, i64 16, !3, i64 24, !3, i64 32, !3, i64 40}
!8 = !{!"int", !4, i64 0}
!9 = !{!"long", !4, i64 0}
!10 = !{!7, !3, i64 24}
!11 = !{!9, !9, i64 0}
!12 = !{!7, !3, i64 32}
!13 = !{!4, !4, i64 0}
!14 = !{!15, !9, i64 8}
!15 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntime7IndicesE", !4, i64 0, !16, i64 2, !9, i64 8, !9, i64 16}
!16 = !{!"short", !4, i64 0}
!17 = !{!15, !9, i64 16}
!18 = !{!19, !4, i64 24}
!19 = !{!"_ZTSN12_GLOBAL__N_121BranchCoverageRuntimeE", !4, i64 0, !15, i64 24, !7, i64 48}
!20 = !{!19, !3, i64 88}
!21 = !{!19, !9, i64 32}
!22 = !{!19, !16, i64 26}
!23 = !{!19, !9, i64 40}
!24 = !{!7, !3, i64 40}
!25 = !{!7, !8, i64 0}
!26 = !{!7, !9, i64 16}
!27 = !{!15, !16, i64 2}
!28 = !{!19, !3, i64 56}
!29 = !{!30}
!30 = distinct !{!30, !31, !"_ZSt11make_uniqueIN12_GLOBAL__N_121BranchCoverageRuntimeEJEENSt9_MakeUniqIT_E15__single_objectEDpOT0_: argument 0"}
!31 = distinct !{!31, !"_ZSt11make_uniqueIN12_GLOBAL__N_121BranchCoverageRuntimeEJEENSt9_MakeUniqIT_E15__single_objectEDpOT0_"}
!32 = !{!33, !3, i64 0}
!33 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderE", !3, i64 0}
!34 = !{!35, !3, i64 0}
!35 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE", !33, i64 0, !9, i64 8, !4, i64 16}
!36 = !{!35, !9, i64 8}
!37 = !{!38, !30}
!38 = distinct !{!38, !39, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime28getOutputPathFromEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE: argument 0"}
!39 = distinct !{!39, !"_ZN12_GLOBAL__N_121BranchCoverageRuntime28getOutputPathFromEnvironmentERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"}
!40 = !{!41, !43, !30}
!41 = distinct !{!41, !42, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_: argument 0"}
!42 = distinct !{!42, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_"}
!43 = distinct !{!43, !44, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv: argument 0"}
!44 = distinct !{!44, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv"}
!45 = !{!41, !43}
!46 = !{!47, !3, i64 0}
!47 = !{!"_ZTSSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EE", !48, i64 0}
!48 = !{!"_ZTSNSt12_Vector_baseINSt12experimental10filesystem2v17__cxx114path5_CmptESaIS5_EE12_Vector_implE", !3, i64 0, !3, i64 8, !3, i64 16}
!49 = !{!47, !3, i64 8}
!50 = !{!51}
!51 = distinct !{!51, !52, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertEPcNS3_17__null_terminatedE: argument 0"}
!52 = distinct !{!52, !"_ZNSt12experimental10filesystem2v17__cxx114path10_S_convertEPcNS3_17__null_terminatedE"}
!53 = !{!54, !54, i64 0}
!54 = !{!"vtable pointer", !5, i64 0}
!55 = !{!56}
!56 = distinct !{!56, !57, !"_ZNKSt10error_code7messageB5cxx11Ev: argument 0"}
!57 = distinct !{!57, !"_ZNKSt10error_code7messageB5cxx11Ev"}
!58 = !{!59}
!59 = distinct !{!59, !60, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_: argument 0"}
!60 = distinct !{!60, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S9_"}
!61 = !{!62, !64}
!62 = distinct !{!62, !63, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_: argument 0"}
!63 = distinct !{!63, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_"}
!64 = distinct !{!64, !65, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv: argument 0"}
!65 = distinct !{!65, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv"}
!66 = !{!67}
!67 = distinct !{!67, !68, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_: argument 0"}
!68 = distinct !{!68, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_"}
!69 = !{!70}
!70 = distinct !{!70, !71, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_: argument 0"}
!71 = distinct !{!71, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_"}
!72 = !{!73, !75}
!73 = distinct !{!73, !74, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_: argument 0"}
!74 = distinct !{!74, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringIcSt11char_traitsIcESaIcEEENSt7__cxx1112basic_stringIT_T0_T1_EERKSC_"}
!75 = distinct !{!75, !76, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv: argument 0"}
!76 = distinct !{!76, !"_ZNKSt12experimental10filesystem2v17__cxx114path6stringEv"}
!77 = !{!78}
!78 = distinct !{!78, !79, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_: argument 0"}
!79 = distinct !{!79, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_"}
!80 = !{!81}
!81 = distinct !{!81, !82, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_: argument 0"}
!82 = distinct !{!82, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_"}
!83 = !{!84}
!84 = distinct !{!84, !85, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_: argument 0"}
!85 = distinct !{!85, !"_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEPKS5_OS8_"}
!86 = !{!87, !3, i64 0}
!87 = !{!"_ZTSSt10_Head_baseILm0EPN12_GLOBAL__N_121BranchCoverageRuntimeELb0EE", !3, i64 0}
