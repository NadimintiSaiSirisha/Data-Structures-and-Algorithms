#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Element
{
int col;
int val=0;
Element *next = NULL;
Element(int c, int v){
    col =c;
    val = v;
}
};

map<int, Element*> input(map<int,Element*> matrix, int rows, int cols){
int element;
for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
        cin >> element;
        if(element!=0){
            Element *node = new Element(j,element);
          
          Element *temp=matrix[i];
            if(temp==NULL){
                matrix[i] = node;
            }
            else{
              //  temp = matrix[i];
            while(temp->next!=NULL){
                temp=temp->next;
            }
            temp->next = node;
            }
        } 
    }
}
return matrix;
}

map<int, Element*> MatrixMultiply(map<int, Element*> a, map<int, Element*>b){
    map<int, Element*> result;

    for(auto it = a.begin();it!=a.end();it++){ //for all rows - it->first is the row number of C        
        Element *aNode = it->second; 
        while(aNode!=NULL){ 
            {
                
                Element *bNode = b[aNode->col];
                while(bNode!=NULL)
                {
                    
                  if(result[it->first]==NULL)
                {
                    result[it->first] = new Element(bNode->col, aNode->val*bNode->val);   
                }
                else{ 
                       Element *temp = result[it->first];
                       while(temp!=NULL){
                           if(temp->col == bNode->col)
                           {
                               temp->val+=aNode->val*bNode->val;
                               break;
                           }
                           temp=temp->next;
                           
                       }
                       if(temp==NULL){
                           Element *insert = result[it->first];
                           result[it->first] = new Element(bNode->col, aNode->val*bNode->val);
                           result[it->first]->next = insert;
                       }

                }
                    bNode=bNode->next;
                } 
                aNode = aNode->next;
            }
        }
    }
    return result;
}

/* Input
3 3 3
0 10 12
1 0 2
0 0 0
2 5 0
0 1 0
8 0 0

Output 
96 10 0
18 5 0
0 0 0

*/


int main(){
   map<int, Element*> A;
   map<int, Element*> B;
    map<int, Element*> C;
    // A: m x n matrix
    // B: nx p matrix

    int m,n,p; 
cin>>m;
cin>>n;
cin>>p;
A = input(A,m,n);
B = input(B,n,p);
C = MatrixMultiply(A,B);
for(auto it=C.begin();it!=C.end();it++){
    Element *node = C[it->first];
cout<<"For row "<< it->first<<": ";
while(node!=NULL){
cout<<" Col number: "<<node->col<<" Value: "<<node->val;
node = node->next;
}
cout<<endl;
}
    return 0;
}