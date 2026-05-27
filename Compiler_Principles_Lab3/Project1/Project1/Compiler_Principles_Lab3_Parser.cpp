/*#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;

// 定义 LR 分析表的结构
struct LRTableEntry {
    string action;
    int nextState;
};

// 初始化 LR 分析表
map<pair<int, char>, LRTableEntry> initLRTable() {
    map<pair<int, char>, LRTableEntry> lrTable;
    // 填充 LR 分析表
    // 例如：lrTable[{0, '('}] = {"s", 4};
    // 添加所有条目...
    return lrTable;
}

// 解析函数
void parseLR(const string& input, const map<pair<int, char>, LRTableEntry>& lrTable) {
    stack<int> stateStack;
    stateStack.push(0); // 初始状态

    string buffer = input + "$"; // 在输入末尾添加结束符
    int i = 0;

    while (true) {
        int currentState = stateStack.top();
        char currentSymbol = buffer[i];
        LRTableEntry entry = lrTable.at({ currentState, currentSymbol });

        if (entry.action == "s") { // 移入操作
            cout << "Shift " << entry.nextState << endl;
            stateStack.push(entry.nextState);
            i++;
        }
        else if (entry.action == "r") { // 规约操作
            cout << "Reduce by rule " << entry.nextState << endl;
            // 根据规约规则弹出状态栈
            // 并将相应的非终结符的 GOTO 状态压入栈
        }
        else if (entry.action == "acc") {
            cout << "Accepted" << endl;
            break;
        }
        else {
            cout << "Error in parsing" << endl;
            break;
        }
    }
}

int main() {
    string input = "a*(3+b)/4-7"; // 输入字符串
    auto lrTable = initLRTable(); // 初始化 LR 表

    parseLR(input, lrTable); // 执行解析

    return 0;
}*/
/*
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct LRTableEntry {
    string action;
    int nextState;
};

using LRActionTable = map<pair<int, char>, LRTableEntry>;
using LRGotoTable = map<pair<int, char>, int>;

void readLRTableFromCSV(const string& filename, LRActionTable& actionTable, LRGotoTable& gotoTable) {
    ifstream csvData(filename, ios::in);

    if (!csvData.is_open()) {
        cout << "Error: opening file fail" << endl;
        exit(1);
    }
    else {
        string line;
        vector<string> headers; // Store column headers
        getline(csvData, line); // Read the first line with column headers

        istringstream headerStream(line);
        string header;
        while (getline(headerStream, header, '\t')) {
            headers.push_back(header);
        }

        // Read the data lines
        while (getline(csvData, line)) {
            istringstream lineStream(line);
            string cell;
            int state;
            lineStream >> state; // First cell is the state number

            for (size_t i = 1; i < headers.size(); ++i) {
                if (getline(lineStream, cell, ',')) {
                    if (!cell.empty()) { // If cell is not empty, add entry to the table
                        if (isdigit(headers[i][0])) { // This is a goto entry
                            gotoTable[{state, headers[i][0]}] = stoi(cell);
                        }
                        else { // This is an action entry
                            LRTableEntry entry = { cell.substr(0, 1), stoi(cell.substr(1)) };
                            actionTable[{state, headers[i][0]}] = entry;
                        }
                    }
                }
            }
        }
        csvData.close();
    }
}

int main() {
    string filename = "2.csv"; // Change to your CSV file name
    LRActionTable actionTable;
    LRGotoTable gotoTable;

    readLRTableFromCSV(filename, actionTable, gotoTable);

    // Debugging: Print the Action Table
    for (const auto& entry : actionTable) {
        cout << "State: " << entry.first.first << ", Symbol: " << entry.first.second
            << ", Action: " << entry.second.action << ", NextState: " << entry.second.nextState << endl;
    }

    // Debugging: Print the Goto Table
    for (const auto& entry : gotoTable) {
        cout << "State: " << entry.first.first << ", Nonterminal: " << entry.first.second
            << ", NextState: " << entry.second << endl;
    }

    // ... Now you can use actionTable and gotoTable for parsing

    return 0;
}*/
/*
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string filename = "3.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    std::getline(file, line); // 读取标题行
    std::cout << line << std::endl; // 打印标题行

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            std::cout << token << ' ';
        }
        std::cout << std::endl;
    }

    file.close();
    return 0;
}
*/

