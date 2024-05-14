//
// Created by 86158 on 2024/5/13.
//

#include "MorseCodeTree.h"
#include "../utils/Logger.h"

#include <iostream>
#include <filesystem>
#include <queue>

namespace morse_code_chatting::morse_tree {
    // initialize: nullptr
    TreeNode* TreeNode::instance = nullptr;

    MorseCodeTree::MorseCodeTree() {
        root = TreeNode::getInstance();

        currCharacter = ' '; // 首先设为空, 从二叉树找
        currentDepth = 0;
    }

    MorseCodeTree *MorseCodeTree::New() {
        auto * morseCode = new MorseCodeTree();

        return morseCode;
    }

    void MorseCodeTree::initTheTree() {
        root = TreeNode::getInstance();
        currCharacter = ' ';
        currentDepth = 0;
    }

    TreeNode::TreeNode() {
        left = nullptr;
        right = nullptr;
        sign = ' ';
    }

    [[maybe_unused]] TreeNode::TreeNode(char sign) {
        left = nullptr;
        right = nullptr;
        this->sign = sign;
    }

    [[maybe_unused]] void TreeNode::setLeft(TreeNode *l) {
        this->left = l;
    }

    [[maybe_unused]] void TreeNode::setRight(TreeNode *r) {
        this->right = r;
    }

    [[maybe_unused]] [[maybe_unused]] char TreeNode::getSign() const {
        return sign;
    }

    void TreeNode::move(TreeNode*& root, char flag) {
        if (root == nullptr) {
            LOG << "TreeNode is null.";
        }
        if (flag == '.') {
            root = root->left;
        }
        else if (flag == '-') {
            root = root->right;
        }
        else {
            LOG << "Invalid Flag: " + std::string(1, flag);
        }
    }

    TreeNode *TreeNode::getInstance() {
        if (instance == nullptr) {
            instance = new TreeNode();
            instance->load();
        }
        return instance;
    }

    void TreeNode::createFolderIfNotExist() {
        std::filesystem::path folderPath = RESOURCE_FOLDER;
        if (!std::filesystem::exists(folderPath)) {
            if (!std::filesystem::create_directories(folderPath)) {
                LOG << "Create Resource Folder Error.";
                std::cerr << "create resource folder error." << std::endl;
                // the program cannot run without the resource.
                exit(-1);
            }
        }
    }

    void TreeNode::createFileIfNotExist() {
        createFolderIfNotExist();
        std::ifstream file;
        file.open(FILE_PATH);
        // the file does not exist.
        if (!file.good()) {
            std::ofstream outFile(FILE_PATH);
            if (outFile.is_open()) {
                outFile << "ETIANMSURWDKGOHVF0L0PJBXCYZQ00";
                outFile.close();
            }
            else {
                LOG << "Cannot create resource file.";
                exit(-1);
            }
        }
        file.close();
    }

    void TreeNode::load() {
        createFileIfNotExist();
        std::string codeString;
        readStringFromFile(codeString);
        bfs(codeString);
    }

    void TreeNode::readStringFromFile(std::string &string) {
        string = ""; // init
        std::ifstream file(FILE_PATH);
        if (!file.is_open()) {
            LOG << "Cannot open resource file.";
            exit(-1);
        }
        std::string line;
        while (std::getline(file, line)) {
            string += line;
        }
        file.close();
    }

    void TreeNode::bfs(const std::string& codeString) {
        std::queue<TreeNode*> queue;
        queue.push(this);

        int i = 0;

        auto chooseSign = [](char ch) -> char {
            if (ch == '0') {
                return ' ';
            }
            else {
                return ch;
            }
        };

        while (i < codeString.length() && !queue.empty()) {
            auto size = queue.size();
            while (size > 0) {
                auto node = queue.front();

                node->left = new TreeNode(chooseSign(codeString[i++]));
                node->right = new TreeNode(chooseSign(codeString[i++]));
                queue.pop();
                queue.push(node->left);
                queue.push(node->right);

                size --;
            }
        }
    }

} // morse_code_chatting
// morse_tree