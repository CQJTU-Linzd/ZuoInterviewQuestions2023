// 101
// https://www.bilibili.com/video/BV1DT411s7hp?p=101&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class CorporateFlightBooking {
public:

    vector<int> booking(vector<vector<int>>& bookings, int n) {
        int* cnt = new int[n + 2];
        for (int i = 0; i < n + 2; i++) {
            cnt[i] = 0;
        }
        for (auto& book : bookings) {
            cnt[book[0]] += book[2];
            cnt[book[1] + 1] -= book[2];
        }
        for (int i = 1; i < n + 2; i++) {
            cnt[i] += cnt[i - 1];
        }
        vector<int>res(n);
        for (int i = 0; i < n; i++) {
            res[i] = cnt[i + 1];
        }
        delete[] cnt;
        return res;
    }

};
