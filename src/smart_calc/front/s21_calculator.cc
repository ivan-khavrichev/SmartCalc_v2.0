#include "s21_calculator.h"

#include <QPixmap>

#include "ui_s21_calculator.h"

namespace s21 {

Calculator::Calculator(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  controller_ = controller;
  ui->setupUi(this);

  ui->input->setMaxLength(255);
  ui->input_x->setMaxLength(50);

  background_color_ = QColor(0, 0, 0, 0);
  axis_color_ = QColor(255, 255, 255);
  graph_line_color_ = QColor(241, 164, 60);

  Stylize();

  QPushButton *simle_buttons[] = {
      ui->pushButton_1,         ui->pushButton_2,         ui->pushButton_3,
      ui->pushButton_4,         ui->pushButton_5,         ui->pushButton_6,
      ui->pushButton_7,         ui->pushButton_8,         ui->pushButton_9,
      ui->pushButton_0,         ui->pushButton_x,         ui->pushButton_e,
      ui->pushButton_dot,       ui->pushButton_plus,      ui->pushButton_minus,
      ui->pushButton_bracket_o, ui->pushButton_bracket_c, ui->pushButton_mod,
      ui->pushButton_pow};

  QPushButton *function_buttons[] = {ui->pushButton_ln,   ui->pushButton_log,
                                     ui->pushButton_sin,  ui->pushButton_cos,
                                     ui->pushButton_tan,  ui->pushButton_asin,
                                     ui->pushButton_acos, ui->pushButton_atan};

  QPushButton *hard_button[] = {ui->pushButton_pi, ui->pushButton_EE,
                                ui->pushButton_div, ui->pushButton_mul,
                                ui->pushButton_sqrt};

  for (QPushButton *button : simle_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(SimpleButton()));
  }

  for (QPushButton *button : function_buttons) {
    connect(button, SIGNAL(clicked()), this, SLOT(FunctionButton()));
  }

