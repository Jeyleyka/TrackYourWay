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

private:
    QLabel *mainHeaderLabel;
    QList<QLabel *> subItemLabels;
    QFrame *frame;
    QVBoxLayout *layout;
};
#endif // INFOBLOCK_H
