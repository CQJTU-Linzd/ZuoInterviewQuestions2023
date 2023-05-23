// 78
// https://www.bilibili.com/video/BV1DT411s7hp?p=78&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinDaysDoneAddProjects {
public:

    int minDays(vector<vector<int>>& projects, int k) {
        int l = 0;
        int r = 0;
        for (auto& p : projects) {
            r = max(r, p[0]);
        }
        int ans = r;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (check(projects, m) <= k) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
    }

    int check(vector<vector<int>>& projects, int days) {
        int ans = 0;
        for (auto& p : projects) {
            if (p[0] > days) {
                ans += (p[0] - days) * p[1];
            }
        }
        return ans;
    }

};
