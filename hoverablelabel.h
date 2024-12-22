#ifndef HOVERABLELABEL_H
#define HOVERABLELABEL_H

#include <QLabel>
#include <QDebug>
#include <QMouseEvent>

class HoverableLabel : public QLabel {
    Q_OBJECT

public:
    HoverableLabel(const QString &text, QWidget *parent = nullptr)
        : QLabel(text, parent) {
        setMouseTracking(true);  // Включаем отслеживание движения мыши
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        // Проверяем, находится ли указатель мыши внутри QLabel
        if (rect().contains(event->pos())) {
            setCursor(Qt::PointingHandCursor);  // Меняем курсор на руку
            qDebug() << "Mouse is over label:" << text();
        } else {
            setCursor(Qt::ArrowCursor);  // Возвращаем курсор в обычное состояние
        }
    }
};

#endif // HOVERABLELABEL_H
