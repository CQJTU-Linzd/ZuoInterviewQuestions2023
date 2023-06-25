// 165
// https://www.bilibili.com/video/BV14P411Q7L6?p=5&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// https://leetcode.cn/problems/find-k-th-smallest-pair-distance/description/
class FindKthSmallestPairDistance {
public:

	int smallestDistance(vector<int>& arr, int k) {
		int n = arr.size();
		sort(arr.begin(), arr.end());
		int l = 0;
		int r = arr[n - 1] - arr[0];
		int ans = 0;
		while (l <= r) {
			int m = (l + r) >> 1;
			int cnt = f(arr, m);
			if (cnt >= k) {
				ans = m;
				r = m - 1;
			} else {
				l = m + 1;
			}
		}
		return ans;
	}

	int f(vector<int>& arr, int dis) {
		int cnt = 0;
		for (int l = 0, r = 0; l < arr.size(); l++) {
			while (r < arr.size() && arr[r] - arr[l] <= dis) {
				r++;
			}
			cnt += r - l + 1;
		}
		return cnt;
	}

};
