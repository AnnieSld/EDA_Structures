#include <bits/stdc++.h>
using namespace std;

class RetroactiveSegmentTree {

private:

    int n;
    vector<long long> tree;

    void update(int node, int l, int r, int pos, long long value) {

        if (l == r) {
            tree[node] = value;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(node * 2, l, mid, pos, value);
        else
            update(node * 2 + 1, mid + 1, r, pos, value);

        tree[node] =
            tree[node * 2] +
            tree[node * 2 + 1];
    }

    long long query(
        int node,
        int l,
        int r,
        int ql,
        int qr
    ) {

        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr)
             + query(node * 2 + 1, mid + 1, r, ql, qr);
    }

public:

    RetroactiveSegmentTree(int n) {
        this->n = n;
        tree.resize(4 * n, 0);
    }

    // Insertar/modificar una operación en el tiempo t
    void retroactiveUpdate(int t, long long value) {

        update(1, 0, n - 1, t, value);
    }

    // Efecto de las operaciones entre [l,r]
    long long query(int l, int r) {

        return query(1, 0, n - 1, l, r);
    }
};

int main() {

    RetroactiveSegmentTree st(5);

    // Historia temporal
    st.retroactiveUpdate(0, 5);
    st.retroactiveUpdate(1, 3);
    st.retroactiveUpdate(2, -2);
    st.retroactiveUpdate(3, 7);

    // Efecto de t0 ... t3
    cout << st.query(0, 3) << "\n";

    // Modificar el pasado:
    // t1 ahora es +10 en lugar de +3
    st.retroactiveUpdate(1, 10);

    cout << st.query(0, 3) << "\n";

    return 0;
}