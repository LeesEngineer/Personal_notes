#include <iostream>
using namespace std;

template <typename T>
struct AVLTreeNode
{
    T m_key;                  // 关键字
    int m_height;             // 高度
    AVLTreeNode *m_leftChild; // 左孩子
    AVLTreeNode *m_rightNode; // 右孩子
    AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r) : m_key(value), m_height(0), m_leftChild(l), m_rightNode(r) {}
};

template <typename T>
class AVLTree
{
public:
    AVLTree() : m_root(NULL) {}
    ~AVLTree() { destroy(m_root); }

public:
    // 中序遍历
    void inOrder() { inOrder(m_root); }

    // 先序遍历
    void preOrder() { preOrder(m_root); }

    // 树的高度
    int height() { return height(m_root); }

    // 查找AVL树种值为key的结点（递归）
    AVLTreeNode<T> *search(T key) { return search(m_root, key); }

    // 查找AVL树种值为key的结点（非递归）
    AVLTreeNode<T> *iterativeSearch(T key) { return iterativeSearch(m_root, key); }

    // 查找最小结点，返回最小结点的键值
    T minimum()
    {
        AVLTreeNode<T> *p = minimum(m_root);
        if (p != NULL)
            return p->m_key;
        return (T)NULL;
    }

    // 查找最大结点，返回最大结点的键值
    T maximum()
    {
        AVLTreeNode<T> *p = maximum(m_root);
        if (p != NULL)
            return p->m_key;
        return (T)NULL;
    }

    // 将键值为key的结点插入到AVL中
    void insert(T key) { insert(m_root, key); }

    // 删除键值为key的结点
    void remove(T key)
    {
        AVLTreeNode<T> *z = search(m_root, key);
        if (z != NULL)
            m_root = remove(m_root, z);
    }

    // 销毁AVL树
    void destroy() { destroy(m_root); }

private:
    void inOrder(AVLTreeNode<T> *node)
    {
        if (node == NULL)
            return;
        inOrder(node->m_leftChild);
        cout << node->m_key << " ";
        inOrder(node->m_rightNode);
    }

    void preOrder(AVLTreeNode<T> *node)
    {
        if (node == NULL)
            return;
        cout << node->m_key << " ";
        preOrder(node->m_leftChild);
        preOrder(node->m_rightNode);
    }

    int height(AVLTreeNode<T> *node)
    {
        return node != NULL ? node->m_height : 0;
    }

    void destroy(AVLTreeNode<T> *&tree)
    {
        if (tree == NULL)
            return;
        if (tree->m_leftChild != NULL)
            destroy(tree->m_leftChild);
        if (tree->m_rightNode != NULL)
            destroy(tree->m_rightNode);
        delete tree;
    }

    AVLTreeNode<T> *search(AVLTreeNode<T> *node, T key)
    {
        if (node == NULL || node->m_key == key)
            return node;
        if (key < node->m_key)
            return search(node->m_leftChild, key);
        else
            return search(node->m_rightNode, key);
    }

    AVLTreeNode<T> *iterativeSearch(AVLTreeNode<T> *node, T key)
    {
        while ((node != NULL) && (node->m_key != key))
        {
            if (key < node->m_key)
                node = node->m_leftChild;
            else
                node = node->m_rightNode;
        }
        return node;
    }

    AVLTreeNode<T> *minimum(AVLTreeNode<T> *node)
    {
        if (node == NULL)
            return NULL;
        while (node->m_leftChild != NULL)
        {
            node = node->m_leftChild;
        }
        return node;
    }

    AVLTreeNode<T> *maximum(AVLTreeNode<T> *node)
    {
        if (node == NULL)
            return NULL;
        while (node->m_rightNode != NULL)
        {
            node = node->m_rightNode;
        }
        return node;
    }

    AVLTreeNode<T> *insert(AVLTreeNode<T> *&node, T key)
    {
        if (node == NULL)
        {
            node = new AVLTreeNode<T>(key, NULL, NULL);
        }
        else if (key < node->m_key) // key插入node的左子树的情况
        {
            node->m_leftChild = insert(node->m_leftChild, key);
            // 插入节点后，如果AVL树失衡，需要进行相应调节
            if (height(node->m_leftChild) - height(node->m_rightNode) == 2)
            {
                if (key < node->m_leftChild->m_key)
                    node = leftLeftRotation(node);
                else
                    node = leftRightRotation(node);
            }
        }
        else if (key > node->m_key) // key插入node的右子树的情况
        {
            node->m_rightNode = insert(node->m_rightNode, key);
            // 插入节点后，如果AVL树失衡，需要进行相应调节
            if (height(node->m_rightNode) - height(node->m_leftChild) == 2)
            {
                if (key > node->m_rightNode->m_key)
                    node = rightRightRotation(node);
                else
                    node = rightLeftRotation(node);
            }
        }
        else
        {
            cout << "添加失败，不能添加相同的结点" << endl;
        }
        node->m_height = max(height(node->m_leftChild), height(node->m_rightNode)) + 1;
        return node;
    }

