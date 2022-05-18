#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Function_Plotter; }
QT_END_NAMESPACE

class Function_Plotter : public QMainWindow
{
    Q_OBJECT

public:
    Function_Plotter(QWidget *parent = nullptr);
    ~Function_Plotter();

private slots:
    void on_startPoint_valueChanged(int arg1);

    void on_PlotButton_clicked();

private:
    Ui::Function_Plotter *ui;
};
#endif // MAINWINDOW_H
