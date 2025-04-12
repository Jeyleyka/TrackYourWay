#include "schedulewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QMessageBox>
#include <QFrame>
#include <QStackedWidget>

void ScheduleWidget::initAddTasksBtn() {
    this->newTaskBtn = new QPushButton("+ New Task", this);
    this->newTaskBtn->setStyleSheet("QPushButton {"
                                    "background-color: #3a4ed9;"
                                    "padding: 10px;"
                                    "border-radius: 5px;"
                                    "color: #fff;"
                                    "min-width: 120px;"
                                    "height: 25px;"
                                    "font-size: 14px;"
                                    "font-weight: bold;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #596ade;"
                                    "}");

    connect(this->newTaskBtn, &QPushButton::clicked, this, &ScheduleWidget::createNewTask);
}

void ScheduleWidget::initTaskCommentBtns() {
    // Создаем кнопку "Задачи"
    this->tasksBtn = new QPushButton("Задачи", this);
    this->tasksBtn->setStyleSheet("QPushButton {"
                                  "background-color: #3a4ed9;"
                                  "padding: 10px;"
                                  "border-radius: 5px;"
                                  "color: #fff;"
                                  "min-width: 120px;"
                                  "height: 25px;"
                                  "font-size: 14px;"
                                  "font-weight: bold;"
                                  "} QPushButton:hover {"
                                  "background-color: #596ade;"
                                  "}");

    // Создаем кнопку "Комментарии"
    this->commentsBtn = new QPushButton("Комментарии", this);
    this->commentsBtn->setStyleSheet("QPushButton {"
                                     "background-color: #3a4ed9;"
                                     "padding: 10px;"
                                     "border-radius: 5px;"
                                     "color: #fff;"
                                     "min-width: 120px;"
                                     "height: 25px;"
                                     "font-size: 14px;"
                                     "font-weight: bold;"
                                     "} QPushButton:hover {"
                                     "background-color: #596ade;"
                                     "}");

    // Подключаем кнопки к слотам для переключения между видами
    connect(this->tasksBtn, &QPushButton::clicked, this, &ScheduleWidget::showTaskView);
    connect(this->commentsBtn, &QPushButton::clicked, this, &ScheduleWidget::showCommentView);
}

void ScheduleWidget::initStackedWidget() {
    // Создаем stacked widget для переключения между видами
    this->stackedWidget = new QStackedWidget(this);

    // Создаем виджет для задач (с подзадачами)
    this->taskViewWidget = new QWidget();
    QVBoxLayout *taskLayout = new QVBoxLayout(taskViewWidget);
    this->initTaskView(taskLayout);  // Инициализируем вид задач
    this->stackedWidget->addWidget(this->taskViewWidget);

    // Создаем виджет для комментариев (с большим полем ввода)
    this->commentViewWidget = new QWidget();
    QVBoxLayout *commentLayout = new QVBoxLayout(commentViewWidget);
    this->initCommentView(commentLayout);  // Инициализируем вид комментариев
    this->stackedWidget->addWidget(this->commentViewWidget);
}

void ScheduleWidget::initTaskView(QVBoxLayout *layout) {
    // Инициализируем интерфейс для задач
    layout->addWidget(this->addSubTask);  // Кнопка для добавления подзадачи
    layout->addWidget(this->inputTask);   // Поле ввода задачи
    layout->addWidget(this->deleteTaskBtn); // Кнопка для удаления задачи
    layout->addWidget(this->completeTaskBtn); // Кнопка для завершения задачи
    layout->addWidget(this->line);  // Линия между элементами
}

void ScheduleWidget::initCommentView(QVBoxLayout *layout) {
    // Инициализируем интерфейс для комментариев
    this->commentInput = new QLineEdit(this);
    this->commentInput->setPlaceholderText("Введите ваш комментарий...");
    this->commentInput->setStyleSheet("font-size: 16px; height: 100px;");
    layout->addWidget(this->commentInput);  // Большое поле для ввода комментария
}

void ScheduleWidget::showTaskView() {
    this->stackedWidget->setCurrentWidget(this->taskViewWidget);  // Отображаем вид задач
}

