#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDoubleSpinBox spinPipeL();
    QDoubleSpinBox spinHoleD();
    QDoubleSpinBox spinHoleI();
    QDoubleSpinBox spinMHead();
    QDoubleSpinBox spinMEnd();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnEnd_clicked();
    void on_btnGen_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
