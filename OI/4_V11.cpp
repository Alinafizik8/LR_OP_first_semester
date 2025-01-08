#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

vector<string> SplitPhrase(string input) {

    istringstream iss(input);
    string temp;
    vector<string> result;

    while (iss >> temp) {
        result.push_back(temp);
    }
    return result;
}

int CheckNum(string line) {
    int resultNum = 0;
    if (!line.empty() && line[0] != '\n' && line.size() < 10) {
        int len = size(line);
        string checking = "";
        for (int i = 0; i < len; ++i) {
            if (isdigit(line[i])) {
                checking.append(1, line[i]);
            }
        }
        if (size(checking) == len) {
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

int main()
{
    char ans;
    do {
        cout << "Text transformation\n";
        string name;
        cout << "Enter the name of the file: ";
        cin >> name;
        cin.ignore(1000, '\n');
        cout << "Enter the len of the line: ";
        int len = check();
        vector<string> lines; //вектор со всеми строками, кроме больших слов
        vector<string> big_lines; //вектор со слишком большими словами
        vector<int> i_big_lines; //вектор с индексами строк, в которые будут помещены большие слова
        vector<string> final; //вектор с финальными строками, который переписывается в файл
        ifstream fin(name);
        if (!fin.is_open()) {
            cout << "Error of open file!";
        }
        else {
            vector<string> ostatki; //вектор с остатками(куски строки, которые мы отрезали, чтобы подогнать строку под нужную длину)
            string nado;
            string line1;
            string line;
            int y = -1;
            while (getline(fin, line1)) {
                if (ostatki.size() > 0) {
                    if (!ostatki[y].empty()) {
                        line.append(ostatki[y]);
                        line.append(1, ' ');
                    }
                }
                line.append(line1);
                line1.clear();
                vector<string> dop = SplitPhrase(line);
                if (dop.size() > 0) {
                    if (dop[0].length() > len) {
                        big_lines.push_back(dop[0]);
                        i_big_lines.push_back(y + 1);
                        vector<string> dop1;
                        for (int f = 1; f < dop.size(); ++f) {
                            dop1.push_back(dop[f]);
                        }
                        dop = dop1;
                        dop1.clear();
                    }
                    if (line.length() > len) {
                        int raznitcha = 0;
                        int kolvo_slov = 0;
                        for (int i = dop.size() - 1; i >= 0; --i) {
                            if (((raznitcha + kolvo_slov) < (line.length() - len)) || ((raznitcha + kolvo_slov) == (0))) {
                                raznitcha += dop[i].length();
                                kolvo_slov += 1;
                            }
                        }
                        for (int i = 0; (i < (dop.size() - kolvo_slov)); ++i) {
                            nado.append(dop[i]);
                            if (i != (dop.size() - kolvo_slov - 1)) {
                                nado.append(1, ' ');
                            }
                        }
                        lines.push_back(nado);
                        nado.clear();
                        for (int i = dop.size() - kolvo_slov; i < dop.size(); ++i) {
                            nado.append(dop[i]);
                            if (i != (dop.size() - 1)) {
                                nado.append(1, ' ');
                            }
                        }
                        ostatki.push_back(nado);
                        nado.clear();
                        dop.clear();
                    }
                    else {
                        lines.push_back(line);
                        ostatki.push_back("");
                    }
                }
                else {
                    lines.push_back("");
                    ostatki.push_back("");
                }
                y += 1;
                line.clear();
            }
            bool fl = true;
            while (!ostatki[y].empty() && fl) {
                if (ostatki[y].length() <= len) {
                    lines.push_back(ostatki[y]);
                    fl = false;
                }
                else {
                    vector<string> f = SplitPhrase(ostatki[y]);
                    if (f.size() > 0) {
                        if (f[0].length() > len) {
                            big_lines.push_back(f[0]);
                            i_big_lines.push_back(y + 1);
                            vector<string> dop2;
                            for (int q = 1; q < f.size(); ++q) {
                                dop2.push_back(f[q]);
                            }
                            f = dop2;
                            dop2.clear();
                        }
                        if (fl) {
                            int raznitcha = 0;
                            int kolvo_slov = 0;
                            for (int i = f.size() - 1; i >= 0; --i) {
                                if (((raznitcha + kolvo_slov) < (ostatki[y].length() - len)) || ((raznitcha + kolvo_slov) == (0))) {
                                    raznitcha += f[i].length();
                                    kolvo_slov += 1;
                                }
                            }
                            for (int i = 0; (i < f.size() - kolvo_slov); ++i) {
                                nado.append(f[i]);
                                if (i != (f.size() - kolvo_slov - 1)) {
                                    nado.append(1, ' ');
                                }
                            }
                            lines.push_back(nado);
                            nado.clear();
                            for (int i = f.size() - kolvo_slov; i < f.size(); ++i) {
                                nado.append(f[i]);
                                if (i != (f.size() - 1)) {
                                    nado.append(1, ' ');
                                }
                            }
                            ostatki.push_back(nado);
                        }
                    }
                    else {
                        lines.push_back("");
                        ostatki.push_back("");
                    }
                    y += 1;
                    nado.clear();
                    f.clear();
                }
            }
        }
        fin.close();
        int r = 0;
        bool got = false;
        for (int d = 0; d < lines.size(); ++d) {
            got = false;
            for (int u = 0; u < i_big_lines.size(); ++u) {
                if (d == i_big_lines[u]) {
                    got = true;
                }
            }
            if (got) {
                final.push_back(big_lines[r]);
                r += 1;
            }
            else {
                final.push_back(lines[d]);
            }
        }
        ofstream fout;
        fout.open(name);
        if (!fout.is_open()) {
            cout << "Error of open file!";
        }
        else {
            for (int i = 0; i < final.size(); ++i) {
                fout << final[i];
                if (i != (final.size() - 1)) {
                    fout << endl;
                }
            }
        }
        fout.close();
        cout << "Continue?\n" << "Enter y/Y of anything to exit: ";
        cin >> ans;
    } while (ans == 'y' || ans=='Y');
    return 0;
}
