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

    speed(int b, double a, string c) {
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

    bool exeptetionsmy() {
        if ((nomber <= 0) || (sped < 0) || ((unit_measure != "km/h") && (unit_measure != "m/s"))) {
            return true;
        }
        else {
            return false;
        }
    }
};

ostream& operator<<(ostream& os, const speed& r) // перегрузка оператора помещения в поток
{
    return os << r.nomber << "\t" << r.sped << "\t" << r.unit_measure;
}

istream& operator>>(istream& is, speed& r) // перегрузка оператора взятия из потока
{
    int prot_nomber;
    double prot_sped;
    string prot_unit_measure;
    is >> prot_nomber >> prot_sped >> prot_unit_measure;
    if (!cin) {
        is.clear();
        is.ignore(10000, '\n');
        r.nomber = 0;
        r.sped = 0;
        r.unit_measure = "Error";
    }
    else {
        r.nomber = prot_nomber;
        r.sped = prot_sped;
        r.unit_measure = prot_unit_measure;
    }
    return is;
}

void displaySpeeds(const vector<speed>& speeds) {
    cout << fixed << setprecision(2);
    cout << "Number\tSpeed (km/h)\tSpeed (m/s)\n";
    for (const auto& sp : speeds) {
        cout << sp.nomber << "\t"
            << sp.toKilometersPerHour() << "\t\t"
            << sp.toMetersPerSecond() << "\n";
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
    vector<speed> speeds;
    string name;
    if (choise1 == 'c') {
        cout << "Enter length of array: ";
        int length = check();
        cout << "Enter the speed data in the following format: " << endl;
        cout << "1 50.0 km/h(m/s)" << endl;
        for (int i = 0; i < length; ++i) {
            speed ruch;
            cout << i + 1 << ": ";
            cin >> ruch;
            while (ruch.exeptetionsmy()) {
                cout << "Error! Enter " << i+1 << " element again: ";
                cin >> ruch;
            }
            speeds.emplace_back(ruch);
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
            int len;
            fin >> len;
            string line;
            getline(fin, line);
            line.clear();
            for (int i = 0; i < len; ++i) {
                speed element;
                fin >> element;
                if (element.exeptetionsmy()) {
                    cout << "Error! Wrong line!" << endl;
                }
                else {
                    speeds.emplace_back(element);
                }
                getline(fin, line);
                line.clear();
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
        if (speeds.size() == 0) {
            cout << "\nThere are no avalubale lines to give you\n";
        }
        else {
            cout << fixed << setprecision(2);
            cout << "\nArray of instances of the class:\n";
            cout << "Number\tSpeed\tUnit of measurement\n";
            for (const auto sp : speeds) {
                cout << sp << endl;
            }
            cout << endl;
            cout << "\nArray processing results of instances of the class:\n";
            displaySpeeds(speeds);
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
            if (speeds.size() == 0) {
                cout << "\nThere are no avalubale lines to give you\n";
            }
            else {
                fout << fixed << setprecision(2);
                fout << "Array of instances of the class:\n";
                fout << "Number\tSpeed\tUnit of measurement\n";
                for (const auto sp : speeds) {
                    fout << sp << endl;
                }
                fout << "\nArray processing results of instances of the class:\n";
                fout << "Number\tSpeed (km/h)\tSpeed (m/s)\n";
                for (const auto& sp : speeds) {
                    fout << sp.nomber << "\t"
                        << sp.toKilometersPerHour() << "\t\t"
                        << sp.toMetersPerSecond() << "\n";
                }
            }
        }
        fout.close();
    }
    cout << "\nHave a nice day!";
    return 0;
}
