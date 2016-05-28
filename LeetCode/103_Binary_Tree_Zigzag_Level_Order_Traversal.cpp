#include "shared.h"
/*
 Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
 
 For example:
 Given binary tree {3,9,20,#,#,15,7},
 3
 / \
 9  20
 /  \
 15   7
 return its zigzag level order traversal as:
 [
 [3],
 [20,9],
 [15,7]
 ]
 */
namespace BinaryTreeZigzagLevelOrderTraversal{
    /**
     * Definition for a binary tree node.
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     * };
     */
    class Solution {
    public:
        vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
            vector<vector<int>> ans;
            if(root == NULL)
                return ans;
            traverse(root, 0, ans);
            return ans;
        }
    private:
        void traverse(TreeNode* root, int level, vector<vector<int>>& ans){
            if(root == NULL)
                return;
            
            if(level == ans.size())
                ans.push_back({});
            
            if(level % 2 == 0)
                ans[level].push_back(root->val);
            else
                ans[level].insert(ans[level].begin(), root->val);
            traverse(root->left, level + 1, ans);
            traverse(root->right, level + 1, ans);
        }
    };
}
