// 132
// https://www.bilibili.com/video/BV1DT411s7hp?p=132&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class LongestSubStringWithoutRepeating {
public:

    // 暴力解
    int longestSubStr(string s) {
        int ans = 1;
        for (int i = 0; i < s.size(); i++) {
            for (int j = i + 1; j < s.size(); j++) {
                string sub = s.substr(i, j - i + 1);
                if (ok(sub)) {
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }

    bool ok(string s) {
        unordered_set<char>st;
        for (char ch : s) {
            if (st.count(ch)) {
                return false;
            }
            st.insert(ch);
        }
        return true;
    }


    // 法一 dp

    int longest(string s) {
        if (s.empty()) {
            return 0;
        }
        int map[256];
        for (int i = 0; i < 256; i++) {
            map[i] = -1;
        }
        int ans = 1;
        int dp = 1;
        map[s[0]] = 0;
        for (int i = 1; i < s.size(); i++) {
            int p1 = i - map[s[i]];
            int p2 = dp + 1;
            int cur = min(p1, p2);
            ans = max(ans, cur);
            dp = cur;
            map[s[i]] = i;
        }
        return ans;
    }


    // 法二
    int longest2(string s) {
        int st[256] = { 0 };
        int ans = 1;
        int l = 0;
        int r = 0;
        for (; r < s.size(); r++) {
            if (!st[s[r]]) {
                st[s[r]]++;
            } else {
                ans = max(ans, r - l);
                while (st[s[r]]) {
                    st[s[l]]--;
                    l++;
                }
                st[s[r]]++;
            }
        }
        ans = max(ans, r - l);
        return ans;
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
        for (int t = 0; t < 2000; t++) {
            int size = rand() % (100 - 1 + 1) + 1;
            string s = randomLowerCaseString(size);
            int ans1 = longestSubStr(s);
            int ans2 = longest2(s);
            if (ans1 != ans2) {
                cout << s << " " << ans1 << " " << ans2 << endl;
                //cout << "fuck" << endl;
            }
        }
    }

};
