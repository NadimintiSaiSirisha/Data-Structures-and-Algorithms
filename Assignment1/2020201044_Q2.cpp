#include <iostream>
#include <string>

using namespace std;

typedef string BigInteger;

bool operator<(BigInteger a, BigInteger b)
{

    int aLength = a.length();
    int bLength = b.length();

    if (aLength < bLength)
        return true;

    if (bLength < aLength)
        return false;

    else if (aLength == bLength)
    {
        for (int i = 0; i < aLength; i++)
            if (a[i] < b[i])
                return true;
            else if (a[i] > b[i])
                return false;
    }

    return false;
}

bool operator<=(BigInteger a, BigInteger b)
{
    return (a < b || a == b);
}

bool operator>=(BigInteger a, BigInteger b)
{
    return (b < a || a == b);
}

void reverse(BigInteger &a)
{
    int n = a.length();
    char temp;
    for (int i = 0; i < n / 2; i++)
    {
        temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

BigInteger operator-(BigInteger a, BigInteger b)
{
    BigInteger diff = "";
    BigInteger ans = "";
    if (a == b)
        return "0";
    if (b == "0")
        return a;
    int aLength = a.length();
    int bLength = b.length();
    reverse(a);
    reverse(b);
    int i = 0, j = 0, resInt, bInt, aInt, borrowFlag = 0;

    while (i < aLength && j < bLength)
    {
        aInt = a[i] - '0';
        bInt = b[i] - '0';
        if (borrowFlag == 1)
        {
            if (aInt == 0)
                aInt = 10;
            aInt -= 1;
        }
        if (aInt != 9)
            borrowFlag = 0;
        if (aInt < bInt)
        {
            aInt += 10;
            borrowFlag = 1;
        }
        resInt = aInt - bInt;
        diff += to_string(resInt);
        i++;
        j++;
    }

    while (i < aLength)
    {
        aInt = a[i] - '0';
        if (borrowFlag == 1)
        {
            if (aInt == 0)
                aInt = 10;
            aInt -= 1;
        }
        if (aInt != 9)
            borrowFlag = 0;
        diff += to_string(aInt);
        i++;
    }
    //cout<<"diff:"<<diff<<endl;
    int k = diff.length() - 1;
    for (int i = k; i >= 0; i--)
    {
        if (diff[i] == '0')
            k--;
        else
            break;
    }
    ans = diff.substr(0, k + 1);
    reverse(ans);
    return ans;
}

int compareBigInt(BigInteger a, BigInteger b)
{
    int aLength = a.length();
    int bLength = b.length();
    if (aLength > bLength)
        return 1;
    else if (aLength < bLength)
        return -1;
    else
        return a.compare(b);
}

bool isEven(BigInteger a)
{
    return (((a[a.length() - 1]-'0') % 2) == 0);
}

BigInteger operator/(BigInteger a, int b)
{
    BigInteger quoteint = "", ans = "";
    long long int aLength = a.length();
    if (aLength == 1)
        return to_string((a[0] - '0') / 2);
    int forward = 0;

    for (int i = 0; i < aLength; i++)
    {
        int num = a[i] - '0';

        forward = forward * 10 + num;

        int q = forward / 2;
        quoteint += to_string(q);
        forward = forward % 2;
    }
    int k = 0;
    for (int i = 0; i < quoteint.length(); i++)
    {
        if (quoteint[i] == '0')
            k++;
        else
            break;
    }
    ans = quoteint.substr(k, quoteint.length() - k + 1);
    return ans;
}

BigInteger operator*(BigInteger a, BigInteger b)
{
    BigInteger ans = "";
    if (a == "0" || b == "0")
        return "0";
    if (a == "1")
        return b;
    if (b == "1")
        return a;
    int aLength, bLength, resLength;
    aLength = a.length();
    bLength = b.length();
    resLength = aLength + bLength;
    int arr[resLength];
    fill(arr, arr + resLength, 0);
    int bInt, aInt, resInt, carry;
    int padding = 1;
    for (int i = bLength - 1; i >= 0; i--)
    {
        carry = 0;
        bInt = b[i] - '0';

        //int pa = 0;
        int resPos = resLength - padding;
        for (int j = aLength - 1; j >= 0; j--)
        {
            aInt = a[j] - '0';
            resInt = (aInt * bInt) + arr[resPos] + carry;
            carry = resInt / 10;
            arr[resPos] = resInt % 10;
            resPos--;
        }
        padding++;
        arr[resPos] += carry;
    }
    int k = 0;
    for (int i = 0; i < resLength; i++)
    {
        if (arr[i] == 0)
            k++;
        else
            break;
    }
    for (int i = k; i < resLength; i++)
        ans += to_string(arr[i]);

    return ans;
}

BigInteger gcd(BigInteger a, BigInteger b)
{
    //cout<<"a: "<<a<<endl;
    //cout<<"b: "<<b<<endl;
    //cout<<"============================"<<endl;
    if (a == b)
        return a;

    if (a == "0")
        return b;
    if (b == "0")
        return a;

    if (isEven(a) && isEven(b))
    {
        return (gcd(a / 2, b / 2) * "2");
    }

    else if (isEven(a) && !isEven(b))
    {
        return gcd(a / 2, b);
    }

    else if (isEven(b) && !isEven(a))
    {
        return gcd(a, b / 2);
    }

    else
    {
        if ((compareBigInt(a, b)) > 0)
            return gcd((a - b) / 2, b);

        return gcd((b - a) / 2, a);
    }
}

BigInteger factorial(int a)
{
    BigInteger res = "1";
    for (int i = 1; i <= a; i++)
    {
        BigInteger istring = to_string(i);
        res = res * istring;
    }
    return res;
}

BigInteger exponentiation(BigInteger x, int n)
{
    BigInteger result;
    if (n == 0)
        return "1";
    if (n == 1)
        return x;
    result = exponentiation(x, n / 2);
    result = result * result;
    if (n % 2 == 0)
    {
        return result;
    }
    else
        return result * x;
}

int main()
{
    /*
==========================
    Menu
1 -> exponentiation
2 -> gcd
3 -> factorial
==========================
*/

    long long int q;
    int type;
    cin >> q;
    while (q--)
    {
        cin >> type;
        switch (type)
        {
        case 1:
        {
            BigInteger a;
            int b;
            cin >> a >> b;
            cout << exponentiation(a, b) << endl;
            break;
        }

        case 2:
        {
            BigInteger a, b;
            cin >> a >> b;
            cout << gcd(a, b) << endl;
            break;
        }

        case 3:
        {
            int a;
            cin >> a;
            cout << factorial(a) << endl;
            break;
        }
        default:
        {
            cout << "Enter values in 1 2 or 3 only" << endl;
            break;
        }
        }
    }
    return 0;
}
