// 147
// https://www.bilibili.com/video/BV1DT411s7hp?p=147&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class CardsWinProbability {
public:

    // 谷歌面试题
	// 面值为1~10的牌组成一组，
	// 每次你从组里等概率的抽出1~10中的一张
	// 下次抽会换一个新的组，有无限组
	// 当累加和<17时，你将一直抽牌
	// 当累加和>=17且<21时，你将获胜
	// 当累加和>=21时，你将失败
	// 返回获胜的概率

    double pWin() {
        return f(0);
    }

    double f(int cur) {
        if (cur >= 17 && cur < 21) {
            return 1.0;
        }
        if (cur >= 21) {
            return 0.0;
        }
        double ans = 0.0;
        for (int i = 1; i <= 10; i++) {
            ans += f(cur + i);
        }
        return ans / 10;
    }


    // 进阶
    // 面值为1~N的牌组成一组，
    // 每次你从组里等概率的抽出1~N中的一张
    // 下次抽会换一个新的组，有无限组
    // 当累加和<a时，你将一直抽牌
    // 当累加和>=a且<b时，你将获胜
    // 当累加和>=b时，你将失败
    // 返回获胜的概率，给定的参数为N，a，b

    double pWin2(int n, int a, int b) {
        if (n < 1 || a >= b || a < 0 || b < 0) {
            return 0.0;
        }
        if (b - a >= n) {
            return 1.0;
        }

    }

    double f2(int n, int a, int b, int cur) {
        if (cur >= a && cur < b) {
            return 1.0;
        }
        if (cur >= b) {
            return 0.0;
        }
        double ans = 0.0;
        for (int i = 1; i <= n; i++) {
            ans += f2(n, a, b, cur + i);
        }
        return ans / n;
    }

    // f2的改进：省掉枚举
    double f3(int n, int a, int b, int cur) {
        if (cur >= a && cur < b) {
            return 1.0;
        }
        if (cur >= b) {
            return 0.0;
        }
        if (cur == a - 1) {
            return 1.0 * (b - a) / n;
        }
        double ans = f3(n, a, b, cur + 1) + f3(n, a, b, cur + 1) * n;
        if (cur + 1 + n < b) {
            ans -= f3(n, a, b, cur + n + 1);
        }
        return ans;
    }

};
