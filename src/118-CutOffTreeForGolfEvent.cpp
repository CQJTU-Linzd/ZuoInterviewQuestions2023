// 118
// https://www.bilibili.com/video/BV1DT411s7hp?p=118&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/cut-off-trees-for-golf-event/
class CutOffTreeForGolfEvent {
public:

    int cutOffTree(vector<vector<int>>& forest) {
        int n = forest.size();
        int m = forest[0].size();
        // cells[i]: [行，列，树的高度]
        vector<vector<int>>cells;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int val = forest[i][j];
                if (val > 1) {
                    cells.push_back(vector<int>{ i, j, val });
                }
            }
        }
        sort(cells.begin(), cells.end(),
             [](vector<int>& a, vector<int>& b)->int {
                 return a[2] < b[2];
             });

        int ans = 0;
        int curR = 0;
        int curC = 0;
        for (auto& cell : cells) {
            int step = bestWalk(forest, curR, curC, cell[0], cell[1]);
            if (step == -1) {
                return -1;
            }
            ans += step;
            curR = cell[0];
            curC = cell[1];
            forest[curR][curC] = 1;
        }
        return ans;
    }

    int dirs[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

    int bestWalk(vector<vector<int>>& forest, int sx, int sy, int tx, int ty) {
        int n = forest.size();
        int m = forest[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        deque<vector<int>>deque;
        //                          步数 行  列
        deque.push_front(vector<int>{0, sx, sy});
        while (!deque.empty()) {
            auto cur = deque.front();
            deque.pop_front();
            int step = cur[0], x = cur[1], y = cur[2];
            if (x == tx && y == ty) {
                return step;
            }
            vis[x][y] = true;
            for (int i = 0; i < 4; i++) {
                int dx = x + dirs[i][0];
                int dy = y + dirs[i][1];
                if (in(n, m, dx, dy) && !vis[dx][dy] && forest[dx][dy] > 0) {
                    vector<int>move = { step + 1, dx, dy };
                    if ((i == 0 && x > tx) || (i == 1 && y > ty) || (i == 2 && x < tx) || (i == 3 && y < ty)) {
                        deque.push_front(move);
                    } else {
                        deque.push_back(move);
                    }
                }

            }
        }
        return -1;
    }

    bool in(int n, int m, int x, int y) {
        return x >= 0 && x < n&& y >= 0 && y < m;
    }

};
