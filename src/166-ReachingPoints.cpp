// 166
// https://www.bilibili.com/video/BV14P411Q7L6?p=6&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// https://leetcode.com/problems/reaching-points/
class ReachingPoints {
public:

	bool reachingPoints(int sx, int sy, int tx, int ty) {
		while (sx < tx && sy < ty) {
			if (tx < ty) {
				ty = ty % tx;
			} else {
				tx = tx % ty;
			}
		}
		// 1) sx >= tx
		// 2) sy >= ty
		return (sx == tx && ty >= sy && (ty - sy) % sx == 0)
			|| (sy == ty && tx >= sx && (tx - sx) % sy == 0);
	}

};
