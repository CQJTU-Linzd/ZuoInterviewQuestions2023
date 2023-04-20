// P17
// https://www.bilibili.com/video/BV1DT411s7hp?p=17&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MatchSticksToSquare {
public:

    bool match(vector<int>& arr) {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }
        int len = sum / 4;

        // 最多15根
        // 用位来表示某一根火柴用没用
        int status = 0; // 000000...000000000000000
        return process(arr, status, 0, 0, 4);
    }

    // sum：当前这条边，已经拼到了sum长度
    // len：固定参数，每条边必须达到这个长度
    // edges：还剩几条边没拼完
    bool process(vector<int>& arr, int status, int sum, int len, int edges) {

        if (edges == 0) {
            int n = arr.size();
            int s = (1 << n) - 1;
            return s == status ? true : false;
        }

        // 还有剩余的边要拼
        bool ans = false;
        for (int i = 0; i < arr.size(); i++) { // 每根火柴全试一遍
            if ((status & (1 << i)) == 0) {
                if (sum + arr[i] <= len) {
                    if (sum + arr[i] < len) {
                        ans = process(arr, status | (1 << i), sum + arr[i], len, edges);
                    } else {
                        ans = process(arr, status | (1 << i), 0, len, edges - 1);
                    }
                }
            }
            if (ans) {
                break;
            }
        }
        return ans;
    }


    // 记忆化搜索
    bool match2(vector<int>& arr) {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        if (sum % 4 != 0) {
            return false;
        }
        int len = sum / 4;

        // 最多15根
        // 用位来表示某一根火柴用没用
        int status = 0; // 000000...000000000000000
        // dp[i] == 0：i号火柴没用过
        // dp[i] == 1：i号火柴用过，结果为true
        // dp[i] == -1：i号火柴用过，结果为false
        vector<int>dp(arr.size());
        return process2(arr, status, 0, 0, 4, dp);
    }

    // sum：当前这条边，已经拼到了sum长度
    // len：固定参数，每条边必须达到这个长度
    // edges：还剩几条边没拼完
    bool process2(vector<int>& arr, int status, int sum, int len, int edges, vector<int>& dp) {
        if (dp[status] != 0) {
            return dp[status] == 1;
        }

        if (edges == 0) {
            int n = arr.size();
            int s = (1 << n) - 1;
            return s == status ? true : false;
        }

        // 还有剩余的边要拼
        bool ans = false;
        for (int i = 0; i < arr.size(); i++) { // 每根火柴全试一遍
            if ((status & (1 << i)) == 0) {
                if (sum + arr[i] <= len) {
                    if (sum + arr[i] < len) {
                        ans = process2(arr, status | (1 << i), sum + arr[i], len, edges, dp);
                    } else {
                        ans = process2(arr, status | (1 << i), 0, len, edges - 1, dp);
                    }
                }
            }
            if (ans) {
                break;
            }
        }
        dp[status] = ans ? 1 : -1;
        return ans;
    }
};
