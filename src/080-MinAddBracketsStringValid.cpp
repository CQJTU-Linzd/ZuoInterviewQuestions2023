// 80
// https://www.bilibili.com/video/BV1DT411s7hp?p=80&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinAddBracketsStringValid {
public:

    int minAdd(string str) {
        return process(str, 0, str.size() - 1);
    }

    int process(string str, int L, int R) {
        if (L == R) {
            return 1;
        }
        if (L == R - 1) {
            if (str[L] == '(' && str[R] == ')'
                || str[L] == '[' && str[R] == ']') {
                return 0;
            }
            return 2;
        }
        // str[L]和str[R]，自己能配对
        int p1 = INT_MAX;
        if (str[L] == '(' && str[R] == ')'
            || str[L] == '[' && str[R] == ']') {
            p1 = min(p1, process(str, L + 1, R - 1));
        } else { // str[L]和str[R]，不配对
            p1 = min({ p1,
                     process(str, L + 1, R) + 1,
                     process(str, L, R - 1) + 1 });
        }

        int p2 = INT_MAX;
        for (int i = L; i < R; i++) {
            p2 = min(p2, process(str, L, i) + process(str, i + 1, R));
        }

        return min(p1, p2);
    }

};
