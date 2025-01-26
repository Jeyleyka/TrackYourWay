#ifndef INFOBLOCK_H
#define INFOBLOCK_H

#include "libs.h"

class InfoBlock : public QWidget
{
    Q_OBJECT

public:
    explicit InfoBlock(const QString &mainHeader, const QStringList &subItems, QWidget *parent = nullptr);
    ~InfoBlock();

    void updateMainHeader(const QString &newHeader);
    void setBackgroundColor(const QString &Bgcolor, const QString &color);

    const int& getCountOfTasks() const;
    const int& getCountOfCompleteTasks() const;

private:
    QLabel *mainHeaderLabel;
    QList<QLabel *> subItemLabels;
    QFrame *frame;
    QVBoxLayout *layout;

    int countOfCompleteTasks;
    int countOfTasks;
};
#endif // INFOBLOCK_H
