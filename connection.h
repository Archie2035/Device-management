#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql>
#include<QDebug>
#include"qdom.h"
static bool creatConnection()
{
    //------------------↓↓↓显示该版本的Qt支持的数据库驱动
    //qDebug() << "Available drivers:";
    //QStringList  drivers = QSqlDatabase::drivers();
    //qDebug() << drivers;
    //---------------------------------------------------------------------------

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("dell");
    db.setDatabaseName("data.db");
    db.setUserName("wangqi");
    db.setPassword("123456");
    if(!db.open())
    {
        return false;//数据库打开失败
    }
    QSqlQuery query;
    //创建设备表          ID| 设备类名
    query.exec("create table device (id varchar primary key,name varchar)");
    query.exec(QString("insert into device values('0','索力')"));
    query.exec(QString("insert into device values('1','倾角')"));
    query.exec(QString("insert into device values('2','振动')"));

    //创建型号表          ID|设备类名|型号|售价|销售量
    query.exec("create table type(id varchar primary key,device varchar,name varchar,price int,selled int)");
    query.exec(QString("insert into type values('0','索力','HCF100',30000,1)"));
    query.exec(QString("insert into type values('1','索力','HCF100-A',20000,2)"));
    query.exec(QString("insert into type values('2','索力','HCF100-B',10000,3)"));
    query.exec(QString("insert into type values('3','索力','HCF100-C',30000,4)"));
    query.exec(QString("insert into type values('4','倾角','HCF200',30400,0)"));
    query.exec(QString("insert into type values('5','倾角','HCF200-A+',31000,1)"));
    query.exec(QString("insert into type values('6','倾角','HCF200-B',50000,3)"));
    query.exec(QString("insert into type values('7','倾角','HCF200-B+',30000,4)"));
    query.exec(QString("insert into type values('8','振动','HCF200-A+',50000,3)"));
    query.exec(QString("insert into type values('9','振动','HCF200',30300,2)"));

    return true;

}


#endif // CONNECTION_H
