#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"libs.h"
#include "hoverablelabel.h"

// #include "Images/moon.png"

class TaskItemWidget : public QWidget {
    Q_OBJECT

public:
    TaskItemWidget(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent), label(new QLabel(text, this)), buttonEdit(new QPushButton(this)), buttonDelete(new QPushButton(this)), line(new QFrame(this)),
        lineEdit(new QLineEdit(this))    {

        font = label->font();

        QFontMetrics fm(font);

        label->setStyleSheet("font-size: 19px; font-weight: 600;");

        int textWidth = fm.horizontalAdvance(label->text());

        // line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setFixedWidth(textWidth * 2);

        lineEdit->setVisible(false);

        // Скрыть кнопку по умолчанию
        QIcon changeIco("G:/Work/untitled1/Images/pencil.png");
        buttonEdit->setIcon(changeIco);
        buttonEdit->setIconSize(QSize(52,25));
        buttonEdit->setFixedSize(52,25);
        buttonEdit->setStyleSheet("background-color: transparent;");
        buttonEdit->setVisible(false);

        connect(buttonEdit, &QPushButton::clicked, [=]() {
            label->setVisible(false);
            lineEdit->setVisible(true);
            lineEdit->setText(label->text());
            lineEdit->setFocus();
        });

        connect(lineEdit, &QLineEdit::returnPressed, [=]() {
            label->setText(lineEdit->text());
            label->setVisible(true);
            lineEdit->setVisible(false);
        });

        QIcon deleteIco("G:/Work/untitled1/Images/close.png");
        buttonDelete->setIcon(deleteIco);
        buttonDelete->setIconSize(QSize(52,25));
        buttonDelete->setFixedSize(52,25);
        buttonDelete->setStyleSheet("background-color: transparent;");
        buttonDelete->setVisible(false);

        connect(buttonDelete, &QPushButton::clicked, this, &TaskItemWidget::onDeleteClicked);

        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->addWidget(label);
        textLayout->addWidget(line);

        // Вставляем кнопки в горизонтальный layout
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(buttonEdit);
        buttonLayout->addWidget(buttonDelete);

        // Основной layout, размещаем текст слева и кнопки справа
        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addLayout(textLayout);
        mainLayout->addStretch();  // Добавляем растяжку, чтобы кнопки были справа
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
        setMouseTracking(true); // Включаем отслеживание движения мыши
    }

    const QPushButton* getDeleteButton() const;

signals:
    void deleteClicked(TaskItemWidget* item);

protected:
    void enterEvent(QEvent *event) override {
        QWidget::enterEvent(event);
        buttonEdit->setVisible(true); // Показываем кнопку при наведении
        buttonDelete->setVisible(true); // Показываем кнопку при наведении
    }

    void leaveEvent(QEvent *event) override {
        QWidget::leaveEvent(event);
        buttonEdit->setVisible(false); // Скрываем кнопку, когда курсор уходит
        buttonDelete->setVisible(false); // Скрываем кнопку, когда курсор уходит
    }

private slots:
    void onDeleteClicked() {
        emit deleteClicked(this);  // Отправляем сигнал на удаление
    }

private:
    QLabel *label;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QFrame *line;
    QLineEdit *lineEdit;
    QFont font;
};

class MainWindow : public QWidget
{
     Q_OBJECT
    // Q_OBJECT

private:
    QColor currentBackgroundColor = Qt::white;
    QLabel *label;
    QHBoxLayout *topLayout;
    QVBoxLayout *mainLayout;
    QPushButton *button;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QFont basicFont;
    QFont inputFont;
    QPoint offset;  // Смещение при перетаскивании
    QLabel *tasks;
    QPushButton* addTasks;
    QLineEdit* inputField;
    QLabel *savedTextLabel;
    QVector<QLabel*> posts;
    QVector<QLabel *> taskLabels;
    QHBoxLayout *tasksLayout;
    // QPushButton *changePostBtn;
    QVBoxLayout* widgetLayout;
    QVector<TaskItemWidget*> widgets;

    int countOfTasks = 1;
    bool dragging = false;  // Флаг для отслеживания, перетаскивается ли окно

    void changeBackgroundColor();
    void onCreateInputClicked();
    void onEnterPressed();
    void onDeleteText(TaskItemWidget* item);
    void updatePostsLabel();
    void showButton(QLabel* label);

private slots:
    void onItemClicked(QListWidgetItem *item) {
        // Здесь можно обработать клик, если необходимо
    }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    // void leaveEvent(QEvent *event) override;
    // bool eventFilter(QObject *watched, QEvent *event) override;
    // void enterEvent(QEvent* event) override;

public:
    MainWindow();
    ~MainWindow();
};
#endif // MAINWINDOW_H
