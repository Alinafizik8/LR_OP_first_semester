#include <iostream> //для работы с потоками ввода и вывода
#include <fstream> //для работы с файлами
#include <string> //для работы с типом string
#include <vector> //для работы с vector
#include <iomanip> //для работы с форматированием ввода
using namespace std; //для использования идентификаторов из пространства имен

int checkNum(string line) {
    int resultNum = 0;
    if (!line.empty() && line[0] != '\n' && line.size() <= 10) {
        int checking = 0;
        for (int i = 0; i < size(line); ++i) {
            if (isdigit(line[i])) {
                checking += 1;
            }
        }
        if (checking == size(line)) {
            resultNum = stoi(line);
        }
    }
    return resultNum;
}

int check() {
    string line;
    getline(cin, line);
    int number = checkNum(line);
    if (!number) {
        cout << "Error! Enter again: ";
        return check();
    }
    return number;
}

class Speed {//создание класса
public://доступно для всех мест программы
    int nomber;
    double sped;               //объявление полей класса
    string unit_measure;

    //конструкторы
    Speed() : nomber(0), sped(0.0), unit_measure("") {};

    Speed(int b, double a, string c) {
        sped = a;
        nomber = b;
        unit_measure = c;
    }

    Speed(string a) {
        if (empty(a)) {
            nomber = 0;
            sped = 0;
            unit_measure = "Error";
        }
        else {
            nomber = 0;
            sped = 0;
            unit_measure = "Error";
        }
    }

    Speed(const Speed& c) {//конструктор копирования
        sped = c.sped;
        nomber = c.nomber;
        unit_measure = c.unit_measure;
    }

    ~Speed() { unit_measure.clear(); };//деструктор

    double SpedChanger() const {
        if (unit_measure == "km/h") {
            return sped / 3.6;
        }
        else {
            return sped * 3.6;
        }
    }

    string UnitChanger() const {
        if (unit_measure == "km/h") {
            return "m/s";
        }
        else {
            return "km/h";
        }
    }

