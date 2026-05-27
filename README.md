# Compiler Principles Course Projects

## 中文说明

本仓库包含《编译原理》课程的 3 个实验/作业项目，均为课程学习用途。

### 1) `Compiler_Principles_Lab1`
- **作业性质**：数据结构与表达式处理基础作业。
- **核心内容**：使用顺序栈实现中缀表达式转后缀表达式，并对后缀表达式进行求值。
- **解决的问题**：
  - 把人类习惯的中缀写法（如 `3+4*2`）转换成便于机器计算的后缀写法；
  - 利用栈结构完成运算符优先级处理与表达式求值流程；
  - 支持小数运算，并处理除零等基本错误场景。
- **如何启动**：
  - 打开 `Compiler_Principles_Lab1/Compiler_Principles_Lab1.sln`；
  - 在 Visual Studio 中将可执行项目设为启动项并运行（F5 / Ctrl+F5）。
- **输入是什么**：
  - 控制台输入一条算术中缀表达式（支持 `+ - * /`、括号、小数）；
  - 以 `#` 结束程序（代码中以 `#` 作为结束标记）。
  - 示例：`3.5*(2+4)-7/2`
- **输出是什么**：
  - 输出该表达式对应的**后缀表达式**；
  - 输出最终**运算结果**（浮点数）。

### 2) `Compiler_Principles_Lab2`
- **作业性质**：语法分析实验（预测分析 / LL(1) 思想）。
- **核心内容**：构造预测分析表，对输入符号串进行自顶向下语法分析，并输出语法树（DOT）。
- **解决的问题**：
  - 将文法规则程序化（分析表驱动），实现自动语法匹配；
  - 在分析过程中定位“失配”与“无产生式可用”等语法错误；
  - 生成语法树描述文件，便于可视化与调试。
- **如何启动**：
  - 打开 `Compiler_Principles_Lab2/Compiler_Principles_Project/Compiler_Principles_Lab2.sln`；
  - 运行主项目（F5 / Ctrl+F5）。
- **输入是什么**：
  - 当前代码使用预设 token 串进行分析（例如 `id * ( number + id ) / number - number`）；
  - 若要改输入，可在源码中修改 token 向量后重新运行。
- **输出是什么**：
  - 控制台输出匹配/推导过程（如 `匹配`、`输出产生式`、错误信息）；
  - 生成 `syntax_tree.dot`（可用 Graphviz 可视化）；
  - 部分版本会同时输出终端可读的树形结构。

### 3) `Compiler_Principles_Lab3`
- **作业性质**：语法分析进阶实验（含 LR 相关探索与实现代码）。
- **核心内容**：围绕算术表达式文法进行分析器实现与实验，包括分析表、输入串匹配、语法树/中间结果输出等。
- **解决的问题**：
  - 进一步理解自底向上分析（Shift/Reduce）与分析表机制；
  - 将文法、输入串、状态转移与动作执行关联起来，形成完整分析流程；
  - 通过实验文件（如 `grammar_2.txt`、`*.csv`、`token.txt`）支持多组输入与结果验证。
- **如何启动**：
  - 打开 `Compiler_Principles_Lab3/Project1/Project1.sln`；
  - 运行项目（F5 / Ctrl+F5）。
- **输入是什么**：
  - 当前主程序主要演示固定的 LR 分析步骤/表格输出（不是交互式输入）；
  - 实验数据来自项目内文法与样例文件（如 `grammar_2.txt`、`token.txt`、`*.csv`）。
- **输出是什么**：
  - 控制台按步骤输出状态栈/输入串/动作（shift、reduce、acc 等）；
  - 用于展示分析流程与结果验证，便于对照 LR 分析表。

## English Description

This repository contains three projects from a **Compiler Principles** course.

### 1) `Compiler_Principles_Lab1`
- **Type**: foundational assignment on data structures and expression processing.
- **What it does**: implements infix-to-postfix conversion and postfix evaluation using a sequential stack.
- **Problems solved**:
  - Converts human-readable infix expressions into machine-friendly postfix form;
  - Handles operator precedence and evaluation flow with a stack;
  - Supports decimal numbers and basic runtime checks (e.g., division by zero).
- **How to run**:
  - Open `Compiler_Principles_Lab1/Compiler_Principles_Lab1.sln`;
  - Set the executable project as startup project and run it (F5 / Ctrl+F5).
- **Input**:
  - A console infix arithmetic expression (`+ - * /`, parentheses, decimals supported);
  - `#` is used as the end marker.
  - Example: `3.5*(2+4)-7/2`
- **Output**:
  - The converted **postfix expression**;
  - The final numeric **evaluation result**.

### 2) `Compiler_Principles_Lab2`
- **Type**: syntax analysis lab (predictive parsing / LL(1)-style approach).
- **What it does**: builds a predictive parsing table, parses token sequences top-down, and exports a syntax tree in DOT format.
- **Problems solved**:
  - Turns grammar rules into executable parsing logic (table-driven parsing);
  - Detects syntax mismatches and missing-production cases;
  - Produces syntax tree artifacts for visualization and debugging.
- **How to run**:
  - Open `Compiler_Principles_Lab2/Compiler_Principles_Project/Compiler_Principles_Lab2.sln`;
  - Run the main project (F5 / Ctrl+F5).
- **Input**:
  - The current implementation parses a built-in token sequence (e.g., `id * ( number + id ) / number - number`);
  - To test another input, update the token vector in source code and rebuild.
- **Output**:
  - Console parsing trace (matches, productions, and possible syntax errors);
  - `syntax_tree.dot` for Graphviz-based visualization;
  - Some versions also print a readable tree in console.

### 3) `Compiler_Principles_Lab3`
- **Type**: advanced syntax analysis lab (including LR-related experiments/implementations).
- **What it does**: explores parser workflows for arithmetic-expression grammars, including parsing tables, input matching, and tree/intermediate outputs.
- **Problems solved**:
  - Deepens understanding of bottom-up parsing concepts (Shift/Reduce);
  - Connects grammar, input stream, parser states, and actions into a full pipeline;
  - Uses experiment assets (`grammar_2.txt`, `*.csv`, `token.txt`) for reproducible tests and validation.
- **How to run**:
  - Open `Compiler_Principles_Lab3/Project1/Project1.sln`;
  - Run the project (F5 / Ctrl+F5).
- **Input**:
  - The current main program mainly demonstrates a fixed LR parsing trace/table output (non-interactive);
  - Experiment assets include `grammar_2.txt`, `token.txt`, and `*.csv`.
- **Output**:
  - Step-by-step parser trace in console (state stack, remaining input, shift/reduce/accept actions);
  - Useful for understanding and validating LR parsing behavior.

## Build / Run Notes

- Main projects are Visual Studio C++ solutions (`.sln` / `.vcxproj`).
- Open each corresponding solution in Visual Studio and run the target project.
- Some projects include generated artifacts (`syntax_tree.dot`, `syntax_tree.png`) for parser visualization.

