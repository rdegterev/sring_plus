#include "check_s21_string.h"

START_TEST(test_s21_sprintf_int) {
  // %d
  verify_sprintf_int("[%d]", INT_MIN);
  verify_sprintf_int("[%+d]", INT_MAX);

  verify_sprintf_int("[% +d]", -0);    /* [+0] */
  verify_sprintf_int("[% +d]", -1);    /* [-1] */
  verify_sprintf_int("[%+ d]", -320);  /* [-320] */
  verify_sprintf_int("[%+ d]", 320);   /* [+320] */
  verify_sprintf_int("[% +d]", 320);   /* [+320] */
  verify_sprintf_int("[% d]", -320);   /* [-320] */
  verify_sprintf_int("[%- 06d]", 320); /* [ 320  ] */

  verify_sprintf_int("[%09.4d]", -42); /* [    -0042] */
  verify_sprintf_int("[%09d]", -41);   /* [-00000041] */
  verify_sprintf_int("[%- 9.4d]", 32); /* [ 0032    ] */
  verify_sprintf_int("[% 9.4d]", 412); /* [     0412] */

  verify_sprintf_int("[% 010d]", 13);  /* [ 000000013] */
  verify_sprintf_int("[%+010d]", 21);  /* [+000000021] */
  verify_sprintf_int("[%010d]", 17);   /* [0000000017] */
  verify_sprintf_int("[%03.3d]", 011); /* [009] */

  verify_sprintf_int("[%#10d]", 10000);
  verify_sprintf_int("[%-#05d]", 300);
  verify_sprintf_int("[%-5d]", -300);
  verify_sprintf_int("[% d]", 5);
  verify_sprintf_int("[% d]", -5);
  verify_sprintf_int("[%+5d]", 32000);
  verify_sprintf_int("[%+5d]", -32000);
  verify_sprintf_int("[% 5d]", 7);
  verify_sprintf_int("[%-d]", 8);
  verify_sprintf_int("[%10.3d]", 0);
  verify_sprintf_int("[%05.3d]", 11111);
  verify_sprintf_int("[%-5.3d]", 11);
  verify_sprintf_int("[% .3d]", 10002);
  verify_sprintf_int("[%+5.3d]", 12345);
  verify_sprintf_int("[% 5.3d]", 0);
  verify_sprintf_int("[%-.3d]", -1);

  verify_sprintf_int("[%+00000d]", INT_MAX);
  verify_sprintf_int("[%+0#3.1d]", INT_MIN);
  verify_sprintf_int("[%+00000+++---#999.12hd]", 987);

  if (!IS_APPLE) {
    // есть различия между alpine и macos
    verify_sprintf_d_with_star("[%*d ]", 5, 3);
    verify_sprintf_d_with_star("[%0*d]", 5, 3);
    verify_sprintf_d_with_star("[% .*d]\n", 5, 12);
    verify_sprintf_d_with_star("[%- *.d]\n", 12, 5);
    verify_sprintf_d_with_star("[%+# *d]\n", 7, 0);
    verify_sprintf_d_with_star("[%0.*d]\n", 5, 12);
    verify_sprintf_d_with_star("=%*d=", 5, 20);
    verify_sprintf_d_with_star("=%10.*d=", 5, 20);
  }

  verify_sprintf_short_int("[%+hd]", SHRT_MAX);
  verify_sprintf_short_int("[%-.1hd]", SHRT_MAX);
  verify_sprintf_short_int("[%15hd]", SHRT_MIN);

  verify_sprintf_long_int("[%ld]", __LONG_MAX__);
  verify_sprintf_long_int("[%+07ld]", LONG_MAX);
  verify_sprintf_long_int("[%ld]", (-__LONG_MAX__ - 1L));
  verify_sprintf_long_int("[%-100ld]", LONG_MIN);
  verify_sprintf_long_int("[%17.1ld]", LONG_MAX);
}
END_TEST

