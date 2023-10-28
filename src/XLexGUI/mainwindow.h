#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <Windows.h>
#include "XLex.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void BtnOpenFileClicked();
    void BtnClearClicked();
    void BtnNFAClicked();
    void BtnDFAClicked();
    void BtnMinDFAClicked();
    void BtntoCodeClicked();

    void on_btn_last_clicked();
    void on_btn_next_clicked();

private:
    Ui::MainWindow *ui;
    XLex xlex;
    int input_index;
    int max_index;

    std::vector<QString> word2vec;
};
#endif // MAINWINDOW_H
