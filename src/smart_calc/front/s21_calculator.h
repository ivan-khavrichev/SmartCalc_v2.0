#ifndef CPP3_SMARTCALC_V2_SMART_CALC_FRONT_S21_CALCULATOR_H_
#define CPP3_SMARTCALC_V2_SMART_CALC_FRONT_S21_CALCULATOR_H_

#include <QColor>
#include <QLineEdit>
#include <QMainWindow>
#include <QWidget>

#include "./../s21_controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

namespace s21 {
class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(Controller *controller, QWidget *parent = nullptr);
  ~Calculator();

 private slots:

  void SimpleButton();
  void FunctionButton();
  void HardButton();
  void AllClearButton();
  void BackspaceButton();
  void EqButton();
  void PlotButton();
  void AnswerPreparation();
  QLineEdit *LineFocusInput();
  void Stylize();

 private:
  const static int kMaxValue = 1000000.0;
  const static int kMinValue = -1000000.0;
  Ui::Calculator *ui;
  s21::Controller *controller_;

  std::string str_x_, str_, str_x_min_, str_x_max_, str_y_min_, str_y_max_;
  double value_x_min_, value_x_max_, value_y_min_, value_y_max_, step_,
      value_x_;

  QVector<double> x_, y_;

  QColor background_color_;
  QColor axis_color_;
  QColor graph_line_color_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SMART_CALC_FRONT_S21_CALCULATOR_H_
