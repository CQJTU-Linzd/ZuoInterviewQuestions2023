// 164
// https://www.bilibili.com/video/BV14P411Q7L6/?p=3&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// https://leetcode-cn.com/problems/design-bitset/
class BitSet {
	vector<int>bits;
	const int size;
	int zeros;
	int ones;
	bool reverse;
public:

	BitSet(int n) : size(n), zeros(n), ones(0), reverse(false) {
		bits.resize((n + 31) / 32);
	}

	// 如果是0，就变1
	void fix(int idx) {
		int index = idx / 32;
		int bit = idx % 32;
		if (!reverse) {
			if ((bits[index] & (1 << bit)) == 0) {
				ones++;
				zeros--;
				bits[index] |= (1 << bit);
			}
		} else {
			if ((bits[index] & (1 << bit)) != 0) {
				ones++;
				zeros--;
				bits[index] ^= (1 << bit);
			}
		}
	}

	// 如果是1，就变0
	void unfix(int idx) {
		int index = idx / 32;
		int bit = idx % 32;
		if (!reverse) {
			if ((bits[index] & (1 << bit)) != 0) {
				ones--;
				zeros++;
				bits[index] ^= (1 << bit);
			}
		} else {
			if ((bits[index] & (1 << bit)) == 0) {
				ones--;
				zeros++;
				bits[index] |= (1 << bit);
			}
		}
	}

	void flip() {
		reverse = !reverse;
		swap(ones, zeros);
	}

	bool all() {
		return ones == size;
	}

	bool one() {
		return ones > 0;
	}

	int count() {
		return ones;
	}

	string toString() {
		string res = "";
		for (int i = 0; i < size; i++) {
			int status = bits[i / 32] & (1 << (i % 32));
			res.push_back(reverse ? (status == 0 ? '1' : '0') : (status == 0 ? '0' : '1'));
		}
		return res;
	}

};
