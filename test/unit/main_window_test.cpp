#include "ui/main_window.h"

#include <she_test.h>

#include <QApplication>

// 全局的 QApplication
int argc     = 0;
char *argv[] = {nullptr};

// 定义全局变量
QApplication *app = nullptr;

TEST(unit, main_window_test) {
  int argc     = 0;
  char *argv[] = {nullptr};
  QApplication app(argc, argv);  // 初始化 QApplication

  // 创建 main_window 实例
  main_window window;

  window.show();

  // 进入事件循环
  app.exec();
}