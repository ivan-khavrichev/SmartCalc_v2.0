/*!
\file
\brief Заголовочный файл с описанием функций, применяемых для осуществления
вычислений

Данный файл содержит в себе определения
функций, используемых в проекте SmartCalc v2.0.
*/

#ifndef CPP3_SMARTCALC_V2_SMART_CALC_BACK_S21_CALC_H_
#define CPP3_SMARTCALC_V2_SMART_CALC_BACK_S21_CALC_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

/**
 * @brief  Перечисление, используемое для обозначения ошибок
 */
enum Errors {
  Ok,  ///< код успешного завершения работы функции
  EmptyInput,  ///< код ошибки, возникаемой при введении пустой строки
  InvalidValue,  ///< код ошибки, возникаемой при введении некорректной строки
  CalculationError,  ///< код ошибки, возникаемой при введении некорректного
                     ///< математического выражения
  InvalidX  ///< код ошибки, возникаемой при введении некорректной переменной
};

/**
 * @brief Перечисление, используемое в стеке лексем для обозначения типа лексемы
 */
enum TypeLexeme {
  Variable,  ///< перменная
  Number,    ///< число
  Operat,    ///< оператор
  Function,  ///< функция
  BracketO,  ///< открывающая скобка
  BracketC   ///< закрывающая скобка
};

/**
 * @brief  Перечисление, используемое в стеке лексем для обозначения приоритета
 */
enum PriorityLexeme {
  VarNum,   ///< приоритет числа и переменной
  BinOper,  ///< приоритет бинарных операций: + и -
  Oper,     ///< приоритет для * и /
  Func,     ///< приоритет для функций и для ^
  UnOper    ///< приоритет унарных операций: + и -
};

namespace s21 {
class Model {
 public:
  Model(){};
  ~Model(){};

  /**
   * @brief итоговая функци калькулятора
   * @param input введённая строка
   * @param result переменная для записи итога вычислений
   * @param x значение переменной
   * @param check_x статус наличия значения переменной
   * @return int статус ошибки, если допущена ошибка, иначе 0
   */
  int SmartCalculation(std::string input, double *result, double x,
                       int check_x);

 private:
  /**
   * @brief Структура, с характеристиками лексем стека
   */
  struct lexeme {
    int type;              ///< тип лексемы
    int priority;          ///< приоритет лексемы
    double value;          ///< значение числа
    char symbol;           ///< символ
    int (Model::*func)();  ///< указатель на функцию, callback
  };

  /**
   * @brief Стек с лексемами введённой строки
   */
  std::vector<struct lexeme> list_;
  /**
   * @brief Стек с лексемами, записанными в постфиксной форме
   */
  std::vector<struct lexeme> list_polish_;
  /**
   * @brief Дополнительный стек для преобразования в записи в польскую нотацию
   */
  std::vector<struct lexeme> list_tmp_;
  /**
   * @brief Стек c итоговым результатом
   */
  std::vector<struct lexeme> list_answer_;

  std::string input_str_;  ///< входящая строка для преобразования
  int index_str_;  ///< индекс элемента входящей строки

  const static int kEmpty = -1;  ///< код проверки на пустоту структуры лексем
  const static int kUnar = 2;  ///< код возвращения унарного оператора

  /**
   * @brief функция защиты от дурака, валидирует строку на пустоту
   *  изменяет статус на 1, если строка пустая, если в ней только пробелы
   * @param status статус ошибки
   */
  void Foolproofing(int *status);

  /**
   * @brief функция пропуска пробела в строке
   * @param status статус ошибки
   */
  void SkipSpace(int *status);

  /**
   * @brief функция парсера строки, определяет лексемы, как скобки
   * изменяют статус на Ok, если лексема найдена успешно
   * @param status статус ошибки
   */
  void ParserBracket(int *status);

