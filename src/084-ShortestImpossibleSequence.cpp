// 84
// https://www.bilibili.com/video/BV1DT411s7hp?p=87&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ShortestImpossibleSequence {
public:

    int shortestSequence(vector<int>& rolls, int k) {
        bool* set = new bool[k + 1];
        for (int i = 0; i <= k; i++) {
            set[i] = false;
        }
        int size = 0; // 当前这一套，收集到几个数字了
        int ans = 0; // 一共能收集几套
        for (int num : rolls) {
            if (!set[num]) {
                set[num] = true;
                size++;
            }
            if (size == k) {
                ans++;
                fill(set, set + k + 1, false);
                size = 0;
            }
        }
        delete[] set;
        return ans + 1;
    }

};
