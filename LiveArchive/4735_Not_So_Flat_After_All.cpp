/*
	Author: Ritik Patel
	
	Idea: 
		      - Distinct primes from x and y will be minimum size of space.
        - Difference between powers of x and y will be distance required.
        - Use sieve to store minimum prime factor to prime factorize and store in map
*/


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& STL DEBUGGER &&&&&&&&&&&&&&&&&&&&&&&&&&&

// #define _GLIBCXX_DEBUG       // Iterator safety; out-of-bounds access for Containers, etc.
// #pragma GCC optimize "trapv" // abort() on (signed) integer overflow.

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& LIBRARIES &&&&&&&&&&&&&&&&&&&&&&&&&&&

#include <bits/stdc++.h>
using namespace std;

/*#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
template<typename T, typename V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<T, V, less<T>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>; 
*/
//find_by_order()->returns an iterator to the k-th largest element(0-based indexing)
//order_of_key()->Number of items that are strictly smaller than our item

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEFINES &&&&&&&&&&&&&&&&&&&&&&&&&&&

#define int long long int
#define all(i) i.begin(), i.end()
#define sz(a) (int)a.size()
 
// const ld PI  = 3.141592;
const int dx4[4] = {0, 1, 0, -1};
const int dy4[4] = {-1, 0, 1, 0};
const int dx8[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dy8[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& DEBUG &&&&&&&&&&&&&&&&&&&&&&&&&&&
 
#define XOX
vector<string> vec_splitter(string s) {
    for(char& c: s) c = c == ','?  ' ': c;
    stringstream ss; ss << s;
    vector<string> res;
    for(string z; ss >> z; res.push_back(z));
    return res;
}
 
void debug_out(vector<string> __attribute__ ((unused)) args, __attribute__ ((unused)) int idx) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, Head H, Tail... T) {
    if(idx > 0) cerr << ", ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, T...);
}
 
#ifdef XOX
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __VA_ARGS__)
#else
#define debug(...) 42
#endif
 
 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& CODE &&&&&&&&&&&&&&&&&&&&&&&&&&&

int x, y;
int T = 1;

const int N = 1e6 + 5;
int prime[N];

void sieve(){
    for(int i = 1; i < N; ++i)
        prime[i] = i;
    for(int pr = 2; pr < N; ++pr){
        if(prime[pr] == pr){
            for(int j = pr * 2; j < N; j += pr){
                prime[j] = min(prime[j], pr);
            }
        }
    }
}

void solve(){
    map<int, int> mpa, mpb;
    while(x > 1){
        mpa[prime[x]]++;
        x /= prime[x];
    }
    while(y > 1){
        mpb[prime[y]]++;
        y /= prime[y];
    }
    int total = sz(mpa);
    for(auto &x: mpb){
        if(!mpa.count(x.first)){
            ++total;
        }
    }
    cout << T << ". ";
    cout << total << ":";
    int dist = 0;
    for(auto &x: mpa){
        if(mpb.count(x.first)){
            dist += abs(x.second - mpb[x.first]);
        } else {
            dist += x.second;
        }
    }
    for(auto &x: mpb){
        if(mpa.count(x.first)){
            continue;
        }
        dist += x.second;
    }
    cout << dist << '\n';
}


int32_t main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr); 
    // int T = 1; 
    // cin >> T;
    sieve();
    while(true){
        cin >> x >> y;
        if(x == 0 and y == 0){
            return 0;
        }
        solve();
        ++T;
    }
    return 0;
}

/*
Sample inp
*/