START_TEST(test_s21_sprintf_char) {
  // %c

  char char_null = 0;
  char char_horizontal_tab = 9;
  verify_sprintf_char("[%c]", 'a');
  verify_sprintf_char("[%10c]", '!');
  verify_sprintf_char("[%-10c]", '@');
  verify_sprintf_char("[%5c]", char_null);
  verify_sprintf_char("[%-5c]", char_horizontal_tab);
  verify_sprintf_char("[% 5c]", '\n');
  verify_sprintf_char("[%-c]", '\0');
  verify_sprintf_char("[% 5c]", '#');
  verify_sprintf_char("[%-05c]", '*');
  verify_sprintf_char("[%-05.1c]", '?');
}
END_TEST

START_TEST(test_s21_sprintf_oct) {
  // %o
  verify_sprintf_int("[%-4o]", 0000);   // [0   ]
  verify_sprintf_int("[%4o]", 0000);    // [   0]
  verify_sprintf_int("[%#o]", 0);       // [0]
  verify_sprintf_int("[%#4o]", 00);     // [   0]
  verify_sprintf_int("[%#-4o]", 0);     // [0   ]
  verify_sprintf_int("[%-0#4o]", 0);    // [0   ]
  verify_sprintf_int("[%-#.4o]", 0);    // [0000]
  verify_sprintf_int("[%0#4.3o]", 0);   // [ 000]
  verify_sprintf_int("[% 0#4.3o]", 0);  // [ 000]
  verify_sprintf_int("[% 0#4.4o]", 0);  // [0000]

  verify_sprintf_int("[%o]", -50);            // [37777777716]
  verify_sprintf_int("[%o]", INT_MAX);        // [17777777777]
  verify_sprintf_int("[%o]", INT_MIN);        // [20000000000]
  verify_sprintf_int("[%10o]", 99999);        // [    303237]
  verify_sprintf_int("[%05o]", 8888888);      // [41721070]
  verify_sprintf_int("[%0o]", 8888888);       // [41721070]
  verify_sprintf_int("[%#0o]", 8888888);      // [041721070]
  verify_sprintf_int("[%-5o]", 0000);         // [0    ]
  verify_sprintf_int("[%#5o]", 10101010);     // [046420422]
  verify_sprintf_int("[%-o]", 0101010);       // [101010]
  verify_sprintf_int("[%.5o]", 1000000001);   // [7346545001]
  verify_sprintf_int("[%10.3o]", 123456789);  // [ 726746425]
  verify_sprintf_int("[%05.3o]", 234561);     // [712101]
  verify_sprintf_int("[%5.3o]", 234561);      // [712101]
  verify_sprintf_int("[%-5.3o]", 0x001);      // [001  ]
  verify_sprintf_int("[%#-10.5o]", 1);        // [00001     ]
  verify_sprintf_int("[%#-10.3o]", 0x001);    // [001       ]
  verify_sprintf_int("[%-#5.3o]", 077);       // [077  ]
  verify_sprintf_int("[%#5.3o]", 077);        // [  077]
  verify_sprintf_int("[%#5.3o]", 321);        // [ 0501]
  verify_sprintf_int("[%#4.4o]", 4321);       // [010341]
  verify_sprintf_int("[%#5.3o]", 0176);       // [ 0176]
  verify_sprintf_int("[%#4.7o]", 0265);       // [0000265]
  verify_sprintf_int("[%#18.21o]", 0115);     // [000000000000000000115]
  verify_sprintf_int("[%#15.15o]", 0157);     // 000000000000157
  verify_sprintf_int("[%-.3o]", 0X123);       // 0000000000000157
  verify_sprintf_int("[%.o]", 0X123);         // [0000000443]
  verify_sprintf_int("[%.10o]", 0X123);       // [0000000443]
  verify_sprintf_int("[%#6.6o]", 23451);      // [055633]
  verify_sprintf_int("[%#-5.3o]", 0X001);     // [001  ]

  verify_sprintf_u_short_int("[%+ho]", (__SHRT_MAX__ * 2 + 1));
  verify_sprintf_u_short_int("[%-.1ho]", USHRT_MAX);
  verify_sprintf_u_short_int("[%15ho]", 0);

  verify_sprintf_u_long_int("[%lo]", UINT64_MAX);
  verify_sprintf_u_long_int("[%+07lo]", LONG_MAX);
  verify_sprintf_u_long_int("[%lo]", (-__LONG_MAX__ - 1L));
  verify_sprintf_u_long_int("[%-100lo]", LONG_MIN);
  verify_sprintf_u_long_int("[%17.1lo]", LONG_MAX);
}
END_TEST

