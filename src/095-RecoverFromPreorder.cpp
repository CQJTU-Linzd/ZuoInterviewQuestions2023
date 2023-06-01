// 95
// https://www.bilibili.com/video/BV1DT411s7hp?p=95&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class RecoverFromPreorder {
public:

    class Node {
    public:
        int level;
        int val;
        Node(int l, int v) {
            level = l;
            val = v;
        }
    };

    // 1-2--3--4-5--6--7
    TreeNode* recoverFromPreorder(string traversal) {
        queue<Node>queue = generateNodes(traversal);
        return rebuild(queue);
    }

    TreeNode* rebuild(queue<Node>& queue) {
        Node cur = queue.front();
        queue.pop();
        int curLevel = cur.level;
        int curVal = cur.val;

        TreeNode* head = new TreeNode(curVal);

        if (!queue.empty() && queue.front().level > curLevel) {
            head->left = rebuild(queue);
        }
        if (!queue.empty() && queue.front().level > curLevel) {
            head->right = rebuild(queue);
        }
        return head;
    }


    queue<Node> generateNodes(string s) {
        queue<Node>que;
        int i = 0, j = 0;
        while (j < s.size() && s[j] != '-') {
            j++;
        }
        string root = s.substr(i, j - i);
        que.push(Node(0, atoi(root.c_str())));
        i = j;
        for (; j < s.size(); j++) {
            if (s[j] != '-') { // 数字开头
                int curLevel = j - i;
                int numEnd = j;
                while (numEnd < s.size() && s[numEnd] != '-') {
                    numEnd++;
                }
                string curVal = s.substr(j, numEnd - j);
                que.push(Node(curLevel, atoi(curVal.c_str())));
                j = numEnd;
                i = numEnd;
            }
        }
        return que;
    }

};
