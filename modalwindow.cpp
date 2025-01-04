#include "modalwindow.h"

void ModalWindow::initCloseBtn() {
    this->label = new QLabel("lfhsd", this);
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(QIcon("icons/modal_close.png"));
    this->closeBtn->setIconSize(QSize(30,30));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "}").arg(30 / 2));
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
    painter.fillRect(rect(), currentBackgroundColor); // Заливаем фон окна белым цветом

    // Применяем маску для окна (закругленные углы)
    QRegion region(path.toFillPolygon().toPolygon());
    setMask(region);  // Применяем маску к окну
}

ModalWindow::ModalWindow(QWidget* parent) : QDialog(parent) {
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // Окно без рамки
    // setModal(true); // Модальное окно

    QHBoxLayout *layout = new QHBoxLayout(this);
    this->initCloseBtn();
    layout->setContentsMargins(0,10,200,0);
    layout->addWidget(this->closeBtn, 0, Qt::AlignTop);
    setLayout(layout);
    setFixedHeight(800);  // Изначально окно имеет ширину 0
    setMinimumWidth(10);

    // По нажатию на кнопку, закрывать окно
    connect(this->closeBtn, &QPushButton::clicked, this, &ModalWindow::slideOut);
    // connect(this->closeBtn, &QPushButton::clicked, this, &ModalWindow::close);

    QPoint mainWindowPos = parentWidget()->pos();
    move(mainWindowPos);  // Устанавливаем начальную позицию окна

    // Настроим анимацию для расширения окна
    this->openAnimation = new QPropertyAnimation(this, "size");
    this->openAnimation->setDuration(500); // Длительность анимации
    this->openAnimation->setStartValue(QSize(0, height())); // Начальная ширина равна 0
    this->openAnimation->setEndValue(QSize(300, height())); // Конечная ширина — желаемая (300 пикселей)
}

void ModalWindow::slideIn() {
    this->openAnimation->start();
}

void ModalWindow::slideOut() {
    QPropertyAnimation *closeAnimation = new QPropertyAnimation(this, "size");
    closeAnimation->setDuration(500); // Длительность анимации
    closeAnimation->setStartValue(size()); // Начальная ширина и высота (текущий размер)
    closeAnimation->setEndValue(QSize(0, height())); // Конечная ширина — 0

    // После завершения анимации закрываем окно
    connect(closeAnimation, &QPropertyAnimation::finished, this, &ModalWindow::close);

    closeAnimation->start(); // Запускаем анимацию сужения
}

void ModalWindow::setBackgroundColor(const QColor& color) {
    this->currentBackgroundColor = color;
}
