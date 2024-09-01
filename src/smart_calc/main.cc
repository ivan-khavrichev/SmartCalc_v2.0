#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "front/s21_calculator.h"
#include "s21_controller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::Calculator w(&controller);
  w.show();
  return a.exec();
}
