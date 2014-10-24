#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include<QDebug>
namespace Ui {
class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QMenu *manegeMenu;//出售设备管理主菜单
    QMenu *passwordMenu;//修改密码菜单
    QAction *manageAction;
    QAction *chartAction;
    QAction *quitAction;//退出

private:
    Ui::Widget *ui;
    void creatMenuBar();
private slots:
    void on_manegeMenu_clicked();
    void on_chartAction_clicked();
    void on_quitAction_clicked();
    void on_comboBox_equipment_currentIndexChanged(const QString &arg1);
    void on_comboBox_model_currentIndexChanged(const QString &arg1);
    void on_spinBox_sellcount_valueChanged(int arg1);
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked(bool checked);
};

#endif // WIDGET_H
