// 21 
// https://www.bilibili.com/video/BV1DT411s7hp?p=21&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class ReversePolishNotation {
public:

    // 根据逆波兰表达式计算结果
    int getAns(string rpn) {
        if (rpn.empty()) {
            return 0;
        }
        vector<string>parts = split(rpn, ' ');
        stack<int>stack;
        for (string part : parts) {
            if (part == "+" || part == "-" || part == "*" || part == "/") {
                int right = stack.top();
                stack.pop();
                int left = stack.top();
                stack.pop();
                int ans = 0;
                if (part == "+") {
                    ans = left + right;
                } else if (part == "-") {
                    ans = left - right;
                } else if (part == "*") {
                    ans = left * right;
                } else {
                    ans = left / right;
                }
                stack.push(ans);
            } else {
                stack.push(atoi(part.c_str()));
            }
        }
        return stack.top();
    }

    // 根据逆波兰式，转化成中序表达式
    enum Operation {
        SingleNumber, AddOrMinus, MultiplyOrDivide
    };

    string convert(string rpn) {
        if (rpn.empty()) {
            return rpn;
        }
        vector<string>parts = split(rpn, ' ');
        stack<string>stack1;
        stack<Operation>stack2;
        for (string cur : parts) {
            if (cur == "+" || cur == "-") { // 加减连接，无需添加括号
                string right = stack1.top();
                stack1.pop();
                string left = stack1.top();
                stack1.pop();
                stack2.pop();
                stack2.pop();
                stack1.push(left + cur + right);
                stack2.push(AddOrMinus);
            } else if (cur == "*" || cur == "/") { // 乘除连接
                string right = stack1.top();
                stack1.pop();
                string left = stack1.top();
                stack1.pop();
                Operation rOp = stack2.top();
                stack2.pop();
                Operation lOp = stack2.top();
                stack2.pop();
                // 左边和右边如果是加减连接，则需要加括号
                left = lOp == AddOrMinus ? ("(" + left + ")") : left;
                right = rOp == AddOrMinus ? ("(" + right + ")") : right;
                stack1.push(left + cur + right);
                stack2.push(MultiplyOrDivide);
            } else {
                stack1.push(cur);
                stack2.push(SingleNumber);
            }
        }
        return stack1.top();
    }


    vector<string> split(string s, char ch) {
        int i = 0;
        int j = 0;
        vector<string>res;
        for (; j < s.size(); j++) {
            if (s[j] == ch) {
                res.push_back(s.substr(i, j - i));
                i = j + 1;
            }
        }
        res.push_back(s.substr(i, j - i));
        return res;
    }
};
