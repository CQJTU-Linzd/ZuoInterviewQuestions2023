// 44
// https://www.bilibili.com/video/BV1DT411s7hp?p=44&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class NumberOfCannon {
public:

    // (1) 只有一门大炮，最多打中几发导弹 
    int mostMissiles(vector<int>& arr) {
        if (arr.empty()) {
            return 0;
        }
        reverse(arr.begin(), arr.end());
        return lis(arr);
    }
    int lis(vector<int>& arr) {
        int n = arr.size();
        vector<int>dp(n);
        vector<int>ends(n);
        int ans = 0;
        int right = 0;
        dp[0] = 1;
        ends[0] = arr[0];
        for (int i = 1; i < n; i++) {
            int l = 0;
            int r = right;
            while (l <= r) {
                int m = (l + r) >> 1;
                if (ends[m] >= arr[i]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            right = max(right, l);
            ends[l] = arr[i];
            dp[i] = l + 1;
            ans = max(ans, dp[i]);
        }
        return ans;
    }


    // (2) 要把所有大炮打下来，最少需要几门大炮
    int minCannon(vector<int>& arr) {
        map<int, int>map;
        for (int num : arr) {
            if (map.lower_bound(num + 1) == map.end()) {
                map[INT_MAX]++;
            } else {
                int bound = map.lower_bound(num + 1)->first;
                map[bound]--;
                if (map[bound] == 0) {
                    map.erase(bound);
                }
                map[num]++;
            }
        }
        int ans = 0;
        for (auto& it : map) {
            ans += it.second;
        }
        return ans;
    }

};
