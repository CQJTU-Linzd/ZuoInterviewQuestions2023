// 38
// https://www.bilibili.com/video/BV1DT411s7hp?p=38&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ModifyOneNumberModXWays {
public:

    int ways(vector<int>& arr, int p, int x) {
        int ans = 0;
        int sum = accumulate(arr.begin(), arr.end(), 0);
        for (int num : arr) {
            ans += cnt(p, num, x, (x - (sum - num) % x) % x);
        }
        return ans;
    }

    // 当前数字num
    // 1~p以内，不能是num的情况下，% x == mod的数字有几个
    int cnt(int p, int num, int x, int mod) {
        int ans = (p / x) + ((p % x) >= mod ? 1 : 0) - (mod == 0 ? 1 : 0);
        // 不能等于num！
        return ans - ((num <= p && num % x == mod) ? 1 : 0);
    }

};
