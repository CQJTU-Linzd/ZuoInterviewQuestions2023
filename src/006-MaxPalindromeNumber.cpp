// P6
// https://www.bilibili.com/video/BV1DT411s7hp?p=6
class MaxPalindromeNumber {
public:
    string largestPalindromic(string num) {
        if (num == "") {
            return "";
        }
        vector<int>arr(10);
        for (char ch : num) {
            arr[ch - '0']++;
        }
        // 检查出现次数大于1次的数里，是不是只有0
        if (onlyZeroMore(arr)) { // 只有0出现次数大于1
            for (int i = 9; i >= 0; i--) {
                if (arr[i] > 0) {
                    return to_string(i);
                }
            }
        } else {
            string left = "";
            string right = "";
            int i = 9;
            while (i >= 0) {
                if (arr[i] > 1) { // 拿来拼
                    left.push_back('0' + i);
                    arr[i] -= 2;
                } else {
                    i--;
                }
            }
            right = left;
            reverse(right.begin(), right.end());
            // 把出现次数恰好为1次的最大数字放在中间
            for (i = 9; i >= 0; i--) {
                if (arr[i] == 1) {
                    left.push_back('0' + i);
                    break;
                }
            }
            return left + right;
        }
    }
    bool onlyZeroMore(vector<int>& arr) {
        if (arr[0] < 2) {
            return false;
        } else {
            for (int i = 1; i <= 9; i++) {
                if (arr[i] > 1) {
                    return false;
                }
            }
            return true;
        }
    }
};
