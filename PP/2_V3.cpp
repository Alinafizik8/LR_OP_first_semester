#include <iostream>
#include <string>
#include <vector>
using namespace std;

//функция возвращающая 1 или 0, в зависимости от типа введенной альфы(int или double), или 2, в случае ошибки(0 или буквы и тд)
int alph(const string& w) {
    int c = 0;//счетчик цифр
    int p = 0;//счеткий точек
    for (int i = 0; i < w.length(); ++i) {
        if (isdigit(w[i])) {
            c += 1;
        }
        else if (w[i] == '.') {
            p += 1;
        }
    }
    if (((c + 1) == w.length()) && (p == 1)) {//проверка на тип double
        if (stod(w)==0) {//проверка на равенство нулю
            return 2;
        }
        else {
            return 0;
        }
    }
    else if (c == w.length()) {//првоерка на тип int
        if (stoi(w)==0) {//проверка на равенство нулю
            return 2;
        }
        else {
            return 1;
        }
    }
    else {//возврат 2, в случае наличия символов, кроме цифр и точки
        return 2;
    }
}

//функция для вычисления n-го члена последовательности
double Anv(double x, int n) {
    double ch = 1;
    for (int i = 0; i < ((4 * n) + 1); ++i) {
        ch *= x;//возведение x в степень 4n+1, вычисление числителя
    }
    double zn = (4 * n) + 1;//вычисление знаменателя
    double An = ch / zn;//вычисление n-го члена последовательности
    return An;//возврат n-го члена последовательности
}
 
int main()
{
    vector<double> st_x;// вектор для хранения предыдущих значений x
    vector<vector<double>> st_Sn;// вектор векторов для хранения предыдущих значений Sn
    vector<vector<double>> st_An;// вектор векторов для хранения предыдущих значений An
    vector<vector<double>> st_an;// вектор векторов для хранения предыдущих значений an
    char ans;//объявление переменной для записи ответа о продолжении использования программы
    cout << "Good time of day" << endl;
    do {
        cout << "Enter x: ";
        double x;
        cin >> x;
        while ((x >= 1) || (x <= (-1))) {//проверка на принадлежность х к допустимому интервалу
            cout << "(-1 < x < 1) Please, enter x again: ";
            cin >> x;
        }
        cout << "Enter a: ";
        string a;//объявление переменной a
        cin >> a;//инициализация переменной а
        while (alph(a) == 2) {//в случае ошибки при вводе а, программа запрашивает повторный его ввод
            cout << "(a > 0) Please, enter a again: ";
            cin >> a;
        }
        int flag = -1;
        for (int i = 0; i < st_x.size();++i) {
            if (st_x[i]==x) {//поиск х в старых значениях
                flag == i;
            }
        }
        cout << endl;
        if (flag == (-1) && x!=0) {//обрабатываем новый х
            st_x.push_back(x);
            st_Sn.push_back(vector<double>());
            st_An.push_back(vector<double>());
            st_an.push_back(vector<double>());
            flag = st_x.size() - 1;
        }
        if (x == 0) {//особый случай
            cout << "An = 0" << "  ";
            cout << "S = 0" << "  ";
            cout << "an = - ";
            cout << endl;
        }
        else if (alph(a)) {//цикл для int a
            int A = stoi(a);
            double Sn = 0;
            double An;
            double an;
            for (int i = 0; i < A;++i) {
                if (i < st_Sn[flag].size()) {//проверка на наличие значений для данного х и n
                    Sn = st_Sn[flag][i];
                    An = st_An[flag][i];        //присвоение уже посчитанных значений
                    an = st_an[flag][i];
                    cout << i + 1 << ")";
                    cout << "An = " << An << "  ";
                    cout << "Sn = " << Sn << "  ";
                    cout << "an = " << an;
                    cout << endl;
                }
                else {//вычисление новых значений и помещение их в векторы
                    An = Anv(x, i);//вычисление n-го элемента
                    st_An[flag].push_back(An);
                    Sn += An;//увеличение итоговой суммы на найденый элемент
                    st_Sn[flag].push_back(Sn);
                    an = Anv(x, i + 1) / Sn;//вычисление точности вычисления
                    st_an[flag].push_back(an);
                    cout << i + 1 << ")";
                    cout << "An = " << An << "  ";
                    cout << "Sn = " << Sn << "  ";
                    cout << "an = " << an;
                    cout << endl;
                }
            }
        }
        else {//цикл для double a
            double A = stod(a);
            double Sn = 0;
            double An;
            double an;
            int t = 0;//счетчик, выступающий в качетсве n
            do {
                if (t < st_Sn[flag].size()) {//проверка на наличие значений для данного х и n
                    Sn = st_Sn[flag][t];
                    An = st_An[flag][t];        //присвоение уже посчитанных значений
                    an = st_an[flag][t];
                    cout << t + 1 << ")";
                    cout << "An = " << An << "  ";
                    cout << "Sn = " << Sn << "  ";
                    cout << "an = " << an;
                    cout << endl;
                }
                else {//вычисление новых значений и помещение их в векторы
                    An = Anv(x, t);//вычисление n-го элемента
                    st_An[flag].push_back(An);
                    Sn += An;//увеличение итоговой суммы на найденый элемент
                    st_Sn[flag].push_back(Sn);
                    an = Anv(x, t + 1) / Sn;//вычисление точности вычисления
                    st_an[flag].push_back(an);
                    cout << t + 1 << ")";
                    cout << "An = " << An << "  ";
                    cout << "Sn = " << Sn << "  ";
                    cout << "an = " << an;
                    cout << endl;
                }
                t += 1;//увеличение счетчика на 1
            } while (abs(an) >= A);//условие для продолжения вычислений(пока модуль нашей точности больше a)
        }
        cout << endl;

        cout << "if you want to continue, enter y ot Y, if you want to exit, enter any other element : ";
        cin >> ans;//возможность запустить программу заново по желанию пользователя
        if ((ans == 'y') || (ans == 'Y')) {
            cout << endl;//добавление отступа между программами для красоты
        }
        if ((ans != 'y') && (ans != 'Y')) {
            st_x.clear();
            st_An.clear();      //освобождение памяти
            st_Sn.clear();
            st_an.clear();
        }
    } while (ans == 'y' || ans == 'Y');//запуск цикла заново, если пользователь захочет продолжить работать с программой
    return 0;//возврат 0 и завершение работы программы в случае отказа пользователя от продолжения
}
