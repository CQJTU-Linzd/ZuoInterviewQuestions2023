// 160
// https://www.bilibili.com/video/BV1DT411s7hp?p=160&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/minimum-window-substring/
class MinWindowLength {
public:

    // 暴力

    int minLength1(string s1, string s2) {
        if (s1.empty() || s2.empty() || s1.size() < s2.size()) {
            return 0;
        }
        int map[256] = { 0 };
        for (char ch : s2) {
            map[ch]++;
        }
        int ans = INT_MAX;
        for (int i = 0; i < s1.size(); i++) {
            for (int j = i; j < s1.size(); j++) {
                if (ok(s1, s2, i, j, map)) {
                    ans = min(ans, j - i + 1);
                }
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }

    bool ok(string s1, string s2, int start, int end, int* map) {
        int tmp[256] = { 0 };
        for (int i = start; i <= end; i++) {
            tmp[s1[i]]++;
        }
        for (char ch : s2) {
            if (tmp[ch] < map[ch]) {
                return false;
            }
        }
        return true;
    }

    // 正式

    int minLength2(string s1, string s2) {
        if (s1.empty() || s2.empty() || s1.size() < s2.size()) {
            return 0;
        }
        int map[256] = { 0 };
        for (char ch : s2) {
            map[ch]++;
        }
        int all = s2.size();
        int L = 0;
        int ans = INT_MAX;
        for (int R = 0; R < s1.size(); R++) {
            map[s1[R]]--;
            if (map[s1[R]] >= 0) {
                all--;
            }
            if (all == 0) {
                while (map[s1[L]] < 0) {
                    map[s1[L]]++;
                    L++;
                }
                ans = min(ans, R - L + 1);
                map[s1[L]]++;
                L++;
                all++;
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }


    // for test

    // 生成大小为size，只包含小写字母的字符串
    string randomLowerCaseString(int size) {
        srand(time(0));
        string s = "";
        for (int i = 0; i < size; i++) {
            char ch = 'a' + (rand() % (26));
            s.push_back(ch);
        }
        return s;
    }

    void test() {
        srand(time(0));
        for (int t = 0; t < 500; t++) {
            int size1 = rand() % (100 - 1 + 1) + 1;
            int size2 = rand() % (100 - 1 + 1) + 1;
            string s1 = randomLowerCaseString(size1);
            string s2 = randomLowerCaseString(size2);
            for (int r = 0; r < 10; r++) {
                random_shuffle(s1.begin(), s1.end());
                random_shuffle(s2.begin(), s2.end());

                int ans1 = minLength1(s1, s2);
                int ans2 = minLength2(s1, s2);

                if (ans1 != ans2) {
                    //cout << "fuck" << endl;
                    cout << s1 << " " << s2 << " " << ans1 << " " << ans2 << endl;
                }
            }
        }
    }

};
