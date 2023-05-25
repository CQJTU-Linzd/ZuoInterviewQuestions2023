// 88
// https://www.bilibili.com/video/BV1DT411s7hp?p=88&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class DistinctSubSeqValue {
public:

    int distinctSubSeq(string s) {
        int count[26] = { 0 };
        int all = 1;
        for (char ch : s) {
            int newAdd = all - count[ch - 'a'];
            all += newAdd;
            count[ch - 'a'] += newAdd;
        }
        return all - 1;
    }

};
