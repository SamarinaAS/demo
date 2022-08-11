#include "RPN.h"
int main()
{
	try
	{
	cout << "Enter an expression"<< endl;
	string l;
	cin >> l;
	double r = RPN::Calculate(l);//Неправильно считает!
    cout << r << endl;
	//Stack<char> s(7);
	//s.push('c');
	//s.pop();
	//return 0;
	}
	catch (const char* error)
	{
		cout<<error<<endl;
	}
}