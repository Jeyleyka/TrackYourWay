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
            this->widgets[i]->setColor("#1e1e20", "color: #fff");
        }

        for (InfoBlock *block : infoBlocks) {
            block->setBackgroundColor("#333338", "#fff");
        }

        if (this->carousel->currentIndex() == 0)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        if (this->carousel->currentIndex() == 1)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        if (this->carousel->currentIndex() == 2)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
        }

        connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(0);
            this->tasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(1);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->historyTasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(2);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
        });
    }
    else
    {
        setStyleSheet("background-color: #EAE2F9");
        this->label->setStyleSheet("color: #000");
        this->tasks->setStyleSheet("color: #000");
        this->inputField->setStyleSheet("color: #000");
        this->savedTextLabel->setStyleSheet("color: #000");
        // this->infoBlock->setBackgroundColor("#EAE2F9", "#000");
        // this->modal->setBackgroundColor(QColor(219,211,233));
        QIcon icon("icons/moon.png");
        button->setIcon(icon);
        for (int i = 0; i < widgets.size(); ++i) {
            this->widgets[i]->setColor("#EAE2F9", "color: #000");
        }

        for (InfoBlock *block : infoBlocks) {
            block->setBackgroundColor("#DBD3E9", "#000");
        }

        if (this->carousel->currentIndex() == 0)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        else if (this->carousel->currentIndex() == 1)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        }
        else if (this->carousel->currentIndex() == 2)
        {
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
        }

        connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(0);
            this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(1);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        });

        connect(this->historyTasksSlideButton, &QPushButton::clicked, this, [=]() {
            this->carousel->setCurrentIndex(2);
            this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
            this->historyTasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
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
        qDebug() << "FULL TEXT: " << fullText;


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
        connect(newWidget, &TaskWidget::changeTask, this, &MainWindow::changeTaskInFile);
        connect(newWidget, &TaskWidget::completeTask, this, &MainWindow::setTaskToCompelete);
        this->saveTasksToFile(newWidget->getFullText());
        qDebug() << "NEW WIDGET TEXT: " << newWidget->getFullText();

        this->loadTasksFromFile();

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

void MainWindow::onDeleteText(const QString& taskId) {
    QString today = this->API->getCurrentDayOfWeek();
    TaskWidget* itemToDelete = new TaskWidget(taskId, this);

    widgetLayout->removeWidget(itemToDelete);

    // Удаляем виджет
    itemToDelete->deleteLater();
    this->updatePostsLabel();

    QFile file("other_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения.";
        return;
    }

    // Читаем строки из файла
    QTextStream in(&file);
    QStringList lines;
    bool curDay = false;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();  // Читаем строку и удаляем лишние пробелы

        // if (line.startsWith("day: "))
        // {
        //     qDebug() << "IT'S LINE: " << line;
        //     qDebug() << "IT'S DAY: " << line.mid(4).trimmed();
        //     qDebug() << "TODAY: " << today;
        //     if (line.mid(4).trimmed() == today)
        //     {
        //         qDebug() << "FIND DAY: " << line;
        //     }
        // }

        if (line.startsWith("day: ") && line.mid(4).trimmed() == today) {  // Добавляем строку, если она не совпадает с удаляемой
            curDay = true;
        }

        if (curDay && line == taskId)
        {
            qDebug() << "FIND TASKS TO DELETE: " << line;
            continue;
        }

        lines.append(line);
    }

    file.close();

    // Открываем файл для записи, чтобы перезаписать его
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Не удалось открыть файл для записи.";
        return;
    }

    // Записываем оставшиеся строки обратно в файл
    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";  // Записываем строку в файл
    }

    file.close();

    qDebug() << "Строка успешно удалена.";


    // QString today = this->API->getCurrentDayOfWeek();
    // QFile file("other_data.txt");

    // if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //     qWarning() << "Не удалось открыть файл для записи!";
    //     return;
    // }

    // QTextStream in(&file);
    // QStringList tasksForToday;
    // QString fileContent;
    // bool todayTasks = false;

    // qDebug() << "TASK FOR DELETE: " << taskId;


    // while (!in.atEnd()) {
    //     fileContent = in.readLine();

    //     // qDebug() << "CUR LINE: " << fileContent.mid(4);

    //     if (fileContent.startsWith("day: ") && fileContent.mid(4).trimmed() == today)
    //     {
    //         qDebug() << "CUR LINE: " << fileContent.mid(4);
    //         todayTasks=true;
    //         continue;
    //     }

    //     if (todayTasks)
    //     {
    //         if (fileContent.trimmed() != taskId)
    //             tasksForToday.append(fileContent);
    //     }
    // }

    // qDebug() << tasksForToday;

    // file.close();

    // if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
    //     qDebug() << "Не удалось открыть файл для записи.";
    //     return;
    // }

    // while (!in.atEnd()) {
    //     fileContent = in.readLine();

    //     if (fileContent.startsWith("day: ") && fileContent.mid(4).trimmed() == today)
    //     {
    //         for (const QString &line : tasksForToday) {
    //             in << line << "\n";  // Записываем строку в файл
    //         }
    //     }
    // }
    // file.close();
}