    bool exeptetionsmy() {//метод проверяющий на корректность введенных данных
        if ((nomber <= 0) || (sped < 0) || ((unit_measure != "km/h") && (unit_measure != "m/s"))) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Racer {
public://доступно для всех мест программы
    string name;
    int number;               //объявление полей класса
    vector<Speed> Speeds_name;

    //конструкторы
    Racer() : name(""), number(0), Speeds_name() {};

    Racer(string a, int b, Speed c) {
        name = a;
        number = b;
        Speeds_name.push_back(c);
    }

    Racer(const  Racer& c) {//конструктор копирования
        name = c.name;
        number = c.number;
        Speeds_name = c.Speeds_name;
    }

    ~Racer() { Speeds_name.clear(); };

    int BestCircle() const {
        vector<vector<double>>circles;
        for (int i = 0; i < Speeds_name.size(); ++i) {
            circles.push_back(vector<double>());
        }
        double max_Speed = 0;
        int result = 0;
        int y = 0;
        for (auto sp : Speeds_name) {
            circles[y].push_back(sp.nomber);
            if (sp.unit_measure == "km/h") {
                circles[y].push_back(sp.sped / 3.6);
            }
            else {
                circles[y].push_back(sp.sped);
            }
            y += 1;
        }
        for (int i = 0; i < Speeds_name.size(); ++i) {
            if (circles[i][1] > max_Speed) {
                max_Speed = circles[i][1];
                result = (int)circles[i][0];
            }
        }
        circles.clear();
        return result;
    }
};

ostream& operator<<(ostream& os, const Speed& r) // перегрузка оператора помещения в поток
{
    return os << setw(12) << left << r.nomber << setw(6) << r.sped << " " << setw(12) << r.unit_measure;
}

istream& operator>>(istream& is, Speed& r) // перегрузка оператора взятия из потока
{
    //проверка на соответствие типам полей класса
    int prot_nomber;
    double prot_sped;
    string prot_unit_measure;
    is >> prot_nomber;
    if (!is || !prot_nomber) {
        is.clear();
        r.nomber = 0;
        r.sped = -1;
        r.unit_measure = "Error";
        return is;
    }
    else {
        r.nomber = prot_nomber;
    }
    is >> prot_sped;
    if (!is) {
        is.clear();
        r.sped = -1;
        r.unit_measure = "Error";
        return is;
    }
    else {
        r.sped = prot_sped;
    }
    is >> prot_unit_measure;
    if (!is) {
        is.clear();
        r.unit_measure = "Error";
        return is;
    }
    else {
        r.unit_measure = prot_unit_measure;
    }
    return is;
}

ostream& operator<<(ostream& os, const Racer& r) // перегрузка оператора помещения в поток
{
    os << setw(15) << left << r.name << setw(13) << left << r.number << setw(19) << r.Speeds_name[0] << r.Speeds_name[0].SpedChanger() << " " << setw(12) << r.Speeds_name[0].UnitChanger() << r.BestCircle() << endl;
    for (int i = 1; i < r.Speeds_name.size(); ++i) {
        os << setw(28) << " " << setw(19) << r.Speeds_name[i] << r.Speeds_name[i].SpedChanger() << " " << setw(12) << r.Speeds_name[i].UnitChanger() << endl;
    }
    os << "------------------------------------------------------------------------------------\n";
    return os;
}

istream& operator>>(istream& is, Racer& r) // перегрузка оператора взятия из потока
{
    //проверка на соответствие типам полей класса
    string prot_number_st;               //объявление полей класса
    Speed prot_Speeds_name;
    cout << "Enter name of the Racer: ";
    is >> r.name;
    is.ignore(1000, '\n');
    cout << "Enter the number of circles: ";
    getline(is, prot_number_st);
    int prot_number = checkNum(prot_number_st);
    while (!prot_number) {
        cout << "Enter the number of circles again: ";
        getline(is, prot_number_st);
        prot_number = checkNum(prot_number_st);
    }
    r.number = prot_number;
    cout << "Enter the Speed data in the following format: " << endl;
    cout << "1 50.0 km/h(m/s)" << endl;
    for (int i = 0; i < r.number; ++i) {
        cout << "Enter " << i + 1 << " element: " << endl;
        is >> prot_Speeds_name;
        while (!is || prot_Speeds_name.nomber != (i + 1) || prot_Speeds_name.exeptetionsmy()) {
            is.clear();
            is.ignore(1000, '\n');
            cout << "Enter the Speed data again: ";
            is >> prot_Speeds_name;
        }
        r.Speeds_name.push_back(prot_Speeds_name);
    }
    return is;
}

void displaySpeeds(const vector<Racer>& Racers) {//функция красивого вывода в консоль
    cout << fixed << setprecision(2);
    cout << setw(15) << left << "Name" << setw(13) << left << "Numbers" << setw(12) << left << "Number" << setw(19) << left << "Speed(before)" << setw(18) << left << "Speed(after)" << "Best Circle\n";
    for (auto sp : Racers) {
        cout << sp;
    }
}

int main() {
    cout << "Good time of a day!" << endl;
    string choise1;
    cout << "Reading from a file or console (f/c)?: ";
    getline(cin, choise1);
    while (choise1[0] == '\n' || empty(choise1) || (choise1!="c" && choise1!="f")) {
        cout << "Enter your chose again: ";
        getline(cin, choise1);
    }
    vector<Racer> Racers;
    vector<Speed> Speeds;
    string name;//имя файла для ввода/вывода
    if (choise1 == "c") {
        cout << "Enter length of array: ";
        int length = check();
        for (int i = 0; i < length; ++i) {
            Racer ruch;
            cout << i + 1 << ": " << endl;
            cin >> ruch;
            Racers.emplace_back(ruch);
        }
    }
    else {
        Racer fragment;
        cout << "Enter the name of the file: ";
        cin >> name;
        ifstream fin(name);
        if (!fin) {
            cout << "Error of open file!";
            return 1;
        }
        else {
            string line;
            string name_of_Racer;
            while (getline(fin, name_of_Racer)) {
                getline(fin, line);
                int len = checkNum(line);
                line.clear();
                if (len == 0) {
                    cout << "Invalid file reading!" << endl;
                    line.clear();
                    getline(fin, name_of_Racer);
                    while (name_of_Racer != "") {
                        getline(fin, name_of_Racer);
                    }
                    getline(fin, name_of_Racer);
                    getline(fin, line);
                    len = checkNum(line);
                    line.clear();
                }
                Speed element;
                int i = -1;
                do {
                    i += 1;
                    fin >> element;
                    if (!(element.exeptetionsmy() || (element.nomber != (i + 1)))) {
                        Speeds.emplace_back(element);
                    }
                } while (!(element.exeptetionsmy() || (element.nomber != (i + 1))));

                fragment.name = name_of_Racer;
                fragment.number = len;
                fragment.Speeds_name = Speeds;
                Racers.emplace_back(fragment);
                Speeds.clear();
            }
        }
        fin.close();
        name.clear();
    }
    cin.ignore(1000, '\n');
    cout << "Output to a file or to the console(f/c)?: ";
    string choise2;
    getline(cin, choise2);
    while (choise2[0] == '\n' || empty(choise2) || (choise2 != "c" && choise2 != "f")) {
        cout << "Enter your chose again: ";
        getline(cin, choise2);
    }
    if (choise2 == "c") {
        if (Racers.size() == 0) {
            cout << "\nThere are no avalubale lines to give you\n";
        }
        else {
            cout << fixed << setprecision(2);
            cout << "\nArray of instances of the class:\n\n";
            cout << setw(13) << left << "Name" << setw(8) << left << "Numbers" << setw(10) << left << "Number" << "Speed Unit of measurement\n";
            for (const auto sp : Racers) {
                cout << setw(13) << sp.name << setw(8) << sp.number << setw(10) << left << sp.Speeds_name[0] << endl;
                for (int i = 1; i < sp.Speeds_name.size(); ++i) {
                    cout << setw(21) << "" << setw(8) << left << sp.Speeds_name[i] << endl;
                }
                cout << "------------------------------------------\n";
            }
            cout << endl;
            cout << "\nArray processing results of instances of the class:\n\n";
            displaySpeeds(Racers);
        }
    }
    else {
        cout << "Enter the name of the file: ";
        cin >> name;
        ofstream fout;
        fout.open(name);
        if (!fout) {
            cout << "Error of open file!";
            return 1;
        }
        else {
            if (Racers.size() == 0) {
                fout << "\nThere are no avalubale lines to give you\n";
            }
            else {
                fout << fixed << setprecision(2);
                fout << "\nArray of instances of the class:\n\n";
                fout << setw(13) << left << "Name" << setw(8) << left << "Numbers" << setw(10) << left << "Number" << "Speed Unit of measurement\n";
                for (const auto sp : Racers) {
                    fout << setw(13) << sp.name << setw(8) << sp.number << setw(10) << left << sp.Speeds_name[0] << endl;
                    for (int i = 1; i < sp.Speeds_name.size(); ++i) {
                        fout << setw(21) << "" << setw(8) << left << sp.Speeds_name[i] << endl;
                    }
                    fout << "------------------------------------------\n";
                }
                fout << endl;
                fout << fixed << setprecision(2);
                fout << "Array processing results of instances of the class:\n\n";
                for (const auto r : Racers) {
                    fout << setw(10) << left << "Name" << setw(13) << left << "Numbers" << setw(12) << left << "Number" << setw(19) << left << "Speed(before)" << setw(18) << left << "Speed(after)" << "Best Circle\n";
                    fout << setw(10) << left << r.name << setw(13) << left << r.number << setw(19) << r.Speeds_name[0] << r.Speeds_name[0].SpedChanger() << " " << setw(12) << r.Speeds_name[0].UnitChanger() << r.BestCircle() << endl;
                    for (int i = 1; i < r.Speeds_name.size(); ++i) {
                        fout << setw(23) << " " << setw(19) << r.Speeds_name[i] << r.Speeds_name[i].SpedChanger() << " " << setw(12) << r.Speeds_name[i].UnitChanger() << endl;
                    }
                    fout << "------------------------------------------------------------------------------------\n";
                }
            }
        }
        fout.close();
    }
    Racers.clear();
    cout << "\nHave a nice day!";
    return 0;
}
