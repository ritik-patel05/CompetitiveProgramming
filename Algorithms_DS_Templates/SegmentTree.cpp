struct node {
    // attributes
    int val;
    static const int null_v = 888888888;

    // Initialization
    node(): val(0) {}
    node(int v): val(v) {}

    // Merge
    node merge(node &other) {
        return node(min(val, other.val));
    }

    // Lazy Operation
    node lazy_op(int v, int size) {
        return node(val + v);
    }
};


class SegmentTree {
    public:
        void init(int size, vector<int> &arr) {
            n = size;
            tree.assign(4 * size, 0);
            isLazy.assign(4 * size, 0);
            lazy.assign(4 * size, 0);
            build(1, 1, n, arr);
        }
        node query(int l, int r) { return query(1, 1, n, l, r); }
        void upd(int l, int r, int v) { update(1, 1, n, l, r, v); }
        void upd(int pos, int v) { update(1, 1, n, pos, v); }

    private:
        // Variables
        int n;
        vector<node> tree;
        vector<int>lazy;
        vector<bool> isLazy;

        int lc(int id) {
            return id << 1;
        } 

        int rc(int id) {
            return lc(id) + 1;
        }

        void eval_lazy(int id, int l, int r) {
            if(isLazy[id]) {
                // Apply
                tree[id] = tree[id].lazy_op(lazy[id], (r - l + 1));
                // Pass it down
                if(l != r) {

                    lazy[lc(id)] += lazy[id];
                    isLazy[lc(id)] = true;

                    lazy[rc(id)] += lazy[id];
                    isLazy[rc(id)] = true;
                }
                //Reset this node
                isLazy[id] = false;
            }
        }

        node build(int id, int tl, int tr, vector<int> &arr) {
            if(tl == tr) {
                tree[id] = arr[tl];
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            node a = build(lc(id), tl, mid, arr),
                 b = build(rc(id), mid + 1, tr, arr);
            
            return tree[id] = a.merge(b);
        }

        node update(int id, int tl, int tr, int ql, int qr, int v) {
            eval_lazy(id, tl, tr);
            if(tl > tr or tr < ql or tl > qr) 
                return tree[id];
            if(ql <= tl and qr >= tr) {
                // Update lazy values;
                isLazy[id] = true;
                lazy[id] += v;

                eval_lazy(id, tl, tr);
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            node a = update(lc(id), tl, mid, ql, qr, v),
                 b = update(rc(id), mid + 1, tr, ql, qr, v);
            
            return tree[id] = a.merge(b);
        }

        node update(int id, int tl, int tr, int pos, int v) {
            if(tl == tr) {
                return tree[id] = v;
            }
            eval_lazy(id, tl, tr);
            int mid = (tl + tr) >> 1;
            node a = tree[lc(id)], b = tree[rc(id)];
            if(pos <= mid) {
                a = update(lc(id), tl, mid, pos, v);
            } else {
                b = update(rc(id), mid + 1, tr, pos, v);
            }
            
            return tree[id] = a.merge(b);
        }

        node query(int id, int tl, int tr, int ql, int qr) {
            eval_lazy(id, tl, tr);
            if(tl > tr or tr < ql or tl > qr) {
                return node::null_v; // Dummy value
            }
            if(ql <= tl and qr >= tr) {
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            node a = query(lc(id), tl, mid, ql, qr),
                 b = query(rc(id), mid + 1, tr, ql, qr);
            return a.merge(b);
        }

};
