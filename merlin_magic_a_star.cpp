// Merlin Search using A* Search

#include <bits/stdc++.h>
using namespace std;

// Heuristic: Hamming distance to target
int heuristic(const string& s, const string& t) {
    int h = 0;
    for (int i = 0; i < 9; ++i)
        if (s[i] != t[i]) ++h;
    return h;
}

// Apply a single mapping op of size 3 to every character in 's'
string applyOp(const string& s, const vector<int>& op) {
    string out = s;
    for (int i = 0; i < 9; ++i) {
        int v = s[i] - '0';
        out[i] = char('0' + op[v]);
    }
    return out;
}

// A* search: returns true if we reach 'target', and fills cameFrom
bool aStarSolve(const string& initial,
                const string& target,
                const vector<vector<int>>& ops,
                unordered_map<string,string>& cameFrom)
{
    struct Node {
        string state;
        int g, f;
        bool operator<(Node const& o) const {
            return f > o.f;         // min-heap on f
        }
    };

    priority_queue<Node> pq;
    unordered_map<string,int> gScore;
    unordered_set<string> closed;

    gScore[initial] = 0;
    pq.push({initial, 0, heuristic(initial,target)});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (cur.state == target) return true;

        if (closed.count(cur.state)) continue;
        closed.insert(cur.state);

        for (auto const& op : ops) {
            string nxt = applyOp(cur.state, op);
            int tentativeG = cur.g + 1;

            if (!gScore.count(nxt) || tentativeG < gScore[nxt]) {
                gScore[nxt] = tentativeG;
                cameFrom[nxt] = cur.state;
                int f = tentativeG + heuristic(nxt, target);
                pq.push({nxt, tentativeG, f});
            }
        }
    }
    return false;
}

// Reconstruct path from cameFrom
vector<string> reconstruct(const string& start,
                           const string& goal,
                           unordered_map<string,string>& cameFrom)
{
    vector<string> path;
    string cur = goal;
    while (cur != start) {
        path.push_back(cur);
        cur = cameFrom[cur];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main(){
    string initial = "012102201";
    string target  = "000000000";

    // Three operations: +0, +1, +2 mod 3
    // (Still unsolvable—but structure is clear!)
  vector<vector<int>> ops = {
    {1, 2, 0},
    {0, 2, 1},
    {1, 1, 1}
};

    unordered_map<string,string> cameFrom;
    bool found = aStarSolve(initial, target, ops, cameFrom);

    if (!found) {
        cout << "No solution found.\n";
        return 0;
    }

    auto path = reconstruct(initial, target, cameFrom);
    cout << "Solved in " << (path.size()-1) << " steps:\n";
    for (auto& s : path) {
        // print as 3×3 grid
        for (int i = 0; i < 9; ++i) {
            cout << s[i];
            if (i%3==2) cout << "\n";
        }
        cout << "---\n";
    }
    return 0;
}
