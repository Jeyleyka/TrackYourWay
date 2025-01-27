#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDate>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class CalendarWidget : public QWidget {
    Q_OBJECT

public:
    CalendarWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Календарь на текущий месяц");
        setFixedSize(300, 350);  // Устанавливаем фиксированный размер окна

        // Получаем текущую дату и месяц
        QDate currentDate = QDate::currentDate();
        currentMonth = currentDate.month();
        currentYear = currentDate.year();
        today = currentDate.day();

        // Читаем информацию о посещенных днях из файла
        visitedDays = readVisitedDays();

        // Создаем layout
        layout = new QGridLayout(this);

        // Заполняем календарь
        fillCalendar();

        // Отмечаем сегодняшний день как посещенный
        markDayAsVisited(today);

        // Окно будет обновляться каждую секунду, чтобы перерисовать статус текущего дня
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CalendarWidget::updateCalendar);
        timer->start(1000);  // Обновление каждую секунду
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);
    }

private:
    QGridLayout *layout;
    int currentMonth;
    int currentYear;
    int today;
    QStringList visitedDays;  // Список, в котором хранится информация о каждом дне месяца (посещен/не посещен)

    // Метод для заполнения календаря
    void fillCalendar() {
        // Получаем первый день месяца и количество дней в месяце
        QDate firstDayOfMonth(currentYear, currentMonth, 1);
        int daysInMonth = firstDayOfMonth.daysInMonth();
        int startDay = firstDayOfMonth.dayOfWeek(); // День недели первого дня месяца (1 - Понед., 7 - Воскр.)

        // Очищаем layout
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Заполняем календарь
        int row = 0, col = startDay - 1;
        for (int day = 1; day <= daysInMonth; ++day) {
            QLabel *dayLabel = new QLabel(QString::number(day));
            dayLabel->setAlignment(Qt::AlignCenter);
            dayLabel->setFixedSize(40, 40);  // Устанавливаем размер кнопки

            // Добавляем кружочек вокруг дня
            dayLabel->setStyleSheet("border: 2px solid black; border-radius: 20px;");

            // Если день посещен, отмечаем его (зеленый цвет)
            if (visitedDays[day - 1] == "1") {
                dayLabel->setStyleSheet("background-color: green; color: white; border: 2px solid black; border-radius: 20px;");
            }

            // Если это сегодня, делаем кружочек зеленым, если он посещен
            if (day == today) {
                if (visitedDays[day - 1] == "1") {
                    dayLabel->setStyleSheet("background-color: green; color: white; border: 2px solid black; border-radius: 20px;");
                } else {
                    dayLabel->setStyleSheet("border: 2px solid black; border-radius: 20px;");
                }
            }

            // Размещаем день в сетке
            layout->addWidget(dayLabel, row, col);

            // Переходим к следующей ячейке (день недели)
            col++;
            if (col == 7) {  // Переход на следующую строку (неделю)
                col = 0;
                row++;
            }
        }
    }

    // Метод для записи посещенных дней в файл
    void saveVisitedDays() {
        QFile file("visited_days.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << visitedDays.join(",");  // Записываем все данные как строку
        } else {
            qWarning() << "Не удалось открыть файл для записи!";
        }
    }

    // Метод для чтения посещенных дней из файла
    QStringList readVisitedDays() {
        QFile file("visited_days.txt");
        QStringList days;
        for (int i = 0; i < 31; ++i) {
            days.append("0");  // Изначально все дни не посещены
        }

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString line = in.readLine();
            if (!line.isEmpty()) {
                days = line.split(",");  // Разделяем строку на отдельные элементы
            }
        } else {
            qWarning() << "Не удалось открыть файл для чтения!";
        }

        return days;
    }

    // Метод для отметки текущего дня как посещенного
    void markDayAsVisited(int day) {
        visitedDays[day - 1] = "1";  // Отметить текущий день как посещенный
        saveVisitedDays();  // Сохраняем данные в файл
    }

    // Метод для обновления календаря (если требуется)
    void updateCalendar() {
        // Здесь можно добавить логику для обновления, если необходимо
    }
};
