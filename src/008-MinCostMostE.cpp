// P8
// https://www.bilibili.com/video/BV1DT411s7hp?p=8&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自网易
// 小红拿到了一个仅由r、e、d组成的字符串
// 她定义一个字符e为"好e" : 当且仅当这个e字符和r、d相邻
// 例如"reeder"只有一个"好e"，前两个e都不是"好e"，只有第三个e是"好e"
// 小红每次可以将任意字符修改为任意字符，即三种字符可以相互修改
// 她希望"好e"的数量尽可能多
// 小红想知道，自己最少要修改多少次
// 输入一个只有r、e、d三种字符的字符串
// 长度 <= 2 * 10^5
// 输出最小修改次数
class MinCostMostE {
public:

	class Info {
	public:
		int mostGoodE;
		int minCost;
		Info(int goodE, int cost) {
			mostGoodE = goodE;
			minCost = cost;
		}
	};

	int minCost(string s) {
		if (s.size() < 3) {
			return 0;
		}
		int maxGoodE = 0;
		int minCost = INT_MAX;
		char chs[3] = { 'r', 'e', 'd' };
		for (int prepre = 0; prepre < 3; prepre++) { // s[0]
			for (int pre = 0; pre < 3; pre++) { // s[1]
				int curCost = 0;
				curCost += s[0] == chs[prepre] ? 0 : 1;
				curCost += s[1] == chs[pre] ? 0 : 1;

				Info curInfo = process(s, 2, chs[prepre], chs[pre]);
				if (curInfo.mostGoodE > maxGoodE) {
					maxGoodE = curInfo.mostGoodE;
					minCost = curInfo.minCost;
				} else if (curInfo.mostGoodE == maxGoodE) {
					minCost = min(minCost, curInfo.minCost + curCost);
				}

			}
		}
		return minCost;
	}

	// prepre: i-2位置的决定
	// pre: i-1位置的决定
	// 可以把i-1位置变成好e，也可以不变，去决策
	Info process(string s, int i, char prepre, char pre) {
		if (i == s.size()) {
			return Info(0, 0);
		}
		int mostGoodE = 0;
		int minCost = INT_MAX;
		// i位置变'r'
		int curValue1 = (prepre == 'd' && pre == 'e') ? 1 : 0;
		int curCost1 = s[i] == 'r' ? 0 : 1;
		Info info1 = process(s, i + 1, pre, 'r');
		int p1Value = curValue1 + info1.mostGoodE;
		int p1Cost = curCost1 + info1.minCost;
		// i位置变'e'
		int curValue2 = 0;
		int curCost2 = s[i] == 'e' ? 0 : 1;
		Info info2 = process(s, i + 1, pre, 'e');
		int p2Value = curValue2 + info2.mostGoodE;
		int p2Cost = curCost2 + info2.minCost;
		// i位置变'd'
		int curValue3 = (prepre == 'r' && pre == 'e') ? 1 : 0;
		int curCost3 = s[i] == 'd' ? 0 : 1;
		Info info3 = process(s, i + 1, pre, 'd');
		int p3Value = curValue3 + info3.mostGoodE;
		int p3Cost = curCost3 + info3.minCost;

		if (p1Value > mostGoodE) {
			mostGoodE = p1Value;
			minCost = p1Cost;
		} else if (p1Value == mostGoodE) {
			minCost = min(minCost, p1Cost);
		}
		if (p2Value > mostGoodE) {
			mostGoodE = p2Value;
			minCost = p2Cost;
		} else if (p2Value == mostGoodE) {
			minCost = min(minCost, p2Cost);
		}
		if (p3Value > mostGoodE) {
			mostGoodE = p3Value;
			minCost = p3Cost;
		} else if (p3Value == mostGoodE) {
			minCost = min(minCost, p3Cost);
		}
		return Info(mostGoodE, minCost);
	}

};
