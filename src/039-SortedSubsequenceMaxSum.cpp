// 39
// https://www.bilibili.com/video/BV1DT411s7hp?p=39&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SortedSubsequenceMaxSum {
public:

    int maxSum(vector<int>& h, vector<int>& v) {
        int n = h.size();
        vector<int>rank(h);
        sort(rank.begin(), rank.end());
        SegmentTree st(n);
        for (int i = 0; i < n; i++) {
            int height = getRank(rank, h[i]);
            st.update(height, st.getMax(height) + v[i]);
        }
        return st.getMax(n);
    }

    int getRank(vector<int>& rank, int height) {
        int l = 0;
        int r = rank.size() - 1;
        int ans = 0;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            if (rank[m] >= height) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans + 1;
    }

    class SegmentTree {
        int n;
        vector<int>maxArr;
        vector<int>updateArr;
    public:
        SegmentTree(int maxSize) {
            n = maxSize + 1;
            maxArr.resize(n << 2);
            updateArr.resize(n << 2, -1);
        }

        void update(int index, int c) {
            update(index, index, c, 1, n, 1);
        }

        int getMax(int right) {
            return getMax(1, right, 1, n, 1);
        }

        void pushUp(int rt) {
            maxArr[rt] = max(maxArr[rt << 1], maxArr[rt << 1 | 1]);
        }

        void pushDown(int rt, int ln, int rn) {
            if (updateArr[rt] != -1) {
                updateArr[rt << 1] = updateArr[rt];
                maxArr[rt << 1] = updateArr[rt];
                updateArr[rt << 1 | 1] = updateArr[rt];
                maxArr[rt << 1 | 1] = updateArr[rt];
                updateArr[rt] = -1;
            }
        }

        void update(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) {
                maxArr[rt] = C;
                updateArr[rt] = C;
                return;
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            if (L <= mid) {
                update(L, R, C, l, mid, rt << 1);
            }
            if (R > mid) {
                update(L, R, C, mid + 1, r, rt << 1 | 1);
            }
            pushUp(rt);
        }

        int getMax(int L, int R, int l, int r, int rt) {
            if (L <= l && r <= R) {
                return maxArr[rt];
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            int ans = 0;
            if (L <= mid) {
                ans = max(ans, getMax(L, R, l, mid, rt << 1));
            }
            if (R > mid) {
                ans = max(ans, getMax(L, R, mid + 1, r, rt << 1 | 1));
            }
            return ans;
        }

    };

};
