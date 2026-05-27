//顺序栈，中缀转后缀并计算后缀表达式，可处理小数但不能处理负数
#include<iostream>
#include<assert.h>
#include<math.h>
#include<string>
#include<map>
using namespace std;

//栈的类定义
const int maxSize = 50;
template<class T>
class Stack
{
public:
	Stack() {};
	virtual void Push(const T& x) = 0;
	virtual bool Pop(T& x) = 0;
	virtual bool getTop(T& x)const = 0;
	virtual bool IsEmpty()const = 0;
	virtual bool IsFull()const = 0;
	virtual int getSize()const = 0;//计算栈中元素个数
};

//顺序栈的类定义
const int stackIncreament = 20;//栈溢出时扩展空间的增量
template<class T>
class SeqStack :public Stack<T>
{
private:
	T* elements;//存放栈中元素的栈数组
	int top;
	int maxSize;
	void overflowProcess();
public:
	SeqStack(int sz = 50);
	~SeqStack() { delete[] elements; };
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x)const;
	bool IsEmpty()const { return (top == -1) ? true : false; }
	bool IsFull()const { return (top == maxSize - 1) ? true : false; }
	int getSize()const { return top + 1; }
	void MakeEmpty() { top = -1; }
	friend ostream& operator<<(ostream& os, SeqStack<T>& s);
};
template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements != NULL);
}

template<class T>
void SeqStack<T>::overflowProcess()
{
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == NULL)
	{
		cerr << "存储分配失败!" << endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete[]elements;
	elements = newArray;
}

template<class T>
void SeqStack<T>::Push(const T& x)
{
	if (IsFull())
		overflowProcess();
	elements[++top] = x;
}

template<class T>
bool SeqStack<T>::Pop(T& x)
{
	if (IsEmpty())
		return false;
	x = elements[top--];
	return true;
}

template<class T>
bool SeqStack<T>::getTop(T& x)const
{
	if (IsEmpty())
		return false;
	x = elements[top];
	return true;
}

template<class T>
ostream& operator<<(ostream& os, SeqStack<T>& s)
{
	os << "top=" << s.top << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":" << s.elements[i] << endl;
	return os;
}


class Calculator//利用顺序栈构建一个计算器,采用中缀转后缀表达式方法计算
{
public:
	Calculator(int sz) :s(sz)
	{
		isp['#'] = 0;
		isp['('] = 1;
		isp['*'] = 5;
		isp['/'] = 5;
		isp['+'] = 3;
		isp['-'] = 3;
		isp[')'] = 6;
		icp['#'] = 0;
		icp['('] = 6;
		icp['*'] = 4;
		icp['/'] = 4;
		icp['+'] = 2;
		icp['-'] = 2;
		icp[')'] = 1;
	}
	void Run();
	void Clear() { s.MakeEmpty(); }
private:
	map<char, int>isp, icp;//操作符的栈内、栈外优先级，用map表示
	SeqStack<double>s;
	void AddOperand(double value) { s.Push(value); }//进操作数栈
	bool getTwoOperands(double& left, double& right);//从栈中退出两个操作数
	void DoOperator(char op);//形成运算指令，进行运算
	string postfix(string expression);
};
bool Calculator::getTwoOperands(double& left, double& right)
{
	if (s.getSize() < 2)
	{
		cout << "栈内操作数少于两个！" << endl;
		return false;
	}
	s.Pop(right);//注意由于栈的特性，右操作数在左操作数上方
	s.Pop(left);
	return true;
}
void Calculator::DoOperator(char op)
{
	double left, right, value;
	bool successGet = getTwoOperands(left, right);
	if (successGet)
	{
		switch (op)//加减乘除操作
		{
		case'+':
			value = left + right;
			s.Push(value);
			break;
		case'-':
			value = left - right;
			s.Push(value);
			break;
		case'*':
			value = left * right;
			s.Push(value);
			break;
		case'/':
			if (right == 0.0)
			{
				cout << "除数为0！" << endl;
				Clear();
			}
			else
			{
				value = left / right;
				s.Push(value);
			}
			break;
		}
	}
	else
		Clear();
}
void Calculator::Run()//计算后缀表达式
{
	string expression;
	while (cin >> expression, expression != "#")
	{
		expression += '#';
		expression = postfix(expression);//表达式由中缀表达式变为后缀表达式

		cout << "后缀表达式: " << expression << endl;  // Print the postfix expression

		char ch;
		double newOperand;
		for (int i = 0, ch = expression[0]; ch != '#' && i < expression.length(); i++, ch = expression[i])
		{
			if (ch == ' ')
				continue;
			switch (ch)
			{
			case'+':case'-':case'*':case'/'://若为运算符
				DoOperator(ch);
				break;
			default://若为数字
				int end = i + 1;
				for (; (isdigit(expression[end]) || expression[end] == '.') && expression[end] != '#'; end++);
				newOperand = stod(expression.substr(i, end - i));
				i = end;//已经读过的内容不必再读，更新游标
				AddOperand(newOperand);
			}
		}
		double result;
		s.getTop(result);
		cout << "运算结果：" << result << endl;
		Clear();
	}
}
string Calculator::postfix(string expression)//中缀转后缀表达式
{
	SeqStack<char>s1;
	char ch, ch1, op;
	string str = "";
	s1.Push('#');
	for (int i = 0; !s1.IsEmpty() && i < expression.length();)
	{
		ch = expression[i];
		if (isdigit(ch) || ch == '.')
		{
			while (isdigit(ch) || ch == '.')
			{
				str += ch;
				i++;
				ch = expression[i];
			}
			str += ' ';
		}
		else
		{
			s1.getTop(ch1);
			if (isp[ch1] < icp[ch])//新操作符优先级高，入栈，游标右移
			{
				s1.Push(ch);
				i++;
			}
			else if (isp[ch1] > icp[ch])//新操作符优先级低，出栈，游标不变
			{
				s1.Pop(op);
				str += op;
				str += ' ';
			}
			else//栈内外优先数相等的只有与'('和')'
			{
				s1.Pop(op);
				if (op == '(')
					i++;
			}
		}
	}
	str += '#';
	return str;
}
int main()
{
	cout << "请输入算数表达式，若想停止输入，请输入“#”。（请使用英文输入法，支持小数运算）" << endl;
	Calculator calculator(50);
	calculator.Run();
	return 0;
}