  /**
   * @brief функция парсера строки, определяет лексемы, как функции
   * изменяют статус на Ok, если лексема найдена успешно
   * @param status статус ошибки
   */
  void ParserFunction(int *status);

  /**
   * @brief функция парсера строки, определяет лексемы, как операторы
   * изменяют статус на Ok, если лексема найдена успешно
   * @param status статус ошибки
   */
  void ParserOperators(int *status);

  /**
   * @brief функция парсера строки, определяет лексемы, как числа
   * изменяют статус на Ok, если лексема найдена успешно
   * @param status статус ошибки
   */
  void ParserNumber(int *status);

  /**
   * @brief функция парсера строки, определяет лексемы, как переменной
   * изменяют статус на Ok, если лексема найдена успешно
   * @param status статус ошибки
   * @param check_x статус наличия переменной в строке
   */
  void ParserVariable(int *status, int check_x);

  /**
   * @brief функция проверки корректной записи числа;
   * через указатели на флаги подсчитывает количество точек и степеней в числе
   * @param flag_digit  счётчик чисел
   * @param flag_point  счётчик точек
   * @param flag_exp  счётчик экспоненты
   * @param index_step  шаг сдвига по строке
   * @return int величина сдвига строки: если число начинается со степени; 0,
   * если число некорректное
   */
  int CheckNumber(int *flag_digit, int *flag_point, int *flag_exp,
                  int index_step);

  /**
   * @brief функция для определения бинарности-унарности "+" и "-"
   * @return int 2, если унарный и 0, если бинарный
   */
  int CheckUnarBinar();

  /**
   * @brief функция выставления приоритета для операторов
   * @param symbol символ строки
   * @return int  1, если бинарный "+" или "-";
   * 4, если унарный "+" или "-", 2, если другие операторы
   */
  int Prioritize(char symbol);

  /**
   * @brief функция возврата последней лексемы из временного списка list_tmp_
   * @param list_tmp список лексем
   * @return lexeme последнюю лексему, если лексемы в списке нет
   * лексем, лексему с параметрами, равными -1
   */
  struct lexeme LastLexeme();

  /**
   * @brief функция для заполнения характеристик лексемам и её запись в стек
   * @param list стек, который заполняется
   * @param type тип лексемы
   * @param priority приоритет лексемы
   * @param value значение числа
   * @param symbol символ
   * @param math_function указатель на функцию, callback
   * @param status переключатель стека, который заполняется
   */
  void PushList(std::vector<struct lexeme> *list, int type, int priority,
                double value, char symbol, int (Model::*func)());

  /**
   * @brief функция обработки унарных операций и функций
   * @param list_numbers стек с числами
   * @param list_operators стек с опретаорами
   * @param func_unar ссылка на унарные функции
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int UnarFunction(double (Model::*func_unar)(double));

  /**
   * @brief  функция обработки бинарных операций и функций
   * @param list_numbers стек с числами
   * @param list_operators стек с опретаорами
   * @param func_binar ссылка на бинарные функции
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int BinarFunction(double (Model::*func_binar)(double, double));

  // функции унарные и бинарные
  // унарные принимают одно число, бинарные - два
  // все функции возвращают результат выполнения операций

  /**
   * @brief унарная функция косинуса, вычисляет косинус числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyCos(double number);

  /**
   * @brief унарная функция синуса, вычисляет синус числа
   * @param number число
   * @return double вычисленное значение
   */
  double MySin(double number);

  /**
   * @brief унарная функция тангенса, вычисляет тангенс числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyTan(double number);

  /**
   * @brief унарная функция аргкосинуса, вычисляет аргкосинус числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyAcos(double number);

  /**
   * @brief унарная функция аргсинуса, вычисляет аргсинус числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyAsin(double number);

  /**
   * @brief унарная функция аргтангенса, вычисляет аргтангенс числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyAtan(double number);

  /**
   * @brief унарная функция квадратного корня, вычисляет квадратный корень числа
   * @param number число
   * @return double вычисленное значение
   */
  double MySqrt(double number);

