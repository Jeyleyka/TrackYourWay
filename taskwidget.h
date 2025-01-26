#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include "libs.h"

class TaskWidget : public QWidget {
    Q_OBJECT

private:
    QString id;  // Уникальный идентификатор
    QLabel *label;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QPushButton *completeTaskButton;
    // QFrame *line;
    QFrame *frame;
    QLineEdit *input;
    QFont font;
    QHBoxLayout *preTextLayout;
    QVBoxLayout *textLayout;
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *connectLayout;
    QHBoxLayout *mainLayout;
    QSpacerItem* spacer;

    bool toggle;

    void initFont();
    void initLabel();
    void initEditButton();
    void initInput();
    void initDeleteButton();
    void initCompleteTaskButton();
    void initSpacer();
    void initPreTextLayout();
    void initTextLayout();
    void initButtonsLayout();
    void initMainLayout();

public:
    int _index = 1;

    TaskWidget(const QString& id, const QString &text, QWidget *parent = nullptr);
    TaskWidget(QString text, QWidget *parent = nullptr);
    TaskWidget(TaskWidget* other, QWidget *parent);
    void updateTextIndex(int newIndex);
    void setText(const QString& text);
    QString getFullText();
    QString getId() const; // Получаем идентификатор

    const QPushButton* getDeleteButton() const;
    void setId(const QString& _id);
    void setColor(const QString& bgColor, const QString& color);
    void setToggle(const bool& toggle);

signals:
    void changeTask(const QString& task);
    void deleteClicked(const QString& task);
    void completeTask(const QString& task, const bool& toggle);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onChangeClicked(const QString& newText);
    void onDeleteClicked();
    void onCompleteTask();
};

#endif // TASKWIDGET_H
