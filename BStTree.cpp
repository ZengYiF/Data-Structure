#include"BSTree.h"

int main()
{
	int arr[10] = { 6,5,7,4,3,0,9,7,6,22 };
	BSTree<int> T;
	for (auto n : arr)
	{
		T.Insert(n);
	}
	T.InOrder();
	return 0;
}