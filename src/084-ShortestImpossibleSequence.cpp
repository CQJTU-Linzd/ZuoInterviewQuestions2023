// 84
// https://www.bilibili.com/video/BV1DT411s7hp?p=87&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给你一个长度为 n 的整数数组 rolls 和一个整数 k 。
// 你扔一个 k 面的骰子 n 次，骰子的每个面分别是 1 到 k ，
// 其中第 i 次扔得到的数字是 rolls[i] 。
// 请你返回 无法 从 rolls 中得到的 最短 骰子子序列的长度。
// 扔一个 k 面的骰子 len 次得到的是一个长度为 len 的 骰子子序列 。
// 注意 ，子序列只需要保持在原数组中的顺序，不需要连续。
// 测试链接 : https://leetcode.cn/problems/shortest-impossible-sequence-of-rolls/
class ShortestImpossibleSequence {
public:

    int shortestSequence(vector<int>& rolls, int k) {
        bool* set = new bool[k + 1];
        for (int i = 0; i <= k; i++) {
            set[i] = false;
        }
        int size = 0; // 当前这一套，收集到几个数字了
        int ans = 0; // 一共能收集几套
        for (int num : rolls) {
            if (!set[num]) {
                set[num] = true;
                size++;
            }
            if (size == k) {
                ans++;
                fill(set, set + k + 1, false);
                size = 0;
            }
        }
        delete[] set;
        return ans + 1;
    }

};
