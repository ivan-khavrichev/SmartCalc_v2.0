#include "s21_calc.h"

namespace s21 {

int Model::SmartCalculation(std::string input, double *result, double x,
                            int check_x) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");

  Reset();
  input_str_ = input;
  int status = Ok;

  Foolproofing(&status);

  while (input_str_[index_str_] != '\0' && status == Ok) {
    status = InvalidValue;

    SkipSpace(&status);
    ParserBracket(&status);
    ParserFunction(&status);
    ParserOperators(&status);
    ParserNumber(&status);
    ParserVariable(&status, check_x);
  }

  ConvertPolish(&status);
  Calculation(result, x, &status);

  return status;
}

int Model::Calculation(double *answer, double x, int *status) {
  if (*status != Ok) {
    return *status;
  }
  int index_step = 0;
  while (index_step < static_cast<int>(list_polish_.size()) && *status == Ok) {
    if (list_polish_[index_step].type == Number) {
      list_answer_.push_back(list_polish_[index_step]);
    } else if (list_polish_[index_step].type == Variable) {
      PushList(&list_answer_, Number, VarNum, x, 'n', NULL);
    } else if (list_polish_[index_step].type == Function ||
               list_polish_[index_step].type == Operat) {
      if (list_answer_.empty()) {
        *status = CalculationError;
      } else {
        *status = (this->*(list_polish_[index_step]).func)();
      }
    }
    index_step++;
  }
  if (!list_answer_.empty()) {
    list_answer_.size();
    if (list_answer_.size() > 1) {
      *status = CalculationError;
    } else {
      *answer = list_answer_[0].value;
    }
  }
  return *status;
}

void Model::Reset() {
  list_.clear();
  list_polish_.clear();
  list_tmp_.clear();
  list_answer_.clear();
  input_str_.clear();
  index_str_ = 0;
}

}  // namespace s21
