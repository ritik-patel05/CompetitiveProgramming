// 0-Indexing.
// Space - O(NlogN), Query Time: O(1).
template<class T> 
class RMQ {
    public:
        void init(const vector<T>& _v) {
            v = _v;
            jump = {vector<int>(v.size())};
            iota(jump[0].begin(),jump[0].end(), 0);
            
            for(int j = 1; (1 << j) <= v.size(); ++j) {
                jump.emplace_back( vector<int>( v.size() - (1<<j) + 1) );
                for(int i = 0; i < jump[j].size(); ++i) {
                    jump[j][i] = merge( jump[j - 1][i] , jump[j - 1][i + (1 << (j - 1))]);
                }
            }
        }

        T query(int l, int r) {
            return v[index(l, r)];
        }

    private:
        vector<int> v;
        vector<vector<int>> jump;
        int level(int x) {
            return 31 - __builtin_clz(x);
        }
        int merge(int a, int b) { // Index of minimum.
            return v[a] == v[b] ? min(a, b) : ( v[a] < v[b] ? a: b);
        }
        int index(int l, int r) { // get index of minimum element in [l, r].
            assert(l <= r); 
            int smallest_powerOf2 = level(r - l + 1);
            return merge(jump[smallest_powerOf2][l], jump[smallest_powerOf2][r - (1 << smallest_powerOf2) + 1]);
        }
};
