; ModuleID = 'staticConstructors.cpp'
source_filename = "staticConstructors.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%class.A = type { i8 }

$_ZN1AC2Ev = comdat any

$_ZN1AD2Ev = comdat any

@_ZN1A11initializedE = global i8 0, align 1
@a = global %class.A zeroinitializer, align 1
@__dso_handle = external hidden global i8
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_staticConstructors.cpp, i8* null }]

; Function Attrs: noinline uwtable
define internal void @__cxx_global_var_init() #0 section ".text.startup" {
  call void @_ZN1AC2Ev(%class.A* @a) #2
  %1 = call i32 @__cxa_atexit(void (i8*)* bitcast (void (%class.A*)* @_ZN1AD2Ev to void (i8*)*), i8* getelementptr inbounds (%class.A, %class.A* @a, i32 0, i32 0), i8* @__dso_handle) #2
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr void @_ZN1AC2Ev(%class.A*) unnamed_addr #1 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  store i8 1, i8* @_ZN1A11initializedE, align 1
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr void @_ZN1AD2Ev(%class.A*) unnamed_addr #1 comdat align 2 {
  %2 = alloca %class.A*, align 8
  store %class.A* %0, %class.A** %2, align 8
  %3 = load %class.A*, %class.A** %2, align 8
  store i8 0, i8* @_ZN1A11initializedE, align 1
  ret void
}

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) #2

; Function Attrs: noinline norecurse nounwind optnone uwtable
define i32 @main() #3 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = load i8, i8* @_ZN1A11initializedE, align 1
  %3 = trunc i8 %2 to i1
  %4 = zext i1 %3 to i32
  ret i32 %4
}

; Function Attrs: noinline uwtable
define internal void @_GLOBAL__sub_I_staticConstructors.cpp() #0 section ".text.startup" {
  call void @__cxx_global_var_init()
  ret void
}

attributes #0 = { noinline uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }
attributes #3 = { noinline norecurse nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 6.0.1-svn334776-1~exp1~20181018153226.114 (branches/release_60)"}
