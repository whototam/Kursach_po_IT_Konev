#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openImage();
    void saveImage();
    void Negativchik();

private:
    QLabel *imageLabel; // Метка для отображения изображения
    QPixmap *pixmap;
};

#endif // MAINWINDOW_H
