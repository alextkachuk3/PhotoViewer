#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    bool eventFilter(QObject* watched, QEvent* event);

    void on_actionCrop_triggered();
    void on_actionFullscreen_triggered();
    void on_actionPaintBlack_triggered();
    void on_actionOpen_triggered();
    void on_actionRotateLeft_triggered();
    void on_actionRotateRight_triggered();
    void on_actionSave_triggered();
    void on_actionShowToolbar_triggered(bool checked);
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomToFit_triggered();


private:
    Ui::MainWindow *ui;

    QPoint croppingStart;
    QPoint croppingEnd;

    QLabel *imageLabel;

    QScrollArea *scrollArea;

    QString fileName;
    QImage image;

    QStatusBar *statusBar;

    QToolBar *mainToolBar;

    QVector<QImage> history;
    QVector<QImage> reverseHistory;

    QAction *actionCrop;
    QAction *actionOpen;
    QAction *actionPaintBlack;
    QAction *actionRotateLeft;
    QAction *actionRotateRight;
    QAction *actionSave;
    QAction *actionShowToolbar;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionZoomToFit;

    void adjustScrollBar(QScrollBar *scrollBar, double factor);
};
#endif // MAINWINDOW_H