void MainWindow::changeTaskInFile(const QString& newText) {
    qDebug() << "NEW TEXT: " << newText;

    QString today = this->API->getCurrentDayOfWeek();
    QFile file("other_data.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения.";
        return;
    }

    QTextStream in(&file);
    QStringList todayTasks;
    QStringList finalTasksList;
    bool readTasks=false;

    while(!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith("day: ") && line.mid(4).trimmed() == today) {  // Добавляем строку, если она не совпадает с удаляемой
            readTasks = true;
            continue;
        }

        if (readTasks)
        {
            qDebug() << "FIND TASKS TO DELETE: " << line;
            break;
        }

        finalTasksList.append(line);


    }
    file.close();

    qDebug() << "DATA FROM FILE: " << todayTasks;

    for (int i = 0; i < this->widgets.size(); ++i) {
        qDebug() << "item: " << this->widgets[i]->getFullText();
    }

    todayTasks.clear();

    for (int i = 0; i < this->widgets.size(); ++i) {
        todayTasks.append(this->widgets[i]->getFullText());
    }

    qDebug() << "NEW TASKS: " << todayTasks;


    // for (int i = 0; i < todayTasks.size(); ++i) {
    //     finalTasksList.append(todayTasks[i]);
    // }

    for (int i = 0; i < finalTasksList.size(); ++i) {
        qDebug() << "FINAL: " << finalTasksList;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Не удалось открыть файл для записи.";
        return;
    }

    finalTasksList.append("day: " + today);

    for (int i = 0; i < this->widgets.size(); ++i) {
        finalTasksList.append(this->widgets[i]->getFullText());
    }

    // Записываем оставшиеся строки обратно в файл
    QTextStream out(&file);
    for (const QString &line : finalTasksList) {
        out << line << "\n";  // Записываем строку в файл
    }
    file.close();
}

void MainWindow::setTaskToCompelete(const QString& taskText, const bool& toggle) {
    QString today = this->API->getCurrentDayOfWeek();  // Текущий день недели
    QFile file("other_data.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл для чтения.";
        return;
    }

    QTextStream in(&file);
    bool curDay = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (line.startsWith("day: ") && line.mid(4).trimmed() == today) {  // Добавляем строку, если она не совпадает с удаляемой
            curDay = true;
        }

        if (curDay && line == taskText)
        {
            if (toggle)
                this->completeTasks.append(taskText);
            else
                this->completeTasks.removeOne(taskText);

        }
    }

    file.close();

    qDebug() << "COMPLETE TASKS: " << this->completeTasks;
}


