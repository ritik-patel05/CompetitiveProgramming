struct DSU {

    vector<int> par, sze;
    int connected;

    void init(int n) {
        par.resize(n), sze.resize(n);
        for(int i = 1; i <= n; ++i) 
            par[i] = i, sze[i] = 1;
        connected = n;
    }

    int get_par(int x) {
        if(x == par[x]) return x;
        return par[x] = get_par(par[x]);
    }

    void merge(int u, int v) {
        if( (u = par[u]) != (v = par[v])) {
            connected--;
            if(sze[u] < sze[v]) {
                swap(u, v);
            }
            sze[u] += sze[v]; sze[v] = 0;
            par[v] = par[u];
        }
    }   
};

struct edge{
    int u, v, w, id;
    edge() {}
    edge(int u, int v, int w, int id) : u(u) , v(v) , w(w), id(id) {}
};

const int MAXN = 1e5 + 5;
vector<pair<int, int> > g[MAXN];
int N, M;
edge edges[MAXN];

void add_edge(int id, int u, int v, int w){
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
    edges[id] = edge(u, v, w, id);
}

bool comp(edge &e1, edge &e2){
    return e1.w < e2.w;
}

int kruskalMST(){
    DSU dsu;
    dsu.init(N + 1);
    int cost = 0;
    sort(edges + 1, edges + M + 1, comp);
    for(int i = 1; i <= M; ++i) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if( (u = dsu.get_par(u)) != (v = dsu.get_par(v)) ) {
            dsu.merge(u, v);
            cost += w;
        }
    }
}
