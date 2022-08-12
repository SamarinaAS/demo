#include "RPN.h"
int main()
{
	try
	{
	cout << "Enter an expression"<< endl;
	string l;
	cin >> l;
	double r = RPN::Calculate(l);
    cout << r << endl;
	}
	catch (const char* error)
	{
		cout<<error<<endl;
	}
}