#ifndef LOGIN_H
#define LOGIN_H

#include "mainwindow.h"

class Login : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QColor currentBackgroundColor = QColor(234,226,249);
    QVBoxLayout* mainLayout;
    QHBoxLayout* logoLayout;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *passwordLayout;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton* btn;
    QLabel* logoLabel;
    QPoint offset;
    QPixmap scaledLogo;
    QLineEdit* username;
    QLineEdit* password;
    QCheckBox *rememberUser;
    QString usernameData;
    QString passwordData;

    bool passwordVisible;
    bool dragging = false;

    void initCentralWidget();
    void initCloseWindowButton();
    void initHideWindowButton();
    void initLogo();
    void initCheckBox();
    void initBtnsLayout();
    void initLogoLayout();
    void initPasswordLayout();
    void initMainLayout();

    int haveAccountAndShowLogin();

private slots:
    // void openSecondWindow();
    void handleLogin();
    bool checkCorrectlyData();
    // void handleCheckBoxStateChanged(int state);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    Login(QWidget *parent = nullptr);
};

#endif // LOGIN_H
