#include "ExpressionManager.h"

ExpressionManager::ExpressionManager()
{
}

ExpressionManager::~ExpressionManager()
{
}

const string OPEN = "([{";
const string CLOSE = ")]}";
const string ExpressionManager::OPERATORS = "+-*/%";
const string ExpressionManager::PARENTHESIS = "()[]{}";

bool ExpressionManager::isOpen(char ch)
{
	return OPEN.find(ch) != string::npos;
}

bool ExpressionManager::isClose(char ch)
{
	return CLOSE.find(ch) != string::npos;
}

bool ExpressionManager::isOperator(char ch) const
{
	return OPERATORS.find(ch) != string::npos;
}

bool ExpressionManager::isParen(char ch)
{
	return PARENTHESIS.find(ch) != string::npos;
}

int ExpressionManager::evalOp(char op)
{
	// when the size of the stack is bigger or equal to 2
	// How to handle errors?
	if (operandStack.empty())
	{
		//error
		throw 1;
	}
	int rightOperand = operandStack.top();
	operandStack.pop();

	if (operandStack.empty())
	{
		throw 2;
	}
	int leftOperand = operandStack.top();
	operandStack.pop();

	int result = 0;
	switch (op)
	{
		case '+':
			result = leftOperand + rightOperand;
			break;
		case '-':
			result = leftOperand - rightOperand;
			break;
		case '*':
			result = leftOperand * rightOperand;
			break;
		case '/':
			//handle exception :: divide by 0
			if (rightOperand == 0)
			{
				throw 3;
			}
			else
			{
				result = leftOperand / rightOperand;
				break;
			}			
		case '%':
			result = leftOperand % rightOperand;
			break;
	}
	return result;
}

//Splitting strings into tokens
vector<string> ExpressionManager::parseTokens(string expression)
{
	stringstream ss(expression);
	string token;
	vector<string> tokens;
	
	while (getline(ss, token, ' '))
	{
		tokens.push_back(token);
	}
	return tokens;
}

//Part 1
bool ExpressionManager::isBalanced(string expression)
{
	stack<char> s;
	bool isBalanced = true;
	for (string::const_iterator itr = expression.begin(); isBalanced && (itr != expression.end()); ++itr)
	{
		char nextCh = *itr;
		if (isOpen(*itr))
		{
			s.push(*itr);
		}
		else if (isClose(*itr))
		{
			if (s.empty())
			{
				isBalanced = false;
			}
			else
			{
				char topCh = s.top();
				s.pop();

				//compare the index
				isBalanced = OPEN.find(topCh) == CLOSE.find(nextCh);
			}
		}
	}
	return isBalanced && s.empty();
}

//Postfix Evaluation
string ExpressionManager::postfixEvaluate(string postfixExpression)
{
	//Split the expression into vector
	//vector<string> tokens = parseTokens(postfixExpression);

	//Be sure the stack is empty
	while (!operandStack.empty())
	{
		operandStack.pop();
	}

	istringstream tokens(postfixExpression);
	char nextCh;

	while (tokens >> nextCh)
	{
		if (isdigit(nextCh))
		{
			//Last character can be once again extracted
			tokens.putback(nextCh);
			int value;
			tokens >> value;
			operandStack.push(value);
		}
		else if (isOperator(nextCh))
		{
			// Error?????????????????????????????
			int result;
			
			try
			{
				result = evalOp(nextCh);
			}
			catch (int which)
			{
				cout << "not enough operands";
				return("invalid");
			}

			//Push the result
			operandStack.push(result);
		}
		else
		{
			//Error
			return("invalid");
		}
	}

	if (!operandStack.empty())
	{
		int answer = operandStack.top();
		operandStack.pop();
		if (operandStack.empty())
		{
			//return answer as string type
			return to_string(answer);
		}
		else
		{
			//error
			return("invalid");
		}
	}
	else
	{
		//error
		return("invalid");
	}
	
}


