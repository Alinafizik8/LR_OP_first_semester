#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int check() {
    int t;
    cin >> t;
    if ((!cin) || (cin.peek() != '\n')) {
        cout << "Input error! Enter again: ";
        cin.clear();
        cin.ignore(1000, '\n');
        return check();
    }
    return t;
}

class speed {
public:
    int nomber;
    double sped;
    string unit_measure;

    speed() : nomber(0), sped(0.0), unit_measure("") {};

    speed(double a, string b) {
        sped = a;
        nomber = 1;
        unit_measure = b;
    }

    speed(double a, int b, string c) {
        sped = a;
        nomber = b;
        unit_measure = c;
    }

    speed(const speed& c) {
        sped = c.sped;
        nomber = c.nomber;
        unit_measure = c.unit_measure;
    }

    ~speed() {};

    double toMetersPerSecond() const {
        if (unit_measure == "km/h") {
            return sped / 3.6;
        }
        else {
            return sped;
        }
    }

    double toKilometersPerHour() const {
        if (unit_measure == "km/h") {
            return sped;
        }
        else {
            return sped * 3.6;
        }
    }
};

ostream& operator<<(ostream& os, const speed& r) // перегрузка оператора помещения в поток
{
    return os << r.nomber << "\t" << r.sped;
}

istream& operator>>(istream& is, speed& r) // перегрузка оператора помещения в поток
{
    is >> r.nomber >> r.sped;
    return is;
}

void displaySpeeds(const vector<speed>& speeds) {
    cout << fixed << setprecision(2);
    cout << "Numbers\tSpeed (km/h)\tSpeed (m/s)\n";
    for (const auto& sp : speeds) {
        cout << sp.nomber << "\t"
            << sp.toKilometersPerHour() << "\t\t"
            << sp.toMetersPerSecond() << "\n";
    }
}

int main() {
    cout << "Good time of a day!"<<endl;
    char choise1;
    cout << "Reading from a file or console (f/c)?: ";
    cin >> choise1;
    while (choise1 != 'f' && choise1 != 'c') {
        cin.ignore(1000, '\n');
        cout << "Enter your chose again: ";
        cin >> choise1;
    }
    vector<speed> speeds;
    string unit_of_measurement;
    double speed_value;
    string name;
    if (choise1 == 'c') {
        cout << "Enter length of array: ";
        int length = check();
        for (int i = 0; i < length; ++i) {
            cout << "Enter the speed for instance " << i + 1 << ": ";
            speed_value = check();
            cout << "Enter the unit of measurement(km/h or m/s): ";
            cin >> unit_of_measurement;
            while (unit_of_measurement != "km/h" && unit_of_measurement != "m/s") {
                cin.ignore(1000, '\n');
                cout << "Enter the unit of measurement again(km/h or m/s): ";
                cin >> unit_of_measurement;
            }
            speeds.emplace_back(speed_value, i + 1, unit_of_measurement); // создаем экземпляр с номером
        }
    }
    else {
        cout << "Enter the name of the file: ";
        cin >> name;
        ifstream fin(name);
        if (!fin) {
            cout << "Error of open file!";
            return 1;
        }
        else {
            char elem;
            int len;
            fin >> len;
            string line;
            getline(fin, line);
            line.clear();
            string speed_value_line;
            for (int i = 0; i < len; ++i) {
                getline(fin, line);
                int flag = 0;
                for (int j = 0; j < size(line); ++j) {
                    if (line[j] != ' ' && flag == 0) {
                        speed_value_line.append(1, line[j]);
                    }
                    else {
                        if (flag == 0) {
                            speed_value = stod(speed_value_line);
                            flag += 1;
                        }
                        else {
                            unit_of_measurement.append(1, line[j]);
                        }
                    }
                }
                speed_value_line.clear();
                line.clear();
                speeds.emplace_back(speed_value, i + 1, unit_of_measurement);
            }
        }
        fin.close();
        name.clear();
    }
    char choise2;
    cout << "Output to a file or to the console(f/c)?: ";
    cin >> choise2;
    while (choise2 != 'f' && choise2 != 'c') {
        cin.ignore(1000, '\n');
        cout << "Enter your chose again: ";
        cin >> choise2;
    }
    if (choise2 == 'c') {
        cout << "\nArray of instances of the speed class and processing results:\n";
        displaySpeeds(speeds);
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
            fout << fixed << setprecision(2);
            fout << "Numbers\tSpeed (km/h)\tSpeed (m/s)\n";
            for (const auto& sp : speeds) {
                fout << sp.nomber << "\t"
                    << sp.toKilometersPerHour() << "\t\t"
                    << sp.toMetersPerSecond() << "\n";
            }
        }
        fout.close();
    }
    cout << "Have a nice day!";
    return 0;
}
