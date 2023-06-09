// 104
// https://www.bilibili.com/video/BV1DT411s7hp?p=104&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 在第 1 天，有一个人发现了一个秘密。
// 给你一个整数 delay ，表示每个人会在发现秘密后的 delay 天之后，
// 每天 给一个新的人 分享 秘密。
// 同时给你一个整数 forget ，表示每个人在发现秘密 forget 天之后会 忘记 这个秘密。
// 一个人 不能 在忘记秘密那一天及之后的日子里分享秘密。
// 给你一个整数 n ，请你返回在第 n 天结束时，知道秘密的人数。
// 由于答案可能会很大，请你将结果对 109 + 7 取余 后返回。
// 测试链接 : https://leetcode.cn/problems/number-of-people-aware-of-a-secret/
class NumberOfPeopleKnowSecret {
public:

    int mod = 1e9 + 7;

    int peopleKnowSecret(int n, int delay, int forget) {
        // 第i天知道秘密的人
        long* dpKnow = new long[n + 1];
        // 第i天会忘记秘密的人
        long* dpForget = new long[n + 1];
        // 第i天将会分享秘密的人(也就是会新增的知道秘密的人)
        long* dpShare = new long[n + 1];

        dpKnow[1] = 1;
        if (1 + forget <= n) {
            dpForget[1 + forget] = 1;
        }
        if (1 + delay <= n) {
            dpShare[1 + delay] = 1;
        }

        for (int i = 2; i <= n; i++) {
            dpKnow[i] = dpKnow[i - 1] - dpForget[i] + dpShare[i];
            if (i + forget <= n) {
                dpForget[i + forget] = dpShare[i];
            }
            if (i + delay <= n) {
                dpShare[i + delay] = dpShare[i] + dpShare[i + delay - 1] - dpForget[i + delay];
            }
        }
        long ans = dpKnow[n];
        delete[] dpKnow;
        delete[] dpForget;
        delete[] dpShare;
        return ans;
    }

};
