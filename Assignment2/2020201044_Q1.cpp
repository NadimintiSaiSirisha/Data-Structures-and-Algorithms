#include <iostream>
#include <climits>
using namespace std;

  int operator - ( string const &a,  string const &b) 
    {
       return 0;
    } 
    
    template <class T> struct Less {
	bool operator()(const T &lhs, const T &rhs) {
		return lhs < rhs;
	}
};

//template <class T, class Comparator = Less<T>>
//template <class T>
template <class T, class Comparator = Less<T>> class AVLTree
//class AVLTree
{
//AVLTree(): cmp(cmparator()){
public:
	Comparator cmp;
 // node = NULL;
 // cmp = cmparator();
 

   class Node
   {
   public:
      int height;
      T data;
      Node *left;
      Node *right;
      int count;
      int LSTSize;
      int RSTSize;

      Node(T t)
      {
         data = t;
         height = 1;
         left = NULL;
         right = NULL;
         count = 1;
         LSTSize = 0;
         RSTSize = 0;
      }
   };

public:
   Node *root;
   int totalCountOfNodes;

   Node *insertNode(Node *root, T value)
   {
      int leftHeight = 0, rightHeight = 0;
      Node *node = new Node(value);
      if (!root)
      {
         return node;
      }

      else if (!cmp(value,root->data) && !cmp(root->data,value))
      {
         (root->count)++;
         return root;
      }
      else if (cmp(value,(root->data)))
      {
         root->left = insertNode(root->left, value);
         (root->LSTSize)++;
         root = balanceAVLTree(root);
      }
      //else if (value > (root->data))
      else if(cmp(root->data,value))
      {
         root->right = insertNode(root->right, value);
         (root->RSTSize)++;
         root = balanceAVLTree(root);
      }

      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      //  root = balanceAVLTree(root);
      return root;
   }

   Node *RR_Rotate(Node *root)
   {
      Node *node;
      node = root->right;
      root->right = node->left;
      root->RSTSize = node->LSTSize;
      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      node->left = root;
      node->LSTSize = root->count + root->LSTSize + root->RSTSize;
      node->height = max(getHeightOfNode(node->left), getHeightOfNode(node->right)) + 1;
      return node;
   }
   Node *LL_Rotate(Node *root)
   {
      Node *node;
      node = root->left;
      root->left = node->right;
      root->LSTSize = node->RSTSize;
      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      node->right = root;
      node->RSTSize = root->count + root->LSTSize + root->RSTSize;
      node->height = max(getHeightOfNode(node->left), getHeightOfNode(node->right)) + 1;
      return node;
   }
   Node *LR_Rotate(Node *root)
   {
      Node *node;
      node = root->left;
      root->left = RR_Rotate(node);
      Node *node2 = LL_Rotate(root);
      return node2;
   }

   Node *RL_Rotate(Node *root)
   {
      Node *node;
      node = root->right;
      root->right = LL_Rotate(node);
      Node *node2 = RR_Rotate(root);
      return node2;
   }

   int getHeightOfNode(Node *node)
   {
      if (!node)
         return 0;
      else
         return node->height;
   }

   Node *balanceAVLTree(Node *root)
   {
      int heightDifference = 0;
      int leftSubtreeDifference = 0;
      int rightSubtreeDifference = 0;
      if (root)
      {
         heightDifference = getHeightOfNode(root->left) - getHeightOfNode(root->right);
      }
      if (root->left)
      {
         leftSubtreeDifference = getHeightOfNode(root->left->left) - getHeightOfNode(root->left->right);
      }
      if (root->right)
      {
         rightSubtreeDifference = getHeightOfNode(root->right->left) - getHeightOfNode(root->right->right);
      }

      //The tree is already balanced
      if (heightDifference >= -1 and heightDifference <= 1)
         return root;

      if (heightDifference > 1)
      {
         if (leftSubtreeDifference > 0)
            root = LL_Rotate(root);
         else
            root = LR_Rotate(root);
      }
      else if (heightDifference < -1)
      {
         if (rightSubtreeDifference > 0)
            root = RL_Rotate(root);
         else
            root = RR_Rotate(root);
      }
      return root;
   }

   Node *deleteNode(Node *root, T value)
   {
      if (!root)
      {
         return root;
      }

      //if (value < root->data)
      if(cmp(value, root->data))
      {
         root->LSTSize -= 1;
         root->left = deleteNode(root->left, value);
      }

      //else if (value > root->data)
      else if(cmp(root->data,value))
      {
         root->RSTSize -= 1;
         root->right = deleteNode(root->right, value);
      }
      else
      {
         if (root->count > 1)
         {
            (root->count)--;
            return root;
         }

         else if (!(root->left) || !(root->right))
         {
            Node *node = root->left ? root->left : root->right;

            if (node == NULL)
            {
               node = root;
               root = NULL;
            }
            else
               *root = *node;

            free(node);
         }
         else
         {
            Node *successor = getInorderSucessor(root);

            root->data = successor->data;
            root->right = deleteNode(root->right, successor->data);
            root->RSTSize -= 1;
         }
      }

      if (root == NULL)
      {
         return root;
      }

      int heightDifference = getHeightOfNode(root->left) - getHeightOfNode(root->right);

      if (heightDifference > 1 && ((getHeightOfNode(root->left->left) - getHeightOfNode(root->left->right)) >= 0))
         return LL_Rotate(root);

      if (heightDifference > 1 && ((getHeightOfNode(root->left->left) - getHeightOfNode(root->left->right)) < 0))
      {
         root->left = RR_Rotate(root->left);
         return LL_Rotate(root);
      }

      if (heightDifference < -1 &&
          ((getHeightOfNode(root->right->left) - getHeightOfNode(root->right->right)) <= 0))
         return RR_Rotate(root);

      if (heightDifference < -1 && ((getHeightOfNode(root->right->left) - getHeightOfNode(root->right->right)) > 0))
      {
         root->right = LL_Rotate(root->right);
         return RR_Rotate(root);
      }
      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      return root;
   }

   void inOrder(Node *root)
   {
      if (!root)
         return;
      inOrder(root->left);
      cout << root->data << " ";
      inOrder(root->right);
   }

/*
   void printTree(Node *root)
   {
      queue<Node *> q;
      Node *node;
      int size;
      if (!root){
         cout<<"Tree is empty"<<endl;  
         return;
      }
      q.push(root);

      while (!q.empty())
      { //In the end, we will have only NULL node in the queue
         size = q.size();
         for (int i = 0; i < size; i++)
         {
            node = q.front();
            q.pop();

            cout << node->data << " , " << node->height << " , " << node->LSTSize << " , " << node->RSTSize << " | ";
            if (node->left)
               q.push(node->left);
            if (node->right)
               q.push(node->right);
         }
         cout << endl;
      }
      cout << "****************" << endl;
   }
*/
   Node *getInorderSucessor(Node *root)
   {
      Node *node = root;
      node = node->right;
      while (node->left)
      {
         node = node->left;
      }
      return node;
   }

   int countOccurrences(Node *root, T value)
   {

      if (!root)
         return 0;
      //if (root->data == value)
      if(!cmp(root->data,value) && !cmp(value,root->data))
      {

         return root->count;
      }
     // else if (value < root->data && root->left)
      else if(cmp(value, root->data) && root->left)
      {
         return countOccurrences(root->left, value);
      }
      else
      {
         if (root->right)
            return countOccurrences(root->right, value);
      }
      return 0;
   }

   T strictlyGreaterElement(Node *root, T value)
   {
      //if (value < root->data)
        if(cmp(value, root->data))
         strictlyGreaterElement(root->left, value);
      //if (value == root->data)
      if(!cmp(value,root->data) && !cmp(root->data,value))
      {
         return (getInorderSucessor(root))->data;
      }
   }

   T upper_bound(Node *root, T value)
   {

      static Node *node = NULL;
      if (root == NULL){
       try{
         throw(504);
       }
       catch(...){
          cout<<"There is no bound to the element you specified."<<endl;
       }
      }
      //if (root->data > value)
      if(cmp(value, root->data))
      {
         //storing the parent to come back if there is no iunorder successor
         node = root;
         if (root->left)
            return upper_bound(root->left, value);
         else return root->data;
      }
      //if (root->data < value)
       else if(cmp(root->data,value)){
         if (root->right)
            return upper_bound(root->right, value);
       }
     // if (root->data == value)
      else if(!cmp(root->data,value) && !cmp(value,root->data))
      {
                  if (root->right != NULL)
         {
            return (getInorderSucessor(root)->data);
         }
         // return node->data;
      }
      if(node==NULL){
           try{
         throw(504);
       }
       catch(...){
          cout<<"There is no bound to the element you specified."<<endl;
       }
      }
  else return node->data;
   }

   bool Search(Node *root, T value)
   {
      if (!root)
         return false;
     // if (root->data == value)
       if(!cmp(root->data,value) && !cmp(value, root->data))
         return true;
      //if (root->data > value)
        if(cmp(value,root->data))
         return Search(root->left, value);
      return Search(root->right, value);
   }

   T lower_bound(Node *root, T value)
   {
      if (Search(root, value) == true)
         return value;
      else
         return upper_bound(root, value);
   }

   T closestValue;
   T closestElement(Node *root, T value, int minDiff)
   {
      //static int minDiff = INT_MAX;
      if (!root)
         return closestValue;
      //if (root->data == value)
        if(!cmp(root->data,value) && !cmp(value,root->data))
         return value;
      if (minDiff > abs((root->data) - value))
      {
         minDiff = abs((root->data) - value);
         closestValue = root->data;
      }
      //if (value < root->data)
        if(cmp(value, root->data))
         return closestElement(root->left, value, minDiff);
      else
         return closestElement(root->right, value,minDiff);
   }

   T kthLargestElement(Node *root, int k)
   {
      Node *node = root;
      int countTemp = k;
      while (node)
      {
         for (int i = 1; i <= node->count; i++)
         {
            if (((node->RSTSize) + i) == countTemp)
               return node->data;
         }
         if (node->RSTSize < countTemp)
         {
            countTemp -= node->RSTSize + node->count;
            node = node->left;
         }
         else
         {
            node = node->right;
         }
      }
      try{
     throw(504);
      }
      catch(...)
      {
      cout<< "Kth largest element not found";
      }
   }

   int countElementsInRange(Node *root, T low, T high)
   {

      if (!root)
         return 0;

      //if (root->data == high && root->data == low)
        if(!cmp(root->data, high) && !cmp(high,root->data)){
         if(!cmp(root->data,low) && !cmp(low,root->data)){
         return root->count;
         }
        }


     // if (root->data <= high && root->data >= low)
     if(!cmp(high,root->data) && !cmp(root->data,low))
         return root->count + countElementsInRange(root->left, low, high) +
                countElementsInRange(root->right, low, high);

     // else if (root->data < low)
       else if(cmp(root->data,low))
         return countElementsInRange(root->right, low, high);
      else
         return countElementsInRange(root->left, low, high);
   }
};
/*
100
1 32
1 32
1 32
1 40
1 40
1 22
1 22
1 10
1 24
*/

