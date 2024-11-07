#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

vector<int> merge(vector<int> l, vector<int> r);//прототипирование функции

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

void vstavki(vector<int>& s) {
    int n = s.size();
    for (int i = 1; i < n; i++) {
        int key = s[i];
        int j = i - 1;
        while (j >= 0 && s[j] > key) {
            s[j + 1] = s[j];
            j--;
        }
        s[j+1] = key;
    }
}//функция сортирует массив вставками

vector<int> slianie(vector<int> s) {
    int n = s.size();
    if (n <= 1) {
        return s;
    }
    else {
        int mid = n / 2;
        vector<int> dm;
        vector<int> pm;
        for (int i = 0; i < mid; ++i) {
            dm.push_back(s[i]);
        }
        for (int i = mid; i < n; ++i) {
            pm.push_back(s[i]);
        }
        auto left = slianie(dm);
        auto right = slianie(pm);
        return merge(left, right);
    }
}//фукнция, делящая вектор пополам, пока не останется два единичных вектора

vector<int> merge(vector<int> l, vector<int> r) {
    int L = l.size();
    int R = r.size();
    vector<int> res;
    int tl = 0;
    int tr = 0;
    while (L > 0 && R > 0) {
        if (l[tl] <= r[tr]) {
            res.push_back(l[tl]);
            L -= 1;
            tl += 1;
        }
        else {
            res.push_back(r[tr]);
            R -= 1;
            tr += 1;
        }
    }
    if (L > 0) {
        for (int i = tl; i < l.size(); ++i) {
            res.push_back(l[i]);
        }
    }
    if (R > 0) {
        for (int i = tr; i < r.size(); ++i) {
            res.push_back(r[i]);
        }
    }
    return res;
}//функция сортирующая элементы из двух векторов в результирующий

