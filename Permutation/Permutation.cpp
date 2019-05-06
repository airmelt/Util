#include <vector> 
#include <algorithm>
#include <iostream>
using namespace std;


/*
 *  普通递归实现全排列, 基于交换
 *  array: 需要全排列的列表
 *  position: 开始位置
 *  end: 结束位置
 */
template <class T>
void permutation(vector<T> array, int position, int end) {
	if (position == end) {
		for (int j = 0; j < end; j++) cout << array[j];
		cout << endl;
	}
	else {
		for (int i = position; i < end; i++) {
			swap(array[i], array[position]);
			permutation(array, position + 1, end);
			swap(array[i], array[position]);
		}
	}
}

/*
 *  深度优先搜索实现全排列
 *  array: 需要全排列的列表
 *  position: 位置参数, 记录递归终点
 */
template <class T>
void dfs_permutation(vector<T> array, int position) {
	vector<int> visit(array.size());
	vector<T> temp(array.size());
	dfs(position, array, temp, visit);
}
template <class T>
void dfs(int pos, vector<T> array, vector<T> temp, vector<T> visit) {
	int len = array.size();
	if (pos == array.size()) {
		for (int i = 0; i < len; i++) cout << temp[i];
		cout << endl;
	}
	for (int j = 0; j < len; j++) {
		if (!visit[j]) {
			temp[pos] = array[j];
			visit[j] = 1;
			dfs(pos + 1, array, temp, visit);
			visit[j] = 0;
		}
	}
}

int main() {
	int arr[3] = {1, 2, 3};
	vector<int> v(arr, arr + 3);
	permutation(v, 0, v.size());
	cout << "--------------" << endl;
	dfs_permutation(v, 0);
	return 0;
}