#ifndef WRITER_H
#define WRITER_H
#include <QMainWindow>
#include "qcolorcombobox.h"
#include <QFontDialog>
#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QFontMetrics>
#include <QAction>
#include <QListData>
#include <QLineEdit>
#include <QComboBox>
#include <QtPrintSupport/QPrintDialog>

namespace Ui {
class writer;
QT_BEGIN_NAMESPACE
class QColor;
class QWidget;

}

class writer : public QMainWindow

{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:
    explicit writer(QWidget *parent = nullptr);
    ~writer();

public:
    QColor color() const;
    QColor getColor();
    void setColor(const QColor &color);
//    QAction *writer::set(const QString &text, const QVariant &data);
//signals:
//   void colorChanged(QColor);
//public slots:
//   void changeColor(const QColor &);
//   void chooseColor();
//   void paintEvent(QPaintEvent *event);

private slots:
    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionBackground_color_triggered();

    void on_actionBold_triggered();

    void on_actionI_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionCenter_triggered();

    void on_actionUnderline_triggered();

    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionzoom_in_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionzoom_out_triggered();

    void on_horizontalSlider_sliderPressed();


//    void on_actionPagesize_objectNameChanged(const QString &objectName);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_actionPDF_triggered();

    void on_actionLB_Writer_triggered();

    void addItem(const QString &text, const QVariant &Data);

//    void on_comboBox_2_currentTextChanged(const QString &arg1);


    void on_comboBox_3_currentIndexChanged(const QString &arg1);


private:
    Ui::writer *ui;
    bool isBool = true;
    bool Bool = true;
    QColor currentColor;
private:
    void populatelist();


};

#endif // WRITER_H
