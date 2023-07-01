// 172
// https://www.bilibili.com/video/BV14P411Q7L6?p=16&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 给定一个正数num，要返回一个大于num的数，并且每一位和相邻位的数字不能相等
// 返回达标的数字中，最小的那个
// 10^9
class NearBiggerNoSameNeighbour {
public:

	int near(int num) {
		string raw = "0" + to_string(num + 1);
		process(raw);
		return atoi(raw.c_str());
	}

	void process(string& raw) {
		for (int i = 1; i < raw.size(); i++) {
			if (raw[i] == raw[i - 1]) {
				addOne(raw, i);
				for (int j = i + 1; j < raw.size(); j++) {
					raw[j] = '0';
				}
				process(raw);
				return;
			}
		}
	}

	void addOne(string& raw, int index) {
		while (raw[index] == '9') {
			raw[index--] = '0';
		}
		raw[index]++;
	}

};
