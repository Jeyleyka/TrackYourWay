#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskwidget.h"
#include "modalwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ModalWindow* modal;

    QWidget *modalWidget;
    QPropertyAnimation *animation;
    QColor currentBackgroundColor = QColor(234,226,249);
    QLabel *label;
    QHBoxLayout *topLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *inputsLayout;
    QVBoxLayout *mainLayout;
    QPushButton *button;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton *modalUser;
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
    QVBoxLayout *testL;
    QPushButton* openWnd;


    int countOfTasks = 1;
    // int index;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно
    bool openModal = false;

    void changeBackgroundColor();
    void onCreateInputClicked();
    void onEnterPressed();
    void onDeleteText(TaskWidget* item);
    void updatePostsLabel();
    void showButton(QLabel* label);

    void initCloseWindowButton();
    void initHideWindowButton();
    void initModalUserMenuBtn();
    void initChangeThemeButton();
    void initAddTasks();
    void initBtnsLayout();
    void initTopLayout();
    void initInputsLayout();
    void initTasksLayout();
    void initWidgetLayout();
    void initMainLayout();

private slots:
    void showModalWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
