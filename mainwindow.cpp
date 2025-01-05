#include "mainwindow.h"

void MainWindow::changeBackgroundColor()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if (this->toggle)
    {
        setStyleSheet("background-color: #1e1e20;");
        this->label->setStyleSheet("color: #fff");
        this->tasks->setStyleSheet("color: #fff");
        this->inputField->setStyleSheet("color: #fff");
        this->savedTextLabel->setStyleSheet("color: #fff");
        // this->modal->setBackgroundColor(QColor(51,51,56));
        QIcon icon("icons/sun.png");
        button->setIcon(icon);

        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #fff");
        }
        // this->taskWidget->setLabelColor("color: #fff");
    }
    else
    {
        setStyleSheet("background-color: #EAE2F9");
        this->label->setStyleSheet("color: #000");
        this->tasks->setStyleSheet("color: #000");
        this->inputField->setStyleSheet("color: #000");
        this->savedTextLabel->setStyleSheet("color: #000");
        // this->modal->setBackgroundColor(QColor(219,211,233));
        QIcon icon("icons/moon.png");
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
    QString enteredText = this->inputField->text().trimmed();  // Удаляем пробелы с начала и конца

    // Проверяем, что строка не пустая после удаления пробелов
    if (!enteredText.isEmpty()) {
        QString stringIndex = QString::number(this->countOfTasks);

        // Добавляем точку между индексом и текстом
        QString fullText = "." + enteredText;

        // Теперь передаем только fullText без индекса в TaskWidget
        this->taskWidget = new TaskWidget(QString::number(countOfTasks), fullText.trimmed(), this);
        this->widgets.append(taskWidget);
        widgetLayout->addWidget(taskWidget);

        // Изменение цвета текста в зависимости от фона
        if (currentBackgroundColor == QColor(234,226,249)) {
            for (int i = 0; i < widgets.size(); ++i) {
                this->widgets[i]->setLabelColor("color: #000");
            }
        } else {
            for (int i = 0; i < widgets.size(); ++i) {
                this->widgets[i]->setLabelColor("color: #fff");
            }
        }

        connect(taskWidget, &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);

        updatePostsLabel();

        // Очищаем поле ввода
        this->inputField->clear();
        this->inputField->setVisible(false);

        this->countOfTasks++;
    } else {
        // Если введенный текст пуст или состоит только из пробелов
        QMessageBox::warning(this, "Ошибка", "Текст не может быть пустым!");
        this->inputField->clear();
        this->inputField->setVisible(false);
    }
}

void MainWindow::onDeleteText(TaskWidget* item) {
    widgetLayout->removeWidget(item);

    // Удаляем сам виджет
    item->deleteLater();

    // Пересчитываем индексы для всех оставшихся виджетов
    for (int i = 1; i < widgets.size(); ++i) {
        // Переназначаем индексы для оставшихся задач
        QString newId = QString::number(i);
        widgets[i]->setId(newId);  // Обновляем id
    }

    // Обновляем количество задач
    this->countOfTasks = widgets.size();

    // Также обновляем отображение индекса в других местах
    updatePostsLabel();
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

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        // Останавливаем стандартное поведение для Space
        event->ignore();

        // Явно предотвратить сворачивание окна
        this->setWindowState(Qt::WindowActive);

        return;  // Останавливаем дальнейшую обработку события
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::focusInEvent(QFocusEvent *event) {
    // Убедитесь, что фокус внутри главного окна
    QWidget::focusInEvent(event);
}

void MainWindow::focusOutEvent(QFocusEvent *event) {
    // Обрабатываем потерю фокуса, если нужно
    QWidget::focusOutEvent(event);
}

bool MainWindow::event(QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        // Если нажата клавиша Space, блокируем её
        if (keyEvent->key() == Qt::Key_Space) {
            event->ignore();  // Игнорируем событие
            return true;  // Не пропускаем событие дальше
        }
    }
    return QMainWindow::event(event);  // Для остальных событий передаем дальше
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    // Проверяем нажатие клавиши Space
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Space) {
            // Игнорируем событие (не даем сворачивать окно)
            event->ignore();
            return true;  // Событие обработано, не передаем дальше
        }
    }
    // Для всех остальных событий передаем дальше
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::initCloseWindowButton() {
    QIcon redIcon("icons/red_circle.png");
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
    QIcon greenIcon("icons/green_circle.png");
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

    QIcon icon("icons/moon.png");
    this->button->setIcon(icon);
    this->button->setIconSize(QSize(52,52));
    this->button->setStyleSheet(QString("QPushButton {"
                                        "border-radius: %1px;"
                                        "border: none;"
                                        "}").arg(52 / 2));

    // Обработчик для кнопки
    connect(this->button, &QPushButton::clicked, this, &MainWindow::changeBackgroundColor);
}

void MainWindow::initModalUserMenuBtn() {
    // this->modal = new ModalWindow(QColor(219,211,233), this);

    this->modalUser = new QPushButton(this);
    this->modalUser->setIcon(QIcon("icons/user.png"));
    this->modalUser->setIconSize(QSize(52,52));
    this->modalUser->setStyleSheet(QString("QPushButton {"
                                           "border-radius: %1px;"
                                           "border: none;"
                                           "}").arg(52 / 2));

    connect(this->modalUser, &QPushButton::clicked, this, &MainWindow::showModalWindow);

}