//Part 3
string ExpressionManager::postfixToInfix(string postfixExpression)
{
	stack<string> expressionStack;

	//Be sure the stack is empty
	while (!expressionStack.empty())
	{
		expressionStack.pop();
	}
	
	//slpit the expression
	istringstream tokens(postfixExpression);
	char nextCh;

	while (tokens >> nextCh)
	{
		if (isdigit(nextCh))
		{
			tokens.putback(nextCh);
			string s;
			int i = 0;
			tokens >> s;

			bool isValid = true;

			while (s[i])
			{
				if (ispunct(s[i]))
				{
					return ("invalid");
				}
				++i;
			}

			if (isValid)
			{
				expressionStack.push(s);
			}

		}
		else if (isOperator(nextCh))
		{
			if (expressionStack.size() >= 2)
			{
				string left;
				string right;
				string result;

				//Error checking is different from the example
				right = expressionStack.top();
				expressionStack.pop();
				left = expressionStack.top();
				expressionStack.pop();

				result = "( " + left + " " + nextCh + " " + right + " )";
				expressionStack.push(result);
			}
			else
			{
				return("invalid");
			}
		}
		else
		{
			return("invalid");
		}
	}

	//Stack should have 1 element
	if (expressionStack.size() == 1)
	{
		return expressionStack.top();
	}
	else
	{
		return("invalid");
	}
}

//Part 4
string ExpressionManager::infixToPostfix(string infixExpression)
{
	string postFix;
	stack<string> operatorStack;

	if (!isBalanced(infixExpression))
	{
		return("invalid");
	}

	//Make sure it's empty at first
	while (!operatorStack.empty())
	{
		operatorStack.pop();
	}

	istringstream tokens(infixExpression);
	char nextCh;

	while (tokens >> nextCh)
	{
		//If the next token is an operand (digit)

		if (isdigit(nextCh))
		{
			tokens.putback(nextCh);
			string s;
			tokens >> s;

			//  append it to postfix (with a space following)
			postFix.append(s);
			postFix += " ";		
			//cout << postFix << endl;
		}
		else if (isOperator(nextCh) || isParen(nextCh))
		{			
			tokens.putback(nextCh);
			string strOp;
			tokens >> strOp;

			bool isValid = processOperator(operatorStack, postFix, strOp);
			
			if (!isValid)
			{
				return("invalid");
			}

		}	
		else
		{			
			return("invalid");
		}

	}


	while (!operatorStack.empty())
	{		
		postFix.append(operatorStack.top());
		operatorStack.pop();
		postFix += " ";
	}

	//erase the last space
	postFix.erase(postFix.size() - 1, 1);

	string test = postfixEvaluate(postFix);
	if (test == "invalid")
	{
		return("invalid");
	}
	else
	{
		return postFix;
	}
	//return postFix;
}

bool ExpressionManager::processOperator(stack<string>& opStack, string& postfix, string& sOp)
{
	string topStack;
	char topOfStack;
	char currentOperator = sOp[0];
	
	if (!opStack.empty())
	{
		topStack = opStack.top();
		topOfStack = topStack[0];
	}
	
	
	if (opStack.empty() || isOpen(topOfStack) || isOpen(currentOperator))
	{
		opStack.push(sOp);
		return true;
	}
	else if (isClose(currentOperator))
	{
		// When top of the stack is not a matching opening paren
		//int openIndex = OPEN.find(topOfStack);

		//while (OPEN.find(topOfStack) != CLOSE.find(currentOperator))
		char chTop;
		while (1)
		{			
			chTop = opStack.top()[0];

			if (isOpen(chTop))
			{
				if (OPEN.find(chTop) == CLOSE.find(currentOperator))
				{
					opStack.pop();
					return true;
				}
			}
			else
			{
				postfix.append(opStack.top());
				opStack.pop();
				postfix += " ";
			}
			

			//empty without finding matching paren
			if (opStack.empty())
			{
				return false;
			}
		}

		//Popping off matching paren
		//opStack.pop();
		//return true;
	}
	else
	{
		char chTop;
		while (1)
		{					
			//what if it's empty?
			if (opStack.empty())
			{
				opStack.push(sOp);
				return true;
			}
			else
			{				
				chTop = opStack.top()[0];
			}

			if (GetPrecedence(currentOperator) <= GetPrecedence(chTop))
			{
				postfix.append(opStack.top());
				opStack.pop();
				postfix += " ";
			}
			else
			{
				opStack.push(sOp);
				return true;
			}		
		}	
	}
}

int ExpressionManager::GetPrecedence(char ch)
{
	int precedence = 0;
	if (ch == '*' || ch == '/' || ch == '%')
	{
		precedence = 2;
		//return precedence;
	}
	else if (ch == '+' || ch == '-')
	{
		precedence = 1;
		//return precedence;
	}

	return precedence;
}