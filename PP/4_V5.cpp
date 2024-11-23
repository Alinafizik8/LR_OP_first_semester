#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    cout << "Good time of day!" << endl;
    vector<vector<string>> vec_st;
    int empt_l = 0;
    for (int i = 0; i < 27; ++i) {
        vec_st.push_back(vector<string>());
    }
    ifstream fin;
    fin.open("start.txt");
    if (!fin.is_open()) {
        cout << "Error of open file!";
    }
    else {
        string s;
        char elem;
        while (fin.get(elem)) {
            string dop = "";
            dop.push_back(elem);
            if (isalpha(elem)) {
                getline(fin, s);
                s.insert(0, dop);
                if (int(elem) <= 90) {
                    vec_st[int(elem) % 65].push_back(s);
                }
                else {
                    vec_st[int(elem) % 97].push_back(s);
                }
            }
            else if (elem!='\n') {
                getline(fin, s);
                s.insert(0, dop);
                vec_st[26].push_back(s);
            }
            else {
                empt_l += 1;
            }
        }
    }
    fin.close();
    ofstream fout;
    fout.open("end.txt");
    if (!fout.is_open()) {
        cout << "Error of open file!";
    }
    else {
        for (int i = 0; i < vec_st.size(); ++i) {
            for (int j = 0; j < vec_st[i].size(); ++j) {
                fout << vec_st[i][j] << '\n';
            }
        }
        if (empt_l != 0) {
            fout << empt_l << " empty line(s)";
        }
    }
    fout.close();
    cout << "Done!";
    return 0;//возврат 0 и завершение работы программы в случае отказа пользователя от продолжения
}
