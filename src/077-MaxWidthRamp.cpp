// 77 
// https://www.bilibili.com/video/BV1DT411s7hp?p=77&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MaxWidthRamp {
public:

    int maxWidth(vector<int>& arr) {
        if (arr.empty()) {
            return 0;
        }
        stack<int>stack;
        for (int i = 0; i < arr.size(); i++) {
            if (stack.empty() || arr[i] < arr[stack.top()]) {
                stack.push(i);
            }
        }
        int ans = 0;
        for (int i = arr.size() - 1; i >= 0; i--) {
            while (!stack.empty() && arr[stack.top()] <= arr[i]) {
                ans = max(ans, i - stack.top());
                stack.pop();
            }
        }
        return ans;
    }

};
