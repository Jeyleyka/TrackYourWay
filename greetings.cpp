#include "greetings.h"

void Greetings::paintEvent(QPaintEvent *event) {
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

void Greetings::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Захватываем окно при нажатии левой кнопкой мыши
        this->dragging = true;
        offset = event->globalPos() - frameGeometry().topLeft();  // Сохраняем смещение для корректного перемещения
        event->accept();
    }
}

// Обработчик движения мыши (перемещение окна)
void Greetings::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Перемещаем окно в зависимости от движения мыши
        move(event->globalPos() - offset);  // Перемещаем окно с учетом смещения
        event->accept();
    }
}

// Обработчик отпускания кнопки мыши (завершение перетаскивания)
void Greetings::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Завершаем захват при отпускании левой кнопки мыши
        dragging = false;
        event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

void Greetings::initCloseWindowButton() {
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

void Greetings::initHideWindowButton() {
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

void Greetings::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addStretch();
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);
}

Greetings::Greetings(QWidget *parent) : QMainWindow(parent) {
        setWindowTitle("Второе окно");
        setWindowIcon(QIcon("icons/logo.png"));
        // Создаем простой виджет в центре окна
        QWidget *centralWidget = new QWidget(this);

        this->initCloseWindowButton();
        this->initHideWindowButton();

        QLabel* logoLabel = new QLabel(this);

        QPixmap logo("icons/logo.png");
        QPixmap scaledLogo = logo.scaled(100, 100, Qt::KeepAspectRatio);
        // logo.scaled(52,52,Qt::KeepAspectRatio);
        logoLabel->setPixmap(scaledLogo);  // Устанавливаем изображение в QLabel
        logoLabel->setFixedSize(100, 100);
        logoLabel->setAlignment(Qt::AlignCenter);


        this->mainLayout = new QVBoxLayout(centralWidget);
        this->logoLayout = new QHBoxLayout;
        this->logoLayout->setContentsMargins(0,50,0,0);
        this->logoLayout->addWidget(logoLabel);

        this->label = new QLabel("Это второе окно", this);
        this->btn = new QPushButton("открыть главное окно", this);

        connect(this->btn, &QPushButton::clicked, this, &Greetings::openSecondWindow);

        this->initBtnsLayout();

        // this->mainLayout->addWidget(logoLabel);
        this->mainLayout->addLayout(this->btnsLayout);
        this->mainLayout->addLayout(this->logoLayout);
        this->mainLayout->addWidget(this->label);
        this->mainLayout->addWidget(this->btn);

        centralWidget->setLayout(this->mainLayout);
        setCentralWidget(centralWidget);
        resize(450, 700);
}