START_TEST(test_s21_sprintf_hex) {
  // %x
  verify_sprintf_int("[%-4x]", 0000);   // [0   ]
  verify_sprintf_int("[%4x]", 0000);    // [   0]
  verify_sprintf_int("[%#x]", 0);       // [0]
  verify_sprintf_int("[%#4x]", 00);     // [   0]
  verify_sprintf_int("[%#-4x]", 0);     // [0   ]
  verify_sprintf_int("[%-0#4x]", 0);    // [0   ]
  verify_sprintf_int("[%-#.4x]", 0);    // [0000]
  verify_sprintf_int("[%0#4.3x]", 0);   // [ 000]
  verify_sprintf_int("[% 0#4.3x]", 0);  // [ 000]
  verify_sprintf_int("[% 0#4.4x]", 0);  // [0000]

  verify_sprintf_int("[%x]", INT32_MAX);      // [7fffffff]
  verify_sprintf_int("[%0x]", INT32_MIN);     // [80000000]
  verify_sprintf_int("[%#0x]", 98765);        // [0x181cd]
  verify_sprintf_int("[%0#x]", 45678);        // [0xb26e]
  verify_sprintf_int("[%8x]", 1024);          // [     400]
  verify_sprintf_int("[%08x]", 512);          // [00000200]
  verify_sprintf_int("[%#5x]", 10101010);     // [0x9a2112]
  verify_sprintf_int("[%-x]", 0101010);       // [8208]
  verify_sprintf_int("[%.5x]", 1000000001);   // [3b9aca01]
  verify_sprintf_int("[%10.3x]", 123456789);  // [   75bcd15]

  verify_sprintf_int("[%05.30x]", 234561);  // [000000000000000000000000039441]
  verify_sprintf_int("[%-5.3x]", 0x001);    // [001  ]
  verify_sprintf_int("[%-3.5x]", 0x007);    // [00007]
  verify_sprintf_int("[%-.3x]", 0X123);     // [123]
  verify_sprintf_int("[%#5x]", 100);        // [ 0x64]
  verify_sprintf_int("[%#05x]", 100);       // [0x064]
  verify_sprintf_int("[%#5.2x]", 077);      // [ 0x3f]
  verify_sprintf_int("[%#05.2x]", 077);     // [ 0x3f]
  verify_sprintf_int("[%#3.4x]", 0xF);      // [0x000f]
  verify_sprintf_int("[%#3.3x]", 0x123);    // [0x123]
  verify_sprintf_int("[%#18.21x]", 0xAA);   // [0x0000000000000000000aa]

  verify_sprintf_long_int("[%#20.13x]", 0x7ffeedac856a);   // [ 0x00000edac856a]
  verify_sprintf_long_int("[%#-20.13x]", 0x7ffeedac856b);  // [0x00000edac856b ]
  verify_sprintf_long_int("[%#014.10x]", 0xdac856c);       // [  0x000dac856c]
  verify_sprintf_long_int("[%#-014.10x]", 0xdac856d);      // [0x000dac856d  ]

  verify_sprintf_int("[%X]", INT32_MAX);  // [7FFFFFFF]
  verify_sprintf_u_long_int("[%lX]", UINT64_MAX);
  verify_sprintf_int("[%10X]", 444444);       // [     6C81C]
  verify_sprintf_int("[%05X]", 2128506);      // [207A7A]
  verify_sprintf_int("[%-5X]", 00);           // [0    ]
  verify_sprintf_int("[%-#5X]", 0);           // [0    ]
  verify_sprintf_int("[%#5X]", 111111);       // [0X1B207]
  verify_sprintf_int("[%-X]", 0101010);       // [8208]
  verify_sprintf_int("[%.8X]", 300003);       // [000493E3]
  verify_sprintf_int("[%10.3X]", 123456789);  // [   75BCD15]
  verify_sprintf_int("[%05.3X]", 545232);     // [851D0]
  verify_sprintf_int("[%05.8X]", 2873119);    // [002BD71F]
  verify_sprintf_int("[%#05.8X]", 2226444);   // [0X0021F90C]
  verify_sprintf_int("[%#05.3X]", 545232);    // [0X851D0]
  verify_sprintf_int("[%6.6X]", 23451);       // [005B9B]
  verify_sprintf_int("[%#6.6X]", 23451);      // [0X005B9B]
  verify_sprintf_int("[%-5.3X]", 0X001);      // [001  ]
  verify_sprintf_int("[%#-5.3X]", 0X001);     // [0X001]
  verify_sprintf_int("[%-.3X]", 0X123);       // [123]
  verify_sprintf_int("[%#5X]", 100);          // [ 0X64]
  verify_sprintf_int("[%#05X]", 100);         // [0X064]
  verify_sprintf_int("[%#5.2X]", 077);        // [ 0X3F]
  verify_sprintf_int("[%#05.2X]", 077);       // [ 0X3F]

  verify_sprintf_u_short_int("[%+hx]", (__SHRT_MAX__ * 2 + 1));
  verify_sprintf_u_short_int("[%-.1hX]", USHRT_MAX);
  verify_sprintf_u_short_int("[%15hx]", 0);

  verify_sprintf_u_long_int("[%lX]", UINT64_MAX);
  verify_sprintf_u_long_int("[%+07lx]", 0);
}
END_TEST

