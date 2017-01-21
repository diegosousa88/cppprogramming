#include <QCoreApplication>
#include "customer.h"
#include <QDebug>
#include <QMetaMethod>

using namespace std;

void displayObjectData(const Customer *cust)
{
    qDebug() << "Customer ID: " << cust->CustomerId() << endl
             << "Name: " << cust->Name() << endl
             << "Class: " << QMetaEnum::fromType<Customer::CustomerClass>().valueToKey(cust->Class()) << endl
             << "Balance: " << cust->Acct()->Balance() << endl;
}

void displayClassMetadata(const Customer *cust)
{
    qDebug() << "### Class metadata ###" << endl;
    qDebug() << "Class name: " << cust->metaObject()->className();
    qDebug() << "Class infos (" << cust->metaObject()->classInfoCount() << ")";
    for (int i = 0; i < cust->metaObject()->classInfoCount(); ++i)
    {
        qDebug() << "Info key: " << cust->metaObject()->classInfo(i).name()
                 << " -> Info value: " << cust->metaObject()->classInfo(i).value();
    }

    qDebug() << "Properties (" << cust->metaObject()->propertyCount() << ")" << endl;
    for (int i = 0; i < cust->metaObject()->propertyCount(); ++i)
    {
        qDebug() << "Name: " << cust->metaObject()->property(i).name() << endl
                 << "Has notify signal: " << cust->metaObject()->property(i).hasNotifySignal() << endl
                 << "Is constant: " << cust->metaObject()->property(i).isConstant() << endl
                 << "Is designable: " << cust->metaObject()->property(i).isDesignable() << endl
                 << "Is editable: " << cust->metaObject()->property(i).isEditable() << endl
                 << "Is enum type: " << cust->metaObject()->property(i).isEnumType() << endl
                 << "Is final: " << cust->metaObject()->property(i).isFinal() << endl
                 << "Is flag type: " << cust->metaObject()->property(i).isFlagType() << endl
                 << "Is readable: " << cust->metaObject()->property(i).isReadable() << endl
                 << "Is resetable: " << cust->metaObject()->property(i).isResettable() << endl
                 << "Is scriptable: " << cust->metaObject()->property(i).isScriptable() << endl
                 << "Is stored: " << cust->metaObject()->property(i).isStored() << endl
                 << "Is user: " << cust->metaObject()->property(i).isUser() << endl
                 << "Is valid: " << cust->metaObject()->property(i).isValid() << endl
                 << "Is writable: " << cust->metaObject()->property(i).isWritable() << endl
                 << "Notify signal method name: " << cust->metaObject()->property(i).notifySignal().name()
                    << "[" << cust->metaObject()->property(i).notifySignalIndex() << "]" << endl
                 << "Read: " << cust->metaObject()->property(i).read(cust).value<double>() << endl
                 << "Type name: " << cust->metaObject()->property(i).typeName() << endl
                 << "User type: " << cust->metaObject()->property(i).userType() << endl;


        // The creation of WRITE Q_PROPERTY allow me to assign a class property's value via metadata.
//        if (!strcmp(cust->metaObject()->property(i).name(), "objectName"))
//            continue;
//        if (!strcmp(cust->metaObject()->property(i).typeName(), "QString"))
//            cust->metaObject()->property(i).write(cust, "Updated via metadata");
//        else if (!strcmp(cust->metaObject()->property(i).typeName(), "CustomerClass"))
//            cust->metaObject()->property(i).write(cust, Customer::Bronze);
//        else if (!strcmp(cust->metaObject()->property(i).typeName(), "int"))
//            cust->metaObject()->property(i).write(cust, 1);

        // As well as the creation of RESET Q_PROPERTY allows me to reset class property's value via metadata.
//        cust->metaObject()->property(i).reset(cust);
    }
}

// TODO: Does not work yet! Suspecting issue with Q_RETURN_ARG and Q_ARG macros
template<typename TRet, typename TObj, typename TArg>
TRet callMethodViaMetadata(TObj *obj, const char *methodSignature, TArg arg)
{
    TRet methodResult;

    QByteArray methodSignNorm = QMetaObject::normalizedSignature(methodSignature);
    int methodIdx = obj->metaObject()->indexOfMethod(methodSignNorm);
    QMetaMethod method = obj->metaObject()->method(methodIdx);
    bool success = method.invoke(obj, Qt::DirectConnection, Q_RETURN_ARG(TRet, methodResult), Q_ARG(TArg, arg));
    // Force an exception here to not return an inconsistent result.
    if (!success) throw;

    return methodResult;
}

bool callMethodFromAccountViaMetadata(Account *acct, const char *methodSignature, double amount)
{
    bool methodResult;

    QByteArray methodSignNorm = QMetaObject::normalizedSignature(methodSignature);
    int methodIdx = acct->metaObject()->indexOfMethod(methodSignNorm);
    QMetaMethod method = acct->metaObject()->method(methodIdx);
    if (method.invoke(acct, Qt::DirectConnection, Q_RETURN_ARG(bool, methodResult), Q_ARG(double, amount)))
        return methodResult;
    else
        return false;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Customer *cust = new Customer(15, "Diego de Sousa Oliveira", &a);
    cust->createAcct(2000);
    cust->setClass(Customer::Gold);

    qDebug() << "### Object created ###" << endl;
    displayObjectData(cust);
    displayClassMetadata(cust);

    // Calling withdraw method via metadata.
//    bool withdrawResult = callMethodViaMetadata<bool, Account, double>(cust->Acct(), "withdraw(double)", 1000.5);
    bool withdrawResult = callMethodFromAccountViaMetadata(cust->Acct(), "withdraw(double)", 1000.5);

    qDebug() << "Withdraw succeeds: " << withdrawResult << endl;
    displayObjectData(cust);

    // Changing the Customer's Class property from a generic QObject
    QObject *obj = cust;
    obj->setProperty("Class", "Platinum");

    qDebug() << "New class property changed through a generic QObject: "
             << QMetaEnum::fromType<Customer::CustomerClass>().valueToKey(cust->Class());

    // Creating a dynamic property in object on the fly (creates if does not find a key. E.g.: NewDynamicProperty)
    obj->setProperty("NewDynamicProperty", "Value of new dynamic property created on the fly");
    qDebug() << "New property value created on the fly: " << obj->property("NewDynamicProperty").value<QString>();

    // Deposit more money normally
    cust->Acct()->deposit(1000);

    return a.exec();
}
