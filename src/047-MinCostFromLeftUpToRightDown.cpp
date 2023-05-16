// 47
// https://www.bilibili.com/video/BV1DT411s7hp?p=48&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinCostFromLeftUpToRightDown {
public:

    class Node {
    public:
        int cost;
        int row;
        int col;
        Node(int cost, int row, int col) {
            this->cost = cost;
            this->row = row;
            this->col = col;
        }
    };

    class Cmp {
    public:
        bool operator()(Node& a, Node& b) {
            return a.cost > b.cost;
        }
    };

    int minCost(vector<vector<int>>& map) {
        int n = map.size();
        int m = map[0].size();
        vector<vector<bool>>vis(n, vector<bool>(m));
        priority_queue<Node, vector<Node>, Cmp>pq;
        pq.push(Node(0, 0, 0));
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            int cost = cur.cost;
            int row = cur.row;
            int col = cur.col;
            if (vis[row][col]) {
                continue;
            }
            if (row == n - 1 && col == m - 1) {
                return cost;
            }
            vis[row][col] = true;
            add(n, m, row - 1, col, cost, map[row][col], vis, map, pq);
            add(n, m, row, col - 1, cost, map[row][col], vis, map, pq);
            add(n, m, row + 1, col, cost, map[row][col], vis, map, pq);
            add(n, m, row, col + 1, cost, map[row][col], vis, map, pq);
        }
        return -1;
    }

    void add(int n, int m, int row, int col, int cost, int preValue,
             vector<vector<bool>>& vis, 
             vector<vector<int>>& map, 
             priority_queue<Node, vector<Node>, Cmp>& pq) {
        if (in(n, m, row, col) && !vis[row][col]) {
            pq.push(Node(cost + (map[row][col] == preValue ? 1 : 2), row, col));
        }
    }

    bool in(int n, int m, int x, int y) {
        return x >= 0 && x < n&& y >= 0 && y < m;
    }

};
