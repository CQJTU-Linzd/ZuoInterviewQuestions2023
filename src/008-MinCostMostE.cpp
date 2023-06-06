// P8
// https://www.bilibili.com/video/BV1DT411s7hp?p=8&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
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

	// prepre: i-2位置的决定
	// pre: i-1位置的决定
	// 可以把i-1位置变成好e，也可以不变，去决策
	Info process(string s, int i, char prepre, char pre) {
		if (i == s.size()) {
			return Info(0, 0);
		}


		// p1：i位置变成'r'
		int cur1Value = s[prepre] == 'd' && s[pre] == 'e' ? 1 : 0;
		int cur1Cost = s[i] == 'r' ? 0 : 1;
		Info info1 = process(s, i + 1, pre, 'r');
		int p1Value = cur1Value + info1.mostGoodE;
		int p1Cost = cur1Cost + info1.minCost;

		// p2：i位置变成'e'
		int cur2Value = 0;
		int cur2Cost = s[i] == 'e' ? 0 : 1;
		Info info2 = process(s, i + 1, pre, 'e');
		int p2Value = cur2Value + info2.mostGoodE;
		int p2Cost = cur2Cost + info2.minCost;

		// p3：i位置变成'd'
		int cur3Value = s[prepre] == 'r' && s[pre] == 'e' ? 1 : 0;
		int cur3Cost = s[i] == 'd' ? 0 : 1;
		Info info3 = process(s, i + 1, pre, 'd');
		int p3Value = cur3Value + info3.mostGoodE;
		int p3Cost = cur3Cost + info3.minCost;

		int mostE = 0;
		int minCost = INT_MAX;

		if (mostE < p1Value) {
			mostE = p1Value;
			minCost = p1Cost;
		} else if (mostE == p1Value) {
			minCost = min(minCost, p1Cost);
		}

		if (mostE < p2Value) {
			mostE = p2Value;
			minCost = p2Cost;
		} else if (mostE == p2Value) {
			minCost = min(minCost, p2Cost);
		}

		if (mostE < p3Value) {
			mostE = p3Value;
			minCost = p3Cost;
		} else if (mostE == p3Value) {
			minCost = min(minCost, p3Cost);
		}

		return Info(mostE, minCost);
	}

};
