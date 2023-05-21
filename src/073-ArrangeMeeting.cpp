// 73
class ArrangeMeeting {
public:

    // 暴力
    vector<vector<int>> arrange1(vector<vector<int>>& meetings) {
        int maxVal = 0;
        for (auto& meeting : meetings) {
            maxVal = max(maxVal, meeting[1]);
        }
        vector<bool>occupy(maxVal + 1);
        vector<vector<int>>ans;
        for (int i = meetings.size() - 1; i >= 0; i--) {
            auto cur = meetings[i];
            bool add = true;
            for (int j = cur[0]; j < cur[1]; j++) {
                if (occupy[j]) {
                    add = false;
                    break;
                }
            }
            if (add) {
                ans.push_back(cur);
            }
            for (int j = cur[0]; j < cur[1]; j++) {
                occupy[j] = true;
            }
        }
        return ans;
    }

    // 正式
    vector<vector<int>> arrange2(vector<vector<int>>& meetings) {
        int n = meetings.size();
        vector<int>rank;
        for (auto& meet : meetings) {
            rank.push_back(meet[0]);
            rank.push_back(meet[1]);
        }
        sort(rank.begin(), rank.end());
        map<int, int>map;
        int index = 1;
        for (int cur : rank) {
            if (!map.count(cur)) {
                map[cur] = index++;
            }
        }


        SegmentTree st(index);
        vector<vector<int>>ans;
        for (int i = meetings.size() - 1; i >= 0; i--) {
            int begin = meetings[i][0];
            int end = meetings[i][1];

            // 映射成线段树中的节点
            int from = map[begin];
            int to = map[end];

            if (st.getSum(from, to, 1, index, 1) == 0) {
                ans.push_back(meetings[i]);

            }
            st.add(from, to, 1, 1, index, 1);
        }
        return ans;
    }

    class SegmentTree {

        int MAXN;
        vector<int>sums;
        vector<int>lazy;

    public:

        SegmentTree(int size) {
            MAXN = size;
            sums.resize(MAXN << 2);
            lazy.resize(MAXN << 2);
        }

        void pushUp(int rt) {
            sums[rt] = sums[rt << 1] + sums[rt << 1 | 1];
        }

        void pushDown(int rt, int ln, int rn) {
            if (lazy[rt] != 0) {
                lazy[rt << 1] += lazy[rt];
                lazy[rt << 1 | 1] += lazy[rt];
                sums[rt << 1] += ln * lazy[rt];
                sums[rt << 1 | 1] += rn * lazy[rt];
                lazy[rt] = 0;
            }
        }

        void add(int L, int R, int C, int l, int r, int rt) {
            if (L <= l && r <= R) {
                sums[rt] += C * (r - l + 1);
                lazy[rt] += C;
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


    // for test
    vector<vector<int>> randomMeeting(int size, int l, int r) {
        srand(NULL);
        vector<vector<int>>res(size, vector<int>(2));
        for (int i = 0; i < size; i++) {
            int a = rand() % (r - l + 1) + l;
            int b = rand() % (r - l + 1) + l;
            if (a == b) {
                b++;
            }
            res[i][0] = min(a, b);
            res[i][1] = max(a, b);
        }
        return res;
    }


    void test() {
        srand(NULL);
        for (int t = 0; t < 100; t++) {
            int size = rand() % (100 - 1 + 1) + 1;
            auto meetings1 = randomMeeting(size, 1, 100);
            vector<vector<int>>meetings2 = meetings1;
            auto ans1 = arrange1(meetings1);
            auto ans2 = arrange1(meetings2);
            if (ans1 != ans2) {
                cout << "fuck" << endl;
            }
        }

    }

};
