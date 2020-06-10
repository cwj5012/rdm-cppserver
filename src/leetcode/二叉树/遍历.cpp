/**
 * 前序遍历首先访问根节点，然后遍历左子树，最后遍历右子树。
 *
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/**
 * 前序遍历，递归
 */
namespace {
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        helper(root, result);
        return result;
    }

    void helper(TreeNode* root, vector<int>& result) {
        if (root == NULL) {
            return;
        }
        result.push_back(root->val);
        helper(root->left, result);
        helper(root->right, result);
    }
};
}

/**
 * 前序遍历，迭代
 *
 * 作者：sonp
 * 链接：https://leetcode-cn.com/problems/binary-tree-preorder-traversal/solution/miao-sha-quan-chang-ba-hou-lang-by-sonp/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */
namespace {
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;  //保存结果
        stack < TreeNode * > call;  //调用栈
        if (root != nullptr) call.push(root);  //首先介入root节点
        while (!call.empty()) {
            TreeNode* t = call.top();
            call.pop();  //访问过的节点弹出
            if (t != nullptr) {
                if (t->right) call.push(t->right);  //右节点先压栈，最后处理
                if (t->left) call.push(t->left);
                call.push(t);  //当前节点重新压栈（留着以后处理），因为先序遍历所以最后压栈
                call.push(nullptr);  //在当前节点之前加入一个空节点表示已经访问过了
            } else {  //空节点表示之前已经访问过了，现在需要处理除了递归之外的内容
                res.push_back(call.top()->val);  //call.top()是nullptr之前压栈的一个节点，也就是上面call.push(t)中的那个t
                call.pop();  //处理完了，第二次弹出节点（彻底从栈中移除）
            }
        }
        return res;
    }
};
}
