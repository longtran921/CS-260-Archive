#ifndef PARSE_TREE_HPP
#define PARSE_TREE_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <stack>
#include <unordered_map>

class ParseTree {
private:
    struct TreeNode {
        char data;
        TreeNode* left;
        TreeNode* right;

        explicit TreeNode(char c) : data(c), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* buildTreeFromPostfix(const std::string& postfix);

    void destroyTree(TreeNode* node);

    std::string preOrder(TreeNode* node) const;
    std::string inOrder(TreeNode* node) const;
    std::string postOrder(TreeNode* node) const;

    static std::string infixToPostfix(const std::string& infix);
    static bool isPostfixExpression(const std::string& expression);

    std::string display(TreeNode* node, int width) const;

public:
    ParseTree() : root(nullptr) {}
    explicit ParseTree(const std::string& infix);

    ~ParseTree();

    [[nodiscard]] std::string preOrder() const;
    [[nodiscard]] std::string inOrder() const;
    [[nodiscard]] std::string postOrder() const;
    void parseInOrder(const std::string& infix);
    [[nodiscard]] std::string display() const;
};

#endif // PARSE_TREE_HPP