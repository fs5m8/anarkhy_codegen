#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
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
    void on_btnPreview_clicked();

private:
    Ui::MainWindow *ui;
    void makeFile(void);
    QString makeData(double pipeL, double holeD, double holeI, double merginHead, double merginEnd);
    bool validation(double pipeL, double holeD, double holeI, double merginHead, double merginEnd);
    uint16_t calcHolenumber(double pipeL, double holeI, double merginHead, double merginEnd);

};
#endif // MAINWINDOW_H
