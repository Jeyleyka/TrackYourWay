#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include "libs.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    void initAddTasksBtn();
    void initMainLayout();
    explicit ScheduleWidget(QWidget *parent = nullptr);

private slots:
    void createNewTask();

private:
    QPushButton* newTaskBtn;
    QPushButton* deleteTaskBtn;
    QPushButton* addSubTask;

    QVBoxLayout* mainLayout;
    QVBoxLayout* taskLayout;

    QVBoxLayout* subTaskLayout;

    QWidget *taskWidget;
    QWidget* subWidget;

    QLineEdit* inputTask;
    QLineEdit* inputSubTask;

    QLabel* task;
    QLabel* subTask;

    QFrame *line;

    QCheckBox* checkBox;
};

#endif // SCHEDULEWIDGET_H
