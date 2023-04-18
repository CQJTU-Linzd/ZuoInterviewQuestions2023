// P16
// https://www.bilibili.com/video/BV1DT411s7hp?p=16&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class WaysWiggle {
public:

    int ways(vector<int>& arr) {
        int n = arr.size();
        vector<bool>leftUpDown(n);
        vector<bool>leftDownUp(n);
        vector<bool>rightUpDown(n);
        vector<bool>rightDownUp(n);

        // 生成预处理信息
        leftDownUp[0] = true;
        leftUpDown[0] = true;
        for (int i = 1; i < arr.size(); i++) {
            leftUpDown[i] = arr[i] < arr[i - 1] && leftDownUp[i - 1];
            leftDownUp[i] = arr[i] > arr[i - 1] && leftUpDown[i - 1];
        }

        rightDownUp[n - 1] = true;
        rightUpDown[n - 1] = true;
        for (int i = n - 2; i >= 0; i--) {
            rightUpDown[i] = arr[i] < arr[i + 1] && rightDownUp[i + 1];
            rightDownUp[i] = arr[i] > arr[i + 1] && rightUpDown[i + 1];
        }

        // 数组是不是天然符合
        if (rightDownUp[0] || rightUpDown[0]) {
            return 0;
        }

        // i == 0 删除
        int ans = rightDownUp[1] || rightUpDown[1] ? 1 : 0;
        // i == n - 1 删除
        ans += leftDownUp[n - 2] || leftUpDown[n - 2] ? 1 : 0;
        for (int i = 1; i < n - 1; i++) {
            int left = arr[i - 1];
            int right = arr[i + 1];
            if (left == right) {
                continue;
            }
            if (left > right) {
                if (rightUpDown[i + 1] && leftDownUp[i - 1]) {
                    ans++;
                }
            } else {
                if (rightDownUp[i + 1] && leftUpDown[i - 1]) {
                    ans++;
                }
            }
        }
        return ans == 0 ? -1 : ans;
    }
};
