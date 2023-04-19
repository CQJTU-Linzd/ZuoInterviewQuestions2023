// P8
// https://www.bilibili.com/video/BV1DT411s7hp?p=8&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class TravelMinFuel {
    int cnt;
public:
    // n个居民点，n + 1个节点
    int minFuel1(vector<int>& a, vector<int>& b, int n) {
        // 先建图 邻接表
        vector<vector<int>>graph(n + 1);
        for (int i = 0; i < a.size(); i++) {
            graph[a[i]].push_back(b[i]);
            graph[b[i]].push_back(a[i]);
        }
        // 建图完毕
        // 办公室是0号点 所有员工往0号点汇聚

        // dfn序 
        // dfn[a] == 0 说明a号点没遍历过
        vector<int>dfn(n + 1);

        // a为头的树，一共有10个节点
        // 没遍历的时候，size[a] = 0
        // 遍历完a，size[a] = 10
        vector<int>size(n + 1);

        // cost[a]：所有居民汇聚到a，总油量是多少
        vector<int>cost(n + 1);

        cnt = 0;
        dfs(graph, 0, dfn, size, cost);
        return cost[0];
    }
    void dfs(vector<vector<int>>& graph, int cur, vector<int>& dfn, vector<int>& size, vector<int>& cost) {
        dfn[cur] = ++cnt;
        size[cur] = 1;
        for (int next : graph[cur]) {
            if (dfn[next] == 0) { // 只有dfn序是0，才往下走
                dfs(graph, next, dfn, size, cost);
                size[cur] += size[next];
                cost[cur] += cost[next]; // next所有孩子，汇聚到next花了多少
                cost[cur] += (size[next] + 5 - 1) / 5; // next及其所有孩子，一起汇聚到cur的花费
            }
        }
    }


    // 法二

    class Info {
    public:
        int size;
        int cost;
        Info(int s, int c) {
            size = s;
            cost = c;
        }
    };

    int minFuel2(vector<int>& a, vector<int>& b, int n) {
        // 先建图 邻接表
        vector<vector<int>>graph(n + 1);
        for (int i = 0; i < a.size(); i++) {
            graph[a[i]].push_back(b[i]);
            graph[b[i]].push_back(a[i]);
        }
        // 建图完毕
        // 办公室是0号点 所有员工往0号点汇聚

        // dfn序 
        // dfn[a] == 0 说明a号点没遍历过
        vector<int>dfn(n + 1);
        cnt = 0;
        return process(graph, dfn, 0).cost;
    }

    Info process(vector<vector<int>>& graph, vector<int>& dfn, int cur) {
        dfn[cur] = ++cnt;
        int size = 1;
        int cost = 0;
        for (int next : graph[cur]) {
            if (dfn[next] == 0) {
                Info nextInfo = process(graph, dfn, next);
                int nextSize = nextInfo.size;
                int nextCost = nextInfo.cost;
                size += nextSize;
                cost += nextCost;
                cost += (nextSize + 5 - 1) / 5;
            }
        }
        return Info(size, cost);
    }

};
