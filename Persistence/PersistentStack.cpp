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


}