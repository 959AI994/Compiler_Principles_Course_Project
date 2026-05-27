/*#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;

int main() {
    // 定义非终端符号集合，用于判断是否为终端符号
    set<string> nV = { "E", "E' ", "T", "T' ", "F" };

    // 1. 定义预测分析表
    map<string, vector<string>> table;
    table["E,number"] = table["E,id"] = table["E,("] = { "E→TE' ", "T", "E' " };
    table["E' ,)"] = table["E' ,$"] = { "E' →ε" };
    table["E' ,+"] = { "E' →+TE' ","+","T" ,"E' " };
    table["E' ,-"] = { "E' →-TE' ","-","T", "E' " };
    table["T,number"] = table["T,id"] = table["T,("] = { "T→FT' ", "F", "T' " };
    table["T' ,)"] = table["T' ,+"] = table["T' ,-"] = table["T' ,$"] = { "T' →ε" };
    table["T' ,*"] = { "T' →*FT' ","*","F", "T' " };
    table["T' ,/"] = { "T' →/FT' ","/","F", "T' " };
    table["F,number"] = { "F→number","number" };
    table["F,id"] = { "F→id" ,"id"};
    table["F,("] = { "F→(E)","(", "E",")"};

    // 2. 准备输入单词序列: a*(3+b)/4-7
    vector<string> w = { "id", "*", "(", "number", "+", "id", ")", "/", "number", "-", "number", "$" };

    // 3. 预测分析表驱动的语法分析算法
    stack<string> s;
    s.push("$");
    s.push("E");
    int ip = 0;

    while (!s.empty()) {
        string X = s.top();
        if (X == w[ip]) {
            cout << "匹配: " << X << endl;
            s.pop();
            ip++;
        }
        else if (nV.find(X) == nV.end()) {
            cout << "语法错误(失配): " << w[ip] << " 期待: " << X << endl;
            break;
        }
        else if (table.find(X + "," + w[ip]) == table.end()) {
            cout << "语法错误(无适当的产生式): " << X << " 下一个符号: " << w[ip] << endl;
            break;
        }
        else {
            vector<string> p = table[X + "," + w[ip]];
            cout << "输出: " << p[0] << endl;
            s.pop(); // 弹出栈顶元素
            // 反向入栈，跳过产生式的左侧
            for (int i = p.size() - 1; i >= 1; i--) {
                if (p[i] != "ε") { // 空字符串不入栈
                    s.push(p[i]);
                }
            }
        }
    }

    return 0;
}*/




#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <fstream>  // 用于文件操作

using namespace std;

// 树节点结构
struct TreeNode {
    string value;
    vector<TreeNode*> children;

    TreeNode(string val) : value(val) {}

    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

void generateDot(TreeNode* node, ofstream& out, int& nodeId, int parentId = -1) {
    if (!node) return;

    int currentNodeId = nodeId++;
    out << "  " << currentNodeId << " [label=\"" << node->value << "\"];" << endl;
    if (parentId != -1) {
        out << "  " << parentId << " -> " << currentNodeId << ";" << endl;
    }

    for (auto& child : node->children) {
        generateDot(child, out, nodeId, currentNodeId);
    }
}

void createDotFile(TreeNode* root, const string& filename) {
    ofstream out(filename);
    out << "digraph SyntaxTree {" << endl;
    int nodeId = 0;
    generateDot(root, out, nodeId);
    out << "}" << endl;
    out.close();
}


// 递归函数，打印树
void printTree(const TreeNode* node, const string& prefix = "", bool isLast = true) {
    if (!node) return;

    cout << prefix << (isLast ? "└─ " : "├─ ") << node->value << endl;
    const string childPrefix = prefix + (isLast ? "   " : "│  ");
    for (size_t i = 0; i < node->children.size(); ++i) {
        printTree(node->children[i], childPrefix, i == node->children.size() - 1);
    }
}

int main() {
    set<string> nV = { "E", "E' ", "T", "T' ", "F" };
    map<string, vector<string>> table;
    // ... (填充预测分析表的代码)
    table["E,number"] = table["E,id"] = table["E,("] = { "E→TE' ", "T", "E' " };
    table["E' ,)"] = table["E' ,$"] = { "E' →ε" };
    table["E' ,+"] = { "E' →+TE' ","+","T" ,"E' " };
    table["E' ,-"] = { "E' →-TE' ","-","T", "E' " };
    table["T,number"] = table["T,id"] = table["T,("] = { "T→FT' ", "F", "T' " };
    table["T' ,)"] = table["T' ,+"] = table["T' ,-"] = table["T' ,$"] = { "T' →ε" };
    table["T' ,*"] = { "T' →*FT' ","*","F", "T' " };
    table["T' ,/"] = { "T' →/FT' ","/","F", "T' " };
    table["F,number"] = { "F→number","number" };
    table["F,id"] = { "F→id" ,"id" };
    table["F,("] = { "F→(E)","(", "E",")" };

    vector<string> w = { "id", "*", "(", "number", "+", "id", ")", "/", "number", "-", "number", "$" };
    stack<string> s;
    stack<TreeNode*> nodeStack;
    TreeNode* root = new TreeNode("E"); // 创建根节点
    s.push("$");
    s.push("E");
    nodeStack.push(root);

    int ip = 0;

    while (!s.empty()) {
        string X = s.top();
        s.pop();

        if (nodeStack.empty()) {
            cout << "错误：节点栈为空" << endl;
            break;
        }

        TreeNode* currentNode = nodeStack.top();
        nodeStack.pop();

        if (X == w[ip]) {
            cout << "匹配: " << X << endl;
            currentNode->children.push_back(new TreeNode(X)); // 添加终结符作为子节点
            ip++;
        }
        else if (nV.find(X) != nV.end()) {
            string key = X + "," + w[ip];
            if (table.find(key) != table.end()) {
                vector<string> p = table[key];
                cout << "输出: " << p[0] << endl;

                vector<TreeNode*> childNodes; // 存储子节点，以保持正确顺序

                for (int i = p.size() - 1; i >= 1; i--) {
                    if (p[i] != "ε") {
                        s.push(p[i]);
                        TreeNode* childNode = new TreeNode(p[i]);
                        childNodes.push_back(childNode); // 添加到子节点列表
                    }
                }

                // 将子节点添加到当前节点，并将它们推入节点栈
                for (auto it = childNodes.rbegin(); it != childNodes.rend(); ++it) {
                    currentNode->children.push_back(*it);
                    nodeStack.push(*it);
                }
            }
            else {
                cout << "语法错误(无适当的产生式): " << X << " 下一个符号: " << w[ip] << endl;
                break;
            }
        }
        else {
            cout << "语法错误(失配): " << w[ip] << " 期待: " << X << endl;
            break;
        }
    }


    printTree(root);

    // 在解析完成后，生成DOT文件
    createDotFile(root, "syntax_tree.dot");

    delete root;

    return 0;
}



