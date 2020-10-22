const int MAXN = 1e5 + 5;

int N, M;
vector<int> g[MAXN], rg[MAXN], cg[MAXN];
vector<int> ord;
bool used[MAXN];
int comp[MAXN], cnt;

void dfs1(int v) {
    used[v] = true;
    for (auto &to: g[v])
        if (!used[to])
            dfs1(to);
    ord.push_back(v);
}

void dfs2(int v) {
    comp[v] = cnt;
    for (auto &to: rg[v]) {
        if (comp[to] == -1)
            dfs2(to);
    }
}

void sccAddEdge(int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
}

void scc() {

    cnt = 0;
    for (int i = 1; i <= N; ++i)
        comp[i] = -1, used[i] = 0;
    
    for (int i = 1; i <= N; ++i) 
        if (!used[i])
            dfs1(i);
    
    reverse(all(ord));

    for (auto &x: ord) 
        if (comp[x] == -1)
            dfs2(x), ++cnt;
    
    // Build scc graph.
    for (int v = 1; v <= N; ++v) {
        for (auto to: g[v]) {
            if (comp[v] == comp[to]) continue;
            cg[comp[v]].push_back(comp[to]); // NOTE: One comp can come more than once here.
        }
    }

}
