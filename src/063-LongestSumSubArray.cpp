// 63
// https://www.bilibili.com/video/BV1DT411s7hp?p=63&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class LongestSumSubArray {
public:

    int longestSubArray(vector<int>& arr, int target) {
        unordered_map<int, int>map;
        map[0] = -1; // 0这个前缀和，一开始就存在了（什么都不选的时候）
        int len = 0;
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            if (map.count(sum - target)) {
                len = max(len, i - map[sum - target]);
            }
            if (!map.count(sum)) {
                map[sum] = i;
            }
        }
        return len;
    }

};
