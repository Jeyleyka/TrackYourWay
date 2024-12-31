#ifndef MODALWINDOW_H
#define MODALWINDOW_H

#include "libs.h"

class ModalWindow : public QDialog
{
    Q_OBJECT

private:
    QColor currentBackgroundColor = QColor(234,226,249, 100);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    ModalWindow(QWidget* parent = nullptr);

    void slideIn(const QPoint &startPosition, int finalWidth);
    void slideOut();
};

#endif // MODALWINDOW_H
