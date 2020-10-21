// Prims - O(N ^2) Implementation.

const int MAXN = 1e5 + 5, INF = 2e9;
bool vis[MAXN];
int N, M, dist[MAXN], par[MAXN];
vector<pair<int, int> > g[MAXN];

void prim() {

    fill(vis, vis + N + 1, false);
    fill(dist, dist + N + 1, INF);

    int ds, v, cost = 0;

    while(true) {
        ds = INF, v = -1;

        for(int i = 1; i <= N; ++i)
            if(!vis[i] and ds >= dist[i])
                ds = dist[i], v = i;

        if(v == -1)
            break;
        
        cost += dist[v];
        dist[v] = 0;
        vis[v] = true;
        for(auto &e: g[v]) {
            int to, w;
            tie(to, w) = e;
            dist[to] = min(dist[to], w);
        }

    }
}

// Prims - O(Mlog(N)) Implementation

const int MAXN = 1e5 + 5, INF = 2e9;
int N, M, dist[MAXN], par[MAXN];
vector<pair<int, int> > g[MAXN], tree[MAXN];

int prim(int src) { // Returns mst and creates mst tree.

    fill(dist + 1, dist + N + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    pq.push({0, src});
    dist[src] = 0;
    int cost = 0;

    while(!pq.empty()) {

        auto cur = pq.top(); pq.pop();
        int v, d;
        tie(d, v) = cur;

        if(dist[v] < d) {
            continue;
        }

        cost += d;
        dist[v] = 0;
        int p = par[v];

        tree[v].push_back({p, d});
        tree[p].push_back({v, d});

        for(auto &e: g[v]) {
            int to, w;
            tie(to, w) = e;
            if(dist[to] > w) {
                dist[to] = w; 
                par[to] = v;
                pq.push({dist[to], to});
            }
        }

    }
}
