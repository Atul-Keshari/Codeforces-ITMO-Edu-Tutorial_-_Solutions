#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define pb push_back
#define ll long long
#define f first
#define s second
#define vl vector<ll>
#define pl pair<ll,ll>
#define vpl vector<pair<ll,ll>>
#define vvl vector<vector<ll>>
#define rep(i,n) for(ll i=0;i<n;i++)
#define repp(i,k,n) for(ll i=k;i<n;i++)
#define en "\n"

class SegmentTree {
    vpl tree;
    ll size;

public:
    SegmentTree(vl& array) {
        size = array.size();
        tree.resize(4 * size);
        buildTree(array, 0, 0, size - 1);
    }

    void updateTree(vl& array, ll treeIndex, ll left, ll right, ll index, ll value) {
        if (index < left || index > right) return;
        if (left == right) {
            tree[treeIndex] = {value, 1}; 
            array[index] = value;
            return;
        }

        ll mid = left + (right - left) / 2;
        updateTree(array, 2 * treeIndex + 1, left, mid, index, value);
        updateTree(array, 2 * treeIndex + 2, mid + 1, right, index, value);
        mergeNodes(treeIndex);  
    }

    pl queryTree(ll treeIndex, ll left, ll right, ll queryLeft, ll queryRight) {
        if (queryRight < left || queryLeft > right) return {INT_MAX, 0};  
        if (queryLeft <= left && queryRight >= right) return tree[treeIndex];  

        ll mid = left + (right - left) / 2;
        pl leftResult = queryTree(2 * treeIndex + 1, left, mid, queryLeft, queryRight);
        pl rightResult = queryTree(2 * treeIndex + 2, mid + 1, right, queryLeft, queryRight);
        return mergeResults(leftResult, rightResult); 
    }

private:
    void buildTree(vl& array, ll treeIndex, ll left, ll right) {
        if (left == right) {
            tree[treeIndex] = {array[left], 1};  
            return;
        }

        ll mid = left + (right - left) / 2;
        buildTree(array, 2 * treeIndex + 1, left, mid);
        buildTree(array, 2 * treeIndex + 2, mid + 1, right);
        mergeNodes(treeIndex); 
    }

    void mergeNodes(ll treeIndex) {
        pl leftChild = tree[2 * treeIndex + 1];
        pl rightChild = tree[2 * treeIndex + 2];

        if (leftChild.f == rightChild.f) {
            tree[treeIndex] = {leftChild.f, leftChild.s + rightChild.s}; 
        } else if (leftChild.f < rightChild.f) {
            tree[treeIndex] = leftChild;  
        } else {
            tree[treeIndex] = rightChild;  
        }
    }

    pl mergeResults(pl leftResult, pl rightResult) {
        if (leftResult.f == rightResult.f) {
            return {leftResult.f, leftResult.s + rightResult.s};  
        } else if (leftResult.f < rightResult.f) {
            return leftResult;  
        } else {
            return rightResult; 
        }
    }
};

void solve() {
    ll n, m;
    cin >> n >> m;
    vl a(n);
    rep(i, n) cin >> a[i];

    SegmentTree st(a);

    rep(i, m) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll ind, val;
            cin >> ind >> val;
            st.updateTree(a, 0, 0, n - 1, ind, val);
        } else {
            ll l, r;
            cin >> l >> r;
            pl result = st.queryTree(0, 0, n - 1, l, r - 1);
            cout << result.f << " " << result.s << en;
        }
    }
}

int main() {
    fast;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
