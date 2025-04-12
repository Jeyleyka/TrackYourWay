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
    void initTaskCommentBtns();
    void initStackedWidget();
    void initTaskView(QVBoxLayout *layout);
    void initCommentView(QVBoxLayout *layout);
    void showTaskView();
    void showCommentView();

    explicit ScheduleWidget(QWidget *parent = nullptr);

private slots:
    void createNewTask();

private:
    QPushButton* newTaskBtn;
    QPushButton* deleteTaskBtn;
    QPushButton* addSubTask;
    QPushButton* completeTaskBtn;
    QPushButton* tasksBtn;
    QPushButton* commentsBtn;

    QVBoxLayout* mainLayout;
    QVBoxLayout* taskLayout;
    QVBoxLayout* subTaskLayout;

    QWidget *taskWidget;
    QWidget* taskViewWidget;
    QWidget* commentViewWidget;

    QLineEdit* inputTask;
    QLineEdit* inputSubTask;
    QLineEdit* commentInput;

    QLabel* task;
    QLabel* subTask;

    QFrame *line;

    QCheckBox* checkBox;

    QStackedWidget* stackedWidget;
};

#endif // SCHEDULEWIDGET_H