void MainWindow::updateFileAfterDeletion(const QString& taskId) {
    QString today = this->API->getCurrentDayOfWeek();  // Текущий день недели
    QFile file("other_data.txt");

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи!";
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    QString dayMarker = "Day: " + today;

    if (fileContent.contains(dayMarker)) {
        int pos = fileContent.indexOf(dayMarker);
        int endOfDay = fileContent.indexOf("\nDay:", pos + 1);
        if (endOfDay == -1) {
            endOfDay = fileContent.length();
        }

        QString tasksForToday = fileContent.mid(pos, endOfDay - pos);
        QStringList lines = tasksForToday.split("\n", QString::SkipEmptyParts);
        lines.removeFirst();  // Удаляем строку "Day: <текущий день>"

        // Удаляем задачу из списка задач
        lines.removeAll(taskId.trimmed()); // Удаляем все совпадения

        // Воссоздаем обновленный блок для текущего дня
        if (lines.isEmpty()) {
            fileContent.remove(tasksForToday);  // Удаляем все задачи для текущего дня, если их не осталось
        } else {
            QString updatedDayContent = "Day: " + today + "\n" + lines.join("\n");
            fileContent.replace(tasksForToday, updatedDayContent);
        }
    }

    // Перезаписываем файл
    file.resize(0);  // Очищаем файл перед записью
    QTextStream out(&file);
    out << fileContent;
    file.close();
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

    connect(this->closeBtn,&QPushButton::clicked, this, [=]() {
        QString today = this->API->getCurrentDayOfWeek();
        QFile file("other_data.txt");

        qDebug() << "CO TASKS: " << this->completeTasks;

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        QTextStream in(&file);
        QStringList lines;
        QString completeTask;
        bool curDay = false;
        bool taskComp = false;

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();

            if (line.startsWith("day: ") && line.mid(4).trimmed() == today) {  // Добавляем строку, если она не совпадает с удаляемой
                curDay = true;
                qDebug() << "LINE: " << line;
            }

            if (curDay)
            {
                for (int i = 0; i < this->completeTasks.size(); ++i) {
                    if (line == this->completeTasks[i])
                    {
                        taskComp=true;
                        break;
                        // line + " - complete";
                        // qDebug() << "NEW LINE: " << line;
                    }
                    taskComp=false;
                }
            }

            if (taskComp)
            {
                if (!line.contains(" - complete"))
                    lines.append(line + " - complete");
            }
            else
                lines.append(line);
        }

        file.close();

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        {
            return;
        }

        QTextStream out(&file);
        for (const QString &line : lines) {
            out << line << "\n";  // Записываем строку в файл
        }

        file.close();

        qDebug() << "LIST: " << lines;

        // this->completeTasks;

        this->close();
    });
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

    this->historyTasksSlideButton = new QPushButton(this);
    this->historyTasksSlideButton->setFixedSize(20,20);
    this->historyTasksSlideButton->setStyleSheet(QString("QPushButton {"
                                                     "border-radius: %1px;"
                                                     "border: none;"
                                                     "}").arg(20 / 2));

    this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
    this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));

    connect(this->tasksSlideButton, &QPushButton::clicked, this, [=]() {
        this->carousel->setCurrentIndex(0);
        this->tasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    });

    connect(this->calendarSlideButton, &QPushButton::clicked, this, [=]() {
        this->carousel->setCurrentIndex(1);
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    });

    connect(this->historyTasksSlideButton, &QPushButton::clicked, this, [=]() {
        this->carousel->setCurrentIndex(2);
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/full_circle.png"));
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
    this->changeSlideLayout->addWidget(this->historyTasksSlideButton);
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
    this->calendar = new CalendarWidget(calendarSlide);
    this->calendarLayout->addWidget(this->calendar);
}

void MainWindow::initHistoryTasksLayout() {
    this->historyTasksSlide = new QWidget(this);



    // qDebug() << "PROCENT: " << procent;

    // QLabel *information = new QLabel;

    // information->setText("your procent of complete task equal " /*+ QString::number(procent)*/);

    // QWrapLayout* historyTasksLayout = new QWrapLayout();
    this->historyTasksLayout = new QVBoxLayout(this->historyTasksSlide);
    this->daysLayout = new QWrapLayout;
    this->informationLayout = new QHBoxLayout;
    this->informationLayout->addStretch(0);
    // this->tasksSlideLayout->addLayout(this->tasksLayout);
    // this->tasksSlideLayout->addLayout(this->inputsLayout);
    // this->tasksSlideLayout->addLayout(this->widgetLayout)
    // this->historyTasksLayout->addWidget(information);

    this->historyTasksLayout->setAlignment(Qt::AlignTop);
    this->historyTasksLayout->addLayout(this->daysLayout);
    this->historyTasksLayout->addLayout(this->informationLayout);

    // this->historyTasksLayout->setContentsMargins(0,100,0,0);
    // this->historyTasksLayout->addStretch(0);

    this->displayInfoBlocks();
}


void MainWindow::initCarousel() {
    this->carousel = new QStackedWidget(this);

    this->carousel->addWidget(this->tasksSlide);
    this->carousel->addWidget(this->calendarSlide);
    this->carousel->addWidget(this->historyTasksSlide);
}

void MainWindow::initMainLayout() {
    this->mainLayout = new QVBoxLayout;

    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->btnsLayout);
    this->mainLayout->addLayout(this->topLayout);
    this->mainLayout->addWidget(this->carousel);
    // this->mainLayout->addWidget(this->carousel);
    this->mainLayout->addLayout(this->changeSlideLayout);

    // this->displayInfoBlocks();
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

    connect(this->modal, &ModalWindow::showCalendar, this, &MainWindow::onShowCalendar);
    connect(this->modal, &ModalWindow::showHistory, this, &MainWindow::onShowHistory);
}

