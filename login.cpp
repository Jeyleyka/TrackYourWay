#include "login.h"

void Login::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание для плавных линий

    // Рисуем слегка закругленные углы
    QPainterPath path;
    path.setFillRule(Qt::WindingFill); // Определяем правило заливки

    int radius = 20; // Радиус закругления углов
    path.addRoundedRect(0, 0, width(), height(), radius, radius); // Добавляем закругленные углы

    // Применяем путь как маску для рисования
    painter.setClipPath(path);
    painter.fillRect(rect(), currentBackgroundColor); // Заливаем фон окна белым цветом

    // Применяем маску для окна (закругленные углы)
    QRegion region(path.toFillPolygon().toPolygon());
    setMask(region);  // Применяем маску к окну
}

void Login::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Захватываем окно при нажатии левой кнопкой мыши
        this->dragging = true;
        offset = event->globalPos() - frameGeometry().topLeft();  // Сохраняем смещение для корректного перемещения
        event->accept();
    }
}

// Обработчик движения мыши (перемещение окна)
void Login::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Перемещаем окно в зависимости от движения мыши
        move(event->globalPos() - offset);  // Перемещаем окно с учетом смещения
        event->accept();
    }
}

// Обработчик отпускания кнопки мыши (завершение перетаскивания)
void Login::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Завершаем захват при отпускании левой кнопки мыши
        dragging = false;
        event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

void Login::initCentralWidget() {
    this->centralWidget = new QWidget(this);
    this->centralWidget->setContentsMargins(0,0,0,0);
}

void Login::initCloseWindowButton() {
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(QIcon("icons/red_circle.png"));
    this->closeBtn->setIconSize(QSize(32,32));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "max-width: 16px;"
                                         "max-height: 16px;"
                                          "background-color: #EAE2F9;"
                                         "}").arg(16 / 2));

    connect(this->closeBtn, &QPushButton::clicked, this, &QWidget::close);
}

void Login::initHideWindowButton() {
    this->hideBtn = new QPushButton(this);
    this->hideBtn->setIcon(QIcon("icons/green_circle.png"));
    this->hideBtn->setIconSize(QSize(32,32));
    this->hideBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "max-width: 16px;"
                                         "max-height: 16px;"
                                         "background-color: #EAE2F9;"
                                         "}").arg(16 / 2));

    connect(this->hideBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
}

void Login::initLogo() {
    this->logoLabel = new QLabel(this);

    QPixmap logo("icons/logo.png");
    this->scaledLogo = logo.scaled(100, 100, Qt::KeepAspectRatio);
    this->logoLabel->setPixmap(this->scaledLogo);  // Устанавливаем изображение в QLabel
    this->logoLabel->setFixedSize(100, 100);
    this->logoLabel->setAlignment(Qt::AlignCenter);
    this->username = new QLineEdit(this);
    this->username->setStyleSheet("margin-left: 28px; margin-top: 90px; max-width: 330px; height: 30px; font-size: 15px; font-weight: 500");
    this->username->setPlaceholderText("username");
}

void Login::initCheckBox() {
    this->rememberUser = new QCheckBox("Remember me", this);
    this->rememberUser->setStyleSheet("margin-left: 40px; margin-top: 10px; font-weight: 600");
    this->rememberUser->setChecked(false);  // По умолчанию не выбран
}

void Login::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->setAlignment(Qt::AlignTop);
    this->btnsLayout->addStretch(0);
    this->btnsLayout->setSpacing(0);
    this->btnsLayout->setContentsMargins(0,10,0,0);
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);

}

void Login::initLogoLayout() {
    this->logoLayout = new QHBoxLayout;
    this->logoLayout->setContentsMargins(0, 100, 0, 50);
    this->logoLayout->addWidget(this->logoLabel);
}

void Login::initPasswordLayout() {
    this->passwordLayout = new QHBoxLayout();
    this->password = new QLineEdit(this);
    this->password->setStyleSheet("max-width: 330px; margin-top: 10px; height: 30px; font-size: 15px; font-weight: 500");
    this->password->setPlaceholderText("password");
    this->password->setEchoMode(QLineEdit::Password);
    this->passwordLayout->addWidget(this->password);
}

