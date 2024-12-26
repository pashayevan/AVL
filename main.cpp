#include <iostream>

struct Node {
    int key;
    unsigned char height;
    Node* left;
    Node* right;
    Node(int k) {key=k, left=right=nullptr; height=1; }
};
unsigned char height(Node* p) {
    return p?p->height:0;
}
int bfactor(Node* p) {
    return p->right->height-p->left->height;
}
void fixheight(Node* p) {
    unsigned char hl=p->left->height;
    unsigned char hr=p->right->height;
    p->height=(hl>hr?hl:hr)+1;
}
Node* rotateRight(Node* p) {
    Node* q=p->left;
    p->left=q->right;
    q->right=p;
    fixheight(p);
    fixheight(q);
    return q;
}
Node* rotateLeft(Node* q) {
    Node* p=q->right;
    q->right=q->left;
    p->left=q;
    fixheight(q);
    fixheight(p);
    return p;
}
Node* balance (Node* p) {
    fixheight((p));
    if(bfactor(p)==2) {
        if (bfactor(p->right)<0)
            p->right=rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p)==-2) {
        if (bfactor(p->left)>0)
            p->left=rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

Node* insert(Node* p, int k) {
    if(!p) return new Node(k);
    if(k<p->key)
        p->left=insert(p->left, k);
    else
        p->right=insert(p->right, k);
    return balance(p);
}

Node* findmin(Node* p) {
    return p->left?findmin(p->left):p;
}
Node* removemin (Node* p) {
    if(p->left==nullptr)
        return p->right;
    p->left=removemin(p->left);
    return balance(p);
}

Node* remove(Node* p, int k) {
    if(!p) return nullptr;
    if(k<p->key)
        p->left=remove(p->left, k);
    else if(k>p->key)
        p->right=remove(p->right,k);
    else {
        Node* q=p->left;
        Node* r=p->right;
        delete p;
        if(!r) return q;
        Node* min=findmin(r);
        min->right=removemin(r);
        min->left=q;
        return balance(min);
    }
    return balance(p);
}

int main() {
    return 0;
}