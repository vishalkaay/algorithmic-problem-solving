

#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int,int>;
const vector<int> dR = {1,-1,0,0};   // row  offsets
const vector<int> dC = {0,0,1,-1};   // col  offsets
/*------------------------------------------------------------
  1.  Is there any path?  – Breadth-First Search
------------------------------------------------------------*/
bool isPathBFS(const vector<string>& maze, Coord s, Coord t) {
    int R = maze.size(), C = maze[0].size();
    vector<vector<bool>> vis(R, vector<bool>(C,false));
    queue<Coord> q;

    q.push(s);
    vis[s.first][s.second] = true;

    while (!q.empty()) {                               /* level-order scan [3] */
        auto [r,c] = q.front(); q.pop();
        if (r==t.first && c==t.second) return true;    // reached destination
        for (int k=0;k<4;++k){
            int nr = r + dR[k], nc = c + dC[k];
            if (nr>=0 && nr<R && nc>=0 && nc<C &&
                !vis[nr][nc] && maze[nr][nc]=='1'){
                vis[nr][nc]=true;
                q.emplace(nr,nc);
            }
        }
    }
    return false;
}
/*------------------------------------------------------------
  2.  Count all simple paths – Depth-First Search + backtracking
------------------------------------------------------------*/
void dfs(const vector<string>& maze, Coord cur, Coord t,
         vector<vector<bool>>& vis, long long& cnt){
    int R = maze.size(), C = maze[0].size();
    auto [r,c] = cur;
    if (cur==t){ cnt++; return; }                      /* goal reached [4] */

    vis[r][c]=true;
    for (int k=0;k<4;++k){
        int nr=r+dR[k], nc=c+dC[k];
        if (nr>=0 && nr<R && nc>=0 && nc<C &&
            !vis[nr][nc] && maze[nr][nc]=='1'){
            dfs(maze, {nr,nc}, t, vis, cnt);          /* explore branch [4] */
        }
    }
    vis[r][c]=false;                                  /* backtrack [4] */
}

long long countAllPaths(const vector<string>& maze, Coord s, Coord t){
    int R = maze.size(), C = maze[0].size();
    vector<vector<bool>> vis(R, vector<bool>(C,false));
    long long cnt = 0;
    dfs(maze,s,t,vis,cnt);
    return cnt;
}
/*------------------------------------------------------------
  Example driver
------------------------------------------------------------*/
int main(){
    vector<string> grid = { "1110",
                            "0011",
                            "1111",
                            "1001" };
    Coord start={0,0}, target={2,3};

    cout<<"Exists path? "<<(isPathBFS(grid,start,target)? "yes":"no")<<"\n";
    cout<<"#paths      : "<<countAllPaths(grid,start,target)<<"\n";
}
