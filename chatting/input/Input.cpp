//
// Created by 86158 on 2024/5/14.
//

#include "Input.h"

#include <conio.h>
#include <thread>
#include <mutex>
#include <atomic>


namespace morse_code_chatting::input {
    std::string Input::inputWord() {
        std::string ans;

        auto inputWordInFunction = [&]() -> void {
            auto ch = inputLetter();
            {
                std::lock_guard<std::mutex> lock(wordInputMutex);
                isInputWord.store(true);
            }
            ans += ch;
        };

        inputWordInFunction();

        while (isInputWord.load()) {
            {
                std::lock_guard<std::mutex> lock(wordInputMutex);
                isInputWord.store(false);
            }

            std::thread inputWordThread(inputWordInFunction);
            inputWordThread.detach();

            for (int i = 0; i < 20; i ++ ) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                if (isInputWord.load()) {
                    break;
                }
            }
        }


        return ans;
    }

    char Input::inputLetter() {
        char res = ' ';

        auto inputSomething = [&]() -> void {
            // No buffered inputs
            int temp = getch();
            {
                std::lock_guard<std::mutex> lock(letterInputMutex);
                isInputLetter.store(true);
            }
            auto sign = static_cast<char>(temp);
            res = tree->move(sign);
            putchar(res);
        };

        inputSomething();
        isInputLetter.store(true);

        while (isInputLetter.load()) {
            // We shouldn't lock it unless we block it.
            {
                std::lock_guard<std::mutex> lock(letterInputMutex);
                isInputLetter.store(false);
            }

            std::thread inputThread(inputSomething);
            inputThread.detach();

            /**
             * We divide 700ms into 7 portions, maybe 14 portions or more is more precise. But it will impacts performance;
             */
            for (int i = 0; i < 7; i ++ ) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (isInputLetter.load()) {
                    break;
                }
            }
        }
        initInput();

        return res;
    }

    Input::Input() {
        isInputWord.store(false);
        isInputLetter.store(false);
        tree = morse_tree::MorseCodeTree::New();
    }

    void Input::initInput() {
        delete tree;
        tree = morse_tree::MorseCodeTree::New();
//        isInputWord.store(false);
        isInputLetter.store(false);
    }
} // morse_code_chatting
// input