//
// Created by 86158 on 2024/5/13.
//

#ifndef LITTLE_GAME_MORSE_CODE_TREE_H
#define LITTLE_GAME_MORSE_CODE_TREE_H

#include <string>

namespace morse_code_chatting::morse_tree {
    class TreeNode {
    private:
        const char* RESOURCE_FOLDER = "resource";
        const char* FILE_PATH = "resource/morseCode.code";

        TreeNode* left;
        TreeNode* right;
        char sign;

        TreeNode();
        [[maybe_unused]] explicit TreeNode(char sign);

        [[maybe_unused]] void setLeft(TreeNode* l);
        [[maybe_unused]] void setRight(TreeNode* r);

    private:
        // Load the tree from file (if file not exist, create it)
        void load();

        // if the file(resource_code) does not exist, then create it.
        void createFileIfNotExist();
        void createFolderIfNotExist();

        // read string from file
        void readStringFromFile(std::string& string);

        // init the node with bfs
        void bfs(const std::string& codeString);

    public:
        // not only one instance. But the start is the only.
        // const TreeNode &operator=(const TreeNode & node) = delete;
        TreeNode(const TreeNode& node) = delete;

    // for single instance
    private:
        static TreeNode* instance;

    public:
        [[maybe_unused]] [[nodiscard]] char getSign() const;

        // move(choose) left or right according the sign ['.']['-']
        static void move(TreeNode*& root, char flag);

        // the entrance of this single class.
        static TreeNode* getInstance();



    };

    class MorseCodeTree {
    private:
        TreeNode* root;
        char currCharacter;
        /**
         * the current depth \n
         * For Morse Code, the depth is less than 6 usually.
         */
        short currentDepth;

        // constructor function, private
        MorseCodeTree();

        void initTheTree();


    public:
        char move(char flag) {
            // init the root
            if (flag != '.' && flag != '-') {
                initTheTree();
                return ' ';
            }
            else {
                TreeNode::move(root, flag);
                currentDepth ++;
                if (!root) {
                    initTheTree();
                }
                currCharacter = root->getSign();
                if (currCharacter == ' ') {
                    initTheTree();
                }

                return currCharacter;
            }
        }

        static MorseCodeTree* New();
    };

} // morse_code_chatting
// morse_tree

#endif //LITTLE_GAME_MORSE_CODE_TREE_H
