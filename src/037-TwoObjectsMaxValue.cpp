// 37
// https://www.bilibili.com/video/BV1DT411s7hp?p=37&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class TwoObjectsMaxValue {
public:

    int maxValue(vector<int>& w, vector<int>& v, int bag) {
        int n = w.size();
        vector<vector<int>>arr(n, vector<int>(2));
        for (int i = 0; i < n; i++) {
            arr[i][0] = w[i];
            arr[i][1] = v[i];
        }
        // 按重量从轻到重排序
        sort(arr.begin(), arr.end(), [](vector<int>& a, vector<int>& b)->int {
            return a[0] < b[0];
        });

        // 重量从轻到重，依次编号1，2，3，4...，作为RMQ中的下标
        // 价值依次被构建成RMQ
        RMQ rmq(arr);

        int ans = 0;
        for (int i = 0, j = 1; i < n && arr[i][0] <= bag; i++, j++) {
            // 当前来到i号货物，RMQ结构i+1号
            // 查询重量的边界，重量 边界 <= bag - 当前货物的重量
            // getRight(arr, bag - arr[i][0]): 货物数组中，找到 <= 边界，最右的位置x
            // RMQ中的位置： x + 1
            int right = getRight(arr, bag - arr[i][0]) + 1;
            int rest = 0; // 另一件货物的最大价值
            // j == i + 1，当前货物在RMQ里的下标
            if (right == j) {
                rest = rmq.getMax(1, right - 1);
            } else if (right < j) {
                rest = rmq.getMax(1, right);
            } else {
                rest = max(
                    rmq.getMax(1, j - 1),
                    rmq.getMax(j + 1, right)
                );
            }
            ans = max(ans, arr[i][1] + rest);
        }
        return ans;
    }

    // <=limit的最右位置
    int getRight(vector<vector<int>>& arr, int limit) {
        int l = 0;
        int r = arr.size() - 1;
        int ans = -1;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            if (arr[m][0] <= limit) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    }


    class RMQ {
        vector<vector<int>>maxArr;
    public:

        RMQ(vector<vector<int>>& arr) {
            int n = arr.size();
            int k = power2(n);
            maxArr.resize(n + 1, vector<int>(k + 1));
            for (int i = 1; i <= n; i++) {
                maxArr[i][0] = arr[i - 1][1];
            }
            for (int j = 1; (1 << j) <= n; j++) {
                for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                    maxArr[i][j] = max(
                        maxArr[i][j - 1],
                        maxArr[i + (1 << (j - 1))][j - 1]
                    );
                }
            }
        }

        int getMax(int l, int r) {
            if (l > r) {
                return 0;
            }
            int k = power2(r - l + 1);
            return max(
                maxArr[l][k],
                maxArr[r - (1 << k) + 1][k]
            );
        }

        int power2(int m) {
            int ans = 0;
            while ((1 << ans) <= (m >> 1)) {
                ans++;
            }
            return ans;
        }

    };

};
