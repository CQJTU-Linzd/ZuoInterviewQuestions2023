// 163
// https://www.bilibili.com/video/BV14P411Q7L6?p=2&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 测试链接 : https://leetcode.com/problems/24-game/
class _24Game {
public:

	class Number {
		int numerator;
		int denominator;
	public:
		Number(int num, int den = 1) : numerator(num), denominator(den) {}
		int nume() const {
			return numerator;
		}
		int deno() const {
			return denominator;
		}
		Number* operator+(const Number& num) {
			return simple(Number(this->numerator * num.denominator + this->denominator * num.numerator,
						  this->denominator * num.denominator));
		}
		Number* operator-(const Number& num) {
			return simple(Number(this->numerator * num.denominator - this->denominator * num.numerator,
						  this->denominator * num.denominator));
		}
		Number* operator*(const Number& num) {
			return simple(Number(this->numerator * num.numerator, this->denominator * num.denominator));
		}
		Number* operator/(const Number& num) {
			return num.numerator == 0 ? NULL : simple(Number(this->numerator * num.denominator,
													  this->denominator * num.numerator));
		}

		Number* simple(const Number& num) {
			if (num.numerator == 0) {
				return new Number(0, 1);
			}
			int g = abs(gcd(num.numerator, num.denominator));
			return new Number(num.numerator / g, num.denominator / g);
		}

		int gcd(int a, int b) {
			return b == 0 ? a : gcd(b, a % b);
		}
	};


	bool judgePoint24(vector<int>& cards) {
		vector<Number*>nums(4);
		for (int i = 0; i < 4; i++) {
			nums[i] = new Number(cards[i]);
		}
		return judge(nums, 4);
	}

	bool judge(vector<Number*>& nums, int size) {
		if (size == 1) {
			return nums[0]->nume() == 24 && nums[0]->deno() == 1;
		}
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				Number* inum = nums[i];
				Number* jnum = nums[j];
				nums[j] = nums[size - 1];

				nums[i] = (*inum) + (*jnum);
				if (judge(nums, size - 1)) {
					return true;
				}
				nums[i] = (*inum) - (*jnum);
				if (judge(nums, size - 1)) {
					return true;
				}
				nums[i] = (*jnum) - (*inum);
				if (judge(nums, size - 1)) {
					return true;
				}
				nums[i] = (*inum) * (*jnum);
				if (judge(nums, size - 1)) {
					return true;
				}
				nums[i] = (*inum) / (*jnum);
				if (nums[i] != NULL && judge(nums, size - 1)) {
					return true;
				}
				nums[i] = (*jnum) / (*inum);
				if (nums[i] != NULL && judge(nums, size - 1)) {
					return true;
				}

				nums[i] = inum;
				nums[j] = jnum;
			}
		}
		return false;
	}

};
