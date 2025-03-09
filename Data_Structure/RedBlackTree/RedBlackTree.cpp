typedef enum { RED = 0, BLACK } Color;

template <typename Type>
struct RBTNode {
    Color color;
    Type key;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
};

template<typename Type>
class RBTree {
public:
    RBTree() {
        Nil = BuyNode();
        root = Nil;
        Nil->color = BLACK;
    }

    ~RBTree() {
        destroy(root);
        delete Nil;
        Nil = NULL;
    }

    void InOrder() { InOrder(root); }

    bool Insert(const Type &value) {
        RBTNode<Type>* pr = Nil;
        RBTNode<Type>* s = root;
        while (s != Nil) {
            if (value == s->key) {
                return false;
            }
            pr = s;
            if (value < s->key) {
                s = s->left;
            } else {
                s = s->right;
            }
        }
        s = BuyNode(value);
        if (pr == Nil) {
            root = s;
            root->parent = pr;
        } else {
            if (value < pr->key) {
                pr->left = s;
            } else {
                pr->right = s;
            }
            s->parent = pr;
        }
        Insert_Fixup(s);
        return true;
    }

    void Remove(Type key) {
        RBTNode<Type>* t;
        if ((t = Search(root, key)) != Nil) {
            Remove(t);
        }
    }

    void InOrderPrint() { InOrderPrint(root); }

protected:
    RBTNode<Type>* BuyNode(const Type &x = Type()) {
        RBTNode<Type>* s = new RBTNode<Type>();
        assert(s != NULL);
        s->color = RED;
        s->left = s->right = s->parent = Nil;
        s->key = x;
        return s;
    }

    void InOrder(RBTNode<Type>* root) {
        if (root != Nil) {
            InOrder(root->left);
            cout << root->key << " ";
            InOrder(root->right);
        }
    }

    void LeftRotate(RBTNode<Type>* z) {
        RBTNode<Type>* y = z->right;
        z->right = y->left;
        if (y->left != Nil) {
            y->left->parent = z;
        }
        y->parent = z->parent;
        if (root == z) {
            root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->left = z;
        z->parent = y;
    }

    void RightRotate(RBTNode<Type>* z) {
        RBTNode<Type>* y = z->left;
        z->left = y->right;
        if (y->right != Nil) {
            y->right->parent = z;
        }
        y->parent = z->parent;
        if (root == z) {
            root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->right = z;
        z->parent = y;
    }

    void Insert_Fixup(RBTNode<Type>* s) {
        RBTNode<Type>* uncle;
        while (s->parent->color == RED) {
            if (s->parent == s->parent->parent->left) {
                uncle = s->parent->parent->right;
                if (uncle->color == RED) {
                    s->parent->color = BLACK;
                    uncle->color = BLACK;
                    s->parent->parent->color = RED;
                    s = s->parent->parent;
                } else {
                    if (s == s->parent->right) {
                        s = s->parent;
                        LeftRotate(s);
                    }
                    s->parent->color = BLACK;
                    s->parent->parent->color = RED;
                    RightRotate(s->parent->parent);
                }
            } else {
                if (s->parent == s->parent->parent->right) {
                    uncle = s->parent->parent->left;
                    if (uncle->color == RED) {
                        s->parent->color = BLACK;
                        uncle->color = BLACK;
                        s->parent->parent->color = RED;
                        s = s->parent->parent;
                    } else {
                        if (s == s->parent->left) {
                            s = s->parent;
                            RightRotate(s);
                        }
                        s->parent->color = BLACK;
                        s->parent->parent->color = RED;
                        LeftRotate(s->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK;
    }

    RBTNode<Type>* Search(RBTNode<Type>* root, Type key) const {
        if (root == Nil) {
            return Nil;
        }
        if (root->key == key) {
            return root;
        }
        if (key < root->key) {
            return Search(root->left, key);
        } else {
            return Search(root->right, key);
        }
    }

    void Transplant(RBTNode<Type>* u, RBTNode<Type>* v) {
        if (u->parent == Nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    RBTNode<Type>* Minimum(RBTNode<Type>* x) {
        if (x->left == Nil) {
            return x;
        }
        return Minimum(x->left);
    }

    void Remove(RBTNode<Type>* z) {
        RBTNode<Type>* x = Nil;
        RBTNode<Type>* y = z;
        Color ycolor = y->color;
        if (z->left == Nil) {
            x = z->right;
            Transplant(z, z->right);
        } else if (z->right == Nil) {
            x = z->left;
            Transplant(z, z->left);
        } else {
            y = Minimum(z->right);
            ycolor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            Transplant(z, y);
            y->left = z->left;
            z->left->parent = y;
            y->color = z->color;
        }
        if (ycolor == BLACK) {
            Remove_Fixup(x);
        }
    }

    void Remove_Fixup(RBTNode<Type>* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTNode<Type>* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->color = RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root;
                }
            } else {
                // 对称处理右子树
            }
        }
        x->color = BLACK;
    }

    RBTNode<Type>* root;
    RBTNode<Type>* Nil;
};
