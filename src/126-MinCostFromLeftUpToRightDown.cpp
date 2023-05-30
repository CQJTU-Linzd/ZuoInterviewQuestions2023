// 126
// https://www.bilibili.com/video/BV1DT411s7hp?p=126&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinCostFromLeftUpToRightDown {
public:

    class Node {
    public:
        int cost;
        int row;
        int col;
        Node(int cos, int r, int c) {
            cost = cos;
            row = r;
            col = c;
        }
    };

    class Cmp {
    public:
        bool operator()(Node& a, Node& b) {
            return a.cost > b.cost;
        }
    };

    int dirs[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

    int minCost(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m));
        priority_queue<Node, vector<Node>, Cmp>pq;
        pq.push(Node(grid[0][0], 0, 0));
        int ans = 0;
        while (!pq.empty()) {
            int curR = pq.top().row;
            int curC = pq.top().col;
            int cost = pq.top().cost;
            pq.pop();
            if (vis[curR][curC]) {
                continue;
            }
            if (curR == n - 1 && curC == m - 1) {
                ans = cost;
                continue;
            }
            vis[curR][curC] = true;
            for (int i = 0; i < 4; i++) {
                int dr = curR + dirs[i][0];
                int dc = curC + dirs[i][1];
                if (in(n, m, dr, dc) && !vis[dr][dc]) {
                    pq.push(Node(cost + grid[dr][dc], dr, dc));
                }
            }
        }
        return ans;
    }

    bool in(int n, int m, int x, int y) {
        return x >= 0 && x < n&& y >= 0 && y < m;
    }

};
