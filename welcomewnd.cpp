#include "welcomewnd.h"

void WelcomeWnd::paintEvent(QPaintEvent* event) {
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

void WelcomeWnd::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Захватываем окно при нажатии левой кнопкой мыши
        this->dragging = true;
        offset = event->globalPos() - frameGeometry().topLeft();  // Сохраняем смещение для корректного перемещения
        event->accept();
    }
}

// Обработчик движения мыши (перемещение окна)
void WelcomeWnd::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Перемещаем окно в зависимости от движения мыши
        move(event->globalPos() - offset);  // Перемещаем окно с учетом смещения
        event->accept();
    }
}

// Обработчик отпускания кнопки мыши (завершение перетаскивания)
void WelcomeWnd::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Завершаем захват при отпускании левой кнопки мыши
        dragging = false;
        event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

void WelcomeWnd::initCentralWidget() {
    this->centralWidget = new QWidget(this);
}

void WelcomeWnd::initCloseWindowButton() {
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

void WelcomeWnd::initHideWindowButton() {
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

void WelcomeWnd::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addStretch();
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);
}

void WelcomeWnd::initMainLayout() {
    this->mainLayout = new QVBoxLayout(this->centralWidget);
    this->mainLayout->setContentsMargins(0, 10, 0, 0); // Убираем все отступы
    this->mainLayout->setSpacing(0);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addWidget(this->welcomeUser);
    this->mainLayout->addWidget(this->btn);
}

QString WelcomeWnd::handleReadPassword() {
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

void WelcomeWnd::openSecondWindow() {
    this->close();
    MainWindow *main = new MainWindow();  // Создаем второе окно
    main->show();           // Открываем его как модальное окно
}

WelcomeWnd::WelcomeWnd(QWidget *parent) : QMainWindow(parent), passwordVisible(false) {
    setWindowTitle("Второе окно");
    setWindowIcon(QIcon("icons/logo.png"));
    // Создаем простой виджет в центре окна

    this->initCentralWidget();
    this->initCloseWindowButton();
    this->initHideWindowButton();
    this->initBtnsLayout();

    QString user = handleReadPassword();

    this->welcomeUser = new QLabel("Welcome " + user + "!", this);
    this->welcomeUser->setStyleSheet("font-size: 20px; font-weight: 600; margin-top: 40px");
    this->welcomeUser->setAlignment(Qt::AlignHCenter);

    this->btn = new QPushButton("Greeting", this);
    this->btn->setStyleSheet(R"(
            QPushButton {
                background-color: #6e61e0;
                border: none;
                border-radius: 30px;
                padding: 10px;
                color: white;
                font-size: 16px;
                font-weight: 600;
                margin-left: auto;
                margin-bottom: 50px;
                margin-right: auto;
                max-width: 420px;
                height: 40px;
            }
            QPushButton:hover {
                background-color: #45a049;
            }
        )");

    connect(this->btn, &QPushButton::clicked, this, &WelcomeWnd::openSecondWindow);

    this->initMainLayout();
    this->centralWidget->setLayout(this->mainLayout);
    setCentralWidget(this->centralWidget);
    resize(450, 250);
}

