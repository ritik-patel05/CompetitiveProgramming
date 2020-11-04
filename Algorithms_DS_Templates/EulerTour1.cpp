const int MAXN = 1e5 + 5;
vector<int> parent, inTime, outTime, euler_order;
vector<bool> vis;

void init(int _sz) {
    parent.resize(_sz), inTime.resize(_sz), outTime.resize(_sz), euler_order.resize(_sz);
    vis.assign(_sz, 0);
}

void dfs(int v, int p = -1) {
    parent[v] = v;
    vis[v] = true;
    inTime[v] = ++timer;
    euler_order[timer] = v;
    for (auto &to: g[v]) {
        if(!vis[to])
            dfs(to, v);
    }
    outTime[v] = timer;
}

void euler_tour(int root) {
    init(_sz);
    dfs(root, -1);
}
