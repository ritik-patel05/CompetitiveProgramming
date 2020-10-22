const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;

int N, M, timer, compid;

vector<pair<int, int>> g[MAXN];
bool used[MAXN], isBridge[MAXM];
int comp[MAXN], tin[MAXN], minAncestor[MAXN];

vector<int> tree[MAXN]; // Store 2-edge-connected component tree.(Bridge tree).

void dfs(int v, int p) {
    tin[v] = minAncestor[v] = ++timer;
    used[v] = 1;
    for(auto &e: g[v]) {
        int to, id;
        tie(to, id) = e;
        if(to == p) continue;
        if(used[to]) {
            minAncestor[v] = min(minAncestor[v], tin[to]);
        } else {
            dfs(to, v);
            minAncestor[v] = min(minAncestor[v], minAncestor[to]);
            if(minAncestor[to] > tin[v]) {
                isBridge[id] = true;
            }
        }
    }
}

void dfs1(int v, int p) {
    used[v] = 1;
    comp[v] = compid;
    for(auto &e: g[v]) {
        int to, id;
        tie(to, id) = e;
        
        if(isBridge[id]) { // avoid traversing from this edge. so we get full component.
            continue;
        }
        if(used[to]) {
            continue;
        }
        dfs1(to, v);
    }
}

vector<pair<int, int>> edges;

void addEdge(int from, int to, int id) {
    g[from].push_back({to, id});
    g[to].push_back({from, id});
    edges[id] = {from, to};
}

void bridge_tree() {
    timer = 0;
    for(int i = 1; i <= N; ++i)
        used[i] = 0;
    
    dfs(1, -1); //Assuming graph is connected.

    compid = 0;
    for(int i = 1; i <= N; ++i)
        used[i] = 0;

    for(int i = 1; i <= N; ++i) {
        if(!used[i]) {
            dfs1(i, -1);
            ++compid;
        }
    }

    for(int i = 1; i <= M; ++i) {
        if(isBridge[i]) {
            int u, v;
            tie(u, v) = edges[i];
            // connect two componets using edge.
            tree[comp[u]].push_back(comp[v]);
            tree[comp[v]].push_back(comp[u]);
        }
    }
}

void solve() {
    cin >> N >> M;
    edges.resize(M + 1);
    for(int i = 1; i <= M; ++i) {
        int u, v;
        cin >> u >> v; addEdge(u, v, i);
    }
    bridge_tree();

    cout << "Each node belongs to components-id: \n";
    for(int i = 1; i <= N; ++i) {
        debug(i, comp[i]);
    }

    cout << "Tree is \n";
    for(int i = 0; i < compid; ++i) {
        cout << i << " Its son's are: ";
        for(auto &x: tree[i])
            cout << x << " ";
        cout << '\n';
    }

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

//  Problem: https://codeforces.com/contest/652/problem/E
// Submission: https://codeforces.com/contest/652/submission/96365943
 
