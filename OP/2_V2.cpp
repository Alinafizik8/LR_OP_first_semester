#include <iostream>//подключаем для работы с потоками ввода и вывода
#include <string>
using namespace std;//указываем компилятору импортировать все имена из пространства имен std в текущую область видимости


//функция для проверяем на корректность ввода типа переменной
double check() {
    double t;//объявление переменной
    cin >> t;//инициализация переменной
    if ((!cin) || (cin.peek()!='\n'))//проверка на ошибку ввода
    {
        cout << "Inpur erorr! Please, enter again: ";//сообщение об ошибке
        cin.clear();//сброс битов ошибки
        cin.ignore(10000, '\n');//пропуск 10000 веденных символом, чтобы они не мешали в дальнейшем выполнении программы
        return check();//запуск функции заново
    }
    return t;//возврат введенной переменной, в случае отсутствия ошибок ввода
}

//функция возвращающая 1 или 0, в зависимости от типа введенной альфы(int или double), или 2,
int alph(const string& w) {
    int c = 0;//счетчик цифр
    int p = 0;//счеткий точек
    int cn = 0;//счетчик нулей
    for (int i = 0; i < w.length(); ++i) {
        if (isdigit(w[i])) {
            c += 1;
        }
        if (w[i]=='.') {
            p += 1;
        }
        if (w[i] == '0') {
            cn += 1;
        }
    }
    if (((c + 1) == w.length()) && (p==1)) {//проверка на тип double
        if ((cn+1)==w.length()) {//проверка на равенство нулю
            return 2;
        }
        else {
            return 0;
        }
    }
    else if (c == w.length()) {//првоерка на тип int
        if (cn == w.length()) {//проверка на равенство нулю
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
    for (int i = 0; i < (2 * n + 1); ++i) {
        ch *= x;//возведение x в степень 2n+1, вычисление числителя
    }
    double zn = (2 * n) + 1;//вычисление знаменателя
    double An = ch / zn;//вычисление n-го члена последовательности
    return An;//возврат n-го члена последовательности
}

int main()
{
    char ans;//объявление переменной для записи ответа о продолжении использования программы
    cout << "Good time of day" << endl;
    do {
        cout << "Enter x: ";
        double x = check();//инициализация переменной x
        while ((x >= 1) || (x <= (-1))) {//проверка на принадлежность х к допустимому интервалу
            cout << "(-1 < x < 1) Please, enter x again: ";
            x = check();
            cin.ignore(10000, '\n');
        }
        cout << "Enter a: ";
        string a;//объявление переменной a
        cin >> a;//инициализация переменной а
        while (alph(a)==2) {//в случае ошибки при вводе а, программа запрашивает повторный его ввод
            cout << "Parameter a can only be positive. Please,enter a again: ";
            cin >> a;
        }
        cout << endl;
        if (x == 0) {//особый случай
            cout << "An = 0" << "  ";
            cout << "S = 0" << "  ";
            cout << "an = - ";
            cout << endl;
        }
        else if (alph(a)) {//цикл для int a
            int A = stoi(a);
            double S = 0;
            for (int i = 0; i < A; ++i) {
                double An = Anv(x, i);//вычисление n-го элемента
                S += An;//увеличение итоговой суммы на найденый элемент
                double an = Anv(x, i + 1) / S;//вычисление точности вычисления
                cout << i + 1 << ")";
                cout << "An = " << An << "  ";
                cout << "S = " << S << "  ";
                cout << "an = " << an;
                cout << endl;
            }
        }
        else {//цикл для double a
            double A = stod(a);
            double S = 0;
            double an;
            int t = 0;//счетчик, выступающий в качетсве n
            do {
                double An = Anv(x, t);//вычисление n-го элемента
                S += An;//увеличение итоговой суммы на найденый элемент
                an = Anv(x, t + 1) / S;//вычисление точности вычисления
                cout << t + 1 << ")";
                cout << "An = " << An << "  ";
                cout << "S = " << S << "  ";
                cout << "an = " << an;
                cout << endl;
                t += 1;//увеличение счетчика на 1
            } while (abs(an) >= A);//условие для продолжения вычислений(пока модуль нашей точности больше a)
        }
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