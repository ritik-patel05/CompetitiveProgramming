/**
 * Description: pi[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 */
vector<int> prefix_function(string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 and s[j] != s[i]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j])
            ++j; 
        pi[i] = j;
    }
    return pi;
}

// Find string s in string t in Time complexity: O(n + m) and Space Complexity: O(n + m);
void match(string &s, string &t) { 
    string temp = s + "#" + t;
    int n1 = s.size(),
        n2 = t.size(),
        n = temp.size();
    vector<int> pi = prefix_function(temp);
    for (int i = 0; i < n; ++i) {
        if (pi[i] == n1) {
            cout << "Found at: " << i - 2 * n1 << '\n'; 
        }
    }
}

// Count number of occurences of each prefix[0:i] in string in O(n).
vector<int> number_of_prefixes(string &s) {

    int n = s.size();
    vector<int> pi = prefix_function(s);
    vector<int> ans(n + 1, 0);

    for (int i = 0; i < n; ++i) ans[pi[i]]++;
    for (int i = n - 1; i > 0; --i) ans[pi[i - 1]] += ans[i];
    for (int i = 0; i <= n; ++i) ans[i]++;
    return ans;
}

// Count number of distinct substrings in O(n^2).
int64_t distinct_substrings(string &s) {
    int n = s.size();
    int64_t answer = 0;
    // Add a char at the end and reverse it, and compute the longest proper prefix which is
    // also a suffix including that character. 
    for (int i = 0; i < n; ++i) {
        string to_check = s.substr(0, i + 1);
        reverse( to_check.begin(), to_check.end() );
        vector<int> new_pi = prefix_function(to_check);
        int mx = *max_element( new_pi.begin(), new_pi.end() );
        answer += (i + 1) - mx;
    }
    return answer;
}

// Computes automation in O(N * 26) Time and Space.
// Finds The prefix function for string s, if we have new character appended at the end.
// Can be used without storing the new string.
vector<vector<int>> compute_automaton(string &s) {

    s += '#';
    int n = s.size();
    vector<vector<int>> automation( n, vector<int>(26) ) ;
    vector<int> pi = prefix_function(s);

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                automation[i][c] = automation[pi[i-1]][c];
            else
                automation[i][c] = i + ('a' + c == s[i]);
        }
    }

    s.pop_back();

    return automation;
}
