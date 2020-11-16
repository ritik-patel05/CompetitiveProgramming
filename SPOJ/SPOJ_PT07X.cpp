/*
Author: Ritik Patel
Idea: If we see, each vertex has two options of being taken or not. Jus like knapsack.
        So we can do a dp on tree as
        dp[v][taken] += min(dp[to][!taken], dp[to][taken]);
        dp[v][!taken] += dp[to][taken];
*/


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& LIBRARIES &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#include <bits/stdc++.h>
using namespace std;
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEFINES &&&&&&&&&&&&&&&&&&&&&&&&&&&

#define int long long int
// #define ll long long int
#define all(i) i.begin(), i.end()
#define SZ(a) (int)a.size()
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& CODE &&&&&&&&&&&&&&&&&&&&&&&&&&&

const int MAXN = 1e5 + 5;
vector<int> g[MAXN];
int dp[MAXN][2];

void dfs(int v, int taken, int p) {
    if (dp[v][taken] > 1) return;
    dp[v][taken] = (taken ? 1 :0);
    for (auto &to: g[v]) {
        if (to == p) continue;
        dfs(to, taken ^ 1, v);
        if (taken) {
            dfs(to, taken, v);
            dp[v][taken] += min(dp[to][taken ^ 1], dp[to][taken] );
        } else {
            dp[v][taken] += dp[to][taken ^ 1];
        }
    }
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    dfs(1, 0, -1);
    dfs(1, 1, -1);
    cout << min(dp[1][0], dp[1][1]) << '\n';
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
