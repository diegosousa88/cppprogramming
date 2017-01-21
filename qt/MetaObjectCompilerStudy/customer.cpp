#include "customer.h"

Customer::Customer(QObject *parent)
    : Customer(0, "", parent) { }

Customer::Customer(int customerId, QString name, QObject *parent)
    : QObject(parent)
  , m_CustomerId(customerId)
  , m_Name(name)
  , m_Class(None)
  , m_Acct(nullptr) { }

Customer::Customer(const Customer &other)
    : Customer()
{
    m_CustomerId = other.CustomerId();
    m_Name = other.Name();
    m_Class = other.Class();
    m_Acct = other.Acct();
}

Customer::~Customer()
{
    if (m_Acct != nullptr)
    {
        delete m_Acct;
        m_Acct = nullptr;
    }
}

int Customer::CustomerId() const
{
    return m_CustomerId;
}

void Customer::setCustomerId(int CustomerId)
{
    if (m_CustomerId != CustomerId)
        emit CustomerIdChanged();

    m_CustomerId = CustomerId;
}


void Customer::unsetCustomerId()
{
    setCustomerId(0);
}

Customer::CustomerClass Customer::Class() const
{
    return m_Class;
}

void Customer::setClass(const CustomerClass &Class)
{
    if (m_Class != Class)
        emit ClassChanged();

    m_Class = Class;
}

void Customer::unsetClass()
{
    m_Class = None;
}

QString Customer::Name() const
{
    return m_Name;
}

void Customer::setName(const QString &Name)
{
    if (m_Name != Name)
        emit NameChanged();

    m_Name = Name;
}

void Customer::unsetName()
{
    setName("");
}

void Customer::createAcct(double amount)
{
    m_Acct = new Account(amount);
}

Account *Customer::Acct() const
{
    return m_Acct;
}

