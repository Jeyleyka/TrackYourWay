#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include "libs.h"

class ScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    void initAddTasksBtn();
    void initMainLayout();
    void initTaskWidgetAndLayout();
    void initDeleteTaskBtn();
    void initLine();
    void initInputTask();
    void initTaskLabel();
    void initAddSubTaskBtn();
    void initSubTaskWidget();
    void initCompleteTaskBtn();

    explicit ScheduleWidget(QWidget *parent = nullptr);

private slots:
    void createNewTask();

private:
    QPushButton* newTaskBtn;
    QPushButton* deleteTaskBtn;
    QPushButton* addSubTask;
    QPushButton* completeTaskBtn;

    QVBoxLayout* mainLayout;
    QVBoxLayout* taskLayout;
    QVBoxLayout* subTaskLayout;

    QWidget *taskWidget;

    QLineEdit* inputTask;
    QLineEdit* inputSubTask;

    QLabel* task;
    QLabel* subTask;

    QFrame *line;

    QCheckBox* checkBox;
};

#endif // SCHEDULEWIDGET_H
