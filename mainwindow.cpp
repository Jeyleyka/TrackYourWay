#include "mainwindow.h"

void MainWindow::changeBackgroundColor()
{
    static bool toggle = true;
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (toggle)
    {
        setStyleSheet("background-color: #000;");
        this->label->setStyleSheet("color: #fff");
        this->tasks->setStyleSheet("color: #fff");
        this->inputField->setStyleSheet("color: #fff");
        this->savedTextLabel->setStyleSheet("color: #fff");
        QIcon icon("G:/Work/untitled1/Images/sun.png");
        button->setIcon(icon);

        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #fff");
        }
        // this->taskWidget->setLabelColor("color: #fff");
    }
    else
    {
        setStyleSheet("background-color: #fff");
        this->label->setStyleSheet("color: #000");
        this->tasks->setStyleSheet("color: #000");
        this->inputField->setStyleSheet("color: #000");
        this->savedTextLabel->setStyleSheet("color: #000");
        QIcon icon("G:/Work/untitled1/Images/moon.png");
        button->setIcon(icon);
        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #000");
        }
    }

    if (!toggle)
        currentBackgroundColor = Qt::white;
    else
        currentBackgroundColor = Qt::black;
    update();

    toggle = !toggle;
}

void MainWindow::onCreateInputClicked()
{
    this->inputField->setVisible(true);
    this->inputField->clear();
    this->inputField->setFocus();
}

void MainWindow::onEnterPressed() {
    stringIndex = QString::number(this->countOfTasks);
    QString enteredText = QString::fromStdString(".") + this->inputField->text();
    // index = countOfTasks;
    QLabel *text = new QLabel(enteredText, this);
    this->taskWidget = new TaskWidget(QString::number(countOfTasks), text->text(), this);
    this->widgets.append(taskWidget);
    widgetLayout->addWidget(taskWidget);
    // widgetLayout->addWidget(taskItemWidget);

    if (currentBackgroundColor == Qt::white)
    {
        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #000");
        }
    }
    else
    {
        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #fff");
        }
    }

    connect(taskWidget, &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);

    updatePostsLabel();

    this->inputField->clear();
    this->inputField->setVisible(false);

    this->countOfTasks++;
}

void MainWindow::onDeleteText(TaskWidget* item) {
    this->widgets.removeAll(item);
    delete item;
    this->countOfTasks--;

    for (int i = 0; i < this->widgets.size(); ++i) {
        this->widgets[i]->setId(QString::number(i + 1));
    }

    // updateTextIndexes();
    qDebug() << this->widgets.size();
}

void MainWindow::paintEvent(QPaintEvent *event) {
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

void MainWindow::updatePostsLabel()
{
    QString allPosts;
    QLabel qAll;
    // transition.setText("\n");

    for (const QLabel* post : posts)
    {
        allPosts += post->text() + "\n";
        qAll.setText(allPosts);
    }

    savedTextLabel->setText(allPosts);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Захватываем окно при нажатии левой кнопкой мыши
        this->dragging = true;
        offset = event->globalPos() - frameGeometry().topLeft();  // Сохраняем смещение для корректного перемещения
        event->accept();
    }
}

// Обработчик движения мыши (перемещение окна)
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (dragging) {
        // Перемещаем окно в зависимости от движения мыши
        move(event->globalPos() - offset);  // Перемещаем окно с учетом смещения
        event->accept();
    }
}

// Обработчик отпускания кнопки мыши (завершение перетаскивания)
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        // Завершаем захват при отпускании левой кнопки мыши
        dragging = false;
        event->accept();
    }

    QWidget::mouseMoveEvent(event);
}

void MainWindow::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    this->button->setVisible(true);
}

