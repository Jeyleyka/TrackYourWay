#ifndef GREETINGS_H
#define GREETINGS_H

#include "mainwindow.h"

class Greetings : public QMainWindow
{
    Q_OBJECT

private:
    QColor currentBackgroundColor = Qt::white;
    QVBoxLayout* mainLayout;
    QLabel* label;
    QPushButton* btn;

private slots:
    void openSecondWindow() {
        this->close();
        MainWindow *main = new MainWindow();  // Создаем второе окно
        main->show();           // Открываем его как модальное окно
    }

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    Greetings(QWidget *parent = nullptr);
};

#endif // GREETINGS_H
