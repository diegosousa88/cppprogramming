#include <iostream>
#include <math.h>
#include <cstdio>
#include <ctime>

using namespace std;

void displayMenu()
{
#ifdef __WIN32
    system("cls");
#else
    system("clear");
#endif
    cout << "Select which prime algorithm to use and press enter:" << endl << endl;
    cout << "Type 1 to check prime using trial division" << endl;
    cout << "Type 2 to use regular algorithm (slower)" << endl;
    cout << "Type 3 to toggle enable timming" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Type 0 to exit application" << endl;
    cout << endl;
    cout << "Type here your choice: ";
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

void toggleEnableTimming(bool &enableTimming)
{
    enableTimming = !enableTimming;
    cout << "Enable timming configuration " << ((enableTimming) ? "enabled" : "disabled") << endl;
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

typedef bool (*isPrimeFunctionPointer)(unsigned long);

void processIsPrime(isPrimeFunctionPointer primeFunction, const bool &enableTimming)
{
    unsigned long number;

    cout << "Type a number and press enter to check if it is not a prime number: ";
    cin >> number;

    bool isPrime = false;

    if (enableTimming)
        isPrime = executeWithTimming<bool, isPrimeFunctionPointer, unsigned long>(primeFunction, number);
    else
        isPrime = primeFunction(number);

    if (isPrime) cout << number << " is a prime number" << endl;
    else cout << number << " is not a prime number" << endl;
}

enum MenuSelection
{
    Exit,
    FastIsPrime,
    SlowIsPrime,
    ToggleEnableTimming,
    InvalidSelection
};

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

        if (selectionAsNumber >= 0 && selectionAsNumber <= 3)
        {
            selection = static_cast<MenuSelection>(selectionAsNumber);

            if (selection != Exit)
            {
                switch (selection) {
                case FastIsPrime:
                    processIsPrime(&isPrimeByTrialDivision, enableTimming);
                    break;
                case SlowIsPrime:
                    processIsPrime(&isPrimeSlower, enableTimming);
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
