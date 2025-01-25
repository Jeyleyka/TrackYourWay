#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskwidget.h"
#include "modalwindow.h"
#include "infoblock.h"
#include "dayofweekapi.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ModalWindow* modal;
    TaskWidget* taskWidget;
    InfoBlock* infoBlock;
    DayOfWeekAPI* API;

    QWidget *modalWidget;
    QWidget *tasksSlide;
    QWidget *calendarSlide;
    QWidget *historyTasksSlide;

    QPropertyAnimation *animation;

    QColor currentBackgroundColor = QColor(234,226,249);

    QLabel *label;
    QLabel *tasks;
    QLabel *savedTextLabel;
    QLabel *dayOfTheWeek;

    QHBoxLayout *topLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *inputsLayout;
    QHBoxLayout *tasksLayout;
    QVBoxLayout* tasksSlideLayout;
    QVBoxLayout *calendarLayout;
    QHBoxLayout *historyTasksLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout* widgetLayout;
    QVBoxLayout *testL;
    QHBoxLayout* changeSlideLayout;

    QPushButton *button;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton *modalUser;
    QPushButton* addTasks;
    QPushButton* openWnd;
    QPushButton *tasksSlideButton;
    QPushButton *calendarSlideButton;
    QPushButton *historyTasksSlideButton;

    QFont basicFont;
    QFont inputFont;

    QPoint offset;  // Смещение при перетаскивании

    QLineEdit* inputField;

    QVector<QLabel*> posts;
    QVector<QLabel *> taskLabels;
    QVector<TaskWidget*> widgets;
    QVector<InfoBlock*> m_blocks;
    QVector<InfoBlock*> infoBlocks;

    QString stringIndex;
    QString stringOfWeek;
    QString day;
    QString m_filePath;

    QStackedWidget* carousel;

    QCalendarWidget *calendar;

    QNetworkAccessManager *networkManager;

    QFile tasksFile;

    int countOfTasks = 1;
    // int index;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно
    bool openModal = false;
    bool toggle = true;

    void changeBackgroundColor();
    void onCreateInputClicked();
    void onEnterPressed();
    void onDeleteText(const QString& taskId);
    void changeTaskInFile(const QString& newText);
    void updateFileAfterDeletion(const QString& taskId);
    void updatePostsLabel();
    void showButton(QLabel* label);

    void initCloseWindowButton();
    void initHideWindowButton();
    void initModalUserMenuBtn();
    void initChangeThemeButton();
    void initAddTasks();
    void initCarouselBtns();
    void initBtnsLayout();
    void initTopLayout();
    void initInputsLayout();
    void initTasksLayout();
    void initWidgetLayout();
    void initChangeSlideLayout();
    void initTasksSlideLayout();
    void initCalendarLayout();
    void initHistoryTasksLayout();
    void initCarousel();
    void initMainLayout();

private slots:
    void showModalWindow();
    void performAction();
    void loadTasksFromFile();
    void saveTasksToFile(const QString& widgetText);
    QPair<int, QStringList> countDaysAndListInFile(const QString &fileName);
    QVector<InfoBlock*> createInfoBlocksFromFile(const QString &fileName, QWidget *parentWidget);
    void displayInfoBlocks();
    void loadDataFromFile();

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