void MainWindow::initCloseWindowButton() {
    QIcon redIcon("G:/Work/untitled1/Images/red_circle.png");
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(redIcon);
    this->closeBtn->setIconSize(QSize(32,32));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(32 / 2));

    connect(this->closeBtn,&QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::initHideWindowButton() {
    QIcon greenIcon("G:/Work/untitled1/Images/green_circle.png");
    this->hideBtn = new QPushButton(this);
    this->hideBtn->setIcon(greenIcon);
    this->hideBtn->setIconSize(QSize(32,32));
    this->hideBtn->setStyleSheet(QString("QPushButton {"
                                         "border-radius: %1px;"
                                         "border: none;"
                                         "}").arg(32 / 2));

    connect(this->hideBtn,&QPushButton::clicked, this, &MainWindow::showMinimized);
}

void MainWindow::initChangeThemeButton() {
    this->button = new QPushButton(this);

    QIcon icon("G:/Work/untitled1/Images/moon.png");
    this->button->setIcon(icon);
    this->button->setIconSize(QSize(52,52));
    this->button->setStyleSheet(QString("QPushButton {"
                                                   "border-radius: %1px;"
                                                   "border: none;"
                                                   "}").arg(52 / 2));

    // Обработчик для кнопки
    connect(this->button, &QPushButton::clicked, this, &MainWindow::changeBackgroundColor);
}

void MainWindow::initAddTasks() {
    this->tasks = new QLabel("Add tasks", this);
    this->tasks->setFont(this->basicFont);

    this->addTasks = new QPushButton(this);
    QIcon plusIcon("G:/Work/untitled1/Images/plus.png");
    this->addTasks->setIcon(plusIcon);
    this->addTasks->setIconSize(QSize(32,32));
    this->addTasks->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(32 / 2));

    connect(this->addTasks, &QPushButton::clicked, this, &MainWindow::onCreateInputClicked);

    this->inputFont.setPixelSize(15);

    this->inputField = new QLineEdit(this);
    this->inputField->setFixedSize(180, 35);
    this->inputField->setFont(this->inputFont);
    this->inputField->setPlaceholderText("describe the task");
    this->inputField->setVisible(false);

    this->savedTextLabel = new QLabel("Task", this);
    this->savedTextLabel->setFont(this->basicFont);

    connect(this->inputField, &QLineEdit::returnPressed, this, &MainWindow::onEnterPressed);
}

void MainWindow::initBtnsLayout() {
    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    this->btnsLayout = new QHBoxLayout;
    this->btnsLayout->addStretch();
    this->btnsLayout->addWidget(this->hideBtn);
    this->btnsLayout->addWidget(this->closeBtn);
}

void MainWindow::initTopLayout() {
    this->topLayout = new QHBoxLayout;
    // Добавляем растяжку для того, чтобы текст оказался по центру
    this->topLayout->addStretch(2);  // Добавляем растяжку слева
    this->topLayout->addWidget(this->label);  // Добавляем метку с текстом
    this->topLayout->addStretch(1);  // Добавляем растяжку справа
    this->topLayout->addWidget(this->button);  // Добавляем кнопку справа
}

void MainWindow::initInputsLayout() {
    this->inputsLayout = new QHBoxLayout;
    this->inputsLayout->addWidget(this->inputField);
    this->inputsLayout->addWidget(this->savedTextLabel);
    this->inputsLayout->setContentsMargins(15,0,0,0);
}

void MainWindow::initTasksLayout() {
    this->tasksLayout = new QHBoxLayout;
    this->tasksLayout->addStretch();
    this->tasksLayout->addWidget(this->tasks);
    this->tasksLayout->addWidget(this->addTasks);
    this->tasksLayout->addStretch(2);
    this->tasksLayout->setContentsMargins(15,30,0,0);
}

void MainWindow::initWidgetLayout() {
    this->widgetLayout = new QVBoxLayout;
}

void MainWindow::initMainLayout() {
    this->mainLayout = new QVBoxLayout;
    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->topLayout);
    this->mainLayout->addLayout(this->tasksLayout);
    this->mainLayout->addLayout(this->inputsLayout);
    this->mainLayout->addLayout(this->widgetLayout);
}

MainWindow::MainWindow()
{
    setWindowTitle("Track Your Day");
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    this->initCloseWindowButton();
    this->initHideWindowButton();

    this->label = new QLabel("Let's start the day by making a plan for today", this);
    this->label->setAlignment(Qt::AlignCenter); // Центрируем текст

    // Изменяем шрифт для текста
    this->basicFont = this->label->font();
    this->basicFont.setPointSize(17);    // Устанавливаем размер шрифта
    this->label->setFont(this->basicFont);   // Применяем шрифт к метке

    this->initChangeThemeButton();
    this->initAddTasks();
    this->initBtnsLayout();
    this->initTopLayout();
    this->initInputsLayout();
    this->initTasksLayout();
    this->initWidgetLayout();
    this->initMainLayout();

    // Устанавливаем макет для окна
    setLayout(this->mainLayout);
    resize(750, 800); // Устанавливаем фиксированный размер окна (опционально)
}

MainWindow::~MainWindow() {}
