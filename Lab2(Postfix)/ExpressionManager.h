#pragma once
#include "ExpressionManagerInterface.h"
#include <vector>
#include <sstream>


class ExpressionManager : public ExpressionManagerInterface
{
public:
	ExpressionManager();
	virtual ~ExpressionManager();

	bool isBalanced(string expression);

	string postfixToInfix(string postfixExpression);

	string postfixEvaluate(string postfixExpression);

	string infixToPostfix(string infixExpression);

	//Helper functions
	bool isOpen(char ch);
	bool isClose(char ch);
	bool isParen(char ch);

	vector<string> parseTokens(string expression);
	bool processOperator(stack<string>& opStack, string& postfix, string& sOp);
	int GetPrecedence(char ch);

private:
	int evalOp(char op);
	bool isOperator(char ch) const;
	static const string OPERATORS;
	static const string PARENTHESIS;
	stack<int> operandStack;
};

