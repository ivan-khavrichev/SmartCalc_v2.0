#include "s21_controller.h"

namespace s21 {

int Controller::CalcResult(std::string input, double *result, double x,
                           int check_x) {
  return model_->SmartCalculation(input, result, x, check_x);
}

}  // namespace s21
