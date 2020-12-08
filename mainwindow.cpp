#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    actionCrop = ui->actionCrop;
       actionPaintBlack = ui->actionPaintBlack;
       actionOpen = ui->actionOpen;
       actionRotateLeft = ui->actionRotateLeft;
       actionRotateRight = ui->actionRotateRight;
       actionSave = ui->actionSave;
       actionShowToolbar = ui->actionShowToolbar;
       actionUndo = ui->actionUndo;
       actionRedo = ui->actionRedo;
       actionZoomIn = ui->actionZoomIn;
       actionZoomOut = ui->actionZoomOut;
       actionZoomToFit = ui->actionZoomToFit;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{

}

void MainWindow::on_actionCrop_triggered()
{

}

//Enter max window size
void MainWindow::on_actionFullscreen_triggered()
{
    if(isFullScreen())
        this->setWindowState(Qt::WindowMaximized);
    else
        this->setWindowState(Qt::WindowFullScreen);
}

void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionPaintBlack_triggered()
{

}

void MainWindow::on_actionRotateLeft_triggered()
{

}

void MainWindow::on_actionRotateRight_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionShowToolbar_triggered(bool checked)
{

}


void MainWindow::on_actionUndo_triggered()
{

}

void MainWindow::on_actionRedo_triggered()
{

}

void MainWindow::on_actionZoomIn_triggered()
{

}

void MainWindow::on_actionZoomOut_triggered()
{

}

void MainWindow::on_actionZoomToFit_triggered()
{

}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    int newValue = factor * scrollBar->value() + (factor - 1) * scrollBar->pageStep() / 2;
    scrollBar->setValue(newValue);
}

void MainWindow::changeCroppingState(bool changeTo)
{
    croppingState = changeTo;
    actionCrop->setDisabled(changeTo);

    if (changeTo)
        setCursor(Qt::CrossCursor);
    else
        setCursor(Qt::ArrowCursor);
}

void MainWindow::refreshLabel()
{
    imageLabel->setPixmap(QPixmap::fromImage(image));
}
