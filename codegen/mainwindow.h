#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>
#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <nlohmann/json.hpp>

#define FEED "feed"
#define DRILL "drill"
#define CUT "cut"
#define END "end"
#define INSTRUCTION "inst"
#define VALUE "value"

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

    struct DataSrc {
        double pipeL;
        double holeD;
        double holeI;
        double merginHead;
        double merginEnd;
    };

    void makeFile(void);
    QString makeData(DataSrc dataSrc);
    bool validation(DataSrc dataSrc);
    uint16_t calcHoleNumber(DataSrc dataSrc);

};
#endif // MAINWINDOW_H
