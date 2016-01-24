#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct point{
    int x, y;
};


int merge_count(point Px[], point temp[], int left, int mid, int right){
    int i = left; // left
    int j = mid;  // mid
    int k = left; // right
    
    int count = 0;
    
    while(i <= mid-1 && j <= right){
        if((Px[i].y <= Px[j].y) || (Px[i].x == Px[j].x)){
            temp[k].x = Px[i].x;
            temp[k].y = Px[i].y;
            k++;
            i++;
        } else {
            temp[k].x = Px[j].x;
            temp[k].y = Px[j].y;
            count = count + mid - i; // left greater than right, add count
            k++;
            j++;
        }
    }
    
    while (i <= mid-1) {
        temp[k].x = Px[i].x;
        temp[k].y = Px[i].y;
        k++;
        i++;
    }
    while (j <= right) {
        temp[k].x = Px[j].x;
        temp[k].y = Px[j].y;
        k++;
        j++;
    }
    for(int m=left; m <= right; m++){
        Px[m].x = temp[m].x;
        Px[m].y = Px[m].y;
    }
    return count;
}

int merge_sort(point Px[], point temp[], int left, int right){
    int mid = 0;
    int count = 0;
    if(right > left){
        mid = (right+left)/2;
        count = merge_sort(Px, temp, left, mid);
        count += merge_sort(Px, temp, mid+1, right);
        count += merge_count(Px, temp, left, mid+1, right);
    }
    return count;
}

/*qsort for x*/
int compareX(const void *a, const void *b){
    point *p1 = (point *)a;
    point *p2 = (point *)b;
    return (p1->x - p2->x);
}

int incomparable(point set[], int n){
    point Px[n];
    point temp[n];
    
    for(int i = 0; i < n; i++){
        Px[i] = set[i];
    }
    
    qsort(Px, n, sizeof(point), compareX);
    return merge_sort(Px, temp, 0, n-1);
}

int main(){
    point set[] = {{2,3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    int n = sizeof(set)/sizeof(set[0]);
    cout << "The number of incomparable pairs is " << incomparable(set, n) << endl;
}
