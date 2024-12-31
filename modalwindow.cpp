#include "modalwindow.h"

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
    setModal(true); // Модальное окно

    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton* btn = new QPushButton("Закрыть", this);
    layout->addWidget(btn);
    setLayout(layout);
    resize(300, 800);

    // По нажатию на кнопку, закрывать окно
    connect(btn, &QPushButton::clicked, this, &ModalWindow::slideOut);
}

void ModalWindow::slideIn(const QPoint &startPosition, int finalWidth) {
    move(startPosition);  // Позиционируем окно у левого края основного окна

    // Анимация ширины
    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    animation->setDuration(500); // Длительность анимации
    animation->setStartValue(QSize(0, height())); // Начальная ширина = 0
    animation->setEndValue(QSize(finalWidth, height())); // Конечная ширина = ширина основного окна
    animation->start();
}

void ModalWindow::slideOut() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "size");
    animation->setDuration(500); // Длительность анимации
    animation->setStartValue(size()); // Начальная ширина (текущая ширина)
    animation->setEndValue(QSize(0, height())); // Конечная ширина = 0
    connect(animation, &QPropertyAnimation::finished, this, &ModalWindow::close); // Закрытие окна после завершения анимации
    animation->start();
}