void MainWindow::onShowCalendar() {
    this->modal->close();
    this->carousel->setCurrentIndex(1);
    if (toggle)
    {
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    }else
    {
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    }

    qDebug() << "action complete!";
}

void MainWindow::onShowHistory() {
    this->modal->close();
    this->carousel->setCurrentIndex(2);
    if (toggle)
    {
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/full_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
    }else
    {
        this->tasksSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->calendarSlideButton->setIcon(QIcon("icons/empty_circle.png"));
        this->historyTasksSlideButton->setIcon(QIcon("icons/red_circle_2.png"));
    }

    qDebug() << "action complete!";
}

void MainWindow::loadTasksFromFile() {
    QFile file("other_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для чтения!";
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    // Здесь можно добавить логику для обработки и создания виджетов на основе содержимого файла
    qDebug() << "Загруженные данные:\n" << content;
}

void MainWindow::saveTasksToFile(const QString& widgetText) {
    QString today = this->API->getCurrentDayOfWeek(); // Текущий день недели
    QString filename = "other_data.txt";
    QString WidgetText = widgetText;

    // Получаем текущую дату
    QDate currentDate = QDate::currentDate();
    int currentWeekNumber = currentDate.weekNumber();

    // Читаем содержимое файла
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи!";
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();

    // Проверка на смену недели
    // Читаем метку последней недели из файла (например, "week: 1")
    int lastWeekNumber = -1;
    if (fileContent.contains("week:")) {
        QRegExp weekRegex("week: (\\d+)");
        int pos = fileContent.indexOf(weekRegex);
        if (pos != -1) {
            weekRegex.indexIn(fileContent, pos);
            lastWeekNumber = weekRegex.cap(1).toInt();
        }
    }

    // Если текущая неделя отличается от предыдущей, очищаем файл
    if (lastWeekNumber != currentWeekNumber) {
        qDebug() << "Новая неделя, очищаем данные старой недели.";
        fileContent.clear();  // Очищаем файл
    }

    // Теперь обрабатываем задачи для текущего дня
    QString dayMarker = "day: " + today;

    // Если запись для текущего дня уже существует
    if (fileContent.contains(dayMarker)) {
        // Находим секцию с сегодняшним днем
        int pos = fileContent.indexOf(dayMarker);
        int endOfDay = fileContent.indexOf("\nday:", pos + 1);
        if (endOfDay == -1) {
            endOfDay = fileContent.length(); // Если следующий день не найден, до конца файла
        }

        // Извлекаем задачи для сегодняшнего дня (не включая строку с днем)
        QString tasksForToday = fileContent.mid(pos, endOfDay - pos);
        QStringList lines = tasksForToday.split("\n", QString::SkipEmptyParts);
        lines.removeFirst(); // Удаляем строку "Day: <текущий день>"

        // Добавляем новую задачу
        lines.append(WidgetText);

        // Воссоздаем обновленный блок для текущего дня
        QString updatedDayContent = "day: " + today + "\n" + lines.join("\n");

        // Заменяем старую секцию на обновленную
        fileContent.replace(tasksForToday, updatedDayContent);
    } else {
        // Если записи нет, создаем новую секцию для сегодняшнего дня
        fileContent.append("\nday: " + today + "\n" + WidgetText);
    }

    // Перезаписываем файл
    file.resize(0);  // Очищаем файл перед записью
    QTextStream out(&file);
    out << fileContent;

    file.close();
}

QPair<int, QStringList> MainWindow::countDaysAndListInFile(const QString &fileName) {
    QFile file(fileName);

    // Проверяем, открылся ли файл
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return QPair<int, QStringList>(-1, QStringList());  // Возвращаем -1 и пустой список в случае ошибки
    }

    QTextStream in(&file);
    int dayCount = 0;
    QString currentLine;
    QStringList daysList;

    // Чтение файла построчно
    while (!in.atEnd()) {
        currentLine = in.readLine().trimmed();  // Читаем строку и убираем лишние пробелы

        // Если строка начинается с "Day:", увеличиваем счетчик дней
        if (currentLine.startsWith("Day:", Qt::CaseInsensitive)) {
            dayCount++;
            QString day = currentLine.mid(4).trimmed();  // Извлекаем день недели (после "Day: ")
            daysList.append(day);  // Добавляем день в список
        }
    }

    file.close();  // Закрываем файл после чтения
    return QPair<int, QStringList>(dayCount, daysList);  // Возвращаем пару: количество дней и список дней
}

