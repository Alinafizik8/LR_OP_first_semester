#include <iostream>
#include <fstream>//подключаем для использования классов ofstream и ifstream
using namespace std;

int main()
{
    char ans;//объявление переменной для записи ответа о продолжении использования программы
    cout << "Good time of day" << endl;
    do {
        ofstream fout;//создаем объект fout класса ofstream
        fout.open("start.txt");//создание и открытия файла start.txt для записи
        if (!fout.is_open()) {//обработка случая сбоя открытия файла
            cout << "Error of open file!";
        }
        else {
            char line[1000];
            cout << "Enter your line: ";
            cin.getline(line, 1000,'\n');//чтение 1000 элементов введенной строки или до перехода на следущую строку
            fout << line;//запись строки в файл 
        }
        fout.close();//закрытие файла
        int res = 1000;//переменная для записи длины самого короткого слова в строке
        ifstream fin;//создаем объект fin класса ifstream
        fin.open("start.txt");//открытие файла для чтения данных из него
        if (!fin.is_open()) {//обработка сбоя открытия файла
            cout << "Error of open file!";
        }
        else {
            char elem;//создание переменной для чтения в нее элементов из файла
            int dop = 0;//дополнительная переменная для записи длины каждого слова и сравнения с результатом
            while (fin.get(elem)) {
                if (isalpha(elem)) {
                    dop+= 1;
                }
                else {
                    if (dop != 0) {
                        res = (res <= dop) ? res : dop;
                    }
                    dop = 0;
                }
            }
            if (dop!=0) {//обработка случая одного слова в строке или когда самое короткое слово стоит в конце строки
                res = (res <= dop) ? res : dop;
            }
        }
        fin.close();//закрытие файла
        ofstream foute;
        foute.open("end.txt");//создание файла end для записи и чтения результата
        if (!foute.is_open()) {
            cout << "Error of open file!";
        }
        else {
            foute << "Result: ";
            foute << res;//запись результата в файл end
        }
        foute.close();
        ifstream fine;
        fine.open("end.txt");
        if (!fine.is_open()) {
            cout << "Error of open file!";
        }
        else {
            char piece;
            while (fine.get(piece)) {
                cout << piece;//чтение результата из файла end
            }
        }
        fine.close();
        cout << endl;
        cout << "if you want to continue, enter y or Y, if you want to exit, enter any other element : ";
        cin >> ans;//возможность запустить программу заново по желанию пользователя
        if ((ans == 'y') || (ans == 'Y'))
        {
            cout << endl;//добавление отступа между программами для красоты
            cin.ignore(1000, '\n');
        }
    } while (ans == 'y' || ans == 'Y');//запуск цикла заново, если пользователь захочет продолжить работать с программой
    return 0;//возврат 0 и завершение работы программы в случае отказа пользователя от продолжения
}
