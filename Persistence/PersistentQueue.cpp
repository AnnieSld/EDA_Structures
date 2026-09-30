#include <bits/stdc++.h>
using namespace std;

template<typename data_type>

struct SegmentTree {
    struct Node {
        int data;
        Node *left, *right;
        int l, r;

        Node(data_type data, int l, int r, Node* left, Node* right) {
            this->data = data;
            this->l = l;
            this->r = r;
            this->left = left;
            this->right = right;
        }
    };

    vector<Node*> vroots;
    SegmentTree(int n) {
        vroots.emplace_back(new Node(data_type(), 0, n - 1, nullptr, nullptr));
        build(vroots[0]);
    }

    SegmentTree(int l, int r, vector<data_type> &a) {
        vroots.emplace_back(new Node(data_type(), l, r, nullptr, nullptr));
        build(vroots[0], a);
    }

    void build(Node *root) {
        if (root -> l == root -> r) {
        root -> data = data_type();
        return;
        }
        int mi = (root -> l + root -> r) / 2;
        root -> left = new Node(data_type(), root -> l, mi, nullptr, nullptr);
        root -> right = new Node(data_type(), mi + 1, root -> r, nullptr, nullptr);
        build(root -> left);
        build(root -> right);
        }


    void build(Node *root, vector<data_type> &a) {
        if (root->l == root->r) {
            root->data = a[root->l - 1];
            return;
        }

        int mid = (root->l + root->r) / 2;

        root->left = new Node(data_type(), root->l, mid, nullptr, nullptr);
        root->right = new Node(data_type(), mid + 1, root->r, nullptr, nullptr);

        build(root->left, a);
        build(root->right, a);
    }

    void update(int pos, data_type val, Node *last, Node *curr) {
        if (curr->l == curr->r) {
            curr->data = val;
            return;
        }

        int mid = (curr->l + curr->r) / 2;

        if (pos <= mid) {
            curr->right = last->right;
            curr->left = new Node(last->left->data, curr->l, mid, nullptr, nullptr);
            update(pos, val, last->left, curr->left);
        }
        else {
            curr->left = last->left;
            curr->right = new Node(last->right->data, mid + 1, curr->r, nullptr, nullptr);
            update(pos, val, last->right, curr->right);
        }

        curr->data = curr->right->data + curr->left->data;
    }

    int update(int version, int pos, data_type value) {
        Node *root = new Node(data_type(), vroots[0]->l, vroots[0]->r, nullptr, nullptr);
        vroots.emplace_back(root);
        update(pos, value, vroots[version], root);
        return (int)vroots.size() - 1;
    }

    int query(data_type x, data_type y, Node *root) {
        if (y < root->l || root->r < x || x > y) {
            return data_type(0);
        }

        if (x <= root->l && root->r <= y) {
            return root->data;
        }

        return query(x, y, root->left) + query(x, y, root->right);
    }

    data_type query(int version, int x, int y) {
        return query(x, y, vroots[version]);
    }
    int get_vcurr(){
        return (int)vroots.size()-1;
    }
};


template<typename data_type>
struct PersistentQueue{
        vector<int> tails;
        vector<int> roots;
        vector<int> heads;
        SegmentTree<data_type> S;

        PersistentQueue(int max_cap): S(max_cap){
            roots.emplace_back(S.get_vcurr());
            heads.emplace_back(0);
            tails.emplace_back(0);
        }
        void push(int v, data_type x){
            S.update(roots[v], tails[v], x);
            roots.emplace_back(S.get_vcurr());
            heads.emplace_back(heads[v]);
            tails.emplace_back(tails[v]+1);
        }
        data_type pop(int v){
            data_type ans = S.query(roots[v], heads[v], heads[v]);
            roots.emplace_back(roots[v]);
            heads.emplace_back(heads[v]+1);
            tails.emplace_back(tails[v]);
            return ans;
        }

};

int main() {

    int m;
    cin >> m;
    PersistentQueue<int> Q(m+1);

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int a, b;
            cin >> a >> b;
            Q.push(a, b);
        }
        else if (op == -1) {
            int e;
            cin >> e;
            cout << Q.pop(e) << '\n';
        }
    }
}