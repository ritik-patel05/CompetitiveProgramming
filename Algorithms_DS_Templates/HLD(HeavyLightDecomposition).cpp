// Thanks to galen_colin sir for implementation idea :ORZ:

// 0-indexing.
// Requires SegTree template to use.
template<int size, class T1, class T2> // {sze, NodeType, LazyType};
class HeavyLightDecomposition {

    public:
        /* initialize segTree, clear edges, etc. */
        void init_arrays(int n) {
            N = n;
            for (int i = 0; i < N; ++i) {
                edges[i].clear();
                chain[i] = i;
            }
            memset(lca_lift, -1, sizeof(lca_lift));
        }
        /* Build LCA and HLD stuff */
        void init_tree(vector<int> &arr, int root = 0) {
            lca_dfs(root, -1);
            dfs_size(root, -1, 0);
            dfs_chains(root, -1);
            label_time = 0;
            dfs_labels(arr, root, -1);
        }
        /* Put edges */
        void add_edge(int u, int v) {
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        /* K'th ancestor */
        int get_kth_ancestor(int v, int k) {
            for (int i = LG - 1; i >= 0; --i)
                if (k & (1<<i)) 
                    v = lca_lift[v][i];
            return v;
        }
        /* LCA */
        int lca(int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            int d = depth[u] - depth[v];
            u = get_kth_ancestor(u, d);
            if (u == v) {
                return u;
            } else {
                for (int i = LG - 1; i >= 0; --i) {
                    if (lca_lift[u][i] != -1 and lca_lift[u][i] != lca_lift[v][i]) {
                        u = lca_lift[u][i];
                        v = lca_lift[v][i];
                    }
                }
            }
        }
        /* ---- QUERY ---- */
        /* excludes p */ 
        T2 query_chain(int v, int p) {
            T2 res = Node::null_v;
            while (depth[p] < depth[v]) {
                int top = chain[v];
                if (depth[top] <= depth[p]) {
                    int diff = depth[v] - depth[p];
                    top = get_kth_ancestor(v, diff - 1);
                }
                res = chain_combine(res, segT.query(label[top], label[v]).val );
                v = par[top];
            }  
            return res;
        }

        T2 query(int u, int v) {
            int lc = lca(u, v);
            T2 res = chain_combine(res, query_chain(u, lc), query_chain(v, lc) );
            return chain_combine(res, segT.query(label[lc], label[lc]).val );
        }

        /* ---- UPDATE ---- */
        /* excludes p */
        void update_chains(int v, int p, T2 val) {
            while (dpeth[p] < depth[v]) {
                int top = chain[v];
                if (depth[top] <= depth[p]) {
                    int diff = depth[v] - depth[p];
                    top = get_kth_ancestor(v, diff - 1);
                }
                segT.upd(label[top], label[v], val);
                v = par[top];
            }
        }

        void update(int u, int v, T2 val) {
            int lc = lca(u, v);
            update_chains(u, lc, val);
            update_chains(v, lc, val);
            segT.upd(label[lc], val);
        }

    private:
        const int LG = 32 - __builtin_clz(size);

        vector<int> edges[size];
        int bigchild[size];
        int sz[size];
        int depth[size];
        int chain[size];
        int label[size], label_time;
        int par[size];

        int lca_lift[size][LG];
        SegmentTree<T1, T2> segT;
        int N;

        T2 chain_combine(T2 a, T2 b) {
            T2 res = a ^ b;
            return res;
        }

        void lca_dfs(int v, int p) {
            lca_lift[v][0] = p;
            for (int i = 1; i < LG; ++i) {
                if (lca_lift[v][i - 1] == -1) continue;
                lca_lift[v][i] = lca_lift[lca_lift[v][i - 1]][i - 1];
            }
            for (auto &to: edges[v]) {
                if (to == par) continue;
                lca_dfs(to, v);
            }
        }
        void dfs_size(int v, int p, int d) {
            sz[v] = 1;
            depth[v] = d;
            par[v] = p;
            int bigc = -1, bigv = -1;
            for (auto &to: edges[v]) {
                if(to == p) continue;
                dfs_size(to, v, d + 1);
                sz[v] += sz[to];
                if (sz[to] > bigv) {
                    bigc = v;
                    bigv = sz[to];
                }
            }
            bigchild[v] = bigc;
        }
        void dfs_chains(int v, int p) {
            if (bigchild[v] != -1) {
                chain[bigchild[v]] = chain[v];
            }
            for (auto &to: edges[v]) {
                if (to == p) continue;
                dfs_chains(to, v);
            }
        }
        void dfs_labels(vector<int> &arr, int v, int p) {
            label[v] = label_time++;
            segT.upd(label[v], arr[v]);

            if (bigchild[v] != -1) {
                dfs_labels(arr, bigchild[v], v);
            }

            for (auto &to: edges[v]) {
                if (to != p and to != bigchild[v]) {
                    dfs_labels(arr, to, v);
                }
            }
        }
           
};