START_TEST(test_s21_sprintf_str) {
  // %s

  verify_sprintf_str("[%s]", "!@#$^&*(){}:|?><");
  verify_sprintf_str("[[==>%10s<==]]", "QWERTY");
  verify_sprintf_str("[%3s]", "In a Galaxy far far away");
  verify_sprintf_str("[%05s]", "In a Galaxy far far away");
  verify_sprintf_str("[%-5s]", "\0\0\0whynot??");
  verify_sprintf_str("[%-05s]", "\0\0\0whynot??");
  verify_sprintf_str("[%-25s]", "In a Galaxy far far away");
  verify_sprintf_str("[%25s]", "In a Galaxy far far away");
  verify_sprintf_str("[%#5s]", "\n456789");
  verify_sprintf_str("[%-s]", "\n\0NULL\\%%");
  verify_sprintf_str("[%.5s]", "1000000001");
  verify_sprintf_str("[%100.300s]", LOREM_IPSUM);
  verify_sprintf_str("[%-300.2s]", LOREM_IPSUM);
  verify_sprintf_str("[%s]", LOREM_IPSUM);
  verify_sprintf_str("[%-5.3s]", "234561");
  verify_sprintf_str("[% 5.3s]", "234561");
  verify_sprintf_str("[%-5.3s]", "0s001");
  verify_sprintf_str("[%#5.3s]", "077");
  verify_sprintf_str("[%-.3s]", "0X123");
  verify_sprintf_str("[%+10.3s]", "qweqwe");
  verify_sprintf_str("[%-010.3s]", "asdfg0998765");
}
END_TEST

