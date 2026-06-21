/*
 * Trie (Prefix Tree) for lowercase English letters
 *
 * A tree where each edge corresponds to a character ('a'..'z').
 * Each node stores:
 *   - children[26]: pointers (indices) to child nodes
 *   - cnt_word:     number of words that end exactly at this node
 *   - cnt_prefix:   number of words that pass through this node
 *
 * Operations:
 *   insert(word)       — insert a word into the trie.
 *   countWord(word)    — how many times this exact word was inserted.
 *   countPrefix(prefix)— how many inserted words have this prefix.
 *
 * Time:  O(|s|) per operation, where |s| is the length of the string.
 * Space: O(total characters inserted * 26) in the worst case.
 *
 * Typical use cases:
 *   - Prefix counting / existence queries.
 *   - Auto-complete style problems.
 *   - XOR maximization (binary trie variant, not covered here).
 *
 * Caveats:
 *   - Alphabet is fixed to lowercase 'a'..'z'.  Adjust ALPHA_SIZE for others.
 *   - No delete operation provided (rarely needed in competitive programming).
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Trie {
    static constexpr int ALPHA_SIZE = 26;

    struct Node {
        int children[ALPHA_SIZE];
        int cnt_word;   // number of words ending here
        int cnt_prefix; // number of words passing through here

        Node() : cnt_word(0), cnt_prefix(0) {
            fill(children, children + ALPHA_SIZE, -1);
        }
    };

    vector<Node> nodes;

    Trie() {
        nodes.emplace_back(); // root node (index 0)
    }

    // Insert a word into the trie.
    void insert(const string& word) {
        int cur = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (nodes[cur].children[idx] == -1) {
                nodes[cur].children[idx] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].children[idx];
            nodes[cur].cnt_prefix++;
        }
        nodes[cur].cnt_word++;
    }

    // Return how many times this exact word was inserted.
    int countWord(const string& word) const {
        int cur = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (nodes[cur].children[idx] == -1) return 0;
            cur = nodes[cur].children[idx];
        }
        return nodes[cur].cnt_word;
    }

    // Return how many inserted words have this prefix.
    int countPrefix(const string& prefix) const {
        int cur = 0;
        for (char c : prefix) {
            int idx = c - 'a';
            if (nodes[cur].children[idx] == -1) return 0;
            cur = nodes[cur].children[idx];
        }
        return nodes[cur].cnt_prefix;
    }
};

int main() {
    // Example: insert N words, then answer Q queries.
    // Query format:
    //   1 word  — insert word
    //   2 word  — print countWord(word)
    //   3 prefix — print countPrefix(prefix)
    int N, Q;
    cin >> N >> Q;

    Trie trie;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        trie.insert(s);
    }

    while (Q--) {
        int type;
        string s;
        cin >> type >> s;
        if (type == 1) {
            trie.insert(s);
        } else if (type == 2) {
            cout << trie.countWord(s) << "\n";
        } else {
            cout << trie.countPrefix(s) << "\n";
        }
    }
    return 0;
}
