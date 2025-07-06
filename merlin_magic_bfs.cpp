// Implementation of Merlin Magic using BFS

#include <bits/stdc++.h>
using namespace std;

// Serialize a 3×3 grid into a string for hashing/visited.
string serializeGrid(const vector<vector<int>>& grid) {
    string s;
    s.reserve(9);
    for (auto& row : grid)
        for (int v : row)
            s.push_back(char('0' + v));
    return s;
}

// Apply a single group-operation (mapping) to every cell in 'src', writing into 'dst'.
void applyOp(const vector<vector<int>>& src,
             vector<vector<int>>& dst,
             const vector<int>& op)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            dst[i][j] = op[ src[i][j] ];
}

// BFS to find minimum operations to reach 'target' from 'start'.
int minOpsToTarget(vector<vector<int>> start,
                   const vector<vector<int>>& target,
                   const vector<vector<int>>& ops)
{
    string tgtKey = serializeGrid(target);
    queue<pair<vector<vector<int>>,int>> q;
    unordered_set<string> seen;

    q.push({start, 0});
    seen.insert(serializeGrid(start));

    while (!q.empty()) {
        auto [grid, dist] = q.front(); 
        q.pop();

        string key = serializeGrid(grid);
        if (key == tgtKey)
            return dist;

        // Try each operation
        for (auto& op : ops) {
            vector<vector<int>> next = grid;
            applyOp(grid, next, op);
            string nk = serializeGrid(next);
            if (!seen.count(nk)) {
                seen.insert(nk);
                q.push({next, dist + 1});
            }
        }
    }

    return -1;  // unreachable
}

int main() {
    // Example start and target
    vector<vector<int>> start = {
        {0,1,2},
        {1,2,0},
        {2,0,1}
    };
    vector<vector<int>> target(3, vector<int>(3, 0));

    // Suppose our group has 3 generators, defined by these mappings:
    //   g0: 0→0, 1→1, 2→2
    //   g1: 0→1, 1→2, 2→0
    //   g2: 0→2, 1→0, 2→1
  vector<vector<int>> ops = {
    {1, 2, 0},
    {0, 2, 1},
    {1, 1, 1}
};

    int ans = minOpsToTarget(start, target, ops);
    if (ans >= 0)
        cout << "Solved in " << ans << " operations.\n";
    else
        cout << "No solution found.\n";
    return 0;
}
