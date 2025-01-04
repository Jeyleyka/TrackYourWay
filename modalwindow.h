#ifndef MODALWINDOW_H
#define MODALWINDOW_H

#include "libs.h"

class ModalWindow : public QDialog
{
    Q_OBJECT

private:
    QPropertyAnimation *openAnimation;
    QPropertyAnimation *closeAnimation;
    QColor currentBackgroundColor = QColor(219,211,233);
    QPushButton* closeBtn;
    QLabel* label;

    void initCloseBtn();

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit ModalWindow(QWidget* parent = nullptr);

    void slideIn();
    void slideOut();
    void setBackgroundColor(const QColor& color);
};

#endif // MODALWINDOW_H
