// 168
// https://www.bilibili.com/video/BV14P411Q7L6?p=9&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/cheapest-flights-within-k-stops/
class CheapestFlightsWithinKStops {
public:

	class Edge {
	public:
		int from;
		int to;
		int cost;
		Edge(int f, int t, int c) {
			from = f;
			to = t;
			cost = c;
		}
	};


	// 类似宽度优先遍历
	// n，城市数量，0...n-1
	// flights = { {0,7,100},  {15,3,300} .... }
	// src -> 源点
	// dst -> 目标点
	// k -> 最多能中转几次
	int minCost(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		vector<vector<Edge>>adjList;
		for (auto& flight : flights) {
			int from = flight[0];
			int to = flight[1];
			int cost = flight[2];
			adjList[from].push_back(Edge(from, to, cost));
		}
		vector<int>costs(n, INT_MAX);
		costs[src] = 0;
		unordered_map<int, int>curMap;
		curMap[src] = 0;
		for (int i = 0; i < k; i++) {
			unordered_map<int, int>nextMap;
			for (auto& it : curMap) {
				int cur = it.first;
				int preCost = it.second;
				for (Edge& nextEdge : adjList[cur]) {
					int to = nextEdge.to;
					int nextCost = nextEdge.cost;
					if (preCost + nextCost < costs[to]) {
						costs[to] = preCost + nextCost;
						nextMap[to] = nextMap.count(to) ? min(nextMap[to], costs[to]) : costs[to];
					}
				}
			}
			curMap = nextMap;
		}
		return costs[dst] == INT_MAX ? -1 : costs[dst];
	}


	// Bellman-Ford
	// 优势：可以处理负边；最多广播n-1次（如果超过n-1次，最短距离还有下降，说明有负边）
	int minCost2(int n, vector<vector<int>>& flights, int src, int dst, int k) {
		vector<int>costs(n, INT_MAX);
		costs[src] = 0;
		for (int i = 0; i <= k; i++) {
			vector<int>next = costs;
			for (auto& f : flights) {
				int from = f[0];
				int to = f[1];
				int cost = f[2];
				if (costs[from] != INT_MAX) {
					next[to] = min(next[to], costs[from] + cost);
				}
			}
			costs = next;
		}
		return costs[dst] == INT_MAX ? -1 : costs[dst];
	}

};
