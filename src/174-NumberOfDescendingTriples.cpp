// 174
// https://www.bilibili.com/video/BV14P411Q7L6?p=18&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class NumberOfDescendingTriples {
public:

	int num(vector<int>& arr) {
		if (arr.size() < 3) {
			return 0;
		}
		int n = arr.size();
		vector<int>sorted = arr;
		sort(sorted.begin(), sorted.end());
		int rank = 1;
		unordered_map<int, int>map;
		for (int num : arr) {
			if (!map.count(num)) {
				map[num] = rank++;
			}
		}
		for (int i = 0; i < n; i++) {
			sorted[i] = map[sorted[i]];
		}

		IndexTree it2(rank - 1);
		IndexTree it3(rank - 1);

		int ans = 0;
		for (int i = n - 1; i >= 0; i--) {
			ans += sorted[i] == 1 ? 0 : (it3.sum(sorted[i] - 1));
			it2.add(sorted[i], 1);
			it3.add(sorted[i], sorted[i] == 1 ? 0 : (it2.sum(sorted[i] - 1)));
		}
		return ans;
	}

	class IndexTree {
		int n;
		vector<int>tree;
	public:
		IndexTree(int size) {
			n = size;
			tree.resize(n + 1);
		}

		int sum(int index) {
			int ans = 0;
			while (index > 0) {
				ans += tree[index];
				index -= index & -index;
			}
			return ans;
		}

		void add(int index, int c) {
			while (index <= n) {
				tree[index] += c;
				index += index & -index;
			}
		}
	};


};
