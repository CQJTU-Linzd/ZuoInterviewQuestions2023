// 23
// https://www.bilibili.com/video/BV1DT411s7hp?p=23&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class CutOrPoison {
public:

    int fast(vector<int>& cuts, vector<int>& poisons, long hp) {
        int l = 1;
        int r = hp + 1;
        int ans = 0;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            if (ok(cuts, poisons, hp, m)) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

    bool ok(vector<int>& cuts, vector<int>& poisons, long hp, int limit) {
        int n = min((int)cuts.size(), limit);
        for (int i = 0, j = 1; i < n; i++, j++) {
            hp -= max(cuts[i], (limit - j) * poisons[j]);
            if (hp <= 0) {
                return false;
            }
        }
        return true;
    }
};
