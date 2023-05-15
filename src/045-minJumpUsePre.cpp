// 45
// https://www.bilibili.com/video/BV1DT411s7hp/?p=45&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class minJumpUsePre {
public:

    class IndexTree;

    int minJump(vector<int>& arr) {
        queue<int>queue;
        IndexTree indexTree(arr.size());
        // indexTree初始化，每个位置填上1，代表该下标没访问过
        for (int i = 1; i <= arr.size(); i++) {
            indexTree.add(i, 1);
        }
        int step = 0;
        queue.push(0);
        while (!queue.empty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int cur = queue.front();
                queue.pop();
                int forward = cur + arr[cur];
                if (forward >= arr.size()) {
                    return step + 1;
                }
                if (indexTree.value(forward) == 1) {
                    queue.push(forward);
                    indexTree.add(forward, -1);
                }
                while (indexTree.sum(cur - 1) != 0) {
                    int mostLeftUnVisited = find(indexTree, cur - 1);
                    queue.push(mostLeftUnVisited);
                    indexTree.add(mostLeftUnVisited, -1);
                }
            }
            step++;
        }
        return step;
    }


    int find(IndexTree indexTree, int right) {
        int l = 1;
        int r = right;
        int ans = 0;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (indexTree.sum(m) != 0) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }

    class IndexTree {
        int N;
        vector<int>tree;
    public:

        IndexTree(int size) {
            N = size;
            tree.resize(N + 1);
        }

        int value(int index) {
            if (index == 0) {
                return sum(0);
            } else {
                return sum(index) - sum(index - 1);
            }
        }

        int sum(int index) {
            int ans = 0;
            while (index > 0) {
                ans += tree[index];
                index -= index & -index;
            }
            return ans;
        }

        void add(int index, int d) {
            while (index <= N) {
                tree[index] += d;
                index += index & -index;
            }
        }

    };

};
