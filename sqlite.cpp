#include "sqlite.h"
#include <QDebug>
Sqlite::Sqlite(QObject *parent) : QObject(parent)
{
   CreatDb();
}

void Sqlite::CreatDb()
{
        db = QSqlDatabase::addDatabase("QSQLITE");//创建一个SQLite数据库连接
        db.setDatabaseName("flappybird_player.db");
//        db.setUserName("test");
//        db.setPassword("test");
        if(!db.open())
        {
            qDebug() << "错误: 连接数据库失败！" << db.lastError() << "\n";
        }
        else {
             qDebug() << "成功连接数据库！\n" ;
        }

}

void Sqlite::CloseDb()
{
    db.close();
}
void Sqlite::CreateTable()//创建数据表
{
    //QSqlQuery sql_query;//sql_query为数据库表
//    QSqlQuery sql_query=QSqlQuery(db);
//    if(!sql_query.exec("create table player(id int primary key, name varchar, age int)")) {
//            qDebug() << "错误：不能创建表"<< sql_query.lastError()<< "\n";
//        } else {
//            qDebug() << "创建表成功！\n";
//        }

}
void Sqlite::InsertData(int id, QString name, int score)
{
    QSqlQuery sql_query=QSqlQuery(db);
    if(!sql_query.exec("create table player( name BLOB,time int, score int)")) {
            qDebug() << "错误：不能创建表"<< sql_query.lastError()<< "\n";
        } else {
            qDebug() << "创建表成功！\n";
        }
    QString insert_sql = "insert into player values (?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(name);
    sql_query.addBindValue(id);
    sql_query.addBindValue(score);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError()<<endl;
    }
    else
    {
        qDebug() << "inserted Wang!"<<endl;
    }
}
void Sqlite::QueryAllData()
{
    QString select_all_sql = "select * from player";
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            int score = sql_query.value(2).toInt();
            qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(score);
        }
    }
}

int Sqlite::bestscore()
{
    QString select_all_sql = "select * from player";
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    int max=0;
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString name = sql_query.value(1).toString();
            int score = sql_query.value(2).toInt();
            if(score>max)max=score;
        }
    }
    return max;
}


