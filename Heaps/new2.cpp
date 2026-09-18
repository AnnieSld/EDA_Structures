// Persistent segment tree

#include <iostream>
#include <vector>
using namespace::std;


//Persistent Stack implementation
template<typename data_type>

struct PersistentSegmentTree {
    struct SegmentTreeNode {
        data_type data;
        SegmentTreeNode *left, *right;
        }    
        
        PersistentSegmentTree(int l, int r){
            version_roots.emplace_back(SegmentTreeNode(data_type(),l, r));
            build(version_roots[0]);

        }

    void update()
    void update(int version, int index, data_type val){
        version_roots.emplace_back(update(version_roots[version], index, val));
    }
    void build(SegmentTreeNode * node){
        if(node->l == node->r) return;
        int mid = (node->l + node->r) / 2;
        node->left = new SegmentTreeNode(data_type(), node->l, mid);
        node->right = new SegmentTreeNode(data_type(), mid + 1, node->r);
        build(node->left);
        build(node->right);
    }

    data_type query(int x, int y, SegmentTreeNode * node){
        if(node->l > y || node->r < x) return data_type();
        if(node->l >= x && node->r <= y) return node->data;
        return query(x, y, node->left) + query(x, y, node->right);
    }
    
    data_type query(int version, int l, int r){
        return query(version_roots[version], l, r);
    }
}
