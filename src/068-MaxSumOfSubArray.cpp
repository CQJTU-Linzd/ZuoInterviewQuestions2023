// 68
// https://www.bilibili.com/video/BV1DT411s7hp?p=68&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxSumOfSubArray {
public:

    int maxSum(vector<int>& arr) {
        vector<int>dp(arr.size());
        dp[0] = arr[0];
        int ans = INT_MIN;
        for (int i = 1; i < arr.size(); i++) {
            dp[i] = max(arr[i], dp[i - 1] + arr[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }

};
