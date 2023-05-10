// 34 
// https://www.bilibili.com/video/BV1DT411s7hp?p=34&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class FindDuplicateOnlyOne {
public:

    // 1,2,3...n,n,n+1,n+2...
    // 一个有序序列里，只有一个数字有重复（n）
    // 如果传入的序列有序，找到重复数字n
    // 如果传入的序列无序，找到重复数字n

    // 无序
    int findDuplicateUnSorted(vector<int>& arr) {
        // 快慢指针找环问题
        int slow = arr[0];
        int fast = arr[arr[0]];
        while (slow != fast) {
            slow = arr[slow];
            fast = arr[arr[fast]];
        }
        // slow == fast
        fast = 0;
        while (slow != fast) {
            slow = arr[slow];
            fast = arr[fast];
        }
        // 第二次相遇，就是环的入口
        return slow;
    }

    int findDuplicateSorted(vector<int>& arr) {
        // 二分
        int l = 0;
        int r = arr.size() - 1;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            int preLen = m + 1;
            if (arr[m] == preLen) {
                l = m + 1;
            } else if (arr[m] < preLen) {
                r = m - 1;
            }
        }
        return l;
    }

};