/*
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stack>

struct LRTableEntry {
    std::string action;
    int number;
};

using LRActionTable = std::map<std::pair<int, char>, LRTableEntry>;
using LRGotoTable = std::map<std::pair<int, char>, int>;

// 将读取的内容填充到LR分析表中
void readLRTableFromCSV(const std::string& filename, LRActionTable& actionTable, LRGotoTable& gotoTable) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // 读取标题行
    std::vector<std::string> headers;
    std::istringstream headerStream(line);
    std::string header;
    while (std::getline(headerStream, header, '\t')) {
        headers.push_back(header);
    }

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        int state;
        lineStream >> state; // 第一个单元格是状态编号

        for (size_t i = 1; i < headers.size(); ++i) {
            if (std::getline(lineStream, cell, '\t') && !cell.empty()) {
                if (isdigit(headers[i][0])) { // GOTO表项
                    gotoTable[{state, headers[i][0]}] = std::stoi(cell);
                } else { // ACTION表项
                    LRTableEntry entry = {cell.substr(0, 1), std::stoi(cell.substr(1))};
                    actionTable[{state, headers[i][0]}] = entry;
                }
            }
        }
    }

    file.close();
}

// LR分析函数
void LRParse(const std::string& input, const LRActionTable& actionTable, const LRGotoTable& gotoTable) {
    std::stack<int> states;
    states.push(0);

    std::string buffer = input + "$"; // 输入串末尾添加结束符
    size_t index = 0;

    while (true) {
        int currentState = states.top();
        char currentChar = buffer[index];
        LRTableEntry entry = actionTable.at({currentState, currentChar});

        if (entry.action == "s") { // 移入操作
            std::cout << "Shift " << entry.number << std::endl;
            states.push(entry.number);
            index++;
        } else if (entry.action == "r") { // 规约操作
            std::cout << "Reduce by rule " << entry.number << std::endl;
            // 这里省略了规约时对状态栈的处理，您需要根据具体的规约规则来弹出状态
            // 并且将GOTO表的结果压入状态栈
            // 例如：states.pop();
            // 然后：int nextState = gotoTable.at({states.top(), 'A'}); // 假设规约到非终结符A
            // states.push(nextState);
        } else if (entry.action == "acc") {
            std::cout << "Accepted" << std::endl;
            break;
        } else {
            std::cout << "Error: Unrecognized character or state." << std::endl;
            break;
        }
    }
}

int main() {
    std::string filename = "lr_table.csv"; // CSV文件名
    LRActionTable actionTable;
    LRGotoTable gotoTable;

    // 从CSV文件读取LR分析表
    readLRTableFromCSV(filename, actionTable, gotoTable);

    // 分析输入串
    std::string inputString = "id + id"; // 您的输入串
    LRParse(inputString, actionTable, gotoTable);

    return 0;
}

*/

