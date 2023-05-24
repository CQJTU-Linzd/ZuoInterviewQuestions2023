// 81
// https://www.bilibili.com/video/BV1DT411s7hp?p=81&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class EatFish {
public:

    int minTurns(vector<int>& arr) {
        int n = arr.size();
        stack<pair<int, int>>stack;
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int curTurn = 0; // 轮数
            while (!stack.empty() && arr[i] > stack.top().first) {
                curTurn = max(curTurn + 1, stack.top().second);
                stack.pop();
            }
            stack.push(make_pair(arr[i], curTurn));
            ans = max(ans, curTurn);
        }
        return ans;
    }

};