void Login::initCheckData() {
    this->btn = new QPushButton("LOG IN", this);
    this->btn->setStyleSheet("QPushButton {"
                             "max-width: 300px;"
                             "margin-top: 30px;"
                             "border-radius: 20px;"
                             "margin-left: 40px;"
                             "height: 30px;"
                             "font-size: 15px;"
                             "font-weight: 600;"
                             "background-color: #109831"
                             "}"
                             "QPushButton:hover {"
                             "background-color: #15c13f;"
                             "}");

    connect(this->btn, &QPushButton::clicked, this, &Login::checkCorrectlyData);

    this->changeUsername = new QPushButton("change username?", this);
    this->changeUsername->setStyleSheet("QPushButton {"
                             "max-width: 300px;"
                             "margin-top: 10px;"
                             "margin-left: 40px;"
                             "height: 30px;"
                             "font-size: 15px;"
                             "font-weight: 600;"
                             "background-color: #EAE2F9;"
                             "color: #6f608a;"
                             "}"
                             "QPushButton:hover {"
                             "color: #b699ea;"
                             "}");
}

void Login::initChangeUsrWnd() {
    this->changeUsrWnd = new ChangeUsernameWnd();
    connect(this->changeUsername, &QPushButton::clicked, this, [this]() {
        this->changeUsrWnd->show();
        this->hide();
    });
}

void Login::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this->centralWidget);
    this->mainLayout->setContentsMargins(0, 0, 0, 0); // Убираем все отступы
    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->logoLayout);
    this->mainLayout->addWidget(this->username);
    this->mainLayout->addLayout(this->passwordLayout);
    this->mainLayout->addWidget(this->rememberUser);
    this->mainLayout->addWidget(this->btn);
    this->mainLayout->addWidget(this->changeUsername);
}

bool Login::checkCorrectlyData() {
    QFile file("login_data.txt");
    int rem = this->rememberUser->isChecked() ? 2 : 0;  // Определяем состояние чекбокса

    if (this->haveAccountAndShowLogin() == 1) {
        if (!file.exists()) {
            QMessageBox::critical(nullptr, "File Error", "File not found.");
            return false;
        }

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "File Error", "Failed to open file for reading.");
            return false;
        }

        QTextStream in(&file);
        QString fileContent = in.readAll();  // Читаем всё содержимое файла

        QString usernameData;
        QString passwordData;

        // Перебираем содержимое и извлекаем данные для логина и пароля
        QStringList lines = fileContent.split("\n", QString::SkipEmptyParts);
        for (const QString& line : lines) {
            if (line.startsWith("Username: ")) {
                usernameData = line.mid(10);  // Извлекаем имя пользователя
            } else if (line.startsWith("Password: ")) {
                passwordData = line.mid(10);  // Извлекаем пароль
            }
        }

        // Проверка на существование и изменение строки "Remember:"
        QRegExp rememberRegex(R"(Remember:\s*\d)");  // Регулярное выражение для поиска строки "Remember:"

        if (fileContent.contains(rememberRegex)) {
            // Если строка "Remember:" существует, заменяем её
            fileContent.replace(rememberRegex, "Remember: " + QString::number(rem));
        } else {
            // Если строки "Remember:" нет, добавляем её в конец
            fileContent.append("\nRemember: " + QString::number(rem));
        }

        // Перезаписываем файл с обновленным содержимым
        file.resize(0);  // Очищаем файл перед записью
        QTextStream out(&file);
        out << fileContent;  // Записываем изменённое содержимое

        file.close();

        // Сравниваем введённые данные с данными из файла
        if (this->username->text() == usernameData && this->password->text() == passwordData) {
            this->close();
            MainWindow* main = new MainWindow();  // Создаём главное окно
            main->show();
            this->openWnd = true;
            connect(main, &MainWindow::showLoginByClicked, this, &Login::show);
            return true;
        } else {
            QMessageBox::warning(this, "Input error", "Incorrect password or username");
        }
    }

    return false;
}

