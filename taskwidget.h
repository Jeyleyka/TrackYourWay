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
    QFrame *line;
    QLineEdit *input;
    QFont font;
    QHBoxLayout *preTextLayout;
    QVBoxLayout *textLayout;
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;
    QSpacerItem* spacer;

    void initFont();
    void initLabel();
    void initLine();
    void initEditButton();
    void initInput();
    void initDeleteButton();
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
    void setLabelColor(const QString& color);

signals:
    void changeTask(const QString& task);
    void deleteClicked(const QString& task);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onChangeClicked(const QString& newText);
    void onDeleteClicked();
};

#endif // TASKWIDGET_H
