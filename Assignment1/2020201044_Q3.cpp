/*
Expected Time Complexity for each operation-
push_back(x) - Amortized O(1)
pop_back() - Amortized O(1)
push_front() - Amortized O(1)
pop_front() - Amortized O(1)
front() - O(1)
back() - O(1)
empty() - O(1)
size() - O(1)
resize() - O(N)
clear() - O(N)
D[n] - O(1)
Deque is the same as dynamic arrays with the ability
to resize itself automatically when an element is
inserted or deleted, with their storage being handled
automatically by the container. They support insertion and Deletion from both ends
in amortized constant time.
Inserting and erasing in the middle is linear in time.
deque() - initialize a blank deque.
 deque(n,x) - initialize a deque of length n with all
values as x.
 push_back(x) - append data x at the end.
 pop_back() - erase data at the end.
 push_front(x) - append data x at the beginning.
 pop_front() - erase data at the beginning.
 front() - returns the first element(value) in the deque.
 back() - returns the last element(value) in the deque.
 empty() - returns true if deque is empty else returns
false.
 size() - returns the current size of deque.
 resize(x, d) - changes the size dynamically. If the
new size is greater than the current size of the
deque, then fill the empty space with the default
value d.
 clear() - remove all elements of deque.
 D[n] - returns the nth element of the deque.
*/

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

static int q;

template <class T>
class deque
{
public:
    T *arr;
    //Size: Number of elements present in the array
    //Capacity: Size of the array (Maximum number of elements the array can take)
    int fr, rear, sz, capacity, pushResizeFlag = 0;

    deque()
    {
        arr = NULL;
        sz = 0;
        capacity = 0;
        fr = -1;
        rear = 0;
    }

    deque(int n, const T &x)
    {

        //cout << "Creating a deque of size " << n << " and with default value as " << x << endl;
        sz = n;
        capacity = n;
        fr = 0;
        rear = n-1;
        arr = new T[n];
        fill_n(arr, n, x);
        display();
    }

    bool isFull()
    {
        if (((rear + 1) % capacity) == fr)
            return true;
        return false;
    }

    bool empty()
    {
        return (sz == 0);
    }

    int size()
    {
        return sz;
    }

