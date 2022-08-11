#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stack>
#include <ctime>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include<vector>
#include <fstream>
#include <limits>
using namespace std;


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::vector<int> bubbleSort(vector<int> arr){
    for (int i = 0; i < arr.size(); i++){
        bool swapFlag = false;
        for (int j = 1; j < arr.size()-i; j++){
            if (arr[j-1]>arr[j]){
                swap(arr[j], arr[j-1]);
                swapFlag = true;
            }
        }
        if (swapFlag == false){
            break;
        }
    }
    return arr;
}

vector<int> combSort(vector<int> arr){
    double factor = 1.2473309;
    for (int k = arr.size() - 1; k >= 1; k = int(k / factor)){
        for (int j = 0; j + k < arr.size(); j++){
            if (arr[j + k] < arr [j]){
                swap(arr[j], arr[j + k]);
            }
        }
    }
    return arr;
}

vector<int> cocktailSort(vector<int> arr){
    for (int i = 0; i < arr.size() / 2; i++){
        bool swapFlag = false;
        for (int j = 1 + i; j < arr.size()-i; j++){
            if (arr[j-1] > arr[j]){
                std::swap(arr[j], arr[j-1]);
                swapFlag = true;
            }
        }
        if (swapFlag == false){
            break;
        }
        swapFlag = false;
        for (int j = arr.size() - 2 - i; j > i; j--){
            if (arr[j - 1] > arr[j]){
                swap(arr[j], arr[j-1]);
                swapFlag = true;
            }
        }
        if (swapFlag == false){
            break;
        }
    }
    return arr;
}

void insertionSort(vector<int> arr, int n)
{
	int i, j;
	int key;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}


vector<int> ShellSort(vector<int> arr, int size)
{
	int step, i, j;
	int tmp;

	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
			for (j = i - step; j >= 0 && arr[j] > arr[j + step]; j -= step)
			{
				tmp = arr[j];
				arr[j] = arr[j + step];
				arr[j + step] = tmp;
			}
	return arr;
}

int main()
{

}