void ScheduleWidget::showCommentView() {
    this->stackedWidget->setCurrentWidget(this->commentViewWidget);  // Отображаем вид комментариев
}

void ScheduleWidget::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this);

    // Добавляем кнопки переключения "Задачи" и "Комментарии"
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(this->tasksBtn);
    buttonLayout->addWidget(this->commentsBtn);
    this->mainLayout->addLayout(buttonLayout);

    // Добавляем stacked widget (вид с задачами или комментариями)
    this->mainLayout->addWidget(this->stackedWidget);

    this->setLayout(this->mainLayout);
}

void ScheduleWidget::initTaskWidgetAndLayout() {
    this->taskWidget = new QWidget(this);
    this->taskWidget->setFixedWidth(500);
    this->taskWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    this->taskWidget->setStyleSheet("background-color: #fff; border-radius: 5px; border: 1px solid #ccc; padding: 15px");

    this->taskLayout = new QVBoxLayout(this->taskWidget);
}

void ScheduleWidget::initDeleteTaskBtn() {
    this->deleteTaskBtn = new QPushButton("Delete", taskWidget);
    this->deleteTaskBtn->setStyleSheet("background-color: #f44336; padding: 10px; color: white; border-radius: 5px; margin-bottom: 20px; ");
    this->deleteTaskBtn->setFixedWidth(100);

    connect(this->deleteTaskBtn, &QPushButton::clicked, this, [this]() {
        this->taskWidget->deleteLater();
    });

    this->taskLayout->addWidget(this->deleteTaskBtn, 0, Qt::AlignRight);  // Добавляем кнопку снизу
}

void ScheduleWidget::initLine() {
    this->line = new QFrame(this->taskWidget);
    this->line->setFrameShape(QFrame::HLine);
    this->line->setFrameShadow(QFrame::Sunken);
    this->taskLayout->addWidget(this->line);
}

void ScheduleWidget::initInputTask() {
    this->inputTask = new QLineEdit(this->taskWidget);
    this->inputTask->setPlaceholderText("input task...");
    this->inputTask->setStyleSheet("margin-top: 20px; ");
    this->taskLayout->addWidget(this->inputTask, 0, Qt::AlignTop);
}

void ScheduleWidget::initTaskLabel() {
    this->task = new QLabel(this->taskWidget);
    this->task->setStyleSheet("font-size: 21px; margin-top: 20px; font-weight: 500; border: none; background-color: transparent");
    this->task->setVisible(false);

    connect(this->inputTask, &QLineEdit::editingFinished, [this]() {
        if (this->inputTask->text().isEmpty()) {
            QMessageBox::critical(nullptr, "Error", "Area must not be empty!");
            return;
        }

        this->task->setText(this->inputTask->text());
        this->inputTask->hide();
        this->task->show();
    });

    this->taskLayout->addWidget(this->task, 0, Qt::AlignTop);
}

void ScheduleWidget::initAddSubTaskBtn() {
    this->addSubTask = new QPushButton("+", this->taskWidget);
    this->addSubTask->setStyleSheet("QPushButton {"
                                    "background-color: #cac9c4;"
                                    "font-size: 16px;"
                                    "font-weight: 600;"
                                    "color: gray;"
                                    "margin-top: 20px;"
                                    "min-width: 400px;"
                                    "max-width: 400px;"
                                    "max-height: 20px;"
                                    "margin-bottom: 100px;"
                                    "} "
                                    "QPushButton:hover {"
                                    "background-color: #e0dfdc;"
                                    "}");

    this->taskLayout->addWidget(this->addSubTask, 0, Qt::AlignHCenter | Qt::AlignTop);
}

