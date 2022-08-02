#include "check_s21_string.h"

START_TEST(test_s21_sscanf_int) {
  // %d

  verify_sscanf_int("0x11", "%d");  // 0
  verify_sscanf_int("012", "%d");   // 12
  verify_sscanf_int("-013", "%d");  // -13
  verify_sscanf_int("0x11", "%i");  // 17
  verify_sscanf_int("012", "%i");   // 10
  verify_sscanf_int("-013", "%i");  // -11

  verify_sscanf_int("103", "%d");
  verify_sscanf_int("-105", "%d");
  verify_sscanf_int("0000007", "%d");
  verify_sscanf_int("0", "%d");
  verify_sscanf_long_int("0", "%ld");
  verify_sscanf_long_int("+9223372036", "%ld");
  verify_sscanf_long_int("-9223372036", "%ld");

  verify_sscanf_short_int("32767", "%hd");
  verify_sscanf_short_int("32768", "%hd");
  verify_sscanf_short_int("32768", "%3hd");
  verify_sscanf_short_int("0", "%hd");

  verify_sscanf_int("|3147483647|", "|%10d|");
  verify_sscanf_int("|876 |", "|%6d|");
  verify_sscanf_int("|8761|", "|%06d|");
  verify_sscanf_int("|1799|", "|%3d|");      // trim to 179
  verify_sscanf_int("|10758585|", "|%2d|");  // trim to 10

  verify_sscanf_ints("11\n\n\n\n22", "%d%d");
  verify_sscanf_ints("9223372036854775807     300", "%d \t\n %d");
  verify_sscanf_ints("1 2 3 4 5 done", "%d %d %d %d %d done");
  verify_sscanf_ints("9 8 7 6 0 !done", "%d %d %d %d %d done");
  verify_sscanf_ints("3.14 2 3 4 5 end", "%d %d %d %d %d end");
  verify_sscanf_ints("|   128  256   1   |", "|%d%d%d|");
  verify_sscanf_ints("| 728  256   10    |", "|  %d%d  %d |");
  verify_sscanf_ints("|    728  256   10 |", "|%d%d    %d |");
  verify_sscanf_ints("|   064  256   1   |", "|    %d%d%d    |");
  verify_sscanf_ints("|   001  256   1   |", "%d %d %d");

  verify_sscanf_ints("184467440 73709551616", "%5d%d");
  verify_sscanf_ints("184467440 73709551616", "%5d %d");
}
END_TEST

START_TEST(test_s21_sscanf_percent) {
  // %%

  verify_sscanf_percent("", "%%");
  verify_sscanf_percent("% % 5 6", "%% %d %d");
  verify_sscanf_percent("%% 1 8", "%% %d %d");
  verify_sscanf_percent("%%   33    44", "%% %d %d");
  verify_sscanf_percent("%% 213 214 %%", "%% %d %d %%");
}
END_TEST

START_TEST(test_s21_sscanf_unsign) {
  // %u

  verify_sscanf_unsign("4294967295", "%u");  // 4294967295
  verify_sscanf_unsign("99999", "%10u");     // 99999
  verify_sscanf_unsign("8888888", "%05u");   //
  verify_sscanf_unsign("0000", "%5u");       // 0
  verify_sscanf_unsign("123456789", "%u");   //
  verify_sscanf_unsign("234561", "%u");      //
  verify_sscanf_unsign("-128", "%u");        //

  verify_sscanf_unsign("43", "%hu");
  verify_sscanf_unsign("32767", "%hu");
  verify_sscanf_unsign("32768", "%hu");
  verify_sscanf_unsign("-3790", "%hu");

  verify_sscanf_lu("47", "%lu");
  verify_sscanf_lu("-9865", "%lu");
  verify_sscanf_lu("4294967295", "%lu");
  verify_sscanf_lu("4294967297", "%lu");
}
END_TEST

START_TEST(test_s21_sscanf_char) {
  // %c

  verify_sscanf_char("a", "%c");
  verify_sscanf_char("", "%c");
  verify_sscanf_char("\t", "%c");
  verify_sscanf_char(" ", "%c");

  verify_sscanf_ints("300 t", "%d %c");
  verify_sscanf_ints("   300 t", "%d %c");
  verify_sscanf_ints(" p  l", "%c%c");        // ` ` `p`
  verify_sscanf_ints("t   q", "%c%c");        // `t` ` `
  verify_sscanf_ints("w   r", "%c  %c");      // `w` `r`
  verify_sscanf_ints("s   a", "%c %c");       // `s` `a`
  verify_sscanf_ints("f   _", "%c      %c");  // `f` `_`
  verify_sscanf_ints("300 t", "%d%c");
  verify_sscanf_ints("   d5_", "%c%c%c");
  verify_sscanf_ints("   e5_", "%c%c%c%c");
  verify_sscanf_ints("   f5_", "%c%c %c%c %c");
}
END_TEST

