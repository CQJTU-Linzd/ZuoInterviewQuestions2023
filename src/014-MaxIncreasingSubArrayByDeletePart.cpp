// P14
// https://www.bilibili.com/video/BV1DT411s7hp?p=14&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自字节
// 5.6笔试
// 给定一个数组arr，长度为n，最多可以删除一个连续子数组，
// 求剩下的数组，严格连续递增的子数组最大长度
// n <= 10^6
class MaxIncreasingSubArrayByDeletePart {
public:

	// 暴力

	int maxLength(vector<int>& arr) {
		int n = arr.size();
		int ans = getAns(arr);
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				auto cur = deletePart(arr, i, j);
				ans = max(ans, getAns(cur));
			}
		}
		return ans;
	}

	vector<int> deletePart(vector<int>& arr, int L, int R) {
		vector<int>res;
		for (int i = 0; i < L; i++) {
			res.push_back(arr[i]);
		}
		for (int i = R + 1; i < arr.size(); i++) {
			res.push_back(arr[i]);
		}
		return res;
	}

	// 求arr的最长递增子数组
	int getAns(vector<int>& arr) {
		if (arr.empty()) {
			return 0;
		}
		int ans = 1;
		int cur = 1;
		for (int i = 1; i < arr.size(); i++) {
			if (arr[i] > arr[i - 1]) {
				cur++;
			} else {
				cur = 1;
			}
			ans = max(ans, cur);
		}
		return ans;
	}


	// 正式

	int maxLength2(vector<int>& arr) {
		vector<int>help = arr;
		int n = help.size();
		// 离散化
		vector<int>tmp = help;
		sort(tmp.begin(), tmp.end());
		unordered_map<int, int>map;
		int index = 1;
		for (int num : tmp) {
			if (!map.count(num)) {
				map[num] = index++;
			}
		}

		for (int i = 0; i < n; i++) {
			help[i] = map[help[i]];
		}

		// 线段树里的下标，就是arr[i]
		// 每个下标对应的值，表示以arr[i]结尾，左边一个也不删，最长递增长度
		SegmentTree st(n);
		vector<int>dp(n); // 每个位置为结尾的情况下，可删可不删，最长递增长度
		dp[0] = 1;
		int ans = 1;
		int cur = 1; // 一个数字也不删，最长递增长度
		st.update(help[0], help[0], 1, 1, n + 1, 1);

		for (int i = 1; i < n; i++) {
			// 左边的数比右边小，必须要左边的数字
			int p1 = help[i - 1] < help[i] ? (dp[i - 1] + 1) : 1;
			// 在线段树里，找小于arr[i]的最大指标
			int p2 = help[i] > 1 ? (st.getMax(1, help[i] - 1, 1, n + 1, 1) + 1) : 1;

			dp[i] = max(p1, p2);
			ans = max(ans, dp[i]);

			if (help[i] > help[i - 1]) {
				cur++;
			} else {
				cur = 1;
			}
			if (st.getMax(help[i], help[i], 1, n + 1, 1) < cur) {
				st.update(help[i], help[i], cur, 1, n + 1, 1);
			}
		}

		return ans;
	}

	class SegmentTree {
		int N;
		vector<int>maxs;
		vector<bool>updates;
		vector<int>change;
	public:

		SegmentTree(int size) {
			N = size + 1;
			maxs.resize(N << 2);
			updates.resize(N << 2, false);
			change.resize(N << 2);
		}

		void pushUp(int rt) {
			maxs[rt] = max(maxs[rt << 1], maxs[rt << 1 | 1]);
		}

		void pushDown(int rt, int ln, int rn) {
			if (updates[rt]) {
				updates[rt << 1] = true;
				updates[rt << 1 | 1] = true;

				maxs[rt << 1] = change[rt];
				maxs[rt << 1 | 1] = change[rt];

				change[rt << 1] = change[rt];
				change[rt << 1 | 1] = change[rt];

				updates[rt] = false;
			}
		}

		void update(int L, int R, int C, int l, int r, int rt) {
			if (L <= l && r <= R) {
				maxs[rt] = C;
				updates[rt] = true;
				change[rt] = C;
				return;
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			if (L <= mid) {
				update(L, R, C, l, mid, rt << 1);
			}
			if (R > mid) {
				update(L, R, C, mid + 1, r, rt << 1 | 1);
			}
			pushUp(rt);
		}

		int getMax(int L, int R, int l, int r, int rt) {
			if (L <= l && r <= R) {
				return maxs[rt];
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			int ans = INT_MIN;
			if (L <= mid) {
				ans = max(ans, getMax(L, R, l, mid, rt << 1));
			}
			if (R > mid) {
				ans = max(ans, getMax(L, R, mid + 1, r, rt << 1 | 1));
			}
			return ans;
		}

	};


	// for test

	// 生成大小为size，数据范围在l~r的随机数组
	vector<int> randomArray(int size, int l, int r) {
		vector<int>nums;
		for (int i = 0; i < size; i++) {
			nums.push_back(rand() % (r - l + 1) + l);
		}
		return nums;
	}

	void test() {
		srand(time(0));
		for (int t = 0; t < 100; t++) {
			int size = rand() % (100 - 1 + 1) + 1;
			auto arr = randomArray(size, 1, 100);
			int ans1 = maxLength(arr);
			int ans2 = maxLength2(arr);
			if (ans1 != ans2) {
				cout << "fuck" << endl;
			}
		}
	}

};
