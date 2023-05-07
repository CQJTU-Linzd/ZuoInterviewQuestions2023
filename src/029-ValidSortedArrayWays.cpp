// 29
// https://www.bilibili.com/video/BV1DT411s7hp?p=29&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ValidSortedArrayWays {
public:

    int ways1(vector<int>& arr, int k) {
        int n = arr.size();
        // dp[i][j]: i个格子里填数，有j种数可以选，保证形成的排列不降序，有几种方法
        vector<vector<int>>dp(n + 1, vector<int>(k + 1));
        for (int i = 1; i <= n; i++) {
            dp[i][1] = 1;
        }
        for (int j = 1; j <= k; j++) {
            dp[1][j] = j;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= k; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        int ans = 1;
        // 找连续的一段0，查询dp表，乘到答案里
        for (int i = 0, j = 0; i < arr.size(); i++) {
            if (arr[i] == 0) {
                j = i + 1;
                while (j < arr.size() && arr[j] == 0) {
                    j++;
                }
                int leftValue = i > 0 ? arr[i - 1] : 1;
                int rightValue = j < arr.size() ? arr[j] : k;
                ans *= dp[j - i][rightValue - leftValue + 1];
                i = j;
            }
        }
        return ans;
    }
};
