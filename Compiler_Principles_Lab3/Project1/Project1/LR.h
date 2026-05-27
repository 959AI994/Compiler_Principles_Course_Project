#pragma once
#ifndef _LR_
#define _LR_

using namespace std;

class Grammar 
{
    public:
        // 产生式的个数
        int grammarNum;
        // 定义产生式数组
        string formula[100];

        Grammar() 
        {
            formula[0] = " ";
            formula[1] = "E->E+T";
            formula[2] = "E->E-T";
            formula[3] = "E->T";
            formula[4] = "T->T*F";
            formula[5] = "T->T/F";
            formula[6] = "T->F";
            formula[7] = "F->(E)";
            formula[8] = "F->i";
            formula[9] = "F->n";
            grammarNum = 9;
        }
};
//定义LR文法的分析表
class LRAnalyseTable 
{
    public:
        // 假设 id 用 'i' 表示，number 用 'n' 表示
        char terminalChar[100] = { '+', '*', '(', ')', 'i', 'n', '#' };
        int terNum = 7;
        char nonTerminalChar[100] = { 'E', 'T', 'F', 'X' };
        int nonTerNum = 4;
        int statusNum = 12;
        string action[12][6] = {
            {"", "", "s4", "", "s5", ""},
            {"s6", "", "", "", "", "acc"},
            {"r2", "s7", "", "r2", "", "r2"},
            {"r4", "r4", "", "r4", "", "r4"},
            {"", "", "s4", "", "s5", ""},
            {"r6", "r6", "", "r6", "", "r6"},
            {"", "", "s4", "", "s5", ""},
            {"", "", "s4", "", "s5", ""},
            {"s6", "", "", "s11", "", ""},
            {"r1", "s7", "", "r1", "", "r1"},
            {"r3", "r3", "", "r3", "", "r3"},
            {"r5", "r5", "", "r5", "", "r5"}
        };
        int goTo[12][4] = {
            {1, 2, 3, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1},
            {8, 2, 3, -1},
            {-1, -1, -1, -1},
            {-1, 9, 3, -1},
            {-1, -1, 10, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        };
        //获取终结符的索引
        int getTerminalIndex(char var) {
            for (int i = 0; i < terNum; i++) {
                if (terminalChar[i] == var) {
                    return i;
                }
            }
            return -1;
        }
        //获取非终结符的索引
        int getNonTerminalIndex(char var) {
            for (int i = 0; i < nonTerNum; i++) {
                if (nonTerminalChar[i] == var) {
                    return i;
                }
            }
            return -1;
        }
};

#endif // _LR_

