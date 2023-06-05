// 121
// https://www.bilibili.com/video/BV1DT411s7hp?p=121&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SplitApples {
public:

    int ways1(int apples, int plates) {
        return process(apples, plates, 1);
    }

    // apples: 剩余的苹果数
    // plates: 剩余的盘子数
    // pre: 前一个盘子的苹果数量，当前盘子的苹果数量不能小于pre
    int process(int apples, int plates, int pre) {
        if (apples == 0) {
            return 1;
        }
        if (plates == 0) {
            return 0;
        }
        if (pre > apples) {
            return 0;
        }
        int ans = 0;
        for (int cur = apples; cur <= apples; cur++) {
            ans += process(apples - cur, plates - 1, cur);
        }
        return ans;
    }


    // 法二
    int ways2(int apples, int plates) {
        if (apples == 0) {
            return 1;
        }
        if (plates == 0) {
            return 0;
        }
        if (plates > apples) {
            return ways2(apples, apples);
        } else {
            return ways2(apples - plates, plates) + ways2(apples, plates - 1);
        }
    }

};
