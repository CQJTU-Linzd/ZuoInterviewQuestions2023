// 52
// https://www.bilibili.com/video/BV1DT411s7hp?p=52&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class PerfectPairNum {
public:

    int perfectNums(vector<vector<int>>& matrix) {
        unordered_map<string, int>map;
        int ans = 0;
        for (auto& arr : matrix) {
            string self = ""; // 自己的差值特征
            string target = ""; // self的相反数组成的差值特征，在map中要找的差值特征
            for (int i = 1; i < arr.size(); i++) {
                self += "_" + to_string(arr[i] - arr[i - 1]);
                target += "_" + to_string(arr[i - 1] - arr[i]);
            }
            ans += map.count(target) ? map[target] : 0;
            map[self]++;
        }
        return ans;
    }

};
