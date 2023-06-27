// 133
// https://www.bilibili.com/video/BV1DT411s7hp?p=133&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给定一个数组arr，代表每个人的能力值。再给定一个非负数k。
// 如果两个人能力差值正好为k，那么可以凑在一起比赛，一局比赛只有两个人
// 返回最多可以同时有多少场比赛
class MaxPairNumber {
public:

    int maxPair(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int ans = 0;
        int L = 0;
        int R = 0;
        bool* used = new bool[n];
        for (int i = 0; i < n; i++) {
            used[i] = false;
        }
        while (L < n && R < n) {
            if (used[L]) {
                L++;
            } else if (L == R) {
                R++;
            } else {
                int dis = arr[R] - arr[L];
                if (dis == k) {
                    ans++;
                    used[R] = true;
                    R++;
                    L++;
                } else if (dis < k) {
                    R++;
                } else {
                    L++;
                }
            }
        }
        delete[] used;
        return ans;
    }

};
