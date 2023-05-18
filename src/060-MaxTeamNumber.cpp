// 60
// https://www.bilibili.com/video/BV1DT411s7hp/?p=60&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxTeamNumber {
public:

    int maxTeams(vector<int>& arr, int num, int k) {
        int n = arr.size();
        if (k > n) {
            return 0;
        }
        sort(arr.begin(), arr.end());
        vector<int>dp(n);
        dp[k - 1] = arr[k - 1] - arr[0] <= num ? 1 : 0;
        for (int i = k; i < n; i++) {
            int p1 = dp[i - 1];
            int p2 = (arr[i] - arr[i - k + 1] <= num ? 1 : 0) + dp[i - k];
            dp[i] = max(p1, p2);
        }
        return dp[n - 1];
    }

};
