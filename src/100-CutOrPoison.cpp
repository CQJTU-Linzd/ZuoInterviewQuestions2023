// 100
// https://www.bilibili.com/video/BV1DT411s7hp?p=100&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class CutOrPoison {
public:

    int minRound(vector<int>& cuts, vector<int>& poisons, int hp) {
        int l = 1;
        int r = hp + 1;
        int ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (ok(cuts, poisons, hp, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }

    bool ok(vector<int>& cuts, vector<int>& poisons, int hp, int limit) {
        int n = min((int)cuts.size(), limit);
        for (int i = 0; i < n; i++) {
            int curMax = max(cuts[i], poisons[i] * (limit - i - 1));
            hp -= curMax;
            if (hp <= 0) {
                return true;
            }
        }
        return false;
    }

};
