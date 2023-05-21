// 76
// https://www.bilibili.com/video/BV1DT411s7hp?p=76&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MagicStone {
public:

    int minCost(vector<vector<int>>& stones) {
        int n = stones.size();
        if (n & 1) {
            return -1;
        }
        sort(stones.begin(), stones.end(), [](vector<int>& a, vector<int>& b)->int {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            } else {
                return (a[1] - a[2]) > (b[1] - b[2]);
            } });
        int zero = 0;
        int red = 0;
        int blue = 0;
        int cost = 0;
        for (auto& stone : stones) {
            if (stone[0] == 0) {
                zero++;
                cost += stone[1];
            } else if (stone[0] == 1) {
                red++;
            } else {
                blue++;
            }
        }
        if (red > n / 2 || blue > n / 2) {
            return -1;
        }
        blue = zero - (n / 2 - red); // zero中，需要分配给蓝色石头blue块
        for (int i = 0; i < blue; i++) {
            cost += stones[i][2] - stones[i][1];
        }
        return cost;
    }

};
