#include "RPN.h"

#define MAX 100

bool RPN::IsDelimeter(char c)
{

	char* delimeter = " =";
	char* pos = strchr(delimeter, c);
	if (pos != NULL)
		return true;
	return false;
}

bool RPN::IsOperator(char c)
{
	char* operators = "+-/*^()";
	char * pos = strchr(operators, c);
	if ((pos != NULL))
		return true;
	return false;
}

short unsigned int RPN::GetPriority(char s)
{
	switch (s)
	{
	case '(': return 0;
	case ')': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 4;
	case '/': return 4;
	case '^': return 5;
	default: return 6;//?!
	}
}

string RPN::GetExpression(string input)
{
	string output; //������ ��� �������� ���������//?!
	int size = input.length();
	Stack<char> operStack(size); //���� ��� �������� ����������

	for (int i = 0; i < input.length(); i++) //��� ������� ������� �� ������� ������
	{
		//����������� ����������
		if (IsDelimeter(input[i]))//�������� ������?!
			continue; //��������� � ���������� �������
		 
		//���� ������ - �����, �� ��������� ��� �����
		if (isdigit(input[i])) //���� �����
		{
			//������ �� ����������� ��� ���������, ��� �� �������� �����
			while ((IsDelimeter(input[i])!=true) && (!IsOperator(input[i])))
			{
				output += input[i]; //��������� ������ ����� ����� � ����� ������
				i++; //��������� � ���������� �������

				if (i == input.length()) 
					break; //���� ������ - ���������, �� ������� �� �����
			}

			output += " "; //���������� ����� ����� ������ � ������ � ����������
			i--; //�����?!������������ �� ���� ������ �����, � ������� ����� ������������
		}

		//���� ������ - ��������
		if (IsOperator(input[i])) //���� ��������
			if (input[i] == '(') //���� ������ - ����������� ������
				operStack.push(input[i]); //���������� � � ����
			else 
				if (input[i] == ')') //���� ������ - ����������� ������
				{
					//���������� ��� ��������� �� ����������� ������ � ������
					char s = operStack.pop();

					while (s != '(')
					{
						output.push_back(s);
						output += " ";
						//output += s.ToString() + ' '; //?!
						s = operStack.pop();
					}
				}
				else //���� ����� ������ ��������!!!��������!
				{
					//if ((operStack.getTop() > -1)) //���� � ����� ���� ��������
						while ((operStack.getTop() > -1) && (GetPriority(input[i]) <= GetPriority(operStack.Peek()))) //� ���� ��������� ������ ��������� ������ ��� ����� ���������� ��������� �� ������� �����
						{
							output.push_back(operStack.pop());
							output += " ";
						}
						operStack.push(input[i]);
				}//���� ���� ����, ��� �� ��������� ��������� ���� - ��������� ���������� �� ������� �����

				if ((islower(input[i])) || isupper(input[i])) //���� �����
				{
					//������ �� ����������� ��� ���������, ��� �� �������� �����
					while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true))
					{
						output += input[i]; //��������� ������ ����� ���������� � ����� ������
						i++; //��������� � ���������� �������

						if (i == input.length()) 
							break; //���� ������ - ���������, �� ������� �� �����
					}

					output += " "; //���������� ����� ����� ������ � ������ � ����������
					i--;

				}
	}

	//����� ������ �� ���� ��������, ���������� �� ����� ��� ���������� ��� ��������� � ������
	while (operStack.getTop() > -1)
	{
		output.push_back(operStack.pop());
		output += " ";
	}
	/*output += operStack.pop() + " ";*/
	return output; //���������� ��������� � ����������� ������
}

double RPN::Counting(string input)
{
    double result = 0; //���������
    Stack<double> temp(input.length()); //Dhtvtyysq ���� ��� �������

    for (int i = 0; i < input.length(); i++) //��� ������� ������� � ������
    {
        //���� ������ - �����, �� ������ ��� ����� � ���������� �� ������� �����
        if (isdigit(input[i])) 
        {
            string a;
			double b;
            while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true)) //���� �� �����������
            {
                a += input[i]; //���������
                i++;
                if (i == input.length()) break;
            }
			istringstream(a) >> b;
            temp.push(b); //���������� � ����
			i--;
            
        }
        else if (IsOperator(input[i])) //���� ������ - ��������
        {
            //����� ��� ��������� �������� �� �����
            double a = temp.pop(); 
            double b = temp.pop();

            switch (input[i]) //� ���������� ��� ���� ��������, �������� ���������
            { 
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
                case '^': result = pow(b,a); break;
            }

            temp.push(result); //��������� ���������� ���������� ������� � ����
        }
    }
    return temp.Peek(); //�������� ��������� ���� ���������� �� ����� � ���������� ���
}

double RPN::Calculate(string input)
{
	cout << input << endl;
	string polish = GetExpression(input);
	cout << polish << endl;
    string output = InsertValue(polish);//��������������� ��������� � ����������� ������ � ������ ����������
    double result = Counting(output); //������ ���������� ���������
    return result; //���������� ���������
}

string RPN::InsertValue(string input/*, string variables*/)
{
	bool flag = false;
	string output;
	string var;
	for (int i = 0; i < input.length(); i++) //��� ������� ������� �� ������� ������
	{
		string variable;
		if ((islower(input[i])) || isupper(input[i])) //���� �����
		{
			flag = true;
			//������ �� ����������� ��� ���������, ��� �� �������� �����
			do
			{
				variable += input[i];
				++i;
				if (i == input.length()) 
					break; //���� ������ - ���������, �� ������� �� �����
			}
			while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true));
			
			cout << "Enter the value of variable " << variable <<endl;
			cin >> var;

			output += var + " " ; //���������� ����� ����� ������ � ������ � ����������
			i--;
		}
		else
		{
			if (i == (input.length()-1)) 
					break;
			output += input[i];
		}
	}
	//if (flag == false)
	//	output = input;
	return output;
}