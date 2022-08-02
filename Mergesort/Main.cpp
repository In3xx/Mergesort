#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

#define ENDL cout << endl

void PrintArray(int*, int);
void Divide(int*, int);
int* Merge(int*, int, int*, int);
void Free(int* arr);

struct Array
{
	int size;
	int arr[];
};

int main() {
	int arrSize;
	int maxValue;

	cout << "Array Size : ";
	cin >> arrSize;
	cout << "Max value : ";
	cin >> maxValue;

	srand((unsigned int)time(NULL));
	int* arr = (int*)malloc(sizeof(int) * arrSize);

	for (int i = 0; i < arrSize; i++)
		*(arr + i) = (rand() % maxValue + 1);

	PrintArray(arr, arrSize);
	ENDL;

	Divide(arr, arrSize);
	Free(arr);

	return 0;
}

void PrintArray(int* arr, int arrSize) {
	for (int i = 0; i < arrSize; i++)
		cout << *(arr + i) << " ";
	cout << "\t";
}

void Divide(int* arr, int arrSize) {
	//int retCount = 0;
	//int divideCnt = 2;
	//int dividedSize = arrSize;
	//while (dividedSize != 1)
	//{
	//	if (dividedSize % 2 != 0) {
	//		dividedSize /= 2;
	//		for (int i = 0, j = 0; i < divideCnt; i++, j = 0) {
	//			cout << "[ ";
	//			while (j < dividedSize)
	//			{
	//				cout << arr[j + (i * dividedSize)] << " ";
	//				j++;
	//			}
	//			cout << "]    ";
	//		}
	//		ENDL;
	//		divideCnt *= 2;
	//	}
	//	else {
	//		dividedSize /= 2;
	//		//if(dividedSize)
	//	}
	//}
	//Free(arr);
	/*int maxSize = arrSize;
	int layer = 0;
	int start, mid, last;
	Array* dividedArr;

	do
	{
		for each (object var in collection_to_loop)
		{

		}
	} while (maxSize > 1);*/
}

int* Merge(int* left, int leftSize, int* right, int rightSize) {
	int* ret = (int*)malloc(sizeof(int) * (leftSize + rightSize));
	int retIndex = 0;
	int leftIndex = 0;
	int rightIndex = 0;

	while ((leftIndex < leftSize) && (rightIndex < rightSize)) {
		if (left[leftIndex] > right[rightIndex]) {
			ret[retIndex++] = right[rightIndex++];
		}
		else {
			ret[retIndex++] = left[leftIndex++];
		}
	}

	if (leftIndex < leftSize) {
		while (leftIndex < leftSize) {
			ret[retIndex++] = left[leftIndex++];
		}
	}

	else if (rightIndex < rightSize) {
		while (rightIndex < rightSize) {
			ret[retIndex++] = right[rightIndex++];
		}
	}

	PrintArray(ret, leftSize + rightSize);
	ENDL;

	Free(left);
	Free(right);

	return ret;
}

void Free(int* arr) {
	if (arr != NULL) {
		free(arr);
		arr = NULL;
	}
	else return;
}