void MainWindow::initAddTasks() {
    this->tasks = new QLabel("Add tasks", this);
    this->tasks->setFont(this->basicFont);

    this->addTasks = new QPushButton(this);
    QIcon plusIcon("icons/plus.png");
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
    this->btnsLayout->addWidget(this->modalUser);
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
    // this->inputsLayout->addWidget(this->openWnd);
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
    QHBoxLayout* carouselLayout = new QHBoxLayout;

    QPushButton *tasksButton = new QPushButton(this);
    tasksButton->setFixedSize(20,20);
    tasksButton->setStyleSheet(QString("QPushButton {"
                                       "border-radius: %1px;"
                                       "border: none;"
                                       "}").arg(20 / 2));
    QPushButton *calendarButton = new QPushButton(this);
    calendarButton->setFixedSize(20,20);
    calendarButton->setStyleSheet(QString("QPushButton {"
                                       "border-radius: %1px;"
                                       "border: none;"
                                       "}").arg(20 / 2));

    tasksButton->setIcon(QIcon("icons/full_circle.png"));
    calendarButton->setIcon(QIcon("icons/empty_circle.png"));

    carouselLayout->addStretch(1);
    carouselLayout->addWidget(tasksButton);
    carouselLayout->addWidget(calendarButton);
    carouselLayout->addStretch(1);

    this->stackedWidget = new QStackedWidget(this);
    this->tasksSlide = new QWidget(this);
    this->tasksSlideLayout = new QVBoxLayout(tasksSlide);
    this->tasksSlideLayout->addLayout(this->tasksLayout);
    this->tasksSlideLayout->addLayout(this->inputsLayout);
    this->tasksSlideLayout->addLayout(this->widgetLayout);

    this->calendarSlide = new QWidget(this);
    this->calendarLayout = new QVBoxLayout(this->calendarSlide);
    QCalendarWidget *calendar = new QCalendarWidget(calendarSlide);
    this->calendarLayout->addWidget(calendar);

    this->stackedWidget->addWidget(this->tasksSlide);
    this->stackedWidget->addWidget(this->calendarSlide);

    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->topLayout);
    // this->mainLayout->addLayout(this->tasksLayout);
    // this->mainLayout->addLayout(this->inputsLayout);
    this->mainLayout->addWidget(this->stackedWidget);
    this->mainLayout->addLayout(carouselLayout);
    // this->mainLayout->addLayout(this->widgetLayout);
    // this->mainLayout->addLayout(this->tasksSlideLayout);

    connect(tasksButton, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(0);
        tasksButton->setIcon(QIcon("icons/full_circle.png"));
        calendarButton->setIcon(QIcon("icons/empty_circle.png"));
    });

    connect(calendarButton, &QPushButton::clicked, this, [=]() {
        stackedWidget->setCurrentIndex(1);
        tasksButton->setIcon(QIcon("icons/empty_circle.png"));
        calendarButton->setIcon(QIcon("icons/full_circle.png"));
    });
}

void MainWindow::showModalWindow() {
    if (this->toggle)
    {
        this->modal = new ModalWindow(QColor(219,211,233), this);
        this->modal->setBackgroundColor(false, "background-color: #DBD3E9");

    }
    else
    {
        this->modal = new ModalWindow(QColor(51,51,56), this);
        this->modal->setBackgroundColor(true, "background-color: #333338");
    }

    this->modal->show();
    this->modal->slideIn();  // Запуск анимации выдвижения
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("Track Your Day");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon("icons/logo.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    this->installEventFilter(this);
    setMouseTracking(true);

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(shortcut, &QShortcut::activated, this, []() {
        // Обрабатываем нажатие клавиши Space, но не сворачиваем окно
    });

    QWidget* centralWidget = new QWidget;

    this->initCloseWindowButton();
    this->initHideWindowButton();
    this->initModalUserMenuBtn();

    this->label = new QLabel("Let's start the day by making a plan for today", this);
    this->label->setAlignment(Qt::AlignCenter); // Центрируем текст

    // Изменяем шрифт для текста
    this->basicFont = this->label->font();
    this->basicFont.setPointSize(17);    // Устанавливаем размер шрифта
    this->label->setFont(this->basicFont);   // Применяем шрифт к метке

    // this->openWnd = new QPushButton;

    // connect(this->openWnd, &QPushButton::clicked, this, &MainWindow::openSecondWindow);

    this->initChangeThemeButton();
    this->initAddTasks();
    this->initBtnsLayout();
    this->initTopLayout();
    this->initInputsLayout();
    this->initTasksLayout();
    this->initWidgetLayout();
    this->initMainLayout();


    // this->carouselWidget = new CarouselWidget(this);

    // Устанавливаем макет для окна
    centralWidget->setLayout(this->mainLayout);
    setCentralWidget(centralWidget);
    // setLayout(this->mainLayout);

    resize(750, 800); // Устанавливаем фиксированный размер окна (опционально)
}

MainWindow::~MainWindow() {}
