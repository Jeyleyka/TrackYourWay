#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskwidget.h"
#include "modalwindow.h"

class CarouselWidget : public QWidget
{
public:
    CarouselWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        // Основной layout
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // QStackedWidget для отображения разных слайдов
        stackedWidget = new QStackedWidget(this);

        // Создание слайдов
        QWidget *tasksSlide = createTasksSlide();
        QWidget *calendarSlide = createCalendarSlide();

        // Добавление слайдов в QStackedWidget
        stackedWidget->addWidget(tasksSlide);
        stackedWidget->addWidget(calendarSlide);

        // Кнопки для перелистывания слайдов
        QPushButton *nextButton = new QPushButton("Следующий слайд", this);
        connect(nextButton, &QPushButton::clicked, this, &CarouselWidget::onNextSlideClicked);

        mainLayout->addWidget(stackedWidget);
        mainLayout->addWidget(nextButton);
    }

private:
    QStackedWidget *stackedWidget;

    QWidget* createTasksSlide()
    {
        // Виджет для добавления задач
        QWidget *tasksSlide = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(tasksSlide);

        // Поле для ввода задач
        QLineEdit *taskInput = new QLineEdit(tasksSlide);
        taskInput->setPlaceholderText("Введите задачу...");
        layout->addWidget(taskInput);

        // Список задач
        QListWidget *taskList = new QListWidget(tasksSlide);
        layout->addWidget(taskList);

        // Кнопка для добавления задачи
        QPushButton *addButton = new QPushButton("Добавить задачу", tasksSlide);
        connect(addButton, &QPushButton::clicked, [taskInput, taskList]() {
            if (!taskInput->text().isEmpty()) {
                taskList->addItem(taskInput->text());
                taskInput->clear();
            }
        });
        layout->addWidget(addButton);

        return tasksSlide;
    }

    QWidget* createCalendarSlide()
    {
        // Виджет с календарем
        QWidget *calendarSlide = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(calendarSlide);

        // Календарь
        QCalendarWidget *calendar = new QCalendarWidget(calendarSlide);
        layout->addWidget(calendar);

        return calendarSlide;
    }

    void onNextSlideClicked()
    {
        // Переключение на следующий слайд
        int currentIndex = stackedWidget->currentIndex();
        int nextIndex = (currentIndex + 1) % stackedWidget->count();  // Переключаем циклично
        stackedWidget->setCurrentIndex(nextIndex);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    ModalWindow* modal;
    CarouselWidget* carouselWidget;

    QWidget *modalWidget;
    QWidget *tasksSlide;
    QWidget *calendarSlide;

    QPropertyAnimation *animation;
    QColor currentBackgroundColor = QColor(234,226,249);
    QLabel *label;
    QHBoxLayout *topLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *inputsLayout;
    QHBoxLayout *tasksLayout;
    QVBoxLayout* tasksSlideLayout;
    QVBoxLayout *calendarLayout;
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
    QVBoxLayout* widgetLayout;
    QVector<TaskWidget*> widgets;
    QString stringIndex;
    TaskWidget* taskWidget;
    QVBoxLayout *testL;
    QPushButton* openWnd;
    QStackedWidget* stackedWidget;


    int countOfTasks = 1;
    // int index;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно
    bool openModal = false;
    bool toggle = true;

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
