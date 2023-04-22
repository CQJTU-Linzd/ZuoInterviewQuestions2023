// P18
// https://www.bilibili.com/video/BV1DT411s7hp?p=18&vd_source=2286e10835cc4cd375b26d18d9e6fa7e

class NumberOfGoodSubSets {
public:

    int mod = 1e9 + 7;

    int primes[31] = {
        0, // 0 00000000
        0, // 1 00000000
        1, // 2 00000001
        2, // 3 00000010
        0, // 4 00000000
        4, // 5 00000100
        3, 8, 0, 0, 5, 16, 0, 32, 9, 6, 0, 64, 0, 128, 0, 10,
        17, 256, 0, 0, 33, 0, 0, 512, 7
    };

    int count[31] = { 0 };
    int status[1 << 10] = { 0 };

    int numberOfGoodSubsets(vector<int>& nums) {
        for (int num : nums) {
            count[num]++;
        }
        status[0] = 1;
        for (int i = 0; i < count[1]; i++) {
            status[0] = (status[0] << 1) % mod;
        }

        for (int i = 2; i <= 30; i++) {
            int curPrimesStatus = primes[i];
            if (curPrimesStatus != 0 && count[i] != 0) {
                for (int from = 0; from < (1 << 10); from++) {
                    if ((from & curPrimesStatus) == 0) {
                        int to = from | curPrimesStatus;
                        //status[to] += count[i] * status[from];
                        status[to] = ((long long)status[to] + (((count[i] * (long long)status[from])))) % mod;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i < (1 << 10); i++) {
            ans = (ans + status[i] % mod) % mod;
        }
        return ans;
    }

};
