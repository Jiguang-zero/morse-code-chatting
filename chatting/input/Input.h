//
// Created by 86158 on 2024/5/14.
//

#ifndef LITTLE_GAME_MORSE_CODE_INPUT_INPUT_H
#define LITTLE_GAME_MORSE_CODE_INPUT_INPUT_H

#include <iostream>
#include <mutex>
#include <atomic>

#include "../morse_tree/MorseCodeTree.h"

namespace morse_code_chatting::input {

    class Input {
    private:
        morse_tree::MorseCodeTree* tree;
        std::atomic<bool> isInputWord;
        std::atomic<bool> isInputLetter;
        std::mutex letterInputMutex;
        std::mutex wordInputMutex;

        // reinitialize input
        void initInput();


    public:
        Input();

        /**
         * Input a word, then return it.
         * @return std::string
         */
        std::string inputWord();

        /**
         * Input a letter, then return it.
         * @return
         */
        char inputLetter();
    };

} // morse_code_chatting
// input

#endif //LITTLE_GAME_MORSE_CODE_INPUT_INPUT_H