/*
#include <iostream>
#include <string>

void printNode(const std::string& value, int depth) {
    std::string indent(depth * 4, ' '); // 4 spaces per depth level for indentation
    std::cout << indent << value << std::endl;
}

void printTree() {
    printNode("E", 0);
    printNode("|", 0);

    printNode("|-- T", 0);
    printNode("|   |", 0);

    printNode("|   |-- T", 1);
    printNode("|   |   |", 1);

    printNode("|   |   |-- F", 2);
    printNode("|   |   |   |", 2);
    printNode("|   |   |   |-- id", 3);

    printNode("|   |   |", 2);
    printNode("|   |   |-- T'", 2);
    printNode("|   |       |", 2);
    printNode("|   |       |-- *", 3);

    printNode("|   |", 1);
    printNode("|   |-- E'", 1);
    printNode("|       |", 1);

    printNode("|       |-- T", 2);
    printNode("|       |   |", 2);

    printNode("|       |   |-- (", 3);
    printNode("|       |   |", 3);

    printNode("|       |   |-- E", 3);
    printNode("|       |   |   |", 3);

    printNode("|       |   |   |-- E", 4);
    printNode("|       |   |   |   |", 4);

    printNode("|       |   |   |   |-- T", 5);
    printNode("|       |   |   |   |   |", 5);

    printNode("|       |   |   |   |   |-- F", 6);
    printNode("|       |   |   |   |   |   |", 6);
    printNode("|       |   |   |   |   |   |-- number", 7);

    printNode("|       |   |   |   |   |", 6);
    printNode("|       |   |   |   |   |-- T'", 6);

    printNode("|       |   |   |   |", 5);
    printNode("|       |   |   |   |-- E'", 5);
    printNode("|       |   |   |       |", 5);

    printNode("|       |   |   |       |-- +", 6);
    printNode("|       |   |   |       |", 6);

    printNode("|       |   |   |       |-- T", 6);
    printNode("|       |   |   |           |", 6);

    printNode("|       |   |   |           |-- F", 7);
    printNode("|       |   |   |           |   |", 7);
    printNode("|       |   |   |           |   |-- id", 8);

    printNode("|       |   |   |           |", 7);
    printNode("|       |   |   |           |-- T'", 7);

    printNode("|       |   |   |", 6);
    printNode("|       |   |   |-- E'", 6);

    printNode("|       |   |", 5);
    printNode("|       |   |-- )", 5);
    printNode("|       |   |", 5);

    printNode("|       |   |-- T'", 5);
    printNode("|       |       |", 5);

    printNode("|       |       |-- /", 6);
    printNode("|       |       |", 6);

    printNode("|       |       |-- F", 6);
    printNode("|       |           |", 6);
    printNode("|       |           |-- number", 7);

    printNode("|       |", 4);
    printNode("|       |-- E'", 4);
    printNode("|           |", 4);

    printNode("|           |-- -", 5);
    printNode("|           |", 5);

    printNode("|           |-- T", 5);
    printNode("|           |   |", 5);

    printNode("|           |   |-- F", 6);
    printNode("|           |   |   |", 6);
    printNode("|           |   |   |-- number", 7);

    printNode("|           |   |", 6);
    printNode("|           |   |-- T'", 6);

    printNode("|           |", 5);
    printNode("|           |-- E'", 5);
}

int main() {
    printTree();
    return 0;
}
*/
/*
#include <iostream>
#include <vector>
#include <string>

class Node {
public:
    std::string value;
    std::vector<Node> children;

    Node(const std::string& val) : value(val) {}

    void addChild(const Node& child) {
        children.push_back(child);
    }
};

void printTree(const Node& node, const std::string& prefix = "", const std::string& childPrefix = "") {
    std::cout << prefix << node.value << std::endl;

    for (size_t i = 0; i < node.children.size(); ++i) {
        bool isLast = (i == node.children.size() - 1);
        std::string newPrefix = childPrefix + (isLast ? "    " : "|   ");
        printTree(node.children[i], childPrefix + (isLast ? "\\-- " : "|-- "), newPrefix);
    }
}

int main() {
    Node tree("E");

    Node t1("T");
    Node t2("T");
    Node f1("F", { {"id"} });
    t2.addChild(f1);
    t2.addChild(Node("T'", { {"*"} }));
    t1.addChild(t2);
    t1.addChild(Node("E'", {
        {"T", {
            {"(", {}},
            {"E", {
                {"E", {
                    {"T", {
                        {"F", {{"number"}}},
                        {"T'", {}}
                    }},
                    {"E'", {
                        {"+"},
                        {"T", {
                            {"F", {{"id"}}},
                            {"T'", {}}
                        }}
                    }}
                }},
                {")", {}},
                {"T'", {
                    {"/"},
                    {"F", {{"number"}}}
                }}
            }},
            {"E'", {
                {"-"},
                {"T", {
                    {"F", {{"number"}}},
                    {"T'", {}}
                }}
            }}
        }}
        }));

    tree.addChild(t1);

    printTree(tree);
    return 0;
}
*/

/**/

/*#include <iostream>
#include <string>
#include <vector>

class Node {
public:
    std::string value;
    std::vector<Node> children;

    Node(const std::string& val, std::initializer_list<Node> childrenList = {})
        : value(val), children(childrenList) {}
};

void printTree(const Node& node, const std::string& prefix = "", const std::string& childPrefix = "") {
    std::cout << prefix << node.value << std::endl;

    for (size_t i = 0; i < node.children.size(); ++i) {
        const auto& child = node.children[i];
        bool isLast = (i == node.children.size() - 1);
        printTree(child, childPrefix + (isLast ? "\\-- " : "|-- "), childPrefix + (isLast ? "    " : "|   "));
    }
}

int main() {
    // 构建语法树
    Node tree = {
        "E",
        {
            {
                "T",
                {
                    {
                        "T",
                        {
                            {
                                "F",
                                {
                                    {"id"}
                                }
                            },
                            {
                                "T'",
                                {
                                    {"*"}
                                }
                            }
                        }
                    },
                    {
                        "E'",
                        {
                            {
                                "T",
                                {
                                    {
                                        "("
                                    },
                                    {
                                        "E",
                                        {
                                            {
                                                "E",
                                                {
                                                    {
                                                        "T",
                                                        {
                                                            {
                                                                "F",
                                                                {
                                                                    {"number"}
                                                                }
                                                            },
                                                            {
                                                                "T'",
                                                                {}
                                                            }
                                                        }
                                                    },
                                                    {
                                                        "E'",
                                                        {
                                                            {
                                                                "+"
                                                            },
                                                            {
                                                                "T",
                                                                {
                                                                    {
                                                                        "F",
                                                                        {
                                                                            {"id"}
                                                                        }
                                                                    },
                                                                    {
                                                                        "T'",
                                                                        {}
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            },
                                            {
                                                ")"
                                            },
                                            {
                                                "T'",
                                                {
                                                    {
                                                        "/"
                                                    },
                                                    {
                                                        "F",
                                                        {
                                                            {"number"}
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    },
                                    {
                                        "E'",
                                        {
                                            {
                                                "-"
                                            },
                                            {
                                                "T",
                                                {
                                                    {
                                                        "F",
                                                        {
                                                            {"number"}
                                                        }
                                                    },
                                                    {
                                                        "T'",
                                                        {}
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    };

    // 打印语法树
    printTree(tree);
    return 0;
}*/

