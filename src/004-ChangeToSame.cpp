// P4
// https://www.bilibili.com/video/BV1DT411s7hp?p=4&vd_source=2286e10835cc4cd375b26d18d9e6fa7e

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
