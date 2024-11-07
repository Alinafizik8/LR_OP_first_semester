#include <iostream>
#include <vector>
using namespace std;

//функция для проверяем на корректность ввода типа переменной
double check() {
    double t;//объявление переменной
    cin >> t;//инициализация переменной
    if ((cin.fail()) || (cin.peek() != '\n'))//проверка на ошибку ввода
    {
        cout << "Inpur erorr! Please, enter again: ";//сообщение об ошибке
        cin.clear();//сброс битов ошибки
        cin.ignore(10000, '\n');//пропуск 10000 веденных символом, чтобы они не мешали в дальнейшем выполнении программы
        return check();//запуск функции заново
    }
    return t;//возврат введенной переменной, в случае отсутствия ошибок ввода
}

int main()
{
    char ans;
    cout << "Computing square root" << endl;
    do {
        cout << "Enter nonnegative decimal: ";
        double x = check();
        while (x < 0) {
            cout << "I said nonnegative decimal, enter again: ";
            x = check();
        }
        cout << "Enter an upper bound absolute error: ";
        double a = check();
        while (a <= 0) {
            cout << "It should be positive! Enter again: ";
            a = check();
        }
        vector<double> values;
        if (x==0) {
            cout << "Element # 1" << endl;
            cout << "Result: 0" << endl;
            cout << "Absolute error: 0" << endl;
        }
        else {
            values.push_back(x);
            int i = 1;
            do {
                values.push_back((values[i - 1] + (x / values[i - 1])) / 2);
                ++i;
            } while (abs((sqrt(x) - values[values.size() - 1])) > a);
            cout << "Element # " << values.size() << endl;
            cout << "Result: " << values[values.size() - 1] << endl;
            cout << "Absolute error: " << abs(sqrt(x) - values[values.size() - 1]) << endl;
        }
        values.clear();
        cout << endl;
        cout << "if you want to continue, enter y or Y, if you want to exit, enter any other element : ";
        cin >> ans;
        if ((ans == 'y') || (ans == 'Y'))
        {
            cout << endl;
        }
    } while (ans == 'y' || ans == 'Y');
    return 0;
}
