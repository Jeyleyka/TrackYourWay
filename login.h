#ifndef LOGIN_H
#define LOGIN_H

#include "changeusernamewnd.h"

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

    const bool& getOpenMainWnd() const;

public slots:
    void showLoginWindow() {
        QWidget::show();
    }

signals:
    void loginSuccessful();  // Сигнал успешного входа

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void initCentralWidget();
    void initCloseWindowButton();
    void initHideWindowButton();
    void initLogo();
    void initCheckBox();
    void initBtnsLayout();
    void initLogoLayout();
    void initPasswordLayout();
    void initCheckData();
    void initChangeUsrWnd();
    void initMainLayout();

    bool checkCorrectlyData();
    void handleLogin();
    void handleData();
    int haveAccountAndShowLogin();  // Функция, которая проверяет наличие аккаунта

    bool openWnd = false;  // Флаг открытия главного окна
    bool passwordVisible = false;
    bool dragging = false;

    ModalWindow* mdlWnd;
    ChangeUsernameWnd *changeUsrWnd;

    QPoint offset;
    QString usernameData;
    QString passwordData;

    // Виджеты
    QColor currentBackgroundColor = QColor(234,226,249);
    QWidget *centralWidget;
    QPushButton *closeBtn;
    QPushButton *hideBtn;
    QPushButton *changeUsername;
    QLabel *logoLabel;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *btn;
    QCheckBox *rememberUser;
    QHBoxLayout *btnsLayout;
    QHBoxLayout *logoLayout;
    QHBoxLayout *passwordLayout;
    QVBoxLayout *mainLayout;

    QPixmap scaledLogo;
};

#endif // LOGIN_H
