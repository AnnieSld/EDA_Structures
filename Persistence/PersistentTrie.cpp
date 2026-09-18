#include<bits/stdc++.h>

using namespace std;


struct PersistentTrie {

    struct Node {
        bool terminal;
        Node* child[26];

        Node(bool terminal = false) {
            this->terminal = terminal;

            for (int i = 0; i < 26; i++)
                child[i] = nullptr;
        }
    };

    vector<Node*> roots;

    PersistentTrie() {
        roots.push_back(new Node());
    }

    int insert(int version, string s) {

        Node* oldRoot = roots[version];

        // Copiamos la raíz
        Node* newRoot = new Node(oldRoot->terminal);

        for (int i = 0; i < 26; i++)
            newRoot->child[i] = oldRoot->child[i];

        Node* oldNode = oldRoot;
        Node* newNode = newRoot;

        for (char c : s) {

            int x = c - 'a';

            // Si existe el hijo viejo, lo copiamos
            if (oldNode->child[x] != nullptr) {

                Node* oldChild = oldNode->child[x];

                Node* newChild =
                    new Node(oldChild->terminal);

                for (int i = 0; i < 26; i++)
                    newChild->child[i] = oldChild->child[i];

                newNode->child[x] = newChild;
            }
            else {
                // No existía: creamos un nodo nuevo
                newNode->child[x] = new Node();
            }

            oldNode = oldNode->child[x];
            newNode = newNode->child[x];
        }

        newNode->terminal = true;

        roots.push_back(newRoot);

        return roots.size() - 1;
    }
};