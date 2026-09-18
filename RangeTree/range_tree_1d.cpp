#include <bits/stdc++.h>
using namespace std;

template<typename data_type, typename build_type = long long>
struct RangeTree {
    int n;
    vector<vector<data_type>> tree;        
    vector<vector<int>> leftPos, rightPos; 

    RangeTree(vector<data_type> a) {
        n = a.size();
        tree.assign(4 * n, {});
        leftPos.assign(4 * n, {});
        rightPos.assign(4 * n, {});
        build(1, 0, n - 1, a);
    }
    build_type query(int l, int r, data_type x) {
        int pos = upper_bound(tree[1].begin(), tree[1].end(), x) - tree[1].begin();
        return query(1, 0, n - 1, l, r, pos);
    }

private:
    void build(int node, int l, int r, vector<data_type>& a) {
        if (l == r) {
            tree[node] = { a[l] };
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, a);
        build(2 * node + 1, mid + 1, r, a);

        auto &L = tree[2 * node];
        auto &R = tree[2 * node + 1];
        auto &cur = tree[node];
        cur.resize(L.size() + R.size());
        leftPos[node].resize(cur.size() + 1);
        rightPos[node].resize(cur.size() + 1);

        int i = 0, j = 0, k = 0;
        while (i < (int)L.size() || j < (int)R.size()) {
            leftPos[node][k] = i;
            rightPos[node][k] = j;
            if (j >= (int)R.size() || (i < (int)L.size() && L[i] <= R[j])) {
                cur[k] = L[i++];
            } else {
                cur[k] = R[j++];
            }
            k++;
        }
        leftPos[node][k] = i;
        rightPos[node][k] = j;
    }

    build_type query(int node, int nodeL, int nodeR, int l, int r, int pos) {
        if (r < nodeL || nodeR < l || pos == 0) return 0;
        if (l <= nodeL && nodeR <= r) return pos;
        int mid = (nodeL + nodeR) / 2;
        int lp = leftPos[node][pos];
        int rp = rightPos[node][pos];
        return query(2 * node, nodeL, mid, l, r, lp)
             + query(2 * node + 1, mid + 1, nodeR, l, r, rp);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    RangeTree<long long> Solver(a);

    while (q--) {
        int l, r;
        long long x;
        cin >> l >> r >> x; // cuenta elementos <= x en a[l..r]
        cout << Solver.query(l, r, x) << "\n";
    }
}