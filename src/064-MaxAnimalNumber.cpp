// 64
// https://www.bilibili.com/video/BV1DT411s7hp?p=64&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxAnimalNumber {
public:

    int maxNumber(vector<int>& arr) {
        vector<int>ends(arr.size());
        int right = 0;
        ends[0] = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            int l = 0;
            int r = right;
            int ans = 0;
            while (l <= r) {
                int m = (l + r) >> 1;
                if (ends[m] <= arr[i]) {
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            if (ans == right) { // 可以扩充有效区
                right++;
                ends[right] = ends[right - 1] + arr[i];
            } else {
                if (ends[ans] + arr[i] < ends[right]) {
                    ends[ans] = ends[ans] + arr[i];
                }
            }
        }
        return right + 1;
    }

};
