// P7
// https://www.bilibili.com/video/BV1DT411s7hp?p=7&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自微软
// 给定两个数组A和B，比如
// A = { 0, 1, 1 }
// B = { 1, 2, 3 }
// A[0] = 0, B[0] = 1，表示0到1有双向道路
// A[1] = 1, B[1] = 2，表示1到2有双向道路
// A[2] = 1, B[2] = 3，表示1到3有双向道路
// 给定数字N，编号从0~N，所以一共N+1个节点
// 题目输入一定保证所有节点都联通，并且一定没有环
// 默认办公室是0节点，其他1~N节点上，每个节点上都有一个居民
// 每天所有居民都去往0节点上班
// 所有的居民都有一辆5座的车，也都乐意和别人一起坐车
// 车不管负重是多少，只要走过一条路，就耗费1的汽油
// 比如A、B、C的居民，开着自己的车来到D居民的位置，一共耗费3的汽油
// D居民和E居民之间，假设有一条路
// 那么D居民可以接上A、B、C，4个人可以用一辆车，去往E的话，就再耗费1的汽油
// 求所有居民去办公室的路上，最少耗费多少汽油
// 测试链接 : https://leetcode.cn/problems/minimum-fuel-cost-to-report-to-the-capital/
class TravelMinFuel {
    int cnt;
public:
    // n个居民点，n + 1个节点
    int minFuel(vector<int>& a, vector<int>& b, int n) {
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
    
    // 法二、进阶

	int minimumFuelCost(vector<vector<int>>& roads, int seats) {
		int n = roads.size();
		vector<vector<int>>adjList(n + 1);
		for (auto& edge : roads) {
			adjList[edge[0]].push_back(edge[1]);
			adjList[edge[1]].push_back(edge[0]);
		}
		vector<bool>vis(n + 1, false);
		return process(adjList, seats, vis, 0).cost;
	}

	Info process(vector<vector<int>>& adjList, int seats, vector<bool>& vis, int i) {
		vis[i] = true;
		int size = 1;
		int cost = 0;
		for (int next : adjList[i]) {
			if (!vis[next]) {
				Info nextInfo = process(adjList, seats, vis, next);
				size += nextInfo.size;
				cost += nextInfo.cost;
				cost += (nextInfo.size + seats - 1) / seats;
			}
		}
		return Info(size, cost);
	}
    
    
};
