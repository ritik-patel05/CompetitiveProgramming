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

// #define int long long int
#define ll long long int
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

const int MAXN = 5e3 + 5;
vector<int> g[MAXN];
int N;
vector<int> depth[MAXN];
vector<int> fn;

const int inf = 1e9;

void dfs(int node, int par, int subtree, int lvl){
    depth[lvl].push_back(subtree);
    for(auto &x: g[node]){
        if(x != par){
            dfs(x, node, subtree, lvl + 1);
        }
    }
}

ll cnt(){ //find triplets summation, a[i] * a[j] * a[k]
    ll total = 0, pairs = 0, sum = 0;
    for(int i = 0; i < sz(fn); ++i){
        total += pairs * fn[i];
        pairs += sum * fn[i];
        sum += fn[i];
    }
    return total;
}

void solve(){
    cin >> N;
    for(int i = 1; i < N; ++i){
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    } 

    ll ans = 0;
    for(int i = 1; i <= N; ++i){

        //now get nodes at each depth and which subtree
        //traverse all subtree of this root i

        int id = 0;
        for(int j = 1; j <= N; ++j){
            depth[j].clear();
        }

        for(auto &x: g[i]){
            dfs(x, i, id, 1);
            id++;
        }

        for(int lvl = 1; lvl <= N; ++lvl){
            if(!depth[lvl].empty()){

                fn.clear();
                sort(all(depth[lvl]));

                int k = 0; 
                while(k < sz(depth[lvl])){
                    int l = k;
                    int cnt = 0;
                    while(l < sz(depth[lvl]) and depth[lvl][l] == depth[lvl][k]){
                        ++l; cnt++;
                    }
                    fn.push_back(cnt);
                    k = l;
                }

                ans += cnt();
            }
        }
    }

    cout << ans << '\n';
}



int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr); 
    int T = 1; 
    // cin >> T;
    for(int i = 1; i <= T; ++i){
        // brute();
        solve();
    }
    return 0;
}

/*
Sample inp
*/
