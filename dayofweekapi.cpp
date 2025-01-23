#include "dayofweekapi.h"

QString DayOfWeekAPI::getCurrentDayOfWeek() {
    // Получаем текущую дату
    QDate currentDate = QDate::currentDate();

    // Получаем день недели (1 - Понеделник, 7 - Воскресенье)
    int dayOfWeek = currentDate.dayOfWeek();

    // Переводим число в строку дня недели
    switch (dayOfWeek) {
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    case 7: return "Sunday";
    default: return "ERROR"; // Это никогда не произойдет
    }
}

void DayOfWeekAPI::setCurrentDayOfWeek() {

}
