// 42
// https://www.bilibili.com/video/BV1DT411s7hp?p=42&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxNumberUnderLimit {
public:

    int maxNumber(vector<int>& arr, int limit) {
        sort(arr.begin(), arr.end());
        int offset = 1;
        while (offset <= limit / 10) {
            offset *= 10;
        }
        int ans = process(arr, limit, offset);
        if (ans != -1) {
            return ans;
        } else {
            offset /= 10;
            int rest = 0;
            while (offset > 0) {
                rest += offset * arr.back();
                offset /= 10;
            }
            return rest;
        }
    }

    int process(vector<int>& arr, int limit, int offset) {
        if (offset == 0) {
            return limit;
        }
        int cur = (limit / offset) % 10;
        int near = nearIndex(arr, cur);
        if (near == -1) {
            return -1;
        } else if (arr[near] == cur) {
            int next = process(arr, limit, offset / 10);
            if (next != -1) {
                return next;
            } else {
                if (near > 0) { // 当前这一位数字还有下降的空间
                    near--;
                    return (limit / (offset * 10)) * offset * 10 + (arr[near] * offset) + rest(arr, offset / 10);
                } else {
                    return -1;
                }
            }
        } else { // arr[near] < cur
            return (limit / (offset * 10)) * offset * 10 + (arr[near] * offset) + rest(arr, offset / 10);
        }
    }

    // 有序数组arr
    // 找到<=num的最右位置
    int nearIndex(vector<int>& arr, int num) {
        int l = 0;
        int r = arr.size();
        int ans = -1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (arr[m] <= num) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    }

    int rest(vector<int>& arr, int offset) {
        int rest = 0;
        while (offset > 0) {
            rest += arr.back() * offset;
            offset /= 10;
        }
        return rest;
    }

};
