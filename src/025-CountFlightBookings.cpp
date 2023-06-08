// 25
// https://www.bilibili.com/video/BV1DT411s7hp?p=25&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 这里有 n 个航班，它们分别从 1 到 n 进行编号。
// 有一份航班预订表 bookings ，
// 表中第 i 条预订记录 bookings[i] = [firsti, lasti, seatsi]
// 意味着在从 firsti 到 lasti 
//（包含 firsti 和 lasti ）的 每个航班 上预订了 seatsi 个座位。
// 请你返回一个长度为 n 的数组 answer，里面的元素是每个航班预定的座位总数。
// 测试链接 : https://leetcode.cn/problems/corporate-flight-bookings/
class CountFlightBookings {
public:

    vector<int> flightBookings(vector<vector<int>>& bookings, int n) {
        vector<int>cnt(n + 2); // 差分数组
        for (vector<int>& book : bookings) {
            cnt[book[0]] += book[2];
            cnt[book[1] + 1] -= book[2];
        }
        for (int i = 1; i < cnt.size(); i++) {
            cnt[i] += cnt[i - 1];
        }
        vector<int>ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = cnt[i + 1];
        }
        return ans;
    }

    // 线段树做法

    vector<int> flightBookings2(vector<vector<int>>& bookings, int n) {
        SegmentTree st(n);
        for (auto& book : bookings) {
            st.add(book[0], book[1], book[2], 1, n + 1, 1);
        }
        vector<int>ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = st.query(i + 1, i + 1, 1, n + 1, 1);
        }
        return ans;
    }

    class SegmentTree {
        int n;
        vector<int>sums;
        vector<int>lazy;
    public:

        SegmentTree(int size) {
            n = size + 1;
            sums.resize(n << 2);
            lazy.resize(n << 2);
        }

        void pushUp(int rt) {
            sums[rt] = sums[rt << 1] + sums[rt << 1 | 1];
        }

        void pushDown(int rt, int ln, int rn) {
            if (lazy[rt] != 0) {
                lazy[rt << 1] += lazy[rt];
                lazy[rt << 1 | 1] += lazy[rt];

                sums[rt << 1] += lazy[rt] * ln;
                sums[rt << 1 | 1] += lazy[rt] * rn;

                lazy[rt] = 0;
            }
        }

        void add(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) {
                lazy[rt] += C;
                sums[rt] += C * (r - l + 1);
                return;
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            if (L <= mid) {
                add(L, R, C, l, mid, rt << 1);
            }
            if (R > mid) {
                add(L, R, C, mid + 1, r, rt << 1 | 1);
            }
            pushUp(rt);
        }

        int query(int L, int R, int l, int r, int rt) {
            if (L <= l && r <= R) {
                return sums[rt];
            }
            int mid = (l + r) >> 1;
            pushDown(rt, mid - l + 1, r - mid);
            int ans = 0;
            if (L <= mid) {
                ans += query(L, R, l, mid, rt << 1);
            }
            if (R > mid) {
                ans += query(L, R, mid + 1, r, rt << 1 | 1);
            }
            return ans;
        }

    };

    // for test

    // [13, 24, 5]
    vector<vector<int>> randomBookings(int size, int l, int r) {
        vector<vector<int>>res(size, vector<int>(3));
        for (int i = 0; i < size; i++) {
            int a = rand() % (r - l + 1) + l;
            int b = rand() % (r - l + 1) + l;
            int L = min(a, b);
            int R = max(a, b);
            int val = rand() % (r - l + 1) + l;
            res[i][0] = L;
            res[i][1] = R;
            res[i][2] = val;
        }
        return res;
    }

    void test() {
        srand(time(0));
        for (int t = 0; t < 5000; t++) {
            int n = rand() % (1000 - 1 + 1) + 1;
            int size = rand() % (1000 - 1 + 1) + 1;
            auto bookings = randomBookings(size, 1, n);
            auto ans1 = flightBookings(bookings, n);
            auto ans2 = flightBookings2(bookings, n);
            if (ans1 != ans2) {
                cout << "fuck" << endl;
            }
        }
    }


};
