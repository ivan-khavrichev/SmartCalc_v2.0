#ifndef CPP3_SMARTCALC_V2_SMART_CALC_BACK_S21_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SMART_CALC_BACK_S21_CONTROLLER_H_

#include <iostream>

#include "back/s21_calc.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  explicit Controller(s21::Model *model) { model_ = model; }
  ~Controller() = default;

  int CalcResult(std::string input, double *result, double x, int check_x);

 private:
  s21::Model *model_;
};

}  // namespace s21

#endif
