#include <cstdio>
#include <iostream>

class A;

extern "C"
void h(A& a) noexcept;

class A {

public:
	
	virtual char f() noexcept = 0;
	
	virtual long g() noexcept = 0;
	
	void h() noexcept {
	    ::h(*this);
	}
	
	virtual void f0() noexcept {}
	/*
	virtual void f1() noexcept {}
	virtual void f2() noexcept {}
	virtual void f3() noexcept {}
	virtual void f4() noexcept {}
	virtual void f5() noexcept {}
	virtual void f6() noexcept {}
	virtual void f7() noexcept {}
	virtual void f8() noexcept {}
	virtual void f9() noexcept {}
	virtual void f10() noexcept {}
	virtual void f11() noexcept {}
	virtual void f12() noexcept {}
	virtual void f13() noexcept {}
	virtual void f14() noexcept {}
	virtual void f15() noexcept {}
	virtual void f16() noexcept {}
	virtual void f17() noexcept {}
	virtual void f18() noexcept {}
	virtual void f19() noexcept {}
	virtual void f20() noexcept {}
	virtual void f21() noexcept {}
	virtual void f22() noexcept {}
	virtual void f23() noexcept {}
	virtual void f24() noexcept {}
	virtual void f25() noexcept {}
	virtual void f26() noexcept {}
	virtual void f27() noexcept {}
	virtual void f28() noexcept {}
	virtual void f29() noexcept {}
	virtual void f30() noexcept {}
	virtual void f31() noexcept {}
	virtual void f32() noexcept {}
	virtual void f33() noexcept {}
	virtual void f34() noexcept {}
	virtual void f35() noexcept {}
	virtual void f36() noexcept {}
	virtual void f37() noexcept {}
	virtual void f38() noexcept {}
	virtual void f39() noexcept {}
	virtual void f40() noexcept {}
	virtual void f41() noexcept {}
	virtual void f42() noexcept {}
	virtual void f43() noexcept {}
	virtual void f44() noexcept {}
	virtual void f45() noexcept {}
	virtual void f46() noexcept {}
	virtual void f47() noexcept {}
	virtual void f48() noexcept {}
	virtual void f49() noexcept {}
	virtual void f50() noexcept {}
	virtual void f51() noexcept {}
	virtual void f52() noexcept {}
	virtual void f53() noexcept {}
	virtual void f54() noexcept {}
	virtual void f55() noexcept {}
	virtual void f56() noexcept {}
	virtual void f57() noexcept {}
	virtual void f58() noexcept {}
	virtual void f59() noexcept {}
	virtual void f60() noexcept {}
	virtual void f61() noexcept {}
	virtual void f62() noexcept {}
	virtual void f63() noexcept {}
	virtual void f64() noexcept {}
	virtual void f65() noexcept {}
	virtual void f66() noexcept {}
	virtual void f67() noexcept {}
	virtual void f68() noexcept {}
	virtual void f69() noexcept {}
	virtual void f70() noexcept {}
	virtual void f71() noexcept {}
	virtual void f72() noexcept {}
	virtual void f73() noexcept {}
	virtual void f74() noexcept {}
	virtual void f75() noexcept {}
	virtual void f76() noexcept {}
	virtual void f77() noexcept {}
	virtual void f78() noexcept {}
	virtual void f79() noexcept {}
	virtual void f80() noexcept {}
	virtual void f81() noexcept {}
	virtual void f82() noexcept {}
	virtual void f83() noexcept {}
	virtual void f84() noexcept {}
	virtual void f85() noexcept {}
	virtual void f86() noexcept {}
	virtual void f87() noexcept {}
	virtual void f88() noexcept {}
	virtual void f89() noexcept {}
	virtual void f90() noexcept {}
	virtual void f91() noexcept {}
	virtual void f92() noexcept {}
	virtual void f93() noexcept {}
	virtual void f94() noexcept {}
	virtual void f95() noexcept {}
	virtual void f96() noexcept {}
	virtual void f97() noexcept {}
	virtual void f98() noexcept {}
	virtual void f99() noexcept {}
	virtual void f100() noexcept {}
	virtual void f101() noexcept {}
	virtual void f102() noexcept {}
	virtual void f103() noexcept {}
	virtual void f104() noexcept {}
	virtual void f105() noexcept {}
	virtual void f106() noexcept {}
	virtual void f107() noexcept {}
	virtual void f108() noexcept {}
	virtual void f109() noexcept {}
	virtual void f110() noexcept {}
	virtual void f111() noexcept {}
	virtual void f112() noexcept {}
	virtual void f113() noexcept {}
	virtual void f114() noexcept {}
	virtual void f115() noexcept {}
	virtual void f116() noexcept {}
	virtual void f117() noexcept {}
	virtual void f118() noexcept {}
	virtual void f119() noexcept {}
	virtual void f120() noexcept {}
	virtual void f121() noexcept {}
	virtual void f122() noexcept {}
	virtual void f123() noexcept {}
	virtual void f124() noexcept {}
	virtual void f125() noexcept {}
	virtual void f126() noexcept {}
	virtual void f127() noexcept {}
	virtual void f128() noexcept {}
	virtual void f129() noexcept {}
	virtual void f130() noexcept {}
	virtual void f131() noexcept {}
	virtual void f132() noexcept {}
	virtual void f133() noexcept {}
	virtual void f134() noexcept {}
	virtual void f135() noexcept {}
	virtual void f136() noexcept {}
	virtual void f137() noexcept {}
	virtual void f138() noexcept {}
	virtual void f139() noexcept {}
	virtual void f140() noexcept {}
	virtual void f141() noexcept {}
	virtual void f142() noexcept {}
	virtual void f143() noexcept {}
	virtual void f144() noexcept {}
	virtual void f145() noexcept {}
	virtual void f146() noexcept {}
	virtual void f147() noexcept {}
	virtual void f148() noexcept {}
	virtual void f149() noexcept {}
	virtual void f150() noexcept {}
	virtual void f151() noexcept {}
	virtual void f152() noexcept {}
	virtual void f153() noexcept {}
	virtual void f154() noexcept {}
	virtual void f155() noexcept {}
	virtual void f156() noexcept {}
	virtual void f157() noexcept {}
	virtual void f158() noexcept {}
	virtual void f159() noexcept {}
	virtual void f160() noexcept {}
	virtual void f161() noexcept {}
	virtual void f162() noexcept {}
	virtual void f163() noexcept {}
	virtual void f164() noexcept {}
	virtual void f165() noexcept {}
	virtual void f166() noexcept {}
	virtual void f167() noexcept {}
	virtual void f168() noexcept {}
	virtual void f169() noexcept {}
	virtual void f170() noexcept {}
	virtual void f171() noexcept {}
	virtual void f172() noexcept {}
	virtual void f173() noexcept {}
	virtual void f174() noexcept {}
	virtual void f175() noexcept {}
	virtual void f176() noexcept {}
	virtual void f177() noexcept {}
	virtual void f178() noexcept {}
	virtual void f179() noexcept {}
	virtual void f180() noexcept {}
	virtual void f181() noexcept {}
	virtual void f182() noexcept {}
	virtual void f183() noexcept {}
	virtual void f184() noexcept {}
	virtual void f185() noexcept {}
	virtual void f186() noexcept {}
	virtual void f187() noexcept {}
	virtual void f188() noexcept {}
	virtual void f189() noexcept {}
	virtual void f190() noexcept {}
	virtual void f191() noexcept {}
	virtual void f192() noexcept {}
	virtual void f193() noexcept {}
	virtual void f194() noexcept {}
	virtual void f195() noexcept {}
	virtual void f196() noexcept {}
	virtual void f197() noexcept {}
	virtual void f198() noexcept {}
	virtual void f199() noexcept {}
	virtual void f200() noexcept {}
	virtual void f201() noexcept {}
	virtual void f202() noexcept {}
	virtual void f203() noexcept {}
	virtual void f204() noexcept {}
	virtual void f205() noexcept {}
	virtual void f206() noexcept {}
	virtual void f207() noexcept {}
	virtual void f208() noexcept {}
	virtual void f209() noexcept {}
	virtual void f210() noexcept {}
	virtual void f211() noexcept {}
	virtual void f212() noexcept {}
	virtual void f213() noexcept {}
	virtual void f214() noexcept {}
	virtual void f215() noexcept {}
	virtual void f216() noexcept {}
	virtual void f217() noexcept {}
	virtual void f218() noexcept {}
	virtual void f219() noexcept {}
	virtual void f220() noexcept {}
	virtual void f221() noexcept {}
	virtual void f222() noexcept {}
	virtual void f223() noexcept {}
	virtual void f224() noexcept {}
	virtual void f225() noexcept {}
	virtual void f226() noexcept {}
	virtual void f227() noexcept {}
	virtual void f228() noexcept {}
	virtual void f229() noexcept {}
	virtual void f230() noexcept {}
	virtual void f231() noexcept {}
	virtual void f232() noexcept {}
	virtual void f233() noexcept {}
	virtual void f234() noexcept {}
	virtual void f235() noexcept {}
	virtual void f236() noexcept {}
	virtual void f237() noexcept {}
	virtual void f238() noexcept {}
	virtual void f239() noexcept {}
	virtual void f240() noexcept {}
	virtual void f241() noexcept {}
	virtual void f242() noexcept {}
	virtual void f243() noexcept {}
	virtual void f244() noexcept {}
	virtual void f245() noexcept {}
	virtual void f246() noexcept {}
	virtual void f247() noexcept {}
	virtual void f248() noexcept {}
	virtual void f249() noexcept {}
	virtual void f250() noexcept {}
	virtual void f251() noexcept {}
	virtual void f252() noexcept {}
	virtual void f253() noexcept {}
	virtual void f254() noexcept {}
	virtual void f255() noexcept {}
	virtual void f256() noexcept {}
	virtual void f257() noexcept {}
	virtual void f258() noexcept {}
	virtual void f259() noexcept {}
	virtual void f260() noexcept {}
	virtual void f261() noexcept {}
	virtual void f262() noexcept {}
	virtual void f263() noexcept {}
	virtual void f264() noexcept {}
	virtual void f265() noexcept {}
	virtual void f266() noexcept {}
	virtual void f267() noexcept {}
	virtual void f268() noexcept {}
	virtual void f269() noexcept {}
	virtual void f270() noexcept {}
	virtual void f271() noexcept {}
	virtual void f272() noexcept {}
	virtual void f273() noexcept {}
	virtual void f274() noexcept {}
	virtual void f275() noexcept {}
	virtual void f276() noexcept {}
	virtual void f277() noexcept {}
	virtual void f278() noexcept {}
	virtual void f279() noexcept {}
	virtual void f280() noexcept {}
	virtual void f281() noexcept {}
	virtual void f282() noexcept {}
	virtual void f283() noexcept {}
	virtual void f284() noexcept {}
	virtual void f285() noexcept {}
	virtual void f286() noexcept {}
	virtual void f287() noexcept {}
	virtual void f288() noexcept {}
	virtual void f289() noexcept {}
	virtual void f290() noexcept {}
	virtual void f291() noexcept {}
	virtual void f292() noexcept {}
	virtual void f293() noexcept {}
	virtual void f294() noexcept {}
	virtual void f295() noexcept {}
	virtual void f296() noexcept {}
	virtual void f297() noexcept {}
	virtual void f298() noexcept {}
	virtual void f299() noexcept {}
	*/
	
	
};

