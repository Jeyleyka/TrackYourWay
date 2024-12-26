#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskwidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QColor currentBackgroundColor = Qt::white;
    QLabel *label;
    QHBoxLayout *topLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *inputsLayout;
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
    QVector<QLabel*> posts;
    QVector<QLabel *> taskLabels;
    QHBoxLayout *tasksLayout;
    QVBoxLayout* widgetLayout;
    QVector<TaskWidget*> widgets;
    QString stringIndex;
    TaskWidget* taskWidget;

    int countOfTasks = 1;
    // int index;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно

    void changeBackgroundColor();
    void onCreateInputClicked();
    void onEnterPressed();
    void onDeleteText(TaskWidget* item);
    void updatePostsLabel();
    void showButton(QLabel* label);

    void initCloseWindowButton();
    void initHideWindowButton();
    void initChangeThemeButton();
    void initAddTasks();
    void initBtnsLayout();
    void initTopLayout();
    void initInputsLayout();
    void initTasksLayout();
    void initWidgetLayout();
    void initMainLayout();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
public:
    MainWindow();
    ~MainWindow();
};
#endif // MAINWINDOW_H
