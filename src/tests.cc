#include <gtest/gtest.h>

#include "smart_calc/back/s21_calc.h"

TEST(ModelTest, test_empty_input_1) {
  std::string str = "        ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, EmptyInput);
}

TEST(ModelTest, test_empty_input_2) {
  std::string str = "";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, EmptyInput);
}

TEST(ModelTest, test_invalid_value_1) {
  std::string str = " 6 + son(pi)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_2) {
  std::string str = "  ~8.874 + tan(0)  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_3) {
  std::string str = "164.4.5 - sqrt(144)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_4) {
  std::string str = " 6E+1E8 + 5  mod 2 ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_5) {
  std::string str = "-785/ 2^9 + y";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_6) {
  std::string str = "(uau - 98 * 252)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_7) {
  std::string str = "  6.4 + cos(l)  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_invalid_value_8) {
  std::string str = "   25 + E-2  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_simple_case_1) {
  std::string str = "3+(5-2*3^2)";
  s21::Model TestModel;
  double answer = 3 + (5 - 2 * pow(3, 2));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_2) {
  std::string str = "3 / (5-5)";
  s21::Model TestModel;
  double answer = 3. / (5. - 5.);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_3) {
  std::string str = "3/5-5^ 2*3.25";
  s21::Model TestModel;
  double answer = 3. / 5 - powl(5, 2) * 3.25;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_4) {
  std::string str = "sin(pi)";
  s21::Model TestModel;
  double answer = sin(M_PI);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_5) {
  std::string str = "ln(e)";
  s21::Model TestModel;
  double answer = log(M_E);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_6) {
  std::string str = " 10 - 5 mod 3";
  s21::Model TestModel;
  double answer = 10 - fmod(5, 3);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_7) {
  std::string str = "tan(0.8)";
  s21::Model TestModel;
  double answer = tan(0.8);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_8) {
  std::string str = "log(1000)";
  s21::Model TestModel;
  double answer = log10(1000);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_9) {
  std::string str = "-cos(0)";
  s21::Model TestModel;
  double answer = -cos(0);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_10) {
  std::string str = "sqrt(144)";
  s21::Model TestModel;
  double answer = sqrt(144);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_11) {
  std::string str = "asin(0.42)";
  s21::Model TestModel;
  double answer = asin(0.42);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_12) {
  std::string str = "acos(0.542)";
  s21::Model TestModel;
  double answer = acos(0.542);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_13) {
  std::string str = "atan(0.21)";
  s21::Model TestModel;
  double answer = atan(0.21);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_14) {
  std::string str = "-(-cos(pi) ^ 5) ";
  s21::Model TestModel;
  double answer = -pow((-cos(M_PI)), 5);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_15) {
  std::string str = "-(+(-(+21)))";
  s21::Model TestModel;
  double answer = 21;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_16) {
  std::string str = "(13.5) ^ (-2)";
  s21::Model TestModel;
  double answer = pow(13.5, (-2));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_simple_case_17) {
  std::string str = "  42.21 ";
  s21::Model TestModel;
  double answer = 42.21;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_calculation_error_1) {
  std::string str = "  /  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_2) {
  std::string str = " 3 *  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_3) {
  std::string str = "  +  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_4) {
  std::string str = "  +-+-+-++ 42  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_5) {
  std::string str = "  +  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_6) {
  std::string str = "(5)+(3";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_7) {
  std::string str = "(5))";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_8) {
  std::string str = "sin(+)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_9) {
  std::string str = "(3+5)-7)*sin(2)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_10) {
  std::string str = "(())";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_11) {
  std::string str = "(.)(.)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_12) {
  std::string str = "/(sin(4))";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_13) {
  std::string str = "3/ *(sin(pi))";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_14) {
  std::string str = "2+4*()-sin(12)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_15) {
  std::string str = "(-1 (2 +(3 ((4) + 5)))";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_16) {
  std::string str = "2 * (2 + 2))";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_17) {
  std::string str = "(2) * 2 + 6 / (2.3";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_calculation_error_18) {
  std::string str = "3 - sin((12)";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_hard_case_1) {
  std::string str = "((2 - (1 - 2)) - 2)";
  s21::Model TestModel;
  double answer = ((2 - (1 - 2)) - 2);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_2) {
  std::string str = "sin(3) * cos(5) + 7*tan(2)";
  s21::Model TestModel;
  double answer = sin(3) * cos(5) + 7 * tan(2);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_3) {
  std::string str = "sin(4 + 5) * cos(-2) ^ (-3) - (-tan(1))";
  s21::Model TestModel;
  double answer = sin(4 + 5) * pow(cos(-2), -3) - (-tan(1));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_4) {
  std::string str = "sin(cos(4) * (-2))^tan(12)";
  s21::Model TestModel;
  double answer = pow(sin(cos(4) * (-2)), tan(12));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_5) {
  std::string str = "-(+sqrt(2.2 * 3 - 6)^3)";
  s21::Model TestModel;
  double answer = -(pow(+sqrt(2.2 * 3 - 6), 3));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_6) {
  std::string str = "ln(12+213821*7)^(-2)+3";
  s21::Model TestModel;
  double answer = pow(log(12 + 213821 * 7), -2) + 3;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_7) {
  std::string str = "5 + 3 * 2 * sqrt(3) + sqrt(53 + 55 * 4)";
  s21::Model TestModel;
  double answer = 5 + 3 * 2 * sqrt(3) + sqrt(53 + 55 * 4);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_8) {
  std::string str =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  s21::Model TestModel;
  double answer = 15.0 / (7 - (1 + 1)) * 3 -
                  (2 + (1 + 1)) * 15.0 / (7 - (200 + 1)) * 3 -
                  (2 + (1 + 1)) * (15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)) +
                                   15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_9) {
  std::string str = "3+(-4)*sin(3+5)*2/(1-5)^2^2";
  s21::Model TestModel;
  double answer = 3 + (-4) * sin(3.0 + 5) * 2.0 / pow(pow((1 - 5.0), 2.0), 2.0);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_10) {
  std::string str = "12-32*(2143-312*(4-5)-1.32/(83.2/3))";
  s21::Model TestModel;
  double answer = 12 - 32 * (2143 - 312 * (4 - 5) - 1.32 / (83.2 / 3));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_hard_case_11) {
  std::string str = "(ln(2 * 2.71828) + log(100))/10 + 0.6";
  s21::Model TestModel;
  double answer = (log(2 * 2.71828) + log10(100)) / 10 + 0.6;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_error_1) {
  std::string str = "6 + son(x)";
  s21::Model TestModel;
  double x = M_PI;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_x_case_error_2) {
  std::string str = "cos()x";
  s21::Model TestModel;
  double x = 0;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_x_case_error_3) {
  std::string str = "+3*4^(lim(x))";
  s21::Model TestModel;
  double x = 0;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_x_case_error_4) {
  std::string str = "xxx+5*2.4";
  s21::Model TestModel;
  double x = 3;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_x_case_error_5) {
  std::string str = " x / ";
  s21::Model TestModel;
  double x = 5;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_x_case_error_6) {
  std::string str = "  / x - sin(0)";
  s21::Model TestModel;
  double x = 4;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, CalculationError);
}

