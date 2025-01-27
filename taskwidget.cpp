#include "taskwidget.h"

void TaskWidget::initFont() {
    this->font = this->label->font();
}

void TaskWidget::initLabel() {
    this->label->setStyleSheet("color: #000; font-size: 19px; font-weight: 600; max-width: 100px");  // Убираем отступы
    this->label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // Выравниваем по левому краю, без отступов
    this->label->setWordWrap(true);  // Разрешаем перенос текста
    this->label->setTextInteractionFlags(Qt::TextEditorInteraction);
}

void TaskWidget::initEditButton() {
    QIcon changeIco("icons/pencil.png");
    this->buttonEdit->setIcon(changeIco);
    this->buttonEdit->setIconSize(QSize(52, 25));
    this->buttonEdit->setFixedSize(52, 25);
    this->buttonEdit->setStyleSheet("background-color: transparent;");
    this->buttonEdit->setVisible(false);

    connect(this->buttonEdit, &QPushButton::clicked, [=]() {
        // Проверка на пустой текст
        if (this->label->text().isEmpty()) {
            // Если текст пустой, не показываем QLineEdit и не удаляем объект
            return;
        }

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
        QString newText = input->text().trimmed(); // Убираем пробелы

        if (newText.isEmpty()) {
            // Если текст пустой, удаляем сам виджет
            this->label->clear();  // Очищаем текст в лейбле
            this->label->setVisible(false); // Скрываем лейбл
            this->input->setVisible(false); // Скрываем поле ввода
            this->onDeleteClicked(); // Вызываем удаление виджета
            return; // Прерываем выполнение функции
        }

        // Обновляем метку с новым текстом
        this->label->setText(newText);
        this->label->setVisible(true);
        this->input->setVisible(false);
        this->preTextLayout->addStretch();
        this->onChangeClicked(newText);
    });
}

void TaskWidget::initDeleteButton() {
    QIcon deleteIco("icons/close.png");
    this->buttonDelete->setIcon(deleteIco);
    this->buttonDelete->setIconSize(QSize(52,25));
    this->buttonDelete->setFixedSize(52,25);
    this->buttonDelete->setStyleSheet("background-color: transparent;");
    this->buttonDelete->setVisible(false);

    connect(this->buttonDelete, &QPushButton::clicked, this, &TaskWidget::onDeleteClicked);
}

void TaskWidget::initCompleteTaskButton() {
    QIcon completeIco("icons/checked.png");
    this->completeTaskButton->setIcon(completeIco);
    this->completeTaskButton->setIconSize(QSize(52,31));
    this->completeTaskButton->setFixedSize(52,31);
    this->completeTaskButton->setStyleSheet("background-color: transparent;");
    this->completeTaskButton->setVisible(false);

    connect(this->completeTaskButton, &QPushButton::clicked, this, &TaskWidget::onCompleteTask);
}

