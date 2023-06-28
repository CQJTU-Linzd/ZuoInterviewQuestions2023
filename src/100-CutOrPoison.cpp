// 100
// https://www.bilibili.com/video/BV1DT411s7hp?p=100&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给定怪兽的血量为hp
// 第i回合如果用刀砍，怪兽在这回合会直接掉血，没有后续效果
// 第i回合如果用毒，怪兽在这回合不会掉血，
// 但是之后每回合都会掉血，并且所有中毒的后续效果会叠加
// 给定的两个数组cuts、poisons，两个数组等长，长度都是n
// 表示你在n回合内的行动，
// 每一回合的刀砍的效果由cuts[i]表示
// 每一回合的中毒的效果由poisons[i]表示
// 如果你在n个回合内没有直接杀死怪兽，意味着你已经无法有新的行动了
// 但是怪兽如果有中毒效果的话，那么怪兽依然会在hp耗尽的那回合死掉
// 返回你最快能在多少回合内将怪兽杀死
// 数据范围 : 
// 1 <= n <= 10的5次方
// 1 <= hp <= 10的9次方
// 1 <= cuts[i]、poisons[i] <= 10的9次方
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
