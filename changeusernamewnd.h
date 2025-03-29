#ifndef CHANGEUSERNAMEWND_H
#define CHANGEUSERNAMEWND_H

#include "libs.h"
#include "mainwindow.h"

class ChangeUsernameWnd : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;

    QColor currentBackgroundColor = QColor(234,226,249);

    QVBoxLayout* mainLayout;
    QHBoxLayout *btnsLayout;

    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton* confirmChanges;
    QPushButton *confirmPassword;

    QLabel* newUsername;
    QLabel* password;

    QPoint offset;

    QLineEdit* inputUsername;
    QLineEdit* inputPassword;

    bool passwordVisible;
    bool dragging = false;

    void initCentralWidget();
    void initCloseWindowButton();
    void initHideWindowButton();
    void initBtnsLayout();
    void initCheckPassword();
    void initCheckNewUsername();
    void initMainLayout();

    bool checkCorrectlyData();

    QString handleReadPassword();

private slots:
    void MsgToMain();

signals:
    void mainByClick();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public:
    explicit ChangeUsernameWnd(QWidget *parent = nullptr);
};

#endif // CHANGEUSERNAMEWND_H
