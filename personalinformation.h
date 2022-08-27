#ifndef PERSONALINFORMATION_H
#define PERSONALINFORMATION_H

#include <QObject>

class personalinformation : public QObject
{
    Q_OBJECT
public:
    explicit personalinformation(QObject *parent = nullptr);


private:
    int money;

signals:

public slots:
};

#endif // PERSONALINFORMATION_H
