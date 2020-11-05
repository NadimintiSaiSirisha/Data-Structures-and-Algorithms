/*
NAME: SAI SIRISHA NADIMINTI
ROLL NO. : 2020201044
DSA ASSIGNMENT 3 Q2
Suffix tree is a sorted array fo all suffixes of the string
0 1 2 3 4 5
b a n a n a suffixes:

0 banana - 
1 anana -
2 nana                 
3 ana -
4 na
5 a -

Sort them:
5 a
3 ana
1 anana
0 banana
4 na
2 nana

Suffix array for banana: {5,3,1,0,4,2}

Sort idea: The idea is to use the fact that strings that are to be sorted are suffixes of a single string.


*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define ASCII_LENGTH 26
using namespace std;

vector<string> suffixWords;
int WORD_LENGTH;
struct suffixString
{
    string s;
    int rank[2];
    int offset;
    int prefixLength = 0;
    int lengthOfString;
};

void printTable(suffixString table[], int n)
{
    // cout << "Offset\t"
    //      << "String\t"
    //      << "Rank 0\t"
    //      << "Rank 1\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << table[i].offset << "\t" << table[i].s << "\t" << table[i].rank[0] << "\t" << table[i].rank[1] << endl;
    }
}

//Range of elements:
// Ascii value of 0 is 48
// Ascii of 1 is 49
// Ascii of A is 65
// Ascii of Z is 90
// Ascii of a is 97
// Ascii value of z is 122

//Range of rank will lie between 0 and 122

struct suffixNode
{
    suffixString row;
    suffixNode *next;
    suffixNode(suffixString s)
    {
        row = s;
        next = NULL;
    }
};

bool cmp(const suffixString &a, const suffixString &b)
{
    if (a.rank[0] < b.rank[0])
        return true;
    else if (a.rank[0] == b.rank[0] && a.rank[1] < b.rank[1])
        return true;
    return false;
}

void SortTable(suffixString *table, int n)
{
    sort(table, table + n, cmp);
}

void calculatePrefixLength(suffixString table[], int n)
{
    table[0].prefixLength = 0;
    string a, b;
    int x;
    for (int i = 1; i < n; i++)
    {
        x = 0;
        a = table[i - 1].s;
        b = table[i].s;
        while (x < a.length() && x < b.length() && (a[x] == b[x]))
        {
            x++;
        }

        table[i].prefixLength = x;
    }
}

// Time complexity to build the suffix array: O(nlognlogn)
void buildSuffixArray(suffixString table[], string word, int *suffixArr, int n)
{

    for (int i = 0; i < n; i++)
    {
        suffixArr[i] = i;
    }

    //Build the initial table
    string suffix = "";
    int length = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        suffix = word[i] + suffix;
        table[i].s = suffix;
        table[i].offset = i;
        table[i].rank[0] = suffix[0]; //Remove 'a' for alphanumeric later
        table[i].lengthOfString = length++;
    }

    // Sort the ranks logn times
    for (int gap = 1; gap < 2 * n; gap = gap * 2)
    {
        for (int i = 0; i < n - 1; i++)
        {
            //Get the rank of character at str[i + 1]
            if (table[i].offset + gap < n)
            {
                table[i].rank[1] = table[suffixArr[table[i].offset + gap]].rank[0];
            }
            else
            {
                table[i].rank[1] = -1;
            }
        }
        table[n - 1].rank[1] = -1;
        //printTable(table, n);
        //Sort the table
        SortTable(table, n);
        //Index mapping

        for (int i = 0; i < n; i++)
        {
            suffixArr[table[i].offset] = i;
        }
        //Print table
        // printTable(table, n);

        //Get new rank 0
        // cout << "Assigning new ranks" << endl;
        int newRanks[n];
        newRanks[0] = 0;
        for (int i = 1; i < n; i++)
        {
            if (table[i].rank[0] == table[i - 1].rank[0] && table[i].rank[1] == table[i - 1].rank[1])
            {
                newRanks[i] = newRanks[i - 1];
            }
            else
            {
                newRanks[i] = newRanks[i - 1] + 1;
            }
        }
        //Store new ranks back in the table
        for (int i = 0; i < n; i++)
        {
            table[i].rank[0] = newRanks[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        suffixArr[i] = table[i].offset;
        suffixWords.push_back(table[i].s);
    }
    // calculatePrefixLength(table, n);

    cout << "Offset "
         << "String "
         << "Prefix Length"
         << "Length of string" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << table[i].offset << " " << table[i].s << " " << table[i].lengthOfString << endl;
    }
}

string minLexRotation(suffixString table[], int n)
{

    for (int i = 0; i < n; i++)
    {
        if (table[i].offset <= n - 1)
            return suffixWords[i].substr(0, n);
    }
    return "ERROR OCCURED";
}

string longestSubstringAtLeastKTimes(suffixString table[], int suffixArr[], int n, int k)
{

    string a, b;
    int x;
    int lengtha, lengthb;
    int maxPreLength = 0;
    int preIndex = -1;
    for (int i = 0; i <= n - k; i++)
    {
        x = 0;
        a = table[i].s;
        b = table[i + k - 1].s;
        lengtha = table[i].lengthOfString;
        lengthb = table[i + k - 1].lengthOfString;

        while (x < lengtha && x < lengthb && (a[x] == b[x]))
        {
            x++;
        }

        if (x > maxPreLength)
        {
            maxPreLength = x;
            preIndex = i;
        }
    }
    if (preIndex == -1)
        return "-1";
    return suffixWords[preIndex];
}

int main()
{
    //string word = "123SaiSirishaNADIMINTI";

    string word;
    cin >> word;
    int type;
    cin >> type;
    //0 1 2 14 15 21 16 18 17 13 19 3 6 20 12 4 11 5 7 9 8 10  - myanswer
    WORD_LENGTH = word.length();
    switch (type)
    {
    case 0:
    {
        //Not for assignment
        //Just build a suffix array
        suffixString table[WORD_LENGTH];
        int arr[WORD_LENGTH];
        buildSuffixArray(table, word, arr, WORD_LENGTH);
        break;
    }
    case 1:
    {
        suffixString table[2 * WORD_LENGTH];
        int arr[2 * WORD_LENGTH];
        buildSuffixArray(table, word + word, arr, 2 * WORD_LENGTH);
        // cout << "Minimum lexographic rotation is: " << endl;
        cout << minLexRotation(table, WORD_LENGTH);
        cout << endl;
        break;
    }
    case 2:
    {
        suffixString table[WORD_LENGTH];
        int k;
        cin >> k;
        int arr[WORD_LENGTH];
        buildSuffixArray(table, word, arr, WORD_LENGTH);
        cout << longestSubstringAtLeastKTimes(table, arr, WORD_LENGTH, k) << endl;

        break;
    }
    case 3:
    {
        string rev;
        rev = word;
        int totLength = (WORD_LENGTH * 2) + 2;
        suffixString table[totLength];
        int arr[totLength];

        reverse(rev.begin(), rev.end());
        buildSuffixArray(table, word + "#" + rev + "$", arr, totLength);
        calculatePrefixLength(table, totLength);
        int maxPrefix = 0;
        string sub = "";
        for (int i = 1; i < totLength; i++)
        {
            // string 1 will have offset from 0 to a-1
            // string 2 will have offset from a+1 to a+b-1
            if (((table[i].offset <= WORD_LENGTH - 1 && table[i - 1].offset >= WORD_LENGTH + 1) || (table[i - 1].offset <= WORD_LENGTH - 1 && table[i].offset >= WORD_LENGTH + 1)))
            {
                if (table[i].offset - 0 == (totLength - (table[i - 1].offset + table[i].prefixLength + 1)))
                {
                    if (table[i].prefixLength > maxPrefix)
                    {
                        // The prefix must be of two different strings

                        //Distance from 0 to start of string 1 should be equal to distance from end of string2 to totallength

                        maxPrefix = table[i].prefixLength;

                        sub = suffixWords[i].substr(0, maxPrefix);
                    }
                }
            }
        }
        cout << "palindrome: " << sub << endl;
        break;
    }
    case 4:
    {
        //Not for assignment - Longest common substring

        string string1, string2;
        cin >> string1 >> string2;
        int a = string1.length();
        int b = string2.length();
        int totLength = a + b + 2;
        // rev = word;
        suffixString table[totLength];
        int arr[totLength];

        //reverse(rev.begin(),rev.end());
        buildSuffixArray(table, string1 + "#" + string2 + "$", arr, totLength);
        int maxPrefix = 0;
        string sub = "";
        for (int i = 1; i < totLength; i++)
        {
            // string 1 will have offset from 0 to a-1
            // string 2 will have offset from a+1 to a+b-1

            if (table[i].prefixLength > maxPrefix)
            {
                // The prefix must be of two different strings
                if ((table[i].offset <= a - 1 && table[i - 1].offset >= a + 1) || (table[i - 1].offset <= a - 1 && table[i].offset >= a + 1))
                {
                    maxPrefix = table[i].prefixLength;
                    sub = suffixWords[i].substr(0, maxPrefix);
                }
            }
        }
        cout << "substring: " << sub << endl;

        break;
    }

    default:
    {
        cout << "Enter valid input" << endl;
        break;
    }
    }
}