void h(A& a) noexcept {
	//a.f10();
    printf("%c: %c, %lu\n", 'A', a.f(), a.g());
	//a.f100();
}

class B : public A {

public:

	char f() noexcept override {
		return 'B';
	}
	
	long g() noexcept override {
		return 1;
	}

};

class C : public A {

public:

	char f() noexcept override {
		return 'C';
	}
	
	long g() noexcept override {
		return 2;
	}

};

//class D : public A {
//
//public:
//
//	char f() noexcept override {
//		return 'D';
//	}
//
//	long g() noexcept override {
//		return 3;
//	}
//
//};
//
//class E : public A {
//
//public:
//
//	char f() noexcept override {
//		return 'E';
//	}
//
//	long g() noexcept override {
//		return 4;
//	}
//
//};

//extern "C"
//void f(int x) {
//	printf("x = %d\n", x);
//}

int main(int argc, char **argv) {
	for (int i = 0; i < argc; i++) {
		printf("%d: %s\n", i, argv[i]);
	}
//	printf("%d\n", argc);
//	if (argc > 1) printf("1");
//	if (argc > 2) printf("2");
//	if (argc > 3) printf("3");
//
//	int aa[10] = {};
//	aa[4] = argc;
//	printf("%d\n", aa[5]);
//	f(aa[4]);
//
//	switch (argc) {
//		case 4: printf("4");
//		case 5: printf("5");
//		case 6: printf("6");
//		case 7: printf("7");
//	}

	B b;
	C c;
//	D d;
//	E e;
	A* array[] = {&b, &c};
	A& a = *array[argc % (sizeof(array) / sizeof(*array))];
	a.h();
	
	std::cout << "sizeof(A) = " << sizeof(A) << std::endl;
	std::cout << "sizeof(B) = " << sizeof(B) << std::endl;
	
	return 0;
}