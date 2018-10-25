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

    Node* LL(Node *prevRoot){
        Node *newRoot=prevRoot->left;
        prevRoot->left=newRoot->right;
        newRoot->right=prevRoot;
        prevRoot->height=1+max(getHeight(prevRoot->left),getHeight(prevRoot->right));
        prevRoot->size=1+getSize(prevRoot->left)+getSize(prevRoot->right);
        newRoot->height=1+max(getHeight(newRoot->left),getHeight(newRoot->right));
        newRoot->size=1+getSize(newRoot->left)+getSize(newRoot->right);
        return newRoot;
    }
    Node* RR(Node *prevRoot){
        Node *newRoot=prevRoot->right;
        prevRoot->right=newRoot->left;
        newRoot->left=prevRoot;
        prevRoot->height=1+max(getHeight(prevRoot->left),getHeight(prevRoot->right));
        prevRoot->size=1+getSize(prevRoot->left)+getSize(prevRoot->right);
        newRoot->height=1+max(getHeight(newRoot->left),getHeight(newRoot->right));
        newRoot->size=1+getSize(newRoot->left)+getSize(newRoot->right);
        return newRoot;
    }
    Node* LR(Node *prevRoot){
        prevRoot->left=RR(prevRoot->left);
        prevRoot->height=1+max(getHeight(prevRoot->left),getHeight(prevRoot->right));
        prevRoot->size=1+getSize(prevRoot->left)+getSize(prevRoot->right);
        return LL(prevRoot);
    }
    Node* RL(Node *prevRoot){
        prevRoot->right=LL(prevRoot->right);
        prevRoot->height=1+max(getHeight(prevRoot->left),getHeight(prevRoot->right));
        prevRoot->size=1+getSize(prevRoot->left)+getSize(prevRoot->right);
        return RR(prevRoot);
    }

    Node* balance(Node *root){
        if(root==NULL)return NULL;
        int lH=getHeight(root->left);
        int rH=getHeight(root->right);
        if(lH-rH>1){
            int llH=getHeight(root->left->left);
            int lrH=getHeight(root->left->right);
            if(llH>=lrH)root=LL(root);
            else  root=LR(root);
        }else if(lH-rH<-1){
            int rlH=getHeight(root->right->left);
            int rrH=getHeight(root->right->right);
            if(rrH>=rlH)root=RR(root);
            else root=RL(root);
        }
        root->height=1+max(getHeight(root->left),getHeight(root->right));
        root->size=1+getSize(root->left)+getSize(root->right);
        return root;
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
        return balance(root);
    }

    Node* remove(Node *root,int data){
        if(root==NULL){
            return NULL;
        }else if(root->data>data){
            root->left=remove(root->left,data);
        }else if(root->data<data){
            root->right=remove(root->right,data);
        }else{
            //this  is the Node
            if(root->left==NULL && root->right==NULL){
                //leaf node
                pool.freeMem(root->poolIndex);
                return NULL;
            }else if(root->left==NULL){
                pool.freeMem(root->poolIndex);
                return root->right;
            }else if(root->right==NULL){
                pool.freeMem(root->poolIndex);
                return root->left;
            }else{
                int replacement=findMin(root->right);//inorder successor
                root->data=replacement;
                root->right=remove(root->right,replacement);
            }
        }
        return balance(root);
    }
    Node* search(int data){
        Node *ptr=root;
        while(ptr!=NULL){
            if(ptr->data>data)ptr=ptr->left;
            else if(ptr->data<data)ptr=ptr->right;
            else break;//found it
        }
        return ptr;
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
    void remove(int data){
        root=remove(root,data);
    }
    boolean exists(int data){
        return (search(data)!=NULL);
    }
};

int main(){
    //driver functions can be added later
    return 0;
}
