// 32
// https://www.bilibili.com/video/BV1DT411s7hp?p=32&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinJumpPreNextAndSameValue {
public:

    int minJumps(vector<int>& arr) {
        unordered_map<int, vector<int>>valueIndex;
        for (int i = 0; i < arr.size(); i++) {
            valueIndex[arr[i]].push_back(i);
        }
        vector<bool>vis(arr.size(), false);
        queue<int>queue;
        
        queue.push(0);
        vis[0] = true;
        int jump = 0;
        while (!queue.empty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int cur = queue.front();
                queue.pop();
                if (cur == arr.size() - 1) {
                    return jump;
                }
                if (cur + 1 < arr.size() && !vis[cur + 1]) {
                    queue.push(cur + 1);
                    vis[cur + 1] = true;
                }
                if (cur > 0 && !vis[cur - 1]) {
                    queue.push(cur - 1);
                    vis[cur - 1] = true;
                }
                // 跳到值相同的位置
                for (int next : valueIndex[arr[cur]]) {
                    if (!vis[next]) {
                        queue.push(next);
                        vis[next] = true;
                    }
                }
                // 重要优化
                valueIndex.erase(arr[cur]);
            }
            jump++;
            
        }
        return jump;
    }

};
