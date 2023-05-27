// 93
// https://www.bilibili.com/video/BV1DT411s7hp?p=93&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SplitNumberProductMax {
public:
    int mod = 1e9 + 7;
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
