// 95
// https://www.bilibili.com/video/BV1DT411s7hp?p=95&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
// 我们从二叉树的根节点 root 开始进行深度优先搜索。
// 在遍历中的每个节点处，我们输出 D 条短划线（其中 D 是该节点的深度）
// 然后输出该节点的值。（如果节点的深度为 D，则其直接子节点的深度为 D + 1
// 根节点的深度为 0
// 如果节点只有一个子节点，那么保证该子节点为左子节点
// 给出遍历输出 S，还原树并返回其根节点 root。
// 测试链接 : https://leetcode.cn/problems/recover-a-tree-from-preorder-traversal/
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
