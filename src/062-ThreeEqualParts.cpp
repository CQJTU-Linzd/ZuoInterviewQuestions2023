// 62
// https://www.bilibili.com/video/BV1DT411s7hp?p=62&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ThreeEqualParts {
public:

    vector<int> threeParts(vector<int>& arr) {
        int ones = 0;
        for (int num : arr) {
            if (num == 1) {
                ones++;
            }
        }
        if (ones % 3 != 0) {
            return vector<int>{-1, -1};
        }
        int n = arr.size();
        if (ones == 0) {
            return vector<int>{0, n - 1};
        }
        int start1 = -1;
        int start2 = -1;
        int start3 = -1;
        int part = ones / 3;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                cnt++;
                if (start1 == -1 && cnt == 1) {
                    start1 = i;
                }
                if (start2 == -1 && cnt == part + 1) {
                    start2 = i;
                }
                if (start3 == -1 && cnt == 2 * part + 1) {
                    start3 = i;
                }
            }
        }
        while (start3 < n) {
            if (arr[start1] == arr[start2] && arr[start1] == arr[start3]) {
                start1++;
                start2++;
                start3++;
            } else {
                return vector<int>{-1, -1};
            }
        }
        return vector<int>{start1 - 1, start2};
    }

};