START_TEST(test_s21_sprintf_float) {
  // %f

  verify_sprintf_float("[[==>%f<==]]", 214748.36478912033453333333333333333333);

  verify_sprintf_float("[[==>%05f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%5f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%3.3f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%1.1f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%5.1f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%1.5f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%#1.5f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%#05.5f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%#6.6f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%7.7f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%-8.8f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%.f<==]]", -S21_INFINITY);
  verify_sprintf_float("[[==>%10.f<==]]", -S21_INFINITY);
  verify_sprintf_float("[[==>%.f<==]]", -S21_INFINITY);
  verify_sprintf_float("[[==>%.f<==]]", -S21_INFINITY);
  verify_sprintf_float("[[==>% f<==]]", S21_INFINITY);
  verify_sprintf_float("[[==>%f<==]]", S21_NAN);
  verify_sprintf_float("[[==>%7f<==]]", S21_NAN);
  verify_sprintf_float("[[==>%-5f<==]]", S21_NAN);
  verify_sprintf_float("[[==>%#f<==]]", S21_NAN);

  verify_sprintf_float("[%10f]", 999.99);
  verify_sprintf_float("[%+10f]", 349.991);
  verify_sprintf_float("[%.0f]", 299.1);
  verify_sprintf_float("[%.f]", 0.113);
  verify_sprintf_float("[%10.0f]", 312.116);
  verify_sprintf_float("[%#10.f]", 310);
  verify_sprintf_float("[%-50.3f]", 12.9);
  verify_sprintf_float("[%040.3f]", 17.29);
  verify_sprintf_float("[%05f]", -8888.888);
  verify_sprintf_float("[%-5f]", 0000);
  verify_sprintf_float("[%+#40.16f]", 1.17549435E-38);
  verify_sprintf_long_double("[%+#40.16Lf]", 1.17549435E-38);
  verify_sprintf_long_double("[%+#400Lf]", 2.2250738585072014E-308);
  verify_sprintf_long_double("[% #4.Lf]", 2.22E-3);
  verify_sprintf_long_double("[%+#4.Lf]", 2.2250738585072014E-308);
  verify_sprintf_float("[% #40.16f]", 1.17549435E-37);
  verify_sprintf_float("[%-f]", -1.17549435E-38);
  verify_sprintf_float("[%.5f]", 1000000001);
  verify_sprintf_float("[%299.3f]", 123456789);
  verify_sprintf_float("[%05.16f]", 234561);
  verify_sprintf_float("[%-5.16f]", 0x001);
  verify_sprintf_float("[%#50.3f]", 077);
  verify_sprintf_float("[%-.3f]", 0X123);
}
END_TEST

START_TEST(test_s21_sprintf_E) {
  // %e

  verify_sprintf_float("[%e]", 0.000001);
  verify_sprintf_float("[%e]", 214748.3647);
  verify_sprintf_float("[%05e]", -8888.888);
  verify_sprintf_float("[%+50.e]", 88.234);
  verify_sprintf_float("[%+50.e]", 99.234);
  verify_sprintf_float("[%+5.e]", 9.2);
  verify_sprintf_float("[%-9.e]", 0.99);
  verify_sprintf_float("[%-#199.e]", 0);
  verify_sprintf_float("[%5.e]", 0.9);
  verify_sprintf_float("[%+5.e]", 9.999999);
  verify_sprintf_float("[%+5.e]", 5.00000000002);
  verify_sprintf_float("[%+5.e]", 15.00000000002);
  verify_sprintf_float("[%+50.e]", -8888.888);
  verify_sprintf_float("[%050.e]", -8888.888);
  verify_sprintf_float("[%-50.e]", -8888.888);
  verify_sprintf_float("[% #99.6e]", 1.17549435E-38);
  verify_sprintf_float("[%05.6e]", 234561);
  verify_sprintf_float("[%-5.6e]", 234561);
  verify_sprintf_float("[%+5.6e]", 234561);
  verify_sprintf_float("[%#50.3e]", 077);
  verify_sprintf_float("[%10E]", 999.99);
  verify_sprintf_float("[%-5E]", 0000);
  verify_sprintf_float("[%-2990E]", 0);
  verify_sprintf_float("[%-E]", -1.17549435E-38);
  verify_sprintf_float("[%.12e]", 9007199254740992);  // [9.007199254741e+15]
  verify_sprintf_float("[%+.5e]", 9907199283248579);
  verify_sprintf_float("[%12e]", 9007199254740992);  // [9.007199e+15]
  verify_sprintf_float("[%.9E]", -3.000000003E-38);  // [-3.000000085E-38]
  verify_sprintf_float("[%.2e]", 6.72E9);            // [6.72e+09]
  verify_sprintf_float("[%.6e]", 9.99E38);
  verify_sprintf_float("[%.5E]", 1000000001);

  verify_sprintf_long_double("[%10Le]", 0);
  verify_sprintf_long_double("[%-#10Le]", -1);
  verify_sprintf_long_double("[%+#40.6Le]", 1.17549435E-38);
  verify_sprintf_long_double("[%+#400Le]", 2.2250738585072014E-308);
  verify_sprintf_long_double("[% #4.LE]", 2.22E-3);
  verify_sprintf_long_double("[%+#8.4LE]", 2.2250738585072014E-308);
  verify_sprintf_long_double("[%+#4.LE]", LONG_MAX);
  verify_sprintf_long_double("[%+#30.3LE]", LONG_MIN);
  verify_sprintf_long_double("[%1.6LE]", (long double)3.4E-308);
  verify_sprintf_long_double("[% .6Le]", (long double)1.1E+308);
}
END_TEST

