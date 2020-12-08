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

       mainToolBar = ui->mainToolBar;
           statusBar = ui->statusBar;

           updateActions(false);
           actionUndo->setEnabled(false);
           actionRedo->setEnabled(false);

           imageLabel = new QLabel;
           imageLabel->resize(0, 0);
           imageLabel->setMouseTracking(true);
           imageLabel->setBackgroundRole(QPalette::Base);
           imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
           imageLabel->setScaledContents(true);
           imageLabel->installEventFilter(this);

           scrollArea = new QScrollArea;
           scrollArea->setBackgroundRole(QPalette::Dark);
           scrollArea->setWidget(imageLabel);
           setCentralWidget(scrollArea);

           setWindowTitle(tr("Photo Viewer"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != imageLabel)
            return false;

        switch (event->type())
        {
            case QEvent::MouseButtonPress:
            {
                if (!croppingState) break;
                const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
                croppingStart = me->pos() / scaleFactor;

                break;
            }

            case QEvent::MouseButtonRelease:
            {
                if (!croppingState) break;
                saveToHistoryWithClear(image);

                const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
                croppingEnd = me->pos() / scaleFactor;

                const QRect rect(croppingStart, croppingEnd);
                image = image.copy(rect);
                refreshLabel();
                imageLabel->adjustSize();

                changeCroppingState(false);

                break;
            }

            case QEvent::MouseMove:
            {
                const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
                const QPoint position = me->pos();
                statusBar->showMessage(QString("(x,y) coordinates: (%1,%2)").arg(position.x()).arg(position.y()));

                break;
            }

            default:
                break;
        }

        return false;
}

void MainWindow::on_actionCrop_triggered()
{
    changeCroppingState(true);
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
    QString lastFileName = fileName.isEmpty() ? QDir::currentPath() : fileName;
       fileName = QFileDialog::getOpenFileName(this,
                                               tr("Open File"),
                                               lastFileName);
       if (!fileName.isEmpty()) {
            image = QImage(fileName);
            if (image.isNull()) {
                QMessageBox::information(this,
                                         tr("Image Viewer"),
                                         tr("Cannot load %1.").arg(fileName));

                return;
            }

            scaleFactor = 1.0;
            croppingState = false;
            setCursor(Qt::ArrowCursor);
            updateActions(true);

            refreshLabel();
            imageLabel->adjustSize();
       }
}


void MainWindow::on_actionPaintBlack_triggered()
{
    saveToHistoryWithClear(image);

        int width = image.width(), height = image.height();

        QRgb color;
        int value;

        for (int x = 0; x < width; ++x)
            for (int y = 0; y < height; ++y)
            {
                color = image.pixel(x, y);
                value = qGray(color);
                image.setPixel(x, y, qRgb(value, value, value));
            }

        refreshLabel();
}

void MainWindow::on_actionRotateLeft_triggered()
{

}

void MainWindow::on_actionRotateRight_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this,
                                                         tr("Save File"),
                                                         "",
                                                         tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

        image.save(imagePath);
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

void MainWindow::rotateImage(int angle)
{
    saveToHistoryWithClear(image);

    QPixmap pixmap(*imageLabel->pixmap());
    QMatrix rm;
    rm.rotate(angle);
    pixmap = pixmap.transformed(rm);
    image = pixmap.toImage();

    refreshLabel();

    imageLabel->adjustSize();
}

void MainWindow::saveToHistory(QImage imageToSave)
{
    history.push_back(imageToSave);
    actionUndo->setEnabled(true);
}

void MainWindow::saveToHistoryWithClear(QImage imageToSave)
{
    saveToHistory(imageToSave);
    reverseHistory.clear();
    actionRedo->setEnabled(false);
}

void MainWindow::saveToReverseHistory(QImage imageToSave)
{
    reverseHistory.push_back(imageToSave);
    actionRedo->setEnabled(true);
}

void MainWindow::scaleImage(double factor)
{
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    actionZoomIn->setEnabled(scaleFactor < 3.0);
    actionZoomOut->setEnabled(scaleFactor > 0.333);
}

void MainWindow::updateActions(bool updateTo)
{
    actionCrop->setEnabled(updateTo);
    actionPaintBlack->setEnabled(updateTo);
    actionRotateLeft->setEnabled(updateTo);
    actionRotateRight->setEnabled(updateTo);
    actionSave->setEnabled(updateTo);
    actionZoomIn->setEnabled(updateTo);
    actionZoomOut->setEnabled(updateTo);
    actionZoomToFit->setEnabled(updateTo);
}
