// 19
// https://www.bilibili.com/video/BV1DT411s7hp?p=19&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
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
        vector<vector<int>>dp(n, vector<int>(n, -1));
        return process(arr, 0, 0, dp);
    }

    // j: arr[0...i-1]已经做完决定的部分，左括号比右括号多j个
    int process(vector<int>& arr, int i, int j, vector<vector<int>>& dp) {
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        if (i == arr.size()) {
            return j == 0 ? 1 : 0;
        }
        if (j < 0) {
            return 0;
        }
        if (arr.size() - i < j) {
            return 0;
        }

        if (arr[i] != 0) {
            dp[i][j] = process(arr, i + 1, j + 1, dp);
            return dp[i][j];
        } else {
            // 可选左括号或右括号
            int p1 = process(arr, i, j + 1, dp);
            int p2 = process(arr, i, j - 1, dp);
            dp[i][j] = p1 + p2;
            return dp[i][j];
        }
    }

};
