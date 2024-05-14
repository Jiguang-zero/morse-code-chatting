//
// Created by 86158 on 2024/5/13.
//

#include <conio.h>
#include <cstdio>
#include "morse_tree/MorseCodeTree.h"

using namespace morse_code_chatting;

int main() {
    auto * tree = morse_tree::MorseCodeTree::New();

    int ch;
    while ((ch = getch()) != ' ') {
        system("cls");
        putchar(tree->move((char)ch));
    }


}