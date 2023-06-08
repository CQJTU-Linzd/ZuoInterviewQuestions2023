// 19
// https://www.bilibili.com/video/BV1DT411s7hp?p=19&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自猿辅导
// 2022.8.7笔试第三道
// 给定一个数组arr，和一个正数k
// 如果arr[i] == 0，表示i这里既可以是左括号也可以是右括号，
// 而且可以涂上1~k每一种颜色
// 如果arr[i] != 0，表示i这里已经确定是左括号，颜色就是arr[i]的值
// 那么arr整体就可以变成某个括号字符串，并且每个括号字符都带有颜色
// 返回在括号字符串合法的前提下，有多少种不同的染色方案
// 不管是排列、还是颜色，括号字符串任何一点不一样，就算不同的染色方案
// 最后的结果%10001，为了方便，我们不处理mod，就管核心思路
// 2 <= arr长度 <= 5000
// 1 <= k <= 1000
// 0 <= arr[i] <= k
class ParenthesesDye {
public:

	int ways(vector<int>& arr, int k) {
		int n = arr.size();
		int a = 0; // arr中已经确定的括号数量
		for (int num : arr) {
			if (num != 0) {
				a++;
			}
		}
		int s = conbines(arr); // 忽略颜色，所有合法括号结合的数量
		return (int)s * pow(k, (n - 2 * a) / 2);
	}

	// 求合法的括号结合数量
	int conbines(vector<int>& arr) {
		int n = arr.size();
		//vector<vector<int>>dp(n, vector<int>(n, -1));
		int** dp = new int* [n];
		for (int i = 0; i < n; i++) {
			dp[i] = new int[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				dp[i][j] = -1;
			}
		}
		int ans = process(arr, 0, 0, dp);
		for (int i = 0; i < n; i++) {
			delete[] dp[i];
		}
		delete[] dp;
		return ans;
	}

	// more: arr[0...i-1]已经做完决定的部分，左括号比右括号多more个
	int process(vector<int>& arr, int i, int more, int** dp) {
		if (dp[i][more] != -1) {
			return dp[i][more];
		}
		if (i == arr.size()) {
			return more == 0 ? 1 : 0;
		}
		if (more < 0 || arr.size() - i < more) {
			return 0;
		}
		if (arr[i] != 0) {
			dp[i][more] = process(arr, i + 1, more + 1, dp);
			return dp[i][more];
		} else {
			int p1 = process(arr, i + 1, more + 1, dp);
			int p2 = process(arr, i + 1, more - 1, dp);
			dp[i][more] = p1 + p2;
			return p1 + p2;
		}
	}

};
