class Solution {
public:
	DoublyListNode * bstToDoublyList(TreeNode * root) {
		DoublyListNode *first = NULL;
		DoublyListNode *q;
		std::stack<TreeNode*> S;
		TreeNode *p = root;
		do {
			while (p != NULL) {
				S.push(p);
				p = p->left;
			}
			if (!S.empty()) {
				p = S.top(); S.pop();
				if (first == NULL) { first = new DoublyListNode(p->val); q = first; }
				else {
					q->next = new DoublyListNode(p->val);
					q->next->prev = q;
					q = q->next;
				}
				p = p->right;
			}
		} while (p != NULL || !S.empty());
		return first;
	}
};
