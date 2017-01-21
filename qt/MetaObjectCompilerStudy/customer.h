#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include "account.h"

class Customer : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Author", "Diego de Sousa Oliveira")
    Q_CLASSINFO("Creation date", "2017-01-20")
    Q_CLASSINFO("Description", "This class represents a client from Empowerment Software company")
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(int CustomerId READ CustomerId WRITE setCustomerId NOTIFY CustomerIdChanged RESET unsetCustomerId)
    Q_PROPERTY(QString Name READ Name WRITE setName NOTIFY NameChanged RESET unsetName)
    Q_PROPERTY(CustomerClass Class READ Class WRITE setClass NOTIFY ClassChanged RESET unsetClass)
    Q_PROPERTY(Account Acct READ Acct)

    Q_ENUMS(CustomerClass)
public:
    explicit Customer(QObject *parent = 0);
    explicit Customer(int customerId, QString name, QObject *parent = 0);
    explicit Customer(const Customer& obj);
    ~Customer();

    int CustomerId() const;
    void setCustomerId(int CustomerId);
    void unsetCustomerId();

    enum CustomerClass
    {
        None,
        Platinum,
        Diamond,
        Gold,
        Silver,
        Bronze
    };
    Q_ENUM(CustomerClass)

    CustomerClass Class() const;
    void setClass(const CustomerClass &Class);
    void unsetClass();

    QString Name() const;
    void setName(const QString &Name);
    void unsetName();

    void createAcct(double amount);

    Account *Acct() const;

signals:
    void CustomerIdChanged();
    void NameChanged();
    void ClassChanged();

public slots:
private:
    int m_CustomerId;
    QString m_Name;
    CustomerClass m_Class;
    Account *m_Acct;
};
Q_DECLARE_METATYPE(Customer)

#endif // CUSTOMER_H
