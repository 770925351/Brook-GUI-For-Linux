#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    proc = new QProcess;
    settings = new QSettings("user.ini",QSettings::IniFormat);
    ui->IP->setText(settings->value("IP").toString());
    ui->Port->setText(settings->value("Port").toString());
    ui->PassWord->setText(settings->value("Password").toString());
    RemeberPasswd = settings->value("remeberPasswd").toString();
    AutoLogin = settings->value("autoLogin").toString();

    if(RemeberPasswd == "true")
        ui->remember_pass->setChecked(true);
    else
        ui->PassWord->clear();
    if(AutoLogin == "true")
        ui->auto_login->setChecked(true);
    ui->login->setCheckable(true);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    proc->close();
}

void Widget::on_exit_clicked()
{
    proc->close();
    close();
}


void Widget::on_remember_pass_clicked()
{
    if (ui->remember_pass->isChecked())
        settings->setValue("remeberPasswd","true");
    else
        settings->setValue("remeberPasswd","false");

}

void Widget::on_auto_login_clicked()
{
    if (ui->auto_login->isChecked())
        settings->setValue("remeberPasswd","true");
    else
        settings->setValue("autoLogin","false");
}

void Widget::on_login_clicked(bool checked)
{
    if (checked)
    {
        shell = "./brook client -l 127.0.0.1:1080 -i 127.0.0.1 -s " + ui->IP->text() + ":" + ui->Port->text() + " -p " + ui->PassWord->text();
        if (ui->IP->text().isEmpty())
            QMessageBox::information(this,"错误","IP为空!");
        else if (ui->Port->text().isEmpty())
            QMessageBox::information(this,"错误","端口号为空!");
        else if (ui->PassWord->text().isEmpty())
            QMessageBox::information(this,"错误","密码为空!");
        else
        {
            proc->start(shell);
            settings->setValue("IP",ui->IP->text());
            settings->setValue("Port",ui->Port->text());
            settings->setValue("Password",ui->PassWord->text());
        }
    }
    else
        proc->close();
}

void Widget::on_stop_clicked()
{
    if (ui->login->isChecked())
    {
        proc->close();
        ui->login->setChecked(false);
    }
    else
        QMessageBox::information(this,"错误","还未开始!");

}
