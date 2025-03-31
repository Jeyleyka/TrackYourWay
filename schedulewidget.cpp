#include "schedulewidget.h"

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

void ScheduleWidget::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->addWidget(this->newTaskBtn);
    this->mainLayout->setAlignment(this->newTaskBtn, Qt::AlignRight | Qt::AlignTop);  // Выравнивание кнопки по центру
}

void ScheduleWidget::initTaskWidgetAndLayout() {
    this->taskWidget = new QWidget(this);
    this->taskWidget->setFixedWidth(500);
    // this->taskWidget->setMinimumHeight(800);
    this->taskWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    this->taskWidget->setStyleSheet("background-color: #fff; border-radius: 5px; border: 1px solid #ccc; padding: 15px");

    this->taskLayout = new QVBoxLayout(this->taskWidget);
}

void ScheduleWidget::initDeleteTaskBtn() {
    this->deleteTaskBtn = new QPushButton("Delete", taskWidget);
    this->deleteTaskBtn->setStyleSheet("background-color: #f44336; padding: 10px; color: white; border-radius: 5px; margin-bottom: 20px;");
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
                                    "}"
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
        this->subTaskLayout->addWidget(subWidget, 0, Qt::AlignHCenter);
        this->taskLayout->insertLayout(4, this->subTaskLayout);

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
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #1dcd04;"
                                    "}");

    this->taskLayout->addWidget(this->completeTaskBtn);
}

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    this->initAddTasksBtn();
    this->initMainLayout();

    this->setLayout(this->mainLayout);
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
