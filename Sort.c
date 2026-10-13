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


// Quick sort 
int findPivot(int a[], int i, int j) { // j = n - 1, return index
    int k = i + 1;
    while(k <= j && a[k] == a[j]) {
        k++;
    }
    if (k > j) return -1;
    return a[k] > a[i] ? k : i; // Luu y: k compare i not j, j is the highly 
}

int partition(int a[], int i, int j, int Pivot) {
    int L = i;
    int R = j;

    while(L <= R) {
        while(a[L] < a[Pivot]) L++;
        while(a[R] >= a[Pivot]) R--;
        if(L <= R) swap(&a[L], &a[R]);
    }
    return L;
}

void quick_sort(int a[], int i, int j, int Pivot) {
    int temp = findPivot(a, i, j);
    if(temp != -1) {
        int k = partition(a, i, j, temp);
        quick_sort(a, i, k - 1, findPivot(a, i, k - 1));
        quick_sort(a, k, j, findPivot(a, k, j));
    }
}
// Heap sort 
void PushDown(int a[], int first, int last) {
    int r = first;

    while (r <= (last - 1) / 2) {
        // 1. Nút r chỉ có 1 con (con trái a[last])
        if (last == 2 * r + 1) {
            if (a[r] > a[last]) {
                swap(&a[r], &a[last]);
            }
            r = last; // Cho r nhảy lên last để thoát vòng lặp
        } 
        // 2. Nút r có đủ 2 con: Con trái nhỏ hơn hoặc bằng con phải
        else if ((a[r] > a[2 * r + 1]) && (a[2 * r + 1] <= a[2 * r + 2])) {
            swap(&a[r], &a[2 * r + 1]);
            r = 2 * r + 1;
        } 
        // 3. Nút r có đủ 2 con: Con phải nhỏ hơn con trái
        else if ((a[r] > a[2 * r + 2]) && (a[2 * r + 2] < a[2 * r + 1])) {
            swap(&a[r], &a[2 * r + 2]);
            r = 2 * r + 2; // Chia ra 2 truong hop 1:neu nhu r = First du lon thi no se chay nguoc ve 0 khi no se vang 
                            // TH2: Neu nhu r nho chay tu 0 thi no se day r len, tui van chua hinh dung duoc no se chay sao
        } 
        // 4. Nút r đã nhỏ hơn cả 2 con -> Đúng vị trí rồi
        else {
            r = last; // Thoát vòng lặp
        }
    }
}

// Hinh thanh y tuong
// B1: 
void PushDown_1(int a[], int first, int last) {  // Cach khong su dung while khong hieu lam phai nghien cuu lai 
    int r = first;
    int smallest = r;
    int left = 2 * r + 1;
    int right = 2 * r + 2;

    // 1. So sánh với con trái (nếu con trái nằm trong phạm vi last)
    if (left <= last && a[left] < a[smallest]) {
        smallest = left;
    }

    // 2. So sánh với con phải (nếu con phải nằm trong phạm vi last)
    if (right <= last && a[right] < a[smallest]) {
        smallest = right;
    }

    // 3. Nếu nút r KHÔNG PHẢI là nhỏ nhất -> Swap và ĐỆ QUY chìm tiếp
    if (smallest != r) {
        swap(&a[r], &a[smallest]);
        
        // TỰ GỌI LẠI CHÍNH NÓ (thay thế hoàn toàn cho vòng lặp while)
        PushDown(a, smallest, last); 
    }
    // Nếu smallest == r thì hàm tự kết thúc (điều kiện dừng đệ quy)
}

void HeapSort(int a[], int n) {
    int i;
    for(i = (n - 2) / 2; i >= 0; i--) {
        PushDown(a, i, n - 1); // Tai sao lau la n - 1
    }
    for(i = n - 1; i >= 2; i--) {
        swap(&a[0], &a[i]);
        PushDown(a, 0, i - 1);
    }
    swap(&a[0], &a[i]);
}


int main() {
    int a[7] = {99, 10, 20, 3, 5, 12, 15};
    quick_sort(a, 0, 7, findPivot(a, 0, 7));
    int i;
    for(i = 0; i < 7; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}