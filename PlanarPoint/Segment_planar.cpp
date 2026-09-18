
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    int left(int node) { return 2 * node + 1; }

    int right(int node) { return 2 * node + 2; }

    int mid(int l, int r) { return l + (r - l) / 2; }

    void build(int node, int start, int end)
    {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int m = mid(start, end);
        build(left(node), start, m);
        build(right(node), m + 1, end);
        tree[node]
            = min(tree[left(node)], tree[right(node)]);
    }

    void update(int node, int start, int end, int idx,
                int val)
    {
        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
            return;
        }
        int m = mid(start, end);
        if (idx <= m)
            update(left(node), start, m, idx, val);
        else
            update(right(node), m + 1, end, idx, val);
        tree[node]
            = min(tree[left(node)], tree[right(node)]);
    }

    int query(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
            return INT_MAX;
        if (l <= start && end <= r)
            return tree[node];
        int m = mid(start, end);

        int left_min = query(left(node), start, m, l, r);
        int right_min = query(right(node), m + 1, end, l, r);
        return min(left_min, right_min);
    }

public:

    SegmentTree(const vector<int>& a)
        : arr(a)
        , n(a.size())
    {
      
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    void update(int idx, int val)
    {
        update(0, 0, n - 1, idx, val);
    }


    int query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }
};

int main()
{
    int t = 0;
    cin >> t;
    vector<int> arr;
    while(--t){
        int a, b, c, d;
        cin >> a >>b >> c >> d;

        vector<int> arr {a, b, c, d};
        SegmentTree st(arr);

        
    }   

    return 0;
}