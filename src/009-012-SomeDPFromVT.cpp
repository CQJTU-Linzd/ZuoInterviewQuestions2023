// P9-P12
// https://www.bilibili.com/video/BV1DT411s7hp?p=9&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SomeDPFromVT {
public:

	// 题目一
	// 方案1 : {7, 10}
	// xxxx : {a , b}
	// 1 2 3 4
	// FunnyGoal = 100
	// OffenseGoal = 130
	// 找到一个最少方案数，让FunnyGoal、OffenseGoal，都大于等于
	// 定义如下尝试过程
	// 贴纸数组stickers
	// stickers[i][0] : i号贴纸的Funny值
	// stickers[i][1] : i号贴纸的Offense值
	// index....所有的贴纸，随便选择。index之前的贴纸不能选择，
	// 在让restFunny和restOffense都小于等于0的要求下，返回最少的贴纸数量
	int minStickers(vector<vector<int>>& stickers, int funnyGoal, int offsenseGoal) {
		int ans = process1(stickers, 0, funnyGoal, offsenseGoal);
		return ans == INT_MAX ? -1 : ans;
	}

	int process1(vector<vector<int>>& arr, int i, int restFunny, int restOffense) {
		if (i == arr.size()) {
			return (restFunny <= 0 && restOffense <= 0) ? 0 : INT_MAX;
		}
		int p1 = process1(arr, i + 1, restFunny, restOffense);
		int p2 = INT_MAX;
		int p2next = process1(arr, i + 1, restFunny - arr[i][0], restOffense - arr[i][1]);
		if (p2next != INT_MAX) {
			p2 = 1 + p2next;
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
	// 绳子总长度为M
	// 100 -> M
	// (6, 100) (7,23) (10,34) -> arr
	// 每一个长度的绳子对应一个价格，比如(6, 10)表示剪成长度为6的绳子，对应价格10
	// 可以重复切出某个长度的绳子
	// 定义递归如下：
	// 所有可以切出来的长度 对应 价值都在数组ropes里
	// ropes[i] = {6, 10} 代表i方案为：切出长度为6的绳子，可以卖10元
	// index....所有的方案，随便选择。index之前的方案，不能选择
	// 返回最大的价值
	// 自己去改动态规划
	// arr[i][0] -> i号方案能切多少长度
	// arr[i][1] -> 切出来这个长度，就能获得的价值
	// arr[index....]自由选择，绳子还剩restLen长度
	// 返回，最大价值
	int maxValue(vector<vector<int>>& ropes, int len) {
		return process2(ropes, 0, len);
	}
	int process2(vector<vector<int>>& arr, int i, int restLen) {
		if (i == arr.size() || restLen <= 0) {
			return 0;
		}
		int p1 = process2(arr, i + 1, restLen);
		int p2 = 0;
		if (arr[i][0] <= restLen) {
			int next = process2(arr, i, restLen - arr[i][0]);
			p2 = arr[i][1] + next;
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

	// 题目三
	// 每一个序列都是[a,b]的形式，a < b
	// 序列连接的方式为，前一个序列的b，要等于后一个序列的a
	// 比如 : [3, 7]、[7, 13]、[13, 26]这三个序列就可以依次连接
	// 给定若干个序列，求最大连接的数量
	// 定义尝试过程如下
	// arr[i] = {4, 9}表示，第i个序列4开始，9结束
	// pre : 代表选择的上一个序列，的，index是多少
	// 比如选择的上一个序列如果是(4,9)，是第5个序列，那么pre==5
	// 特别注意：如果从来没有选过序列，那么pre == -1
	// 这个函数含义 :
	// index....所有的序列，随便选择。index之前的序列，不能选择
	// 上一个选择的序列，是pre号，如果pre==-1,说明之前没有选择过序列
	// 返回题目要求的那种连接方式下，最大的序列数量
	// [5,13] [1,19] [2, 3] [79, 81] ...
	// [1,19] [2, 3] [5, 13] [79, 81]
	// arr[i][0] : 开头
	// arr[i][1] : 结尾
	// arr已经根据开头排过序了！
	// preEnd index
	// [1, 3] [2, 4] [4, 7]
	// 0 1 2
	// maxLen(0, -1)
	// 0（选） -> maxLen(1, 0)
	// 在arr[index...]选择序列，之前选的，离index最近的序列，位置在preIndex
	// 请返回，index...能链接起来的，序列数量的最大值
	class Cmp {
	public:
		bool operator()(vector<int>& a, vector<int>& b) {
			return a[0] < b[0];
		}
	};
	int maxLen(vector<vector<int>>& arr) {
		sort(arr.begin(), arr.end(), Cmp()); // 根据开头排序
		return process3(arr, 0, -1);
	}
	int process3(vector<vector<int>>& arr, int i, int preIndex) {
		if (i == arr.size()) {
			return 0;
		}
		int p1 = process3(arr, i + 1, preIndex);
		int p2 = 0;
		if (preIndex == -1 || arr[preIndex][1] == arr[i][0]) {
			p2 = 1 + process3(arr, i + 1, i);
		}
		return max(p1, p2);
	}
	int dp3(vector<vector<int>>& arr) {
		sort(arr.begin(), arr.end(), Cmp()); // 根据开头排序
		int n = arr.size();

		int** dp = new int* [n + 1];
		for (int i = 0; i < n + 1; i++) {
			dp[i] = new int[n + 1];
		}

		for (int i = 0; i < n + 1; i++) {
			for (int j = 0; j < n + 1; j++) {
				dp[i][j] = 0;
			}
		}

		// dp[i][0]: preIndex == -1
		// dp[i][1]: preIndex == 0
		// dp[i][n]: preIndex == n - 1
		for (int i = n - 1; i >= 0; i--) {
			for (int preIndex = -1; preIndex <= n - 1; preIndex++) {
				int p1 = dp[i + 1][preIndex + 1];
				int p2 = 0;
				if (preIndex == -1 || arr[preIndex][1] == arr[i][0]) {
					p2 = 1 + dp[i + 1][i + 1];
				}
				dp[i][preIndex + 1] = max(p1, p2);
			}
		}

		int ans = dp[0][0];
		for (int i = 0; i < n + 1; i++) {
			delete[] dp[i];
		}
		delete[] dp;
		return ans;
	}


	// for test

	vector<vector<int>> randomArray(int size, int l, int r) {
		vector<vector<int>>nums(size, vector<int>(2));
		for (int i = 0; i < size; i++) {
			int a = rand() % (r - l + 1) + l;
			int b = rand() % (r - l + 1) + l;
			if (a == b) {
				b = a + 1;
			}
			int L = min(a, b);
			int R = max(a, b);
			nums[i][0] = L;
			nums[i][1] = R;
		}
		return nums;
	}

	void test() {
		srand(time(0));
		for (int t = 0; t < 5000; t++) {
			int size = rand() % (100 - 1 + 1) + 1;
			auto arr = randomArray(size, 1, 100);
			int ans1 = maxLen(arr);
			int ans2 = dp3(arr);
			if (ans1 != ans2) {
				cout << "fuck" << endl;
			}
		}
	}

};
