#include "cameraemp.h"
#include "ui_cameraemp.h"

cameraemp::cameraemp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cameraemp)
{
    ui->setupUi(this);

    //Camera devices:
    setCamera(QCameraInfo::defaultCamera());
}

cameraemp::~cameraemp()
{
    delete ui;
}

void cameraemp::setCamera(const QCameraInfo &cameraInfo)
{
    Camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(Camera);
    Camera->setViewfinder(ui->viewfinder);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &cameraemp::readyForCapture);
    Camera->start();
}

void cameraemp::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void cameraemp::on_takeImageButton_clicked()
{
    isCapturingImage = true;
    imageCapture->capture();
}
