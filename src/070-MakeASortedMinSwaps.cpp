// 70
// https://www.bilibili.com/video/BV1DT411s7hp?p=70&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MakeASortedMinSwaps {
public:

    int minSwaps(vector<int>& A, vector<int>& B) {
        sort(B.begin(), B.end());
        int ans = process(A, B, 0, 0, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    int process(vector<int>& A, vector<int>& B, int ai, int bi, bool pre) {
        if (ai == A.size()) {
            return 0;
        }
        int prePrice = INT_MAX;
        if (pre == false) {
            prePrice = A[ai - 1];
        } else {
            prePrice = B[bi - 1];
        }

        // 不换
        int p1 = INT_MAX;
        if (prePrice < A[ai]) {
            p1 = process(A, B, ai + 1, bi, false);
        }

        // 换
        int p2 = INT_MAX;
        int changeIndex = mostLeftIndex(B, bi, prePrice);
        if (changeIndex != -1) {
            int next2 = process(A, B, ai + 1, changeIndex + 1, true);
            if (next2 != INT_MAX) {
                p2 = 1 + next2;
            }
        }
        return min(p1, p2);
    }
    int mostLeftIndex(vector<int>& arr, int begin, int target) {
        int l = begin;
        int r = arr.size() - 1;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (arr[m] > target) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

};
