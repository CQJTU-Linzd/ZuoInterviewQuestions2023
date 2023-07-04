// 173
// https://www.bilibili.com/video/BV14P411Q7L6?p=17&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/partition-array-for-maximum-sum/
class PartitionArrayForMaxSum {
public:

	int partitionMaxSum(vector<int>& arr, int k) {
		if (arr.empty()) {
			return 0;
		}
		int n = arr.size();
		vector<int>dp(n);
		dp[0] = arr[0];
		for (int i = 1; i < n; i++) {
			int curMax = arr[i];
			for (int j = i; j >= 0 && (i - j + 1) <= k; j--) {
				curMax = max(curMax, arr[j]);
				dp[i] = max(dp[i], curMax * (i - j + 1) + (j == 0 ? 0 : dp[j - 1]));
			}
		}
		return dp[n - 1];
	}

};