START_TEST(test_s21_sscanf_oct) {
  // %o

  verify_sscanf_unsign("00", "%o");                   // 0
  verify_sscanf_unsign("17", "%o");                   // 15
  verify_sscanf_unsign("09", "%o");                   // 0
  verify_sscanf_unsign("00000060", "%o");             // 48
  verify_sscanf_unsign("7223372036054775705", "%o");  // overflow to 4038327237
  verify_sscanf_unsign("2147483647", "%o");           // 9020
  verify_sscanf_unsign("1111", "%10o");               // 585
  verify_sscanf_unsign("7777777    ", "%o");          // 2097151
  verify_sscanf_unsign("7777777\t\n", "%5o");         // 32767
  verify_sscanf_unsign("666666666", "%05o");          // 28086
  verify_sscanf_unsign("010101010", "%5o");           // 520
  verify_sscanf_unsign("123456789", "%10o");          // 342391
  verify_sscanf_unsign("|0xFF|", "|%o|");             // 0
  verify_sscanf_unsign("|076 |", "|%6o|");            // 62
  verify_sscanf_unsign("|0761|", "|%06o|");           // 497
  verify_sscanf_unsign("|1499|", "|%99o|");           // 12
  verify_sscanf_unsign("|2707|", "|%3o|");            // trim to 184
  verify_sscanf_unsign("|1799|", "|%3o|");            // trim to 15
  verify_sscanf_unsign("|10758585|", "|%2o|");        // trim to 8
  verify_sscanf_unsign("|    1|", "|%88o|");          // 1

  verify_sscanf_ints("11\n\n\n\n22", "%o%o");
  verify_sscanf_ints("0223372036054775107     300", "%o \t\n %o");
  verify_sscanf_ints("0223372036054775106 100500    \n   3 4", "%o%o%o%o");
  verify_sscanf_ints("0223372036054775105 100500   break 2 3", "%o%o%o%o");
  verify_sscanf_ints("0223372036054775104 \t\t 300", "%o     %o");
  verify_sscanf_ints("1 2 3 4 5 done", "%o %o %o %o %o done");
  verify_sscanf_ints("6 2 7 6 0 !done", "%o %o %o %o %o done");
  verify_sscanf_ints("3.14 2 3 4 5 end", "%o %o %o %o %o end");
  verify_sscanf_ints("7 14 27", "%o %o %o");
  verify_sscanf_ints("|   121  256   1   |", "|%o%o%o|");
  verify_sscanf_ints("| 727  256   10    |", "|  %o%o  %o |");
  verify_sscanf_ints("|   064  256   1   |", "|    %o%o%o    |");
  verify_sscanf_ints("|   001  256   1   |", "%o %o %o");
  verify_sscanf_ints("| 7 14 break 81 13 |", "%o %o %o %o");
  verify_sscanf_ints("A__       4", "%o__%o");
  verify_sscanf_ints("3       __B", "%o__%o");

  verify_sscanf_ints("707__1__33", "%o__%*o__%o");
  verify_sscanf_ints("1 3 9 5 4", "%o %*o%*o %o");
}
END_TEST

START_TEST(test_s21_sscanf_hex) {
  // %x

  verify_sscanf_unsign("7223372036054775705", "%x");  // overflow to 4294967295
  verify_sscanf_unsign("2147483647", "%x");           // 1195914823
  verify_sscanf_unsign("99999", "%10x");              // 629145
  verify_sscanf_unsign("8888888", "%05x");            // 559240
  verify_sscanf_unsign("0000", "%5x");                // 0
  verify_sscanf_unsign("123456789", "%X");            // 591751049
  verify_sscanf_unsign("234561", "%X");               // 2311521
  verify_sscanf_unsign("-128", "%X");                 // -296

  verify_sscanf_unsign("Tractor drivers favourite number is 300",
                       "Tractor drivers favourite number is %X");

  verify_sscanf_ints("2 12 85", "%d %o %x");
}
END_TEST

START_TEST(test_s21_sscanf_str) {
  // %s

  verify_sscanf_str("", "%s");
  verify_sscanf_str("first text", "%s");
  verify_sscanf_str("trimmed text", "%3s");
  verify_sscanf_str("one more trimmed text", "%3s");
  verify_sscanf_str("another trimmed text", "%10s");
  verify_sscanf_str("five text", "%s");
  verify_sscanf_str(LOREM_IPSUM, "%s");

  verify_sscanf_strs("a    bob   bus", "%s  %s %s");
  verify_sscanf_strs("g dog      pes", "%1s       %2s %s");
  verify_sscanf_strs(LOREM_IPSUM_LOW, "%s%s%s");
  verify_sscanf_strs(LOREM_IPSUM_UP, "%1s%3s%10s");
  verify_sscanf_strs(LOREM_IPSUM, "%10s%7s%15s");
  verify_sscanf_strs("word1    word2    word3", "%7s%7s%7s");
  verify_sscanf_strs("i    love    spaces", "%3s%3s%3s");
  verify_sscanf_strs("mnogomnogobykovbezprobelov", "%3s%3s%3s");
}
END_TEST

