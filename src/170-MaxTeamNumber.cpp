// 170
// https://www.bilibili.com/video/BV14P411Q7L6?p=13&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给定一个数组arr，一个正数num，一个正数k
// 可以把arr中的某些数字拿出来组成一组，要求该组中的最大值减去最小值<=num
// 且该组数字的个数一定要正好等于k
// 每个数字只能选择进某一组，不能进多个组
// 返回arr中最多有多少组
class MaxTeamNumber {
public:

	int maxTeam(vector<int>& arr, int num, int k) {
		int n = arr.size();
		if (n == 0 || k > n) {
			return 0;
		}
		sort(arr.begin(), arr.end());
		vector<int>dp(n); // 0~i范围上，最多有几组
		dp[k - 1] = arr[k - 1] - arr[0] <= num ? 1 : 0;
		for (int i = k; i < n; i++) {
			int p1 = dp[i - 1];
			int p2 = (arr[i] - arr[i - k + 1] <= num ? 1 : 0) + dp[i - k];
			dp[i] = max(p1, p2);
		}
		return dp[n - 1];
	}

};
