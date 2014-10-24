#include "widget.h"
#include "ui_widget.h"
#include "connection.h"
#include <qmessagebox.h>
Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(530,393);
    creatMenuBar();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::creatMenuBar()
{
    manageAction = new QAction(tr("出售设备管理"),this);
    chartAction = new QAction(tr("销售统计"),this);
    quitAction = new QAction(tr("退出"),this);

    manageAction->setShortcut(tr("Ctrl+M"));
    chartAction->setShortcut(tr("Ctrl+C"));
    quitAction->setShortcut(tr("Ctrl+Q"));


    manegeMenu = menuBar()->addMenu(tr("销售管理"));
    manegeMenu->addAction(manageAction);
    manegeMenu->addAction(chartAction);
    manegeMenu->addSeparator();
    manegeMenu->addAction(quitAction);

    passwordMenu= menuBar()->addMenu(tr("修改密码"));
    ui->stackedWidget->setCurrentIndex(0);
    connect(manageAction,SIGNAL(triggered()),this,SLOT(on_manegeMenu_clicked()));
    connect(chartAction,SIGNAL(triggered()),this,SLOT(on_chartAction_clicked()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(on_quitAction_clicked()));
    //数据库部分操作
    QSqlQueryModel *deviceMode = new QSqlQueryModel(this);
    deviceMode->setQuery("select name from device");
    ui->comboBox_equipment->setModel(deviceMode);
}
void Widget::on_manegeMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void Widget::on_chartAction_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void Widget::on_quitAction_clicked()
{
    this->close();
}
//设备下拉框改变
void Widget::on_comboBox_equipment_currentIndexChanged(const QString &arg1)
{
    QSqlQueryModel *type = new QSqlQueryModel(this);
    type->setQuery(QString("select name from type where device='%1'").arg(arg1));
    ui->comboBox_model->setModel(type);
}
//型号下拉框改变
void Widget::on_comboBox_model_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.exec(QString("select price from type where device='%1' and name='%2' ").arg(ui->comboBox_equipment->currentText()).arg(arg1));
    query.next();
    ui->lineEdit_offer->setText(query.value(0).toString());
}

void Widget::on_spinBox_sellcount_valueChanged(int arg1)
{
    double sum=arg1*ui-> lineEdit_offer->text().toInt();
    ui->lineEdit_sellmoney->setText(QString::number(sum));
}

void Widget::on_pushButton_clicked(bool checked)//取消按钮
{
    ui->spinBox_sellcount->clear();
    ui->lineEdit_sellmoney->clear();
}
void Widget::on_pushButton_2_clicked(bool checked)//确定按钮
{
        checked = checked;
        QString deviceName = ui->comboBox_equipment->currentText();//获取设备名
        QString deviceType = ui->comboBox_model->currentText();//获取设备型号
        int selledNum = ui->spinBox_sellcount->text().toInt();//获取销量

        QSqlQuery query;
        query.exec(QString("select sell from type where device='%1' and name='%2'").arg(deviceName).arg(deviceType));
        query.next();
        int sellSum = query.value(0).toInt()+selledNum;//数据库中原来的售出数量加上现在的出售数量
        //数据库事务处理
        QSqlDatabase::database().transaction();
        bool flag = query.exec(QString("update type set sell='%1' where device='%2' and name='%3'").arg(sellSum).arg(deviceName).arg(deviceType));
        if(flag)
        {
            QSqlDatabase::database().commit();
            QMessageBox::information(this,tr("友情提示"),tr("设备信息已更新"),QMessageBox::Ok);
            on_pushButton_clicked(true);
        }
        else
        {
            QSqlDatabase::database().rollback();
        }

}
