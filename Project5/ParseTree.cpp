#include "ParseTree.hpp"

std::string ParseTree::display() const {
    return display(root, 64);  // Adjust width as needed
}

std::string ParseTree::display(TreeNode* node, int width) const {
    // Dummy placeholder for null leaves
    TreeNode* dummy = nullptr;

    // Empty node output
    std::string emptyNode = ".";

    // Define buffer to collect output
    std::stringstream buffer;

    // Define queue (FIFO) to hold next layer's nodes
    std::queue<TreeNode*> theQueue;

    // Boolean to keep track of when no nodes in the layer
    bool more = true;

    // Start with the root
    theQueue.push(node);

    // First layer has one node
    int curNodes = 1;

    // While there are nodes in the queue
    while (more) {
        more = false;

        // Calculate the base offset
        int offset = width / (curNodes * 2);

        // Process the nodes in the layer
        for (int i = 0; i < curNodes; i++) {
            // Get and remove front node
            TreeNode* ptr = theQueue.front();
            theQueue.pop();

            // All offsets after the first are doubled
            if (i == 1) {
                offset *= 2;
            }

            // If not a dummy node, process it
            if (ptr != dummy) {
                // Add contents to buffer
                buffer << std::setw(offset) << ptr->data;

                // If there is a left child, add to fifo
                if (ptr->left) {
                    more = true;
                    theQueue.push(ptr->left);
                }
                    // No left child, add dummy in its place
                else {
                    theQueue.push(dummy);
                }

                // If right child, add to fifo
                if (ptr->right) {
                    more = true;
                    theQueue.push(ptr->right);
                }
                    // No right child, add dummy in its place
                else {
                    theQueue.push(dummy);
                }
            }
                // This node was a dummy
                // Output the emptyNode symbol
                // Add two dummies to FIFO for children placeholders
            else {
                buffer << std::setw(offset) << emptyNode;
                theQueue.push(dummy);
                theQueue.push(dummy);
            }
        }
        curNodes *= 2;
        buffer << std::endl;
    }

    return buffer.str();
}

ParseTree::ParseTree(const std::string& expression) {
    if (isPostfixExpression(expression)) {
        root = buildTreeFromPostfix(expression);
    } else {
        root = buildTreeFromPostfix(infixToPostfix(expression));
    }
}

ParseTree::TreeNode* ParseTree::buildTreeFromPostfix(const std::string& postfix) {
    std::stack<TreeNode*> stack;

    for (char c : postfix) {
        if (isalnum(c)) {
            auto* node = new TreeNode(c);
            stack.push(node);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            TreeNode* rightOperand = stack.top();
            stack.pop();

            TreeNode* leftOperand = stack.top();
            stack.pop();

            auto* newNode = new TreeNode(c);
            newNode->left = leftOperand;
            newNode->right = rightOperand;

            stack.push(newNode);
        }
    }

    if (!stack.empty()) {
        return stack.top();
    } else {
        return nullptr; // Handle the case where the stack is empty
    }
}

ParseTree::~ParseTree() {
    destroyTree(root);
}

void ParseTree::destroyTree(TreeNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

bool ParseTree::isPostfixExpression(const std::string& expression) {
    // Count of operands and operators
    int operandCount = 0;
    int operatorCount = 0;

    // Iterate through each character in the expression
    for (char c : expression) {
        if (isalnum(c)) {
            operandCount++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            operatorCount++;
        }
    }

    // For a valid postfix expression, the operand count should be one less than the operator count
    return (operandCount == operatorCount + 1);
}

std::string ParseTree::preOrder(TreeNode* node) const {
    if (node == nullptr) {
        return "";
    }

    std::string result;
    result += node->data;
    result += preOrder(node->left);
    result += preOrder(node->right);
    return result;
}

std::string ParseTree::inOrder(TreeNode* node) const {
    if (node == nullptr) {
        return "";
    }

    std::string result;
    if (node->left || node->right) {
        result += '(';
    }

    result += inOrder(node->left);
    result += node->data;
    result += inOrder(node->right);

    if (node->left || node->right) {
        result += ')';
    }

    return result;
}

std::string ParseTree::postOrder(TreeNode* node) const {
    if (node == nullptr) {
        return "";
    }

    std::string result;
    result += postOrder(node->left);
    result += postOrder(node->right);
    result += node->data;
    return result;
}

std::string ParseTree::preOrder() const {
    return preOrder(root);
}

std::string ParseTree::inOrder() const {
    return inOrder(root);
}

std::string ParseTree::postOrder() const {
    return postOrder(root);
}

std::string ParseTree::infixToPostfix(const std::string& infix) {
    std::string postfix;
    std::stack<char> operators;

    auto getPrecedence = [](char op) {
        if (op == '+' || op == '-') {
            return 1;
        } else if (op == '*' || op == '/') {
            return 2;
        }
        return 0; // Assuming other characters are operands
    };

    auto isLeftAssociative = [](char op) {
        return (op == '+' || op == '-' || op == '*' || op == '/');
    };

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Pop the '('
        } else {
            while (!operators.empty() && operators.top() != '(' &&
                   getPrecedence(c) <= getPrecedence(operators.top()) &&
                   (isLeftAssociative(c) || getPrecedence(c) < getPrecedence(operators.top()))) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

void ParseTree::parseInOrder(const std::string& infix) {
    root = buildTreeFromPostfix(infixToPostfix(infix));
}

