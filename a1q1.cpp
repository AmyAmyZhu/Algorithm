#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <cstdio>
#include <string>

using namespace std;

int merge_count(int arr[], int temp[], int left, int mid, int right){
    int i = left; // left
    int j = mid;  // mid
    int k = left; // right
    
    int count = 0;
    
    while(i <= mid-1 && j <= right){
        if(arr[i] <= arr[j]){
            temp[k] = arr[i];
            k++;
            i++;
        } else {
            temp[k] = arr[j];
            count = count + mid - i; // left greater than right, add count
            k++;
            j++;
        }
    }
    
    while (i <= mid-1) {
        temp[k] = arr[i];
        k++;
        i++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        k++;
        j++;
    }
    for(int m=left; m <= right; m++){
        arr[m] = temp[m];
    }
    return count;
}

// regular merge sort, instead we have count to count how many inversions
int merge_sort(int arr[], int temp[], int left, int right){
    int mid = 0;
    int count = 0; // count inversions
    if(right > left){
        mid = (right+left)/2;
        count = merge_sort(arr, temp, left, mid);
        count += merge_sort(arr, temp, mid+1, right);
        count += merge_count(arr, temp, left, mid+1, right);
    }
    return count;
}

int main(){
    int i,k;
    int size = 0;
    
    stringstream ss;
    // get the size of array, and store all integers into ss
    while (cin >> i) {
        size++;
        ss << i << ' ';
    }
    
    int *arr = new int[size];
    int *temp = new int[size];
    // store all integers from ss into array
    for(int l = 0; l < size; l++){
        ss >> k;
        arr[l] = k;
    }
    
    cout << merge_sort(arr, temp, 0, size-1) << endl;
    delete[] arr;
}

