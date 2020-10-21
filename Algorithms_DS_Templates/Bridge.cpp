const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;

int N, M;

int timer = 0;
int u[MAXN], v[MAXN];
int tin[MAXN], tout[MAXN], minAncestor[MAXN];
bool isBridge[MAXM], vis[MAXM];

vector<pair<int, int> > g[MAXN];

void dfs(int v, int p) {

    vis[v] = 1;
    tin[v] = ++timer;
    minAncestor[v] = tin[v];
    
    for(auto &e: g[v]) {
        int to, id;
        tie(to, id) = e;

        if(vis[to]) {
            // a back edge from v - to(not direct ancestor)
            minAncestor[v] = min(minAncestor[v], tin[to]);
        } else {
            dfs(to, v);
            minAncestor[v] = min(minAncestor[v], minAncestor[to]);
            
            if(minAncestor[to] > tin[v]) 
                isBridge[id] = 1;
        }
    }
    
}
