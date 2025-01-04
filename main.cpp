#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include "login.h"  // Подключаем заголовочный файл для Greetings
#include "welcomewnd.h"  // Подключаем заголовочный файл для MainWindow

int haveAccountAndShowLogin() {
    QFile file("login_data.txt");

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        QMessageBox::critical(nullptr, "File Error", "File not found.");
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file.";
        QMessageBox::critical(nullptr, "File Error", "Failed to open file for reading.");
        return 0;
    }

    QTextStream in(&file);
    int showLogin = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();

        // if ((line.startsWith("Username: ") && !line.mid(10).isEmpty()) || (line.startsWith("Remember: ") && line.mid(10) == 0))
        //     return true;

        if (line.startsWith("Username: "))
        {
            if (!line.mid(10).isEmpty())
            {
                qDebug() << "username: " << line.mid(10);
                showLogin = 1;
            }
        }
        if (line.startsWith("Remember: "))
        {
            if (line.mid(10).toInt() == 2)
            {
                qDebug() << "remember: " << line.mid(10).toInt();
                return 2;
                qDebug() << "have account";
            }
        }
        else
        {
            return 0;
            qDebug() << "have not account";
        }
    }

    return showLogin;
}

int handleReadPassword() {
    QFile file("login_data.txt");  // Путь к файлу. Убедитесь, что файл существует.

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        QMessageBox::critical(nullptr, "File Error", "File not found.");
        return 0;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file.";
        QMessageBox::critical(nullptr, "File Error", "Failed to open file for reading.");
        return 0;
    }

    QTextStream in(&file);
    int remembNum = 0;  // Инициализируем значение по умолчанию

    // Читаем файл построчно и ищем строку с паролем
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("Remember: ")) {
            remembNum = line.mid(10).toInt();  // Извлекаем число после "Remember: "
            qDebug() << "Found Remember value: " << remembNum;  // Логируем найденное значение
            break;
        }
    }

    file.close();
    return remembNum;  // Возвращаем считанное значение
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // В зависимости от значения, открываем нужное окно
    if (handleReadPassword() == 0 || haveAccountAndShowLogin() == 1) {
        Login *window = new Login();
        window->show();

    } else if (handleReadPassword() == 2 || haveAccountAndShowLogin() == 2) {
        WelcomeWnd *window = new WelcomeWnd();
        window->show();
    }


    return a.exec();  // Возвращаем результат работы
}