  for (QPushButton *button : hard_button) {
    connect(button, SIGNAL(clicked()), this, SLOT(HardButton()));
  }

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AllClearButton()));
  connect(ui->pushButton_backspace, SIGNAL(clicked()), this,
          SLOT(BackspaceButton()));

  connect(ui->pushButton_eq, SIGNAL(clicked()), this, SLOT(EqButton()));

  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(PlotButton()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::SimpleButton() {
  QLineEdit *line_input = LineFocusInput();
  QPushButton *button = (QPushButton *)sender();
  line_input->setText(line_input->text() + button->text());

  line_input->setFocus();
}

void Calculator::FunctionButton() {
  QLineEdit *line_input = LineFocusInput();
  QPushButton *button = (QPushButton *)sender();
  line_input->setText(line_input->text() + button->text() + "(");

  line_input->setFocus();
}

void Calculator::HardButton() {
  QLineEdit *line_input = LineFocusInput();
  QPushButton *button = (QPushButton *)sender();

  QString hard_symbols[5] = {"π", "EE", "÷", "×", "√"};
  QString simle_symbols[5] = {"pi", "E", "/", "*", "sqrt("};
  for (int i = 0; i < 5; i++) {
    if (button->text() == hard_symbols[i]) {
      line_input->setText(line_input->text() + simle_symbols[i]);
    }
  }

  line_input->setFocus();
}

void Calculator::AllClearButton() {
  QLineEdit *line_input = LineFocusInput();
  line_input->clear();

  line_input->setFocus();
}

void Calculator::BackspaceButton() {
  QLineEdit *line_input = LineFocusInput();
  line_input->backspace();

  line_input->setFocus();
}

void Calculator::EqButton() {
  bool empty_x = true;
  double x_value = 0;
  double error_x = 0;
  double result = 0;
  double error = 0;

  str_ = ui->input->text().toStdString();

  empty_x = ui->input_x->displayText().isEmpty();

  if (empty_x == false) {
    str_x_ = ui->input_x->text().toStdString();
    error_x = controller_->CalcResult(str_x_, &x_value, 0, 1);
  }

  error = controller_->CalcResult(str_, &result, x_value, empty_x);

  if (error == EmptyInput) {
    AnswerPreparation();
    ui->input->setText("EMPTY INPUT");
  } else if (error == InvalidValue) {
    AnswerPreparation();
    ui->input->setText("INVALID VALUE");
  } else if (error == CalculationError) {
    AnswerPreparation();
    ui->input->setText("CALCULATION ERROR");
  } else if (error == InvalidX || error_x != Ok) {
    AnswerPreparation();
    ui->input->setText("INVALID X");
  } else if (error == Ok) {
    AnswerPreparation();
    QString ans = QString::number(result, 'f', 7);
    ui->input->setText(ans);
  }

  ui->input->setFocus();
}

void Calculator::PlotButton() {
  double error_x_min = 0;
  double error_x_max = 0;
  double error_y_min = 0;
  double error_y_max = 0;
  double result = 0;
  int status = 0;

  str_ = ui->input->text().toStdString();

  ui->plot_window->clearGraphs();

  str_x_min_ = ui->x_min->text().toStdString();
  str_x_max_ = ui->x_max->text().toStdString();
  str_y_min_ = ui->y_min->text().toStdString();
  str_y_max_ = ui->y_max->text().toStdString();

  error_x_min = controller_->CalcResult(&str_x_min_[0], &value_x_min_, 0, 1);
  error_x_max = controller_->CalcResult(&str_x_max_[0], &value_x_max_, 0, 1);
  error_y_min = controller_->CalcResult(&str_y_min_[0], &value_y_min_, 0, 1);
  error_y_max = controller_->CalcResult(&str_y_max_[0], &value_y_max_, 0, 1);

  if (error_x_min == Ok && error_x_max == Ok && error_y_min == Ok &&
      error_y_max == Ok && value_x_max_ > value_x_min_ &&
      value_y_max_ > value_y_min_ && value_x_min_ >= kMinValue &&
      value_y_min_ >= kMinValue && value_x_max_ <= kMaxValue &&
      value_y_max_ <= kMaxValue) {
    ui->plot_window->xAxis->setRange(value_x_min_, value_x_max_);
    ui->plot_window->yAxis->setRange(value_y_min_, value_y_max_);
    ui->plot_window->replot();

    step_ = (value_x_max_ - value_x_min_) / 10000.0;

    for (value_x_ = value_x_min_; value_x_ <= value_x_max_ && status == Ok;
         value_x_ += step_) {
      status = controller_->CalcResult(str_, &result, value_x_, 0);
      if (status == Ok && result <= kMaxValue && result >= kMinValue &&
          result == result) {
        x_.push_back(value_x_);
        y_.push_back(result);
      } else if (status == EmptyInput) {
        AnswerPreparation();
        ui->input->setText("EMPTY INPUT");
      } else if (status == InvalidValue) {
        AnswerPreparation();
        ui->input->setText("INVALID VALUE");
      } else if (status == CalculationError) {
        AnswerPreparation();
        ui->input->setText("CALCULATION ERROR");
      }
    }
    ui->plot_window->addGraph();
    ui->plot_window->graph(0)->setPen(QPen(graph_line_color_, 2));
    ui->plot_window->graph(0)->setData(x_, y_);
    ui->plot_window->replot();
    x_.clear();
    y_.clear();

    if (status == Ok) {
      AnswerPreparation();
    }

    ui->input->setFocus();

  } else {
    ui->x_min->clear();
    ui->x_max->clear();
    ui->y_min->clear();
    ui->y_max->clear();
    ui->entered->clear();
    ui->entered->setText(ui->input->text());
    ui->input->clear();
    ui->input->setText("INVALID BORDERS");

    ui->input->setFocus();
  }
}

QLineEdit *Calculator::LineFocusInput() {
  QLineEdit *line_input = NULL;
  QLineEdit *line_inputs[] = {
      ui->input, ui->input_x, ui->x_min, ui->x_max, ui->y_min, ui->y_max,
  };
  for (QLineEdit *line : line_inputs) {
    if (line->hasFocus() == true) {
      line_input = line;
    }
  }
  return line_input;
}

void Calculator::AnswerPreparation() {
  ui->entered->clear();
  if (ui->input_x->displayText().isEmpty()) {
    ui->entered->setText(ui->input->text());
  } else {
    ui->entered->setText(ui->input->text() + ", x = " + ui->input_x->text());
  }
  ui->input->clear();
  ui->input_x->clear();
}

void Calculator::Stylize() {
  ui->plot_window->setBackground(QBrush(background_color_));
  QPen axisPen(axis_color_);
  axisPen.setWidth(1);
  ui->plot_window->xAxis->setBasePen(axisPen);
  ui->plot_window->yAxis->setBasePen(axisPen);
  ui->plot_window->xAxis->setTickPen(axisPen);
  ui->plot_window->yAxis->setTickPen(axisPen);
  ui->plot_window->xAxis->setSubTickPen(axisPen);
  ui->plot_window->yAxis->setSubTickPen(axisPen);
  ui->plot_window->xAxis->setTickLabelColor(axis_color_);
  ui->plot_window->yAxis->setTickLabelColor(axis_color_);
  ui->plot_window->xAxis->setLabelColor(axis_color_);
  ui->plot_window->yAxis->setLabelColor(axis_color_);
}

}  // namespace s21
