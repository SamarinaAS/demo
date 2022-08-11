#include "stack.h"
#include <string>
#include <cstring>
#include <cctype>
#include <sstream> 
#include <cmath>
using namespace std;

class RPN//Reverse Polish Notation
{
public:
	static double Calculate(string input);
	string GetPolish();
	// функция заполнения значений переменных
private:
	// массив позиций переменных
	// массив значений переменных
	static string GetExpression(string input);
	static string InsertValue(string input);
	static double Counting(string input);
	static bool IsDelimeter(char c);
	static bool IsOperator(char с);
	static short unsigned int GetPriority(char s);
};