#ifndef QRCODEDIALOG_H
#define QRCODEDIALOG_H

#include <QDialog>
#include <QImage>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>


namespace Ui {
class QrCodeDialog;
}

class QrCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QrCodeDialog(QWidget *parent = nullptr);
    ~QrCodeDialog();
    void setQrCodeImage(const QImage &image);

private slots:
    void on_pushButton_clicked();

private:
    Ui::QrCodeDialog *ui;
};

#endif // QRCODEDIALOG_H
