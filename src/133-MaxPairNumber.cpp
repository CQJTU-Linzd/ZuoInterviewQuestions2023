// 133
// https://www.bilibili.com/video/BV1DT411s7hp?p=133&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxPairNumber {
public:

    int maxPair(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int ans = 0;
        int L = 0;
        int R = 0;
        bool* used = new bool[n];
        for (int i = 0; i < n; i++) {
            used[i] = false;
        }
        while (L < n && R < n) {
            if (used[L]) {
                L++;
            } else if (L == R) {
                R++;
            } else {
                int dis = arr[R] - arr[L];
                if (dis == k) {
                    ans++;
                    used[R] = true;
                    R++;
                    L++;
                } else if (dis < k) {
                    R++;
                } else {
                    L++;
                }
            }
        }
        delete[] used;
        return ans;
    }

};
