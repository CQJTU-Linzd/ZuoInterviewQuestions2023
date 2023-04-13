// P9-P12
// https://www.bilibili.com/video/BV1DT411s7hp?p=9&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class DPFromVT {
public:
    // 题目一
    int process1(vector<vector<int>>& arr, int i, int restFunny, int restOffense) {
        /* if (restFunny <= 0 && restOffense <= 0) {
            return 0;
        }*/
        if (i == arr.size()) {
            return (restFunny <= 0 && restOffense <= 0) ? 0 : INT_MAX;
        }
        int p1 = process1(arr, i + 1, restFunny, restOffense);
        int p2 = INT_MAX;
        int next = process1(arr, i + 1, restFunny - arr[i][0], restOffense - arr[i][1]);
        if (next != INT_MAX) {
            p2 = 1 + next;
        }
        return min(p1, p2);
    }
    int dp1(vector<vector<int>>& arr, int funny, int offense) {
        int n = arr.size();
        vector<vector<int>>tmp(funny + 1, vector<int>(offense + 1));
        vector<vector<vector<int>>>dp(n + 1, tmp);
        for (int f = 0; f <= funny; f++) {
            for (int o = 0; o <= offense; o++) {
                if (f != 0 || o != 0) {
                    dp[n][f][o] = INT_MAX;
                }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int restFunny = 0; restFunny <= funny; restFunny++) {
                for (int restOffense = 0; restOffense <= offense; restOffense++) {
                    int p1 = dp[i + 1][restFunny][restOffense];
                    int p2 = INT_MAX;
                    if (restFunny - arr[i][0] >= 0 && restOffense - arr[i][1] >= 0) {
                        int next = dp[i + 1][restFunny - arr[i][0]][restOffense - arr[i][1]];
                        if (next != INT_MAX) {
                            p2 = 1 + next;
                        }
                    }
                    dp[i][restFunny][restOffense] = min(p1, p2);
                }
            }
        }
        return dp[0][funny][offense];
    }

    // 题目二
    int process2(vector<vector<int>>& arr, int i, int restLen) {
        if (restLen <= 0 || i == arr.size()) {
            return 0;
        }
        // 绳子还有剩余，且还有方案
        int p1 = process2(arr, i + 1, restLen);
        int p2 = 0;
        if (restLen >= arr[i][0]) { // 剩余长度够长才能选
            int p2 = arr[i][1] + process2(arr, i, restLen - arr[i][0]);
        }
        return max(p1, p2);
    }
    int dp2(vector<vector<int>>& arr, int len) {
        int n = arr.size();
        vector<vector<int>>dp(n + 1, vector<int>(len + 1));
        for (int i = n - 1; i >= 0; i--) {
            for (int restLen = 0; restLen <= len; restLen++) {
                int p1 = dp[i + 1][restLen];
                int p2 = 0;
                if (restLen >= arr[i][0]) {
                    int p2 = arr[i][1] + dp[i][restLen - arr[i][0]];
                }
                dp[i][restLen] = max(p1, p2);
            }
        }
        return dp[0][len];
    }
};
