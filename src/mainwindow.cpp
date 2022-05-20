/**
 * @file mainwindow.cpp
 * @author Muhammad Ahmad (muhammadathabet@gmail.com)
 * @brief This file is responsible for the main window of the application.
 * @version 1.0.0-beta
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evaluatePostfix.h"
#include "qcustomplot.h"
#include <QMessageBox>

Function_Plotter::Function_Plotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Function_Plotter)
{
    ui->setupUi(this);
    //ui->lineEdit->setText("Enter f(x) here.");
}

Function_Plotter::~Function_Plotter()
{
    delete ui;
}


/**
 * @brief Set Minimum value for the spin box on Changing value of start point spin box.
 * 
 * @param arg1 The Value of the start point spin box.
 */
 */
void Function_Plotter::on_startPoint_valueChanged(int arg1)
{
    ui->endPoint->setMinimum(arg1 + 10);
}

/**
 * @brief This Funcion is responsible for evaluating and plotting the graph of the function After plot button is pressed.
 * 
 */
void Function_Plotter::on_PlotButton_clicked()
{
    QString userInput = ui->lineEdit->text();
    int start = ui->startPoint->value();
    int end = ui->endPoint->value();
    float points = ui->nPoints->value();
    float steps = (end - start)/points;
    QString clean = input(userInput);
    QVector<QString> errors = isValid(clean);
    if(!errors.size()){
        try{
            QVector<QString> postfix = infix2Postfix(clean);
            QVector<double> x, y;
            float f;
            for(float i = 0; i <= points; i += 1){
                x.push_back(i * steps + start);
                f = evaluate(postfix, x[i]);
                y.push_back(f);
            }
            // Plotting Graph
            ui->customPlot->addGraph();
            ui->customPlot->graph(0)->setData(x, y);
            // Labelling Axes
            ui->customPlot->xAxis->setLabel("x");
            ui->customPlot->yAxis->setLabel("f(x)");
            ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
            // Rescaling Axes
            ui->customPlot->graph(0)->rescaleAxes();
            ui->customPlot->replot();
        }
        catch(...){
            QMessageBox errmsg;
            errmsg.setText("Please enter valid expression!");
            errmsg.setStandardButtons(QMessageBox::Ok);
            errmsg.exec();
        }
}
    else{
        QString errormsg = "";
        for(QString i : errors){errormsg += i + "\n";}
        QMessageBox msg;
        msg.setText(errormsg);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}

