// 20
// https://www.bilibili.com/video/BV1DT411s7hp?p=20&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class TreeDye {
public:

    vector<int>rule1 = { 1, 2, 3 };
    vector<int>rule2 = { 1, 3, 2 };

    vector<int> dye(int n, vector<vector<int>>& edges) {
        vector<vector<int>>graph(n);
        for (vector<int>& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int head = -1;
        for (int i = 0; i < n; i++) {
            if (graph[i].size() > 1) {
                head = i;
                break;
            }
        }
        vector<int>colors(n);
        if (head == -1) { // 只有两个节点
            fill(colors.begin(), colors.end(), 1);
        } else {
            colors[head] = 1;
            dfs(graph, graph[head][0], 1, rule1, colors); // 挑出head的一个相邻点按rule1染色
            for (int i = 1; i < graph[head].size(); i++) {
                dfs(graph, graph[head][i], 1, rule2, colors);
            }
        }
    }

    // head: 当前来到的节点
    // 和蔼的节点在level层
    void dfs(vector<vector<int>>& graph,
             int head,
             int level, vector<int>& rule, vector<int>& colors) {
        colors[head] = rule[level % 3];
        for (int next : graph[head]) {
            if (colors[next] == 0) {
                dfs(graph, next, level + 1, rule, colors);
            }
        }
    }

};
