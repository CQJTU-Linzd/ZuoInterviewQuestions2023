#ifndef _HEADFILE_
#define _HEADFILE_

#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<iomanip>
#include<string>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<ctime>
#include<cmath>

class ListNode {
public:
	int val;
	ListNode* next;
	ListNode(int val) {
		this->val = val;
		this->next = nullptr;
	}
};

// 双向链表
class DoubleNode {
public:
	int val;
	DoubleNode* next;
	DoubleNode* last;
	DoubleNode(int val) {
		this->val = val;
		this->next = nullptr;
		this->last = nullptr;
	}
};

// 二叉树
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int val) {
		this->val = val;
		this->left = NULL;
		this->right = NULL;
	}
};

#endif // !_HEADFILE_
