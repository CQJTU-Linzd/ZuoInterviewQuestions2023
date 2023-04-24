// 22
// https://www.bilibili.com/video/BV1DT411s7hp?p=22&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class LongestCycleInGraph {
public:

    int longestCycle(vector<int>& edges) {
        // edges[i] == j: i->j
        // edges[i] == -1: i往外没有通路
        int n = edges.size();
        vector<int>ids(n);
        int ans = -1;
        int cnt = 1;
        for (int from = 0; from < n; from++) {
            if (ids[from] == 0) { // 没访问过
                for (int cur = from, fromId = cnt; cur != -1; cur = edges[cur]) {
                    if (ids[cur] > 0) { // cur之前访问过
                        if (ids[cur] >= fromId) { // 新环
                            ans = max(ans, cnt - ids[cur]);
                        }
                        break;
                    }
                    ids[cur] = cnt++;
                }
            }
        }
        return ans;
    }
};
