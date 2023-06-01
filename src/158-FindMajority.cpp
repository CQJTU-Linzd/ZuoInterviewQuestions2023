// 158
// https://www.bilibili.com/video/BV1DT411s7hp/?p=158&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class FindMajority {
public:

    // 超级水王问题
    // 在数组中找到出现次数大于N/2的数字

    int findMajority(vector<int>& arr) {
        int cand = 0;
        int hp = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (hp == 0) {
                cand = arr[i];
                hp = 1;
            } else if (arr[i] == cand) {
                hp++;
            } else {
                hp--;
            }
        }
        if (hp == 0) {
            return INT_MAX;
        }
        hp = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == cand) {
                hp++;
            }
        }
        return hp > arr.size() / 2 ? cand : INT_MAX;
    }


    // 进阶
    // 在数组中找到出现次数大于N/K的数字

    vector<int> findKMajority(vector<int>& arr, int k) {
        if (k < 2) {
            return vector<int>{};
        }
        // cands 候选表 最多有K-1条记录 因为最多只会有K-1个数，出现次数 > N/K
        unordered_map<int, int>cands;
        for (int i = 0; i != arr.size(); i++) {
            if (cands.count(arr[i])) {
                cands[arr[i]]++;
            } else { // 当前数不是候选
                if (cands.size() == k - 1) { // 当前数肯定不要，每一个候选付出1点血量，血量变成0的候选，要删掉！
                    allCandsMinusOne(cands);
                } else {
                    cands[arr[i]] = 1;
                }
            }
        }

        // 所有可能的候选，都在cands表中！遍历一遍arr，每个候选收集真实次数
        
        vector<int>res;
        auto reals = getReals(arr, cands);
        for (auto& it : cands) {
            int cand = it.first;
            if (reals[cand] > arr.size() / k) {
                res.push_back(cand);
            }
        }
        return res;
    }

    void allCandsMinusOne(unordered_map<int, int>& cands) {
        list<int>removeList;
        for (auto& it : cands) {
            if (--it.second == 0) {
                removeList.push_back(it.first);
            }
        }
        for (auto it = removeList.begin(); it != removeList.end(); it++) {
            cands.erase(*it);
        }
    }

    unordered_map<int, int> getReals(vector<int>& arr, unordered_map<int, int>& cands) {
        unordered_map<int, int>reals;
        for (int num : arr) {
            if (cands.count(num)) {
                reals[num]++;
            }
        }
        return reals;
    }


    // 法二

    vector<int> findKMajority2(vector<int>& arr, int k) {
        if (k < 2) {
            return vector<int>{};
        }
        unordered_map<int, int>cnts;
        for (int num : arr) {
            cnts[num]++;
        }
        vector<int>res;
        for (auto& it : cnts) {
            if (it.second > arr.size() / k) {
                res.push_back(it.first);
            }
        }
        return res;
    }


    // for test

    // 生成大小为size，数据范围在l~r的随机数组
    vector<int> randomArray(int size, int l, int r) {
        srand(time(0));
        vector<int>nums;
        for (int i = 0; i < size; i++) {
            nums.push_back(rand() % (r - l + 1) + l);
        }
        return nums;
    }


    void test() {
        srand(time(0));
        for (int t = 0; t < 500; t++) {
            int size = rand() % (1000 - 1 + 1) + 1;
            vector<int>arr = randomArray(size, 0, 1000);
            for (int r = 0; r < 10; r++) {
                random_shuffle(arr.begin(), arr.end());
                int k = rand() % (100 - 1 + 1) + 1;
                auto ans1 = findKMajority(arr, k);
                auto ans2 = findKMajority2(arr, k);
                sort(ans1.begin(), ans1.end());
                sort(ans2.begin(), ans2.end());
                if (ans1 != ans2) {
                    cout << "fuck" << endl;
                }
            }
        }
    }

};
