#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <time.h>

using namespace std;

#define endl		cout << endl
#define FREE(ptr)	{if(ptr){free(ptr); ptr = nullptr;}}
#define check		printf("Check\n")

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
void Binary(int*, int);


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

	//����ü ����
	//Array* retStruct = (Array*)malloc(sizeof(Array) * arrSize);
	//
	//Divide_2(retStruct, arr, arrSize);
	//
	//Merge_2(retStruct, arrSize);
	//Merge_1(retStruct, arrSize);

	Binary(arr, arrSize);

	return 0;
}

void PrintArray(int* arr, int arrSize) {
	printf("[ ");
	for (int i = 0; i < arrSize; i++)
		printf("%d ", arr[i]);
	printf("] ");
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
	endl;

	do
	{
		for (int i = 0; i < arrSize; i++)
		{
			//���� ū�迭���� �̺���
			if (retStruct[i].size >= maxSize && maxSize > 1) {
				//left, right ������ ����
				int leftSize = retStruct[i].size / 2 + retStruct[i].size % 2;
				int rightSize = retStruct[i].size / 2;

				//left, right �ӽ� �Ҵ�
				int* left = (int*)malloc(sizeof(int) * leftSize);
				int* right = (int*)malloc(sizeof(int) * rightSize);

				//left, right ���Ұ� �ֱ�
				for (int j = 0; j < retStruct[i].size; j++)
				{
					if (j < leftSize)
						left[j] = retStruct[i].arr[j];
					else
						right[j - leftSize] = retStruct[i].arr[j];
				}

				//�θ�迭 �Ҵ�����
				FREE(retStruct[i].arr);
				retStruct[i].size = 0;

				//left����
				retStruct[i].arr = (int*)malloc(sizeof(int) * leftSize);
				retStruct[i].size = leftSize;
				for (int j = 0; j < retStruct[i].size; j++) {
					retStruct[i].arr[j] = left[j];
				}

				//right����
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
				//maxSize ����
				maxSize = 0;
				for (int i = 0; i < arrSize; i++)
					if (maxSize < retStruct[i].size)
						maxSize = retStruct[i].size;
				//���
				count++;
				if (count == printLayer || maxSize == 1) {
					count = 0;
					printLayer *= 2;
					for (int k = 0; k < printLayer; k++)
					{
						if (k >= arrSize)	break;
						PrintArray(retStruct[k].arr, retStruct[k].size);
					}
					endl;
				}
				break;
			}
		}
	} while (maxSize > 1);
}

void Divide_2(Array* retStruct, int* arr, int arrSize) {
	PrintArray(arr, arrSize);
	endl;
	int layerSize = 1;
	//retStruct�� arr����
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
			//retStruct���� ���� �����ӽ�
			int leftSize = retStruct[i].size / 2 + retStruct[i].size % 2;
			int* left = (int*)malloc(sizeof(int) * leftSize);
			for (int j = 0; j < leftSize; j++)
				left[j] = retStruct[i].arr[j];

			//retStruct���� ���� �������ӽ�
			int rightSize = retStruct[i].size / 2;
			int* right = (int*)malloc(sizeof(int) * rightSize);
			for (int j = 0; j < rightSize; j++)
				right[j] = retStruct[i].arr[j + leftSize];

			//���� temp ����
			temp[x].arr = (int*)malloc(sizeof(int) * leftSize);
			for (int j = 0; j < leftSize; j++)
				temp[x].arr[j] = left[j];
			temp[x].size = leftSize;
			
			//������ temp ����
			temp[x + 1].arr = (int*)malloc(sizeof(int) * rightSize);
			for (int j = 0; j < rightSize; j++)
				temp[x + 1].arr[j] = right[j];
			temp[x + 1].size = rightSize;
			
			//Free left, right
			FREE(left);
			FREE(right);
		}
		layerSize *= 2;
		//retStruct <- temp ����
		for (int i = 0; i < arrSize; i++)
			retStruct[i] = temp[i];
		//Free temp
		FREE(temp);
		for (int i = 0; i < layerSize; i++) {
			if (i < arrSize)
				PrintArray(retStruct[i].arr, retStruct[i].size);
			else break;
		}
		endl;

	} while (layerSize < arrSize);
}

void Sort(int* ret, int* left, int leftSize, int* right, int rightSize) {
	int retIndex = 0;
	int leftIndex = 0;
	int rightIndex = 0;
	//�����͵���� �ϳ��� ���ϸ� ä���ֱ�
	while ((leftIndex < leftSize) && (rightIndex < rightSize)) {
		if (left[leftIndex] > right[rightIndex]) {
			ret[retIndex++] = right[rightIndex++];
		}
		else {
			ret[retIndex++] = left[leftIndex++];
		}
	}
	//������ �����͵��� ä���ֱ�
	if (leftIndex < leftSize) {
		while (leftIndex < leftSize) {
			ret[retIndex++] = left[leftIndex++];
		}
	}
	//�������� �����͵��� ä���ֱ�
	else if (rightIndex < rightSize) {
		while (rightIndex < rightSize) {
			ret[retIndex++] = right[rightIndex++];
		}
	}
}

