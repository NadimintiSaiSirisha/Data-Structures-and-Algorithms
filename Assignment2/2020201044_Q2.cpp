#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

template <class K, class V>
class Unordered_Map
{
public:
    int size = 97;
    int multiplier = 3;
    
    class Node
    {
    public:
        K key;
        V value;

        Node *next = NULL;

        Node(K k, V v)
        {
            key = k;
            value = v;
            next = NULL;
        }
    };
    
    //took prime number to reduce collision
    Node *hashTable[97];

    Unordered_Map()
    {
        for (int i = 0; i < 98; i++)
            hashTable[i] = NULL;
    }

    //Reference for hashing function: https://cses.fi/book/book.pdf
    int HashKey(K key)
    {
        stringstream s1;
        s1 << key;
        string hashString = s1.str();
        int stringSize = hashString.length();
        int preprocessedHash[stringSize];
        preprocessedHash[0] = (hashString[0])%size;
        // cout<<preprocessedHash[0]<<endl;
        for (int i = 1; i < stringSize; i++)
        {
            preprocessedHash[i] = ((preprocessedHash[i - 1] * multiplier) + (hashString[i])) % size;
            // cout<<preprocessedHash[i]<<endl;
        }

        // cout<<"Hash Key for string: "<<preprocessedHash[stringSize-1]<<endl;
        return preprocessedHash[stringSize - 1];
    }

    void displayTheMap()
    {
        for (int i = 0; i < size; i++)
        {
            cout << i << " :";
            Node *begin = hashTable[i];
            while (begin != NULL)
            {
                cout << " | " << begin->key << "->" << begin->value << " | ";
                begin = begin->next;
            }
            cout << endl;
        }
    }

    void insert(K k, V v)
    {
        int hashKey = HashKey(k);
        Node *node = new Node(k, v);
        if(find(k))
        {
            erase(k);
        }
        
        Node *insertAt = hashTable[hashKey];
        if (insertAt == NULL)
        {
            hashTable[hashKey] = node;
        }
        else
        {
            node->next = insertAt;
            hashTable[hashKey] = node;
        }

    }

    void erase(K k)
    {
        int hashKey = HashKey(k);

        Node *currPtr = hashTable[hashKey];

        Node *prevPtr = NULL;
        if (currPtr != NULL && currPtr->key == k)
        {

            hashTable[hashKey] = currPtr->next;
            free(currPtr);
            return;
        }
        while (currPtr != NULL && currPtr->key != k)
        {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }

        if (currPtr == NULL)
            return;

        prevPtr->next = currPtr->next;

        free(currPtr); // Free memory
     
    }

    bool find(K k)
    {

        int hashKey = HashKey(k);
        Node *currPtr = hashTable[hashKey];
        while (currPtr != NULL)
        {
            if (currPtr->key == k)
            {
              return true;
            }
            currPtr = currPtr->next;
        }
    return false;
    }

    V operator[](K k)
    {
      
       if(find(k)){
        int hashKey = HashKey(k);
        Node *currPtr = hashTable[hashKey];
        while (currPtr != NULL)
        {
            if (currPtr->key == k)
            {
               return currPtr->value;
                
            }
            currPtr = currPtr->next;
        }
       }
            cout<<"Key not found"<<endl;
        }
    
};

int main()
{
    Unordered_Map<string, int> m;
int queries;
cin>>queries;
while(queries--){
    int choice;
    cin>>choice;
    switch(choice){
        case 1:{
            //Insert the key value pair
            string key; int value;
            cin>>key>>value;
            cout<<"Inserting {"<<key<< "->" <<value<<"} ..."<<endl;
            m.insert(key,value);
            m.displayTheMap();
            break;
        }
        case 2:
        {
            //Erase the key
            string key;
            cin>>key;
            cout<<"Erasing the key "<<key<<" ..."<<endl;
            m.erase(key);
            m.displayTheMap();
            break;

        }
        case 3:{
            string key;
            cin>>key;
            cout<<"Finding "<<key<<" in the map ...**"<<endl;
            if(m.find(key))
            cout<<"Key is present in the map"<<endl;
            else
            cout<<"Key not found"<<endl;
            break;
        }
        case 4:
        {
            string key;
            cin>>key;
           
            if(m.find(key)){
            cout<<"Returning value of "<<key<< " ..."<<endl;
            cout<<m[key]<<endl;
            }
            else {
                cout<<"Key is not present"<<endl;
            }
            break;
        }
        default: {
            cout<<"Please enter a valid choice"<<endl;
            break;
        }
    }
}
    return 0;
}