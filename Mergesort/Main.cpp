#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

#define ENDL		cout << endl
#define FREE(ptr)	{if(ptr){free(ptr); ptr = nullptr;}}
#define CHECK		printf("Check\n")

struct Array
{
	int size = 0;
	int* arr = nullptr;
};

void PrintArray(int*, int);
void Divide(Array*, int*, int);
void Sort(int*, int*, int, int*, int);
void Merge(Array*, int);


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

	//구조체 선언
	Array* retStruct = (Array*)malloc(sizeof(Array) * arrSize);

	Divide(retStruct, arr, arrSize);

	Merge(retStruct, arrSize);

	return 0;
}

void PrintArray(int* arr, int arrSize) {
	printf("[ ");
	for (int i = 0; i < arrSize; i++)
		printf("%d ", arr[i]);
	printf("] ");
}

void Divide(Array* retStruct, int* arr, int arrSize) {
	int maxSize = arrSize;
	int printLayer = 1;
	int count = 0;

	retStruct[0].arr = (int*)malloc(sizeof(int) * arrSize);	
	for (int i = 0; i < arrSize; i++)
	{
		retStruct[0].size = arrSize;
		retStruct[0].arr[i] = arr[i];
	}
	FREE(arr);

	PrintArray(retStruct[0].arr, retStruct[0].size);
	ENDL;

	do
	{
		for (int i = 0; i < arrSize; i++)
		{
			//제일 큰배열부터 이분할
			if (retStruct[i].size >= maxSize && maxSize > 1) {
				//left, right 사이즈 설정
				int leftSize = retStruct[i].size / 2;
				int rightSize = retStruct[i].size / 2 + retStruct[i].size % 2;

				//left, right 임시 할당
				int* left = (int*)malloc(sizeof(int) * leftSize);
				int* right = (int*)malloc(sizeof(int) * rightSize);

				//left, right 원소값 넣기
				for (int j = 0; j < retStruct[i].size; j++)
				{
					if (j < leftSize)
						left[j] = retStruct[i].arr[j];
					else
						right[j - leftSize] = retStruct[i].arr[j];
				}

				//부모배열 할당해제
				FREE(retStruct[i].arr);
				retStruct[i].size = 0;

				//left삽입
				retStruct[i].arr = (int*)malloc(sizeof(int) * leftSize);
				retStruct[i].size = leftSize;
				for (int j = 0; j < retStruct[i].size; j++) {
					retStruct[i].arr[j] = left[j];
				}

				//right삽입
				if (retStruct[i + 1].arr == nullptr) {
					retStruct[i + 1].arr = (int*)malloc(sizeof(int) * rightSize);
					retStruct[i + 1].size = rightSize;
					for (int j = 0; j < retStruct[i + 1].size; j++) {
						retStruct[i + 1].arr[j] = right[j];
					}
				}
				else {
					for (int j = arrSize - 1; j > i + 1 ; j--)
					{
						retStruct[j] = retStruct[j - 1];
					}
					retStruct[i + 1].arr = (int*)malloc(sizeof(int) * rightSize);
					retStruct[i + 1].size = rightSize;
					for (int j = 0; j < retStruct[i + 1].size; j++) {
						retStruct[i + 1].arr[j] = right[j];
					}
				}
				FREE(left);
				FREE(right);
				count++;
				//maxSize 설정
				maxSize = 0;
				for (int i = 0; i < arrSize; i++)
					if (maxSize < retStruct[i].size)
						maxSize = retStruct[i].size;
				//출력
				if (count == printLayer || maxSize == 1) {
					count = 0;
					printLayer *= 2;
					for (int k = 0; k < printLayer; k++)
					{
						if (k >= arrSize)	break;
						PrintArray(retStruct[k].arr, retStruct[k].size);
					}
					ENDL;
				}
				break;
			}
		}
	} while (maxSize > 1);
}

void Sort(int* ret, int* left, int leftSize, int* right, int rightSize) {
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
}

void Merge(Array* dividedArr, int arrSize)
{
	int divideSize = arrSize;
	do
	{
		bool flag = divideSize % 2;
		divideSize = divideSize / 2 + divideSize % 2;
		Array* temp = (Array*)malloc(sizeof(Array) * divideSize);
		for (int i = 0, j = 0; i < divideSize; i++, j += 2) {
			temp[i].arr = (int*)malloc(sizeof(int) * (dividedArr[j].size + dividedArr[j + 1].size));
			temp[i].size = dividedArr[j].size + dividedArr[j + 1].size;
			Sort(temp[i].arr, dividedArr[j].arr, dividedArr[j].size, dividedArr[j + 1].arr, dividedArr[j + 1].size);
			if (i == divideSize - 1) 
				if (flag) {
					temp[i].arr = (int*)malloc(sizeof(int) * (dividedArr[j].size));
					temp[i].size = dividedArr[j].size;
					temp[i] = dividedArr[j];
				}					
		}
		for (int i = 0; i < arrSize; i++) {
			if(i < divideSize)
				dividedArr[i] = temp[i];
			else {
				dividedArr[i].arr = nullptr;
				dividedArr[i].size = 0;
			}
		}
		for (int i = 0; i < divideSize; i++)
		{
			PrintArray(dividedArr[i].arr, dividedArr[i].size);
		}
		ENDL;
		FREE(temp);
	} while (divideSize > 1);

}
