// 74
// https://www.bilibili.com/video/BV1DT411s7hp?p=74&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class GoodENumbers {
public:

    class Info {
    public:

        int value;
        int cost;
        Info(int v, int c) {
            value = v;
            cost = c;
        }

    };

    //                                           i-1        i-2
    static Info process(string& str, int i, char pre, char prepre) {
        if (i == str.size()) {
            return Info(0, 0);
        }
        // [i]->'r'
        int curCost1 = str[i] == 'r' ? 0 : 1;
        int curValue1 = prepre == 'd' && pre == 'e' ? 1 : 0;
        Info info1 = process(str, i + 1, 'r', pre);

        // [i]->'e'
        int curCost2 = str[i] == 'e' ? 0 : 1;
        int curValue2 = 0;
        Info info2 = process(str, i + 1, 'e', pre);

        // [i]->'d'
        int curCost3 = str[i] == 'd' ? 0 : 1;
        int curValue3 = prepre == 'r' && pre == 'e' ? 1 : 0;
        Info info3 = process(str, i + 1, 'd', 'pre');

        int p1Value = curValue1 + info1.value;
        int p1Cost = curCost1 + info1.cost;
        int p2Value = curValue2 + info2.value;
        int p2Cost = curCost2 + info2.cost;
        int p3Value = curValue3 + info3.value;
        int p3Cost = curCost3 + info3.cost;

        int maxValue = 0;
        int minCost = INT_MAX;
        if (maxValue < p1Value) {
            maxValue = p1Value;
            minCost = p1Cost;
        } else if (maxValue == p1Value) {
            minCost = min(minCost, p1Cost);
        }
        if (maxValue < p2Value) {
            maxValue = p2Value;
            minCost = p2Cost;
        } else if (maxValue == p2Value) {
            minCost = min(minCost, p2Cost);
        }
        if (maxValue < p3Value) {
            maxValue = p3Value;
            minCost = p3Cost;
        } else if (maxValue == p3Value) {
            minCost = min(minCost, p3Cost);
        }
        return Info(maxValue, minCost);
    }

};
