#include <algorithm>
#include <iostream>
// 格式化输出文件
#include <iomanip>
using namespace std;

template <class T>
// 1. AVL树的结点
class AVLTreeNode {
	public:
		// 关键字(键值)
		T key;
		// 高度
		int height;
		// 左孩子
		AVLTreeNode* left;
		// 右孩子
		AVLTreeNode* right;

		AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r):
			key(value), height(0), left(l), right(r) {}
};

template <class T>
// 2. AVL树
class AVLTree {
	public:
		AVLTree();
		~AVLTree();

		// 获取树的高度
		int height();

		// 前序遍历 AVL
		void preOrder();
		// 中序遍历 AVL
		void inOrder();
		// 后序遍历 AVL
		void postOrder();

		// (递归实现)查找 AVL树中键值为 key的结点
		AVLTreeNode<T>* search(T key);
		// (非递归实现)查找 AVL树中键值为 key的结点
		AVLTreeNode<T>* iterativeSearch(T key);

		// 查找最小结点: 返回最小结点的键值
		T minimum();
		// 查找最大结点: 返回最大结点的键值
		T maximum();

		// 将结点(key为结点键值)插入到 AVL树中
		void insert(T key);
		// 删除结点(key为结点键值)
		void remove(T key);

		// 销毁 AVL树
		void destroy();
		// 打印 AVL树
		void print();
	private:
		// 根结点
		AVLTreeNode<T> *root;

        // 获取树的高度
        int height(AVLTreeNode<T>* tree) ;

        // 前序遍历"AVL树"
        void preOrder(AVLTreeNode<T>* tree) const;
        // 中序遍历"AVL树"
        void inOrder(AVLTreeNode<T>* tree) const;
        // 后序遍历"AVL树"
        void postOrder(AVLTreeNode<T>* tree) const;

        // (递归实现)查找"AVL树x"中键值为key的节点
        AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
        // (非递归实现)查找"AVL树x"中键值为key的节点
        AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

        // 查找最小结点：返回tree为根结点的AVL树的最小结点。
        AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
        // 查找最大结点：返回tree为根结点的AVL树的最大结点。
        AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

        // LL：左左对应的情况(左单旋转)。
        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

        // RR：右右对应的情况(右单旋转)。
        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

        // LR：左右对应的情况(左双旋转)。
        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

        // RL：右左对应的情况(右双旋转)。
        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

        // 将结点(z)插入到AVL树(tree)中
        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

        // 删除AVL树(tree)中的结点(z)，并返回被删除的结点
        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

        // 销毁AVL树
        void destroy(AVLTreeNode<T>* &tree);

        // 打印AVL树
        void print(AVLTreeNode<T>* tree, T key, int direction);
};

/* 
 * 构造函数
 */
template <class T>
AVLTree<T>::AVLTree():root(NULL) {
}

/* 
 * 析构函数
 */
template <class T>
AVLTree<T>::~AVLTree() {
    destroy(root);
}

/*
 * 获取树的高度
 */
template <class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree) {
    if (tree) return tree -> height;
    return 0;
}

template <class T>
int AVLTree<T>::height() {
    return height(root);
}

