// 27
// https://www.bilibili.com/video/BV1DT411s7hp?p=27&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxOneNumbers {
public:

    int maxOneNumbers(vector<int>& arr) {
        int ans = 0;
        for (int& num : arr) {
            ans += num;
            num = num == 0 ? 1 : -1;
        }
        return ans + maxSubArraySum(arr);
    }

    int maxSubArraySum(vector<int>& arr) {
        int ans = INT_MIN;
        int cur = 0;
        for (int i = 0; i < arr.size(); i++) {
            cur += arr[i];
            ans = max(ans, cur);
            cur = cur < 0 ? 0 : cur;
        }
        return ans;
    }

};