START_TEST(test_s21_sprintf_G) {
  // %g

  verify_sprintf_float("[%g]", 392.650);
  verify_sprintf_float("[%g]", 123.40);
  verify_sprintf_float("[%g]", 1.4000000000000e+01);
  verify_sprintf_float("[%g]", 1.4000000000000e-01);
  verify_sprintf_float("[% g]", 7e-7);
  verify_sprintf_float("[%#g]", 1e-6);
  verify_sprintf_float("[%#g]", 0.000001);
  verify_sprintf_float("[%7.15g]", 999.999);
  verify_sprintf_float("[%10.15g]", 999.999);   // [   999.999]
  verify_sprintf_float("[%-#7.15g]", 999.999);  // [999.999000000000]
  verify_sprintf_float("[%#g]", 0.0);           // [0.00000]
  verify_sprintf_float("[%#g]", 1.);            // [1.00000]
  verify_sprintf_float("[%#g]", 1000.);         // [1000.00]
  verify_sprintf_float("[%#g]", 0.000009);
  verify_sprintf_float("[%g]", 0.000009);
  verify_sprintf_float("[%-g]", 0.000009);
  verify_sprintf_float("[%g]", 10.000009);  // [10]
  verify_sprintf_float("[%g]", 10.0000010);
  verify_sprintf_float("[%5g]", 10.0000010);
  verify_sprintf_float("[%7g]", 10.0000010);
  verify_sprintf_float("[%0g]", 10.0000010);
  verify_sprintf_float("[%1g]", 10.0000010);
  verify_sprintf_float("[%.g]", 10.0000010);
  verify_sprintf_float("[%6.6g]", 10.0000010);
  verify_sprintf_float("[%5.5g]", 10.0000010);
  verify_sprintf_float("[%7.7g]", 10.0000010);
  verify_sprintf_float("[%7.7g]", 9.9000090);
  verify_sprintf_float("[%7.7g]", 9.99990);  // [ 9.9999]
  verify_sprintf_float("[%7.7g]", 9.1111110);
  verify_sprintf_float("[%7.7g]", 9.9999910);
  verify_sprintf_float("[%7.7g]", 10.9999910);
  verify_sprintf_float("[%7.7g]", 11.9999910);
  verify_sprintf_float("[%7.7g]", 10.1010);
  verify_sprintf_float("[%g]", 00010.1010);
  verify_sprintf_float("[%#g]", 00010.1010);  //  [10.1010]

  verify_sprintf_float("[%g]", 123456.0);
  verify_sprintf_float("[%g]", 1234567.0);
  verify_sprintf_float("[%g]", 123.4567);
  verify_sprintf_float("[%-5.0g]", 0x002);  // [2    ]
  verify_sprintf_float("[%-5.6g]", 0x001);  // [1    ]
  verify_sprintf_float("[%.5g]", 1000000001);
  verify_sprintf_float("[%2990.3G]", 123456789);
  verify_sprintf_float("[%-.3G]", 0X123);
  verify_sprintf_float("[%-.4G]", 66.33333333);
  verify_sprintf_float("[%.G]", 66.0000000333);
  verify_sprintf_float("[%12g]", 45);  // [          45]
  verify_sprintf_float("[%5g]", 0);    // [    0]
  verify_sprintf_float("[%.1g]", -0);

  verify_sprintf_long_double("[%+#40.6Lg]", 1.17549435E-38);
  verify_sprintf_long_double("[%+#400LG]", 2.2250738585072014E-308);
  verify_sprintf_long_double("[% 4.Lg]", 2.22E-3);
  verify_sprintf_long_double("[%+#4.LG]", 2.2250738585072014E-308);
  verify_sprintf_long_double("[% 04.LG]", 2.2250738585072014E-306);
  verify_sprintf_long_double("[%#Lg]", 1e-19);
  verify_sprintf_long_double("[%0Lg]", 1e-17);
  verify_sprintf_long_double("[%9Lg]", 2.300e+16);
}
END_TEST