void TaskWidget::initSpacer() {
    this->spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void TaskWidget::initPreTextLayout() {
    this->initSpacer();
    this->preTextLayout = new QHBoxLayout();
    // this->preTextLayout->addItem(this->spacer);
    this->preTextLayout->addWidget(this->label);
    this->preTextLayout->addWidget(this->input);
}

void TaskWidget::initTextLayout() {
    this->initPreTextLayout();
    this->textLayout = new QVBoxLayout();
    this->textLayout->addLayout(this->preTextLayout);
    // this->textLayout->addWidget(this->line);

    // Установим фиксированную ширину для текстового блока, чтобы окно не расширялось
    this->label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void TaskWidget::initButtonsLayout() {
    // Вставляем кнопки в горизонтальный layout
    this->buttonsLayout = new QHBoxLayout();
    this->buttonsLayout->addWidget(this->buttonEdit);
    this->buttonsLayout->addWidget(this->buttonDelete);
    this->buttonsLayout->addWidget(this->completeTaskButton);
}

void TaskWidget::initMainLayout() {
    // Основной layout, размещаем текст слева и кнопки справа

    this->frame = new QFrame(this);

    this->frame->setFrameShape(QFrame::StyledPanel);
    this->frame->setFrameShadow(QFrame::Raised);
    this->frame->setStyleSheet("QFrame {"
                         "border: 2px solid black;"
                         "border-radius: 10px;"
                         "background-color: #EAE2F9;"
                         "padding: 10px;"
                         "}");

    this->mainLayout = new QHBoxLayout(this);

    this->connectLayout = new QHBoxLayout(frame);
    this->connectLayout->addLayout(this->textLayout);
    // this->mainLayout->setLayout(this->textLayout);
    this->connectLayout->addStretch();  // Добавляем растяжку, чтобы кнопки были справа
    // this->frame->setLayout(this->buttonsLayout);
    this->connectLayout->addLayout(this->buttonsLayout);
    // this->frame->setLayout(this->connectLayout);
    // this->mainLayout->addWidget(this->frame);
}

TaskWidget::TaskWidget(const QString& id, const QString &text, QWidget *parent)
    : QWidget(parent), label(new QLabel(text, this)), buttonEdit(new QPushButton(this)), buttonDelete(new QPushButton(this)),
    completeTaskButton(new QPushButton(this)), input(new QLineEdit(this)), toggle(false)
{
    this->initFont();
    this->initLabel();
    this->initEditButton();
    this->initInput();
    this->initDeleteButton();
    this->initCompleteTaskButton();
    this->initTextLayout();
    this->initButtonsLayout();
    this->initMainLayout();

    setLayout(this->mainLayout);
    setMouseTracking(true); // Включаем отслеживание движения мыши
}

TaskWidget::TaskWidget(QString text, QWidget *parent)
    : QWidget(parent), label(new QLabel(text, this)), buttonEdit(new QPushButton(this)), buttonDelete(new QPushButton(this)),
    completeTaskButton(new QPushButton(this)), input(new QLineEdit(this)), toggle(false)
{

    static int currentId = 0; // Статический счетчик для уникальных идентификаторов
    id = QString::number(currentId++);

    this->initFont();
    // this->id->setStyleSheet("color: #000; font-size: 19px; font-weight: 600;");
    this->label->setStyleSheet("color: #000; font-size: 19px; font-weight: 600; max-width: 250px");  // Убираем отступы

    this->label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // Выравниваем по левому краю, без отступов
    this->label->setWordWrap(true);  // Разрешаем перенос текста
    // this->label->setFixedWidth(300);
    this->label->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->initEditButton();
    this->initInput();
    this->initDeleteButton();
    this->initCompleteTaskButton();
    this->initSpacer();
    this->preTextLayout = new QHBoxLayout();
    // this->preTextLayout->addWidget(this->id);
    // this->preTextLayout->addItem(this->spacer);
    this->preTextLayout->addWidget(this->label);
    this->preTextLayout->addWidget(this->input);
    this->textLayout = new QVBoxLayout();
    this->textLayout->addLayout(this->preTextLayout);
    // this->textLayout->addWidget(this->line);
    this->initButtonsLayout();
    this->initMainLayout();

    this->mainLayout->addWidget(this->frame);
    setLayout(this->mainLayout);
    setMouseTracking(true); // Включаем отслеживание движения мыши
}

TaskWidget::TaskWidget(TaskWidget* other, QWidget *parent)
    : QWidget(parent), label(other->label), buttonEdit(other->buttonEdit), buttonDelete(other->buttonDelete),
    input(other->input), toggle(false)    {

    static int currentId = 0; // Статический счетчик для уникальных идентификаторов
    id = QString::number(currentId++);

    this->initFont();
    // this->id->setStyleSheet("color: #000; font-size: 19px; font-weight: 600;");
    this->label->setStyleSheet("color: #000; font-size: 19px; font-weight: 600; max-width: 200px");  // Убираем отступы
    this->label->setWordWrap(true);
    this->label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);  // Выравниваем по левому краю, без отступов
    this->label->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->initEditButton();
    this->initInput();
    this->initDeleteButton();
    this->initSpacer();
    this->preTextLayout = new QHBoxLayout();
    // this->preTextLayout->addWidget(this->id);
    // this->preTextLayout->addItem(this->spacer);
    this->preTextLayout->addWidget(this->label);
    this->preTextLayout->addWidget(this->input);
    this->textLayout = new QVBoxLayout();
    this->textLayout->addLayout(this->preTextLayout);
    // this->textLayout->addWidget(this->line);
    this->initButtonsLayout();
    this->initMainLayout();

    setLayout(this->mainLayout);
    setMouseTracking(true); // Включаем отслеживание движения мыши
}

void TaskWidget::setText(const QString& text) {
    this->label->setText(text);
}

QString TaskWidget::getFullText() {
    QString text = this->label->text();
    qDebug() << "Returning full text: " << text;  // Для отладки
    return text;
}

QString TaskWidget::getId() const {
    return id;  // Возвращаем уникальный идентификатор
}

const QPushButton* TaskWidget::getDeleteButton() const
{
    return this->buttonDelete;
}

const bool& TaskWidget::getToggle() const {
    return this->toggle;
}

void TaskWidget::setColor(const QString& bgColor, const QString& color)
{
    frame->setStyleSheet("border: 2px solid black; border-radius: 10px; background-color: #f0f0f0; padding: 10px; background-color: " + bgColor);
    if (!toggle)
        this->label->setStyleSheet("font-size: 19px; font-weight: 600; max-width: 250px;" + color);

    this->input->setStyleSheet("font-size: 19px; font-weight: 600;" + color);
}

void TaskWidget::setLabelColor(const QString& color)
{
    this->label->setStyleSheet("font-size: 19px; font-weight: 600; max-width: 250px;" + color);
}

void TaskWidget::setToggle(const bool &toggle) {
    this->toggle = toggle;
}

void TaskWidget::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    buttonEdit->setVisible(true); // Показываем кнопку при наведении
    buttonDelete->setVisible(true); // Показываем кнопку при наведении
    completeTaskButton->setVisible(true);
}

void TaskWidget::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    buttonEdit->setVisible(false); // Скрываем кнопку, когда курсор уходит
    buttonDelete->setVisible(false); // Скрываем кнопку, когда курсор уходит
    completeTaskButton->setVisible(false);
}

void TaskWidget::onChangeClicked(const QString& newText) {
    emit changeTask(newText);  // Отправляем сигнал на удаление
}

void TaskWidget::onDeleteClicked() {
    QString taskText = this->getFullText();
    this->label->clear();
    this->input->clear();
    this->label->setVisible(false);
    this->input->setVisible(false);
    // this->line->clearMask();
    // this->line->setVisible(false);



    emit deleteClicked(taskText);  // Отправляем сигнал на удаление
    delete this;
}

void TaskWidget::onCompleteTask() {
    if (!toggle)
        this->label->setStyleSheet("font-size: 19px; font-weight: 600; color: #077e2d");
    else
        this->label->setStyleSheet("font-size: 19px; font-weight: 600;");

    toggle = !toggle;

    emit completeTask(this->label->text(), this->toggle);
}
