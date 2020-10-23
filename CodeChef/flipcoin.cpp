/*
	Author: Ritik Patel
*/
 
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& STL DEBUGGER &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
// #define _GLIBCXX_DEBUG       // Iterator safety; out-of-bounds access for Containers, etc.
// #pragma GCC optimize "trapv" // abort() on (signed) integer overflow.
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& LIBRARIES &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#include <bits/stdc++.h>
using namespace std;
 
/*#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; 
*/
//find_by_order()->returns an iterator to the k-th largest element(0-based indexing)
//order_of_key()->Number of items that are strictly smaller than our item
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEFINES &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#define int long long int
// #define ll long long int
#define all(i) i.begin(), i.end()
#define sz(a) (int)a.size()
 
// #define ld long double
// const ld PI  = 3.141592;
const int dx4[4] = {0, 1, 0, -1};
const int dy4[4] = {-1, 0, 1, 0};
const int dx8[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEBUG &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#define XOX
vector<string> vec_splitter(string s) {
    for(char& c: s) c = c == ','?  ' ': c;
    stringstream ss; ss << s;
    vector<string> res;
    for(string z; ss >> z; res.push_back(z));
    return res;
}
 
void debug_out(vector<string> __attribute__ ((unused)) args, __attribute__ ((unused)) int idx) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, T...);
}
 
#ifdef XOX
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __VA_ARGS__)
#else
#define debug(...) 42
#endif
 
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& CODE &&&&&&&&&&&&&&&&&&&&&&&&&&&

const int MAXN = 1e5 + 5;

struct node {
    bool isLazy = 0;
    int totalTails = 0; // 0-> tails, 1-> heads

    node() {};
    node(bool isLazy, int totalTails) : isLazy(isLazy), totalTails(totalTails) {};
};

vector<node> tree(4 * MAXN);

inline int lc(int i) {
    return i * 2;
}

inline int rc(int i) {
    return i * 2 + 1;
}

node merge(const node &a, const node &b) {
    return node(0, a.totalTails + b.totalTails);
}

void build(int id, int tl, int tr) {
    if(tl == tr) {
        tree[id] = node(0, 1);
        // debug(id, tl, tree[id].totalTails);
        return;
    }
    int mid = (tl + tr) >> 1;
    build(lc(id), tl, mid);
    build(rc(id), mid + 1, tr);

    tree[id] = merge(tree[lc(id)], tree[rc(id)]);
    // debug(id, tl, tr, tree[id].totalTails);
}

void lazy(int id, int tl, int tr) {

    if(!tree[id].isLazy) return;

    tree[id].isLazy = false;
    int total = tr - tl + 1;
    int mine = tree[id].totalTails;
    tree[id].totalTails = total - mine;

    if(tl != tr)
        tree[lc(id)].isLazy ^= 1,
        tree[rc(id)].isLazy ^= 1;

} 

void update(int id, int tl, int tr, int l , int r) {
    lazy(id, tl, tr);
    if(tl > r or tr < l) return;
    if(l <= tl and r >= tr) {
        tree[id].isLazy ^= 1;
        lazy(id, tl, tr); // Update the current node, so parent nodes have correct value.
        // debug(id, tl, tree[id].isLazy, tree[id].totalTails);
        return;
    }
    
    int mid = (tl + tr) >> 1;
    update(lc(id), tl, mid, l, r);
    update(rc(id), mid + 1, tr, l, r);

    tree[id] = merge(tree[lc(id)], tree[rc(id)]);
    // debug(id, tl, tr, tree[id].totalTails, tree[id].isLazy);
}

node query(int id, int tl, int tr, int l, int r) {
    lazy(id, tl, tr);
    if(tl > r or tr < l) return node(0, 0);
    if(l <= tl and r >= tr) {
        // debug(id, tl, tr, l, r, tree[id].isLazy, tree[id].totalTails);
        return tree[id];
    }

    int mid = (tl + tr) >> 1;
    node lq = query(lc(id), tl, mid, l, r);
    node rq = query(rc(id), mid + 1, tr, l, r);

    // debug(id, tl, tr, tree[id].isLazy, tree[id].totalTails);
    return merge(lq, rq);
}

void solve(){
    int N, M;
    cin >> N >> M;
    build(1, 1, N);
    for(int i = 0; i < M; ++i) {
        int q; cin >> q;
        if(q == 1) {
            int l, r; cin >> l >> r; ++l, ++r;
            cout <<  r - l  + 1 - query(1, 1, N, l, r).totalTails << '\n';
        } else {
            int l, r; cin >> l >> r; ++l, ++r;
            update(1, 1, N, l, r);
        }
    }
}

int32_t main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout); 
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    int T = 1; 
    // cin >> T;
    for(int i = 1; i <= T; ++i){
        // cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
 
/*
Sample inp
*/