QVector<InfoBlock*> MainWindow::createInfoBlocksFromFile(const QString &fileName, QWidget *parentWidget) {
    QFile file(fileName);

    // Проверяем, открылся ли файл
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return QVector<InfoBlock*>();  // Возвращаем пустой вектор в случае ошибки
    }

    QTextStream in(&file);
    QString currentLine;
    QString currentDay;
    QStringList currentTasks;
    QVector<InfoBlock*> infoBlocks;

    // Чтение файла построчно
    while (!in.atEnd()) {
        currentLine = in.readLine().trimmed();  // Читаем строку и убираем лишние пробелы

        // Если строка начинается с "Day:", это начало нового дня
        if (currentLine.startsWith("Day:", Qt::CaseInsensitive)) {
            // Если уже были задачи для дня, создаем InfoBlock для предыдущего дня
            if (!currentDay.isEmpty()) {
                InfoBlock *block = new InfoBlock(currentDay, currentTasks, parentWidget);
                infoBlocks.append(block);  // Добавляем новый InfoBlock
            }

            // Обновляем текущий день
            currentDay = currentLine.mid(4).trimmed();  // Извлекаем день недели
            currentTasks.clear();  // Очищаем список задач
        } else if (!currentLine.isEmpty()) {
            // Если строка не пустая, это задача для текущего дня


            currentTasks.append(currentLine);  // Добавляем задачу в список задач
        }
    }

    // Добавляем последний день и задачи
    if (!currentDay.isEmpty()) {
        if (currentDay == this->API->getCurrentDayOfWeek())
            currentDay = "Today:";

        InfoBlock *block = new InfoBlock(currentDay, currentTasks, parentWidget);
        infoBlocks.append(block);  // Добавляем новый InfoBlock
    }

    // for (int i = 0; i < this->infoBlocks.size(); ++i) {
    //     this->countOfTasks+=this->infoBlock[i].getCountOfTasks();
    //     this->countOfCompleteTasks+=this->infoBlock[i].getCountOfCompleteTasks();
    // }



    file.close();  // Закрываем файл после чтения
    return infoBlocks;  // Возвращаем вектор InfoBlock
}

void MainWindow::displayInfoBlocks() {
    this->infoBlocks = createInfoBlocksFromFile("other_data.txt", this);

    // QIcon infIcon("icons/exclamation.png");


    // information->setText( /*+ QString::number(procent)*/);

    // this->historyTasksLayout->addWidget(information);

    // Создаем и добавляем блоки на страницу
    for (InfoBlock *block : infoBlocks) {
        this->daysLayout->addWidget(block);
        this->countOfTasks+=block->getCountOfTasks();
        this->countOfCompleteTasks+=block->getCountOfCompleteTasks();
    }

    qDebug() << "COUNT OF TASKS: " <<this->countOfTasks;
    qDebug() << "COUNT OF COMPLETE TASKS: " <<this->countOfCompleteTasks;

    float procent = static_cast<float>(this->countOfCompleteTasks / this->countOfTasks) * 100.f;

    qDebug() << "PROCENT: " <<procent;

    this->information = new QLabel("your procent of complete tasks equal " + QString::number(procent).left(1) + "%", this);
    this->infBtn = new QPushButton(this);

    if (procent <= 50.f)
    {
        // this->infIcon.addFile("icons/exclamation.png");
        this->infBtn->setIcon(QIcon("icons/exclamation.png"));
        this->infBtn->setIconSize(QSize(25,25));
        this->infBtn->setStyleSheet(QString("QPushButton {"
                                              "border-radius: %1px;"
                                              "border: none;"
                                              "}").arg(25 / 2));

        this->information->setStyleSheet("font-size: 13px; font-weight: 500; margin-right: 80px; color: #e00018");
        this->information->setText(
            "Your procent of complete tasks equal " + QString::number(procent).left(2) + "%.You should try harder to get all the things done"
            );
    } else if (procent > 50.f && procent < 65.f)
    {
        // this->infIcon.addFile("icons/exclamation.png");
        this->infBtn->setIcon(QIcon("icons/warning.png"));
        this->infBtn->setIconSize(QSize(25,25));
        this->infBtn->setStyleSheet(QString("QPushButton {"
                                            "border-radius: %1px;"
                                            "border: none;"
                                            "}").arg(25 / 2));

        this->information->setStyleSheet("font-size: 13px; font-weight: 500; margin-right: 80px; color: #ef8506");
        this->information->setText(
            "Your procent of complete tasks equal " + QString::number(procent).left(2) + "%.Most of the tasks are finished, you just need to be a little more diligent"
            );
    }

    this->informationLayout->addWidget(this->infBtn);
    this->informationLayout->addWidget(this->information);

    this->historyTasksSlide->setLayout(daysLayout);
}

