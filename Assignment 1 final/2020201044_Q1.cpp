#include <iostream>
#include <sstream>
#include <string>
#include<iomanip>

using namespace std;

int n;

template <class T>
class st
{
public:
    T *arr;
    int top = -1;

    st()
    {
        // cout << "Creating a stack..." << endl;
        arr = new T[n];
    }

    void push(const T &x)
    {
        if (top == n - 1)
        {
            //   cout << "Stack overflow" << endl;
            return;
        }

        //cout << "Pushing " << x << " to stack..." << endl;
        arr[++top] = x;
    }

    T pop()
    {
        if (top == -1)
        {
            //  cout << "Stack is empty" << endl;
            return -1;
        }
        //cout << "Popping " << arr[top] << " from stack..." << endl;
        return arr[top--];
    }

    void print()
    {

        if (top == -1)
        {
            //cout << "Stack is empty" << endl;
            return;
        }
        cout << "Elements of stack are:" << endl;
        for (int i = 0; i <= top; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    bool isEmpty()
    {
        if (top == -1)
            return true;
        return false;
    }

    T peek()
    {
        if (top == -1)
        {
            //     cout << "Stack is empty" << endl;
            return -1;
        }
        return arr[top];
    }
};

int precedence(char op)
{
    int p;
    if (op == '%' || op == '/' || op == '*')
        p = 2;
    else if (op == '+' || op == '-')
        p = 1;
    return p;
}

//((1+1.3)*4.555)/3

long double performOperation(long double a, long double b, char op)
{
    double result;
    if (op == '*')
        result = a * b;
    else if (op == '/')
        result = a / b;
    else if (op == '%')
        result = (long int)a % (long int)b;
    else if (op == '+')
        result = a + b;
    else if (op == '-')
        result = a - b;
    return result;
}

void replace(string &str, char a, char b)
{
    int n = str.length();
    for (int i = 0; i < n; i++)
    {
        if (str[i] == a)
            str[i] = b;
    }
}

int main()
{

    string expr;
    char ch;
    //int t=100;
    //while(t--){
    getline(cin, expr);
    replace(expr, '{', '(');
    replace(expr, '[', '(');
    replace(expr, '}', ')');
    replace(expr, ']', ')');

    //cout<<"String is: " <<expr<<endl;

    n = expr.size();

    st<long double> operand;
    st<char> operation;

    //values that expr has are numbers, . , + , - , % , / , ( , )

    for (int i = 0; i < expr.size(); i++)
    {
        ch = expr[i];
        if (isdigit(ch))
        {
            string decimalVal = "";
            while (isdigit(expr[i]))
            {
                decimalVal += expr[i];
                i++;
            }
            i--;
            operand.push(stod(decimalVal));
        }

        else if (ch == '(')
        {
            operation.push(ch);
        }

        else if (ch == ')')
        {
            while (operation.peek() != '(')
            {
                long double b = operand.pop();
               long double a = operand.pop();
                char op = operation.pop();
                long double result = performOperation(a, b, op);
                operand.push(result);
            }
            operation.pop();
        }

        else if (ch == '.')
        {
            int decimal = (int)(operand.pop());
            string dec = to_string(decimal) + ".";

            i++;

            while (isdigit(expr[i]))
            {
                dec += expr[i];
                i++;
            }
            i--;
            operand.push(stod(dec));
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '%' || ch == '/')
        {

            while (precedence(ch) <= precedence(operation.peek()) && !operation.isEmpty() && operation.peek() != '(')
            {
                long double b = operand.pop();
                long double a = operand.pop();
                char op = operation.pop();
                long double result = performOperation(a, b, op);
                operand.push(result);
            }
            operation.push(ch);
        }
    }

    //end operations in the stack
    while (!operation.isEmpty())
    {
        long double b = operand.pop();
        long double a = operand.pop();
        char op = operation.pop();
        long double result = performOperation(a, b, op);
        operand.push(result);
    }
   printf("%.5Lf\n",operand.pop()); 
   // }
    return 0;
}