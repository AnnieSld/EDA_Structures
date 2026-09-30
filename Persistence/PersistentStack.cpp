#include<bits/stdc++.h>

using namespace std;

struct PersistentStack{
struct Node{
    int data;
    Node* next;
    Node(int data, Node* next): data(data), next(next){}
};


vector<Node*> roots;

PersistentStack(){
    roots.push_back(nullptr);}
    
    void push(int version, int value){
        Node* newNode = new Node(value, roots[version]);
        roots.push_back(newNode);
    }

    void pop(int version) {
    roots.push_back(roots[version]->next);}

    int top(int version){
        int data = roots[version]->data;
        return data;
    }
};



int main(){
    PersistentStack p;

    p.push(0,1);
    cout << "v1 push(1): " << p.top(1) << "\n";

    p.push(1, 2);
    cout << "v2 push(2): " << p.top(2) << "\n";

    p.push(1, 3);
    cout << "v3 push(3): " << p.top(3) << "\n";
    p.pop(2);

    cout << "v4 pop de v2: " << p.top(4) << "\n";

}