/*
 * LL：左左对应的情况(左单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2) {
    AVLTreeNode<T>* k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1->right = k2;

    k2 -> height = max(height(k2 -> left), height(k2 -> right)) + 1;
    k1 -> height = max(height(k1 -> left), k2 -> height) + 1;

    return k1;
}

/*
 * RR：右右对应的情况(右单旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2 = k1 -> right;
    k1 -> right = k2 -> left;
    k2 -> left = k1;

    k1 -> height = max(height(k1 -> left), height(k1 -> right)) + 1;
    k2 -> height = max(height(k2 -> right), k1 -> height) + 1;

    return k2;
}

/*
 * LR：左右对应的情况(左双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3) {
    k3 -> left = rightRightRotation(k3 -> left);

    return leftLeftRotation(k3);
}

/*
 * RL：右左对应的情况(右双旋转)。
 *
 * 返回值：旋转后的根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1) {
    k1 -> right = leftLeftRotation(k1 -> right);

    return rightRightRotation(k1);
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key) {
    if (!tree) {
        // 新建节点
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (!tree) {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
	// 应该将key插入到"tree的左子树"的情况
    else if (key < tree -> key) {
        tree -> left = insert(tree -> left, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree -> left) - height(tree -> right) == 2) {
            if (key < tree -> left -> key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
	// 应该将key插入到"tree的右子树"的情况
    else if (key > tree->key) {
        tree->right = insert(tree->right, key);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree->right) - height(tree->left) == 2) {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
	// key == tree -> key
    else {
        cout << "添加失败：不允许添加相同的节点！" << endl;
    }

    tree -> height = max(height(tree -> left), height(tree -> right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key) {
    insert(root, key);
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z) {
    // 根为空 或者 没有要删除的节点，直接返回NULL。
    if (!tree || !z)
        return NULL;
	// 待删除的节点在"tree的左子树"中
    if (z -> key < tree -> key) {
        tree -> left = remove(tree -> left, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree -> right) - height(tree -> left) == 2) {
            AVLTreeNode<T> *r =  tree -> right;
            if (height(r -> left) > height(r -> right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
	// 待删除的节点在"tree的右子树"中
    else if (z -> key > tree -> key) {
        tree -> right = remove(tree -> right, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(tree -> left) - height(tree -> right) == 2) {
            AVLTreeNode<T> *l = tree -> left;
            if (height(l -> right) > height(l -> left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
	// tree是对应要删除的节点。
    else {
        // tree的左右孩子都非空
        if ((tree -> left!=NULL) && (tree -> right!=NULL)) {
            if (height(tree -> left) > height(tree -> right)) {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T>* max = maximum(tree -> left);
                tree -> key = max -> key;
                tree -> left = remove(tree -> left, max);
            } else {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                AVLTreeNode<T>* min = maximum(tree -> right);
                tree -> key = min -> key;
                tree -> right = remove(tree -> right, min);
            }
        }
        else {
            AVLTreeNode<T>* tmp = tree;
            tree = (!tree -> left) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void AVLTree<T>::remove(T key){
    AVLTreeNode<T>* z; 
    if (z = search(root, key)) root = remove(root, z);
}

/*
 * 前序遍历"AVL树"
 */
template <class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const {
    if(tree) {
        cout<< tree -> key << " " ;
        preOrder(tree -> left);
        preOrder(tree -> right);
    }
}

template <class T>
void AVLTree<T>::preOrder() {
    preOrder(root);
}

/*
 * 中序遍历"AVL树"
 */
template <class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const {
    if(tree) {
        inOrder(tree -> left);
        cout<< tree -> key << " " ;
        inOrder(tree -> right);
    }
}

template <class T>
void AVLTree<T>::inOrder() {
    inOrder(root);
}

/*
 * 后序遍历"AVL树"
 */
template <class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const {
    if(tree) {
        postOrder(tree -> left);
        postOrder(tree -> right);
        cout<< tree -> key << " " ;
    }
}

template <class T>
void AVLTree<T>::postOrder() {
    postOrder(root);
}

/*
 * (递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const {
    if (!x || x -> key == key) return x;
    if (key < x -> key) return search(x -> left, key);
    else return search(x -> right, key);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key) {
    return search(root, key);
}

/*
 * (非递归实现)查找"AVL树x"中键值为key的节点
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const {
    while (x && (x -> key != key)) {
        if (key < x -> key) x = x -> left;
        else x = x -> right;
    }
    return x;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key) {
    return iterativeSearch(root, key);
}

/* 
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree) {
    if (!tree) return NULL;
    while (tree -> left) tree = tree -> left;
    return tree;
}

template <class T>
T AVLTree<T>::minimum() {
    AVLTreeNode<T> *p = minimum(root);
    if (p) return p -> key;
    return (T)NULL;
}
 
/* 
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree) {
    if (!tree) return NULL;
    while (tree -> right) tree = tree->right;
    return tree;
}

template <class T>
T AVLTree<T>::maximum() {
    AVLTreeNode<T> *p = maximum(root);
    if (p) return p -> key;
    return (T)NULL;
}

/* 
 * 销毁AVL树
 */
template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree) {
    if (!tree) return;
    if (tree -> left) destroy(tree -> left);
    if (tree -> right) destroy(tree -> right);
    delete tree;
}

template <class T>
void AVLTree<T>::destroy() {
    destroy(root);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction) {
    if(tree) {
        // tree是根节点
        if (direction == 0)    
            cout << setw(2) << tree -> key << " is root" << endl;
        // tree是分支节点
        else                
            cout << setw(2) << tree -> key << " is " << setw(2) << key << "'s "  << setw(12) << (direction == 1 ? "right child" : "left child") << endl;
        print(tree -> left, tree -> key, -1);
        print(tree -> right, tree -> key, 1);
    }
}

template <class T>
void AVLTree<T>::print() {
    if (root) print(root, root -> key, 0);
}
