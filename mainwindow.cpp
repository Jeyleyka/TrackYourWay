#include "mainwindow.h"

const QPushButton* TaskItemWidget::getDeleteButton() const
{
    return this->buttonDelete;
}

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
    QString enteredText = QString::number(this->countOfTasks) + QString::fromStdString(".") + this->inputField->text();
    QLabel *text = new QLabel(enteredText, this);
    TaskItemWidget* taskItemWidget = new TaskItemWidget(text->text(), this);
    this->widgets.append(taskItemWidget);
    widgetLayout->addWidget(taskItemWidget);
    // widgetLayout->addWidget(taskItemWidget);

    connect(taskItemWidget, &TaskItemWidget::deleteClicked, this, &MainWindow::onDeleteText);
    // text.setText(enteredText);
    // this->listWidget->addItem(text->text());

    // this->listWidget->setGeometry(100,500,400,300);
    // this->posts.append(new TaskItemWidget(text->text(), this));  // Добавляем задачу в список

    // for (int i = 0; i < listWidget->count(); ++i) {
    //     QListWidgetItem *item = listWidget->item(i);

    //     item->setData(Qt::UserRole, QVariant(i)); // Сохраняем индекс элемента
    // }

    updatePostsLabel();

    this->inputField->clear();
    this->inputField->setVisible(false);

    this->countOfTasks++;
}

void MainWindow::onDeleteText(TaskItemWidget* item) {
    this->widgets.removeAll(item);
    delete item;
    qDebug() << this->widgets.size();
}

// void MainWindow::showButton(QLabel* label) {
//     QPoint labelPos = label->mapTo(this, QPoint(0,0));
//     this->changePostBtn->move(labelPos.x() + label->width() + 10, labelPos.y());
//     this->changePostBtn->setVisible(true);
// }

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

    // for (int i = 0; i < listWidget->count(); ++i) {
    //     QListWidgetItem *item = listWidget->item(i);
    //     // Проверяем, находится ли курсор на элементе
    //     QRect itemRect = listWidget->visualItemRect(item);
    //     if (itemRect.contains(event->pos())) {
    //         // Курсор находится на элементе
    //         // Отображаем кнопку рядом с элементом
    //         changePostBtn->move(itemRect.right() + 10, itemRect.top());
    //         changePostBtn->setVisible(true);
    //         return; // Завершаем обработку, так как кнопка уже показана
    //     }
    // }
    // // Если курсор не на элементе, скрываем кнопку
    // this->changePostBtn->setVisible(false);
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
    button->setVisible(true);
}

// void MainWindow::leaveEvent(QEvent *event) {
//     QWidget::leaveEvent(event);
//     this->changePostBtn->setVisible(false); // Прячем кнопку, когда курсор покидает виджет
// }

// bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
//     for (int i = 0; i < posts.size(); ++i) {
//         if (watched == taskLabels[i]) {
//             if (event->type() == QEvent::Enter) {
//                 showButton(i);
//             } else if (event->type() == QEvent::Leave) {
//                 hideButton(i);
//             }
//         }
//     }
//     return QWidget::eventFilter(watched, event);
// }

// void MainWindow::enterEvent(QEvent *event) {
//     for (int i = 0; i < this->posts.size(); ++i) {
//         // QLabel* label = this->posts[i];
//         if (this->posts[i]->underMouse()) {
//             showButton(this->posts[i]);
//             break;
//         } else {
//             this->changePostBtn->setVisible(false);
//         }
//     }
// }

