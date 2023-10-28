#include "mainwindow.h"

#include <QApplication>
#include <Qfont>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 设置字体
    int fontID = QFontDatabase::addApplicationFont(":/fonts/HarmonyOS_Sans_SC_Regular.ttf");
    QString HarmonyOSSC = QFontDatabase::applicationFontFamilies ( fontID ).at(0);
    QFont font(HarmonyOSSC,10);
    QApplication::setFont(font);
    w.show();
    return a.exec();
}
