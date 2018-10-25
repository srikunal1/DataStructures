#include<stdio.h>
#ifndef NULL
#define NULL 0
#endif
#define N 1000000
#define FOR(i,a,b) for(i=a;i<b;i++)
struct Node{
    int data;
    Node *left;
    Node *right;
    int height;
    int size;
    int poolIndex;
};
class Mem{
private:
    Node mempool[N];
    int q[N];
    int a,b;
public:
    Mem(){
        FOR(a,0,N)mempool[a].poolIndex=a;
        init();
    }
    void init(){
        FOR(b,0,N)q[b]=b;
        a=b=0;//assuming we will never run of space
    }
    Node* getMem(){
        int availableMemIndex=q[a];
        a=(a+1)%N;
        Node *newMem=&mempool[availableMemIndex];
        return newMem;
    }
    void freeMem(int poolIndex){
        q[b]=poolIndex;
        b(b+1)%N;
    }
};

class AVL{
private:
    Mem pool;
    Node *root;
    inline int getHeight(Node *root){
        return (root==NULL?-1:root->height);
    }
    inline int getSize(Node *root){
        return (root==NULL?0:root->size);
    }

    int findMin(Node *ptr){
        while(ptr->left!=NULL)ptr=ptr->left;
        return ptr->data;
    }

    Node* insert(Node *root,int data){
        if(root==NULL){
            root=pool.getMem();
            root->data=data;
            root->left=NULL;
            root->right=NULL;
            root->height=0;
            root->size=1;
            return root;
        }else if(root->data>data){
            root->left=insert(root->left,data);
        }else if(root->data<data){
            root->right=insert(root->right,data);
        }
        root->height=1+max(getHeight(root->left),getHeight(root->right));
        root->size=1+getSize(root->left)+getSize(root->right);
        return root;
    }
public:
    AVL(){
        init();
    }
    void init(){
        root=NULL;
        pool.init();
    }
    void insert(int data){
        root=insert(root,data);
    }
};

int main(){
    //driver functions can be added later
    return 0;
}
