// P15
// https://www.bilibili.com/video/BV1DT411s7hp?p=15&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ABCSameNumber {
public:

    int minTimes(vector<int>& arr) {
        int cnt[3] = { 0 };
        for (int num : arr) {
            cnt[num]++;
        }
        if (cnt[0] == cnt[1] && cnt[0] == cnt[2]) {
            return 0;
        }
        int n = arr.size();
        int m = n / 3;
        if ((cnt[0] < m && cnt[1] < m) || (cnt[0] < m && cnt[2] < m) || (cnt[2] < m && cnt[1] < m)) {
            return 2;
        } else { // 只有一种数是少于n/3的
            return once(arr, cnt, m) ? 1 : 2;
        }
    }

    // 只有一种数是少于n/3的
    bool once(vector<int>& arr, int cnt[], int m) {
        int lessNum = cnt[0] < m ? 0 : (cnt[1] < m ? 1 : 2);
        int lessCnt = lessNum == 0 ? cnt[0] : (lessNum == 1 ? cnt[1] : cnt[2]);
        if (cnt[0] > m && modify(arr, 0, cnt[0], lessNum, lessCnt)) {
            return true;
        }
        if (cnt[1] > m && modify(arr, 1, cnt[1], lessNum, lessCnt)) {
            return true;
        }
        if (cnt[2] > m && modify(arr, 2, cnt[2], lessNum, lessCnt)) {
            return true;
        }
        return false;
    }

    // 目标：0->10个，1->10个，2->10个
    // 此时：0：7个，1：12个，2：11个
    // more=1，less=0，other=2
    // 或者more=2，less=0，other=1
    bool modify(vector<int>& arr, int more, int moreT, int less, int lessT) {
        int cnt[3] = { 0 }; // cnt[i]：窗口外，i这个数字的出现次数
        cnt[more] = moreT;
        cnt[less] = lessT;

        int aim = arr.size() / 3;
        // [L,R)的窗口
        int L = 0;
        int R = 0;
        while (R < arr.size() || cnt[more] <= aim) {
            if (cnt[more] > aim) {
                cnt[arr[R]]--;
                R++;
            } else if (cnt[more] < aim) {
                cnt[arr[L]]++;
                L++;
            } else { // 窗口外，多的数，够了
                // 判断less和other，能不能平均都是10个
                if (cnt[less] + R - L < aim) {
                    cnt[arr[R]]--;
                    R++;
                } else if (cnt[less] + R - L > aim) {
                    cnt[arr[L]]++;
                    L++;
                } else {
                    return true;
                }
            }
        }
        return false;
    }
};
