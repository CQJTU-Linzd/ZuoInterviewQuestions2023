// 102
// https://www.bilibili.com/video/BV1DT411s7hp?p=102&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。
// 在加热器的加热半径范围内的每个房屋都可以获得供暖。
// 现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置，
// 请你找出并返回可以覆盖所有房屋的最小加热半径。
// 说明：所有供暖器都遵循你的半径标准，加热的半径都一样。
// 测试链接 :https://leetcode.cn/problems/heaters
class Heaters {
public:

    // 法一

    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int l = 0;
        int r = 1e9;
        int ans = 0;

        while (l <= r) {
            int mid = (l + r) >> 1;
            if (ok(houses, heaters, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }

    bool ok(vector<int>& houses, vector<int>& heaters, int R) {
        int i = 0;
        int j = 0;
        int curCoverL = heaters[0] - R;
        int curCoverR = heaters[0] + R;
        while (i < houses.size()) {
            if (curCoverL <= houses[i] && houses[i] <= curCoverR) {
                i++;
            } else {
                if (j == heaters.size() - 1) {
                    return false;
                } else {
                    j++;
                    curCoverL = heaters[j] - R;
                    curCoverR = heaters[j] + R;
                }
            }
        }
        return true;
    }

    // 法二
    int findRadius2(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int ans = 0;
        for (int i = 0, j = 0; i < houses.size(); i++) {
            // 由j号火炉给i号房供暖，是不是最优的
            while (!best(houses, heaters, i, j)) {
                j++;
            }
            ans = max(ans, abs(heaters[j] - houses[i]));
        }
    }

    bool best(vector<int>& houses, vector<int>& heaters, int i, int j) {
        return
            j == heaters.size() - 1 // 已经是最后的火炉了
            ||
            // 下一个火炉到房子的距离大于当前火炉到房子的距离
            abs(heaters[j + 1] - houses[i]) > abs(heaters[j] - houses[i]);
    }

};
