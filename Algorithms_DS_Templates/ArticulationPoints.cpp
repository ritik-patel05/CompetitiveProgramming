const int MAXN = 1e5 + 5;

vector<int> g[MAXN];
int timer = 0;
bool isArticulation[MAXN], used[MAXN];
int tin[MAXN], tout[MAXN], minAncestor[MAXN];

void dfs(int v, int p = -1) {
    used[v] = 1;
    tin[v] = minAncestor[v] = ++timer;
    int children = 0;

    for (auto &to: g[v]) {
        if (to == p) continue;
        if (used[to]) {
            minAncestor[v] = min(minAncestor[v], tin[to]);
        } else {

            dfs(to, v);
            minAncestor[v] = min(minAncestor[v], minAncestor[to]);
            
            if (minAncestor[to] >= tin[v] and p != -1) {
                isArticulation[v] = true;
            }
        }
    }

    tout[v] = timer;

    if(p == -1 and children > 1)
        isArticulation[v] = true;
}
