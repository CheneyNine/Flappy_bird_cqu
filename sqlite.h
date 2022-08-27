#ifndef SQLITE_H
#define SQLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>
class Sqlite : public QObject
{
    Q_OBJECT
public:
    explicit Sqlite(QObject *parent = nullptr);

    void CreatDb();

    void CloseDb();
    void CreateTable();
    void InsertData(int id,QString name, int score);
    void UpdateData();
    void QueryAllData();
    int  bestscore();
    int  SearchData_score();
    QSqlDatabase db;
    QSqlQuery sql_query;

signals:
    void return_id_socre();

public slots:
};

#endif // SQLITE_H


