#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>

double calculatedValue = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool perTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize everything
    ui->NumDisplay->setText(QString::number(calculatedValue));
    QPushButton *numButtons[10];

    for (int i = 0; i < 10; i++) {
        QString bName = "Button" + QString::number(i);

        // Find the widget by name
        numButtons[i] = MainWindow::findChild<QPushButton *>(bName);
        // Call numPressed slot when the button is released
        connect(numButtons[i], &QPushButton::released, this, &MainWindow::numPressed);
    }

    // Connect operators
    connect(ui->AddButtton, &QPushButton::released, this, &MainWindow::opPressed);
    connect(ui->SubtractButton, &QPushButton::released, this, &MainWindow::opPressed);
    connect(ui->DivideButton, &QPushButton::released, this, &MainWindow::opPressed);
    connect(ui->MultiplyButton, &QPushButton::released, this, &MainWindow::opPressed);

    // Connect EQ button
    connect(ui->EqualsButton, &QPushButton::released, this, &MainWindow::eqPressed);

    // Connect modifiers
    connect(ui->PosNegButton, &QPushButton::released, this, &MainWindow::signPressed);
    connect(ui->ClearButton, &QPushButton::released, this, &MainWindow::clearPressed);
    connect(ui->PercentButton, &QPushButton::released, this, &MainWindow::perPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// A number is pressed
void MainWindow::numPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString bVal = button->text();
    QString displayVal = ui->NumDisplay->text();
    if ((displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0)) {
        ui->NumDisplay->setText(bVal);
    } else {
        QString newVal = displayVal + bVal;
        double dblNewVal = newVal.toDouble();
        ui->NumDisplay->setText(QString::number(dblNewVal, 'g', 16));
    }
}

// A mathematical button is pressed
void MainWindow::opPressed()
{
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    perTrigger = false;

    QString displayVal = ui->NumDisplay->text();
    calculatedValue = displayVal.toDouble();
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString bVal = button->text();

    // Figure out which operation was pressed
    if (QString::compare(bVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(bVal, "X", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if (QString::compare(bVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if (QString::compare(bVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    } else if (QString::compare(bVal, "%", Qt::CaseInsensitive) == 0) {
        perTrigger = true;
    }
    ui->NumDisplay->setText("");
}

// Equals button pressed
void MainWindow::eqPressed()
{
    double sol = 0.0;
    QString displayVal = ui->NumDisplay->text();
    double dblDispVal = displayVal.toDouble();

    // Figure out which operation needs to be done and do it
    if (divTrigger || mulTrigger || addTrigger || subTrigger || perTrigger) {
        if (divTrigger) {
            sol = calculatedValue / dblDispVal;
            calculationsHistory.append(QString::number(calculatedValue) +
                                       " / " + QString::number(dblDispVal) +
                                       " = " + QString::number(sol));
        } else if (mulTrigger) {
            sol = calculatedValue * dblDispVal;
            calculationsHistory.append(QString::number(calculatedValue) +
                                       " * " + QString::number(dblDispVal) +
                                       " = " + QString::number(sol));
        } else if (addTrigger) {
            sol = calculatedValue + dblDispVal;
            calculationsHistory.append(QString::number(calculatedValue) +
                                       " + " + QString::number(dblDispVal) +
                                       " = " + QString::number(sol));
        } else if (subTrigger) {
            sol = calculatedValue - dblDispVal;
            calculationsHistory.append(QString::number(calculatedValue) +
                                       " - " + QString::number(dblDispVal) +
                                       " = " + QString::number(sol));
        }
    }
    ui->NumDisplay->setText(QString::number(sol));
}

// Change sign button pressed
void MainWindow::signPressed()
{
    QString val = ui->NumDisplay->text();
    QString Exp = "[-]?[0-9.]*";
    QRegularExpression re(Exp);
    QRegularExpressionMatchIterator matchIterator = re.globalMatch(val);

    if (matchIterator.hasNext()) {
        double dblDispVal = val.toDouble();
        double dblDispValSign = -1 * dblDispVal;
        ui->NumDisplay->setText(QString::number(dblDispValSign));
    }
}

// Clear button pressed
void MainWindow::clearPressed()
{
    calculatedValue = 0;
    ui->NumDisplay->setText("");
}

// Percentage button pressed
void MainWindow::perPressed()
{
    QString val = ui->NumDisplay->text();
    double numVal = val.toDouble();
    double percentage = numVal / 100;
    ui->NumDisplay->setText(QString::number(percentage));
}

void MainWindow::on_pushButton_clicked()
{
    QString historyText;
    for (const QString &entry : calculationsHistory) {
        historyText += entry + "\n";
    }

    ui->textBrowser->setText("Previous Calculations:\n" + historyText);
}


void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Felina_FinalProject_CalculationHistory");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setBaseSize(QSize(400, 300));
    msgBox.setText("This is my algorithm :<br />Users will see a calculator in the GUI. Users will be able to use this calculator like a normal calculator. They can input any number and mathematical operator to get their desired calculation. Users can also view the calculations they have done previously by pressing the 'History' button.");
    msgBox.exec();
}

