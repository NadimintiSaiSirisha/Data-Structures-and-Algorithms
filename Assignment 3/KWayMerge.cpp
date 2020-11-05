#include <iostream>
#include <vector>
#define deb(x) cout << #x << ": " << x << endl
#define CHUNCK_SIZE 100000
using namespace std;

struct MinHeapNode
{
    long long int val;
    FILE *fPointer;
    long long int position;
    MinHeapNode(long long int v, FILE *f, long long int p)
    {
        val = v;
        fPointer = f;
        position = p;
    }
};

//Trickle down
void min_heapify(vector<MinHeapNode *> &a, long long int i)
{
    long long int smallest; //contains the smallest element ka index
    long long int n = a.size();
    long long int l = (i << 1) + 1; //Left child ka index
    long long int r = (i << 1) + 2; //Right child ka index
    if (l < n && (((a[l])->val) < ((a[i])->val)))
    {
        smallest = l;
    }
    else
        smallest = i;
    if (r < n && (((a[r])->val) < ((a[smallest])->val)))
    {
        smallest = r;
    }
    if (smallest != i)
    {
        swap(a[i], a[smallest]);
        min_heapify(a, smallest);
    }
}

void buildMinHeap(vector<MinHeapNode *> &a)
{
    long long int n = a.size();
    for (long long int i = ((n / 2) - 1); i >= 0; i--)
    {
        min_heapify(a, i);
    }
}

MinHeapNode *extractMin(vector<MinHeapNode *> &a)
{
    long long int n = a.size();
    MinHeapNode *minEle;
    if (n < 1)
    {
        cout << "Heap is empty" << endl;
        return NULL;
    }
    minEle = a[0];
    a[0] = a[n - 1];
    a.pop_back();
    min_heapify(a, 0);
    return minEle;
}

