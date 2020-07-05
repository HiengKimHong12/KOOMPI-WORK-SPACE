#include "qcolorcombobox.h"
#include <QPaintEvent>
#include "writer.h"
#include "ui_writer.h"
#include <QStylePainter>
#include <QListWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QColor>
#include <QLayout>
#include <QJsonObject>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QTextEdit>

qcolorcombobox::qcolorcombobox(QWidget *parent)
    :QWidget{parent}
{
       mListWidget = new QListWidget(this);
       mMenu = makeMenu();
       setCurrentColor(Qt::color0);


}
void qcolorcombobox :: setCurrentColor(const QColor &color)
{
   if ( qcolorcombobox::Bool )
   {
       mcurrentColor = color;
       update();
       emit currentColorChanged(mcurrentColor);

   }
}
QRect qcolorcombobox ::makeColorRect() const
{
    QRect colorRect;
    QPoint center = rect().center();
    colorRect.setWidth(int(width()*2.8/3.0));
    colorRect.setX(center.x() - colorRect.width()/2);
    colorRect.setY(center.y()-colorRect.height()/4);
    return colorRect;
}
QStyleOptionComboBox qcolorcombobox ::makeComboBoxStyle()
{
    QStyleOptionComboBox option;
    option.initFrom(this);
    return option;
}

void qcolorcombobox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);
    painter.drawComplexControl(QStyle::CC_ComboBox, makeComboBoxStyle());
    painter.fillRect(makeColorRect(), mcurrentColor);
    QWidget::paintEvent(e);
}
void qcolorcombobox::mousePressEvent(QMouseEvent *e)
{
    mListWidget->setMaximumWidth(10000);
    QPoint p = parentWidget()->mapToGlobal(pos());
    p.setY(p.y() + height());
    mMenu -> popup(p);
    QWidget::mousePressEvent(e);
}
QListWidget *qcolorcombobox :: makeListWidget()
{
    QListWidget *listWidget = new QListWidget;
    listWidget->setMinimumSize(width(), 250);
    assignColors(listWidget);
    connect(listWidget, &QListWidget::itemClicked, this, [&](QListWidgetItem *item)
    {
        setCurrentColor(item->background().color());
        update();
        mMenu->show();
    });
    return listWidget;
}
QMenu *qcolorcombobox::makeMenu()
{
    QMenu *menu = new QMenu(this);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(mListWidget);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    menu->setLayout(vbox);
    return menu;
}

void qcolorcombobox::assignColors(QListWidget *listWidget)
{
    QFile JSFile(":/color.json");
    if(JSFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QJsonDocument dot = QJsonDocument::fromJson(JSFile.readAll());
        JSFile.close();
        QJsonArray colorsArray = dot.array();
        const int nColors = colorsArray.size();
        if(nColors > 0)
        {
            listWidget->clear();
            for (int iColor = 0; iColor< nColors ; iColor++)
            {
                QJsonObject colorObj = colorsArray.at(iColor).toObject();
                QListWidgetItem *colorItem = new QListWidgetItem;
                colorItem->setText(colorObj["name"].toString());
                colorItem->setBackground(QColor(colorObj["hexvalue"].toString()));
                colorItem->setForeground(Qt::white);
                listWidget->addItem(colorItem);
            }
        }
}
}
