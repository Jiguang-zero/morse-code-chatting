//
// Created by 86158 on 2024/5/13.
//

#include <iostream>

using namespace std;

int main() {
    string ans;
    char ch = '.';

    auto changeCh = [&ch]() {
        ch = (ch == '.') ? '-' : '.';
    };

    for (int i = 0; i < 30; i ++ ) {
        char a;
        cin >> a;

        if (a != '0') {
            ans += string(1, a);
            ans += "((\"" + string(1, ch) + string(1, a) + "\"))\n";
        }


        changeCh();
    }

    cout << ans;
}