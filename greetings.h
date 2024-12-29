#ifndef GREETINGS_H
#define GREETINGS_H

#include "libs.h"

class Greetings : public QMainWindow
{
private:
    QColor currentBackgroundColor = Qt::white;
    QVBoxLayout* mainLayout;
    QLabel* label;
    QPushButton* btn;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    Greetings(QWidget *parent = nullptr);
};

#endif // GREETINGS_H