  /**
   * @brief унарная функция натурального логарифма, вычисляет натуральный
   * логарифм числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyLn(double number);

  /**
   * @brief унарная функция десятичного логарифма, вычисляет десятичный логарифм
   * числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyLog(double number);

  /**
   * @brief унарная функция плюса, вычисляет знак числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyPlus(double number);

  /**
   * @brief унарная функция минуса, вычисляет знак числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyMinus(double number);

  /**
   * @brief бинарная функция суммы, вычисляет сумму двух чисел
   * @param number число
   * @return double вычисленное значение
   */
  double MySum(double number_1, double number_2);

  /**
   * @brief бинарная функция вычитания, вычисляет разность двух чисел
   * @param number число
   * @return double вычисленное значение
   */
  double MySub(double number_1, double number_2);

  /**
   * @brief бинарная функция умножения, вычисляет произведение двух чисел
   * @param number число
   * @return double вычисленное значение
   */
  double MyMul(double number_1, double number_2);

  /**
   * @brief бинарная функция деления, вычисляет частное двух чисел
   * @param number число
   * @return double вычисленное значение
   */
  double MyDiv(double number_1, double number_2);

  /**
   * @brief бинарная функция возведения в степень, вычисляет степень числа
   * @param number число
   * @return double вычисленное значение
   */
  double MyPow(double number_1, double number_2);

  /**
   * @brief бинарная функция взятия остатка, вычисляет остаток от деления
   * @param number число
   * @return double вычисленное значение
   */
  double MyMod(double number_1, double number_2);

  /**
   * @brief функция косинуса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathCos();

  /**
   * @brief функция синуса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathSin();

  /**
   * @brief функция тангенса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathTan();

  /**
   * @brief функция аргкосинуса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathAcos();

  /**
   * @brief функция аргсинуса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathAsin();

  /**
   * @brief функция аргтангенса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathAtan();

  /**
   * @brief функция квадратного корня, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathSqrt();

  /**
   * @brief функция натурального логарифма, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathLn();

  /**
   * @brief функция десятичного логарифма, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathLog();

  /**
   * @brief функция плюса, передаваемая в структуру лексемы
   * @return int  1, если операцию провести невозможно, иначе 0
   */
  int MathPlus();

  /**
   * @brief функция минуса, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathMinus();

  /**
   * @brief функция сложения, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathSum();

  /**
   * @brief функция вычитания, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathSub();

  /**
   * @brief функция умножения, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathMul();

  /**
   * @brief функция деления, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathDiv();

  /**
   * @brief функция возведения в степень, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathPow();

  /**
   * @brief функция деления с остатком, передаваемая в структуру лексемы
   * @return int 1, если операцию провести невозможно, иначе 0
   */
  int MathMod();

  /**
   * @brief функция конвертации записи в инфиксной форме в постфиксную
   * с помощью алгоритма «сортировочная станция»
   * @param status статус ошибки, если ошибка, если успешно 0
   * @return int статус ошибки, если ошибка, если успешно 0
   */
  int ConvertPolish(int *status);

  /**
   * @brief функция очистки временного стека
   * добавляет верхний элемент стека в выходную запись и удаляет этот элемент
   * @param operat последняя лексема во временном стеке
   * @return int 1, если в стеке лишняя скобка, иначе 0
   */
  int EmptyStackPolish(lexeme *operat);

  /**
   * @brief функция вычисления введённой строки
   * @param answer переменная для записи итога вычислений
   * @param x значение переменной
   * @param status статус наличия значения переменной
   * @return int стутус ошибки, если она была, иначе 0
   */
  int Calculation(double *answer, double x, int *status);

  /**
   * @brief функция очистки векторов и обнуления переменных класса
   */
  void Reset();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SMART_CALC_BACK_S21_CALC_H_