MainWindow::MainWindow()
{
    setWindowTitle("Центрированный QLabel");
    setWindowFlags(Qt::FramelessWindowHint);

    setMouseTracking(true);

    // this->widgets = new QVBoxLayout(this);

    // QVBoxLayout *tasks = new QVBoxLayout(this);

    QIcon redIcon("G:/Work/untitled1/Images/red_circle.png");
    this->closeBtn = new QPushButton(this);
    this->closeBtn->setIcon(redIcon);
    this->closeBtn->setIconSize(QSize(32,32));
    this->closeBtn->setStyleSheet(QString("QPushButton {"
                                        "border-radius: %1px;"
                                        "border: none;"
                                        "}").arg(32 / 2));

    connect(this->closeBtn,&QPushButton::clicked, this, &MainWindow::close);

    QIcon greenIcon("G:/Work/untitled1/Images/green_circle.png");
    this->hideBtn = new QPushButton(this);
    this->hideBtn->setIcon(greenIcon);
    this->hideBtn->setIconSize(QSize(32,32));
    this->hideBtn->setStyleSheet(QString("QPushButton {"
                                          "border-radius: %1px;"
                                          "border: none;"
                                          "}").arg(32 / 2));

    connect(this->hideBtn,&QPushButton::clicked, this, &MainWindow::showMinimized);


    this->label = new QLabel("Let's start the day by making a plan for today", this);
    this->label->setAlignment(Qt::AlignCenter); // Центрируем текст

    // Изменяем шрифт для текста
    this->basicFont = label->font();
    this->basicFont.setPointSize(17);    // Устанавливаем размер шрифта
    label->setFont(this->basicFont);   // Применяем шрифт к метке

    // Создаем кнопку
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

    // connect(this->listWidget, &QListWidget::itemEntered, this, &MainWindow::onItemEntered);
    // connect(this->listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);

    this->tasks = new QLabel("Add tasks", this);
    this->tasks->setFont(this->basicFont);
    // this->tasks->setAlignment(Qt::AlignLeft);

    this->addTasks = new QPushButton(this);
    QIcon plusIcon("G:/Work/untitled1/Images/plus.png");
    this->addTasks->setIcon(plusIcon);
    this->addTasks->setIconSize(QSize(32,32));
    this->addTasks->setStyleSheet(QString("QPushButton {"
                                        "border-radius: %1px;"
                                        "border: none;"
                                        "}").arg(32 / 2));

    // this->editTasksBtn = new QPushButton(this);
    // this->editTasksBtn->setIcon(pencilIcon);
    // this->addTasks->setIconSize(QSize(32,32));

    connect(this->addTasks, &QPushButton::clicked, this, &MainWindow::onCreateInputClicked);

    this->inputFont.setPixelSize(15);

    this->inputField = new QLineEdit(this);
    this->inputField->setFixedSize(180, 35);
    this->inputField->setFont(this->inputFont);
    this->inputField->setPlaceholderText("describe the task");
    this->inputField->setVisible(false);

    this->savedTextLabel = new QLabel("Task", this);
    this->savedTextLabel->setFont(this->basicFont);


    // this->listWidget = new QListWidget(this);
    // this->listWidget->setGeometry(0, 0, 400, 300);

    // connect(this->listWidget, &QListWidget::itemEntered, this, &MainWindow::onItemEntered);

    connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::onEnterPressed);

    // for (int i = 0; i < this->posts.size(); i++) {
    //     QString taskText = QString("Task %1").arg(i + 1);
    //     HoverableLabel* newLabel = new HoverableLabel(taskText, this);
    //     newLabel->move(10,30 + i*40);
    //     newLabel->show();

    //     this->posts.append(newLabel);
    // }
    // connect(listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);

    QIcon changeIco("G:/Work/untitled1/Images/pencil.png");
    // this->changePostBtn = new QPushButton(this);
    // this->changePostBtn->setIcon(changeIco);
    // this->changePostBtn->setIconSize(QSize(52,52));
    // this->changePostBtn->setVisible(true);

    // Создаем горизонтальный макет для кнопки, чтобы она была в правом верхнем углу
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(this->hideBtn);
    btnLayout->addWidget(this->closeBtn);

    QHBoxLayout *topLayout = new QHBoxLayout;

    // Добавляем растяжку для того, чтобы текст оказался по центру
    topLayout->addStretch(2);  // Добавляем растяжку слева
    topLayout->addWidget(label);  // Добавляем метку с текстом
    topLayout->addStretch(1);  // Добавляем растяжку справа
    topLayout->addWidget(button);  // Добавляем кнопку справа

    QHBoxLayout *inputsLayout = new QHBoxLayout;
    inputsLayout->addWidget(this->inputField);
    inputsLayout->addWidget(this->savedTextLabel);
    // inputsLayout->addWidget(this->editTasksBtn);
    inputsLayout->setContentsMargins(15,0,0,0);

    tasksLayout = new QHBoxLayout;
    tasksLayout->addStretch();
    tasksLayout->addWidget(this->tasks);
    tasksLayout->addWidget(this->addTasks);
    tasksLayout->addStretch(2);
    // tasksLayout->addWidget(new TaskItemWidget("Task 1", this));
    // tasksLayout->addWidget(new TaskItemWidget("Task 2", this));
    // tasksLayout->addWidget(new TaskItemWidget("Task 3", this));
    tasksLayout->setContentsMargins(15,30,0,0);

    this->widgetLayout = new QVBoxLayout;
    // widgetLayout->addWidget(new TaskItemWidget("Task 1", this));
    // widgetLayout->addWidget(new TaskItemWidget("Task 2", this));
    // widgetLayout->addWidget(new TaskItemWidget("Task 3", this));
    // tasksLayout->addStretch(2);
    // widgetLayout->setContentsMargins(0,50,0,50);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(tasksLayout);
    mainLayout->addLayout(inputsLayout);
    mainLayout->addLayout(widgetLayout);
    // mainLayout->addLayout(this->widgetLayout);
    // mainLayout->addLayout(listWidgetLayout);

    // Устанавливаем макет для окна
    setLayout(mainLayout);
    resize(750, 800); // Устанавливаем фиксированный размер окна (опционально)
}

MainWindow::~MainWindow() {}