int main()
{
    char ans;//объявление переменной для записи ответа о продолжении использования программы
    cout << "Good time of day" << endl;
    srand(time(NULL));//для действительно случайных значений при запуске программы с одинаковой длинной массива
    do {
        cout << "Enter the length of the array: ";
        int x = check();
        while (x <= 0) {//Проверка х на адекватность
            cout << "Length should be positive! Please, enter again: ";
            x = check();
        }
        cout << "How would you like to fill the array?" << endl << "(1 - manually, 2 - strictly random values, 3 - almost sorted random values): ";
        int zap = check();
        while (zap < 1 || zap > 3) {//проверка zap на соответствие параметрам 
            cout << "Please< enter 1, 2 or 3" << endl << "(1 - manually, 2 - strictly random values, 3 - almost sorted random values): ";
            zap = check();
        }
        vector<int> s;//создание основного вектора
        vector<int> s_vs;//создание вектора для сортировки вставками
        vector<int> s_sl;//создание вектора для сортировки слиянием
        if (zap == 1) {
            for (int i = 0; i < x; ++i) {//цикл для заполнения вектора вручную пользователем
                cout << "Enter the " << i+1 << " element of array: ";
                int el = check();
                s.push_back(el);
            }
        }
        else if (zap == 2) {
            for (int i = 0; i < x; ++i) {//цикл для заполнения вектора случайными значениями до 50
                s.push_back(abs(rand() % (x+1)));
            }
        }
        else {
            for (int i = 0; i < x; ++i) {//цикл для заполнения вектора почти отсортированными случайными значениями до 50
                s.push_back(abs(rand() % (x+1)));
            }
            sort(s.begin(), s.end());
            for (int i = 0; i < (x / 5); ++i) {
                int o = abs(rand() % x);
                int d = abs(rand() % x);
                if (s[o] != s[d]) {
                    swap(s[o], s[d]);
                }
            }
        }
        s_vs = s;
        s_sl = s;
        chrono::duration<double> time_vstavki;
        chrono::duration<double> time_slianie;
        chrono::duration<double> time_sort;
        if (x > 50) {//вывод для слишком большого массива
            const int vivod = 10;
            cout << endl;
            cout << "I think that it is too much..." << endl;
            cout << "Before: " << endl;
            for (int i = 0; i < vivod; ++i) {//цикл вывода первых 10 значений вектора до сортировки
                cout << s[i] << " ";
            }
            cout << ".......";
            for (int i = x - vivod; i <= x - 1; ++i) {//цикл вывода последних 10 значений вектора до сортировки
                cout << s[i] << " ";
            }
            cout << endl;
            cout << endl;

            auto start_vs = chrono::high_resolution_clock::now();//начало отсчета времени
            vstavki(s_vs);//сортировка массива
            auto end_vs = chrono::high_resolution_clock::now();//конец отсчета времени
            time_vstavki = end_vs - start_vs;//время выполнения сортировки

            auto start_sl = chrono::high_resolution_clock::now();
            s_sl = slianie(s_sl);
            auto end_sl = chrono::high_resolution_clock::now();
            time_slianie = end_sl - start_sl;

            auto start = chrono::high_resolution_clock::now();
            sort(s.begin(), s.end());
            auto end = chrono::high_resolution_clock::now();
            time_sort = end - start;

            cout << "After sorting by inserts: " << endl;
            for (int i = 0; i < vivod; ++i) {//цикл вывода первых 10 значений вектора после сортировки вставками
                cout << s_vs[i] << " ";
            }
            cout << ".......";
            for (int i = x - vivod; i <= x - 1; ++i) {//цикл вывода последних 10 значений вектора после сортировки вставками
                cout << s_vs[i] << " ";
            }
            cout << endl;
            cout << endl;
            cout << "After the merge sort: " << endl;
            for (int i = 0; i < vivod; ++i) {//цикл вывода первых 10 значений вектора после сортировки слиянием
                cout << s_sl[i] << " ";
            }
            cout << ".......";
            for (int i = x - vivod; i <= x - 1; ++i) {//цикл вывода последних 10 значений вектора после сортировки слиянием
                cout << s_sl[i] << " ";
            }
            cout << endl;
            cout << endl;
            cout << "After library sorting: " << endl;
            for (int i = 0; i < vivod; ++i) {//цикл вывода первых 10 значений вектора после библиотечной сортировки
                cout << s[i] << " ";
            }
            cout << ".......";
            for (int i = x - vivod; i <= x - 1; ++i) {//цикл вывода последних 10 значений вектора после библиотечной сортировки
                cout << s[i] << " ";
            }
        }
        else {//вывод для массива адекватного размера
            cout << endl;
            cout << "Before: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода вектора до сортировки
                cout << s[i] << " ";
            }
            cout << endl;
            cout << endl;

            auto start_vs = chrono::high_resolution_clock::now();
            vstavki(s_vs);//сортировка массива
            auto end_vs = chrono::high_resolution_clock::now();
            time_vstavki = end_vs - start_vs;

            auto start_sl = chrono::high_resolution_clock::now();
            s_sl = slianie(s_sl);
            auto end_sl = chrono::high_resolution_clock::now();
            time_slianie = end_sl - start_sl;

            auto start = chrono::high_resolution_clock::now();
            sort(s.begin(), s.end());
            auto end = chrono::high_resolution_clock::now();
            time_sort = end - start;

            cout << "After sorting by inserts: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода первых 10 значений вектора после сортировки вставками
                cout << s_vs[i] << " ";
            }
            cout << endl;
            cout << endl;
            cout << "After the merge sort: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода первых 10 значений вектора после сортировки слиянием
                cout << s_sl[i] << " ";
            }
            cout << endl;
            cout << endl;
            cout << "After library sorting: " << endl;
            for (int i = 0; i < x; ++i) {//цикл вывода первых 10 значений вектора после библиотечной сортировки
                cout << s[i] << " ";
            }
        }
        double usk_vs = 0;
        double usk_sl = 0;
        if (time_vstavki.count() != 0 && time_sort.count() != 0) {
            usk_vs = time_vstavki.count() / time_sort.count();//вычисление ускорения библиотечной сортировки по сравнению с сортировкой вставками
        }
        if (time_slianie.count() != 0 && time_sort.count() != 0) {
            usk_sl = time_slianie.count() / time_sort.count();//вычисление ускорения библиотечной сортировки по сравнению с сортировкой слиянием
        }
        cout << endl;
        cout << endl;
        cout << "Time to perform insertion sorting: "<< time_vstavki.count() <<" sec"<<endl;
        cout << "Acceleration of library sorting compared to insertion sorting: " << usk_vs << endl;
        cout << endl;
        cout << "Merge sorting execution time: " << time_slianie.count() << " sec" << endl;
        cout << "Acceleration of library sorting compared to merge sorting: " << usk_sl << endl;
        cout << endl;
        cout << "Library sorting execution time: " << time_sort.count() << " sec" << endl;
        cout << endl;
        s.clear();
        s_vs.clear();        //освобождение памяти
        s_sl.clear();
        cout << endl;
        cout << "if you want to continue, enter y or Y, if you want to exit, enter any other element : ";
        cin >> ans;//возможность запустить программу заново по желанию пользователя
        if ((ans == 'y') || (ans == 'Y'))
        {
            cout << endl;//добавление отступа между программами для красоты
        }
    } while (ans == 'y' || ans == 'Y');//запуск цикла заново, если пользователь захочет продолжить работать с программой
    return 0;//возврат 0 и завершение работы программы в случае отказа пользователя от продолжения
}
