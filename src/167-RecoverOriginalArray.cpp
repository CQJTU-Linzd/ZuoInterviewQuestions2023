// 167
// https://www.bilibili.com/video/BV14P411Q7L6?p=7&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// https://leetcode.cn/problems/recover-the-original-array/
class RecoverOriginalArray {
public:

	vector<int> recoverArray(vector<int>& nums) {
		int n = nums.size();
		int m = n >> 1;
		sort(nums.begin(), nums.end());
		vector<bool>used(n);
		// nums[0]一定是小数组的第一个元素
		for (int first = 1; first <= m; first++) { // 去枚举大数组的第一个元素
			int d = nums[first] - nums[0];
			if (d > 0 && (d & 1) == 0) {
				int i = 0;
				vector<int>ans(m); // 试图生成原始数组
				fill(used.begin(), used.end(), false);
				int k = d >> 1;
				int l = 0;
				int r = first;
				while (r < n) {
					while (used[l]) {
						l++;
					}
					if (l == r) {
						r++;
					}
					if (nums[r] - nums[l] > d) {
						break;
					} else if (nums[r] - nums[l] < d) {
						r++;
					} else {
						used[r] = true;
						ans[i++] = nums[l] + k;
						r++;
						l++;
					}
				}
				if (i == m) {
					return ans;
				}
			}
		}
		return vector<int>{};
	}

};
