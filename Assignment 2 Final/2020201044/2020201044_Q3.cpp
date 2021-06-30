#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

template <class K, class V>
class Ordered_Map
{
public:
   int keysNumber = 0;

   class Node
   {
   public:
      int height;
      K key;
      V value;
      Node *left;
      Node *right;

      Node(K k, V v)
      {
         key = k;
         value = v;
         height = 1;
         left = NULL;
         right = NULL;
      }
   };

public:
   Node *rootMain = NULL;

   void insert(K k, V v)
   {
      rootMain = insertNode(rootMain, k, v);
   }

   Node *insertNode(Node *root, K k, V v)
   {
      int leftHeight = 0, rightHeight = 0;
      Node *node = new Node(k, v);
      if (!root)
      {
         keysNumber++;
         return node;
      }

      else if (k == (root->key))
      {
         root->value = v;
         return root;
      }

      else if (k < (root->key))
      {

         root->left = insertNode(root->left, k, v);
         root = balanceAVLTree(root);
      }
      else if (k > (root->key))
      {
         root->right = insertNode(root->right, k, v);
         root = balanceAVLTree(root);
      }

      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      return root;
   }

   Node *RR_Rotate(Node *root)
   {

      Node *node;
      node = root->right;
      root->right = node->left;
      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      node->left = root;
      node->height = max(getHeightOfNode(node->left), getHeightOfNode(node->right)) + 1;
      return node;
   }

   Node *LL_Rotate(Node *root)
   {

      Node *node;
      node = root->left;
      root->left = node->right;

      root->height = max(getHeightOfNode(root->left), getHeightOfNode(root->right)) + 1;
      node->right = root;
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

   void erase(K k)
   {
      rootMain = deleteNode(rootMain, k);
   }

   Node *deleteNode(Node *root, K k)
   {
      if (!root)
      {
         return root;
      }

      if (k < root->key)
      {
         root->left = deleteNode(root->left, k);
      }

      else if (k > root->key)
      {
         root->right = deleteNode(root->right, k);
      }
      else
      {

         if (!(root->left) || !(root->right))
         {
            Node *node = root->left ? root->left : root->right;

            if (node == NULL)
            {
               node = root;
               root = NULL;
            }
            else
               *root = *node;
            keysNumber--;
            free(node);
         }
         else
         {
            Node *successor = getInorderSucessor(root);

            root->key = successor->key;
            root->value = successor->value;
            root->right = deleteNode(root->right, successor->key);
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

   void printMap()
   {
      if (!rootMain)
      {
         cout << "Map is empty" << endl;
         return;
      }
      else
      {
         inOrder(rootMain);
         cout << endl;
      }
   }

   void inOrder(Node *root)
   {
      if (!root)
         return;
      inOrder(root->left);
      cout << root->key << "->" << root->value << " | ";
      inOrder(root->right);
   }

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

   bool find(K k)
   {
      return Search(rootMain, k) == NULL ? false : true;
   }

   Node *Search(Node *root, K k)
   {
      if (!root)
         return NULL;
      if (root->key == k)
         return root;
      if (root->key > k)
         return Search(root->left, k);
      return Search(root->right, k);
   }

   void clear()
   {
      keysNumber = 0;
      deleteEverything(rootMain);
      rootMain = NULL;
   }

   void deleteEverything(Node *root)
   {
      if (root == NULL)
         return;

      deleteEverything(root->left);
      deleteEverything(root->right);
      delete root;
   }

   //map[3]=4

   V &operator[](K k)
   {

      V dummy;
      if (typeid(V) == typeid(char))
      {
         char dummy = '0';
      }
      else if (typeid(V) == typeid(int))
      {
         int dummy = 0;
      }

      else if (typeid(V) == typeid(int))
      {
         int dummy = 0;
      }

      Node *root = rootMain;
      if (find(k))
      {
         while (root)
         {
            if (root->key == k)
            {

               return root->value;
            }
            if (k < root->key)
            {
               root = root->left;
            }
            else if (k > root->key)
            {
               root = root->right;
            }
         }
         return root->value;
      }
      else
      {
         insert(k, dummy);
         return (Search(root, k))->value;
      }
   }
};

int main()
{
   Ordered_Map<int, char> m;
   int key;
   char value;
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
         //Insert the key value pair
         cin >> key >> value;
         // cout << "**INSERTING {" << key << "->" << value << "} **" << endl;
         m.insert(key, value);
         m.printMap();
         break;
      }
      case 2:
      {
         //Erase the key
         cin >> key;
         //  cout << "**ERASING THE KEY " << key << " **" << endl;
         m.erase(key);
         m.printMap();
         break;
      }
      case 3:
      {
         cin >> key;
         //   cout << "**FINDING " << key << " IN THE MAP**" << endl;
         if (m.find(key))
            cout << "Key is present in the map" << endl;
         else
            cout << "Key not found" << endl;
         break;
      }

      case 4:
      {
         cin >> key;
         // cout << "**RETURNING VALUE OF " << key << "**" << endl;
         if (m.find(key))
            cout << m[key] << endl;
          else
         {
           cout<<"Key not found"<<endl;
          }
         break;
      }

      case 5:
      {
         //Inserting the value in key using [] operator
         cin>>key;
         cin>>value;
         m[key]=value;
         m.printMap();
         break;
      }

      case 6:
      {
         // cout << "**NUMBER OF KEYS IN MAP ARE:**" << endl;
         cout << m.keysNumber << endl;
         break;
      }
      case 7:
      {
         // cout << "Clearing" << endl;
         // keysNumber = 0
         m.clear();
         m.printMap();
         break;
      }
      default:
      {
         //   cout << "Please enter a valid choice" << endl;
         break;
      }
      }
   }
   return 0;
}