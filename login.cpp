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
}

void Login::initCloseWindowButton() {
    QIcon redIcon("icons/red_circle.png");
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(redIcon);
    this->closeBtn->setIconSize(QSize(32,32));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(32 / 2));

    connect(this->closeBtn,&QPushButton::clicked, this, &MainWindow::close);
}

void Login::initHideWindowButton() {
    QIcon greenIcon("icons/green_circle.png");
    this->hideBtn = new QPushButton(this);
    this->hideBtn->setIcon(greenIcon);
    this->hideBtn->setIconSize(QSize(32,32));
    this->hideBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "}").arg(32 / 2));

    connect(this->hideBtn,&QPushButton::clicked, this, &MainWindow::showMinimized);
}

void Login::initLogo() {
    this->logoLabel = new QLabel(this);

    QPixmap logo("icons/logo.png");
    this->scaledLogo = logo.scaled(100, 100, Qt::KeepAspectRatio);
    this->logoLabel->setPixmap(this->scaledLogo);  // Устанавливаем изображение в QLabel
    this->logoLabel->setFixedSize(100, 100);
    this->logoLabel->setAlignment(Qt::AlignCenter);
}

void Login::initCheckBox() {
    this->rememberUser = new QCheckBox("Remember me", this);
    this->rememberUser->setStyleSheet("margin-left: 40px; margin-top: 10px; font-weight: 600");
    this->rememberUser->setChecked(false);  // По умолчанию не выбран
}

void Login::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addStretch();
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);
}

void Login::initLogoLayout() {
    this->logoLayout = new QHBoxLayout;
    this->logoLayout->setContentsMargins(0,100,0,50);
    this->logoLayout->addWidget(this->logoLabel);
}

void Login::initPasswordLayout() {
    this->passwordLayout = new QHBoxLayout();
    this->passwordLayout->addWidget(this->password);
}

void Login::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this->centralWidget);
    this->mainLayout->setContentsMargins(0, 0, 0, 30); // Убираем все отступы
    this->mainLayout->setSpacing(0);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->logoLayout);
    this->mainLayout->addWidget(this->username);
    // this->mainLayout->addWidget(this->password);
    this->mainLayout->addLayout(this->passwordLayout);
    this->mainLayout->addWidget(this->rememberUser);
    this->mainLayout->addWidget(this->btn);
}

bool Login::checkCorrectlyData() {
    QFile file("login_data.txt");

    if (this->haveAccountAndShowLogin() == 1)
    {
        if (!file.exists())
        {
            QMessageBox::critical(nullptr, "File Error", "File not found.");
            return false;
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(nullptr, "File Error", "Failed to open file for reading.");
            return false;
        }

        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line.startsWith("Username: ")) {
                this->usernameData = line.mid(10);
            } else if (line.startsWith("Password: ")) {
                this->passwordData = line.mid(10);
            }
        }


        if (this->username->text() == this->usernameData && this->password->text() == this->passwordData)
        {
            this->close();
            MainWindow *main = new MainWindow();  // Создаем второе окно
            main->show();
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

        // if ((line.startsWith("Username: ") && !line.mid(10).isEmpty()) || (line.startsWith("Remember: ") && line.mid(10) == 0))
        //     return true;

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

// void Login::openSecondWindow() {
//     if (haveAccountAndShowLogin() == 0)
//     {
//         this->close();
//         MainWindow *main = new MainWindow();  // Создаем второе окно
//         main->show();
//     }
//     else if (haveAccountAndShowLogin() == 1)
//     {
//         if (checkCorrectlyData() == true)
//         {
//             this->close();
//             MainWindow *main = new MainWindow();  // Создаем второе окно
//             main->show(); // Открываем его как модальное окно
//         } else {
//             QMessageBox::warning(this, "Input error", "Incorrect password or username");
//         }
//     }
// }

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

            QMessageBox::warning(this, "Input Error", "Data saved successfully!");

            this->username->clear();
            this->password->clear();
            this->rememberUser->setChecked(false);
        } else
        {
            QMessageBox::critical(this, "File Error", "Failed to open file for writing.");
        }

        this->close();
        MainWindow *main = new MainWindow();  // Создаем второе окно
        main->show();
    }
}

Login::Login(QWidget *parent) : QMainWindow(parent), passwordVisible(false) {
        setWindowTitle("Второе окно");
        setWindowIcon(QIcon("icons/logo.png"));
        // Создаем простой виджет в центре окна
        this->haveAccountAndShowLogin();
        this->initCentralWidget();
        this->initCloseWindowButton();
        this->initHideWindowButton();
        this->initLogo();

        this->initLogoLayout();
        this->initBtnsLayout();

        this->username = new QLineEdit(this);
        this->username->setPlaceholderText("Username");
        this->username->setStyleSheet(R"(
            QLineEdit {
                border: none;
                border-radius: 15px;
                padding: 10px;
                font-size: 16px;
                max-width: 420px;
                margin-left: auto;
                margin-right: auto;
                height: 40px;
            }
        )");
        this->password = new QLineEdit(this);
        this->password->setPlaceholderText("password");
        this->password->setEchoMode(QLineEdit::Password);
        this->password->setStyleSheet(R"(
            QLineEdit {
                border-radius: 15px;
                padding: 10px;
                font-size: 16px;
                margin-top: 20px;
                margin-left: auto;
                margin-right: auto;
                max-width: 420px;
                height: 40px;
            }
        )");

        this->btn = new QPushButton("Login", this);
        this->btn->setStyleSheet(R"(
            QPushButton {
                background-color: #6e61e0;
                border: none;
                border-radius: 30px;
                padding: 10px;
                color: white;
                font-size: 16px;
                font-weight: 600;
                margin-top: 40px;
                margin-left: auto;
                margin-right: auto;
                max-width: 420px;
                height: 40px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        )");

        if (haveAccountAndShowLogin() == 0)
            connect(this->btn, &QPushButton::clicked, this, &Login::handleLogin);
        else if (haveAccountAndShowLogin() == 1)
            connect(this->btn, &QPushButton::clicked, this, &Login::checkCorrectlyData);

        // connect(this->btn, &QPushButton::clicked, this, &Login::openSecondWindow);

        this->initCheckBox();
        this->initPasswordLayout();
        this->initMainLayout();
        this->centralWidget->setLayout(this->mainLayout);
        setCentralWidget(this->centralWidget);
        resize(450, 650);
}
