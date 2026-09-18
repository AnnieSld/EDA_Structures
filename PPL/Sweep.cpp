#include <bits/stdc++.h>
using namespace std;

const int ADD = -1e9 - 1;
const int REM = -1e9 - 2;
const int QUERY = -1e9 - 3;

// ============================================================
// SEGMENT TREE
// ============================================================

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n, 0);
    }

    // A[pos] += val
    void update(int node, int l, int r, int pos, int val) {
        if (l == r) {
            tree[node] += val;
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(2 * node, l, mid, pos, val);
        else
            update(2 * node + 1, mid + 1, r, pos, val);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }

    // Suma en [ql, qr]
    int query(int node, int l, int r, int ql, int qr) {
        // No hay intersección
        if (qr < l || r < ql)
            return 0;

        // El nodo está completamente dentro del rango
        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return query(2 * node, l, mid, ql, qr)
             + query(2 * node + 1, mid + 1, r, ql, qr);
    }

    int query(int l, int r) {
        if (l > r)
            return 0;

        return query(1, 0, n - 1, l, r);
    }
};


int compress(vector<int>& Y) {
    vector<int> values(Y.begin(), Y.end());

    sort(values.begin(), values.end());

    values.erase(
        unique(values.begin(), values.end()),
        values.end()
    );

    for (int& x : Y) {
        x = lower_bound(
            values.begin(),
            values.end(),
            x
        ) - values.begin();
    }

    return values.size();
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> Y;
    vector<int> X;

    vector<tuple<int, int, int>> events;

    for (int i = 0; i < n; ++i) {

        int a, b, c, d;
        cin >> a >> b >> c >> d;

      

        if (a == c) {

            if (b > d)
                swap(b, d);

            // La coordenada x es fija = a
            // El segmento ocupa y = b ... d

            Y.emplace_back(a);
            Y.emplace_back(a + 1);

            X.emplace_back(b);
            X.emplace_back(d + 1);
        }

        else {

            if (a > c)
                swap(a, c);

            // El segmento ocupa x = a ... c
            // y = b

            Y.emplace_back(a);
            Y.emplace_back(c + 1);

            X.emplace_back(QUERY);
            X.emplace_back(b);
        }
    }

    // Comprimir coordenadas
    int m = compress(Y);



    for (int i = 0; i < X.size(); i += 2) {

        if (X[i] == QUERY) {

            // Consulta de una vertical
            events.emplace_back(
                X[i + 1],
                Y[i],
                Y[i + 1] - 1
            );

        }
        else {

            // Activar
            events.emplace_back(
                X[i],
                ADD,
                Y[i]
            );

            // Desactivar
            events.emplace_back(
                X[i + 1],
                REM,
                Y[i]
            );
        }
    }


    // Procesamos los eventos de izquierda a derecha
    sort(events.begin(), events.end());

    int res = 0;

    SegmentTree ST(m);

    for (auto& e : events) {

        int t, l, r;
        tie(t, l, r) = e;

        if (l == ADD) {

            ST.update(r, +1);
        }

  

        else if (l == REM) {

            ST.update(r, -1);
        }

  

        else {

            res += ST.query(l, r);
        }
    }

    cout << res << '\n';

    return 0;
}