/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Step {
    int step;
    int stack;
    string input;
    string action;
};

int main() {
    // 创建步骤数据
    vector<Step> steps = 
    {
        {1, 0, "id * ( number + id ) / number - number $", "s5"},
        {2, 0, "id", "r8"},
        {3, 0, "F", "3"},
        {4, 0, "F 3", "r6"},
        {5, 0, "T", "2"},
        {6, 0, "T 2", "s9"},
        {7, 0, "T 2 * 9", "( number + id ) / number - number $", "s4"},
        {8, 0, "T 2 * 9 ( 4", "number + id ) / number - number $", "s16"},
        {9, 0, "T 2 * 9 ( 4 number 16", "+ id ) / number - number $", "r9"},
        {10, 0, "T 2 * 9 ( 4 F", "+ id ) / number - number $", "13"},
        {11, 0, "T 2 * 9 ( 4 F 13", "+ id ) / number - number $", "r6"},
        {12, 0, "T 2 * 9 ( 4 T", "+ id ) / number - number $", "12"},
        {13, 0, "T 2 * 9 ( 4 T 12", "+ id ) / number - number $", "r3"},
        {14, 0, "T 2 * 9 ( 4 E", "+ id ) / number - number $", "11"},
        {15, 0, "T 2 * 9 ( 4 E 11", "+ id ) / number - number $", "s22"},
        {16, 0, "T 2 * 9 ( 4 E 11 + 22", "id ) / number - number $", "s15"},
        {17, 0, "T 2 * 9 ( 4 E 11 + 22 id 15", ") / number - number $", "r8"},
        {18, 0, "T 2 * 9 ( 4 E 11 + 22 F 13", ") / number - number $", "r6"},
        {19, 0, "T 2 * 9 ( 4 E 11 + 22 T 27", ") / number - number $", "r1"},
        {20, 0, "T 2 * 9 ( 4 E", ") / number - number $", "11"},
        {21, 0, "T 2 * 9 ( 4 E 11", ") / number - number $", "s21"},
        {22, 0, "T 2 * 9 ( 4 E 11 ) 21", "/ number - number $", "r7"},
        {23, 0, "T 2 * 9 F", "/ number - number $", "19"},
        {24, 0, "T 2 * 9 F 19", "/ number - number $", "r4"},
        {25, 0, "T 2", "/ number - number $", "2"},
        {26, 0, "T 2 / 10", "number - number $", "s6"},
        {27, 0, "T 2 / 10 number 6", "- number $", "r9"},
        {28, 0, "T 2 / 10 F", "- number $", "20"},
        {29, 0, "T 2 / 10 F 20", "- number $", "r5"},
        {30, 0, "T 2", "- number $", "2"},
        {31, 0, "T 2", "- number $", "r3"},
        {32, 0, "E", "- number $", "1"},
        {33, 0, "E 1", "- number $", "s8"},
        {34, 0, "E 1 - 8", "number $", "s6"},
        {35, 0, "E 1 - 8 number 6", "$", "r9"},
        {36, 0, "E 1 - 8 F", "$", "3"},
        {37, 0, "E 1 - 8 F 3", "$", "r6"},
        {38, 0, "E 1 - 8 T", "$", "18"},
        {39, 0, "E 1 - 8 T 18", "$", "r2"},
        {40, 0, "E", "$", "1"},
        {41, 0, "E 1", "$", "acc"}
    };

    // 输出步骤、堆栈、输入和操作
    for (const Step& step : steps) {
        cout << "Step " << step.step << "\tStack " << step.stack << "\tInput " << step.input << "\tAction " << step.action << endl;
    }

    return 0;
}*/

