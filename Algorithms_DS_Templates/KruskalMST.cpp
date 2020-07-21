const int MAXN = ;

struct edge{
    int u, v, w, id;
    edge() {}
    edge(int u, int v, int w, int id) : u(u) , v(v) , w(w), id(id) {}
};

int N, M;
int connected;
int root[MAXN], sz[MAXN];
vector<pair<int, int> > g[MAXN];
edge edges[MAXN];

void init(){
    for(int i = 1; i <= N; ++i){
        root[i] = i;
        sz[i] = 1;
    }
    connected = N;
}

int get_par(int x){
    if(x == root[x]){
        return x;
    }
    return root[x] = get_par(root[x]);
}

void merge(int u, int v){
    u = get_par(u);
    v = get_par(v);

    if(u == v){
        return;
    }

    connected--;

    if(sz(u) > sz(v)){
        swap(u, v);
    }

    sz[v] += sz[u];
    sz[u] = 0;
    root[v] = root[u];
}

void add_edge(int id, int u, int v, int w){
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
    edges[id] = edge(u, v, w, id);
}

bool comp(edge &e1, edge &e2){
    return e1.w < e2.w;
}

int kruskalMST(){
    init();
    int cost = 0;
    sort(edges + 1, edges + M + 1, comp);
    for(int i = 1; i <= M; ++i){
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        u = get_par(u), v = get_par(v);
        if(u == v){
            continue;
        } else {
            cost += w;
            merge(u, v);
        }
    }
    return cost;
}