START_TEST(test_s21_sprintf_unsign) {
  // %u

  verify_sprintf_u_long_int("[%u]", -50);
  verify_sprintf_u_long_int("[%u]", UINT64_MAX);
  verify_sprintf_u_long_int("[%lu]", UINT64_MAX);
  verify_sprintf_u_long_int("[%hu]", USHRT_MAX);
  verify_sprintf_u_long_int("[%hu]", 0);
  verify_sprintf_u_long_int("[%lu]", 0);
  verify_sprintf_u_long_int("[%u]", INT64_MIN);
  verify_sprintf_u_long_int("[%10u]", 146651);
  verify_sprintf_u_long_int("[%05u]", 789000);
  verify_sprintf_u_long_int("[%010u]", 745);
  verify_sprintf_u_long_int("[%0u]", 351786);
  verify_sprintf_u_long_int("[%#0u]", 42);
  verify_sprintf_u_long_int("[%-5u]", 0000);
  verify_sprintf_u_long_int("[%#5u]", 10101010);
  verify_sprintf_u_long_int("[%-u]", 0101010);
  verify_sprintf_u_long_int("[%.5u]", 1000000001);
  verify_sprintf_u_long_int("[%10.3u]", 123456789);
  verify_sprintf_u_long_int("[%10.3lu]", 123000789);
  verify_sprintf_u_long_int("[%05.3u]", 234561);
  verify_sprintf_u_long_int("[%5.3u]", 234561);
  verify_sprintf_u_long_int("[%-5.3u]", 0x001);
  verify_sprintf_u_long_int("[%#-10.5u]", 1);
  verify_sprintf_u_long_int("[%-#5.3u]", 77);
  verify_sprintf_u_long_int("[%#5.3u]", 77);
  verify_sprintf_u_long_int("[%#5.3u]", 321);
  verify_sprintf_u_long_int("[%#4.4u]", 4321);
  verify_sprintf_u_long_int("[%#4.7u]", 265);
  verify_sprintf_u_long_int("[%#18.21u]", 115);
  verify_sprintf_u_long_int("[%#15.15u]", 157);
  verify_sprintf_u_long_int("[%#16.16lu]", 157);
  verify_sprintf_u_long_int("[%-.3u]", 10203);
  verify_sprintf_u_long_int("[%.u]", 962);
  verify_sprintf_u_long_int("[%.10u]", 2112);
}
END_TEST