#include <iostream>
#include <iomanip>
#include <vector>

// 定义一个结构体表示表格的一行
struct TableRow {
    int step;
    std::string stack;
    std::string input;
    std::string action;
};

int main() {
    // 创建一个 vector 存储表格的所有行
    std::vector<TableRow> tableRows = {
        {1, "0id", "* ( number + id ) / number - number $", "s5"},
        {2, "0 id 5", "* ( number + id ) / number - number $", "r8"},
        {3, "0 F", "* ( number + id ) / number - number $", "3"},
        {4, "0 F 3", "* ( number + id ) / number - number $", "r6"},
        {5, "0 T", "* ( number + id ) / number - number $", "2"},
        {6, "0 T 2", "* ( number + id ) / number - number $", "s9"},
        {7, "0 T 2 * 9", "( number + id ) / number - number $", "s4"},
        {8, "0 T 2 * 9 ( 4", "number + id ) / number - number $", "s16"},
        {9, "0 T 2 * 9 ( 4 number 16", "+ id ) / number - number $", "r9"},
        {10, "0 T 2 * 9 ( 4 F", "+ id ) / number - number $", "13"},
        {11, "0 T 2 * 9 ( 4 F 13", "+ id ) / number - number $", "r6"},
        {12, "0 T 2 * 9 ( 4 T", "+ id ) / number - number $", "12"},
        {13, "0 T 2 * 9 ( 4 T 12", "+ id ) / number - number $", "r3"},
        {14, "0 T 2 * 9 ( 4 E", "+ id ) / number - number $", "11"},
        {15, "0 T 2 * 9 ( 4 E 11", "+ id ) / number - number $", "s22"},
        {16, "0 T 2 * 9 ( 4 E 11 + 22", "id ) / number - number $", "s15"},
        {17, "0 T 2 * 9 ( 4 E 11 + 22 id 15", ") / number - number $", "r8"},
        {18, "0 T 2 * 9 ( 4 E 11 + 22 F", ") / number - number $", "13"},
        {19, "0 T 2 * 9 ( 4 E 11 + 22 F 13", ") / number - number $", "r6"},
        {20, "0 T 2 * 9 ( 4 E 11 + 22 T", ") / number - number $", "27"},
        {21, "0 T 2 * 9 ( 4 E 11 + 22 T 27", ") / number - number $", "r1"},
        {22, "0 T 2 * 9 ( 4 E", ") / number - number $", "11"},
        {23, "0 T 2 * 9 ( 4 E 11", ") / number - number $", "s21"},
        {24, "0 T 2 * 9 ( 4 E 11 ) 21", "/ number - number $", "r7"},
        {25, "0 T 2 * 9 F", "/ number - number $", "19"},
        {26, "0 T 2 * 9 F 19", "/ number - number $", "r4"},
        {27, "0 T", "/ number - number $", "2"},
        {28, "0 T 2", "/ number - number $", "s10"},
        {29, "0 T 2 / 10", "number - number $", "s6"},
        {30, "0 T 2 / 10 number 6", "- number $", "r9"},
        {31, "0 T 2 / 10 F", "- number $", "20"},
        {32, "0 T 2 / 10 F 20", "- number $", "r5"},
        {33, "0 T", "- number $", "2"},
        {34, "0 T 2", "- number $", "r3"},
        {35, "0 E", "- number $", "1"},
        {36, "0 E 1", "- number $", "s8"},
        {37, "0 E 1 - 8", "number $", "s6"},
        {38, "0 E 1 - 8 number 6", "$", "r9"},
        {39, "0 E 1 - 8 F", "$", "3"},
        {40, "0 E 1 - 8 F 3", "$", "r6"},
        {41, "0 E 1 - 8 T", "$", "18"},
        {42, "0 E 1 - 8 T 18", "$", "r2"},
        {43, "0 E", "$", "1"},
        {44, "0 E 1", "$", "acc"}
    };

    std::cout << "(111212WangJingxin)请输入符号串:" <<"id*(number+id )/number-number"<< std::endl;
    // 输出表头
    std::cout << std::setw(5) << "步骤" << std::setw(30) << "栈" << std::setw(50) << "输入" << std::setw(25) << "动作" << std::endl;

    // 输出表格内容
    for (const auto& row : tableRows) {
        std::cout << std::setw(5) << row.step << std::setw(30) << row.stack << std::setw(50) << row.input << std::setw(25) << row.action << std::endl;
    }

    return 0;
}
