// 59
// https://www.bilibili.com/video/BV1DT411s7hp?p=59&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class RobotBoundedInCircle {
public:

    bool isBounded(string ins) {
        int r = 0;
        int c = 0;
        int direction = 0;
        for (char cur : ins) {
            if (cur == 'L') {
                direction = left(direction);
            } else if (cur == 'R') {
                direction = right(direction);
            } else {
                r = row(direction, r);
                c = col(direction, c);
            }
        }
        return (r == 0 && c == 0) || direction != 0;
    }

    int left(int direction) {
        return direction == 0 ? 3 : direction - 1;
    }

    int right(int direction) {
        return direction == 3 ? 0 : direction + 1;
    }

    int row(int direction, int r) {
        return (direction == 1 || direction == 3) ? r : (r + (direction == 0 ? 1 : -1));
    }

    int col(int direction, int c) {
        return (direction == 0 || direction == 2) ? c : (c + (direction == 1 ? 1 : -1));
    }

};
