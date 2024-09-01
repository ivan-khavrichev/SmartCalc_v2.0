#include "s21_calc.h"

namespace s21 {

void Model::Foolproofing(int *status) {
  if (input_str_.length() == 0) {
    *status = EmptyInput;
  } else if (input_str_.length() != 0 && input_str_[0] == ' ') {
    *status = EmptyInput;
    while (input_str_[index_str_] != '\0' && *status != Ok) {
      index_str_++;
      ;
      if (input_str_[index_str_] != ' ' && input_str_[index_str_] != '\0') {
        *status = Ok;
      }
    }
  }
}

void Model::SkipSpace(int *status) {
  while (input_str_[index_str_] == ' ') {
    index_str_++;
  }
  if (input_str_[index_str_] == '\0') {
    *status = Ok;
  }
}

void Model::ParserBracket(int *status) {
  if (input_str_[index_str_] == '(') {
    PushList(&list_, BracketO, 0, 0, '(', NULL);
    *status = Ok;
    index_str_++;
  } else if (input_str_[index_str_] == ')') {
    PushList(&list_, BracketC, 0, 0, ')', NULL);
    *status = Ok;
    index_str_++;
  }
}

void Model::ParserFunction(int *status) {
  std::string functions[9] = {"cos",  "sin",  "tan", "acos", "asin",
                              "atan", "sqrt", "ln",  "log"};
  const char symbols[9] = {'c', 's', 't', 'C', 'S', 'T', 'q', 'l', 'L'};
  int (Model::*math_function[9])() = {
      &Model::MathCos,  &Model::MathSin,  &Model::MathTan,
      &Model::MathAcos, &Model::MathAsin, &Model::MathAtan,
      &Model::MathSqrt, &Model::MathLn,   &Model::MathLog};
  int index_found = -1;
  int len = 0;
  for (int i = 0; i < 9 && index_str_ != index_found; i++) {
    index_found = input_str_.find(functions[i], index_str_);
    len = functions[i].length();
    if (index_str_ == index_found) {
      PushList(&list_, Function, Func, 0, symbols[i], math_function[i]);
      *status = Ok;
      index_str_ += len;
    }
  }
}

void Model::ParserOperators(int *status) {
  std::string operators[6] = {"*", "/", "^", "mod", "+", "-"};
  int (Model::*math_operators[8])() = {
      &Model::MathMul, &Model::MathDiv, &Model::MathPow,  &Model::MathMod,
      &Model::MathSum, &Model::MathSub, &Model::MathPlus, &Model::MathMinus};
  int index_found = -1;
  int len = 0;
  for (int i = 0; i < 6 && index_str_ != index_found; i++) {
    index_found = input_str_.find(operators[i], index_str_);
    len = operators[i].length();
    if (index_str_ == index_found) {
      int precedence = Prioritize(input_str_[index_found]);
      int unar_factor = CheckUnarBinar();
      PushList(&list_, Operat, precedence, 0, input_str_[index_found],
               math_operators[i + unar_factor]);
      *status = Ok;
      index_str_ += len;
    }
  }
}

void Model::ParserNumber(int *status) {
  int flag_digit = 0;
  int flag_point = 0;
  int flag_exp = 0;
  int index_step = 0;
  int step_num = CheckNumber(&flag_digit, &flag_point, &flag_exp, index_step);
  if (step_num != 0) {
    index_step = step_num;
    while (step_num != 0 && input_str_[index_str_ + index_step] != '\0') {
      step_num = CheckNumber(&flag_digit, &flag_point, &flag_exp, index_step);
      index_step += step_num;
    }
    if (flag_point < 2 && flag_exp < 2) {
      std::string str_number = input_str_.substr(index_str_, index_step);
      double num = atof(str_number.c_str());
      PushList(&list_, Number, VarNum, num, 'n', NULL);
      *status = Ok;
      index_str_ += str_number.length();
    }
  } else if (input_str_[index_str_] == 'p' &&
             input_str_[index_str_ + 1] == 'i') {
    PushList(&list_, Number, VarNum, M_PI, 'p', NULL);
    *status = Ok;
    index_str_ += 2;
  } else if (input_str_[index_str_] == 'e') {
    PushList(&list_, Number, VarNum, M_E, 'e', NULL);
    *status = Ok;
    index_str_ += 1;
  }
}

void Model::ParserVariable(int *status, int check_x) {
  if (input_str_[index_str_] == 'x') {
    PushList(&list_, Variable, VarNum, 0, 'x', NULL);
    index_str_ += 1;
    if (check_x == 0) {
      *status = Ok;
    } else {
      *status = InvalidX;
    }
  }
}

int Model::CheckNumber(int *flag_digit, int *flag_point, int *flag_exp,
                       int index_step) {
  int len = 0;
  if (isdigit(input_str_[index_str_ + index_step]) != 0) {
    *flag_digit += 1;
    len = 1;
  } else if (input_str_[index_str_ + index_step] == '.') {
    *flag_point += 1;
    len = 1;
  } else if (input_str_[index_str_ + index_step] == 'E' &&
             (input_str_[index_str_ + index_step + 1] == '+' ||
              input_str_[index_str_ + 1] == '-')) {
    *flag_exp += 1;
    len = 2;
  } else if (input_str_[index_str_ + index_step] == 'E') {
    *flag_exp += 1;
    len = 1;
  }
  if (*flag_exp == 1 && *flag_digit == 0 && *flag_point == 0) {
    len = 0;
  }
  return len;
}

int Model::CheckUnarBinar() {
  int status = 0;
  if (list_.empty() == true) {
    status = kUnar;
  } else {
    int index_last = list_.size();
    if (list_[index_last - 1].type == Operat ||
        list_[index_last - 1].type == BracketO) {
      status = kUnar;
    }
  }
  return status;
}

int Model::Prioritize(char symbol) {
  int precedence = 0;
  if (symbol == '^') {
    precedence = Func;
  } else if (symbol != '-' && symbol != '+') {
    precedence = Oper;
  } else if ((symbol == '-' || symbol == '+') && CheckUnarBinar() == kUnar) {
    precedence = UnOper;
  } else {
    precedence = BinOper;
  }
  return precedence;
}

void Model::PushList(std::vector<struct lexeme> *list, int type, int priority,
                     double value, char symbol, int (Model::*func)()) {
  struct lexeme lex;
  lex.type = type;
  lex.priority = priority;
  lex.value = value;
  lex.symbol = symbol;
  lex.func = func;
  list->push_back(lex);
}

}  // namespace s21
