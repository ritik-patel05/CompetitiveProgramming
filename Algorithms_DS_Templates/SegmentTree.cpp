class Node {
    // attributes
    public:
        int val;
        static const int null_v = 888888888;
    
        // Initialization
        Node(): val(0) {}
        Node(int v): val(v) {}

        // Merge
        Node merge(Node &other) {
            return Node(min(val, other.val));
        }

        // Lazy Operation
        Node lazy_op(int v, int size) {
            return Node(val + v);
        }
};

// 0-Indexed.
//SegmentTree <NodeType, lazyType> segt;
template<class T1, class T2>
class SegmentTree {
    public:
        void init(int size, vector<int> &arr) {
            N = size;
            tree.assign(4 * size, 0);
            isLazy.assign(4 * size, 0);
            lazy.assign(4 * size, 0);
            build(1, 0, n - 1, arr);
        }
        T1 query(int l, int r) { return query(1, 0, N - 1, l, r); }
        void upd(int l, int r, int v) { update(1, 0, N - 1, l, r, v); }
        void upd(int pos, int v) { update(1, 0, N - 1, pos, v); }

    private:
        // Variables
        int N;
        vector<T1> tree;
        vector<T2> lazy;
        vector<bool> isLazy;

        int lc(int id) {
            return id << 1;
        } 

        int rc(int id) {
            return lc(id) + 1;
        }

        void eval_lazy(int id, int l, int r) {
            if (!isLazy[id]) return;
            
            tree[id] = tree[id].lazy_op(lazy[id], (r - l + 1)); // Apply

            if (l != r) { // Pass it down
                lazy[lc(id)] += lazy[id];
                isLazy[lc(id)] = true;

                lazy[rc(id)] += lazy[id];
                isLazy[rc(id)] = true;
            }
            
            isLazy[id] = false; //Reset this Node
            lazy[id] = Node::null_v;
            
        }

        T1 build(int id, int tl, int tr, vector<int> &arr) {
            if (tl == tr) {
                tree[id] = T1(arr[tl]);
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            T1 a = build(lc(id), tl, mid, arr),
               b = build(rc(id), mid + 1, tr, arr);
            
            return tree[id] = a.merge(b);
        }

        T1 update(int id, int tl, int tr, int ql, int qr, T2 v) {
            eval_lazy(id, tl, tr);
            if (tl > tr or tr < ql or tl > qr) 
                return tree[id];
            if (ql <= tl and qr >= tr) {
                // Update lazy values;
                isLazy[id] = true;
                lazy[id] += v;

                eval_lazy(id, tl, tr);
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            T1 a = update(lc(id), tl, mid, ql, qr, v),
               b = update(rc(id), mid + 1, tr, ql, qr, v);
            
            return tree[id] = a.merge(b);
        }

        T1 update(int id, int tl, int tr, int pos, T2 v) {
            if (tl == tr) {
                return tree[id] = v;
            }
            eval_lazy(id, tl, tr);
            int mid = (tl + tr) >> 1;
            T1 a = tree[lc(id)], b = tree[rc(id)];
            if (pos <= mid) {
                a = update(lc(id), tl, mid, pos, v);
            } else {
                b = update(rc(id), mid + 1, tr, pos, v);
            }
            
            return tree[id] = a.merge(b);
        }

        T1 query(int id, int tl, int tr, int ql, int qr) {
            eval_lazy(id, tl, tr);
            if (tl > tr or tr < ql or tl > qr) {
                return Node::null_v; // Dummy value
            }
            if (ql <= tl and qr >= tr) {
                return tree[id];
            }
            int mid = (tl + tr) >> 1;
            T1 a = query(lc(id), tl, mid, ql, qr),
               b = query(rc(id), mid + 1, tr, ql, qr);
            return a.merge(b);
        }

};