void MainWindow::loadDataFromFile() {
    QFile file("other_data.txt");  // Путь к файлу. Убедитесь, что файл существует.

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        QMessageBox::critical(nullptr, "File Error", "File not found.");
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        QStringList tasks;  // Список задач
        QString currentLine;

        bool todayTasks=false;

        in.readLine();

        // Определяем список дней недели
        QStringList daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

        while (!in.atEnd()) {
            currentLine = in.readLine().trimmed();  // Читаем строку и убираем лишние пробелы

            if (currentLine.startsWith("day: ")) {
                if (currentLine.mid(5) == this->API->getCurrentDayOfWeek())
                {
                    todayTasks=true;
                    qDebug() << "return true";
                }
                else
                {
                    todayTasks=false;
                    qDebug() << "return false";
                }
            }

            // Если строка соответствует дню недели, пропускаем её
            if (daysOfWeek.contains(currentLine)) {
                continue;  // Пропускаем строки с днями недели
            }

            if (todayTasks && !currentLine.startsWith("day: "))
            {
                int index = currentLine.indexOf("-");

                QString result = currentLine.left(index);

                TaskWidget* oldWidget = new TaskWidget(result, this);

                if (currentLine.contains(" - complete"))
                {
                    // if (oldWidget->getToggle())
                    oldWidget->setLabelColor("color: #077e2d");
                    // else
                    //     oldWidget->setLabelColor("color: #077e2d");

                    oldWidget->setToggle(true);
                }

                this->widgets.append(oldWidget);
                this->widgetLayout->addWidget(oldWidget);
                connect(oldWidget, &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);
                connect(oldWidget, &TaskWidget::changeTask, this, &MainWindow::changeTaskInFile);
                connect(oldWidget, &TaskWidget::completeTask, this, &MainWindow::setTaskToCompelete);
                tasks.append(currentLine);
            }

            // Если это строка с задачей (не пустая), добавляем её в список задач
            if (!currentLine.isEmpty()) {
                for (int i = 0; i < this->widgets.size(); ++i) {
                    connect(this->widgets[i], &TaskWidget::deleteClicked, this, &MainWindow::onDeleteText);
                }

                updatePostsLabel();

                // Очищаем поле ввода
                this->inputField->clear();
                this->inputField->setVisible(false);
            }
        }

        file.close();

        this->tasksFile.setFileName("other_data.txt");
        this->loadTasksFromFile();

    } else {
        qDebug() << "Не удалось открыть файл для чтения!";
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



    this->initChangeThemeButton();
    this->initAddTasks();
    this->initBtnsLayout();
    this->initTopLayout();
    this->initInputsLayout();
    this->initTasksLayout();
    this->initWidgetLayout();
    this->initChangeSlideLayout();
    this->initTasksSlideLayout();
    this->initHistoryTasksLayout();
    this->initCalendarLayout();
    this->initCarousel();

    this->loadDataFromFile();

    this->initMainLayout();


    // Устанавливаем макет для окна
    centralWidget->setLayout(this->mainLayout);
    setCentralWidget(centralWidget);
    // setLayout(this->mainLayout);

    resize(900, 800); // Устанавливаем фиксированный размер окна (опционально)
}

MainWindow::~MainWindow() {}