void Merge_1(Array* retStruct, int arrSize)
{
	int tempSize = 1;	//temp ����ü ������
	while ((tempSize << 1) < arrSize)
	{
		tempSize *= 2;
	}
	do
	{
		tempSize /= 2;
		//�ӽ÷� �����ų ����ü
		Array* temp = (Array*)malloc(sizeof(Array) * tempSize);
		for (int i = 0, j = 0; i < tempSize; i++, j += 2) {
			temp[i].arr = (int*)malloc(sizeof(int) * (retStruct[j].size + retStruct[j + 1].size));
			temp[i].size = retStruct[j].size + retStruct[j + 1].size;
			Sort(temp[i].arr, retStruct[j].arr, retStruct[j].size, retStruct[j + 1].arr, retStruct[j + 1].size);			
		}
		for (int i = 0; i < arrSize; i++) {
			if(i < tempSize)
				retStruct[i] = temp[i];
			else {
				retStruct[i].arr = nullptr;
				retStruct[i].size = 0;
			}
		}
		FREE(temp);
		for (int i = 0; i < tempSize; i++)
		{
			PrintArray(retStruct[i].arr, retStruct[i].size);
		}
		endl;
	} while (tempSize > 1);

}

void Merge_2(Array* retStruct, int arrSize)
{
	int layer = 1;	//2^N
	int tempSize = 1;	//temp ����ü ������
	int cnt = 0;		//inx�� ī��Ʈ
	int x_cnt = 0;		//x8 �� ī��Ʈ
	//arrSize ������ 
	while ((layer << 1) < arrSize)
	{
		layer *= 2;		//��ȭ��
		tempSize *= 2;		//������
	}
	int inx = arrSize - tempSize;//**�߿䰪**

	Array* temp = (Array*)malloc(sizeof(Array) * tempSize);
	for (int i = 0; i < tempSize; i++)
		temp[i].size = 1;

	if (inx > 0)
	{
		int x_cnt = 1;
		temp[0].size = 2;
		cnt++;
		while (inx > cnt)
		{
			//���̳ʸ� �迭�ϳ� �޾Ƽ� �װ��� �ε����� �������� �����ϱ�(���ݰ� ����)
			if (cnt == tempSize / 2) {
				layer = tempSize;
				x_cnt = 1;
				temp[1].size = 2;
				cnt++;
				continue;
			}
			layer /= 2;
			for (int i = 0; i < x_cnt; i++)
			{
					for (int j = layer + i * (tempSize / 4); j < tempSize; j += tempSize / 2)
					{
						if (inx > cnt) {
							if (temp[j].size == 2)
								continue;
							temp[j].size = 2;
							cnt++;
							if (cnt > tempSize / 2) {
								if (temp[j + 1].size == 2)
									continue;
								temp[j + 1].size = 2;
								cnt++;
							}
						}
						else break;
					}				
			}
			x_cnt += 2;
		}
	}
	//temp����� ���� ����
	for (int i = 0, i_cnt = 0 ; i < tempSize; i++)
	{
		temp[i].arr = (int*)malloc(sizeof(int) * temp[i].size);
		
		for (int j = 0; j < temp[i].size; j++)
		{
			if (temp[i].size > 1) {
				Sort(temp[i].arr, retStruct[i_cnt].arr, retStruct[i_cnt].size, retStruct[i_cnt + 1].arr, retStruct[i_cnt + 1].size);
				i_cnt += 2;
				break;
			}
			else temp[i].arr[j] = retStruct[i_cnt++].arr[0];
		}
	}

	//�ٽ� retStruct�� ����
	for (int i = 0; i < arrSize; i++)
	{
		if (i < tempSize) {
			for (int j = 0; j < temp[i].size; j++)
			{
				retStruct[i].arr[j] = temp[i].arr[j];
				retStruct[i].size = temp[i].size;
			}
			//FREE temp->arr
			FREE(temp[i].arr);
		}
		else{
			FREE(retStruct[i].arr);
			retStruct[i].size = 0;
		}
	}
	for (int i = 0; i < tempSize; i++)
	{
		PrintArray(retStruct[i].arr, retStruct[i].size);
	}
	endl;
	//free temp
	FREE(temp);
}

void Binary(int* ret, int arrSize) {
	int layerCnt = 1;
	int even = 0;
	for (int i = 0; i < arrSize; i++)
	{
		ret[i] = 0;
	}
	do
	{
		int minimum = 0;
		int cnt = 0;
		do
		{
			for (int i = 0; i < layerCnt; i++)
			{
				if (ret[i] == minimum) {
					if (layerCnt == 1) {
						even += 2;
						minimum += 2;
						cnt++;
						break;
					}
					else
					{
						for (int j = arrSize - 2; j >= i + 1; j--)
						{
							ret[j + 1] = ret[j];
						}
						ret[i + 1] = even;
						even += 2;
						minimum += 2;
						cnt++;
					}
				}
			}
		} while (cnt < layerCnt);
		PrintArray(ret, arrSize);
		endl;
		layerCnt *= 2;
	} while (even < arrSize);
}

void Binary(int* ret, int arrSize) {
	
	int layer = 1;			//layer
	int tempCnt = 0;		//�߰��ɿ����ǰ���
	int even = 0;			//�þ ¦��

	//ret �迭 �ʱ�ȭ
	for (int i = 0; i < arrSize; i++)
		ret[i] = 0;
	
	do
	{
		int minimum = 0;
		int cnt = 0;
		do
		{
			if (layer == 1) {
				layer *= 2;
				even += 2;
				break;
			}
			for (int i = 0; i < layer; i++)
			{
				if (ret[i] <= minimum) {
					for (int j = arrSize - 2; j >= i + 1; j--)
					{
						ret[j + 1] = ret[j];
					}
					ret[i + 1] = even;
					even += 2;
					minimum += 2;
					i++;
					//�̺κ� while ����� ���� ��������
				}
			}
		} while (true);
	} while (true);
}