# Compiler Principles Course Projects

## 中文说明

本仓库包含《编译原理》课程的 3 个实验/作业项目，均为课程学习用途。

### 1) `Compiler_Principles_Homework`
- **作业性质**：数据结构与表达式处理基础作业。
- **核心内容**：使用顺序栈实现中缀表达式转后缀表达式，并对后缀表达式进行求值。
- **解决的问题**：
  - 把人类习惯的中缀写法（如 `3+4*2`）转换成便于机器计算的后缀写法；
  - 利用栈结构完成运算符优先级处理与表达式求值流程；
  - 支持小数运算，并处理除零等基本错误场景。

### 2) `Compiler_Principles_Lab2`
- **作业性质**：语法分析实验（预测分析 / LL(1) 思想）。
- **核心内容**：构造预测分析表，对输入符号串进行自顶向下语法分析，并输出语法树（DOT）。
- **解决的问题**：
  - 将文法规则程序化（分析表驱动），实现自动语法匹配；
  - 在分析过程中定位“失配”与“无产生式可用”等语法错误；
  - 生成语法树描述文件，便于可视化与调试。

### 3) `Compiler_Principles_Lab3`
- **作业性质**：语法分析进阶实验（含 LR 相关探索与实现代码）。
- **核心内容**：围绕算术表达式文法进行分析器实现与实验，包括分析表、输入串匹配、语法树/中间结果输出等。
- **解决的问题**：
  - 进一步理解自底向上分析（Shift/Reduce）与分析表机制；
  - 将文法、输入串、状态转移与动作执行关联起来，形成完整分析流程；
  - 通过实验文件（如 `grammar_2.txt`、`*.csv`、`token.txt`）支持多组输入与结果验证。

## English Description

This repository contains three projects from a **Compiler Principles** course.

### 1) `Compiler_Principles_Homework`
- **Type**: foundational assignment on data structures and expression processing.
- **What it does**: implements infix-to-postfix conversion and postfix evaluation using a sequential stack.
- **Problems solved**:
  - Converts human-readable infix expressions into machine-friendly postfix form;
  - Handles operator precedence and evaluation flow with a stack;
  - Supports decimal numbers and basic runtime checks (e.g., division by zero).

### 2) `Compiler_Principles_Lab2`
- **Type**: syntax analysis lab (predictive parsing / LL(1)-style approach).
- **What it does**: builds a predictive parsing table, parses token sequences top-down, and exports a syntax tree in DOT format.
- **Problems solved**:
  - Turns grammar rules into executable parsing logic (table-driven parsing);
  - Detects syntax mismatches and missing-production cases;
  - Produces syntax tree artifacts for visualization and debugging.

### 3) `Compiler_Principles_Lab3`
- **Type**: advanced syntax analysis lab (including LR-related experiments/implementations).
- **What it does**: explores parser workflows for arithmetic-expression grammars, including parsing tables, input matching, and tree/intermediate outputs.
- **Problems solved**:
  - Deepens understanding of bottom-up parsing concepts (Shift/Reduce);
  - Connects grammar, input stream, parser states, and actions into a full pipeline;
  - Uses experiment assets (`grammar_2.txt`, `*.csv`, `token.txt`) for reproducible tests and validation.

## Build / Run Notes

- Main projects are Visual Studio C++ solutions (`.sln` / `.vcxproj`).
- Open each corresponding solution in Visual Studio and run the target project.
- Some projects include generated artifacts (`syntax_tree.dot`, `syntax_tree.png`) for parser visualization.

