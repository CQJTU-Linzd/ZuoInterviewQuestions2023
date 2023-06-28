// 93
// https://www.bilibili.com/video/BV1DT411s7hp?p=93&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给你一根长度为 n 的绳子
// 请把绳子剪成整数长度的 m 段
// m、n都是整数，n > 1并且m > 1
// 每段绳子的长度记为 k[0],k[1]...k[m - 1]
// 请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少
// 例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18
// 答案需要取模1000000007
// 测试链接 : https://leetcode.cn/problems/jian-sheng-zi-ii-lcof/
class SplitNumberProductMax {
public:
    const int mod = 1e9 + 7;
    int cuttingRope(int n) {
        if (n == 2) {
            return 1;
        }
        if (n == 3) {
            return 2;
        }
        int rest = n % 3 == 0 ? n : (n % 3 == 1 ? (n - 4) : (n - 2));
        int last = n % 3 == 0 ? 1 : (n % 3 == 1 ? 4 : 2);
        int ans = pow(3, rest / 3) * last;
        return ans % mod;
    }

};
