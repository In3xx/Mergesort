#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

#define ENDL		cout << endl
#define FREE(ptr)	{if(ptr){free(ptr); ptr = nullptr;}}

void PrintArray(int*, int);
void Divide(int*, int);
int* Merge(int*, int, int*, int);

struct Array
{
	int size = 0;
	int* arr = nullptr;
};

int main() {
	int arrSize;
	int maxValue;

	cout << "Array Size : ";
	cin >> arrSize;
	cout << "Max value : ";
	cin >> maxValue;

	srand((unsigned int)time(nullptr));
	int* arr = (int*)malloc(sizeof(int) * arrSize);

	for (int i = 0; i < arrSize; i++)
		*(arr + i) = (rand() % maxValue + 1);

	//PrintArray(arr, arrSize);
	//ENDL;

	Divide(arr, arrSize);

	return 0;
}

void PrintArray(int* arr, int arrSize) {
	for (int i = 0; i < arrSize; i++)
		cout << *(arr + i) << " ";
	cout << "\t";
}

void Divide(int* arr, int arrSize) {
	int maxSize = arrSize;
	int printLayer = 1;
	int count = 0;

	//구조체 선언
	Array* dividedArr = (Array*)malloc(sizeof(struct Array) * arrSize);
	dividedArr[0].arr = (int*)malloc(sizeof(int) * arrSize);
	
	for (int i = 0; i < arrSize; i++)
	{
		dividedArr[0].size = arrSize;
		dividedArr[0].arr[i] = arr[i];
	}
	FREE(arr);

	PrintArray(dividedArr[0].arr, dividedArr[0].size);
	ENDL;

	do
	{
		for (int i = 0; i < arrSize; i++)
		{
			//제일 큰배열부터 이분할
			if (dividedArr[i].size >= maxSize) {
				//left, right 사이즈 설정
				int leftSize = dividedArr[i].size / 2;
				int rightSize = dividedArr[i].size / 2 + dividedArr[i].size % 2;

				//left, right 임시 할당
				int* left = (int*)malloc(sizeof(int) * leftSize);
				int* right = (int*)malloc(sizeof(int) * rightSize);

				//left, right 원소값 넣기
				for (int k = 0; k < dividedArr[i].size; k++)
				{
					if (k < leftSize)
						left[k] = dividedArr[i].arr[k];
					else
						right[k - leftSize] = dividedArr[i].arr[k];
				}
				//임시출력
				/*for (int l = 0; l < dividedArr[i].size; l++)
				{
					printf("LEFT(%d)  ", left[l]);
					printf("RIGHT(%d)\n", right[l]);
				}*/

				//부모배열 할당해제
				FREE(dividedArr[i].arr);
				dividedArr[i].size = 0;

				//left, right를 두 자리씩 넣기
				for (int j = i; j < arrSize - 1; j++)
				{
					//left
					dividedArr[j].arr = (int*)malloc(sizeof(int) * leftSize);
					dividedArr[j].size = leftSize;
					for (int x = 0; x < dividedArr[j].size; x++) {
						dividedArr[j].arr[x] = left[x];
					}

					//right
					if (dividedArr[j + 1].arr == nullptr) {
						dividedArr[j + 1].arr = (int*)malloc(sizeof(int) * rightSize);
						dividedArr[j + 1].size = rightSize;
						for (int x = 0; x < dividedArr[j + 1].size; x++) {
							dividedArr[j + 1].arr[x] = left[x];
						}
					}
					else {
						for (int u = arrSize - 1; u >= j + 1; u--)
						{
							dividedArr[u + 1] = dividedArr[u];
						}
						dividedArr[j + 1].arr = (int*)malloc(sizeof(int) * rightSize);
						dividedArr[j + 1].size = rightSize;
						for (int x = 0; x < dividedArr[j + 1].size; x++) {
							dividedArr[j + 1].arr[x] = left[x];
						}
					}
				}
				FREE(left);
				FREE(right);
				count++;
				//출력
				if (count == printLayer || count == arrSize) {
					count = 0;
					printLayer *= 2;
					for (int i = 0; i < printLayer; i++)
					{
						if (i < arrSize) {
							printf("[ ");
							for (int j = 0; j < dividedArr[i].size; j++)
								printf("%d ", dividedArr[i].arr[j]);
							printf("] ");
						}
						else break;
					}
					ENDL;
				}
				//maxSize 설정
				maxSize = 0;
				for (int i = 0; i < arrSize; i++)
					if (maxSize < dividedArr[i].size)
						maxSize = dividedArr[i].size;
			}
		}
	} while (maxSize > 1);
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

	FREE(left);
	FREE(right);

	return ret;
}