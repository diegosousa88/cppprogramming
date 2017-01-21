#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int AccountId READ AccountId WRITE setAccountId NOTIFY AccountIdChanged RESET unsetAccountId)
    Q_PROPERTY(double Balance READ Balance WRITE setBalance NOTIFY BalanceChanged RESET unsetBalance)
public:
    explicit Account(QObject *parent = 0);
    explicit Account(double amount, QObject *parent = 0);
    Account(const Account &obj);
    ~Account();

    int AccountId() const;
    void setAccountId(int AccountId);
    void unsetAccountId();
    void unsetBalance();

    double Balance() const;
    void setBalance(double Balance);

signals:
    void AccountIdChanged();
    void BalanceChanged();
public slots:
    bool withdraw(double amount);
    bool deposit(double amount);
private:
    int m_AccountId;
    double m_Balance;
};
Q_DECLARE_METATYPE(Account)

#endif // ACCOUNT_H
