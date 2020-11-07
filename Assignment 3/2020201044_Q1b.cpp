/*
NAME: SAI SIRISHA NADIMINTI
ROLL NO. : 2020201044
DSA ASSIGNMENT 3 Q2: SUFFIX ARRAY
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<string> suffixWords;

struct suffixString
{
    int rank[2];
    int offset;
    int prefixLength = 0;
    int lengthOfString;
};

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

// Time complexity to build the suffix array: O(nlognlogn)
void buildSuffixArray(suffixString table[], string word, int *suffixArr, int n)
{

    for (int i = 0; i < n; i++)
    {
        suffixArr[i] = i;
    }

    //Build the initial table
    //string suffix = "";
    int length = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        //  suffix = word[i] + suffix;
        //table[i].s = suffix;
        table[i].offset = i;
        table[i].rank[0] = word[i]; //Remove 'a' for alphanumeric later
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
    }
}

void printTable(suffixString table[], int n, string word)
{
    cout << "Offset "
         << "String"
         << "Prefix length"
         << "Total length" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << table[i].offset << " " << word.substr(table[i].offset) << " " << table[i].prefixLength << " " << table[i].lengthOfString << endl;
    }
}


//Kasai Algo
void calculatePrefixArray(suffixString table[], string word, int n)
{
    int startLength = 0;
    vector<int> reverse(n, 0);
    for (int i = 0; i < n; i++)
    {
        reverse[table[i].offset] = i;
    }
    int next;
    for (int present = 0; present < n; present++)
    {
        if (reverse[present] == n - 1)
        {
            startLength = 0;
            table[reverse[present]].prefixLength = 0;
        }
        else
        {
            int index = reverse[present] + 1;
            next = table[index].offset;
            while (present + startLength < n && next + startLength < n && word[present + startLength] == word[next + startLength])
            {
                startLength++;
            }
            table[reverse[next]].prefixLength = startLength;
            startLength = startLength > 0 ? startLength - 1 : startLength;
        }
    }
}

string longestSubstringAtLeastKTimes(string word, suffixString table[], int suffixArr[], int n, int k)
{
    if (k == 1)
    {
        return word;
    }
    int offset = -1;
    int maxOffset = -1;
    int maxPrefix = -1;

    for (int i = 0; i <= n - k + 1; i++)
    {
        int min = table[i].prefixLength;
        offset = table[i].offset;
        for (int j = i + 1; j < i + k - 1; j++)
        {
            if (min > table[j].prefixLength)
            {
                min = table[j].prefixLength;
                offset = table[j].offset;
            }
        }
        //  cout<<"min for the range"<<i<< " to "<<(i+k-2)<<" is "<<min<<endl;
        if (min > maxPrefix)
        {
            maxPrefix = min;
            maxOffset = offset;
        }
    }
    return word.substr(maxOffset, maxPrefix);
}


int main()
{
    //string word = "123SaiSirishaNADIMINTI";
    int WORD_LENGTH;
    string word;
    cin >> word;
    //0 1 2 14 15 21 16 18 17 13 19 3 6 20 12 4 11 5 7 9 8 10  - myanswer
    WORD_LENGTH = word.length();

        suffixString table[WORD_LENGTH];
        int k;
        cin >> k;
        int arr[WORD_LENGTH];
        buildSuffixArray(table, word, arr, WORD_LENGTH);
        calculatePrefixArray(table, word, WORD_LENGTH);
        //printTable(table,WORD_LENGTH,word);
        cout << longestSubstringAtLeastKTimes(word, table, arr, WORD_LENGTH, k) << endl;

    return 0;
}
