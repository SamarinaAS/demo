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
	string output; //Строка для хранения выражения//?!
	int size = input.length();
	Stack<char> operStack(size); //Стек для хранения операторов

	for (int i = 0; i < input.length(); i++) //Для каждого символа во входной строке
	{
		//Разделители пропускаем
		if (IsDelimeter(input[i]))//ЗАМЕНИТЬ ЦИКЛОМ?!
			continue; //Переходим к следующему символу
		 
		//Если символ - цифра, то считываем все число
		if (isdigit(input[i])) //Если цифра
		{
			//Читаем до разделителя или оператора, что бы получить число
			while ((IsDelimeter(input[i])!=true) && (!IsOperator(input[i])))
			{
				output += input[i]; //Добавляем каждую цифру числа к нашей строке
				i++; //Переходим к следующему символу

				if (i == input.length()) 
					break; //Если символ - последний, то выходим из цикла
			}

			output += " "; //Дописываем после числа пробел в строку с выражением
			i--; //ЗАЧЕМ?!Возвращаемся на один символ назад, к символу перед разделителем
		}

		//Если символ - оператор
		if (IsOperator(input[i])) //Если оператор
			if (input[i] == '(') //Если символ - открывающая скобка
				operStack.push(input[i]); //Записываем её в стек
			else 
				if (input[i] == ')') //Если символ - закрывающая скобка
				{
					//Выписываем все операторы до открывающей скобки в строку
					char s = operStack.pop();

					while (s != '(')
					{
						output.push_back(s);
						output += " ";
						//output += s.ToString() + ' '; //?!
						s = operStack.pop();
					}
				}
				else //Если любой другой оператор!!!ИЗМЕНЕНО!
				{
					//if ((operStack.getTop() > -1)) //Если в стеке есть элементы
						while ((operStack.getTop() > -1) && (GetPriority(input[i]) <= GetPriority(operStack.Peek()))) //И если приоритет нашего оператора меньше или равен приоритету оператора на вершине стека
						{
							output.push_back(operStack.pop());
							output += " ";
						}
						operStack.push(input[i]);
				}//Если стек пуст, или же приоритет оператора выше - добавляем операторов на вершину стека

				if ((islower(input[i])) || isupper(input[i])) //Если буква
				{
					//Читаем до разделителя или оператора, что бы получить букву
					while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true))
					{
						output += input[i]; //Добавляем каждую букву переменной к нашей строке
						i++; //Переходим к следующему символу

						if (i == input.length()) 
							break; //Если символ - последний, то выходим из цикла
					}

					output += " "; //Дописываем после числа пробел в строку с выражением
					i--;

				}
	}

	//Когда прошли по всем символам, выкидываем из стека все оставшиеся там операторы в строку
	while (operStack.getTop() > -1)
	{
		output.push_back(operStack.pop());
		output += " ";
	}
	/*output += operStack.pop() + " ";*/
	return output; //Возвращаем выражение в постфиксной записи
}

double RPN::Counting(string input)
{
    double result = 0; //Результат
    Stack<double> temp(input.length()); //Dhtvtyysq стек для решения

    for (int i = 0; i < input.length(); i++) //Для каждого символа в строке
    {
        //Если символ - цифра, то читаем все число и записываем на вершину стека
        if (isdigit(input[i])) 
        {
            string a;
			double b;
            while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true)) //Пока не разделитель
            {
                a += input[i]; //Добавляем
                i++;
                if (i == input.length()) break;
            }
			istringstream(a) >> b;
            temp.push(b); //Записываем в стек
			i--;
            
        }
        else if (IsOperator(input[i])) //Если символ - оператор
        {
            //Берем два последних значения из стека
            double a = temp.pop(); 
            double b = temp.pop();

            switch (input[i]) //И производим над ними действие, согласно оператору
            { 
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
                case '^': result = pow(b,a); break;
            }

            temp.push(result); //Результат вычисления записываем обратно в стек
        }
    }
    return temp.Peek(); //Забираем результат всех вычислений из стека и возвращаем его
}

double RPN::Calculate(string input)
{
	cout << input << endl;
	string polish = GetExpression(input);
	cout << polish << endl;
    string output = InsertValue(polish);//Преобразовываем выражение в постфиксную запись и замена переменных
    double result = Counting(output); //Решаем полученное выражение
    return result; //Возвращаем результат
}

string RPN::InsertValue(string input/*, string variables*/)
{
	bool flag = false;
	string output;
	string var;
	for (int i = 0; i < input.length(); i++) //Для каждого символа во входной строке
	{
		string variable;
		if ((islower(input[i])) || isupper(input[i])) //Если буква
		{
			flag = true;
			//Читаем до разделителя или оператора, что бы получить букву
			do
			{
				variable += input[i];
				++i;
				if (i == input.length()) 
					break; //Если символ - последний, то выходим из цикла
			}
			while ((IsDelimeter(input[i])!=true) && (IsOperator(input[i])!=true));
			
			cout << "Enter the value of variable " << variable <<endl;
			cin >> var;

			output += var + " " ; //Дописываем после числа пробел в строку с выражением
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