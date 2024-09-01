#include "s21_calc.h"

namespace s21 {

int Model::UnarFunction(double (Model::*func_unar)(double)) {
  int status = CalculationError;
  if (!list_answer_.empty() && !list_polish_.empty()) {
    double num = list_answer_[list_answer_.size() - 1].value;
    double new_num = (this->*func_unar)(num);
    list_answer_[list_answer_.size() - 1].value = new_num;
    status = Ok;
  }
  return status;
}

int Model::BinarFunction(double (Model::*func_binar)(double, double)) {
  int status = CalculationError;
  if (list_answer_.size() > 1 && !list_polish_.empty()) {
    double num_1 = list_answer_[list_answer_.size() - 2].value;
    double num_2 = list_answer_[list_answer_.size() - 1].value;
    double new_num = (this->*func_binar)(num_1, num_2);
    list_answer_[list_answer_.size() - 2].value = new_num;
    list_answer_.pop_back();

    status = Ok;
  }
  return status;
}

double Model::MyCos(double number) { return cos(number); }

double Model::MySin(double number) { return sin(number); }

double Model::MyTan(double number) { return tan(number); }

double Model::MyAcos(double number) { return acos(number); }

double Model::MyAsin(double number) { return asin(number); }

double Model::MyAtan(double number) { return atan(number); }

double Model::MySqrt(double number) { return sqrt(number); }

double Model::MyLn(double number) { return log(number); }

double Model::MyLog(double number) { return log10(number); }

double Model::MyPlus(double number) { return number; }

double Model::MyMinus(double number) { return (-1 * number); }

double Model::MySum(double number_1, double number_2) {
  return (number_1 + number_2);
}

double Model::MySub(double number_1, double number_2) {
  return (number_1 - number_2);
}

double Model::MyMul(double number_1, double number_2) {
  return (number_1 * number_2);
}

double Model::MyDiv(double number_1, double number_2) {
  return (number_1 / number_2);
}

double Model::MyPow(double number_1, double number_2) {
  return pow(number_1, number_2);
}

double Model::MyMod(double number_1, double number_2) {
  return fmod(number_1, number_2);
}

int Model::MathCos() { return UnarFunction(&Model::MyCos); }

int Model::MathSin() { return UnarFunction(&Model::MySin); }

int Model::MathTan() { return UnarFunction(&Model::MyTan); }

int Model::MathAcos() { return UnarFunction(&Model::MyAcos); }

int Model::MathAsin() { return UnarFunction(&Model::MyAsin); }

int Model::MathAtan() { return UnarFunction(&Model::MyAtan); }

int Model::MathSqrt() { return UnarFunction(&Model::MySqrt); }

int Model::MathLn() { return UnarFunction(&Model::MyLn); }

int Model::MathLog() { return UnarFunction(&Model::MyLog); }

int Model::MathPlus() { return UnarFunction(&Model::MyPlus); }

int Model::MathMinus() { return UnarFunction(&Model::MyMinus); }

int Model::MathSum() { return BinarFunction(&Model::MySum); }

int Model::MathSub() { return BinarFunction(&Model::MySub); }

int Model::MathMul() { return BinarFunction(&Model::MyMul); }

int Model::MathDiv() { return BinarFunction(&Model::MyDiv); }

int Model::MathPow() { return BinarFunction(&Model::MyPow); }

int Model::MathMod() { return BinarFunction(&Model::MyMod); }

}  // namespace s21
