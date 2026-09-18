#include<bits/stdc++.h>

using namespace std;

struct SegmentTree{
    struct Node{
        int data;
        Node* left;
        Node* right;
        int l, r;
        Node(int d, Node* left, Node* right, int l, int r): data(d), left(left), right(right), r(r), l(l){}
    };
    vector<int> b; // arreglo de nros
    vector<Node*> roots; // arreglo de versiones

    SegmentTree(vector<int> a){ // constructor
        b = a;
        roots.push_back(build(0, b.size()-1));
    }

    Node* build(int l, int r){
        if(l == r){ // si hoja, el valor se coloca nomas
            Node* x = new Node (b[l], nullptr, nullptr, l, r);
            return(x);
        }
        else{ // si no hoja se calcula el medio y se construyen los hijos segun los rangos
            int mid = (l + r)/2;
            Node* left = build(l, mid);
            Node* right = build(mid+1, r);
            Node* y = new Node(left->data + right->data, left, right, l, r);
            return(y); // al final  y padre se construye con los hijos y como data la suma
        }
        
    }
    Node* update(int pos, int val, Node* last, Node* curr) {
    if (curr->l == curr->r) {  // llegamos a la hoja
        curr->data = val;
        return curr;
    }

    int mid = (curr->l + curr->r) / 2;

    if (pos <= mid) {
        curr->left = new Node(last->left->data, last->left->left,last->left->right, last->left->l, last->left->r);
        curr->left = update(pos, val, last->left, curr->left);
        curr->right = last->right;
    }
    else {
        curr->right = new Node(last->right->data,last->right->left,last->right->right, last->right->l,last->right->r);
        curr->right = update(pos, val, last->right, curr->right);
        curr->left = last->left;
    }
    curr->data = curr->left->data + curr->right->data;

    return curr;}

    int update(int version, int pos, int val){// update pero ahora retorna la version
        Node* last = roots[version];
        Node* curr = new Node(int(), last->left, last->right, last->l, last->r);

        update(pos, val, last, curr);
        
        roots.push_back(curr);
        return roots.size()-1;
       
        
    }

    int query(Node* node, int l, int r, int ql, int qr){
        if(ql <= l && qr >= r){
            return node->data;
        }
        else if (l > qr || r < ql){
            return 0;
        }
        else{
            int ans = 0;
            int mid = ( l + r )/2;
            if (ql <= mid ){
                ans += query(node->left, l,mid,ql, qr);
            }
            if ( qr > mid){
                ans += query(node->right, mid+1 ,r,ql, qr);
            }
            return ans;
        }
        
    }
    
};

int main(){
    
}