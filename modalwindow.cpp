#include "modalwindow.h"

ModalWindow::ModalWindow(QColor color, QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // Окно без рамки
    setModal(true); // Модальное окно

    // Создаем layout и кнопку
    this->btnLayout = new QHBoxLayout;
    // this->setBackgroundColor(this->currentBackgroundColor);
    this->initCloseBtn();
    this->btnLayout->setContentsMargins(0,5,240,0);
    this->btnLayout->addWidget(this->closeBtn);

    this->menuLayout = new QVBoxLayout;
    this->menuLayout->addWidget(this->weekTasks);

    this->menuLayout->addWidget(this->line);
    this->menuLayout->setContentsMargins(0,0,0,670);
    this->menuLayout->setSpacing(0);
    this->currentBackgroundColor = color;
    // this->label->setStyle(color);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->addLayout(this->btnLayout);
    this->mainLayout->addLayout(this->menuLayout);

    setLayout(this->mainLayout);
    setFixedHeight(800);  // Высота окна
    setMinimumWidth(10);  // Минимальная ширина

    // Подключаем сигнал закрытия окна
    connect(this->closeBtn, &QPushButton::clicked, this, &ModalWindow::slideOut);
}

void ModalWindow::initCloseBtn() {
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(QIcon("icons/cancel_wh.png"));
    this->closeBtn->setIconSize(QSize(30, 30));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(30 / 2));

    this->weekTasks = new QPushButton("Таски за прошлые дни", this);
    this->weekTasks->setStyleSheet("border: none;");
    this->line = new QFrame;
    this->line->setFrameShape(QFrame::HLine);
    this->line->setFrameShadow(QFrame::Sunken);
    this->line->setFixedWidth(170);
    this->line->setStyleSheet("background-color: red");
}

void ModalWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание для плавных линий
    // Рисуем слегка закругленные углы
    QPainterPath path;
    path.setFillRule(Qt::WindingFill); // Определяем правило заливки
    int radius = 20; // Радиус закругления углов
    path.addRoundedRect(0, 0, width(), height(), radius, radius); // Добавляем закругленные углы
    // Применяем путь как маску для рисования
    painter.setClipPath(path);
    painter.fillRect(rect(), this->currentBackgroundColor); // Заливаем фон окна белым цветом
    // Применяем маску для окна (закругленные углы)
    QRegion region(path.toFillPolygon().toPolygon());
    setMask(region);  // Применяем маску к окну
}

void ModalWindow::slideIn() {
    QPoint mainWindowPos = parentWidget()->pos();
    move(mainWindowPos);  // Устанавливаем начальную позицию окна

    // Настроим анимацию для расширения окна
    this->openAnimation = new QPropertyAnimation(this, "size");
    this->openAnimation->setDuration(500); // Длительность анимации
    this->openAnimation->setStartValue(QSize(0, height())); // Начальная ширина
    this->openAnimation->setEndValue(QSize(300, height())); // Конечная ширина
    this->openAnimation->start();
}

void ModalWindow::slideOut() {
    QPropertyAnimation *closeAnimation = new QPropertyAnimation(this, "size");
    closeAnimation->setDuration(500); // Длительность анимации
    closeAnimation->setStartValue(size()); // Начальный размер
    closeAnimation->setEndValue(QSize(0, height())); // Конечный размер (0 по ширине)

    // После завершения анимации закрываем окно
    connect(closeAnimation, &QPropertyAnimation::finished, this, &ModalWindow::close);
    closeAnimation->start();
}

void ModalWindow::setBackgroundColor(const bool& toggle, const QString &color) {
    if (toggle)
    {
        this->closeBtn->setIcon(QIcon("icons/cancel_bl.png"));
        this->weekTasks->setStyleSheet("background-color: transparent; color: #fff;" + color);
    }
    else
    {
        this->closeBtn->setIcon(QIcon("icons/cancel_wh.png"));
        this->weekTasks->setStyleSheet("background-color: transparent; color: #000;" + color);
    }

    this->closeBtn->setStyleSheet(QString("border-radius: %1px; border: none;").arg(30 / 2) + color);
}