START_TEST(test_s21_sprintf_none) {
  // %n

  if (IS_APPLE) {
    char buffer[MANY];
    int counter = 0;
    s21_sprintf(buffer, "This text with [%n] counter", &counter);
    ck_assert_str_eq(buffer, "This text with [] counter");
    ck_assert_int_eq(counter, 16);
  } else {
    verify_sprintf_n("[%s==>%n<==]");
    verify_sprintf_n("[%s==>%10n<== %n== (%n)]");
    verify_sprintf_n("[%.1s=%%=>%-5n<==% n== (%+n)]");
    verify_sprintf_n("[%.5s==>%10n<== %#n== (%0n)]");
    verify_sprintf_n("[%10.10s==>%010n<== %03.4n== (%01.2n)]");
    verify_sprintf_n("[%-100.10s==>%.10n<== %n== (%5.17n)]");
  }
}
END_TEST

START_TEST(test_s21_sprintf_ptr) {
  // %p

  float test_data[3] = {3.14, 21, 1E-34};

  verify_sprintf_long_int("1[%#2.20x]", 0x7ffeedac856c);

  verify_sprintf_ptr("2[%20.16p][%2.20p]", &test_data, &test_data);
  verify_sprintf_ptr("3[%p     ][   %.20p]", &test_data, &test_data);

  verify_sprintf_ptr_e("4 zero ptr (% 3p)", 0x000000000000, "4 zero ptr (0x0)");
  verify_sprintf_ptr_e("5 zero ptr (%+6p)", 0x0, "5 zero ptr (   0x0)");
  verify_sprintf_ptr_e("6 zero ptr (% -9p)", 0, "6 zero ptr (0x0      )");

  if (!IS_APPLE) {
    verify_sprintf_ptr("7 [%p]<[%p] ", &(test_data[1]), &(test_data[2]));
    verify_sprintf_ptr("8 [%p]!=[%p]", &test_data + 1, &(test_data[1]));
    verify_sprintf_ptr("9 [%p]==[%p]", &test_data, &(test_data[0]));
  }
}
END_TEST

START_TEST(test_s21_unstable) {
  /*
  здесь собраны тесты чей результат может меняться
  в зависимости от os /компилятора / режима сборки и т.д.
  */

  verify_sprintf_str("[%010.3s]", "qweqwe");
  verify_sprintf_char("[%0121c]", '#');

  verify_sprintf_float("[[==>%+f<==]]", S21_NAN);
  verify_sprintf_float("[[==>% f<==]]", S21_NAN);

  verify_sprintf_float("[%#50.3e]", S21_INFINITY);
  verify_sprintf_float("[%-#50.3e]", S21_INFINITY);
  verify_sprintf_float("[%#10e]", -S21_INFINITY);
  verify_sprintf_float("[%-#10e]", -S21_INFINITY);
  verify_sprintf_float("[%#50.3e]", S21_NAN);
  verify_sprintf_float("[%#50.3e]", S21_NAN);

  verify_sprintf_float("[%g]", S21_INFINITY);
  verify_sprintf_float("[%10g]", -S21_INFINITY);
  verify_sprintf_float("[%-9g]", -S21_INFINITY);
  verify_sprintf_float("[%g]", S21_NAN);

  verify_sprintf_long_double("[%-#5Le]", S21_INFINITY);
  verify_sprintf_long_double("[%-#4.Le]", -S21_INFINITY);
  verify_sprintf_long_double("[%-#10Le]", S21_NAN);
  verify_sprintf_long_double("[%-#10Le]", S21_NAN);
}
END_TEST

TCase *sprintf_tests() {
  TCase *t_case = tcase_create("Sprintf");

  tcase_add_test(t_case, test_s21_sprintf_int);
  tcase_add_test(t_case, test_s21_sprintf_char);
  tcase_add_test(t_case, test_s21_sprintf_oct);
  tcase_add_test(t_case, test_s21_sprintf_hex);
  tcase_add_test(t_case, test_s21_sprintf_unsign);
  tcase_add_test(t_case, test_s21_sprintf_str);
  tcase_add_test(t_case, test_s21_sprintf_float);
  tcase_add_test(t_case, test_s21_sprintf_E);
  tcase_add_test(t_case, test_s21_sprintf_G);
  tcase_add_test(t_case, test_s21_sprintf_none);
  tcase_add_test(t_case, test_s21_sprintf_ptr);

  return t_case;
}
