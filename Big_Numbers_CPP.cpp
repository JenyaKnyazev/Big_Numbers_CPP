
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> to_vec(string s) {
    vector<int> vec;
    int i;
    for (i = 0; i < s.length(); i++)
        vec.push_back(s[i] - 48);
    return vec;
}
void print(vector<int> vec) {
    for (int x : vec)
        cout << x;
    cout << endl;
}
void refresh1(vector<int>& vec) {
    int i;
    for (i = vec.size() - 1; i > 0; i--) {
        vec[i - 1] += vec[i] / 10;
        vec[i] %= 10;
    }
    if (vec[0] > 9) {
        vec.insert(vec.begin(), vec[0] / 10);
        vec[1] %= 10;
    }
}
void refresh2(vector<int>& vec) {
    int i;
    for (i = 0; i < vec.size() - 1; i++) {
        vec[i]--;
        vec[i + 1] += 10;
    }
    refresh1(vec);
    while (vec.size() > 1 && vec[0] == 0)
        vec.erase(vec.begin());
}
int compare(vector<int>& a, vector<int>& b) {
    int i;
    if (a.size() > b.size())
        return 1;
    if (a.size() < b.size())
        return -1;
    for (i = 0; i < a.size(); i++) {
        if (a[i] > b[i])
            return 1;
        if (a[i] < b[i])
            return -1;
    }
    return 0;
}
vector<int> add(vector<int>& a, vector<int>& b) {
    vector<int> vec((a.size() > b.size()) ? a.size() : b.size(), 0);
    int i, r;
    for (i = a.size() - 1, r = vec.size() - 1; i >= 0; i--, r--)
        vec[r] = a[i];
    for (i = b.size() - 1, r = vec.size() - 1; i >= 0; i--, r--)
        vec[r] += b[i];
    refresh1(vec);
    return vec;
}
vector<int> subtract(vector<int>& a, vector<int>& b) {
    vector<int> vec(a);
    int i, r;
    for (i = vec.size() - 1, r = b.size() - 1; i >= 0 && r >= 0; i--, r--)
        vec[i] -= b[r];
    refresh2(vec);
    return vec;
}
vector<int> mult(vector<int>& a, vector<int>& b) {
    vector<int>vec(a.size() + b.size(), 0);
    int i, r;
    for (i = a.size() - 1; i >= 0; i--)
        for (r = b.size() - 1; r >= 0; r--) {
            vec[i + r + 1] += a[i] * b[r];
            refresh1(vec);
        }
    while (vec.size() > 1 && vec[0] == 0)
        vec.erase(vec.begin());
    return vec;
}
vector<int> modulu(vector<int>& a, vector<int>& b) {
    vector<int>res;
    int i;
    for (i = 0; i < a.size();) {
        while (i < a.size() && compare(res, b) == -1)
            res.push_back(a[i++]);
        while (res.size() > 0 && res[0] == 0)
            res.erase(res.begin());
        while (compare(res, b) != -1)
            res = subtract(res, b);
    }
    while (res.size() > 1 && res[0] == 0)
        res.erase(res.begin());
    if (res.size() == 0)
        res.push_back(0);
    return res;
}
vector<int> div(vector<int>& a, vector<int>& b) {
    vector<int>res;
    vector<int>vec;
    vector<int> r(1, 1);
    int i;
    for (i = 0; i < a.size();) {
        while (i < a.size() && compare(vec, b) == -1) {
            vec.push_back(a[i++]);
            res.push_back(0);
        }
        while (compare(vec, b) != -1) {
            vec = subtract(vec, b);
            res = add(res, r);
        }
        while (vec.size() > 0 && vec[0] == 0)
            vec.erase(vec.begin());
    }
    while (res.size() > 1 && res[0] == 0)
        res.erase(res.begin());
    return res;
}
void run() {
    string a, b, op;
    vector<int>a2;
    vector<int>b2;
    cout << "Big numbers C++" << endl;
    while (true) {
        cout << endl << "Enter arithmetic operator + - * / % or other exit" << endl;
        getline(cin, op);
        if (op != "+" && op != "-" && op != "*" && op != "/" && op != "%")
            return;
        cout << "Enter first number" << endl;
        getline(cin, a);
        cout << "Enter second number" << endl;
        getline(cin, b);
        a2 = to_vec(a);
        b2 = to_vec(b);
        cout << "Result = ";
        if (op == "+")
            print(add(a2, b2));
        else if (op == "-")
            print(subtract(a2, b2));
        else if (op == "*")
            print(mult(a2, b2));
        else if (op == "/")
            print(div(a2, b2));
        else
            print(modulu(a2, b2));
    }
}
int main()
{
    string a;
    run();
    cout << "Good Bye" << endl;
    getline(cin, a);
}


