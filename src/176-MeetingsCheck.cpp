// 176
// https://www.bilibili.com/video/BV14P411Q7L6?p=36&spm_id_from=pageDriver&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 来自字节飞书团队
// 在字节跳动，大家都使用飞书的日历功能进行会议室的预订，遇到会议高峰时期，
// 会议室就可能不够用，现在请你实现一个算法，判断预订会议时是否有空的会议室可用。
// 为简化问题，这里忽略会议室的大小，认为所有的会议室都是等价的，
// 只要空闲就可以容纳任意的会议，并且：
// 1. 所有的会议预订都是当日预订当日的时段
// 2. 会议时段是一个左闭右开的时间区间，精确到分钟
// 3. 每个会议室刚开始都是空闲状态，同一时间一个会议室只能进行一场会议
// 4. 会议一旦预订成功就会按时进行
// 比如上午11点到中午12点的会议即[660, 720)
// 给定一个会议室总数m
// 一个预定事件由[a,b,c]代表 : 
// a代表预定动作的发生时间，早来早得; b代表会议的召开时间; c代表会议的结束时间
// 给定一个n*3的二维数组，即可表示所有预定事件
// 返回一个长度为n的boolean类型的数组，表示每一个预定时间是否成功
class MeetingsCheck {
public:

	class Info {
	public:
		int origIndex;
		int time;
		int start;
		int end;
		Info(int o, int t, int s, int e)
			: origIndex(o), time(t), start(s), end(e) {
		}
	};

	vector<bool> reserveMeetings(vector<vector<int>>& meetings, int m) {
		int n = meetings.size();
		// 开始时间，结束时间
		vector<int>ranks(n << 1);
		for (int i = 0; i < n; i++) {
			ranks[i] = meetings[i][1];
			ranks[i + n] = meetings[i][2] - 1;
		}
		sort(ranks.begin(), ranks.end());
		vector<Info>reMeetings(n);
		int size = 0;
		for (int i = 0; i < n; i++) {
			int origIndex = i;
			int time = meetings[i][0];
			int start = rank(ranks, meetings[i][1]);
			int end = rank(ranks, meetings[i][2] - 1);
			reMeetings[i] = Info(origIndex, time, start, end);
		}
		SegmentTree st(n);
		sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b)->int {
			return a[0] < b[0];
			 });
		vector<bool>ans(n);
		for (auto& meeting : reMeetings) {
			if (st.getMax(meeting.start, meeting.end, 1, n, 1) < m) {
				ans[meeting.origIndex] = true;
				st.add(meeting.start, meeting.end, 1, 1, n, 1);
			}
		}
		return ans;
	}


	// 返回>=num, 最左位置
	int rank(vector<int>& sorted, int num) {
		int l = 0;
		int r = sorted.size() - 1;
		int m = 0;
		int ans = 0;
		while (l <= r) {
			m = (l + r) / 2;
			if (sorted[m] >= num) {
				ans = m;
				r = m - 1;
			} else {
				l = m + 1;
			}
		}
		return ans + 1;
	}

	class SegmentTree {
		int n;
		vector<int>maxs;
		vector<int>lazy;
	public:
		SegmentTree(int size) {
			n = size;
			maxs.resize(n << 2);
			lazy.resize(n << 2);
		}
		void pushUp(int rt) {
			maxs[rt] = max(maxs[rt << 1], maxs[rt << 1 | 1]);
		}
		void pushDown(int rt, int ln, int rn) {
			if (lazy[rt] != 0) {
				maxs[rt << 1] += lazy[rt];
				maxs[rt << 1 | 1] += lazy[rt];
				lazy[rt << 1] += lazy[rt];
				lazy[rt << 1 | 1] += lazy[rt];
				lazy[rt] = 0;
			}
		}
		void add(int L, int R, int C, int l, int r, int rt) {
			if (L <= l && r <= R) {
				maxs[rt] += C;
				lazy[rt] += C;
				return;
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			if (L <= mid) {
				add(L, R, C, l, mid, rt << 1);
			}
			if (R > mid) {
				add(L, R, C, mid + 1, r, rt << 1 | 1);
			}
			pushUp(rt);
		}
		int getMax(int L, int R, int l, int r, int rt) {
			if (L <= l && r <= R) {
				return maxs[rt];
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			int ans = INT_MIN;
			if (L <= mid) {
				ans = max(ans, getMax(L, R, l, mid, rt << 1));
			}
			if (R > mid) {
				ans = max(ans, getMax(L, R, mid + 1, r, rt << 1 | 1));
			}
			return ans;
		}
	};

};
