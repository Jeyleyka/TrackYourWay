#ifndef GREETINGS_H
#define GREETINGS_H

#include "mainwindow.h"

class Greetings : public QMainWindow
{
    Q_OBJECT

private:
    QColor currentBackgroundColor = Qt::white;
    QVBoxLayout* mainLayout;
    QHBoxLayout* logoLayout;
    QHBoxLayout *btnsLayout;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton* btn;
    QLabel* logoLabel;
    QLabel* label;
    QPoint offset;

    bool dragging = false;

    void initCloseWindowButton();
    void initHideWindowButton();
    void initBtnsLayout();

private slots:
    void openSecondWindow() {
        this->close();
        MainWindow *main = new MainWindow();  // Создаем второе окно
        main->show();           // Открываем его как модальное окно
    }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    Greetings(QWidget *parent = nullptr);
};

#endif // GREETINGS_H