START_TEST(test_s21_sscanf_float) {
  // %eEfFgG

  verify_sscanf_float("| 7 |", "| %f |");
  verify_sscanf_float("0", "%f");
  verify_sscanf_float("0xa", "%f");
  verify_sscanf_float("0XB", "%f");
  verify_sscanf_float("03", "%f");
  verify_sscanf_float("7.20", "%f");
  verify_sscanf_float("1.17549435E-38", "%f");
  verify_sscanf_float("1.12222222E-38", "%e");
  verify_sscanf_float("1.13333333e-38", "%e");
  verify_sscanf_float("1.1444e-38", "%g");
  verify_sscanf_float("1.1555E-38", "%G");
  verify_sscanf_float("3.14444444444", "%f");
  verify_sscanf_float("3.14444444444 13", "%f %f");
  verify_sscanf_float("3.1234560000987", "%f");
  verify_sscanf_float("949599687.64655788903", "%f");

  verify_sscanf_long_double("2.2250738585072014E-308", "%Lf");
  verify_sscanf_long_double("2.3250738585072014E-308", "%6Lf");
  verify_sscanf_long_double("2.2250738585072011E-308", "%Le");
  verify_sscanf_long_double("2.2250738585072012E-308", "%LE");
  verify_sscanf_long_double("1.7976931348623158E+308", "%Lf");
  verify_sscanf_long_double("1.7976931348623155E+308", "%LG");
  verify_sscanf_long_double("1.8976931348623155E+308", "%4LG");
  verify_sscanf_long_double("1.7976931348623144E+308", "%Lg");

  verify_sscanf_float("2.147484e+05 7.2", "%f %f");
  verify_sscanf_float("|3. 4.|", "|%f %f|");
  verify_sscanf_float("3.1444422222201", "%5f");
  verify_sscanf_float("1.34567890123 21", "%3f %f");
  verify_sscanf_float("1.34500001123 42.", "%4f %2f");
  verify_sscanf_float("1.34500001123 42.", "%4f %2f");

  verify_sscanf_double("300 0.00003", "%lf %lf");
  verify_sscanf_double("1.345 42.21", "%6lf %2lf");
}
END_TEST

START_TEST(test_s21_sscanf_none) {
  // %n

  verify_sscanf_ints("123 456 30 0", "%1d%2d%3d%4d%5n");
  verify_sscanf_ints("123 456 30 0", "%d%d%d%d%n");
  verify_sscanf_none("123456 300", "%d%n%d");
  verify_sscanf_none("1000 300", "%1d%n%3d");
  verify_sscanf_none("1234 300", "%5d%2n%d");
  verify_sscanf_none("356 12300", "%4d%0n%d");
  verify_sscanf_none("356 12300", "%1d%n%5d");
  verify_sscanf_none("9 7666666", "%d %n %d");
  verify_sscanf_none("     1  44 56   ", "%d %n %d");
  verify_sscanf_none("     2", "%n%n%n");
  verify_sscanf_none(" 37833  55 002  ", "%3d %n55 %n");
  verify_sscanf_ints(" 3  55 002  ", "%n %d %n %d");
}
END_TEST

START_TEST(test_s21_sscanf_ptr) {
  // %p

  verify_sscanf_ptr("0x7ffee33bf5a8 0x7ffee55bf5a9", "%p %p");
  verify_sscanf_ptr("0xabcdef987 140732746429865", "%5p%p");
  verify_sscanf_ptr("0xabcdef986 18446744073709551616", "%5p%p");
  verify_sscanf_ptr("0 0", "%p%p");
}
END_TEST

TCase *sscanf_tests() {
  TCase *t_case = tcase_create("Sscanf");

  tcase_add_test(t_case, test_s21_sscanf_int);
  tcase_add_test(t_case, test_s21_sscanf_percent);
  tcase_add_test(t_case, test_s21_sscanf_unsign);
  tcase_add_test(t_case, test_s21_sscanf_char);
  tcase_add_test(t_case, test_s21_sscanf_oct);
  tcase_add_test(t_case, test_s21_sscanf_hex);
  tcase_add_test(t_case, test_s21_sscanf_str);
  tcase_add_test(t_case, test_s21_sscanf_float);
  tcase_add_test(t_case, test_s21_sscanf_none);
  tcase_add_test(t_case, test_s21_sscanf_ptr);

  return t_case;
}
