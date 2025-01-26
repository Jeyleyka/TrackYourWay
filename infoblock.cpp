#include "infoblock.h"

InfoBlock::InfoBlock(const QString &mainHeader, const QStringList &subItems, QWidget *parent)
    : QWidget(parent),
    mainHeaderLabel(new QLabel(this)),
    frame(new QFrame(this)),
    layout(new QVBoxLayout(frame)), countOfCompleteTasks(0), countOfTasks(0)
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

    setFixedWidth(200);

    // Главный заголовок
    mainHeaderLabel->setText(mainHeader);
    mainHeaderLabel->setStyleSheet("font-size: 18px; font-weight: bold; max-height: 20px");

    // Подпункты
    subItemLabels.clear();
    for (const QString &item : subItems) {
        QLabel *subItemLabel = new QLabel(item, this);
        // subItemLabel->setStyleSheet("font-size: 14px; font-weight: 400; max-height: 20px");

        if (item.contains(" - complete"))
        {
            this->countOfCompleteTasks++;
            subItemLabel->setStyleSheet("font-size: 14px; font-weight: 400; max-height: 20px; color: #077e2d");
        }
        else
            subItemLabel->setStyleSheet("font-size: 14px; font-weight: 400; max-height: 20px; color: #e00018");

        int index = item.indexOf("-");
        subItemLabel->setText(item.left(index));

        subItemLabels.append(subItemLabel);
    }

    for (int i = 0; i < this->subItemLabels.size(); ++i) {
        this->countOfTasks++;

        // if (this->subItemLabels[i]->text().contains(" - complete"))
        //     this->countOfCompleteTasks++;
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

    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    setSizePolicy(sizePolicy);
    setMaximumHeight(mainHeaderLabel->height() * 6 + subItemLabels.size() * 30);
}

InfoBlock::~InfoBlock()
{
    // Удаление всех подписок происходит автоматически при уничтожении виджетов.
}

void InfoBlock::updateMainHeader(const QString &newHeader) {
    mainHeaderLabel->setText(newHeader);
}

void InfoBlock::setBackgroundColor(const QString &Bgcolor, const QString &color) {
    frame->setStyleSheet("border: 2px solid black; border-radius: 10px; background-color: #f0f0f0; padding: 10px; background-color: " + Bgcolor);
    this->mainHeaderLabel->setStyleSheet("font-size: 18px; font-weight: bold; max-height: 20px; color: " + color);

    // for (QLabel *item : subItemLabels) {
    //     item->setStyleSheet("font-size: 14px; font-weight: 500; max-height: 20px; color: " + color);
    // }
}

const int& InfoBlock::getCountOfTasks() const {
    return this->countOfTasks;
}

const int& InfoBlock::getCountOfCompleteTasks() const {
    return this->countOfCompleteTasks;
}

