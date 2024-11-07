#include <iostream>
#include <vector>
using namespace std;

int check() {
    int t;
    cin >> t;
    if ((!cin) || (cin.peek()!='\n')) {
        cout << "Input error! Please, enter again: ";
        cin.clear();
        cin.ignore(10000,'\n');
        return check();
    }
    return t;
}

int main()
{
    char ans;
    cout << "Array modification" << endl;
    do {
        cout << "Enter lenght of array: ";
        int x = check();
        while (x <= 0) {
            cout << "Length soold pe positive! Please, enter again: ";
            x = check();
        }
        while (x >= 1000) {
            cout << "It is too much:(" << endl << "Please, give me fewer number: ";
            x = check();
        }
        vector<int> s;
        for (int i = 0; i < x; ++i) {
            cout << "Enter the " << i + 1 << " element of array: ";
            int el = check();
            s.push_back(el);
        }
        cout << "Current array: ";
        cout << "[";
        for (int i = 0; i < x; ++i) {
            cout << s[i];
            if (i != (x - 1)) {
                cout << ", ";
            }
            else {
                cout << "]";
            }
        }
        cout << endl;
        char ans_move;
        do {
            char move;
            cout << "Enter an operation(i/e ; i - insert; e - erase): ";
            cin >> move;
            while ((move != 'i' && move != 'e') || (cin.peek() != '\n')) {
                cout << "Enter an operation(i/e ; i - insert; e - erase): ";
                cin.ignore(1000, '\n');
                cin >> move;
            }
            int c = 0;
            vector<int> res;
            if (move == 'i') {
                cout << "Enter the position: ";
                int pos = check();
                while (pos<1 || pos>(x + 1)) {
                    cout << "There are no position like that in your array: ";
                    pos = check();
                }
                cout << "Enter an integer: ";
                int chis = check();
                for (int i = 0; i < (pos - 1); ++i) {
                    res.push_back(s[i]);
                }
                res.push_back(chis);
                for (int i = (pos-1); i < x; ++i) {
                    res.push_back(s[i]);
                }
                c += 1;
            }
            else {
                cout << "Enter the position: ";
                int pos = check();
                while (pos<1 || pos>x) {
                    cout << "There are no position like that in your array: ";
                    pos = check();
                }
                for (int i = 0; i < (pos - 1); ++i) {
                    res.push_back(s[i]);
                }
                for (int i = pos; i < x; ++i) {
                    res.push_back(s[i]);
                }
                c -= 1;
            }
            cout << "Current array: ";
            cout << "[";
            for (int i = 0; i < (x + c); ++i) {
                cout << res[i];
                if (i != (x+c - 1)) {
                    cout << ", ";
                }
                else {
                    cout << "]";
                }
            }
            cout << endl;
            cout << "If you want to continue enter y or Y: ";
            cin >> ans_move;
            if (ans_move == 'y' || ans_move == 'Y') {
                s = res;
            }
            else {
                res.clear();
                s.clear();
            }
        } while (ans_move=='y' || ans_move=='Y');
        cout << "If you want to make new array enter y or Y: ";
        cin >> ans;
        if (ans=='y' || ans=='Y') {
            cout << endl;
        }
    } while (ans == 'y' || ans=='Y');
    return 0;
}
