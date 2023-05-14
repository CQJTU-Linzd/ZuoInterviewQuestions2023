// 43
// https://www.bilibili.com/video/BV1DT411s7hp?p=43&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class RemoveNumbersIncreasingLessK {
public:

    int minRemoves(vector<int>& arr, int k) {
        return process(arr, k, 0, 0);
    }

    int process(vector<int>& arr, int k, int i, int len) {
        // 长度已经凑到k了
        if (len == k) {
            return INT_MAX;
        }
        // 长度还没凑到k，但已到结尾
        if (i == arr.size()) {
            return 0;
        }
        // 长度没到k，还有数
        int cur = arr[i];
        // p1：保留
        // 1..3 3
        if (len >= cur) {
            return process(arr, k, i + 1, len);
        }
        // 1..3 5
        if (len + 1 < cur) {
            return process(arr, k, i + 1, len);
        }
        // len + 1 == cur
        int p1 = process(arr, k, i + 1, len + 1);
        int p2 = INT_MAX;
        int next2 = process(arr, k, i + 1, len);
        if (next2 != INT_MAX) {
            p2 = 1 + next2;
        }
        return min(p1, p2);
    }

};
