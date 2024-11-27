#include <iostream> //для работы с потоками ввода и вывода
#include <fstream> //для работы с файлами
#include <string> //для работы с типом string
#include <vector> //для работы с vector
#include <iomanip> //для работы с форматированием ввода
using namespace std; //для использования идентификаторов из пространства имен

int CheckNum(string line) {
    int resultNum = 0;
    if (!line.empty() && line[0] != '\n' && line.size() <= 20) {
        string checking = "";
        for (int i = 0; i < size(line); ++i) {
            if (isdigit(line[i])) {
                checking.append(1, line[i]);
            }
        }
        if (size(checking) == size(line)) {
            resultNum = stoi(line);
        }
    }
    return resultNum;
}

int check() {
    string line;
    getline(cin, line);
    int number = CheckNum(line);
    if (!number) {
        cout << "Error! Enter again: ";
        return check();
    }
    return number;
}

class speed {//создание класса
public://доступно для всех мест программы
    int nomber;
    double sped;               //объявление полей класса
    string unit_measure;

    //конструктор
    speed() : nomber(0), sped(0.0), unit_measure("") {};

    speed(int b, double a, string c) {
        sped = a;
        nomber = b;
        unit_measure = c;
    }

    speed(string a) {
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

    speed(const speed& c) {//конструктор копирования
        sped = c.sped;
        nomber = c.nomber;
        unit_measure = c.unit_measure;
    }

    ~speed() { unit_measure.clear(); };//деструктор

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

class racer {
public://доступно для всех мест программы
    string name;
    int number;               //объявление полей класса
    vector<speed> speeds_name;

    racer() : name(""), number(0), speeds_name() {};

    racer(string a, int b, speed c) {
        name = a;
        number = b;
        speeds_name.push_back(c);
    }

    racer(const  racer& c) {//конструктор копирования
        name = c.name;
        number = c.number;
        speeds_name = c.speeds_name;
    }

    ~racer() {};

    int BestCircle() const {
        vector<vector<int>>circles;
        for (int i = 0; i < speeds_name.size(); ++i) {
            circles.push_back(vector<int>());
        }
        double max_speed = 0;
        int result = 0;
        int y = 0;
        for (auto sp : speeds_name) {
            circles[y].push_back(sp.nomber);
            if (sp.unit_measure == "km/h") {
                circles[y].push_back(sp.sped / 3.6);
            }
            else {
                circles[y].push_back(sp.sped);
            }
            y += 1;
        }
        for (int i = 0; i < speeds_name.size(); ++i) {
            if (circles[i][1] > max_speed) {
                max_speed = circles[i][1];
                result = circles[i][0];
            }
        }
        circles.clear();
        return result;
    }

};

ostream& operator<<(ostream& os, const speed& r) // перегрузка оператора помещения в поток
{
    return os << setw(12) << left << r.nomber << setw(6) << r.sped << " " << setw(12) << r.unit_measure;
}

istream& operator>>(istream& is, speed& r) // перегрузка оператора взятия из потока
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

ostream& operator<<(ostream& os, const racer& r) // перегрузка оператора помещения в поток
{
    os << setw(15) << left << r.name << setw(13) << left << r.number << setw(19) << r.speeds_name[0] << r.speeds_name[0].SpedChanger() << " " << setw(12) << r.speeds_name[0].UnitChanger() << r.BestCircle() << endl;
    for (int i = 1; i < r.speeds_name.size(); ++i) {
        os << setw(28) << " " << setw(19) << r.speeds_name[i] << r.speeds_name[i].SpedChanger() << " " << setw(12) << r.speeds_name[i].UnitChanger() << endl;
    }
    os << "------------------------------------------------------------------------------------\n";
    return os;
}

istream& operator>>(istream& is, racer& r) // перегрузка оператора взятия из потока
{
    //проверка на соответствие типам полей класса
    string prot_number_st;               //объявление полей класса
    speed prot_speeds_name;
    cout << "Enter name of the racer: ";
    is >> r.name;
    is.ignore(1000, '\n');
    cout << "Enter the number of circles: ";
    getline(is, prot_number_st);
    int prot_number = CheckNum(prot_number_st);
    while (!prot_number) {
        cout << "Enter the number of circles again: ";
        getline(is, prot_number_st);
        prot_number = CheckNum(prot_number_st);
    }
    r.number = prot_number;
    cout << "Enter the speed data in the following format: " << endl;
    cout << "1 50.0 km/h(m/s)" << endl;
    for (int i = 0; i < r.number; ++i) {
        cout << "Enter " << i + 1 << " element: " << endl;
        is >> prot_speeds_name;
        while (!is || prot_speeds_name.nomber != (i + 1) || prot_speeds_name.exeptetionsmy()) {
            is.clear();
            is.ignore(1000, '\n');
            cout << "Enter the speed data again: ";
            is >> prot_speeds_name;
        }
        r.speeds_name.push_back(prot_speeds_name);
    }
    return is;
}

void displaySpeeds(const vector<racer>& racers) {//функция красивого вывода в консоль
    cout << fixed << setprecision(2);
    cout << setw(15) << left << "Name" << setw(13) << left << "Numbers" << setw(12) << left << "Number" << setw(19) << left << "Speed(before)" << setw(18) << left << "Speed(after)" << "Best Circle\n";
    for (auto sp : racers) {
        cout << sp;
    }
}

int main() {
    cout << "Good time of a day!" << endl;
    char choise1;
    cout << "Reading from a file or console (f/c)?: ";
    cin >> choise1;
    while ((choise1 != 'f' && choise1 != 'c') || cin.peek() != '\n') {
        cin.ignore(1000, '\n');
        cout << "Enter your chose again: ";
        cin >> choise1;
    }
    cin.ignore(1000, '\n');
    vector<racer> racers;
    vector<speed> speeds;
    string name;//имя файла для ввода/вывода
    if (choise1 == 'c') {
        cout << "Enter length of array: ";
        int length = check();
        for (int i = 0; i < length; ++i) {
            racer ruch;
            cout << i + 1 << ": " << endl;
            cin >> ruch;
            racers.emplace_back(ruch);
        }
    }
    else {
        racer fragment;
        cout << "Enter the name of the file: ";
        cin >> name;
        ifstream fin(name);
        if (!fin) {
            cout << "Error of open file!";
            return 1;
        }
        else {
            string line;
            string name_of_racer;
            while (getline(fin, name_of_racer)) {
                getline(fin, line);
                int len = CheckNum(line);
                line.clear();
                if (len == 0) {
                    cout << "Invalid file reading!" << endl;
                    line.clear();
                    getline(fin, name_of_racer);
                    while (name_of_racer != "") {
                        getline(fin, name_of_racer);
                    }
                    getline(fin, name_of_racer);
                    getline(fin, line);
                    len = CheckNum(line);
                    line.clear();
                }
                speed element;
                int i = -1;
                do {
                    i += 1;
                    fin >> element;
                    if (!(element.exeptetionsmy() || (element.nomber != (i + 1)))) {
                        speeds.emplace_back(element);
                    }
                } while (!(element.exeptetionsmy() || (element.nomber != (i + 1))));

                fragment.name = name_of_racer;
                fragment.number = len;
                fragment.speeds_name = speeds;
                racers.emplace_back(fragment);
                speeds.clear();
            }
        }
        fin.close();
        name.clear();
    }
    char choise2;
    cout << "Output to a file or to the console(f/c)?: ";
    cin >> choise2;
    while ((choise2 != 'f' && choise2 != 'c') || cin.peek() != '\n') {
        cin.ignore(1000, '\n');
        cout << "Enter your chose again: ";
        cin >> choise2;
    }
    if (choise2 == 'c') {
        if (racers.size() == 0) {
            cout << "\nThere are no avalubale lines to give you\n";
        }
        else {
            cout << fixed << setprecision(2);
            cout << "\nArray of instances of the class:\n";
            cout << "Name\tNumbers\tNumber\tSpeed Unit of measurement\n";
            for (const auto sp : racers) {
                cout << sp.name << "\t" << sp.number << "\t" << sp.speeds_name[0] << endl;
                for (int i = 1; i < sp.speeds_name.size(); ++i) {
                    cout << "\t\t" << sp.speeds_name[i] << endl;
                }
                cout << "----------------------------------------\n";
            }
            cout << endl;
            cout << "\nArray processing results of instances of the class:\n";
            displaySpeeds(racers);
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
            if (racers.size() == 0) {
                cout << "\nThere are no avalubale lines to give you\n";
            }
            else {
                fout << fixed << setprecision(2);
                fout << "Array of instances of the class:\n";
                fout << "Name\tNumbers\tNumber\tSpeed Unit of measurement\n";
                for (const auto sp : racers) {
                    fout << sp.name << "\t" << sp.number << "\t" << sp.speeds_name[0] << endl;
                    for (int i = 1; i < sp.speeds_name.size(); ++i) {
                        fout << "\t\t" << sp.speeds_name[i] << endl;
                    }
                    fout << "--------------------------------------\n";
                }
                fout << endl;
                fout << fixed << setprecision(2);
                fout << "Array processing results of instances of the class:\n";
                for (const auto r : racers) {
                    fout << setw(10) << left << "Name" << setw(13) << left << "Numbers" << setw(12) << left << "Number" << setw(19) << left << "Speed(before)" << setw(18) << left << "Speed(after)" << "Best Circle\n";
                    fout << setw(10) << left << r.name << setw(13) << left << r.number << setw(19) << r.speeds_name[0] << r.speeds_name[0].SpedChanger() << " " << setw(12) << r.speeds_name[0].UnitChanger() << r.BestCircle() << endl;
                    for (int i = 1; i < r.speeds_name.size(); ++i) {
                        fout << setw(23) << " " << setw(19) << r.speeds_name[i] << r.speeds_name[i].SpedChanger() << " " << setw(12) << r.speeds_name[i].UnitChanger() << endl;
                    }
                    fout << "------------------------------------------------------------------------------------\n";
                }
            }
        }
        fout.close();
    }
    racers.clear();
    cout << "\nHave a nice day!";
    return 0;
}
