#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QWidget>
#include <QDate>
#include <QDebug>

class ScheduleWidget : public QWidget {
    Q_OBJECT

public:
    ScheduleWidget(QWidget* parent = nullptr) : QWidget(parent) {
        // Основной layout
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        // Layout для кнопок дней недели
        QHBoxLayout* weekLayout = new QHBoxLayout();
        QStringList daysOfWeek = {"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"};
        for (const QString& day : daysOfWeek) {
            QPushButton* dayButton = new QPushButton(day);
            dayButton->setStyleSheet("background-color: #EAE2F9; padding: 10px; font-weight: bold;");
            connect(dayButton, &QPushButton::clicked, this, [=]() {
                changeDay(day);
            });
            weekLayout->addWidget(dayButton);
        }

        // Создаем элемент для отображения задач для текущего дня
        QLabel* dayLabel = new QLabel("Задачи на сегодня");
        dayLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");

        // Создаем поле ввода задачи
        QLineEdit* taskInput = new QLineEdit();
        taskInput->setPlaceholderText("Введите задачу...");
        taskInput->setStyleSheet("padding: 10px; border-radius: 5px;");

        // Кнопка для добавления задачи
        QPushButton* addTaskButton = new QPushButton("Добавить задачу");
        addTaskButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px;");
        connect(addTaskButton, &QPushButton::clicked, this, [=]() {
            addTask(taskInput->text());
            taskInput->clear();
        });

        // Список задач
        taskList = new QListWidget();
        taskList->setStyleSheet("background-color: #f4f4f4; padding: 10px; border-radius: 5px;");

        // Добавляем все элементы в layout
        mainLayout->addLayout(weekLayout);
        mainLayout->addWidget(dayLabel);
        mainLayout->addWidget(taskInput);
        mainLayout->addWidget(addTaskButton);
        mainLayout->addWidget(taskList);

        setLayout(mainLayout);
        setWindowTitle("Расписание");
        resize(600, 400);

        // Изначально показываем задачи для текущего дня
        currentDay = QDate::currentDate().toString("ddd"); // Получаем день недели
        changeDay(currentDay);
    }

private slots:
    void addTask(const QString& task) {
        if (!task.isEmpty()) {
            taskList->addItem(task);
        }
    }

    void changeDay(const QString& day) {
        currentDay = day;

        // Очистить текущий список задач и показать новые задачи для выбранного дня
        taskList->clear();

        // Здесь будет логика для загрузки задач для выбранного дня из файла или памяти
        // Пример: добавим несколько фиктивных задач для демонстрации
        if (currentDay == "Пн") {
            taskList->addItem("Задача 1 для понедельника");
            taskList->addItem("Задача 2 для понедельника");
        } else if (currentDay == "Вт") {
            taskList->addItem("Задача 1 для вторника");
        }
        // Добавьте аналогичные условия для других дней
    }

private:
    QListWidget* taskList;
    QString currentDay;
};

#endif // SCHEDULEWIDGET_H
