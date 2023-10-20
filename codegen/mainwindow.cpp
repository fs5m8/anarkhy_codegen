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
    DataSrc dataSrc;
    dataSrc.pipeL = ui->spinPipeL->value();
    dataSrc.holeD = ui->spinHoleD->value();
    dataSrc.holeI = ui->spinHoleI->value();
    dataSrc.merginHead = ui->spinMHead->value();
    dataSrc.merginEnd = ui->spinMEnd->value();
    if (!validation(dataSrc)) {
        QMessageBox::warning(this, tr("Error"), tr("Invaild value."));
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Instruction File"), "", tr("Text file (*.txt)"));
    if (filename.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Invaild file name."));
        return;
    }
    QMessageBox::information(this, tr("OK"), tr("Vaild file name!"));
    QString strFiledata = makeData(dataSrc);
    QFile fileinst(filename);
    if (!fileinst.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Unable to open file"), fileinst.errorString());
        return;
    }
    QTextStream filestream(&fileinst);
    filestream << strFiledata.toUtf8();
    fileinst.close();
    QMessageBox::information(this, tr("OK"), tr("Done!"));
}

QString MainWindow::makeData(DataSrc dataSrc) {
    Mfunc func;
    QString data = "";
    uint16_t numHole = calcHoleNumber(dataSrc);
    double surplus = dataSrc.pipeL - ((numHole * dataSrc.holeI) + dataSrc.merginHead + dataSrc.merginEnd);
    data += func.FEED + QString::number(dataSrc.merginHead) + func.EOL;
    for (int i = 0; i < numHole; i++){
        data += func.DRILL + func.EOL;
        data += func.FEED + QString::number(dataSrc.holeI) + func.EOL;
    }
    data += func.DRILL + func.EOL;
    data += func.FEED + QString::number(dataSrc.merginEnd) + func.EOL;
    if (surplus > 0) data += func.FEED + QString::number(surplus) + func.EOL;
    data += func.CUT + func.EOL;
    QMessageBox::information(this, QString::number(numHole), QString::number(surplus));
    QMessageBox::information(this, tr("data"), data.toUtf8());
    return data;
}

bool MainWindow::validation(DataSrc dataSrc) {
    bool result;
    if (dataSrc.pipeL >= dataSrc.holeD &&
        dataSrc.holeD > 0.0 &&
        dataSrc.holeI >= 0.0 &&
        dataSrc.merginHead >= 0.0 &&
        dataSrc.merginEnd >= 0.0 &&
        (dataSrc.pipeL - dataSrc.merginHead - dataSrc.merginEnd) >= 0.0 )
        result = true;
    else result = false;
    return result;
}

uint16_t MainWindow::calcHoleNumber(DataSrc dataSrc) {
    uint16_t numHole = 0;
    if (dataSrc.holeI != 0.0) numHole = std::floor((dataSrc.pipeL - dataSrc.merginHead - dataSrc.merginEnd) / dataSrc.holeI);
    else numHole = 1;
    return numHole;
}
