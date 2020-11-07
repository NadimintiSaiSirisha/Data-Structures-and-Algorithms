/*
NAME: SAI SIRISHA NADIMINTI
ROLL NO.: 2020201044
Aim: Given an array A of N numbers, you will be given q queries. Each query will
contain a single integer x. You have to find then maximum xor of x from any number
in A.
Approach: Keep making the least significant bits of solutions as 1, if possible
*/

#include <iostream>
#define INT_LENGTH 64
#define TRIE_CHILDEN 2

using namespace std;

struct TrieNode
{
    TrieNode *child[2];
    bool isEnd;
    long long int value;
    TrieNode()
    {
        isEnd = false;
        for (int i = 0; i < TRIE_CHILDEN; i++)
        {
            child[i] = NULL;
        }
        value = -1;
    }
};

// Time Complexity: Theta(N) : N is sum of lengths
TrieNode *insert(TrieNode *root, int element)
{
    TrieNode *node = root;
    string bin = "";
    int n = element;
    for (int i = 0; i < INT_LENGTH; i++)
    {
        if (n & 1)
            bin += "1";
        else
            bin += "0";
        n = n >> 1;
    }

    for (int i = INT_LENGTH - 1; i >= 0; i--)
    {
        char ch = bin[i];
        int index = ch - '0';
        if (node->child[index] == NULL)
        {
            TrieNode *childNode = new TrieNode();
            //cout << "Address of " << ch << ": " << childNode << endl;
            node->child[index] = childNode;
            node = childNode;
        }
        else
        {
            node = node->child[index];
        }
    }
    node->isEnd = true;
    node->value = element;
    //cout<<"Inserted "<<element<<endl;
    return root;
}

int findMaxXOR(TrieNode *root, int element)
{
    string ele = "";
    long long int n = element;
    for (int i = 0; i < INT_LENGTH; i++)
    {
        if (n & 1)
            ele += "1";
        else
            ele += "0";
        n = n >> 1;
    }

    TrieNode *node = root;
    for (int i = INT_LENGTH - 1; i >= 0; i--)
    {
        char c = ele[i];
        if (c == '0' && node->child[1] != NULL)
            node = node->child[1];
        else if (c == '1' && node->child[0] != NULL)
            node = node->child[0];
        else if (node->child[0] != NULL)
            node = node->child[0];
        else
            node = node->child[1];
    }
    return node->value;
}

int main()
{
    long long int n, q;
    long long int value;
    cin >> n >> q;
    long long int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        arr[i] = value;
    }
    TrieNode *root = new TrieNode();
    for (long long int i = 0; i < n; i++)
    {
        root = insert(root, arr[i]);
    }
    long long int element;
    while (q--)
    {
        cin >> element;
        long long int x = findMaxXOR(root, element);
        // cout<<"Max XOR is with "<<x<<endl;
        // cout<<"Max XOR value is "<<(x^element)<<endl;
        cout << (x ^ element) << endl;
    }
    return 0;
}