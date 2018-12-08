#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QSettings>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
     void closeEvent(QCloseEvent *event);

private slots:

    void on_exit_clicked();

    void on_remember_pass_clicked();

    void on_auto_login_clicked();

    void on_login_clicked(bool checked);

    void on_stop_clicked();

private:
    Ui::Widget *ui;
    QString shell;
    QProcess *proc;
    QSettings *settings;
    QString RemeberPasswd;
    QString AutoLogin;
    QString remeberPasswd;
    QString autoLogin;
};

#endif // WIDGET_H
