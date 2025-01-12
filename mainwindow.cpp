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
        QIcon icon("icons/sun.png");
        button->setIcon(icon);

        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setLabelColor("color: #fff");
        }

        if (this->carousel->currentIndex() == 0)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        else
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
        }

        connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(0);
            this->tasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(1);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
        });
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

        if (this->carousel->currentIndex() == 0)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        else
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
        }

        connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(0);
            this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(1);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
        });
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
        // Добавляем точку между индексом и текстом
        QString fullText = enteredText;


        qDebug() << "создание нового виджета...";
        // Теперь передаем только fullText без индекса в TaskWidget
        TaskWidget* newWidget = new TaskWidget(fullText.trimmed(), this);
        qDebug() << "добавление нового виджета в массив...";
        this->widgets.append(newWidget);
        qDebug() << "добавление нового виджета в лайоут...";
        widgetLayout->addWidget(newWidget);

        qDebug() << "создание и добавление прошло успешно...";

        // Изменение цвета текста в зависимости от фона


        qDebug() << "конект нового виджета...";

        connect(newWidget, &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);
        this->saveTasksToFile();

        updatePostsLabel();

        // Очищаем поле ввода
        this->inputField->clear();
        this->inputField->setVisible(false);

        // this->countOfTasks++;
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
    this->saveTasksToFile();

    // Пересчитываем индексы для всех оставшихся виджетов
    // for (int i = 1; i < widgets.size(); ++i) {
    //     // Переназначаем индексы для оставшихся задач
    //     QString newId = QString::number(i);
    //     widgets[i]->setId(newId);  // Обновляем id
    // }

    // // Обновляем количество задач
    // this->countOfTasks = widgets.size();

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
    this->modal = new ModalWindow(QColor(219,211,233), this);

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

void MainWindow::initCarouselBtns() {
    QString active;

    this->tasksSlideButton = new QPushButton(this);
    this->tasksSlideButton->setFixedSize(20,20);
    this->tasksSlideButton->setStyleSheet(QString("QPushButton {"
                                                  "border-radius: %1px;"
                                                  "border: none;"
                                                  "}").arg(20 / 2));

    this->calendarSlideButton = new QPushButton(this);
    this->calendarSlideButton->setFixedSize(20,20);
    this->calendarSlideButton->setStyleSheet(QString("QPushButton {"
                                                     "border-radius: %1px;"
                                                     "border: none;"
                                                     "}").arg(20 / 2));

    this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
    this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));

    connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
        this->carousel->setCurrentIndex(0);
        this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    });

    connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
        this->carousel->setCurrentIndex(1);
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
    });
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
    // this->tasksLayout->setSpacing(0);
}

void MainWindow::initWidgetLayout() {
    this->widgetLayout = new QVBoxLayout;
}

void MainWindow::initChangeSlideLayout() {
    this->initCarouselBtns();
    this->changeSlideLayout = new QHBoxLayout;
    this->changeSlideLayout->addStretch(1);
    this->changeSlideLayout->addWidget(this->tasksSlideButton);
    this->changeSlideLayout->addWidget(this->calendarSlideButton);
    this->changeSlideLayout->addStretch(1);
}

void MainWindow::initTasksSlideLayout() {
    this->tasksSlide = new QWidget(this);

    this->tasksSlideLayout = new QVBoxLayout(this->tasksSlide);
    this->tasksSlideLayout->addLayout(this->tasksLayout);
    this->tasksSlideLayout->addLayout(this->inputsLayout);
    this->tasksSlideLayout->addLayout(this->widgetLayout);
    this->tasksSlideLayout->setContentsMargins(0,0,0,0);
    this->tasksSlideLayout->addStretch(0);
}

void MainWindow::initCalendarLayout() {
    this->calendarSlide = new QWidget(this);
    this->calendarLayout = new QVBoxLayout(this->calendarSlide);
    this->calendar = new QCalendarWidget(calendarSlide);
    this->calendarLayout->addWidget(this->calendar);
}

void MainWindow::initCarousel() {
    this->carousel = new QStackedWidget(this);

    this->carousel->addWidget(this->tasksSlide);
    this->carousel->addWidget(this->calendarSlide);
}

void MainWindow::initMainLayout() {
    this->mainLayout = new QVBoxLayout;

    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->topLayout);
    this->mainLayout->addWidget(this->carousel);
    this->mainLayout->addLayout(this->changeSlideLayout);
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

    connect(this->modal, &ModalWindow::actionPerformed, this, &MainWindow::performAction);
}

void MainWindow::performAction() {
    this->modal->close();
    this->carousel->setCurrentIndex(1);
    this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));

    qDebug() << "action complete!";
}

