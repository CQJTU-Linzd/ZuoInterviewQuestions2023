// 40
// https://www.bilibili.com/video/BV1DT411s7hp?p=40&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class OneEdgeMagicMinPathSum {
public:

    int minSum(int n, vector<vector<int>>& roads) {
        vector<vector<vector<int>>>graph(n + 1);
        for (auto& road : roads) {
            //     from                       0是实边  to      weight
            graph[road[0]].push_back(vector<int>{0, road[1], road[2]});
            graph[road[1]].push_back(vector<int>{1, road[0], road[2]});
        }
        priority_queue<vector<int>, vector<vector<int>>, Cmp>pq;
        vector<vector<int>>vis(n + 1, vector<int>(2));
        // 0,1,0：之前没有走过魔法路径，当前到达1节点，代价是0
        pq.push(vector<int>{0, 1, 0});
        int ans = INT_MAX;
        while (!pq.empty()) {
            vector<int>cur = pq.top();
            pq.pop();
            if (vis[cur[1]][cur[0]]) {
                continue;
            }
            vis[cur[1]][cur[0]] = true;
            if (cur[1] == n) {
                ans = min(ans, cur[2]);
            }
            for (auto& edge : graph[cur[1]]) {
                // cur[0] == 0: 当前点没走过魔法路径
                // edge[0] == 0: 当前这条边不是魔法路径
                if (cur[0] == 0 && edge[0] == 0) {
                    if (!vis[edge[1]][0]) {
                        pq.push(vector<int>{0, edge[1], cur[2] + edge[2]});
                    }
                } else if (cur[0] + edge[0] == 1) {
                    // cur[0] == 0 && edge[0] == 1: 当前点没走过魔法路径，当前边是魔法路径
                    // cur[0] == 1 && edge[0] == 0: 当前点走过魔法路径，当前边不是魔法路径
                    if (!vis[edge[1]][1]) {
                        pq.push(vector<int>{1, edge[1], cur[2] + edge[2]});
                    }
                }
            }
        }
        return ans;
    }

    class Cmp {
    public:
        bool operator()(vector<int>& a, vector<int>& b) {
            return a[2] > b[2];
        }
    };

};
