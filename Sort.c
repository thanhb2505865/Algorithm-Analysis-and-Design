#include<stdio.h>


/*
 * @brief Swaps the values of two integer variables.
 * @param x Pointer to the first integer.
 * @param y Pointer to the second integer.

*/
void swap(int* x, int* y) { 
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
// SELECTION SORT //

 * @brief Sorts an array of integers in ascending order using the Selection Sort algorithm.
 * 
 * @details Time Complexity: O(n^2) in all cases (Best, Average, Worst).
 *          Space Complexity: O(1) auxiliary space (In-place sorting).
 * 
 * @param a The target array to be sorted.
 * @param n The total number of elements in the array.

*/
void selection_sort(int a[], int n) {    
    int i, j; // Loop counters for outer and inner iterations


    // Assume the current index 'i' holds the minimum element
    for(i = 0; i < n; i++) { 
        int index_lower = i;

        // Find the index of the minimum element in the remaining unsorted subarray
        for(j = i; j <= n -1; j++) {
            if(a[j] < a[index_lower]) { // Update index of the newly found minimum element
                index_lower = j;
            }
        }
        swap(&a[i], &a[index_lower]);
    }
}



/*
// INSERTION SORT //

*/


void insertion_sort(int a[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        j = i + 1;
        while(a[j] <= a[j - 1]  && j > 0 ){
            swap(&a[j - 1], &a[j]);
            j--;
        }
    }
}


void bubble_sort(int a[], int n) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = n - 1; j > i; j--) { // Notice: of if j >= i when j = i so j - 1 is number random(TAh viet nen co snytax is bad )
            if(a[j] < a[j-1]) {
                swap(&a[j], &a[j-1]);
            }
        }
    }
}


// Heap sort 
void push_down(int a[], int first, int last) { // Tai sao lai co first va last
    int r = first;

    while(r <= (last - 1) / 2) { // Dang lay cay trong 
        if(last == 2 * r + 1) { // last = cay con cua first 
            if(a[r] > a[last]) { // Goc lon nhanh trai 
                swap(&a[r], &a[last]); // TH1: doi cho 
                r = r - 1; //?? tai sao lai dat bien r bang last 
            }
            else {
                if((a[r] > a[2 * r + 1]) && (a[2 * r + 1] <= a[2 * r + 2])) {
                    swap(&a[r], &a[2 * r + 1]);
                    r = 2 * r + 1;  // ???????????
                }
                else {
                    if((a[2 * r + 1] > a[2 * r + 2] && (a[r] > a[2 * r + 2]))) {
                        swap(&a[r] ,&a[2 * r + 2]);
                        r = 2 * r + 2;
                    }
                }
            }
        }
        else {
            r = last;
        }
    }
}


void PushDown(int a[], int first, int last) {
    int r = first;

    while (r <= (last - 1) / 2) {
        // 1. Nút r chỉ có 1 con (con trái a[last])
        if (last == 2 * r + 1) {
            if (a[r] > a[last]) {
                Swap(&a[r], &a[last]);
            }
            r = last; // Cho r nhảy lên last để thoát vòng lặp
        } 
        // 2. Nút r có đủ 2 con: Con trái nhỏ hơn hoặc bằng con phải
        else if ((a[r] > a[2 * r + 1]) && (a[2 * r + 1] <= a[2 * r + 2])) {
            Swap(&a[r], &a[2 * r + 1]);
            r = 2 * r + 1;
        } 
        // 3. Nút r có đủ 2 con: Con phải nhỏ hơn con trái
        else if ((a[r] > a[2 * r + 2]) && (a[2 * r + 2] < a[2 * r + 1])) {
            Swap(&a[r], &a[2 * r + 2]);
            r = 2 * r + 2;
        } 
        // 4. Nút r đã nhỏ hơn cả 2 con -> Đúng vị trí rồi
        else {
            r = last; // Thoát vòng lặp
        }
    }
}
int main() {
    int a[10] = {42, 7, 15, 89, 3, 64, 21, 50, 12, 35};
    int n = 10;
    bubble_sort(a, n);

    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}