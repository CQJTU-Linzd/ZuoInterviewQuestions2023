// 114
// https://www.bilibili.com/video/BV1DT411s7hp?p=114&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MagicSum {
public:

    int maxSum(vector<int>& arr, vector<vector<int>>& magics) {
        int n = arr.size();
        SegmentTree st(n);
        sort(magics.begin(), magics.end(), [](vector<int>& a, vector<int>& b)->int {
            return a[2] < b[2];
             });
        for (auto& magic : magics) {
            st.update(magic[0] + 1, magic[1] + 1, magic[2], 1, n, 1);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += max(st.getSum(i + 1, i + 1, 1, n, 1), arr[i]);
        }
        return ans;
    }

    class SegmentTree {
        // update
        // getSum
        int MAXN;
        vector<int>sums;
        vector<bool>updates;
        vector<int>change;
    public:

        SegmentTree(int size) {
            MAXN = size + 1;
            sums.resize(MAXN << 2);
            updates.resize(MAXN << 2);
            change.resize(MAXN << 2);
        }

        void pushUp(int rt) {
            sums[rt] = sums[rt << 1] + sums[rt << 1 | 1];
        }

        void pushDown(int rt, int ln, int rn) {
            if (updates[rt]) {
                updates[rt << 1] = true;
                updates[rt << 1 | 1] = true;
                updates[rt] = false;

                sums[rt << 1] = ln * change[rt];
                sums[rt << 1 | 1] = rn * change[rt];

                change[rt << 1] = change[rt];
                change[rt << 1 | 1] = change[rt];
            }
        }

        void update(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) {
                sums[rt] = C * (r - l + 1);
                updates[rt] = true;
                change[rt] = C;
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

        int getSum(int L, int R, int l, int r, int rt) {
            if (L <= l && r <= R) {
                return sums[rt];
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            int ans = 0;
            if (L <= mid) {
                ans += getSum(L, R, l, mid, rt << 1);
            }
            if (R > mid) {
                ans += getSum(L, R, mid + 1, r, rt << 1 | 1);
            }
            return ans;
        }

    };

};