    void push_back(const T &x)
    {
        // cout << "Pushing '" << x << "' to the back of the deque" << endl;
        if (capacity == 0)
        {
            pushResizeFlag = 1;
            resize(1, 0);
            //capacity = 1;
        }
        else if (isFull())
        {
            pushResizeFlag = 1;
            resize(2 * capacity, "x");
            //capacity = 2 * capacity;
        }

        if (fr == -1)
        {
            fr = rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = x;
        sz += 1;
        display();
    }

    void pop_back()
    {

        if (empty())
        {
            cout << "Empty deque" << endl;
            return;
        }

        if (fr == rear) //only one element is present
        {
            fr = -1;
            rear = 0;
        }

        else
            rear = (rear - 1) % capacity;
        sz -= 1;
        display();
    }

    void push_front(const T &x)
    {
        //cout << "Pushing '" << x << "' to the front of the deque" << endl;
        if (capacity == 0)
        {
            pushResizeFlag = 1;
            resize(1, "x");
            //capacity = 1;
        }
        else if (isFull())
        {
            pushResizeFlag = 1;
            resize(2 * capacity, "x");
            //capacity = 2 * capacity;
        }
        if (fr == -1)
        {
            fr = rear = 0;
        }
        else if (fr == 0)
            fr = capacity - 1;
        else
            fr -= 1;
        arr[fr] = x;
        sz += 1;
        display();
    }

    void pop_front()
    {

        if (empty())
        {
            cout << "Empty deque" << endl;
            return;
        }
        //cout << "Popping the element " << arr[fr] << endl;

        if (fr == rear)
        {
            fr = -1;
            rear = 0;
        }
        else
            fr = (fr + 1) % capacity;
        sz -= 1;
        display();
    }

    T front()
    {
        if (!empty())
            return arr[fr];
        else
            return 0;
    }

    T back()
    {
        if (!empty())
            return arr[rear];
        else
            return 0;
    }

    void display()
    {
        if (sz == 0)
        {
            cout << "Empty deque" << endl;
            return;
        }
        //cout << "Elements in the deque are: ";

        if (rear >= fr)
        {
            for (int i = fr; i <= rear; i++)
                cout << arr[i] << " ";
        }
        else
        {
            int i = fr;
            while (i < capacity)
            {
                cout << arr[i] << " ";
                i++;
            }
            i = 0;
            while (i <= rear)
            {
                cout << arr[i] << " ";
                i++;
            }
        }
        cout << endl;
    }

    void resize(int x, T d)
    {
        int changeRear = 0;
        int copyLength = 0;
        if(x<capacity) copyLength = x;
        else copyLength = sz;
        if (rear < fr)
            changeRear = 1;
        //cout<<"Resizing the array..."<<endl;
        T *temp = new T[x];

        if (capacity > 0)
        {
            for (int i = 0; i < copyLength; i++)
            {
                temp[i] = arr[fr];
                fr = (fr + 1) % capacity;
            }
            if (changeRear == 1)
                rear = fr;
        }
      if(fr==-1)
      {
          if(pushResizeFlag==0) fr=0;
          else fr=-1;
      }
      else fr=0;
        /*
        front pushResizeFlag 
        -1      0               fr=0
        -1      1                fr=-1
        0       0               fr=0
                                fr=0        

*/

        delete[] arr;
        arr = temp;

        if (x > capacity)
            fill_n(arr + sz, x - sz, d);
        capacity = x;
        if (pushResizeFlag == 0)
        {
            sz = x;
            rear = sz - 1;
            display();
        }
        pushResizeFlag = 0;
    }

    void freeSpace()
    {
        delete[] arr;
    }
    void clear()
    {
        //delete[] arr;
        fr = -1;
        rear = sz = capacity = 0;
    }

    T operator[](int n)
    {
        if (n < sz && !empty())
            return arr[(fr + n) % sz];
        else
        {
            cout << "Out of bound" << endl;
            return "";
        }
    }
};

int MenuCall(deque<string> &D)
{
    int initializeNew = 0;
    while (q--)
    {
        int type;
        cin >> type;
        switch (type)
        {
        case 1:
        {
            string x;
            cin >> x;
            D.push_front(x);
            break;
        }

        case 2:
        {
            D.pop_front();
            break;
        }
        case 3:
        {
            string x;
            cin >> x;
            D.push_back(x);
            break;
        }
        case 4:
        {
            D.pop_back();
            break;
        }
        case 5:
        {
            initializeNew = 5;
            return initializeNew;
        }
        case 6:
        {
            initializeNew = 6;
            return initializeNew;
        }
        case 7:
        {
            cout << D.front() << endl;
            break;
        }
        case 8:
        {
            cout << D.back() << endl;
            break;
        }
        case 9:
        {
            cout << D.empty() << endl;
            break;
        }
        case 10:
        {
            cout << D.size() << endl;
            break;
        }
        case 11:
        {
            int x; string d;
            cin >> x >> d;
            D.resize(x, d);
            break;
        }
        case 12:
        {
            D.clear();
            break;
        }
        case 13:
        {
            int n;
            cin >> n;
            if (D[n] != "")
                cout << D[n] << endl;
            break;
        }
        case 14:
        {
            D.display();
            break;
        }
        default:
        {
            cout << "Enter the value between 1- 14" << endl;
            break;
        }
        }
    }
    return initializeNew;
}

void initializeEmptyDeque()
{
    //cout<<q<<endl;
    void initializeDefaultDeque();
    int initializeNew = 0;
    deque<string> d;
    initializeNew = MenuCall(d);
    d.freeSpace();
    if (initializeNew == 5)
        initializeEmptyDeque();
    if (initializeNew == 6)
        initializeDefaultDeque();
}

void initializeDefaultDeque()
{
    //cout<<q<<endl;
    void initializeEmptyDeque();
    int initializeNew = 0;
    int n; string x;
    cin >> n >> x;
    deque<string> d(n, x);
    initializeNew = MenuCall(d);
    d.freeSpace();
    if (initializeNew == 5)
        initializeEmptyDeque();
    if (initializeNew == 6)
        initializeDefaultDeque();
}

int main()
{

    /*
MENU
===========================================
1. push_front(x) --
2. pop_front()
3. push_back(x)
4. pop_back() --
5. deque()
6. deque(n,x) --
7. front()
8. back()
9. empty()
10. size() --
11. resize(x, d) --
12. clear() --
13. D[n] --
14. display() - display contents of deque
============================================
*/
    
    int type;
    int initializeNew = 0;
    cin >> q;
    cin >> type;
    q--;
    switch (type)
    {
    case 5:
    {
        initializeEmptyDeque();
        break;
    }
    case 6:
        initializeDefaultDeque();
        break;
    }

    return 0;
}
