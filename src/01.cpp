#include"headFile.h"

/*
https://www.bilibili.com/video/BV1DT411s7hp?p=4&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
*/
// P4
class ChangeToSame {
public:
    int minCost(vector<int>& A, vector<int>& B) {
        return process(A, B, 0, 0);
    }
    int process(vector<int>& A, vector<int>& B, int ai, int bi) {
        if (ai == A.size() && bi == B.size()) {
            return 0;
        }
        if (ai == A.size() && bi != B.size()) {
            return B[bi] + process(A, B, ai, bi + 1);
        }
        if (ai != A.size() && bi == B.size()) {
            return A[ai] + process(A, B, ai + 1, bi);
        }
        // ai和bi都没结束
        // 删掉A[ai]
        int p1 = A[ai] + process(A, B, ai + 1, bi);
        // 删掉B[bi]
        int p2 = B[bi] + process(A, B, ai, bi + 1);
        // 两个同时删掉
        // p3的代价一定是大于等于p4的，所以不需要去尝试
        // int p3 = A[ai] + B[bi] + process(A, B, ai + 1, bi + 1);

        // 变
        int p4 = abs(A[ai] - B[bi]) + process(A, B, ai + 1, bi + 1);
        return min({ p1, p2, p4 });
    }
    // dp
    int minCost2(vector<int>& A, vector<int>& B) {
        int n1 = A.size();
        int n2 = B.size();
        vector<vector<int>>dp(n1 + 1, vector<int>(n2 + 1));
        for (int bi = n2 - 1; bi >= 0; bi--) {
            dp[n1][bi] = B[bi] + dp[n1][bi + 1];
        }
        for (int ai = n1 - 1; ai >= 0; ai--) {
            dp[ai][n2] = A[ai] + dp[ai + 1][n2];
        }
        for (int ai = n1 - 1; ai >= 0; ai--) {
            for (int bi = n2 - 1; bi >= 0; bi--) {
                int p1 = A[ai] + dp[ai + 1][bi];
                int p2 = B[bi] + dp[ai][bi + 1];
                int p3 = abs(A[ai] - B[bi]) + dp[ai + 1][bi + 1];
                dp[ai][bi] = min({ p1, p2, p3 });
            }
        }
        return dp[0][0];
    }
};

// P5 
// https://www.bilibili.com/video/BV1DT411s7hp?p=5&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class FindPosition {
public:
    vector<int> find(int n, vector<int>& a, vector<int>& b, vector<int>& c,
                     int ad, int bd, int cd) {
        vector<int>x1; // 存圆心坐标的
        int r1 = INT_MAX;
        vector<int>x2;
        int r2 = 0;
        vector<int>x3;
        int r3 = 0;
        // 找到曼哈顿距离最小的点
        if (ad < r1) {
            x1 = a;
            r1 = ad;
            x2 = b;
            r2 = bd;
            x3 = c;
            r3 = cd;
        }
        if (bd < r1) {
            x1 = b;
            r1 = bd;
            x2 = a;
            r2 = ad;
            x3 = c;
            r3 = cd;
        }
        if (cd < r1) {
            x1 = c;
            r1 = cd;
            x2 = b;
            r2 = bd;
            x3 = a;
            r3 = ad;
        }
        // 此时x1和r1就是曼哈顿距离最小的点坐标和距离
        vector<int>cur = { x1[0] - r1, x1[1] };
        queue<vector<int>>queue;
        unordered_set<string>vis;
        vector<vector<int>>ans;
        queue.push(cur);
        vis.insert(cur[0] + "_" + cur[1]);
        while (!queue.empty()) {
            cur = queue.front();
            queue.pop();
            if (in(n, cur[0], cur[1]) 
                && distance(cur[0], cur[1], x2) == r2
                && distance(cur[0], cur[1], x3) == r3) {
                ans.push_back(cur);
            }
            if (ans.size() == 2) { // 最多只会有两个点满足要求
                break;
            }
            // 周围八个点入队
            add(cur[0] - 1, cur[1], x1, r1, queue, vis);
            add(cur[0] - 1, cur[1] - 1, x1, r1, queue, vis);
            add(cur[0], cur[1] - 1, x1, r1, queue, vis);
            add(cur[0] + 1, cur[1] - 1, x1, r1, queue, vis);
            add(cur[0] + 1, cur[1], x1, r1, queue, vis);
            add(cur[0] + 1, cur[1] + 1, x1, r1, queue, vis);
            add(cur[0], cur[1] + 1, x1, r1, queue, vis);
            add(cur[0] - 1, cur[1] + 1, x1, r1, queue, vis);
        }
        if (ans.size() == 1 || ans[0][0] < ans[1][0]
            || (ans[0][0] == ans[1][0] && ans[0][1] < ans[1][1])) {
            return ans[0];
        } else {
            return ans[1];
        }
    }
    bool in(int n, int x, int y) {
        return x >= 1 && x <= n && y >= 1 && y <= n;
    }
    // c是圆心
    // 只有(x,y)这个点到圆心的距离是r，才可以加入队列
    void add(int x, int y, vector<int>& c, int r, 
             queue<vector<int>>& que, unordered_set<string>& vis) {
        string key = x + "_" + y;
        if (distance(x, y, c) == r && !vis.count(key)) {
            que.push(vector<int>{x, y});
            vis.insert(key);
        }
    }
    int distance(int x, int y, vector<int>& c) {
        return abs(x - c[0]) + abs(y - c[1]);
    }
};