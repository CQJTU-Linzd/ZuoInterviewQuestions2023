// 30
// https://www.bilibili.com/video/BV1DT411s7hp?p=30&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SumEvenSubNumber {
public:

    int number(vector<int>& arr, int k) {
        int n = arr.size();
        // even[i][j]: arr的前i个数中，选出j个，和是偶数的子序列个数
        // odd[i][j]: arr的前i个数中，选出j个，和是奇数的子序列个数
        vector<vector<int>>even(n + 1, vector<int>(k + 1));
        vector<vector<int>>odd(n + 1, vector<int>(k + 1));
        for (int i = 0; i <= n; i++) {
            even[i][0] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                even[i][j] = even[i - 1][j];
                odd[i][j] = odd[i - 1][j];
                even[i][j] += arr[i - 1] & 1 ? odd[i - 1][j - 1] : even[i - 1][j - 1];
                odd[i][j] += arr[i - 1] & 1 ? even[i - 1][j - 1] : odd[i - 1][j - 1];
            }
        }
        return even[n][k];
    }

};
