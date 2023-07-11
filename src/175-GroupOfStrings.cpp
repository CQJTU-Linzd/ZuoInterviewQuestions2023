// 175
// https://www.bilibili.com/video/BV14P411Q7L6?p=20&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/groups-of-strings/
class GroupOfStrings {
public:

	// 比较暴力，没有优化
	vector<int> groupStrings(vector<string>& words) {
		int n = words.size();
		UnionFind uf(n);
		vector<int>strs(n);
		unordered_map<int, int>map;
		
		for (int i = 0; i < n; i++) {
			int status = 0;
			// abd -> 0...01011
			for (char& ch : words[i]) {
				status |= 1 << (ch - 'a');
			}
			strs[i] = status;
			if (map.count(status)) {
				uf.unionSets(i, map[status]);
			} else {
				map[status] = i;
			}
		}

		// 添一个字符、减一个字符、替换一个字符，挨个去试
		for (int i = 0; i < n; i++) {
			int status = strs[i];	
			for (int j = 0; j < 26; j++) {
				int addStatus = status | (1 << j);
				if (map.count(addStatus)) {
					uf.unionSets(i, map[addStatus]);
				}
			}
			for (int j = 0; j < 26; j++) {
				if ((status & (1 << j)) != 0) {
					int delStatus = status ^ (1 << j);
					if (map.count(delStatus)) {
						uf.unionSets(i, map[delStatus]);
					}
				}
			}
			for (int j = 0; j < 26; j++) {
				if ((status & (1 << j)) != 0) {
					status ^= 1 << j;
					for (int replace = 0; replace < 26; replace++) {
						int repStatus = status | (1 << replace);
						if (map.count(repStatus)) {
							uf.unionSets(i, map[repStatus]);
						}
					}
					status |= 1 << j;
				}
			}
		}
		return vector<int>{ uf.sets(), uf.maxSize() };
	}

	// 经过优化的
	vector<int> groupStrings2(vector<string>& words) {
		int n = words.size();
		UnionFind uf(n);
		vector<int>strs(n);
		unordered_map<int, int>map;

		for (int i = 0; i < n; i++) {
			int status = 0;
			// abd -> 0...01011
			for (char& ch : words[i]) {
				status |= 1 << (ch - 'a');
			}
			strs[i] = status;
			if (map.count(status)) {
				uf.unionSets(i, map[status]);
			} else {
				map[status] = i;
			}
		}

		for (int i = 0; i < n; i++) {
			int yes = strs[i];
			// 0... 00110011 -> 0... 11001100 (最后26位取反，最前面的保持0不变)
			int no = (~yes) & ((1 << 26) - 1);
			int tmpYes = yes;
			int tmpNo = no;
			int rightYesOne = 0;
			int rightNoOne = 0;

			// tmpYes: 0...0110011
			// rightYesOne: 0...0000001 -> 异或
			// tmpYes: 0...0110010
			// rightYesOne: 0...0000010 -> 异或
			while (tmpYes != 0) {
				rightYesOne = tmpYes & -tmpYes;
				int delStatus = yes ^ rightYesOne;
				if (map.count(delStatus)) {
					uf.unionSets(i, map[delStatus]);
				}
				tmpYes ^= rightYesOne;
			}

			// yes:   0... 00110011
			// tmpNo: 0... 11001100
			// rightNoOne: 0... 00000100
			// tmpNo: 0... 11001000
			// rightNoOne: 0... 00001000
			while (tmpNo != 0) {
				rightNoOne = tmpNo & -tmpNo;
				int addStatus = yes | rightNoOne;
				if (map.count(addStatus)) {
					uf.unionSets(i, map[addStatus]);
				}
				tmpNo ^= rightNoOne;
			}


			tmpYes = yes;
			// yes:    0... 00110011
			// tmpYes: 0... 00110011
			// tmpNo:  0... 11001100
			// rightYesOne: 0...00000001
			// rightNoOne: 0... 00000100
			while (tmpYes != 0) {
				rightYesOne = tmpYes & (-tmpYes);
				tmpNo = no;
				while (tmpNo != 0) {
					rightNoOne = tmpNo & -tmpNo;
					int repStatus = (yes ^ rightYesOne) | rightNoOne;
					if (map.count(repStatus)) {
						uf.unionSets(i, map[repStatus]);
					}
					tmpNo ^= rightNoOne;
				}
				tmpYes ^= rightYesOne;
			}
		}
		return vector<int>{ uf.sets(), uf.maxSize() };
	}

	class UnionFind {
		vector<int>father;
		vector<int>size;
		vector<int>help;
	public:
		UnionFind(int n) {
			father.resize(n);
			size.resize(n);
			help.resize(n);
			for (int i = 0; i < n; i++) {
				father[i] = i;
				size[i] = 1;
			}
		}
		int findHead(int x) {
			int index = 0;
			while (x != father[x]) {
				help[index++] = x;
				x = father[x];
			}
			index--;
			for (; index >= 0; index--) {
				father[help[index]] = x;
			}
			return x;
		}
		void unionSets(int a, int b) {
			int af = findHead(a);
			int bf = findHead(b);
			if (af != bf) {
				if (size[af] >= size[bf]) {
					size[af] += size[bf];
					father[bf] = af;
				} else {
					size[bf] += size[af];
					father[af] = bf;
				}
			}
		}
		int sets() {
			int ans = 0;
			for (int i = 0; i < father.size(); i++) {
				if (father[i] == i) {
					ans++;
				}
			}
			return ans;
		}
		int maxSize() {
			return *max_element(size.begin(), size.end());
		}
	};

};
