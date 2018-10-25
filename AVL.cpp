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
public:
    AVL(){
        init();
    }
    void init(){
        root=NULL;
        pool.init();
    }
};

int main(){
    //driver functions can be added later
    return 0;
}
