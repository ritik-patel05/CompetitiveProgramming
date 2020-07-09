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
 
const int MAXN = 505;
char g[MAXN][MAXN];
int cost[MAXN][MAXN];
int dist[MAXN][MAXN];
int N, M;
const int inf = (int)1e13;
 
 
int bfs(){
 
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= M; ++j)
            dist[i][j] = inf;
 
    deque<pair<int, int>> q;
    q.push_front({1,1});
    dist[1][1] = cost[1][1];
 
    auto valid = [&](int x, int y){
        if(x >= 1 and x <= N and y >= 1 and y <= M)
            return true;
        return false;
    };
 
    while(!q.empty()){
        auto p = q.front();
        int x = p.first;
        int y = p.second;
        q.pop_front();
        for(int k = 0; k < 8; ++k){
            int nx = x + dx8[k];
            int ny = y + dy8[k];
            if((x + y)&1){
                if(nx == x - 1 and ny == y - 1)
                    continue;
                if(nx == x + 1 and ny == y + 1)
                    continue;
            } else {
                if(nx == x + 1 and ny == y - 1)
                    continue;
                if(nx == x - 1 and ny == y + 1)
                    continue;
            }
            if(valid(nx, ny) and dist[nx][ny] > dist[x][y] + cost[nx][ny]){
                dist[nx][ny] = dist[x][y] + cost[nx][ny];
                if(cost[nx][ny] == 0){
                    q.push_front({nx, ny});
                } else {
                    q.push_back({nx, ny});
                }
            }
        }
    }
    return dist[N][M];
}
 
void solve(){
 
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= M; ++j){
            cin >> g[i][j];
            int sum = i + j;
            if(g[i][j] == '/'){
                cost[i][j] = ((sum&1) ? 0 : 1);  
            } else {
                cost[i][j] = ((sum&1) ? 1 : 0);
            }
        }
    }
 
    if((N + M)&1){
        cout << "NO SOLUTION";
        return;
    }
    cout << bfs() << '\n';
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
