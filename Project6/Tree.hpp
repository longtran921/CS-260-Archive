#include <iostream>
#include <sstream>

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;
    bool deleted;

    explicit TreeNode(int val) : value(val), left(nullptr), right(nullptr), deleted(false) {}
};

class Tree {
private:
    TreeNode* root;
    void insertValue(TreeNode*& node, int value);
    bool findValue(TreeNode* node, int value) const;
    bool removeValue(TreeNode*& node, int value);
    void preOrder(TreeNode* node, std::stringstream& ss) const;
    void inOrder(TreeNode* node, std::stringstream& ss) const;
    void postOrder(TreeNode* node, std::stringstream& ss) const;
    void destructor(TreeNode*& node);
    //TreeNode* findMin(TreeNode* node) const;
    int findLarger(TreeNode* node, int value) const;
    int removeLarger(TreeNode*& node, int value);
    //p
public:
    Tree() : root(nullptr) {}

    void insertValue(int value) {
        insertValue(root, value);
    }
    [[nodiscard]] bool findValue(int value) const {
        return findValue(root, value);
    }
    bool removeValue(int value) {
        return removeValue(root, value);
    }

    [[nodiscard]] std::string preOrder() const;
    [[nodiscard]] std::string inOrder() const;
    [[nodiscard]] std::string postOrder() const;

    void destructor() {
        destructor(root);
    }

    [[nodiscard]] int findLarger(int value) const {
        return findLarger(root, value);
    }
    int removeLarger(int value) {
        return removeLarger(root, value);
    }
};