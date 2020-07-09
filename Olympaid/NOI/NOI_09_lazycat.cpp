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

const int MAXN = 33;
char g[MAXN][MAXN];
int N;
int dist[MAXN][MAXN][MAXN][MAXN];
const int inf = 1e8;

int sx, sy, ex, ey;
int c = 0;
int memo[1<<12][MAXN][MAXN];
pair<int, int> food[12];

void bfs(int i, int j){
    dist[i][j][i][j] = 0;
    queue<pair<int, int>> q;
    q.push({i, j});

    auto valid = [&](int x, int y){
        if(x >= 1 and x <= N and y >= 1 and y <= N){
            return true;
        }
        return false;
    };

    while(!q.empty()){
        auto p = q.front();
        int x = p.first;
        int y = p.second;
        q.pop();
        for(int k = 0; k < 4; ++k){
            int nx = x + dx4[k];
            int ny = y + dy4[k];
            if( valid(nx, ny) and dist[i][j][nx][ny] == inf and g[nx][ny] != 'X'){
                dist[i][j][nx][ny] = dist[i][j][x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int dp(int mask, int i, int j){
    if(mask == (1<<c) - 1){
        return dist[i][j][ex][ey];
    }
    auto &res = memo[mask][i][j];
    if(res != -1){
        return res;
    }
    res = inf;
    for(int k = 0; k < c; ++k){
        if( ( (1<<k)&mask ) == 0 and dist[i][j][food[k].first][food[k].second] < inf ){
            res = min(res, dp( (1<<k)|mask, food[k].first, food[k].second) + dist[i][j][food[k].first][food[k].second] );
        }
    }
    return res;
}

void solve(){
    cin >> N;
    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            cin >> g[i][j];
        }
    }  
    for(int i = 1; i <= N; ++i)
        for(int j = 1; j <= N; ++j)
            for(int k = 1; k <= N; ++k)
                for(int l = 1; l <= N; ++l)
                    dist[i][j][k][l] = inf;

    for(int i = 1; i <= N; ++i){
        for(int j = 1; j <= N; ++j){
            if(g[i][j] == 'X'){
                continue;
            }
            bfs(i, j);
            if(g[i][j] == 'F'){
                food[c++] = {i, j};
            } else if(g[i][j] == 'S'){
                sx = i; sy = j;
            } else if(g[i][j] == 'B'){
                ex = i; ey = j;
            } 
        }
    }

    // for(int i = 1; i <= N; ++i){
    //     for(int j = 1; j <= N; ++j){
    //         debug(i, j);
    //         for(int k = 1; k <= N; ++k){
    //             for(int l = 1; l <= N; ++l){
    //                 cout << dist[i][j][k][l] << " ";
    //             }
    //             cout << '\n';
    //         }
    //     }
    // }
    memset(memo, -1, sizeof(memo));
    int res = dp(0, sx, sy);
    if(res >= inf){
        cout << -1 << '\n';
    } else {
        cout << res << '\n';
    }
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
