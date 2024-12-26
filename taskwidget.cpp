#include "taskwidget.h"

void TaskWidget::initFont() {
    this->font = this->label->font();
}

void TaskWidget::initLabel() {
    this->id->setStyleSheet("font-size: 19px; font-weight: 600;");
    this->label->setStyleSheet("font-size: 19px; font-weight: 600;");
}

void TaskWidget::initLine() {
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(this->label->text());

    this->line->setFrameShape(QFrame::HLine);
    this->line->setFrameShadow(QFrame::Sunken);
    this->line->setFixedWidth(textWidth * 2);
}

void TaskWidget::initEditButton() {
    QIcon changeIco("G:/Work/untitled1/Images/pencil.png");
    this->buttonEdit->setIcon(changeIco);
    this->buttonEdit->setIconSize(QSize(52,25));
    this->buttonEdit->setFixedSize(52,25);
    this->buttonEdit->setStyleSheet("background-color: transparent;");
    this->buttonEdit->setVisible(false);

    connect(this->buttonEdit, &QPushButton::clicked, [=]() {
        this->label->setVisible(false);
        this->input->setVisible(true);
        this->input->setText(label->text());
        this->input->setFocus();
    });
}

void TaskWidget::initInput() {
    this->input->setVisible(false);
    this->input->setStyleSheet("font-size: 19px; font-weight: 600;");

    connect(this->input, &QLineEdit::returnPressed, [=]() {
        this->label->setText(input->text());
        this->label->setVisible(true);
        this->input->setVisible(false);
        this->preTextLayout->addStretch();
        this->initLine();
    });
}

void TaskWidget::initDeleteButton() {
    QIcon deleteIco("G:/Work/untitled1/Images/close.png");
    this->buttonDelete->setIcon(deleteIco);
    this->buttonDelete->setIconSize(QSize(52,25));
    this->buttonDelete->setFixedSize(52,25);
    this->buttonDelete->setStyleSheet("background-color: transparent;");
    this->buttonDelete->setVisible(false);

    connect(this->buttonDelete, &QPushButton::clicked, this, &TaskWidget::onDeleteClicked);
}

void TaskWidget::initSpacer() {
    this->spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void TaskWidget::initPreTextLayout() {
    this->initSpacer();
    this->preTextLayout = new QHBoxLayout();
    this->preTextLayout->addWidget(this->id);
    // this->preTextLayout->addItem(this->spacer);
    this->preTextLayout->addWidget(this->label);
    this->preTextLayout->addWidget(this->input);
}

void TaskWidget::initTextLayout() {
    this->initPreTextLayout();
    this->textLayout = new QVBoxLayout();
    this->textLayout->addLayout(this->preTextLayout);
    this->textLayout->addWidget(this->line);
}

void TaskWidget::initButtonsLayout() {
    // Вставляем кнопки в горизонтальный layout
    this->buttonsLayout = new QHBoxLayout();
    this->buttonsLayout->addWidget(this->buttonEdit);
    this->buttonsLayout->addWidget(this->buttonDelete);
}

void TaskWidget::initMainLayout() {
    // Основной layout, размещаем текст слева и кнопки справа
    this->mainLayout = new QHBoxLayout(this);
    this->mainLayout->addLayout(this->textLayout);
    this->mainLayout->addStretch();  // Добавляем растяжку, чтобы кнопки были справа
    this->mainLayout->addLayout(this->buttonsLayout);
}

TaskWidget::TaskWidget(const QString& id, const QString &text, QWidget *parent)
    : QWidget(parent), id(new QLabel(id)), label(new QLabel(text, this)), buttonEdit(new QPushButton(this)), buttonDelete(new QPushButton(this)), line(new QFrame(this)),
    input(new QLineEdit(this))    {

    this->initFont();
    this->initLabel();
    this->initLine();
    this->initEditButton();
    this->initInput();
    this->initDeleteButton();
    this->initTextLayout();
    this->initButtonsLayout();
    this->initMainLayout();

    setLayout(this->mainLayout);
    setMouseTracking(true); // Включаем отслеживание движения мыши
}

const QPushButton* TaskWidget::getDeleteButton() const
{
    return this->buttonDelete;
}

void TaskWidget::setId(const QString& _id) {
    this->id->setText(_id);
}

void TaskWidget::setLabelColor(const QString& color)
{
    this->label->setStyleSheet("font-size: 19px; font-weight: 600;" + color);
    this->id->setStyleSheet("font-size: 19px; font-weight: 600;" + color);
    this->input->setStyleSheet("font-size: 19px; font-weight: 600;" + color);
}

void TaskWidget::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    buttonEdit->setVisible(true); // Показываем кнопку при наведении
    buttonDelete->setVisible(true); // Показываем кнопку при наведении
}

void TaskWidget::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    buttonEdit->setVisible(false); // Скрываем кнопку, когда курсор уходит
    buttonDelete->setVisible(false); // Скрываем кнопку, когда курсор уходит
}

void TaskWidget::onDeleteClicked() {
    emit deleteClicked(this);  // Отправляем сигнал на удаление
}
