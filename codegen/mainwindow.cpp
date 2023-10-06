#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnEnd_clicked() {
    if (QMessageBox::question(this, tr("Question"), tr("Quit?")) == QMessageBox::Yes) exit(0);
    return;
}

void MainWindow::on_btnPreview_clicked() {
    QMessageBox::information(this, tr("Error"), tr("Comming Soon..."));
    return;
}

void MainWindow::on_btnGen_clicked() {
    if (!validation()) {
        QMessageBox::warning(this, tr("Error"), tr("Invaild value."));
        return;
    }
    QMessageBox::information(this, tr("OK"), tr("Vaild value!"));
    return;
}

bool MainWindow::validation(void) {
    bool result;
    double holeD = ui->spinHoleD->value();
    if (ui->spinPipeL->value() >= holeD && holeD > 0.0 && ui->spinHoleI->value() > 0.0 && ui->spinMHead->value() >= 0.0 && ui->spinMEnd->value() >= 0.0 )
        result = true;
    else result = false;
    return result;
}
