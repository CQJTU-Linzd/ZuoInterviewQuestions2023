// 177
// https://www.bilibili.com/video/BV14P411Q7L6?p=37&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 小歪每次会给你两个字符串：
// 笔记s1和关键词s2，请你写一个函数
// 判断s2的排列之一是否是s1的子串
// 如果是，返回true
// 否则，返回false
class StringCheck {
public:

	// 自己的

	bool stringCheck(string s1, string s2) {
		if (s1.size() < s2.size()) {
			return false;
		}
		int map[256] = { 0 };
		int all = 0;
		for (char& ch : s2) {
			map[ch]++;
			all++;
		}
		int n1 = s1.size();
		int n2 = s2.size();
		int l = 0;
		for (int r = 0; r < n1; r++) {
			if (--map[s1[r]] >= 0) {
				all--;
			}
			if (r - l + 1 == n2) {
				if (all == 0) {
					return true;
				}
				// l移动
				if (++map[s1[l]] > 0) {
					all++;
				}
				l++;
			}
		}
		return false;
	}

	// 左神

	bool stringCheck2(string s1, string s2) {
		if (s1.size() < s2.size()) {
			return false;
		}
		int map[256] = { 0 };
		for (char ch : s2) {
			map[ch]++;
		}
		int m = s2.size();
		int inValidTimes = 0;
		int r = 0;
		for (; r < m; r++) {
			if (map[s1[r]]-- <= 0) {
				inValidTimes++;
			}
		}
		for (; r < s1.size(); r++) {
			if (inValidTimes == 0) {
				return true;
			}
			if (map[s1[r]]-- <= 0) {
				inValidTimes++;
			}
			if (map[s1[r - m]]++ < 0) {
				inValidTimes--;
			}
		}
		return inValidTimes == 0;
	}

	// for test

	// 生成大小为size，只包含小写字母的字符串
	string randomLowerCaseString(int size) {
		string s = "";
		for (int i = 0; i < size; i++) {
			char ch = 'a' + (rand() % (26));
			s.push_back(ch);
		}
		return s;
	}

	void test() {
		srand(time(0));
		for (int t = 0; t < 500000; t++) {
			int size1 = rand() % (20 - 1 + 1) + 1;
			int size2 = rand() % (20 - 1 + 1) + 1;
			string s1 = randomLowerCaseString(size1);
			string s2 = randomLowerCaseString(size2);
			//cout << s1 << " " << s2 << endl;
			bool ans1 = stringCheck(s1, s2) ? 1 : 0;
			bool ans2 = stringCheck2(s1, s2) ? 1 : 0;
			// cout << ans1 << endl;
			if (ans1 != ans2) {
				cout << "fuck" << endl;
			}
		}
	}


};
