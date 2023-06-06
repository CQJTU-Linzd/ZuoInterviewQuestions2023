// P4
// https://www.bilibili.com/video/BV1DT411s7hp?p=4&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ChangeToSame {
public:

    int minCost(vector<int>& A, vector<int>& B) {
        return process(A, B, 0, 0);
    }

    int process(vector<int>& A, vector<int>& B, int ai, int bi) {
        if (ai == A.size() && bi == B.size()) {
            return 0;
        }

        if (ai == A.size() && bi != B.size()) {
            return B[bi] + process(A, B, ai, bi + 1);
        }
        if (ai != A.size() && bi == B.size()) {
            return A[ai] + process(A, B, ai + 1, bi);
        }

        // A还有数，B还有数

        if (A[ai] == B[bi]) {
            return process(A, B, ai + 1, bi + 1);
        }

        // 可能性1：修改
        int p1 = abs(A[ai] - B[bi]) + process(A, B, ai + 1, bi + 1);
        // 可能性2：删除
        int p2A = A[ai] + process(A, B, ai + 1, bi);
        int p2B = B[bi] + process(A, B, ai, bi + 1);
        return min({ p1, p2A, p2B });
    }

    // dp

    int minCost2(vector<int>& A, vector<int>& B) {
        int n = A.size();
        int m = B.size();
        int** dp = new int* [n + 1];
        for (int i = 0; i < n + 1; i++) {
            dp[i] = new int[m + 1];
        }
        for (int i = 0; i < n + 1; i++) {
            for (int j = 0; j < m + 1; j++) {
                dp[i][j] = 0;
            }
        }
        for (int bi = m - 1; bi >= 0; bi--) {
            dp[n][bi] = B[bi] + dp[n][bi + 1];
        }
        for (int ai = n - 1; ai >= 0; ai--) {
            dp[ai][m] = A[ai] + dp[ai + 1][m];
        }

        for (int ai = n - 1; ai >= 0; ai--) {
            for (int bi = m - 1; bi >= 0; bi--) {
                if (A[ai] == B[bi]) {
                    dp[ai][bi] = dp[ai + 1][bi + 1];
                } else {
                    int p1 = abs(A[ai] - B[bi]) + dp[ai + 1][bi + 1];
                    int p2A = A[ai] + dp[ai + 1][bi];
                    int p2B = B[bi] + dp[ai][bi + 1];
                    dp[ai][bi] = min({ p1, p2A, p2B });
                }
            }
        }
        int ans = dp[0][0];
        for (int i = 0; i < n + 1; i++) {
            delete[] dp[i];
        }
        delete[] dp;
        return ans;
    }

    // for test
    
    // 生成大小为size，数据范围在l~r的随机数组
    vector<int> randomArray(int size, int l, int r) {
        vector<int>nums;
        for (int i = 0; i < size; i++) {
            nums.push_back(rand() % (r - l + 1) + l);
        }
        return nums;
    }


    void test() {
        srand(time(0));
        for (int t = 0; t < 50; t++) {
            int size1 = rand() % (10 - 1 + 1) + 1;
            int size2 = rand() % (10 - 1 + 1) + 1;

            auto A = randomArray(size1, 0, 1000);
            auto B = randomArray(size2, 0, 1000);

            for (int r = 0; r < 5; r++) {
                random_shuffle(A.begin(), A.end());
                random_shuffle(B.begin(), B.end());
                int ans1 = minCost(A, B);
                int ans2 = minCost2(A, B);

                if (ans1 != ans2) {
                    cout << "fuck" << endl;
                }
            }

        }
    }

};
