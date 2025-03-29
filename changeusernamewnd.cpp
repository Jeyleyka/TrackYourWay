#include "changeusernamewnd.h"

void ChangeUsernameWnd::paintEvent(QPaintEvent* event) {
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

void ChangeUsernameWnd::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Захватываем окно при нажатии левой кнопкой мыши
        this->dragging = true;
        offset = event->globalPos() - frameGeometry().topLeft();  // Сохраняем смещение для корректного перемещения
        event->accept();
    }
}

// Обработчик движения мыши (перемещение окна)
void ChangeUsernameWnd::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Перемещаем окно в зависимости от движения мыши
        move(event->globalPos() - offset);  // Перемещаем окно с учетом смещения
        event->accept();
    }
}

// Обработчик отпускания кнопки мыши (завершение перетаскивания)
void ChangeUsernameWnd::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Завершаем захват при отпускании левой кнопки мыши
        dragging = false;
        event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

void ChangeUsernameWnd::initCentralWidget() {
    this->centralWidget = new QWidget(this);
}

void ChangeUsernameWnd::initCloseWindowButton() {
    QIcon redIcon("icons/red_circle.png");
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(redIcon);
    this->closeBtn->setIconSize(QSize(32,32));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(32 / 2));

    connect(this->closeBtn, &QPushButton::clicked, this, &ChangeUsernameWnd::close);
}

void ChangeUsernameWnd::initHideWindowButton() {
    QIcon greenIcon("icons/green_circle.png");
    this->hideBtn = new QPushButton(this);
    this->hideBtn->setIcon(greenIcon);
    this->hideBtn->setIconSize(QSize(32,32));
    this->hideBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "}").arg(32 / 2));

    connect(this->hideBtn, &QPushButton::clicked, this, &ChangeUsernameWnd::showMinimized);
}

void ChangeUsernameWnd::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addStretch();
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);
}

void ChangeUsernameWnd::initCheckPassword() {
    this->password = new QLabel("confirm that it is you", this);
    this->password->setAlignment(Qt::AlignHCenter);
    this->password->setStyleSheet("font-size: 20px; font-weight: 600; margin-top: 40px");

    this->inputPassword = new QLineEdit(this);
    this->inputPassword->setPlaceholderText("password");
    this->inputPassword->setEchoMode(QLineEdit::Password);
    this->inputPassword->setStyleSheet("max-width: 330px; margin-top: 10px; margin-left: 60px; height: 30px; font-size: 15px; border-radius: 10px; font-weight: 500");

    this->confirmPassword = new QPushButton("next", this);
    this->confirmPassword->setStyleSheet("QPushButton {"
                "background-color: #6e61e0;"
                "border: none;"
                "border-radius: 30px;"
                "padding: 10px;"
                "color: white;"
                "font-size: 16px;"
                "font-weight: 600;"
                "margin-left: auto;"
                "margin-bottom: 40px;"
                "margin-top: 20px;"
                "margin-right: auto;"
                "max-width: 420px;"
                "height: 40px;"
                "border-radius: 10px;"
            "}"
            "QPushButton:hover {"
                "background-color: #45a049;"
            "}");

    connect(this->confirmPassword, &QPushButton::clicked, this, [this]() {
        QFile file("login_data.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "File can't open in function ChangeUsernameWnd::initCheckPassword");
            return;
        }

        QTextStream in(&file);
        QString line = in.readAll();
        QString passwordData;
        QStringList lines = line.split("\n", QString::SkipEmptyParts);

        for (const QString& line : lines) {
            if (line.startsWith("Password: ")) {
                passwordData = line.mid(10);  // Извлекаем пароль
            }
        }

        if (this->inputPassword->text() == passwordData)
        {
            this->inputUsername->setReadOnly(false);
            QMessageBox::warning(nullptr, "Warning", "Password is correct, input new username");
        }
        else
            QMessageBox::critical(nullptr, "Error", "Uncorrect password");

        file.close();
    });
}

void ChangeUsernameWnd::initCheckNewUsername() {
    this->newUsername = new QLabel("input new username", this);
    this->newUsername->setStyleSheet("font-size: 20px; font-weight: 600; margin-top: 40px");
    this->newUsername->setAlignment(Qt::AlignHCenter);

    this->inputUsername = new QLineEdit(this);
    this->inputUsername->setStyleSheet("max-width: 330px; margin-top: 10px; height: 30px; margin-left: 60px; font-size: 15px; border-radius: 10px; font-weight: 500");
    this->inputUsername->setPlaceholderText("username");
    this->inputUsername->setReadOnly(true);

    this->confirmChanges = new QPushButton("confirm", this);
    this->confirmChanges->setStyleSheet(R"(
            QPushButton {
                background-color: #6e61e0;
                border: none;
                border-radius: 30px;
                padding: 10px;
                color: white;
                font-size: 16px;
                font-weight: 600;
                margin-left: auto;
                margin-bottom: 40px;
                margin-top: 20px;
                margin-right: auto;
                max-width: 420px;
                border-radius: 10px;
                height: 40px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        )");

    connect(this->confirmChanges, &QPushButton::clicked, this, [this]() {
        if (inputUsername->text().isEmpty())
        {
            QMessageBox::critical(nullptr, "Error", "Area must not be empty");
            return;
        }

        QMessageBox::warning(nullptr, "Warning", "To save changes close the application");

        QFile file("login_data.txt");

        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::critical(nullptr, "Error", "File not found in function ChangeUsernameWnd");
            return;
        }

        QTextStream in(&file);

        QString line = in.readAll();
        QRegExp rememberRegex(R"(Username:\s*[a-zA-Z]+)");

        if (line.contains(rememberRegex))
            line.replace(rememberRegex, "Username: " + this->inputUsername->text());
        else
            QMessageBox::critical(nullptr, "Error", "File not contains this line");

        file.resize(0);

        QTextStream out(&file);
        out << line;

        file.close();

        this->close();
    });
}

void ChangeUsernameWnd::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this->centralWidget);
    this->mainLayout->setContentsMargins(0, 10, 0, 0); // Убираем все отступы
    this->mainLayout->setSpacing(0);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addWidget(this->password);
    this->mainLayout->addWidget(this->inputPassword);
    this->mainLayout->addWidget(this->confirmPassword);
    this->mainLayout->addWidget(this->newUsername);
    this->mainLayout->addWidget(this->inputUsername);
    this->mainLayout->addWidget(this->confirmChanges);
}

QString ChangeUsernameWnd::handleReadPassword() {
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
    QString usName;  // Инициализируем значение по умолчанию

    // Читаем файл построчно и ищем строку с паролем
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.startsWith("Username: ")) {
            usName = line.mid(10);  // Извлекаем число после "Remember: "
            break;
        }
    }

    file.close();
    return usName;  // Возвращаем считанное значение
}

void ChangeUsernameWnd::MsgToMain() {
    emit mainByClick();
    // this->hide();
    qDebug() << "ACTION!\n";
}

ChangeUsernameWnd::ChangeUsernameWnd(QWidget *parent) : QMainWindow(parent), passwordVisible(false) {
    this->setWindowTitle("Второе окно");
    this->setWindowIcon(QIcon("icons/logo.png"));
    // Создаем простой виджет в центре окна

    this->initCentralWidget();
    this->initCloseWindowButton();
    this->initHideWindowButton();
    this->initBtnsLayout();
    this->initCheckPassword();
    this->initCheckNewUsername();
    this->initMainLayout();

    this->centralWidget->setLayout(this->mainLayout);
    this->setCentralWidget(this->centralWidget);
    this->setFixedSize(450, 450);
}

