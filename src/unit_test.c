#include <check.h>

#include "s21_smartcalc.h"

/* simple tests */
START_TEST(simple_test_1) {
  char *string = "2+3";
  double res = 5;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_2) {
  char *string = "2*3";
  double res = 6;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_3) {
  char *string = "2*3+2";
  double res = 8;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_4) {
  char *string = "3+2*3";
  double res = 9;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_5) {
  char *string = "3+2*3+1";
  double res = 10;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_6) {
  char *string = "3+2*3+2*5";
  double res = 19;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_7) {
  char *string = "2*3+2*5+3";
  double res = 19;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_8) {
  char *string = "2*3+2*5+4*25";
  double res = 116;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_9) {
  char *string = "2*5-4*25";
  double res = -90;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_10) {
  char *string = "-2*5-4*25";
  double res = -110;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_11) {
  char *string = "110-2*5-4*25";
  double res = 0;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_12) {
  char *string = "-2*5-4*25/2";
  double res = -60;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_13) {
  char *string = "-2*5/2-4*25/2";
  double res = -55;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_14) {
  char *string = "2/5*10-26";
  double res = -22;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_15) {
  char *string = "2/5*10-26+100";
  double res = 78;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_16) {
  char *string = "-999";
  double res = -999;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(simple_test_17) {
  char *string = "999";
  double res = 999;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

/* brackets */

START_TEST(brackets_1) {
  char *string = "2*(5+10)/2";
  double res = 15;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_2) {
  char *string = "(2*5)+(10/2)";
  double res = 15;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_3) {
  char *string = "(10+10/2)";
  double res = 15;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_4) {
  char *string = "(10+10/2/5)";
  double res = 11;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_5) {
  char *string = "(10/2+10)";
  double res = 15;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_6) {
  char *string = "(10/2*5+10)";
  double res = 35;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_7) {
  char *string = "(10/2*5+10+5)";
  double res = 40;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_8) {
  char *string = "(-8+10/2*5+10+5)";
  double res = 32;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_9) {
  char *string = "(-8+10/2*5+10*5)";
  double res = 67;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_10) {
  char *string = "(-10+120)/2*(5+10*5)";
  double res = 3025;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_11) {
  char *string = "(-10+120)/(2*(5+10*5))";
  double res = 1;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_12) {
  char *string = "(-110)/(2*(5+10*5))";
  double res = -1;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_13) {
  char *string = "-(130-10)/(2*(5+10)/3)";
  double res = -12;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(brackets_14) {
  char *string =
      "(15/(7-(1+1))*3-(2+(1+1-1+1*2/2))+15/(7-(1+1))*3-(2+(1+1+1-1*2/2)))";
  double res = 10;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

/* uno minus */

START_TEST(unary_minus_1) {
  char *string = "2*-5";
  double res = -10;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_2) {
  char *string = "-2*6";
  double res = -12;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_3) {
  char *string = "-6/(-2)*3";
  double res = 9;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_4) {
  char *string = "-6/(-2)*-3";
  double res = -9;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_5) {
  char *string = "-6/(-2)*-3*(-10-1)";
  double res = 99;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_6) {
  char *string = "-6/-2*-3*(-10-1)";
  double res = 99;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_7) {
  char *string = "-16/8+(-8*-1)/-2";
  double res = -6;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_8) {
  char *string = "-16/(8*-2)+(-8*-1)/-2";
  double res = -3;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_9) {
  char *string = "(-92-8)*-1";
  double res = 100;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_10) {
  char *string = "-(-92-8)*-1";
  double res = -100;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_11) {
  char *string = "-(-92-8)*-(1/-10)";
  double res = 10;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(unary_minus_12) {
  char *string = "1*-(-1)";
  double res = 1;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

/* pow */

START_TEST(pow_1) {
  char *string = "10+2^2^2^2";
  double res = 65546;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_2) {
  char *string = "2^2^2^2+10";
  double res = 65546;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_3) {
  char *string = "2^2^2^2/2";
  double res = 32768;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_4) {
  char *string = "65536/2^2^2^2";
  double res = 1;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_5) {
  char *string = "100+2^2^2^2+10";
  double res = 65646;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_6) {
  char *string = "2*2^2^2^2";
  double res = 131072;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_7) {
  char *string = "2*2^2^2^2/2";
  double res = 65536;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_8) {
  char *string = "-10*2^2^2^2/2";
  double res = -327680;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_9) {
  char *string = "2^-2";
  double res = 0.25;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_10) {
  char *string = "-2^-2";
  double res = -0.25;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(pow_11) {
  char *string = "2^-2^-3";
  double res = 0.917004;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(pow_12) {
  char *string = "-2^-2^-3";
  double res = -0.917004;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(pow_13) {
  char *string = "-2^-2^-3+20";
  double res = 19.082996;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

/* fmod */

START_TEST(fmod_1) {
  char *string = "10%8+2*10^2";
  double res = 202;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_2) {
  char *string = "10%8+2*10/5+2^2^2";
  double res = 22;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_3) {
  char *string = "10%8+2^2^2%5";
  double res = 3;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_4) {
  char *string = "10%8+100%72/8";
  double res = 5.5;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_5) {
  char *string = "10%8+100%(72/8)";
  double res = 3;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_6) {
  char *string = "10%(8+43%(72/8))";
  double res = 10;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_7) {
  char *string = "-34*10%(8+43%(72/8))^2";
  double res = -115;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq(res, calc);
}
END_TEST

START_TEST(fmod_8) {
  char *string = "0.000295%(8+43%(72/8))^-3";
  double res = 0.000295;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(fmod_9) {
  char *string = "2%10%8%5";
  double res = 2;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(fmod_10) {
  char *string = "2%10%8%5*(8-(3-2*5))";
  double res = 30;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

/* trigonometry */

START_TEST(trigonometry_1) {
  char *string = "cos(5)";
  double res = 0.283662;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_2) {
  char *string = "cos(2+3)";
  double res = 0.283662;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_3) {
  char *string = "sqrt(cos(2+3))";
  double res = 0.532599;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_4) {
  char *string = "1+sqrt(cos(2+3))";
  double res = 1.532599;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_5) {
  char *string = "cos(5)+sqrt(cos(2+3))";
  double res = 0.816262;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_6) {
  char *string = "-cos(5)+sqrt(cos(2+3))";
  double res = 0.248937;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_7) {
  char *string = "2^cos(5)";
  double res = 1.217281;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

START_TEST(trigonometry_8) {
  char *string = "2^cos(5)^2";
  double res = 1.057358;
  double calc = smart_calc(string, 0);
  ck_assert_double_eq_tol(res, calc, 1e-6);
}
END_TEST

int main(void) {
  int number_failed;
  Suite *s = suite_create("s21_smartcalc");
  TCase *s21_smartcalc_h = tcase_create("s21_smartcalc_h");
  SRunner *sr = srunner_create(s);

  suite_add_tcase(s, s21_smartcalc_h);

  /* simple tests */
  tcase_add_test(s21_smartcalc_h, simple_test_1);
  tcase_add_test(s21_smartcalc_h, simple_test_2);
  tcase_add_test(s21_smartcalc_h, simple_test_3);
  tcase_add_test(s21_smartcalc_h, simple_test_4);
  tcase_add_test(s21_smartcalc_h, simple_test_5);
  tcase_add_test(s21_smartcalc_h, simple_test_6);
  tcase_add_test(s21_smartcalc_h, simple_test_7);
  tcase_add_test(s21_smartcalc_h, simple_test_8);
  tcase_add_test(s21_smartcalc_h, simple_test_9);
  tcase_add_test(s21_smartcalc_h, simple_test_10);
  tcase_add_test(s21_smartcalc_h, simple_test_11);
  tcase_add_test(s21_smartcalc_h, simple_test_12);
  tcase_add_test(s21_smartcalc_h, simple_test_13);
  tcase_add_test(s21_smartcalc_h, simple_test_14);
  tcase_add_test(s21_smartcalc_h, simple_test_15);
  tcase_add_test(s21_smartcalc_h, simple_test_16);
  tcase_add_test(s21_smartcalc_h, simple_test_17);

  /* brackets */
  tcase_add_test(s21_smartcalc_h, brackets_1);
  tcase_add_test(s21_smartcalc_h, brackets_2);
  tcase_add_test(s21_smartcalc_h, brackets_3);
  tcase_add_test(s21_smartcalc_h, brackets_4);
  tcase_add_test(s21_smartcalc_h, brackets_5);
  tcase_add_test(s21_smartcalc_h, brackets_6);
  tcase_add_test(s21_smartcalc_h, brackets_7);
  tcase_add_test(s21_smartcalc_h, brackets_8);
  tcase_add_test(s21_smartcalc_h, brackets_9);
  tcase_add_test(s21_smartcalc_h, brackets_10);
  tcase_add_test(s21_smartcalc_h, brackets_11);
  tcase_add_test(s21_smartcalc_h, brackets_12);
  tcase_add_test(s21_smartcalc_h, brackets_13);
  tcase_add_test(s21_smartcalc_h, brackets_14);

  /* unary minus */
  tcase_add_test(s21_smartcalc_h, unary_minus_1);
  tcase_add_test(s21_smartcalc_h, unary_minus_2);
  tcase_add_test(s21_smartcalc_h, unary_minus_3);
  tcase_add_test(s21_smartcalc_h, unary_minus_4);
  tcase_add_test(s21_smartcalc_h, unary_minus_5);
  tcase_add_test(s21_smartcalc_h, unary_minus_6);
  tcase_add_test(s21_smartcalc_h, unary_minus_7);
  tcase_add_test(s21_smartcalc_h, unary_minus_8);
  tcase_add_test(s21_smartcalc_h, unary_minus_9);
  tcase_add_test(s21_smartcalc_h, unary_minus_10);
  tcase_add_test(s21_smartcalc_h, unary_minus_11);
  tcase_add_test(s21_smartcalc_h, unary_minus_12);

  /* pow */
  tcase_add_test(s21_smartcalc_h, pow_1);
  tcase_add_test(s21_smartcalc_h, pow_2);
  tcase_add_test(s21_smartcalc_h, pow_3);
  tcase_add_test(s21_smartcalc_h, pow_4);
  tcase_add_test(s21_smartcalc_h, pow_5);
  tcase_add_test(s21_smartcalc_h, pow_6);
  tcase_add_test(s21_smartcalc_h, pow_7);
  tcase_add_test(s21_smartcalc_h, pow_8);
  tcase_add_test(s21_smartcalc_h, pow_9);
  tcase_add_test(s21_smartcalc_h, pow_10);
  tcase_add_test(s21_smartcalc_h, pow_11);
  tcase_add_test(s21_smartcalc_h, pow_12);
  tcase_add_test(s21_smartcalc_h, pow_13);

  /* fmod */
  tcase_add_test(s21_smartcalc_h, fmod_1);
  tcase_add_test(s21_smartcalc_h, fmod_2);
  tcase_add_test(s21_smartcalc_h, fmod_3);
  tcase_add_test(s21_smartcalc_h, fmod_4);
  tcase_add_test(s21_smartcalc_h, fmod_5);
  tcase_add_test(s21_smartcalc_h, fmod_6);
  tcase_add_test(s21_smartcalc_h, fmod_7);
  tcase_add_test(s21_smartcalc_h, fmod_8);
  tcase_add_test(s21_smartcalc_h, fmod_9);
  tcase_add_test(s21_smartcalc_h, fmod_10);

  /* trigonometry */

  tcase_add_test(s21_smartcalc_h, trigonometry_1);
  tcase_add_test(s21_smartcalc_h, trigonometry_2);
  tcase_add_test(s21_smartcalc_h, trigonometry_3);
  tcase_add_test(s21_smartcalc_h, trigonometry_4);
  tcase_add_test(s21_smartcalc_h, trigonometry_5);
  tcase_add_test(s21_smartcalc_h, trigonometry_6);
  tcase_add_test(s21_smartcalc_h, trigonometry_7);
  tcase_add_test(s21_smartcalc_h, trigonometry_8);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (!number_failed) ? EXIT_SUCCESS : EXIT_FAILURE;
}