void ScheduleWidget::initSubTaskWidget() {
    connect(this->addSubTask, &QPushButton::clicked, this, [this]() {
        // Создаем новый subWidget для каждой пары чекбокса и лейбла
        QWidget *subWidget = new QWidget(this->taskWidget);
        subWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        subWidget->setFixedHeight(60);
        subWidget->setFixedWidth(400);
        QHBoxLayout *subWidgetLayout = new QHBoxLayout(subWidget);

        // Поле ввода для подзадачи
        QLineEdit *inputSubTask = new QLineEdit(subWidget);
        inputSubTask->setPlaceholderText("Input subtask...");
        inputSubTask->setStyleSheet("min-width: 370px; max-width: 400px; margin: 5px; border: none; max-height: 20px; min-height: 20px;");

        subWidgetLayout->addWidget(inputSubTask, 0, Qt::AlignVCenter);

        // Подключаем сигнал, чтобы добавить подзадачу в label
        QLabel *subTask = new QLabel(subWidget);
        subTask->setStyleSheet("font-size: 14px; border: none; max-height: 40px; min-height: 10px; max-width: 300px; min-width: 300px; margin-right: 5px; margin-top: 5px; margin-bottom: 5px;");

        QCheckBox *checkBox = new QCheckBox(subWidget);
        checkBox->setStyleSheet("margin-left: 10px; margin-top: 10px; margin-bottom: 10px; max-height: 30px; min-height: 10px; border: none;");
        checkBox->setVisible(false);  // Сначала скрываем чекбокс

        subWidgetLayout->addWidget(checkBox);
        subWidgetLayout->addWidget(subTask);

        // Устанавливаем фиксированную высоту для layout
        subWidgetLayout->setContentsMargins(0, 0, 0, 0);  // Убираем отступы

        // Подключаем сигнал для завершения ввода
        connect(inputSubTask, &QLineEdit::editingFinished, [this, subTask, inputSubTask, checkBox]() {
            if (inputSubTask->text().isEmpty()) {
                QMessageBox::critical(nullptr, "Error", "Subtask must not be empty!");
                return;
            }

            subTask->setText(inputSubTask->text());
            inputSubTask->setHidden(true);
            subTask->setHidden(false);
            checkBox->setVisible(true);  // Показываем чекбокс после ввода подзадачи
        });

        // Подключаем сигнал для чекбокса
        connect(checkBox, &QCheckBox::toggled, [this, subTask](bool checked) {
            if (checked) {
                subTask->setStyleSheet("font-size: 14px; max-height: 20px; margin-right: 10px; padding-left: 5px; border: none; max-width: 300px; min-width: 300px; text-decoration: line-through; color: #aaa;");
            } else {
                subTask->setStyleSheet("font-size: 14px; max-height: 20px; margin-right: 10px; padding-left: 5px; border: none; max-width: 300px; min-width: 300px; text-decoration: none; color: #000;");
            }
        });

        // Добавляем новый subWidget в layout
        this->taskLayout->addWidget(subWidget, 0, Qt::AlignHCenter);
        this->taskWidget->adjustSize();
        this->taskWidget->update();
    });
}

void ScheduleWidget::initCompleteTaskBtn() {
    this->completeTaskBtn = new QPushButton("✓ Complete", this->taskWidget);
    this->completeTaskBtn->setStyleSheet("QPushButton {"
                                         "background-color: #18aa03;"
                                         "padding: 10px;"
                                         "border-radius: 5px;"
                                         "color: #fff;"
                                         "max-width: 120px;"
                                         "height: 20px;"
                                         "margin-top: 10px;"
                                         "font-size: 14px;"
                                         "font-weight: bold;"
                                         "} "
                                         "QPushButton:hover {"
                                         "background-color: #1dcd04;"
                                         "}");

    this->taskLayout->addWidget(this->completeTaskBtn);
}

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    this->initTaskCommentBtns();   // Инициализируем кнопки переключения
    this->initStackedWidget();     // Инициализируем stacked widget для переключаемых видов
    this->initMainLayout();        // Устанавливаем основной layout
}

void ScheduleWidget::createNewTask() {
    this->initTaskWidgetAndLayout();
    this->initDeleteTaskBtn();
    this->initLine();
    this->initInputTask();
    this->initTaskLabel();

    this->subTaskLayout = new QVBoxLayout();

    this->initAddSubTaskBtn();
    this->initSubTaskWidget();
    this->taskLayout->addStretch(0);
    this->taskLayout->setSpacing(0);
    this->initLine();
    this->initCompleteTaskBtn();

    layout()->addWidget(taskWidget);
    layout()->setAlignment(Qt::AlignRight);
}
