#include "mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Негативчик");
    setStyleSheet("background-color: #fa8fb1;");

    imageLabel = new QLabel(this);//на строку ниже не смотрите))
    imageLabel->setStyleSheet("background-color: #ffc1d5; margin-top: 10px; margin-right: 20px; margin-bottom: 0px; margin-left: 20px; border: none;; border-radius:10px;");
    QString stylishMrazish = "QPushButton{font:18px italic; color: #ffe4ec; background-color: qlineargradient(x0:0, y1:0, x0:1, y1:1, stop:0 #f74780, stop:1 #fc6998); width: 150px; height: 35px; border: none;; border-radius:9px; margin: 20px;} QPushButton:hover{background-color: qlineargradient(x0:0, y1:0, x0:1, y1:1, stop:0 #fc6998, stop:1 #f74780);}";

    QHBoxLayout *knopo4ki = new QHBoxLayout;
    QVBoxLayout *body = new QVBoxLayout;

    body->addWidget(imageLabel);
    body->addLayout(knopo4ki);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(body);
    setCentralWidget(centralWidget);

    QPushButton *openButton = new QPushButton("Открыть", this);//создание кнопки
    openButton->setStyleSheet(stylishMrazish);
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openImage); // Подключение сигнала нажатия кнопки к слоту openImage
    knopo4ki->addWidget(openButton);

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    saveButton->setStyleSheet(stylishMrazish);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveImage);
    knopo4ki->addWidget(saveButton);

    QPushButton *negativeButton = new QPushButton("Отнегативить", this);
    negativeButton->setStyleSheet(stylishMrazish);
    connect(negativeButton, &QPushButton::clicked, this, &MainWindow::Negativchik);
    knopo4ki->addWidget(negativeButton);
}

void MainWindow::openImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg)");
    if (!imagePath.isEmpty())
    {
        QImage image(imagePath);
        if (image.isNull())
        {
            return;
        }
        QPixmap pixmap = QPixmap::fromImage(image);
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        imageLabel->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::saveImage()
{
           QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::homePath(), "Image Files (*.jpeg)");
           if (!fileName.isEmpty())
                   {
                       QImage image = imageLabel->pixmap()->toImage(); // Получение изображения из imageLabel для его сохранения
                       image.save(fileName);
                   }
       }

void MainWindow::Negativchik()
{
    if (imageLabel->pixmap()&&!imageLabel->pixmap()->isNull())//проверка условий(наличие пикчи в лейбле и отсуствие пустоты в лейбле(ЭТО НЕ ОДНО И ТОЖЕ!!!))
    {
        QImage image = imageLabel->pixmap()->toImage(); // Получение изображения из imageLabel
        for(int y = 0; y < image.height(); ++y) {
                for(int x = 0; x < image.width(); ++x) {
                    QRgb pixel = image.pixel(x, y);
                    int red = 255 - qRed(pixel);
                    int green = 255 - qGreen(pixel);
                    int blue = 255 - qBlue(pixel);
                    image.setPixel(x, y, qRgb(red, green, blue));
                }
            }
        imageLabel->setPixmap(QPixmap::fromImage(image));
    }
}