    AVLTreeNode<T> *remove(AVLTreeNode<T> *&node, AVLTreeNode<T> *z)
    {
        if (node == NULL || z == NULL)
            return NULL;

        if (z->m_key < node->m_key) // 待删除的节点在tree的左子树中
        {
            node->m_leftChild = remove(node->m_leftChild, z);
            // 删除节点后，如果AVL树失衡，需要进行相应调节
            if (height(node->m_rightNode) - height(node->m_leftChild) == 2)
            {
                AVLTreeNode<T> *r = node->m_rightNode;
                if (height(r->m_leftChild) > height(r->m_rightNode))
                    node = rightLeftRotation(node);
                else
                    node = rightRightRotation(node);
            }
        }
        else if (z->m_key > node->m_key) //待删除的节点在node的右子树中
        {
            // 删除节点后，如果AVL树失衡，需要进行相应调节
            node->m_rightNode = remove(node->m_rightNode, z);
            if (height(node->m_leftChild) - height(node->m_rightNode) == 2)
            {
                AVLTreeNode<T> *l = node->m_leftChild;
                if (height(l->m_rightNode) > height(l->m_leftChild))
                    node = leftRightRotation(node);
                else
                    node = leftLeftRotation(node);
            }
        }
        else //当前node就是要删除的节点
        {
            if ((node->m_leftChild != NULL) && (node->m_rightNode != NULL))
            {
                if (height(node->m_leftChild) > height(node->m_rightNode))
                {
                    if (height(node->m_leftChild) > height(node->m_rightNode))
                    {
                        /* 如果node节点的左子树比右子树高，则:
                         * (01)找出node的左子树中最大节点
                         * (02)将该最大节点的值赋值给node
                         * (03)删除该最大节点
                         * 相当于用node的左子树中最大节点作为node的替身
                         * 这种方式删除node左子树中最大节点之后，AVL树任然是平衡的
                         */
                        AVLTreeNode<T> *max = maximum(node->m_leftChild);
                        node->m_key = max->m_key;
                        node->m_leftChild = remove(node->m_leftChild, max);
                    }
                    else
                    {
                        /* 如果node节点的右子树比左子树高，则:
                         * (01)找出node的右子树中最小节点
                         * (02)将该最小节点的值赋值给node
                         * (03)删除该最小节点
                         * 相当于用node的右子树中最小节点作为node的替身
                         * 这种方式删除node右子树中最小节点之后，AVL树任然是平衡的
                         */
                        AVLTreeNode<T> *min = minimum(node->m_rightNode);
                        node->m_key = min->m_key;
                        node->m_rightNode = remove(node->m_rightNode, min);
                    }
                }
            }
            else
            {
                // 被删除的节点等于node，并且node有一个孩子
                // 将当前节点指向该孩子节点并删除当前节点
                AVLTreeNode<T> *tmp = node;
                node = node->m_leftChild != NULL ? node->m_leftChild : node->m_rightNode;
                delete tmp;
            }
        }
        return node;
    }

private:
    /* LL：左子树的左边失去平衡(左单旋转)
     *       k2              k1     
     *      /  \            /  \
     *     k1   z   ===>   x    k2
     *    /  \                 /  \
     *   x    y               y    z
     */

    AVLTreeNode<T> *leftLeftRotation(AVLTreeNode<T> *&k2)
    {
        AVLTreeNode<T> *k1 = k2->m_leftChild;
        k2->m_leftChild = k1->m_rightNode;
        k1->m_rightNode = k2;
        k2->m_height = std::max(height(k2->m_leftChild), height(k2->m_rightNode)) + 1;
        k1->m_height = std::max(height(k1->m_leftChild), k2->m_height) + 1;
        return k1;
    }

    /* RR：右子树的右边失去平衡(右单旋转)
     *       k1              k2     
     *      /  \            /  \
     *     x   k2   ===>   k1   z
     *        /  \        /  \   
     *       y    z      x    y  
     */
    AVLTreeNode<T> *rightRightRotation(AVLTreeNode<T> *&k1)
    {
        AVLTreeNode<T> *k2 = k1->m_rightNode;
        k1->m_rightNode = k2->m_leftChild;
        k2->m_leftChild = k1;

        k1->m_height = std::max(height(k1->m_leftChild), height(k1->m_rightNode)) + 1;
        k2->m_height = std::max(height(k2->m_rightNode), k1->m_height) + 1;
        return k2;
    }

    /* LR：左子树的右边失去平衡(左双旋转)
     *       k3               k3               k2
     *      /  \     RR      /  \     LL      /  \
     *     k1   D   ===>   k2    D   ===>   k1    k3
     *    /  \            /  \             /  \  /  \
     *   A    K2         k1   C           A    B C   D
     *       /  \       /  \
     *      B    C     A    B
     */
    AVLTreeNode<T> *leftRightRotation(AVLTreeNode<T> *&k3)
    {
        k3->m_leftChild = rightRightRotation(k3->m_leftChild);
        return leftLeftRotation(k3);
    }

    /* RL：右子树的左边失去平衡(右双旋转)
     *     k1               k1                K2
     *    /  \      LL     /  \      RR      /  \
     *   A    k3   ===>   A    k2   ===>   k1    K3
     *       /  \             /  \        /  \  /  \
     *      k2   D           B    k3     A    B C   D
     *     /  \                  /   \
     *    B    D                C     D
     */
    AVLTreeNode<T> *rightLeftRotation(AVLTreeNode<T> *&k1)
    {
        k1->m_rightNode = leftLeftRotation(k1->m_rightNode);
        return rightRightRotation(k1);
    }

private:
    AVLTreeNode<T> *m_root; // AVL树的根节点
};
