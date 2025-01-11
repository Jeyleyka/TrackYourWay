#include "infoblock.h"

InfoBlock::InfoBlock(const QString &mainHeader, const QStringList &subItems, QWidget *parent)
    : QWidget(parent),
    mainHeaderLabel(new QLabel(this)),
    frame(new QFrame(this)),
    layout(new QVBoxLayout(frame))
{
    // Настроим рамку с закругленными углами
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    frame->setStyleSheet("QFrame {"
                         "border: 2px solid black;"
                         "border-radius: 10px;"
                         "background-color: #f0f0f0;"
                         "padding: 10px;"
                         "}");

    setFixedWidth(500);

    // Главный заголовок
    mainHeaderLabel->setText(mainHeader);
    mainHeaderLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    // Подпункты
    subItemLabels.clear();
    for (const QString &item : subItems) {
        QLabel *subItemLabel = new QLabel(item, this);
        subItemLabels.append(subItemLabel);
    }

    // Добавляем виджеты в layout
    layout->addWidget(mainHeaderLabel);
    for (QLabel *subItem : subItemLabels) {
        layout->addWidget(subItem);
    }

    // Устанавливаем layout для контейнера
    frame->setLayout(layout);

    // Главный layout для InfoBlock
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(frame);
    setLayout(mainLayout);
}

InfoBlock::~InfoBlock()
{
    // Удаление всех подписок происходит автоматически при уничтожении виджетов.
}

void InfoBlock::updateMainHeader(const QString &newHeader) {
    mainHeaderLabel->setText(newHeader);
}
