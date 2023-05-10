// 33
// https://www.bilibili.com/video/BV1DT411s7hp?p=33&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class PickBallsWin {
public:

    string whoWin(int balls) {
        return process(0, balls, 0, 0);
    }

    string process(int turn, int rest, int jia, int yi) {
        if (rest == 0) {
            return (jia & 1) == 0 ? "甲" : "乙";
        }
        if (turn == 0) { // 甲的回合
            for (int pick = 1; pick <= min(3, rest); pick++) {
                if (process(1, rest - pick, jia + pick, yi) == "甲") {
                    return "甲";
                }
            }
            return "乙";
        } else {
            for (int pick = 1; pick <= min(3, rest); pick++) {
                if (process(0, rest - pick, jia + pick, yi) == "乙") {
                    return "乙";
                }
            }
            return "甲";
        }
    }

};
