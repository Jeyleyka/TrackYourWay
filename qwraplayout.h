#ifndef QWRAPLAYOUT_H
#define QWRAPLAYOUT_H

#include "libs.h"

class QWrapLayout : public QLayout {
public:
    explicit QWrapLayout(QWidget *parent = nullptr) : QLayout(parent) {}

    ~QWrapLayout() {
        // Удаляем все элементы из layout при его удалении
        QLayoutItem *item;
        while ((item = takeAt(0))) {
            delete item;
        }
    }

    void addItem(QLayoutItem *item) override {
        items.append(item);
    }

    int count() const override {
        return items.count();
    }

    QLayoutItem *itemAt(int index) const override {
        return items.value(index);
    }

    QLayoutItem *takeAt(int index) override {
        if (index >= 0 && index < items.count()) {
            return items.takeAt(index);
        }
        return nullptr;
    }

    void setGeometry(const QRect &rect) override {
        QLayout::setGeometry(rect);

        // Получаем доступную ширину контейнера
        int x = rect.x();
        int y = rect.y();
        int rowHeight = 0;

        // Проходим по всем элементам
        for (int i = 0; i < items.count(); ++i) {
            QLayoutItem *item = items.at(i);
            QWidget *widget = item->widget();
            if (!widget) continue;

            // Получаем размер элемента
            QSize itemSize = item->sizeHint();
            if (x + itemSize.width() > rect.right()) {
                // Если элемент не помещается по ширине, переносим на следующую строку
                x = rect.x();
                y += rowHeight;
                rowHeight = 0;
            }

            // Размещаем элемент
            item->setGeometry(QRect(QPoint(x, y), itemSize));
            x += itemSize.width();
            rowHeight = qMax(rowHeight, itemSize.height());
        }
    }

    QSize sizeHint() const override {
        QSize size(0, 0);
        for (QLayoutItem *item : items) {
            size = size.expandedTo(item->sizeHint());
        }
        return size;
    }

private:
    QList<QLayoutItem *> items;
};

#endif // QWRAPLAYOUT_H
