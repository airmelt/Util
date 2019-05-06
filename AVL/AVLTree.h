#include <algorithm>
#include <iostream>
// ��ʽ������ļ�
#include <iomanip>
using namespace std;

template <class T>
// 1. AVL���Ľ��
class AVLTreeNode {
	public:
		// �ؼ���(��ֵ)
		T key;
		// �߶�
		int height;
		// ����
		AVLTreeNode* left;
		// �Һ���
		AVLTreeNode* right;

		AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r):
			key(value), height(0), left(l), right(r) {}
};

template <class T>
// 2. AVL��
class AVLTree {
	public:
		AVLTree();
		~AVLTree();

		// ��ȡ���ĸ߶�
		int height();

		// ǰ����� AVL
		void preOrder();
		// ������� AVL
		void inOrder();
		// ������� AVL
		void postOrder();

		// (�ݹ�ʵ��)���� AVL���м�ֵΪ key�Ľ��
		AVLTreeNode<T>* search(T key);
		// (�ǵݹ�ʵ��)���� AVL���м�ֵΪ key�Ľ��
		AVLTreeNode<T>* iterativeSearch(T key);

		// ������С���: ������С���ļ�ֵ
		T minimum();
		// ���������: ���������ļ�ֵ
		T maximum();

		// �����(keyΪ����ֵ)���뵽 AVL����
		void insert(T key);
		// ɾ�����(keyΪ����ֵ)
		void remove(T key);

		// ���� AVL��
		void destroy();
		// ��ӡ AVL��
		void print();
	private:
		// �����
		AVLTreeNode<T> *root;

        // ��ȡ���ĸ߶�
        int height(AVLTreeNode<T>* tree) ;

        // ǰ�����"AVL��"
        void preOrder(AVLTreeNode<T>* tree) const;
        // �������"AVL��"
        void inOrder(AVLTreeNode<T>* tree) const;
        // �������"AVL��"
        void postOrder(AVLTreeNode<T>* tree) const;

        // (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
        AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
        // (�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
        AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

        // ������С��㣺����treeΪ������AVL������С��㡣
        AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
        // ��������㣺����treeΪ������AVL��������㡣
        AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

        // LL�������Ӧ�����(����ת)��
        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

        // RR�����Ҷ�Ӧ�����(�ҵ���ת)��
        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

        // LR�����Ҷ�Ӧ�����(��˫��ת)��
        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

        // RL�������Ӧ�����(��˫��ת)��
        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

        // �����(z)���뵽AVL��(tree)��
        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

        // ɾ��AVL��(tree)�еĽ��(z)�������ر�ɾ���Ľ��
        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

        // ����AVL��
        void destroy(AVLTreeNode<T>* &tree);

        // ��ӡAVL��
        void print(AVLTreeNode<T>* tree, T key, int direction);
};

/* 
 * ���캯��
 */
template <class T>
AVLTree<T>::AVLTree():root(NULL) {
}

/* 
 * ��������
 */
template <class T>
AVLTree<T>::~AVLTree() {
    destroy(root);
}

/*
 * ��ȡ���ĸ߶�
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
 * LL�������Ӧ�����(����ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
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
 * RR�����Ҷ�Ӧ�����(�ҵ���ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
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
 * LR�����Ҷ�Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3) {
    k3 -> left = rightRightRotation(k3 -> left);

    return leftLeftRotation(k3);
}

/*
 * RL�������Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1) {
    k1 -> right = leftLeftRotation(k1 -> right);

    return rightRightRotation(k1);
}

/* 
 * �������뵽AVL���У������ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     key ����Ľ��ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key) {
    if (!tree) {
        // �½��ڵ�
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (!tree) {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
	// Ӧ�ý�key���뵽"tree��������"�����
    else if (key < tree -> key) {
        tree -> left = insert(tree -> left, key);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree -> left) - height(tree -> right) == 2) {
            if (key < tree -> left -> key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
	// Ӧ�ý�key���뵽"tree��������"�����
    else if (key > tree->key) {
        tree->right = insert(tree->right, key);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->right) - height(tree->left) == 2) {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
	// key == tree -> key
    else {
        cout << "���ʧ�ܣ������������ͬ�Ľڵ㣡" << endl;
    }

    tree -> height = max(height(tree -> left), height(tree -> right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key) {
    insert(root, key);
}

/* 
 * ɾ�����(z)�����ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     z ��ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z) {
    // ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
    if (!tree || !z)
        return NULL;
	// ��ɾ���Ľڵ���"tree��������"��
    if (z -> key < tree -> key) {
        tree -> left = remove(tree -> left, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree -> right) - height(tree -> left) == 2) {
            AVLTreeNode<T> *r =  tree -> right;
            if (height(r -> left) > height(r -> right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
	// ��ɾ���Ľڵ���"tree��������"��
    else if (z -> key > tree -> key) {
        tree -> right = remove(tree -> right, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree -> left) - height(tree -> right) == 2) {
            AVLTreeNode<T> *l = tree -> left;
            if (height(l -> right) > height(l -> left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
	// tree�Ƕ�ӦҪɾ���Ľڵ㡣
    else {
        // tree�����Һ��Ӷ��ǿ�
        if ((tree -> left!=NULL) && (tree -> right!=NULL)) {
            if (height(tree -> left) > height(tree -> right)) {
                // ���tree�����������������ߣ�
                // ��(01)�ҳ�tree���������е����ڵ�
                //   (02)�������ڵ��ֵ��ֵ��tree��
                //   (03)ɾ�������ڵ㡣
                // ����������"tree�������������ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode<T>* max = maximum(tree -> left);
                tree -> key = max -> key;
                tree -> left = remove(tree -> left, max);
            } else {
                // ���tree��������������������(��������ȣ�������������������1)
                // ��(01)�ҳ�tree���������е���С�ڵ�
                //   (02)������С�ڵ��ֵ��ֵ��tree��
                //   (03)ɾ������С�ڵ㡣
                // ����������"tree������������С�ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
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
 * ǰ�����"AVL��"
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
 * �������"AVL��"
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
 * �������"AVL��"
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
 * (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
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
 * (�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
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
 * ������С��㣺����treeΪ������AVL������С��㡣
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
 * ��������㣺����treeΪ������AVL��������㡣
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
 * ����AVL��
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
 * ��ӡ"���������"
 *
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction) {
    if(tree) {
        // tree�Ǹ��ڵ�
        if (direction == 0)    
            cout << setw(2) << tree -> key << " is root" << endl;
        // tree�Ƿ�֧�ڵ�
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
