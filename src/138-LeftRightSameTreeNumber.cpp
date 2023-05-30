// 138
// https://www.bilibili.com/video/BV1DT411s7hp?p=138&vd_source=2286e10835cc4cd375b26d18d9e6fa7e
class LeftRightSameTreeNumber {
public:

    int sameNumber(TreeNode* head) {
        if (head == NULL) {
            return 0;
        }
        return sameNumber(head->left) + sameNumber(head->right)
            + (isSame(head->left, head->right) ? 1 : 0);
    }

    bool isSame(TreeNode* h1, TreeNode* h2) {
        if ((h1 == NULL) ^ (h2 == NULL)) {
            return false;
        }
        if (h1 == NULL && h2 == NULL) {
            return true;
        }
        return h1->val == h2->val && isSame(h1->left, h2->left) && isSame(h1->right, h2->right);
    }

};
