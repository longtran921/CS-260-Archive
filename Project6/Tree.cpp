#include "Tree.hpp"

void Tree::insertValue(TreeNode*& node, int value) {
    if (node == nullptr) {
        node = new TreeNode(value);
    } else if (value < node->value) {
        insertValue(node->left, value);
    } else if (value > node->value) {
        insertValue(node->right, value);
    } else {
        if (node->deleted) {
            node->deleted = false;
        }
    }
}

bool Tree::findValue(TreeNode* node, int value) const {
    if (node == nullptr) {
        return false;
    } else if (value == node->value && !node->deleted) {
        return true;
    } else if (value < node->value) {
        return findValue(node->left, value);
    } else {
        return findValue(node->right, value);
    }
}

bool Tree::removeValue(TreeNode*& node, int value) {
    if (node == nullptr) {
        return false;
    } else if (value == node->value && !node->deleted) {
        node->deleted = true;
        return true;
    } else if (value < node->value) {
        return removeValue(node->left, value);
    } else {
        return removeValue(node->right, value);
    }
}

void Tree::preOrder(TreeNode* node, std::stringstream& ss) const {
    if (node != nullptr) {
        ss << node->value << (node->deleted ? "D " : " ");
        preOrder(node->left, ss);
        preOrder(node->right, ss);
    }
}

void Tree::inOrder(TreeNode* node, std::stringstream& ss) const {
    if (node != nullptr) {
        inOrder(node->left, ss);
        ss << node->value << (node->deleted ? "D " : " ");
        inOrder(node->right, ss);
    }
}

void Tree::postOrder(TreeNode* node, std::stringstream& ss) const {
    if (node != nullptr) {
        postOrder(node->left, ss);
        postOrder(node->right, ss);
        ss << node->value << (node->deleted ? "D " : " ");
    }
}

void Tree::destructor(TreeNode*& node) {
    if (node != nullptr) {
        destructor(node->left);
        destructor(node->right);
        delete node;
        node = nullptr;
    }
}

int Tree::findLarger(TreeNode* node, int value) const {
    if (node == nullptr) {
        return -1;
    } else if (value == node->value && !node->deleted) {
        return value;
    } else if (value < node->value) {
        int largerInLeft = findLarger(node->left, value);
        return (largerInLeft != -1) ? largerInLeft : node->value;
    } else {
        return findLarger(node->right, value);
    }
}

int Tree::removeLarger(TreeNode*& node, int value) {
    if (node == nullptr) {
        return false;
    }

    int largerValue = findLarger(node, value);

    if (largerValue != -1) {
        removeValue(node, largerValue);
        return largerValue;
    }

    return -1;
}

std::string Tree::preOrder() const {
    std::stringstream ss;
    preOrder(root, ss);
    return ss.str();
}

std::string Tree::inOrder() const {
    std::stringstream ss;
    inOrder(root, ss);
    return ss.str();
}

std::string Tree::postOrder() const {
    std::stringstream ss;
    postOrder(root, ss);
    return ss.str();
}

/*
TreeNode* Tree::findMin(TreeNode* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
} //just in case, delete later if D
*/