int Login::haveAccountAndShowLogin() {
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

        if (line.startsWith("Username: "))
        {
            if (!line.mid(10).isEmpty())
            {
                qDebug() << "username: " << line.mid(10);
                return 1;
            }
        }
        if (line.startsWith("Remember: "))
        {
            if (line.mid(10).toInt() == 2)
            {
                qDebug() << "remember: " << line.mid(10).toInt();
                return 2;
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

void Login::handleLogin() {
    int state = this->haveAccountAndShowLogin();
    qDebug() << "state: " << state;

    if (state == 0)
    {
        QString usernameText = this->username->text();
        QString passwordText = this->password->text();
        int remUs = this->rememberUser->checkState();

        if (usernameText.isEmpty() || passwordText.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
            return;
        }

        QFile file("login_data.txt");

        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream out(&file);
            out << "Username: " << usernameText << "\n";
            out << "Password: " << passwordText << "\n";
            out << "Remember: " << QString::number(remUs) << "\n\n";
            file.close();

            QMessageBox::warning(this, "Input Error", "Data saved successfully.");
            return;
        } else {
            QMessageBox::warning(this, "File Error", "Failed to write to the file.");
        }
    }
}

void Login::handleData() {
    QString usernameText = this->username->text();
    QString passwordText = this->password->text();

    if (usernameText.isEmpty()) {
        this->username->setStyleSheet("max-width: 330px; margin-left: 28px; margin-top: 90px; height: 30px; font-size: 15px; font-weight: 500; border: 2px solid red;");
        QMessageBox::warning(this, "Input Error", "Username is required.");
        return;
    } else {
        this->username->setStyleSheet("max-width: 330px; margin-left: 28px; margin-top: 90px; height: 30px; font-size: 15px; font-weight: 500");  // Сбрасываем стиль
    }

    if (passwordText.isEmpty()) {
        this->password->setStyleSheet("max-width: 330px; margin-top: 10px; height: 30px; font-size: 15px; font-weight: 500; border: 2px solid red;");
        QMessageBox::warning(this, "Input Error", "Password is required.");
        return;
    } else {
        this->password->setStyleSheet("max-width: 330px; margin-top: 10px; height: 30px; font-size: 15px; font-weight: 500");  // Сбрасываем стиль
    }

    // Продолжение обработки...
}

Login::Login(QWidget *parent) : QMainWindow(parent),
    passwordVisible(false),
    openWnd(false)
{
    // Инициализация центрального виджета и остальных элементов интерфейса
    this->initCentralWidget();
    this->initCloseWindowButton();
    this->initHideWindowButton();
    this->initLogo();
    this->initCheckBox();
    this->initBtnsLayout();
    this->initLogoLayout();
    this->initPasswordLayout();
    this->initCheckData();
    this->initChangeUsrWnd();
    this->initMainLayout();

    // Установка центрального виджета
    this->centralWidget->setLayout(this->mainLayout);
    setCentralWidget(this->centralWidget);

    // Настройка окна
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setAttribute(Qt::WA_TranslucentBackground);  // Окно без фона
    this->setFixedSize(400, 700); // Размер окна
    this->setWindowIcon(QIcon("icons/logo.png"));  // Установка иконки окна

    // Подключение сигнала успешного входа
    connect(this->btn, &QPushButton::clicked, this, &Login::handleLogin);

    qDebug() << "LOGIN IS CREATED!\n";

    // Стиль для текста кнопок и других элементов
    this->setStyleSheet("QLineEdit {"
                        "background-color: #ffffff;"
                        "border: 1px solid #dcdcdc;"
                        "border-radius: 5px;"
                        "padding: 5px;"
                        "}"
                        "QPushButton {"
                        "background-color: #3498db;"
                        "color: white;"
                        "border: none;"
                        "border-radius: 5px;"
                        "padding: 10px;"
                        "}"
                        "QCheckBox {"
                        "font-size: 14px;"
                        "}");
}
