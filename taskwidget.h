#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include "libs.h"

class TaskWidget : public QWidget {
    Q_OBJECT

private:
    QLabel *label;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QFrame *line;
    QLineEdit *input;
    QFont font;
    QVBoxLayout *textLayout;
    QHBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;

    void initFont();
    void initLabel();
    void initLine();
    void initEditButton();
    void initInput();
    void initDeleteButton();
    void initTextLayout();
    void initButtonsLayout();
    void initMainLayout();

public:
    TaskWidget(const QString &text, int index, QWidget *parent = nullptr);
    void updateTextIndex(int newIndex);

    const QPushButton* getDeleteButton() const;

signals:
    void deleteClicked(TaskWidget* item);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onDeleteClicked();
};

#endif // TASKWIDGET_H
