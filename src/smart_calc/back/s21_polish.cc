#include "s21_calc.h"

namespace s21 {

int Model::ConvertPolish(int *status) {
  if (*status != Ok) {
    return *status;
  }
  int index_step = 0;
  while (index_step < static_cast<int>(list_.size())) {
    if (list_[index_step].type == Number ||
        list_[index_step].type == Variable) {
      list_polish_.push_back(list_[index_step]);
    } else if (list_[index_step].type == Function ||
               list_[index_step].type == BracketO) {
      list_tmp_.push_back(list_[index_step]);
    } else if (list_[index_step].type == Operat) {
      lexeme oper = LastLexeme();
      while (oper.priority >= list_[index_step].priority) {
        EmptyStackPolish(&oper);
      }
      list_tmp_.push_back(list_[index_step]);
    } else if (list_[index_step].type == BracketC) {
      lexeme oper = LastLexeme();
      while (oper.type != BracketO && oper.type != kEmpty) {
        EmptyStackPolish(&oper);
      }
      if (oper.type == BracketO) {
        list_tmp_.pop_back();
        oper = LastLexeme();
        if (oper.type == Function) {
          EmptyStackPolish(&oper);
        }
        if (oper.priority == UnOper) {
          EmptyStackPolish(&oper);
        }
      } else {
        *status = CalculationError;
      }
    }
    index_step++;
  }
  lexeme oper = LastLexeme();
  if (oper.type == BracketO || oper.type == BracketC) {
    *status = CalculationError;
  } else {
    while (!list_tmp_.empty() && *status != CalculationError) {
      *status = EmptyStackPolish(&oper);
    }
  }
  if (list_polish_.empty()) {
    *status = CalculationError;
  }
  return *status;
}

int Model::EmptyStackPolish(lexeme *operat) {
  int status = Ok;
  list_polish_.push_back(*operat);
  list_tmp_.pop_back();
  *operat = LastLexeme();
  if ((operat->type == BracketC || operat->type == BracketO)) {
    status = CalculationError;
  }
  return status;
}

s21::Model::lexeme Model::LastLexeme() {
  struct lexeme last_lexeme = {-1, -1, -1, '1', NULL};
  if (!list_tmp_.empty()) {
    last_lexeme = list_tmp_[list_tmp_.size() - 1];
  }
  return last_lexeme;
}

}  // namespace s21
