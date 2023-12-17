#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStringList calculationsHistory;

private slots:
    void numPressed();
    void opPressed();
    void eqPressed();
    void signPressed();
    void clearPressed();
    void perPressed();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
