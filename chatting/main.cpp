//
// Created by 86158 on 2024/5/13.
//

#include "input/Input.h"

using namespace morse_code_chatting;

int main() {

    input::Input input;
    auto word = input.inputWord();

    std::cout << word << std::endl;
    system("pause");

}