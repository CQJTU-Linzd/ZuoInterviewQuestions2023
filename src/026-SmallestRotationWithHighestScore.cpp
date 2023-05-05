// 26
// https://www.bilibili.com/video/BV1DT411s7hp?p=26&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SmallestRotationWithHighestScore {
public:

    int bestRotation(vector<int>& nums) {
        int n = nums.size();
        // cnt[i]: 是个差分数组
        // 求完前缀和之后，表示：nums整体往右移动i次，最大得分是多少
        vector<int>cnt(n + 1);
        for (int i = 0; i < n; i++) {
            if (nums[i] < n) {
                if (nums[i] < i) {
                    add(cnt, 0, n - i - 1);
                    add(cnt, n - i + nums[i], n - 1);
                } else {
                    add(cnt, nums[i] - i, n - i - 1);
                }
            }
        }
        // 求前缀和
        for (int i = 1; i <= n; i++) {
            cnt[i] += cnt[i - 1];
        }
        // 往右移动任意次，得到的最大得分已经求出来了
        
        int maxScore = cnt[0];
        int ans = 0;
        for (int i = n - 1; i >= 1; i--) {
            if (cnt[i] > maxScore) {
                ans = i;
                maxScore = cnt[i];
            }
        }
        return ans == 0 ? 0 : (n - ans);
    }

    void add(vector<int>& cnt, int l, int r) {
        cnt[l]++;
        cnt[r + 1]--;
    }

};
