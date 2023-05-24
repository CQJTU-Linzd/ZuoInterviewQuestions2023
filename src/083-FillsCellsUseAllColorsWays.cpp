// 83
// https://www.bilibili.com/video/BV1DT411s7hp?p=83&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class FillsCellsUseAllColorsWays {
public:

    int ways(int n, int m) {
        int** dp = new int* [n + 1];
        for (int i = 0; i <= n; i++) {
            dp[i] = new int(m + 1);
        }

        for (int i = 1; i <= n; i++) {
            dp[i][1] = m;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                dp[i][j] = dp[i - 1][j] * j + dp[i - 1][j - 1] * (m - j + 1);
            }
        }
        int ans = dp[n][m];

        for (int i = 0; i <= n; i++) {
            delete[] dp[i];
        }
        delete[] dp;

        return ans;
    }

};
