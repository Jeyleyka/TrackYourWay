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

Greetings::Greetings(QWidget *parent) : QMainWindow(parent) {
        setWindowTitle("Второе окно");

        // Создаем простой виджет в центре окна
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        QLabel *label = new QLabel("Это второе окно", this);
        layout->addWidget(label);

        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
}
