// P13
// https://www.bilibili.com/video/BV1DT411s7hp?p=13&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class MinSetForEveryRange {
public:

    class Event {
    public:
        int val;
        int end;
        bool isStart; // 若为false，则end没用
        Event(int s, int e, int is) {
            val = s;
            end = e;
            isStart = is;
        }
    };

    class Cmp {
    public:
        bool operator()(Event& a, Event& b) {
            return a.val < b.val;
        }
    };

    int minSetSize(vector<vector<int>>& ranges) {
        vector<Event>events;
        for (int i = 0; i < ranges.size(); i++) {
            // ranges[i][0]: 开始事件
            // ranges[i][1]: 结束事件
            events.push_back(Event(ranges[i][0], ranges[i][1], true));
            events.push_back(Event(ranges[i][1], 0, false));
        }
        sort(events.begin(), events.end(), Cmp());
        
        unordered_set<int>set;
        int ans = 0;
        for (Event& curEvent : events) {
            if (curEvent.isStart) {
                set.insert(curEvent.end);
            } else {
                if (set.count(curEvent.val)) {
                    ans++;
                    set.clear();
                }
            }
        }
        return ans;
    }

};
