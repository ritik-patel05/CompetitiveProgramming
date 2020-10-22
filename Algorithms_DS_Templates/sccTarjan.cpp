const int MAXN = 1e5 + 5;

int N, M;

vector<int> g[MAXN], cg[MAXN];
int timer = 0;
bool inStack[MAXN], used[MAXN];
int tin[MAXN], tout[MAXN], minAncestor[MAXN], comp[MAXN];
stack<int> st;
int cnt = 0;

void dfs(int v, int p = -1) {
    used[v] = true;
    tin[v] = minAncestor[v] = ++timer;
    inStack[v] = true;
    st.push(v);

    for (auto &to: g[v]) {
        if (to == p) continue;
        if (inStack[to]) { // Back edge.
            minAncestor[v] = min(minAncestor[v], tin[to]);
        } else {

            dfs(to, v);
            minAncestor[v] = min(minAncestor[v], minAncestor[to]);
        }
    }

    // If its the root of an SCC.
    if (minAncestor[v] == tin[v]) {
        while(st.top() != v) {
            comp[st.top()] = cnt;
            inStack[st.top()] = false;
            st.pop();
        }
        st.pop(); 
        inStack[v] = false; comp[v] = cnt;
        ++cnt;
    }
   
}

void scc() {
    
    cnt = 0;
    for (int i = 1; i <= N; ++i)
        used[i] = false, comp[i] = -1;
    
    for(int i = 1; i <= N; ++i)
        if(comp[i] == -1)
            dfs(i);
    
    // Build scc graph.
    for (int v = 1; v <= N; ++v) {
        for (auto to: g[v]) {
            if (comp[v] == comp[to]) continue;
            cg[comp[v]].push_back(comp[to]); // NOTE: One comp can come more than once here.
        }
    }

}
