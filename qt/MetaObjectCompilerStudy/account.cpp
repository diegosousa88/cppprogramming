#include "account.h"

Account::Account(QObject *parent) : Account(0, parent) { }

Account::Account(double amount, QObject *parent) : QObject(parent)
  , m_AccountId(0)
  , m_Balance(amount) { }

Account::Account(const Account &obj) { }

Account::~Account() { }

int Account::AccountId() const
{
    return m_AccountId;
}

void Account::setAccountId(int AccountId)
{
    m_AccountId = AccountId;
    emit AccountIdChanged();
}

void Account::unsetAccountId()
{
    setAccountId(0);
}

double Account::Balance() const
{
    return m_Balance;
}

void Account::setBalance(double Balance)
{
    m_Balance = Balance;
    emit BalanceChanged();
}

bool Account::withdraw(double amount)
{
    if (m_Balance - amount < 0)
        return false;

    setBalance(m_Balance - amount);
    return true;
}

bool Account::deposit(double amount)
{
    if (amount < 1)
        return false;

    setBalance(m_Balance + amount);
    return true;
}

void Account::unsetBalance()
{
    setBalance(0);
}
