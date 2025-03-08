#include <iostream>

using namespace std;

enum Color { RED, BLACK };

// 红黑树节点
struct Node
{
    int data; // 节点值
    bool color; // 颜色
    Node *left, *right, *parent; // 左右子节点及父节点
    
    // 构造函数
    Node(int data)
    {
        this->data = data;
        left = right = parent = nullptr;
        this->color = RED; // 新插入的节点为红色
    }
};

// 红黑树
class RedBlackTree
{
private:
    Node *root; // 根节点
    
    // 左旋操作
    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;
        pt->right = pt_right->left;
        if (pt->right != nullptr)
            pt->right->parent = pt;
        pt_right->parent = pt->parent;
        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;
        pt_right->left = pt;
        pt->parent = pt_right;
    }
    
    // 右旋操作
    void rotateRight(Node *&root, Node *&pt)
    {
        Node *pt_left = pt->left;
        pt->left = pt_left->right;
        if (pt->left != nullptr)
            pt->left->parent = pt;
        pt_left->parent = pt->parent;
        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;
        pt_left->right = pt;
        pt->parent = pt_left;
    }
    
    // 调整树以保持红黑树性质
    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;
        while ((pt != root) && (pt->color != BLACK) &&
               (pt->parent->color == RED))
        {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;
            // 情况A: 父节点是祖父节点的左子节点
            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;
                // 情况1: 叔叔节点是红色
                if (uncle_pt != nullptr && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    // 情况2: 叔叔节点是黑色，且当前节点是右子节点
                    if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    // 情况3: 叔叔节点是黑色，且当前节点是左子节点
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
            // 情况B: 父节点是祖父节点的右子节点
            else
            {
                Node *uncle_pt = grand_parent_pt->left;
                // 情况1: 叔叔节点是红色
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {
                    // 情况2: 叔叔节点是黑色，且当前节点是左子节点
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    // 情况3: 叔叔节点是黑色，且当前节点是右子节点
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }
    
public:
    
    // 构造函数
    RedBlackTree() { root = nullptr; }
    
    // 插入新节点
    void insert(const int &data)
    {
        Node *pt = new Node(data);
        // 执行BST插入
        root = BSTInsert(root, pt);
        // 修复红黑树的性质
        fixViolation(root, pt);
    }
    
    // 中序遍历
    void inorder() { inorderHelper(root); }
    
    // 层序遍历
    void levelOrder() { levelOrderHelper(root); }
    
private:
    
    // 中序遍历辅助函数
    void inorderHelper(Node *root)
    {
        if (root == nullptr)
            return;
        inorderHelper(root->left);
        cout << root->data << " ";
        inorderHelper(root->right);
    }
    
    // 层序遍历辅助函数
    void levelOrderHelper(Node *root)
    {
        if (root == nullptr)
            return;
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
            cout << temp->data << " ";
            q.pop();
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
    }
    
    // 标准BST插入
    Node *BSTInsert(Node *root, Node *pt)
    {
        // 如果树为空，返回新节点
        if (root == nullptr)
            return pt;
        // 否则递归插入子树
        if (pt->data < root->data)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }
};
