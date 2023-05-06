// 28
// https://www.bilibili.com/video/BV1DT411s7hp/?p=28&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class _RMQ {
public:

    class RMQ {
    public:

        // maxArr[i][j]: i下标开始，往后的 2^j 个数中，最大值是多少
        vector<vector<int>>maxArr;

        RMQ(vector<int>& arr) {
            int n = arr.size();
            int k = power2(n); // 2的k次方最接近n
            maxArr.resize(n + 1, vector<int>(k + 1));
            
            for (int i = 1; i <= n; i++) {
                maxArr[i][0] = arr[i - 1];
            }
            for (int j = 1; (1 << j) <= n; j++) {
                for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                    // maxArr[10][3], i=10, j=3
                    // 下标10开始，连续8个数，最大值是多少
                    // 1) maxArr[10][2]
                    // 2) maxArr[14][2]
                    maxArr[i][j] = max(
                        maxArr[i][j - 1],
                        maxArr[i + (1 << (j - 1))][j - 1]
                    );
                }
            }
        }

        int max(int l, int r) {
            int len = r - l + 1;
            int k = power2(len);// 2的k次方，可以容下len
            return max(
                maxArr[l][k],
                maxArr[r - (1 << k) + 1][k]
            );
        }

        int power2(int n) {
            // 2的ans次幂最接近n
            int ans = 0;
            while ((1 << ans) <= (n >> 1)) {
                ans++;
            }
            return ans;
        }

    };

};
