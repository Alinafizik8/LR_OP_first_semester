#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    cout << "Good time of day" << endl;
    int res = 1000;
    vector<int> slova;
    ifstream fin;
    fin.open("start.txt");
    if (!fin.is_open()) {
        cout << "Error of open file!";
    }
    else {
        char elem;
        int dop = 0;
        while (fin.get(elem)) {
            if (isalpha(elem)) {
                dop += 1;
            }
            else if (elem != '\n') {
                if (dop != 0) {
                    res = (res <= dop) ? res : dop;
                }
                dop = 0;
            }
            else {
                res = (res <= dop) ? res : dop;
                slova.push_back(res);
                res = 1000;
            }
        }
        if (dop != 0) {
            res = (res <= dop) ? res : dop;
            slova.push_back(res);
        }
    }
    fin.close();
    ofstream fout;
    fout.open("end.txt");
    if (!fout.is_open()) {
        cout << "Error of open file!";
    }
    else {
        int ch = 0;
        while (ch < slova.size()) {
            fout << "Result: ";
            if (slova[ch] != 1000) {
                fout << slova[ch];
            }
            else {
                fout << "There are no words in your line";
            }
            ch += 1;
            if (ch < slova.size()) {
                fout << '\n';
            }
        }
    }
    fout.close();
    slova.clear();
    return 0;
} 
