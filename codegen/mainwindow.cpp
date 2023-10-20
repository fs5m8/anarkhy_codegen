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
    makeFile();
    return;
}

void MainWindow::makeFile(void) {
    double pipeL = ui->spinPipeL->value();
    double holeD = ui->spinHoleD->value();
    double holeI = ui->spinHoleI->value();
    double merginHead = ui->spinMHead->value();
    double merginEnd = ui->spinMEnd->value();
    if (!validation(pipeL, holeD, holeI, merginHead, merginEnd)) {
        QMessageBox::warning(this, tr("Error"), tr("Invaild value."));
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, tr("Save Instruction File"), "", tr("Text file (*.txt)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Invaild file name."));
        return;
    }
    QMessageBox::information(this, tr("OK"), tr("Vaild file name!"));
    QString strFiledata = makeData(pipeL, holeD, holeI, merginHead, merginEnd);
    QFile fileinst(filename);
    if (!fileinst.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Unable to open file"), fileinst.errorString());
        return;
    }
    QTextStream filestream(&fileinst);
    filestream << strFiledata;
    fileinst.close();
    QMessageBox::information(this, tr("OK"), tr("Done!"));
}

bool MainWindow::validation(double pipeL, double holeD, double holeI, double merginHead, double merginEnd) {
    bool result;
    if (pipeL >= holeD &&
        holeD > 0.0 &&
        holeI >= 0.0 &&
        merginHead >= 0.0 &&
        merginEnd >= 0.0 &&
        (pipeL - merginHead - merginEnd) >= 0.0 )
        result = true;
    else result = false;
    return result;
}

uint16_t MainWindow::calcHolenumber(double pipeL, double holeI, double merginHead, double merginEnd) {
    uint16_t numHole = 0;
    if (holeI != 0.0) numHole = std::floor(float(pipeL - merginHead - merginEnd / holeI));
    else numHole = 1;
    return numHole;
}
