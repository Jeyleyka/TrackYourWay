#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QDebug>
#include <QIcon>
#include <QString>
#include <Qpainter>
#include <QRegion>
#include <QPainterPath>
#include <QMouseEvent>
#include <QLineEdit>
#include <QList>
#include <QGroupBox>

// #include "Images/moon.png"

class MainWindow : public QWidget
{
private:
    QColor currentBackgroundColor = Qt::white;
    QLabel *label;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;
    QPushButton *button;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QFont basicFont;
    QFont inputFont;
    QPoint offset;  // Смещение при перетаскивании
    QLabel *tasks;
    QPushButton* addTasks;
    QLineEdit* inputField;
    QLabel *savedTextLabel;
    QList<QString> posts;

    int countOfTasks = 1;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно

    void changeBackgroundColor();
    void onCreateInputClicked();
    void onEnterPressed();
    void updatePostsLabel();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    MainWindow();
    ~MainWindow();
};
#endif // MAINWINDOW_H
