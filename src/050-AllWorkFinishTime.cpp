// 50
// https://www.bilibili.com/video/BV1DT411s7hp?p=50&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class AllWorkFinishTime {
public:

    vector<int> finishTime(int n, vector<int>& time, vector<vector<int>>& matrix) {
        vector<vector<int>>graph(n);
        vector<int>in(n);
        for (auto& edge : matrix) {
            graph[edge[1]].push_back(edge[0]);
            in[edge[0]]++;
        }
        queue<int>zeroInQueue;
        for (int i = 0; i < in.size(); i++) {
            if (in[i] == 0) {
                zeroInQueue.push(i);
            }
        }
        vector<int>res(n);
        while (!zeroInQueue.empty()) {
            int cur = zeroInQueue.front();
            zeroInQueue.pop();
            res[cur] += time[cur];
            for (int next : graph[cur]) {
                res[next] = max(res[next], res[cur]);
                if (--in[next] == 0) {
                    zeroInQueue.push(next);
                }
            }
        }
        return res;
    }

};
