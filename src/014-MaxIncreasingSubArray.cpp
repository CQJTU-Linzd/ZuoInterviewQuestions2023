// P14
// https://www.bilibili.com/video/BV1DT411s7hp?p=14&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxIncreasingSubArray {
public:
    int maxLength(vector<int>& arr) {
        int n = arr.size();
        vector<int>sorted(arr);
        sort(sorted.begin(), sorted.end());
        SegmentTree st(sorted);
        st.update(rank(sorted, arr[0]), rank(sorted, arr[0]), 1, 1, n, 1);
        vector<int>dp(n);
        dp[0] = 1;
        int ans = 1;
        int cur = 1;
        for (int i = 1; i < n; i++) {
            int _rank = rank(sorted, arr[i]);

            int p1 = arr[i - 1] < arr[i] ? dp[i - 1] + 1 : 1;
            int p2 = _rank > 1 ? (st.getMax(1, _rank - 1, 1, n, 1) + 1) : 1;

            dp[i] = max(p1, p2);
            ans = max(ans, dp[i]);
            if (arr[i] > arr[i - 1]) {
                cur++;
            } else {
                cur = 1;
            }

            if (st.getMax(_rank, _rank, 1, n, 1) < cur) {
                st.update(_rank, _rank, cur, 1, n, 1);
            }
        }
        return ans;
    }

    int rank(vector<int>& sorted, int num) {
        int l = 0;
        int r = sorted.size() - 1;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (sorted[m] >= num) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans + 1;
    }


    // 线段树
    class SegmentTree {
    public:

        int N;
        vector<int>arr;
        vector<int>sum;
        vector<int>lazy;
        vector<int>change;
        vector<bool>updates;

        vector<int>maxArr;

        SegmentTree(vector<int>& origin) {
            N = origin.size() + 1;
            arr.resize(N); // 0下标不用 从1开始使用
            for (int i = 1; i < N; i++) {
                arr[i] = origin[i - 1];
            }
            sum.resize(N << 2);
            lazy.resize(N << 2);
            change.resize(N << 2);
            updates.resize(N << 2);
            maxArr.resize(N << 2);
        }

        // 初始化阶段，先把sum数组填好
        // 在arr[l...r]范围上，去build
        // rt：这个范围在sum数组中的下标
        void build(int l, int r, int rt) {
            if (l == r) {
                sum[rt] = arr[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(l, mid, rt << 1);
            build(mid + 1, r, rt << 1 | 1); // rt << 1 | 1，其实就是 rt * 2 + 1
            pushUp(rt); // 汇总
        }

        void pushUp(int rt) {
            sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
            maxArr[rt] = max(maxArr[rt << 1], maxArr[rt << 1 | 1]);
        }

        // L...R：任务范围，所有的值累加上C
        // l...r：表达的范围
        void add(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) { // 任务范围把当前范围覆盖了
                sum[rt] += (r - l + 1) * C;
                lazy[rt] += C;
                return;
            }
            // 任务没有把当前范围l...r全覆盖，需要继续往下发
            int mid = (l + r) >> 1;
            // 下发之前攒的所有任务
            pushDown(rt, mid - l + 1, r - mid);
            // 左孩子是否需要接受任务
            if (L <= mid) {
                add(L, R, C, l, mid, rt << 1);
            }
            // 右孩子是否需要接受任务
            if (R >= mid + 1) {
                add(L, R, C, mid + 1, r, rt << 1 | 1);
            }
            // 左右孩子做完任务后，更新我的sum信息
            pushUp(rt);
        }

        // L...R范围上的数更新为C
        void update(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) {
                updates[rt] = true;
                change[rt] = C;
                sum[rt] = C * (r - l + 1);
                lazy[rt] = 0;
                maxArr[rt] = C;
                return;
            }
            // 任务要往下发
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            if (L <= mid) {
                update(L, R, C, l, mid, rt << 1);
            }
            if (R >= mid + 1) {
                update(L, R, C, mid + 1, r, rt << 1 | 1);
            }
            pushUp(rt);
        }

        // 懒增加和懒更新，从父范围，发给左右两个子范围
        // ln表示左子树元素节点个数，rn表示右子树元素节点个数
        void pushDown(int rt, int ln, int rn) {
            if (updates[rt]) { // rt这个范围要更新成新的值
                updates[rt << 1] = true;
                updates[rt << 1 | 1] = true;

                change[rt << 1] = change[rt];
                change[rt << 1 | 1] = change[rt];

                lazy[rt << 1] = 0;
                lazy[rt << 1 | 1] = 0;

                sum[rt << 1] = ln * change[rt];
                sum[rt << 1 | 1] = rn * change[rt];

                maxArr[rt << 1] = change[rt];
                maxArr[rt << 1 | 1] = change[rt];

                updates[rt] = false;
            }
            if (lazy[rt] != 0) {
                lazy[rt << 1] += lazy[rt];
                sum[rt << 1] += lazy[rt] * ln;
                lazy[rt << 1 | 1] += lazy[rt];
                sum[rt << 1 | 1] += lazy[rt] * rn;
                lazy[rt] = 0;
            }
        }

        // L...R范围上的累加和是多少
        int query(int L, int R, int l, int r, int rt) {
            if (L <= l && r <= R) {
                return sum[rt];
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            int ans = 0;
            if (L <= mid) {
                ans += query(L, R, l, mid, rt << 1);
            }
            if (R >= mid + 1) {
                ans += query(L, R, mid + 1, R, rt << 1 | 1);
            }
            return ans;
        }

        // L...R范围上的最大值是多少
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
