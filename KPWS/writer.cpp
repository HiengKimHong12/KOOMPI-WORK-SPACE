#include "writer.h"
#include "ui_writer.h"
#include <QPlainTextEdit>
#include <QPlainTextDocumentLayout>
#include <QFont>
#include <QColor>
#include <QtWidgets>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QString>
#include <QCursor>
#include <QSizeF>
#include <QTextFormat>
#include <QApplication>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocumentWriter>
#include <QPageSize>
#include <QDesktopWidget>
#include <qpagelayout.h>
#include <QTextFrame>
#include <QPainter>
#include <QScrollBar>
#include <QWidget>
#include <QComboBox>
#include <QFontComboBox>
#include "qcolorcombobox.h"
#include <QPalette>
#include <QPixmap>
#include <QDebug>
#include <QAbstractProxyModel>


QString name;
writer::writer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::writer)
{
    ui->setupUi(this);
    ui->comboBox_3->hide();
    setWindowTitle("KOOMPI Workspace");

    for (int i = 1; i<2; i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }
        QPixmap px(50, 15);
        QStringList colorNames = QColor::colorNames();
        foreach (name, colorNames) {
            px.fill(QColor(name));
            ui->comboBox_3->addItem(px, name);                                }
    }

QColor writer::color() const{
    return qvariant_cast<QColor>(Qt::DecorationRole);
}

void writer::setColor(const QColor &color)
{

}

writer::~writer()
{
    delete ui;
}
void writer::on_actionFont_triggered()
{
        bool ok;
        QFont font = QFontDialog::getFont(&ok, QFont("Khmer OS", 12), this);

        if(ok){
        ui->textEdit->setFont(font);
        }
}
void writer::on_actionColor_triggered()
{
        QColor dia = QColorDialog::getColor(Qt::white,this,"Color");
//    if(color.isValid())
 {
//       ui->textEdit->setTextColor(color);
       if (dia.isValid()) {
       QColorDialog *dia1 = new QColorDialog(this);
       connect(dia1, SIGNAL(colorSelected(const QColor&)),
       this, SLOT(updateColor(const QColor&)));
       }
       ui->textEdit->setTextColor(dia);

    }
}

void writer::on_actionBackground_color_triggered()
{
    QColor color1 = QColorDialog::getColor(Qt::white,this,"Color");
    if(color1.isValid()){

       ui->textEdit->setTextBackgroundColor(color1);
}
}

void writer::on_actionBold_triggered()
{
    if(isBool){
        ui->textEdit->setFontWeight(QFont::Bold);
        isBool = !isBool;
    }else{
        ui->textEdit->setFontWeight(QFont::Normal);
        isBool = !isBool;
    }
}

void writer::on_actionI_triggered()
{
    if(Bool){
        ui->textEdit->setFontItalic(QFont::StyleItalic);
        Bool = !Bool;
    }else{
        ui->textEdit->setFontItalic(QFont::StyleNormal);
        Bool = !Bool;
}
}

void writer::on_actionLeft_triggered()
{
    QTextEdit *edit2 =new QTextEdit("Left");
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void writer::on_actionRight_triggered()
{
    QTextEdit *edit1 =new QTextEdit("Right");
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void writer::on_actionCenter_triggered()
{
    QTextEdit *edit3 =new QTextEdit("Center");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}
void writer::on_actionUnderline_triggered()
{
    if(Bool){
    ui->textEdit->setFontUnderline(QFont::UnderlineResolved);
    Bool = ! Bool;
    }else{
        ui->textEdit->setFontUnderline(QFont::StyleNormal);
        Bool = ! Bool;
    }
}
void writer::on_actionNew_triggered()
{
    ui->textEdit->setText(QString());
}

void writer::on_actionClose_triggered()
{
    ui->textEdit->setText(QString());
        QMessageBox::information(this, "Title", "Are you want to close?");
        {
            QApplication::quit();
        }
}

void writer::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open the file"), tr("Address(*.abk);;All Files (*)"));
}

void writer::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Address"), "", tr("Address(*.odt);;All Files(*)"));
    if (filename.isEmpty())
        return;
    else {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }
    }
}

void writer::on_actionzoom_in_triggered()
{
    ui->textEdit->zoomIn();
}
void writer::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}
void writer::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
void writer::on_actionzoom_out_triggered()
{
    ui->textEdit->zoomOut();
}

void writer::on_horizontalSlider_sliderPressed()
{
    for (int i=2; i<22; i++){
    ui->textEdit->zoomIn();}
}

void writer::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setFont(f);
    QTextCursor cursor(ui->textEdit->document());

}

void writer::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QComboBox *fontsizecombo = new QComboBox ();
    for (int i = 2; i<125; i++){
        ui->comboBox->addItem(QString::number(i));
    }
    ui->textEdit->setFontPointSize(arg1.toInt());
}

void writer::on_actionPDF_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Export Pdf"
                                                    , QString(),"*.pdf");
    if(!filename.isEmpty()){
        if(QFileInfo(filename).suffix().isEmpty())
            {filename.append(".pdf");}
        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(filename);
        ui->textEdit->document()->print(&printer);
    }
}

void writer::on_actionLB_Writer_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Export Pdf"
                                                    , QString(),"*.pdf");
    if(!filename.isEmpty()){
        if(QFileInfo(filename).suffix().isEmpty())
            {filename.append(".docx");}
        QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(filename);
        ui->textEdit->document()->print(&printer);
    }

}

void writer::addItem(const QString &text, const QVariant &Data)
{

}

void writer::populatelist()
{
    const QStringList colorNames = QColor::colorNames();

    for (int i = 0 ; i<colorNames.size(); i++){
        QColor color(colorNames[i]);
        ui->textEdit->setTextColor(i);

    }
}

void writer::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    QPalette palette;
    palette.setColor(QPalette::Normal, QPalette::WindowText, arg1);
    ui->textEdit->setPalette(palette);
    qDebug()<<ui->comboBox_3->currentText();

    ui->comboBox_3->hide();
    ui->comboBox_3->showPopup();
    ui->comboBox_3->show();
    ui->textEdit->setTextColor(arg1);
}

