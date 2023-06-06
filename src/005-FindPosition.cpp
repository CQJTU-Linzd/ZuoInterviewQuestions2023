// P5 
// https://www.bilibili.com/video/BV1DT411s7hp?p=5&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自美团
// 8.20笔试
// 题目1
// 小美将要期中考试，有n道题，对于第i道题，
// 小美有pi的几率做对，获得ai的分值，还有(1-pi)的概率做错，得0分。
// 小美总分是每道题获得的分数。
// 小美不甘于此，决定突击复习，因为时间有限，她最多复习m道题，复习后的试题正确率为100%。
// 如果以最佳方式复习，能获得期望最大总分是多少？
// 输入n、m
// 接下来输入n个整数，代表pi%，为了简单期间，将概率扩大了100倍。
// 接下来输入n个整数，代表ai，某道题的分值
// 输出最大期望分值，精确到小数点后2位
// 数据 1m<=n<=50000
// 简单题, 课上提一下解法即可
// 题目2
// 小团在地图上放了3个定位装置，想依赖他们进行定位！
// 地图是一个n*n的棋盘，
// 有3个定位装置(x1,y1),(x2,y2),(x3,y3)，每个值均在[1,n]内。
// 小团在(a,b)位置放了一个信标，
// 每个定位装置会告诉小团它到信标的曼哈顿距离，也就是对于每个点，小团知道|xi-a|+|yi-b|
// 求信标位置，信标不唯一，输出字典序最小的。
// 输入n，然后是3个定位装置坐标，
// 最后是3个定位装置到信标的曼哈顿记录。
// 输出最小字典序的信标位置。
// 1 <= 所有数据值 <= 50000
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
