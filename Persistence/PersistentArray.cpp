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

    SegmentTree(int l, int r, vector<data_type> &a) {
        vroots.emplace_back(new Node(data_type(), l, r, nullptr, nullptr));
        build(vroots[0], a);
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
};

int main() {
    int n = 0;
    cin >> n;
    vector<int> ans;

    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SegmentTree<int> S(1, n, arr);

    int m;
    cin >> m;

    while (m--) {
        string op;
        cin >> op;

        if (op == "create") {
            int a, b, c;
            cin >> a >> b >> c;
            S.update(a - 1, b, c);
        }
        else if (op == "get") {
            int e, f;
            cin >> e >> f;
            ans.push_back(S.query(e - 1, f, f));
        }
    }
    for (int x : ans) {
    cout << x << endl;
}
}