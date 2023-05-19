// 67
// https://www.bilibili.com/video/BV1DT411s7hp?p=67&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SumOfSubSequenceWidth {
public:

    int sumOfWidth(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        if (arr.size() <= 1) {
            return 0;
        }
        if (arr.size() == 2) {
            return arr[1] - arr[0];
        }
        int mod = 1e9 + 7;
        long ans = 0;
        
        long A = arr[1];
        long B = 1;
        long C = arr[0];
        ans += A * B - C;
        ans %= mod;
        for (int i = 2; i < arr.size(); i++) {
            A = arr[i] % mod;
            B = (B + (1 << (i - 1))) % mod;
            C = (C * 2 + arr[i - 1]) % mod;
            ans += (A * B - C) % mod;
            ans %= mod;
        }
        return ans;
    }

};
