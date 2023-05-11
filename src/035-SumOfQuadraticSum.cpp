// 35
// https://www.bilibili.com/video/BV1DT411s7hp?p=35&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SumOfQuadraticSum {
public:

    long sum(long n) {
        long sqrtN = (long)sqrt(n);
        long ans = 0;
        // 前半段
        for (int i = 1; i <= sqrtN; i++) {
            ans += (i * i) * (n / i);
        }
        // 后半段
        for (long k = n / (sqrtN + 1); k >= 1; k--) {
            ans += sumOfLimitNumber(n, k);
        }
        return ans;
    }

    // 平方和公式n(n+1)(2n+1)/6
    long sumOfLimitNumber(long v, long n) {
        long r = cover(v, n);
        long l = cover(v, n + 1);
        return ((r * (r + 1) * ((r << 1) + 1)
                - l * (l + 1) * ((l << 1) + 1)) * n)
            / 6;
    }

    long cover(long v, long n) {
        long l = 1;
        long r = v;
        long ans = 0;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            if (m * n <= v) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    }

};