TEST(ModelTest, test_x_case_error_7) {
  std::string str = " x - y";
  s21::Model TestModel;
  double x = 21;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, InvalidValue);
}

TEST(ModelTest, test_x_case_error_8) {
  std::string str = " x - 42*x  ^2  ";
  s21::Model TestModel;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, 0, 1);
  EXPECT_EQ(status, InvalidX);
}

TEST(ModelTest, test_x_case_1) {
  std::string str = "  x*(-(1+2))^(-(x+1*(-(x+4)))) ";
  s21::Model TestModel;
  double x = 2;
  double answer = 2 * (pow(-(1 + 2), (-(2 + 1 * (-(2 + 4))))));
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_2) {
  std::string str = "log(ln(x) * 12^3 - 1)";
  s21::Model TestModel;
  double x = 3223;
  double answer = log10(log(3223) * pow(12, 3) - 1);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_3) {
  std::string str = "  3+34-cos(7*x) ";
  s21::Model TestModel;
  double x = M_PI;
  double answer = 3 + 34 - cos(7 * M_PI);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_4) {
  std::string str = "  3.5-cos(x+pi/e) ";
  s21::Model TestModel;
  double x = M_PI;
  double answer = 3.5 - cos(x + M_PI / M_E);
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_5) {
  std::string str = "  x + 84 / 42 mod 5 ";
  s21::Model TestModel;
  double x = 21;
  double answer = 21 + 84 / 42 % 5;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_6) {
  std::string str = "  -x + x ";
  s21::Model TestModel;
  double x = 42;
  double answer = -42 + 42;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

TEST(ModelTest, test_x_case_7) {
  std::string str = "  x / x ";
  s21::Model TestModel;
  double x = 15;
  double answer = 1;
  double result = 0;
  int status = TestModel.SmartCalculation(str, &result, x, 0);
  EXPECT_EQ(status, Ok);
  EXPECT_DOUBLE_EQ(result, answer);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
