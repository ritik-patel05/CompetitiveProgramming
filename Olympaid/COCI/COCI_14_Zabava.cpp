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

const int MAXN = 105;
int cnt[MAXN];
int N, M, K;

int AP(int x){
    return x * (x + 1) / 2;
}

int get(int n, int k){
    int groups = k + 1;
    int val1 = n / groups;
    int val2 = (n + groups - 1) / groups;
    int extra = n % groups;
    int normal = groups - extra;
    return normal * AP(val1) + extra * AP(val2);
}

int memo[105][505];

int dp(int id, int left){
    if(id == M + 1){
        return 0;
    }
    auto &res = memo[id][left];
    if(res != -1){
        return res;
    }
    res = 1e13;
    //use k partitions on this building.
    for(int k = 0; k <= min(cnt[id], left); ++k){
        int now = left - k;
        res = min(res, get(cnt[id], k) + dp(id + 1, now));
    }
    return res;
}


 
void solve(){
    cin >> N >> M >> K;
    for(int i = 1; i <= N; ++i){
        int x; cin >> x;
        cnt[x]++;
    }
    memset(memo, -1, sizeof(memo));
    cout << dp(1, K) << '\n';
    
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
