#ifndef MODALWINDOW_H
#define MODALWINDOW_H

#include "libs.h"

class ModalWindow : public QDialog
{
    Q_OBJECT

private:
    QPropertyAnimation *openAnimation;
    QPropertyAnimation *closeAnimation;
    QPushButton* closeBtn;
    QPushButton* visitingCalendarBtn;
    QPushButton* showTasksOfPastDaysBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *menuLayout;
    QVBoxLayout* mainLayout;

    void initCloseBtn();

signals:
    void actionPerformed();

private slots:
    void onActionButtonClicked();


protected:
    void paintEvent(QPaintEvent *event) override;

public:
    QColor currentBackgroundColor = QColor(219,211,233);
    explicit ModalWindow(QColor color, QWidget* parent = nullptr);

    void slideIn();
    void slideOut();
    void setBackgroundColor(const bool& toggle, const QString& color);

};

#endif // MODALWINDOW_H
