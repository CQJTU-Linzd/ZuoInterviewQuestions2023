// 130
// https://www.bilibili.com/video/BV1DT411s7hp?p=130&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.cn/problems/two-city-scheduling/
class MaxMoneyOfDrivers {
public:

    int maxMoney(vector<vector<int>>& incomes) {
        if (incomes.empty() || (incomes.size() & 1) != 0) {
            return 0;
        }
        int n = incomes.size();
        int m = n / 2; // A去n/2人，B去n/2人
        return process(incomes, 0, m);
    }

    // i...所有的司机，往A和B区域分配，最终A和B人数同样多的情况下，最大收入是多少
    // A区域还有rest个名额，还需要去rest个人
    int process(vector<vector<int>>& incomes, int i, int rest) {
        if (i == incomes.size()) {
            return 0;
        }
        if (incomes.size() - i == rest) { // B区域已经满了，只能去A！
            return incomes[i][0] + process(incomes, i + 1, rest - 1);
        }
        if (rest == 0) { // A区域已经满了，只能去B！
            return incomes[i][1] + process(incomes, i + 1, rest);
        }
        // 当前司机，可以去A，也可以去B
        int p1 = incomes[i][0] + process(incomes, i + 1, rest - 1);
        int p2 = incomes[i][1] + process(incomes, i + 1, rest);
        return max(p1, p2);
    }

};
