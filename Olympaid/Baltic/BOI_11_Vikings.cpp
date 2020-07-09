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
 
const int MAXN = 705;
char g[MAXN][MAXN];
int N, M;
int sx, sy;
int tx, ty;
int vx, vy;
const int inf = 1e9;
int vd[MAXN][MAXN];
int cover[MAXN][MAXN];
bool vis[MAXN][MAXN];
 
void bfs(){
    queue<pair<int, pair<int, int>>> q;
 
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= M; ++j)
            vd[i][j] = cover[i][j] = inf;
 
    auto valid = [&](int i, int j){
        if(i >= 1 and i <= N and j >= 1 and j <= M)
            return true;
        return false;
    };
 
    q.push({0, {vx, vy}});
    vd[vx][vy] = 0;
    while(!q.empty()){
 
        auto p = q.front(); q.pop();
        int d = p.first;
        int x = p.second.first, y = p.second.second; 
 
        for(int k = 0; k < 4; ++k){
            int nx = x + dx4[k];
            int ny = y + dy4[k];
            if(valid(nx, ny) and vd[nx][ny] == inf and g[nx][ny] != 'I'){
                vd[nx][ny] = d + 1;
                q.push({d + 1, {nx, ny}});
            }
        }
    }
 
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            if(vd[i][j] == inf){
                continue;
            }
            cover[i][j] = min(cover[i][j], vd[i][j]);
            for(int k = j + 1; k <= M and g[i][k] != 'I'; ++k){
                cover[i][k] = min(cover[i][k], vd[i][j]);
            }
            for(int k = j - 1; k >= 1 and g[i][k] != 'I'; --k){
                cover[i][k] = min(cover[i][k], vd[i][j]);
            }
            for(int k = i + 1; k <= N and g[k][j] != 'I'; ++k){
                cover[k][j] = min(cover[k][j], vd[i][j]);
            }
            for(int k = i - 1; k >= 1 and g[k][j] != 'I'; --k){
                cover[k][j] = min(cover[k][j], vd[i][j]);
            }
        }
    }
 
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= M; ++j)
            cover[i][j] = max(cover[i][j], (int)1);
    
    q.push({0, {sx, sy}});
    while(!q.empty()){
        auto p = q.front(); q.pop();
        int d = p.first, x = p.second.first, y = p.second.second;
        if(x == tx and y == ty){
            cout << "YES\n";
            return;
        }
        for(int k = 0; k < 4; ++k){
            int nx = x + dx4[k];
            int ny = y + dy4[k];
            if(valid(nx, ny) and !vis[nx][ny] and g[nx][ny] != 'I' and d + 1 < cover[nx][ny]){
                vis[nx][ny] = true;
                q.push({d + 1, {nx, ny}});
            }
        }
    }
    cout << "NO\n";
    return;
}
 
void solve(){
    cin >> N >> M;
    
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> g[i][j];
            if(g[i][j] == 'Y')
                sx = i, sy = j;
            else if(g[i][j] == 'V')
                vx = i, vy = j;
            else if(g[i][j] == 'T')
                tx = i, ty = j;
        }
    }
 
    bfs();
     
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
