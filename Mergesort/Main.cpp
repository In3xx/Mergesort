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
void Divide_1(Array*, int*, int);
void Divide_2(Array*, int*, int);
void Sort(int*, int*, int, int*, int);
void Merge_1(Array*, int);
void Merge_2(Array*, int);


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

	Divide_2(retStruct, arr, arrSize);

	//Merge_1(retStruct, arrSize);

	return 0;
}

void PrintArray(int* arr, int arrSize) {
	printf("[ ");
	for (int i = 0; i < arrSize; i++)
		printf("%d ", arr[i]);
	printf("]");
}

void Divide_1(Array* retStruct, int* arr, int arrSize) {
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
				int leftSize = retStruct[i].size / 2 + retStruct[i].size % 2;
				int rightSize = retStruct[i].size / 2;

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
				//maxSize 설정
				maxSize = 0;
				for (int i = 0; i < arrSize; i++)
					if (maxSize < retStruct[i].size)
						maxSize = retStruct[i].size;
				//출력
				count++;
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

void Divide_2(Array* retStruct, int* arr, int arrSize) {
	PrintArray(arr, arrSize);
	ENDL;
	int layerSize = 1;
	//retStruct에 arr삽입
	retStruct[0].arr = (int*)malloc(sizeof(int) * arrSize);
	retStruct[0].size = arrSize;
	for (int i = 0; i < arrSize; i++)
		retStruct[0].arr[i] = arr[i];
	//Free arr
	FREE(arr);

	do
	{
		Array* temp = (Array*)malloc(sizeof(Array) * layerSize * 2);
		for (int i = 0, x = 0; i < layerSize; i++, x += 2) {
			if (retStruct[i].size == 1) {
				temp[x--] = retStruct[i];
				continue;
			}
			//retStruct으로 부터 왼쪽임시
			int leftSize = retStruct[i].size / 2 + retStruct[i].size % 2;
			int* left = (int*)malloc(sizeof(int) * leftSize);
			for (int j = 0; j < leftSize; j++)
				left[j] = retStruct[i].arr[j];

			//retStruct으로 부터 오른쪽임시
			int rightSize = retStruct[i].size / 2;
			int* right = (int*)malloc(sizeof(int) * rightSize);
			for (int j = 0; j < rightSize; j++)
				right[j] = retStruct[i].arr[j + leftSize];

			//왼쪽 temp 삽입
			temp[x].arr = (int*)malloc(sizeof(int) * leftSize);
			for (int j = 0; j < leftSize; j++)
				temp[x].arr[j] = left[j];
			temp[x].size = leftSize;
			
			//오른쪽 temp 삽입
			temp[x + 1].arr = (int*)malloc(sizeof(int) * rightSize);
			for (int j = 0; j < rightSize; j++)
				temp[x + 1].arr[j] = right[j];
			temp[x + 1].size = rightSize;
			
			//Free left, right
			FREE(left);
			FREE(right);
		}
		layerSize *= 2;
		//retStruct <- temp 삽입
		for (int i = 0; i < arrSize; i++)
			retStruct[i] = temp[i];
		//Free temp
		FREE(temp);
		for (int i = 0; i < layerSize; i++) {
			if (i < arrSize)
				PrintArray(retStruct[i].arr, retStruct[i].size);
			else break;
		}
		ENDL;

	} while (layerSize < arrSize);
}

void Sort(int* ret, int* left, int leftSize, int* right, int rightSize) {
	int retIndex = 0;
	int leftIndex = 0;
	int rightIndex = 0;
	//작은것들부터 하나씩 비교하며 채워넣기
	while ((leftIndex < leftSize) && (rightIndex < rightSize)) {
		if (left[leftIndex] > right[rightIndex]) {
			ret[retIndex++] = right[rightIndex++];
		}
		else {
			ret[retIndex++] = left[leftIndex++];
		}
	}
	//왼쪽의 남은것들을 채워넣기
	if (leftIndex < leftSize) {
		while (leftIndex < leftSize) {
			ret[retIndex++] = left[leftIndex++];
		}
	}
	//오른쪽의 남은것들을 채워넣기
	else if (rightIndex < rightSize) {
		while (rightIndex < rightSize) {
			ret[retIndex++] = right[rightIndex++];
		}
	}
}

void Merge_1(Array* dividedArr, int arrSize)
{
	int divideSize = arrSize;
	do
	{
		//홀수 플래그
		bool flag = divideSize % 2;
		divideSize = divideSize / 2 + divideSize % 2;
		//임시로 저장시킬 구조체
		Array* temp = (Array*)malloc(sizeof(Array) * divideSize);
		for (int i = 0, j = 0; i < divideSize; i++, j += 2) {
			temp[i].arr = (int*)malloc(sizeof(int) * (dividedArr[j].size + dividedArr[j + 1].size));
			temp[i].size = dividedArr[j].size + dividedArr[j + 1].size;
			//마지막 인덱스가 홀수 일때는 그냥 추가
			if (i == divideSize - 1)
				if (flag) {
					temp[i].arr = (int*)malloc(sizeof(int) * (dividedArr[j].size));
					temp[i].size = dividedArr[j].size;
					temp[i] = dividedArr[j];
					break;
				}
			Sort(temp[i].arr, dividedArr[j].arr, dividedArr[j].size, dividedArr[j + 1].arr, dividedArr[j + 1].size);
			
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

void Merge_2(Array* retStruct, int arrSize)
{
	int layerCnt = 1;
	int printLayer = 1;
	while ((printLayer << 1) < arrSize)
	{
		layerCnt++;
		printLayer *= 2;
	}
	int rest = arrSize % layerCnt;

	do
	{
		/*int mergeCnt = arrSize - printLayer;

		Array* temp = (Array*)malloc(sizeof(Array) * printLayer);*/

		
	} while (true);
}