//Bubble up
void insertElement(vector<MinHeapNode *> &a, MinHeapNode *node)
{
    a.push_back(node);
    long long int i = a.size() - 1;
    while (i >= 0 && (((a[(i - 1) / 2])->val) > ((a[i]->val))))
    {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//4,3,1,5,17

void MergeNormal(long long int a[], long long int l, long long int mid, long long int r)
{
    long long int size1, size2, n, p1 = 0, p2 = 0, k = l;
    size1 = mid - l + 1;
    size2 = r - mid;
    long long int first[size1], second[size2];
    for (long long int i = 0; i < size1; i++)
    {
        first[i] = a[i + l];
    }
    for (long long int i = 0; i < size2; i++)
    {
        second[i] = a[i + mid + 1];
    }

    while (p1 < size1 && p2 < size2)
    {
        if (first[p1] < second[p2])
        {
            a[k++] = first[p1++];
        }
        else
        {
            a[k++] = second[p2++];
        }
    }
    while (p1 < size1)
    {
        a[k++] = first[p1++];
    }
    while (p2 < size2)
    {
        a[k++] = second[p2++];
    }
    /*
    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
*/
}

void MergeSortNormal(long long int a[], long long int l, long long int r)
{
    if (l < r)
    {
        long long int mid = (l + r) / 2;
        MergeSortNormal(a, l, mid);
        MergeSortNormal(a, mid + 1, r);
        MergeNormal(a, l, mid, r);
    }
}

void writeToOutputFile(string element)
{

   // cout << element << endl;
    FILE *filePointer;

    //Writing sorted arrays into files
    string path = "data/output.txt";
    filePointer = fopen(path.c_str(), "a+");
    if (!filePointer)
    {
        cout << "Could not open first file";
        return;
    }
    fputs(element.c_str(), filePointer);
    fclose(filePointer);
}

void writeFile(long long int &turn, string element)
{

    //Removing the last comma from the string
    element.pop_back();
   // cout << element    << endl;
    FILE *filePointer;

    //Writing sorted arrays into files

    filePointer = fopen(("data/file" + to_string(turn) + ".txt").c_str(), "w+");
    if (!filePointer)
    {
        cout << "Could not open first file";
        return;
    }
    fputs(element.c_str(), filePointer);
    fclose(filePointer);
}

int openFile(string filepath)
{
    long long int arr[CHUNCK_SIZE];
    long long int i = -1;
    long long int turn = 0;
    FILE *fp = NULL;
    char ch;
    string element = "";
    fp = fopen(filepath.c_str(), "r");
    if (!fp)
    {
        cout << "Could not open the file." << endl;
    }
    else
    {
        while ((ch = fgetc(fp)) != EOF)
        {
            //printf("%c", ch);
            if (ch != ',')
            {
                element += ch;
            }
            else
            {

                //Insert the number into array
                arr[++i] = stoll(element);
                element = "";
                //Check if the array is full
                if (i == CHUNCK_SIZE - 1)
                {
                    //Sort the array
                    MergeSortNormal(arr, 0, CHUNCK_SIZE - 1);
                    //Write this array into a new file
                    element = "";
                    for (long long int i : arr)
                    {
                        element += to_string(i) + ",";
                    }
                    writeFile(turn, element);
                    turn++;
                    element = "";
                    i = -1;
                }
            }
        }
        //Element has the last iteration string
        string lastItr = "";
        arr[++i] = stoll(element);
        long long int n = i + 1; //Last n can be less than the chunk size
        MergeSortNormal(arr, 0, n - 1);
        //Write this array into a new file
        element = "";
        for (long long int i = 0; i < n; i++)
        {
            element += to_string(arr[i]) + ",";
        }
        //Last file is turn
        writeFile(turn, element);
        element = "";
    }
    // Returning the number of files generated
    return (turn + 1);
}

//Returns the string from the file
string getLineFromFile(string filepath)
{
    FILE *file1 = fopen(filepath.c_str(), "r");
    char ch;
    string str;
    while ((ch = fgetc(file1)) != EOF)
    {
        str += ch;
    }
    fclose(file1);
    return str;
}

//Returns the length of the array
long long int convertStringToArray(string s, long long int a[])
{
    long long int i = -1;
    string element = "";
    for (char c : s)
    {
        if (c != ',')
        {
            element += c;
        }
        else
        {
            a[++i] = stoll(element);
        }
    }
    return i;
}

void kWayMerge(long long int k)
{
    vector<MinHeapNode *> MinHeap;
    char ch;
    string str = "";
    string outputPath = "data/output.txt";
    int r = remove(outputPath.c_str());
    if (r >= 0)
    {
        cout << "Output file deleted" << endl;
    }

    //Only one chunk is present. So, output will be this chunk.
    if (k == 1)
    {
        //Working for one chunk
        str = getLineFromFile("data/file0.txt");
        writeToOutputFile(str);
        //fputs(str.c_str(), outputFile);
        return;
    }
    vector<FILE *> filePointers(k, NULL);
    //Make the heap out of first element of each sorted file
    for (long long int i = 0; i < k; i++)
    {
        filePointers[i] = fopen(("data/file" + to_string(i) + ".txt").c_str(), "r");
        if ((filePointers[i]) == NULL)
        {
            cout << "File data/file" << i << ".txt could not be opened." << endl;
            return;
        }
        string number = "";
        while ((ch = fgetc(filePointers[i])) != ',' && ch != EOF)
        {
            number += ch;
        }
        MinHeapNode *temp = new MinHeapNode(stoll(number), filePointers[i], i);
        MinHeap.push_back(temp);
    }

    buildMinHeap(MinHeap);
    MinHeapNode *minEle = extractMin(MinHeap);
    long long int minElementExtracted = minEle->val;
    //deb(minElementExtracted);
    FILE *minElementPointer = minEle->fPointer;
    writeToOutputFile(to_string(minElementExtracted));

    //Start building the min heap one node at a time now
    //Till the minheap does not get empty
    string number = "";
    while (MinHeap.size() > 0)
    {
        number = "";

        while ((ch = fgetc(minElementPointer)) != ',' && ch != EOF)
        {
            number += ch;
        }
        if (number != "")
        {
            MinHeapNode *temp = new MinHeapNode(stoll(number), minEle->fPointer, minEle->position);
            insertElement(MinHeap, temp);
        }
        else
        {
            fclose(minEle->fPointer);
        }

        minEle = extractMin(MinHeap);
        minElementExtracted = minEle->val;
        //deb(minElementExtracted);
        minElementPointer = minEle->fPointer;
        writeToOutputFile("," + to_string(minElementExtracted));
    }

    //Write last file

    number = "";
    while ((ch = fgetc(minElementPointer)) != EOF)
    {
        number += ch;
        while ((ch = fgetc(minElementPointer)) != ',' && ch != EOF)
        {
            number += ch;
        }
        if (number != "")
        {
            writeToOutputFile("," + number);
            number = "";
        }
    }
}

int main()
{
    long long int k;
    k = openFile("data/input1000000.txt");
    kWayMerge(k);
    return 0;
}