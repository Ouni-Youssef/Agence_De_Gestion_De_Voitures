#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"

QrCodeDialog::QrCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QrCodeDialog)
{
    ui->setupUi(this);
}

QrCodeDialog::~QrCodeDialog()
{
    delete ui;
}

void QrCodeDialog::setQrCodeImage(const QImage &image)
{
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void QrCodeDialog::on_pushButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", QString(), "PDF Files (*.pdf)");

        if (!filePath.isEmpty()) {
            // Check for a valid pixmap
            const QPixmap* constPixmap = ui->label->pixmap();
            if (!constPixmap) {
                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Error: Invalid QR code pixmap."), QMessageBox::Cancel);

                return;
            }

            // Create a copy of the QPixmap
            QPixmap qrCodePixmap(*constPixmap);

            // Save the QR code image to the PDF file
            QImage qrCodeImage = qrCodePixmap.toImage();

            // Set the image format to PDF
            QPdfWriter pdfWriter(filePath);
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));

            // Check for successful initialization of QPainter
            QPainter painter(&pdfWriter);
            if (!painter.isActive()) {
                QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("Error: Failed to initialize QPainter."), QMessageBox::Cancel);


                return;
            }

            // Draw the image on the PDF
            painter.drawImage(QRectF(0, 0, pdfWriter.width(), pdfWriter.height()), qrCodeImage);
        }
}
