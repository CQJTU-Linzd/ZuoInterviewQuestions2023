// 171
// https://www.bilibili.com/video/BV14P411Q7L6?p=15&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class SplitSameNumberWays {
public:

	int splitWays(string s) {
		if (s.empty()) {
			return 0;
		}
		int xAll = 0;
		int yAll = 0;
		for (char& ch : s) {
			if (ch == 'x') {
				xAll++;
			} else if (ch == 'y') {
				yAll++;
			}
		}
		int leftX = 0;
		int leftY = 0;
		int ans = 0;
		for (int i = 0; i < s.size() - 1; i++) {
			if (s[i] == 'x') {
				leftX++;
			} else if (s[i] == 'y') {
				leftY++;
			}
			int rightX = xAll - leftX;
			int rightY = yAll - leftY;
			if (leftX == leftY || rightX == rightY) {
				ans++;
			}
		}
		return ans;
	}

};
