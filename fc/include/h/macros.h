#ifndef MACROS_H
#define MACROS_H
#define EXP(_)_
#define M_(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,__,...)__
#define M1(_,_1)_(_1)
#define M2(_,_1,_2)_(_1)M1(_,_2)
#define M3(_,_1,_2,_3)_(_1)M2(_,_2,_3)
#define M4(_,_1,_2,_3,_4)_(_1)M3(_,_2,_3,_4)
#define M5(_,_1,_2,_3,_4,_5)_(_1)M4(_,_2,_3,_4,_5)
#define M6(_,_1,_2,_3,_4,_5,_6)_(_1)M5(_,_2,_3,_4,_5,_6)
#define M7(_,_1,_2,_3,_4,_5,_6,_7)_(_1)M6(_,_2,_3,_4,_5,_6,_7)
#define M8(_,_1,_2,_3,_4,_5,_6,_7,_8)_(_1)M7(_,_2,_3,_4,_5,_6,_7,_8)
#define M9(_,_1,_2,_3,_4,_5,_6,_7,_8,_9)_(_1)M8(_,_2,_3,_4,_5,_6,_7,_8,_9)
#define M10(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)_(_1)M9(_,_2,_3,_4,_5,_6,_7,_8,_9,_10)
#define M11(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)_(_1)M10(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)
#define M12(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)_(_1)M11(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)
#define M13(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)_(_1)M12(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)
#define M14(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)_(_1)M13(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)
#define M15(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)_(_1)M14(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)
#define M16(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16)_(_1)M15(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16)
#define M17(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17)_(_1)M16(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17)
#define M18(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18)_(_1)M17(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18)
#define M19(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19)_(_1)M18(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19)
#define M20(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20)_(_1)M19(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20)
#define M21(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21)_(_1)M20(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21)
#define M22(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22)_(_1)M21(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22)
#define M23(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23)_(_1)M22(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23)
#define M24(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24)_(_1)M23(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24)
#define M25(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25)_(_1)M24(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25)
#define M26(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26)_(_1)M25(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26)
#define M27(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27)_(_1)M26(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27)
#define M28(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28)_(_1)M27(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28)
#define M29(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29)_(_1)M28(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29)
#define M30(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30)_(_1)M29(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30)
#define M31(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31)_(_1)M30(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31)
#define M32(_,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32)_(_1)M31(_,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32)
#define M$(...)EXP(M_(__VA_ARGS__,M32,M31,M30,M29,M28,M27,M26,M25,M24,M23,M22,M21,M20,M19,M18,M17,M16,M15,M14,M13,M12,M11,M10,M9,M8,M7,M6,M5,M4,M3,M2,M1)(__VA_ARGS__))
#ifdef _MSC_VER
//#define TO_CHAR "\""
#define FOR_CHAR "`"
#define IOS_(o,a,k) o##a#k##a
#define M_HELPER(_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53,_52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37,_36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,__VA_ARGS_,...) __VA_ARGS_
#define NUM_ARGS(...) EXP(M_HELPER(__VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
#else
//#define TO_CHAR "
/*\" for web markdown,~!@#$%^&*///"
#define FOR_CHAR `
#define IOS_(o,a,k) o#a#k#a
#define M_HELPER(_64,_63,_62,_61,_60,_59,_58,_57,_56,_55,_54,_53,_52,_51,_50,_49,_48,_47,_46,_45,_44,_43,_42,_41,_40,_39,_38,_37,_36,_35,_34,_33,_32,_31,_30,_29,_28,_27,_26,_25,_24,_23,_22,_21,_20,_19,_18,_17,_16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1,__VA_ARGS_,...) __VA_ARGS_
#define NUM_ARGS(...) M_HELPER(__VA_ARGS__ ,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#endif
#define PROTO_1(k)      #k
#define PROTO_2(k,...)  #k,EXP(PROTO_1(__VA_ARGS__))
#define PROTO_3(k,...)  #k,EXP(PROTO_2(__VA_ARGS__))
#define PROTO_4(k,...)  #k,EXP(PROTO_3(__VA_ARGS__))
#define PROTO_5(k,...)  #k,EXP(PROTO_4(__VA_ARGS__))
#define PROTO_6(k,...)  #k,EXP(PROTO_5(__VA_ARGS__))
#define PROTO_7(k,...)  #k,EXP(PROTO_6(__VA_ARGS__))
#define PROTO_8(k,...)  #k,EXP(PROTO_7(__VA_ARGS__))
#define PROTO_9(k,...)  #k,EXP(PROTO_8(__VA_ARGS__))
#define PROTO_10(k,...) #k,EXP(PROTO_9(__VA_ARGS__))
#define PROTO_11(k,...) #k,EXP(PROTO_10(__VA_ARGS__))
#define PROTO_12(k,...) #k,EXP(PROTO_11(__VA_ARGS__))
#define PROTO_13(k,...) #k,EXP(PROTO_12(__VA_ARGS__))
#define PROTO_14(k,...) #k,EXP(PROTO_13(__VA_ARGS__))
#define PROTO_15(k,...) #k,EXP(PROTO_14(__VA_ARGS__))
#define PROTO_16(k,...) #k,EXP(PROTO_15(__VA_ARGS__))
#define PROTO_17(k,...) #k,EXP(PROTO_16(__VA_ARGS__))
#define PROTO_18(k,...) #k,EXP(PROTO_17(__VA_ARGS__))
#define PROTO_19(k,...) #k,EXP(PROTO_18(__VA_ARGS__))
#define PROTO_20(k,...) #k,EXP(PROTO_19(__VA_ARGS__))
#define PROTO_21(k,...) #k,EXP(PROTO_20(__VA_ARGS__))
#define PROTO_22(k,...) #k,EXP(PROTO_21(__VA_ARGS__))
#define PROTO_23(k,...) #k,EXP(PROTO_22(__VA_ARGS__))
#define PROTO_24(k,...) #k,EXP(PROTO_23(__VA_ARGS__))
#define PROTO_25(k,...) #k,EXP(PROTO_24(__VA_ARGS__))
#define PROTO_26(k,...) #k,EXP(PROTO_25(__VA_ARGS__))
#define PROTO_27(k,...) #k,EXP(PROTO_26(__VA_ARGS__))
#define PROTO_28(k,...) #k,EXP(PROTO_27(__VA_ARGS__))
#define PROTO_29(k,...) #k,EXP(PROTO_28(__VA_ARGS__))
#define PROTO_30(k,...) #k,EXP(PROTO_29(__VA_ARGS__))
#define PROTO_31(k,...) #k,EXP(PROTO_30(__VA_ARGS__))
#define PROTO_32(k,...) #k,EXP(PROTO_31(__VA_ARGS__))
#define PROTO_NDK(__VA_ARGS_,...) EXP(PROTO_##__VA_ARGS_(__VA_ARGS__))
#define PROTO_N(__VA_ARGS_,...) PROTO_NDK(__VA_ARGS_,__VA_ARGS__)
#define STAR_1(o,k)      &o::k
#define STAR_2(o,k,...)  &o::k, EXP(STAR_1(o,__VA_ARGS__))
#define STAR_3(o,k,...)  &o::k, EXP(STAR_2(o,__VA_ARGS__))
#define STAR_4(o,k,...)  &o::k, EXP(STAR_3(o,__VA_ARGS__))
#define STAR_5(o,k,...)  &o::k, EXP(STAR_4(o,__VA_ARGS__))
#define STAR_6(o,k,...)  &o::k, EXP(STAR_5(o,__VA_ARGS__))
#define STAR_7(o,k,...)  &o::k, EXP(STAR_6(o,__VA_ARGS__))
#define STAR_8(o,k,...)  &o::k, EXP(STAR_7(o,__VA_ARGS__))
#define STAR_9(o,k,...)  &o::k, EXP(STAR_8(o,__VA_ARGS__))
#define STAR_10(o,k,...) &o::k, EXP(STAR_9(o,__VA_ARGS__))
#define STAR_11(o,k,...) &o::k, EXP(STAR_10(o,__VA_ARGS__))
#define STAR_12(o,k,...) &o::k, EXP(STAR_11(o,__VA_ARGS__))
#define STAR_13(o,k,...) &o::k, EXP(STAR_12(o,__VA_ARGS__))
#define STAR_14(o,k,...) &o::k, EXP(STAR_13(o,__VA_ARGS__))
#define STAR_15(o,k,...) &o::k, EXP(STAR_14(o,__VA_ARGS__))
#define STAR_16(o,k,...) &o::k, EXP(STAR_15(o,__VA_ARGS__))
#define STAR_17(o,k,...) &o::k, EXP(STAR_16(o,__VA_ARGS__))
#define STAR_18(o,k,...) &o::k, EXP(STAR_17(o,__VA_ARGS__))
#define STAR_19(o,k,...) &o::k, EXP(STAR_18(o,__VA_ARGS__))
#define STAR_20(o,k,...) &o::k, EXP(STAR_19(o,__VA_ARGS__))
#define STAR_21(o,k,...) &o::k, EXP(STAR_20(o,__VA_ARGS__))
#define STAR_22(o,k,...) &o::k, EXP(STAR_21(o,__VA_ARGS__))
#define STAR_23(o,k,...) &o::k, EXP(STAR_22(o,__VA_ARGS__))
#define STAR_24(o,k,...) &o::k, EXP(STAR_23(o,__VA_ARGS__))
#define STAR_25(o,k,...) &o::k, EXP(STAR_24(o,__VA_ARGS__))
#define STAR_26(o,k,...) &o::k, EXP(STAR_25(o,__VA_ARGS__))
#define STAR_27(o,k,...) &o::k, EXP(STAR_26(o,__VA_ARGS__))
#define STAR_28(o,k,...) &o::k, EXP(STAR_27(o,__VA_ARGS__))
#define STAR_29(o,k,...) &o::k, EXP(STAR_28(o,__VA_ARGS__))
#define STAR_30(o,k,...) &o::k, EXP(STAR_29(o,__VA_ARGS__))
#define STAR_31(o,k,...) &o::k, EXP(STAR_30(o,__VA_ARGS__))
#define STAR_32(o,k,...) &o::k, EXP(STAR_31(o,__VA_ARGS__))
#define STARS_N(o,__VA_ARGS_,...) EXP(STAR_##__VA_ARGS_(o,__VA_ARGS__))
#define STARS(o,__VA_ARGS_,...) STARS_N(o,__VA_ARGS_,__VA_ARGS__)
#define STAR__1(o,k)      decltype(&o::k)
#define STAR__2(o,k,...)  decltype(&o::k), EXP(STAR__1(o,__VA_ARGS__))
#define STAR__3(o,k,...)  decltype(&o::k), EXP(STAR__2(o,__VA_ARGS__))
#define STAR__4(o,k,...)  decltype(&o::k), EXP(STAR__3(o,__VA_ARGS__))
#define STAR__5(o,k,...)  decltype(&o::k), EXP(STAR__4(o,__VA_ARGS__))
#define STAR__6(o,k,...)  decltype(&o::k), EXP(STAR__5(o,__VA_ARGS__))
#define STAR__7(o,k,...)  decltype(&o::k), EXP(STAR__6(o,__VA_ARGS__))
#define STAR__8(o,k,...)  decltype(&o::k), EXP(STAR__7(o,__VA_ARGS__))
#define STAR__9(o,k,...)  decltype(&o::k), EXP(STAR__8(o,__VA_ARGS__))
#define STAR__10(o,k,...) decltype(&o::k), EXP(STAR__9(o,__VA_ARGS__))
#define STAR__11(o,k,...) decltype(&o::k), EXP(STAR__10(o,__VA_ARGS__))
#define STAR__12(o,k,...) decltype(&o::k), EXP(STAR__11(o,__VA_ARGS__))
#define STAR__13(o,k,...) decltype(&o::k), EXP(STAR__12(o,__VA_ARGS__))
#define STAR__14(o,k,...) decltype(&o::k), EXP(STAR__13(o,__VA_ARGS__))
#define STAR__15(o,k,...) decltype(&o::k), EXP(STAR__14(o,__VA_ARGS__))
#define STAR__16(o,k,...) decltype(&o::k), EXP(STAR__15(o,__VA_ARGS__))
#define STAR__17(o,k,...) decltype(&o::k), EXP(STAR__16(o,__VA_ARGS__))
#define STAR__18(o,k,...) decltype(&o::k), EXP(STAR__17(o,__VA_ARGS__))
#define STAR__19(o,k,...) decltype(&o::k), EXP(STAR__18(o,__VA_ARGS__))
#define STAR__20(o,k,...) decltype(&o::k), EXP(STAR__19(o,__VA_ARGS__))
#define STAR__21(o,k,...) decltype(&o::k), EXP(STAR__20(o,__VA_ARGS__))
#define STAR__22(o,k,...) decltype(&o::k), EXP(STAR__21(o,__VA_ARGS__))
#define STAR__23(o,k,...) decltype(&o::k), EXP(STAR__22(o,__VA_ARGS__))
#define STAR__24(o,k,...) decltype(&o::k), EXP(STAR__23(o,__VA_ARGS__))
#define STAR__25(o,k,...) decltype(&o::k), EXP(STAR__24(o,__VA_ARGS__))
#define STAR__26(o,k,...) decltype(&o::k), EXP(STAR__25(o,__VA_ARGS__))
#define STAR__27(o,k,...) decltype(&o::k), EXP(STAR__26(o,__VA_ARGS__))
#define STAR__28(o,k,...) decltype(&o::k), EXP(STAR__27(o,__VA_ARGS__))
#define STAR__29(o,k,...) decltype(&o::k), EXP(STAR__28(o,__VA_ARGS__))
#define STAR__30(o,k,...) decltype(&o::k), EXP(STAR__29(o,__VA_ARGS__))
#define STAR__31(o,k,...) decltype(&o::k), EXP(STAR__30(o,__VA_ARGS__))
#define STAR__32(o,k,...) decltype(&o::k), EXP(STAR__31(o,__VA_ARGS__))
#define STAR_S_N(o,__VA_ARGS_,...) EXP(STAR__##__VA_ARGS_(o,__VA_ARGS__))
#define STAR_S(o,__VA_ARGS_,...) STAR_S_N(o,__VA_ARGS_,__VA_ARGS__)
#define OFFSET_1(o,k)      (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k))
#define OFFSET_2(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_1(o,__VA_ARGS__))
#define OFFSET_3(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_2(o,__VA_ARGS__))
#define OFFSET_4(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_3(o,__VA_ARGS__))
#define OFFSET_5(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_4(o,__VA_ARGS__))
#define OFFSET_6(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_5(o,__VA_ARGS__))
#define OFFSET_7(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_6(o,__VA_ARGS__))
#define OFFSET_8(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_7(o,__VA_ARGS__))
#define OFFSET_9(o,k,...)  (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_8(o,__VA_ARGS__))
#define OFFSET_10(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_9(o,__VA_ARGS__))
#define OFFSET_11(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_10(o,__VA_ARGS__))
#define OFFSET_12(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_11(o,__VA_ARGS__))
#define OFFSET_13(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_12(o,__VA_ARGS__))
#define OFFSET_14(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_13(o,__VA_ARGS__))
#define OFFSET_15(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_14(o,__VA_ARGS__))
#define OFFSET_16(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_15(o,__VA_ARGS__))
#define OFFSET_17(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_16(o,__VA_ARGS__))
#define OFFSET_18(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_17(o,__VA_ARGS__))
#define OFFSET_19(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_18(o,__VA_ARGS__))
#define OFFSET_20(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_19(o,__VA_ARGS__))
#define OFFSET_21(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_20(o,__VA_ARGS__))
#define OFFSET_22(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_21(o,__VA_ARGS__))
#define OFFSET_23(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_22(o,__VA_ARGS__))
#define OFFSET_24(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_23(o,__VA_ARGS__))
#define OFFSET_25(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_24(o,__VA_ARGS__))
#define OFFSET_26(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_25(o,__VA_ARGS__))
#define OFFSET_27(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_26(o,__VA_ARGS__))
#define OFFSET_28(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_27(o,__VA_ARGS__))
#define OFFSET_29(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_28(o,__VA_ARGS__))
#define OFFSET_30(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_29(o,__VA_ARGS__))
#define OFFSET_31(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_30(o,__VA_ARGS__))
#define OFFSET_32(o,k,...) (size_t)(&reinterpret_cast<char const volatile&>(((o*)0)->k)), EXP(OFFSET_31(o,__VA_ARGS__))
#define OFFSET_N1(o,N,...) EXP(OFFSET_##N(o,__VA_ARGS__))
#define OFFSET_N(o,N,...) OFFSET_N1(o,N,__VA_ARGS__)
#ifndef _WIN32
#define _IS_WIN 0
#else
#define _IS_WIN 1
#endif
#endif // MACROS_H
