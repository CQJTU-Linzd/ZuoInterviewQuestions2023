// 109
// https://www.bilibili.com/video/BV1DT411s7hp?p=109&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class XToYMinDistance {
public:

    int minDistance(int n, vector<vector<int>>& loads, int x, int y) {
        // 邻接矩阵
        int** map = new int* [n + 1];
        for (int i = 0; i <= n; i++) {
            map[i] = new int[n + 1];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                map[i][j] = INT_MAX;
            }
        }

        for (auto& load : loads) {
            map[load[0]][load[1]] = load[2];
            map[load[1]][load[0]] = load[2];
        }
        // true，表示从源出发点到当前城市，已经计算出最短距离了
        bool* computed = new bool[n + 1];
        for (int i = 0; i <= n; i++) {
            computed[i] = false;
        }
        int ans = INT_MAX;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pq;
        pq.push(make_pair(0, x));
        while (!pq.empty()) {
            int curDis = pq.top().first;
            int curCity = pq.top().second;
            pq.pop();
            if (computed[curCity]) {
                continue;
            }
            if (curCity == y) {
                ans = curDis;
                break;
            }
            computed[curCity] = true;
            for (int next = 1; next <= n; next++) {
                if (next != curCity && map[curCity][next] != INT_MAX && !computed[next]) {
                    pq.push(make_pair(curDis + map[curCity][next], next));
                }
            }
        }
        for (int i = 0; i <= n; i++) {
            delete[] map[i];
        }
        delete[] map;
        delete[] computed;
        return ans;
    }

};
