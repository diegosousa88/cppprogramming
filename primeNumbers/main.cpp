#include <iostream>
#include <math.h>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

enum MenuSelection
{
    Exit,
    IsPrimeByTrialDivision,
    IsPrimeRegular,
    ListOfPrimeByEratosthenes,
    ToggleEnableTimming,
    InvalidSelection
};

void displayMenu()
{
#ifdef __WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "Select which prime algorithm to use and press enter:" << endl << endl;
    cout << "Type " << static_cast<int>(IsPrimeByTrialDivision)
         << " to check prime using trial division" << endl;
    cout << "Type " << static_cast<int>(IsPrimeRegular)
         << " to use regular algorithm (slower)" << endl;
    cout << "Type " << static_cast<int>(ListOfPrimeByEratosthenes)
         << " to list prime numbers using Sieve of Eratosthenes" << endl;
    cout << "Type " << static_cast<int>(ToggleEnableTimming)
         << " to toggle enable timming" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Type 0 to exit application" << endl;
    cout << endl;
    cout << "Type here your choice: ";
}

template<typename TRet, typename TFunc, typename TParams>
TRet executeWithTimming(TFunc func, TParams params)
{
    TRet result;
    clock_t startTime;
    double executionDuration;
    startTime = clock();

    result = func(params);

    executionDuration = (clock() - startTime) / (double)CLOCKS_PER_SEC;
    cout << "Function executed in " << executionDuration << " seconds" << endl;

    return result;
}

bool isPrime(unsigned long number)
{
    cout << "Executing " << __FUNCTION__ << endl;
    bool isNotPrime = false;
    for (unsigned long i = 2; i <= number - 1; ++i)
    {
        if (number % i == 0)
            isNotPrime = true;
    }
    return !isNotPrime;
}

bool isPrimeByTrialDivision(unsigned long number)
{
    cout << "Executing " << __FUNCTION__ << endl;
    bool isNotPrime = false;
    for (unsigned long i = 2; i <= sqrt(number); ++i)
    {
        if (number % i == 0)
            isNotPrime = true;
    }
    return !isNotPrime;
}

vector<unsigned long> generatePrimeNumbersBySieveEratosthenes(unsigned long maxNumber)
{
    cout << "Executing " << __FUNCTION__ << endl;

    vector<unsigned long> primeNumbers;
    for (unsigned int i = 0; i < maxNumber; ++i)
        primeNumbers.push_back(1);

    primeNumbers[0] = 0;
    primeNumbers[1] = 0;

    for (unsigned long i = 2; i <= maxNumber; ++i)
    {
        if (primeNumbers[i] == 1)
        {
            for (unsigned long j = 2; i * j <= maxNumber; ++j)
                primeNumbers[i * j] = 0;
        }
    }

    return primeNumbers;
}

void displayList(vector<unsigned long> list, string message, string separator = " | ")
{
    cout << message << endl;

    bool addSeparator = false;
    for (unsigned long i = 0; i < list.size(); ++i)
    {
        if (list.at(i) == 0)
            continue;

        if (addSeparator)
            cout << separator;

        cout << i;

        addSeparator = true;
    }
    cout << endl;
}

typedef vector<unsigned long> (* generatePrimeNumbers)(unsigned long);

void processListPrimeNumbers(const bool &enableTimming)
{
    vector<unsigned long> primeNumbers;
    unsigned long maxNumber;

    cout << "List prime numbers until number: ";
    cin >> maxNumber;

    if (maxNumber <= 1)
    {
        cout << "The number must be greater than 1." << endl;
        return ;
    }

    if (enableTimming)
        primeNumbers = executeWithTimming<vector<unsigned long>, generatePrimeNumbers, unsigned long>(&generatePrimeNumbersBySieveEratosthenes, maxNumber);
    else
        primeNumbers = generatePrimeNumbersBySieveEratosthenes(maxNumber);

    displayList(primeNumbers, "Listing prime numbers...");
}

typedef bool (*isPrimeFunctionPointer)(unsigned long);

void processIsPrime(isPrimeFunctionPointer primeFunction, const bool &enableTimming)
{
    unsigned long number;

    cout << "Type a number greater than 1 and press enter to check if it is not a prime number: ";
    cin >> number;

    if (number <= 1)
    {
        cout << "The number must be greater than 1." << endl;
        return;
    }

    bool isPrime = false;

    if (enableTimming)
        isPrime = executeWithTimming<bool, isPrimeFunctionPointer, unsigned long>(primeFunction, number);
    else
        isPrime = primeFunction(number);

    if (isPrime) cout << number << " is a prime number" << endl;
    else cout << number << " is not a prime number" << endl;
}

void toggleEnableTimming(bool &enableTimming)
{
    enableTimming = !enableTimming;
    cout << "Enable timming configuration " << ((enableTimming) ? "enabled" : "disabled") << endl;
}

int main()
{
    int selectionAsNumber = 0;
    MenuSelection selection = Exit;
    bool enableTimming = true;

#ifdef __WIN32
    system("color 17");
#else
    system("setterm -term linux -back blue -fore white -clear");
#endif

    do
    {
        displayMenu();
        cin >> selectionAsNumber;

        if (selectionAsNumber >= 0 && selectionAsNumber <= 4)
        {
            selection = static_cast<MenuSelection>(selectionAsNumber);

            if (selection != Exit)
            {
                switch (selection) {
                case IsPrimeByTrialDivision:
                    processIsPrime(&isPrimeByTrialDivision, enableTimming);
                    break;
                case IsPrimeRegular:
                    processIsPrime(&isPrime, enableTimming);
                    break;
                case ListOfPrimeByEratosthenes:
                    processListPrimeNumbers(enableTimming);
                    break;
                case ToggleEnableTimming:
                    toggleEnableTimming(enableTimming);
                    break;
                case Exit:
                case InvalidSelection:
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid selection. Select again." << endl;
            selection = InvalidSelection;
        }

        if (selection != Exit)
        {
            cout << "Press <enter> to continue";
            fflush(stdin);
            getchar();
        }
    } while (selection != Exit);

    return 0;
}
