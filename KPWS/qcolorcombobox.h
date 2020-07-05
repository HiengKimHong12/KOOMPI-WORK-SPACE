#ifndef QCOLORCOMBOBOX_H
#define QCOLORCOMBOBOX_H

#include <QWidget>
#include <QColor>
#include <QMenu>
#include <QListWidget>
#include <QStyleOptionComboBox>

class QMenu;
class QListWidget;
class qcolorcombobox: public QWidget
{
    Q_OBJECT
public:
    qcolorcombobox(QWidget *parent = nullptr);
    void setCurrentColor(const QColor &color);
    QColor currentColor() const
    {
        return mcurrentColor;
    }

signals:
    void currentColorChanged(const QColor &color);
protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    QColor mcurrentColor;
    QMenu *mMenu;
    QMenu *popup;
    QMenu *makeMenu();
    QListWidget *mListWidget;
    QListWidget *makeListWidget();
    QRect makeColorRect() const;
    void assignColors(QListWidget *listWidget);
    QStyleOptionComboBox makeComboBoxStyle();
    bool isBool = true;
    bool Bool = true;
};

#endif // QCOLORCOMBOBOX_H
