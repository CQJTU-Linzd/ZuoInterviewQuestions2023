// 162
// https://www.bilibili.com/video/BV1DT411s7hp?p=162&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinRange {
public:

    // 暴力

    // [3,6,7]
    // [5,10,13,16]
    // [2,3]
    int minRange1(vector<vector<int>>& matrix) {
        for (auto& arr : matrix) {
            if (arr.empty()) {
                return -1;
            }
        }
        this->ans = INT_MAX;
        int n = matrix.size();
        process(matrix, 0);
        return ans == INT_MAX ? -1 : ans;
    }

    int ans = INT_MAX;
    vector<int>path;

    void process(vector<vector<int>>& matrix, int i) {
        if (i == matrix.size()) {
            if (path.size() == matrix.size()) {
                int left = *min_element(path.begin(), path.end());
                int right = *max_element(path.begin(), path.end());
                //cout << left << " " << right << endl;
                ans = min(ans, right - left);
            }
            return;
        }
        for (int j = 0; j < matrix[i].size(); j++) {
            path.push_back(matrix[i][j]);
            process(matrix, i + 1);
            path.pop_back();
        }
    }


    // 正式

    class Node {
    public:
        int val;
        int arrIndex;
        int ownIndex;
        Node(int v, int a, int o) {
            val = v;
            arrIndex = a;
            ownIndex = o;
        }
    };

    class NodeCmp {
    public:
        bool operator()(const Node& a, const Node& b) const {
            return a.val != b.val ? (a.val < b.val) : (a.arrIndex < b.arrIndex);
        }
    };

    // [3,6,7]
    // [5,10,13,16]
    // [2,3]
    int minRange2(vector<vector<int>>& matrix) {
        for (auto& arr : matrix) {
            if (arr.empty()) {
                return -1;
            }
        }
        int n = matrix.size();
        set<Node, NodeCmp>set;
        for (int i = 0; i < n; i++) {
            set.insert(Node(matrix[i][0], i, 0));
        }
        int minInterval = INT_MAX;
        while (set.size() == n) {
            int left = set.begin()->val;
            int right = set.rbegin()->val;
            minInterval = min(minInterval, right - left);

            Node popNode = *set.begin();
            set.erase(set.begin());
            int arri = popNode.arrIndex;
            int owni = popNode.ownIndex;
            if (owni < matrix[arri].size() - 1) {
                set.insert(Node(matrix[arri][owni + 1], arri, owni + 1));
            }
        }
        return minInterval == INT_MAX ? -1 : minInterval;
    }


    // for test

    vector<vector<int>> randomMatrix(int size, int levelMaxSize, int l, int r) {
        srand(time(0));
        vector<vector<int>>res(size);
        for (int i = 0; i < size; i++) {
            int curLevelSize = rand() % (levelMaxSize - 0 + 1) + 0;
            res[i].resize(curLevelSize);
            for (int j = 0; j < curLevelSize; j++) {
                res[i][j] = rand() % (r - l + 1) + l;
            }
            sort(res[i].begin(), res[i].end());
        }
        return res;
    }


    void test() {
        srand(time(0));
        for (int t = 0; t < 5000; t++) {
            int size = rand() % (10 - 1 + 1) + 1;
            auto mat = randomMatrix(size, 10, 0, 100);

            int ans1 = minRange1(mat);
            int ans2 = minRange2(mat);

            if (ans1 != ans2) {
                cout << "fuck" << endl;
            }
        }
    }

};
