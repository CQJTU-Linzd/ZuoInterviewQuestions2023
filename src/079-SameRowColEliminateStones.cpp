// 79
// https://www.bilibili.com/video/BV1DT411s7hp?p=79&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SameRowColEliminateStones {
public:

    int maxRemoves(vector<vector<int>>& stones) {
        int n = stones.size();
        // 第100行，有一个石子，是第17个石子
        // key: 100, value: 17
        unordered_map<int, int>rowMap;
        unordered_map<int, int>colMap;
        UnionFind uf(n);
        for (int i = 0; i < n; i++) {
            int x = stones[i][0];
            int y = stones[i][1];
            if (!rowMap.count(x)) {
                rowMap[x] = i;
            } else {
                uf.unionSets(i, rowMap[x]);
            }
            if (!colMap.count(y)) {
                colMap[y] = i;
            } else {
                uf.unionSets(i, colMap[y]);
            }
        }
        return n - uf.sets;
    }

    class UnionFind {
        vector<int>father;
        vector<int>size;
        vector<int>help;
    public:
        int sets;

        UnionFind(int n) {
            father.resize(n);
            size.resize(n);
            help.resize(n);
            for (int i = 0; i < n; i++) {
                father[i] = i;
                size[i] = 1;
            }
            sets = n;
        }

        int findHead(int x) {
            int hi = 0;
            while (x != father[x]) {
                help[hi++] = x;
                x = father[x];
            }
            while (hi != 0) {
                father[help[--hi]] = x;
            }
            return x;
        }

        bool isSameSet(int a, int b) {
            return findHead(a) == findHead(b);
        }

        void unionSets(int a, int b) {
            int aF = findHead(a);
            int bF = findHead(b);
            if (aF != bF) {
                if (size[aF] >= size[bF]) {
                    father[bF] = aF;
                    size[aF] += size[bF];
                } else {
                    father[aF] = bF;
                    size[bF] += size[aF];
                }
                sets--;
            }
        }

    };

};
