#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define pb push_back
#define ll long long
#define vl vector<ll>
#define pl pair<ll,ll>
#define vpl vector<pair<ll,ll>>
#define vvl vector<vector<ll>>
#define rep(i,n) for(ll i=0;i<n;i++)
#define repp(i,k,n) for(ll i=k;i<n;i++)
#define en "\n"
class SegmentTree {
    vl tree;
    ll size;
public:
    SegmentTree(vl& array) {
        size = array.size();
        tree.resize(4 * size);
        buildTree(array, 0, 0, size - 1);
    }
    void updateTree(vl& array, ll treeIndex, ll left, ll right, ll index, ll value) {
        if(index<left || index>right) return;
        if(left==right){
            tree[treeIndex]=value;
            array[index]=value;
            return;
        }
        ll mid = left + (right - left) / 2;
        updateTree(array, 2 * treeIndex + 1, left, mid, index, value);
        updateTree(array, 2 * treeIndex + 2, mid + 1, right, index, value);
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];
    }
    ll queryTree(ll treeIndex, ll left, ll right, ll queryLeft, ll queryRight) {
        if(queryRight<left || queryLeft>right) return 0;
        if(queryLeft<=left && queryRight>=right) return tree[treeIndex];
        ll mid = left + (right - left) / 2;
        ll leftResult = queryTree(2 * treeIndex + 1, left, mid, queryLeft, queryRight);
        ll rightResult = queryTree(2 * treeIndex + 2, mid + 1, right, queryLeft, queryRight);
        return leftResult + rightResult;
    }
private:
    void buildTree(vl& array, ll treeIndex, ll left, ll right) {
        if (left == right) {
            tree[treeIndex] = array[left];
            return;
        }
        ll mid = left + (right - left) / 2;
        buildTree(array, 2 * treeIndex + 1, left, mid);
        buildTree(array, 2 * treeIndex + 2, mid + 1, right);
        tree[treeIndex] = tree[2 * treeIndex + 1]+ tree[2 * treeIndex + 2];
    }
};
void solve(){
    ll n,m;
    cin>>n>>m;
    vl a(n);
    rep(i,n)cin>>a[i];
    SegmentTree st(a);
    rep(i,m){
        ll t;
        cin>>t;
        if(t==1){
            ll ind,val;
            cin>>ind>>val;
            st.updateTree(a,0,0,n-1,ind,val);
        }
        else{
            ll l,r;
            cin>>l>>r;
            cout<<st.queryTree(0,0,n-1,l,r-1)<<en;
        }
    }
}
int main()
{

    fast;
    int t=1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