int main()
{
   AVLTree<string> tree;
   tree.root = NULL;
   string value,start,end;
   int queries;
   
   cin >> queries;
   while (queries--)
   {
      int choice;
      cin >> choice;
      switch (choice)
      {
      case 1:
      {
         //Inseting the node
         cin >> value;
         tree.root = tree.insertNode(tree.root, value);
         tree.totalCountOfNodes++;
         tree.inOrder(tree.root);
         cout<<endl;
         break;
      }
      case 2:
      {
         //Deleting the node
         cin >> value;
         tree.root = tree.deleteNode(tree.root, value);
         tree.totalCountOfNodes--;
         tree.inOrder(tree.root);
           cout<<endl;
         break;
      }
      case 3:
      {
         //Searching for the node
         cin >> value;
         if (tree.Search(tree.root, value))
         {
            cout << "Value found" << endl;
         }
         else
         {
            cout << "Value not found" << endl;
         }
         break;
      }
      case 4:
      {
         //Count occurences of element
         cin >> value;
         cout << tree.countOccurrences(tree.root, value) << endl;
         
         break;
      }
      case 5:
      {
         //Find lower bound
         cin >> value;
         cout << tree.lower_bound(tree.root, value) << endl;
         break;
      }
      case 6:
      {
         // Find upper bound
         cin >> value;
         cout << tree.upper_bound(tree.root, value) << endl;
         break;
      }
      case 7:
      {
         //Find closest element to value
         cin >> value;
         cout << tree.closestElement(tree.root, value, INT_MAX) << endl;
         break;
      }
      case 8:
      {
         //Find kth largest element
         int k;
         cin >> k;
         cout << tree.kthLargestElement(tree.root, k) << endl;
         break;
      }
      case 9:
      {
         //COunt nodes count in range

         cin >> start >> end;
         cout << tree.countElementsInRange(tree.root, start, end) << endl;
         break;
      }
      default:
      {
         cout << "Enter number between 1 and 9" << endl;
         break;
      }
      }
   }

   return 0;
}