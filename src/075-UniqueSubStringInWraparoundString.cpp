// 75
// https://www.bilibili.com/video/BV1DT411s7hp?p=75&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class UniqueSubStringInWraparoundString {
public:

    int findSubString(string s) {
        int n = s.size();
        int len = 1; // 前一个字符最长能长到的长度
        int maxLen[256] = { 0 };
        maxLen[s[0]]++;
        for (int i = 1; i < n; i++) {
            char cur = s[i];
            char pre = s[i - 1];
            if ((cur == 'a' && pre == 'z') || (cur == pre + 1)) {
                len++;
            } else {
                len = 1;
            }
            maxLen[cur] = max(maxLen[cur], len);
        }
        int ans = 0;
        for (int i = 0; i < 256; i++) {
            ans += maxLen[i];
        }
        return ans;
    }

};