void MainWindow::saveTasksToFile() {
    QFile file("other_data.txt");
    QString day = this->API->getCurrentDayOfWeek();  // Текущий день недели
    QStringList lines;  // Список строк из файла
    QVector<TaskWidget*> updatedList;  // Список для хранения всех задач

    bool dayFound = false; // Переменная для поиска дня

    qDebug() << "Opening file for reading...";

    // Чтение файла
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString currentLine;

        bool dayFound = false;
        QStringList tasksForCurrentDay;  // Список строк для текущего дня (не виджетов)

        while (!in.atEnd()) {
            currentLine = in.readLine().trimmed();  // Читаем строку и убираем лишние пробелы
            lines.append(currentLine);  // Сохраняем строки из файла

            // Проверяем, если строка с днем недели
            if (currentLine.startsWith("Day: ")) {
                qDebug() << "Found day: " << currentLine.mid(4).trimmed();

                // Если нашли день, проверяем, что это текущий день
                if (currentLine.mid(4).trimmed() == day) {
                    dayFound = true;  // Устанавливаем флаг, что день найден
                    qDebug() << "Day found: " << day;
                } else if (dayFound) {
                    // Если день найден, сохраняем задачи для текущего дня
                    // Прерываем, так как мы уже нашли нужный день, и дальше уже не нужно читать задачи для других дней
                    break;
                }
            } else if (dayFound) {
                // Если день найден, сохраняем задачи для этого дня
                updatedList.append(new TaskWidget(currentLine, this));  // Добавляем задачу как виджет
            }
        }
        file.close();  // Закрытие файла после чтения
        qDebug() << "Finished reading file.";
    } else {
        QMessageBox::warning(this, "File Error", "Failed to open the file for reading.");
        return;
    }

    // Добавим новые задачи из widgets в updatedList
    for (int i = 0; i < this->widgets.size(); ++i) {
        updatedList.append(new TaskWidget(this->widgets[i]->getFullText(), this));  // Добавляем новые задачи
    }

    // Открываем файл для записи с очисткой
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);

        // Перезаписываем файл, если текущий день найден
        if (dayFound) {
            // Перезаписываем только новый день и задачи
            out << "Day: " << day << "\n";

            // Записываем все задачи без разделителей
            for (int i = 0; i < updatedList.size(); ++i) {
                out << updatedList[i]->getFullText() << "\n";  // Записываем задачу, просто с новой строки
            }
        } else {
            // Если день не найден, добавляем новый день с задачами
            out << "Day: " << day << "\n";
            for (int i = 0; i < this->widgets.size(); ++i) {
                out << this->widgets[i]->getFullText() << "\n";  // Записываем задачу
            }
        }

        file.close();  // Закрытие файла после записи
        qDebug() << "Finished writing data to file.";
    }
    else {
        QMessageBox::warning(this, "File Error", "Failed to open the file for writing.");
    }
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), networkManager(new QNetworkAccessManager(this))
{
    setWindowTitle("Track Your Day");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon("icons/logo.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    this->installEventFilter(this);
    setMouseTracking(true);

    // QStringList subItems = {"fwsdfs", "fsdfsadf"};


    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(shortcut, &QShortcut::activated, this, []() {
        // Обрабатываем нажатие клавиши Space, но не сворачиваем окно
    });

    //////////////////////////////////// FIX ZONE ////////////////////////////////////

    // this->getDayOfWeek();

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

    this->initChangeThemeButton();
    this->initAddTasks();
    this->initBtnsLayout();
    this->initTopLayout();
    this->initInputsLayout();
    this->initTasksLayout();
    this->initWidgetLayout();
    this->initChangeSlideLayout();
    this->initTasksSlideLayout();
    this->initCalendarLayout();
    this->initCarousel();

    // NetworkManager* manager = new NetworkManager(this);
    QFile file("other_data.txt");  // Путь к файлу. Убедитесь, что файл существует.

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        QMessageBox::critical(nullptr, "File Error", "File not found.");
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        QStringList tasks;  // Список задач
        QString currentLine;

        in.readLine();

        // Определяем список дней недели
        QStringList daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

        while (!in.atEnd()) {
            currentLine = in.readLine().trimmed();  // Читаем строку и убираем лишние пробелы

            // Если строка соответствует дню недели, пропускаем её
            if (daysOfWeek.contains(currentLine)) {
                continue;  // Пропускаем строки с днями недели
            }

            qDebug() << "write started";

            // Если это строка с задачей (не пустая), добавляем её в список задач
            if (!currentLine.isEmpty()) {
                tasks.append(currentLine);
                TaskWidget* oldWidget = new TaskWidget(currentLine, this);
                this->widgets.append(oldWidget);
                this->widgetLayout->addWidget(oldWidget);

                for (int i = 0; i < this->widgets.size(); ++i) {
                    connect(this->widgets[i], &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);
                }

                qDebug() << "count of widgets: " << this->widgets.size();
                updatePostsLabel();

                // Очищаем поле ввода
                this->inputField->clear();
                this->inputField->setVisible(false);
            }
        }
        qDebug() << "write is success";
        file.close();

        // Выводим все задачи

        QString currentDay = this->API->getCurrentDayOfWeek();

        this->infoBlock = new InfoBlock(currentDay, tasks, this);

    } else {
        qDebug() << "Не удалось открыть файл для чтения!";
    }

    this->initMainLayout();
    this->mainLayout->addWidget(infoBlock);

    //////////////////////////////////// FIX ZONE ////////////////////////////////////


    // Устанавливаем макет для окна
    centralWidget->setLayout(this->mainLayout);
    setCentralWidget(centralWidget);
    // setLayout(this->mainLayout);

    resize(750, 800); // Устанавливаем фиксированный размер окна (опционально)
}

MainWindow::~MainWindow() {}
