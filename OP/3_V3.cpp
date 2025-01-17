#include <iostream>
#include <vector>
using namespace std;

int check() {
    int t;//объявление переменной
    cin >> t;//инициализация переменной
    if ((!cin) || (cin.peek() != '\n'))//проверка на ошибку ввода
    {
        cout << "Inpur erorr! Please, enter again: ";//сообщение об ошибке
        cin.clear();//сброс битов ошибки
        cin.ignore(10000, '\n');//пропуск 10000 веденных символом, чтобы они не мешали в дальнейшем выполнении программы
        return check();//запуск функции заново
    }
    return t;//возврат введенной переменной, в случае отсутствия ошибок ввода
} //функция для проверяем на корректность ввода типа переменной

vector<int> sortirovka(vector<int>& s) {
    int n = s.size();
    for (int c = 0; c < n - 1; ++c) {//цикл бегущий по несортированным значениям
        for (int i = n - 2; i >= c; --i) {//цикл бегущий по парам значений
            if (s[i] > s[i + 1]) {//сравнение пар значений
                int a = s[i + 1];
                s[i + 1] = s[i];
                s[i] = a;
            }
        }
    }
} //функция возвращает отсортированный пузырьком массив

int main()
{
    char ans;//объявление переменной для записи ответа о продолжении использования программы
    cout << "Good time of day" << endl;
    srand(time(NULL));
    do {
        cout << "Enter the length of the array: ";
        int x = check();
        while (x<=0) {//Проверка х на адекватность
            cout << "Length should be positive! Please, enter again: ";
            x = check();
        }
        vector<int> s;//создание вектора
        for (int i = 0; i < x;++i) {//цикл для заполнения вектора случайными значениями до 50
            s.push_back(abs(rand()%51));
        }
        if (x>50) {//вывод для слишком большого массива
            cout << "I think that it is too much..." << endl;
            cout << "Before: " << endl;
            for (int i = 0; i < 10; ++i) {//цикл вывода первых 10 значений вектора до сортировки
                cout << s[i] << " ";
            }
            cout << ".......";
            for (int i = x - 10; i <= x-1; ++i) {//цикл вывода последних 10 значений вектора до сортировки
                cout << s[i] << " ";
            }
            cout << endl;
            s = sortirovka(s);//сортировка массива
            cout << "After: " << endl;
            for (int i = 0; i < 10; ++i) {//цикл вывода первых 10 значений вектора после сортировки
                cout << s[i] << " ";
            }
            cout << ".......";
            for (int i = x-10; i <= x-1; ++i) {//цикл вывода последних 10 значений вектора после сортировки
                cout << s[i] << " ";
            }
        }
        else {//вывод для массива адекватного размера
            cout << "Before: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода значений вектора до сортировки
                cout << s[i] << " ";
            }
            cout << endl;
            s = sortirovka(s);//сортировка массива
            cout << "After: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода значений вектора после сортировки
                cout << s[i] << " ";
            }
        }
        s.clear();//освобождение памяти
        cout << endl;
        cout << "if you want to continue, enter y, if you want to exit, enter any other element : ";
        cin >> ans;//возможность запустить программу заново по желанию пользователя
        if ((ans == 'y') || (ans == 'Y'))
        {
            cout << endl;//добавление отступа между программами для красоты
        }
    } while (ans == 'y' || ans == 'Y');//запуск цикла заново, если пользователь захочет продолжить работать с программой
    return 0;//возврат 0 и завершение работы программы в случае отказа пользователя от продолжения
}
