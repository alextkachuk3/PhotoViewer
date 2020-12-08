#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
};
#endif // MAINWINDOW_H
