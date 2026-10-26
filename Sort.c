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
    for(i = 1; i < n; i++) {
        j = i;
        while( j > 0 && a[j] < a[j - 1] ){
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
int findPivot(int a[], int i, int j) { // j = n - 1, return index, co the i la index dau 
    int k = i + 1; // tai sao k = i + 1 
    while(k <= j && a[k] == a[i]) { // k > j or a[k] != a[j]
        k++;
    }
    if (k > j) return -1;
    return a[k] > a[i] ? k : i; // Luu y: k compare i not j, j is the highly 
}

int partition(int a[], int i, int j, int Pivot) { // j = n - 1 // Tim L cho de cat
    int L = i;
    int R = j;

    while(L <= R) { // Phu dinh cua L > R 
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


// PushDown chi ap dung cho 2 truong hop 
// Tao heap ban dau
// first = n - 2 / 2
// last = n - 1 tui nghi chac rao bien thoi
// r = 1 
void PushDown(int a[], int first, int last) { // Ham k goi de quy cach viet cua co , tinh theo index 
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
            r = 2 * r + 1; // Doi vs ai pushdown tk do lai
        } 
        // 3. Nút r có đủ 2 con: Con phải nhỏ hơn con trái
        else if ((a[r] > a[2 * r + 2]) && (a[2 * r + 2] < a[2 * r + 1])) {
            swap(&a[r], &a[2 * r + 2]);
            r = 2 * r + 2; // Kieu nhu khi lam may tk nho nhu 0 1 2 xong phai nhay xuong kia coi no co heap k 
        } 
        // 4. Nút r đã nhỏ hơn cả 2 con -> Đúng vị trí rồi
        else {
            r = last; // Thoát vòng lặp
        }
    }
}

// Hinh thanh y tuong
// B1: Minh se coi thu trong 2 tk left vs right co ai nho hon tk first k;
// Th1: Co ==> Doi cho xong don gian chi can push down vao cho moi doi
// Th2: K ==> Thi se ngung 
void PushDown_1(int a[], int first, int last) {  // Cach khong su dung while khong hieu lam phai nghien cuu lai 
    int r = first;
    int smallest = r;
    int left = 2 * r + 1; // left = 9
    int right = 2 * r + 2; // right = 10 

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
        PushDown(a, i, n - 1); // Tai sao lau la n - 1, n - 1 la vi tri last nen no co the la th 1 hoac khong thi no se du 2 nhanh left va right cho de nhin va do pushdown c
                                // co viet se co last - 1 / 2 => r la tinh toi truong hop tron dau tien 
    }
    for(i = n - 1; i >= 2; i--) {
        swap(&a[0], &a[i]); 
        PushDown(a, 0, i - 1); // pushdown(a, 0, 1)
    }
    swap(&a[0], &a[1]); 
}


void merge(int a[], int left, int mid, int right) {
    int count = right - left + 1;

    int temp[count];
    int i = left;
    int j = mid + 1;
    int z = 0;
    while(i <= mid && j <= right) {
        if(a[i] < a[j]) {
            temp[z] = a[i];
            i++;
        }
        else {
            temp[z] = a[j];
            j++;
        }
        z++;
    }
    // 2. Vét phần tử còn thừa ở nửa trái (nếu nửa phải hết trước)
    while (i <= mid) {
        temp[z] = a[i];
        i++;
        z++;
    }

    // 3. Vét phần tử còn thừa ở nửa phải (nếu nửa trái hết trước)
    while (j <= right) {
        temp[z] = a[j];
        j++;
        z++;
    }

    // 4. Chép mảng tạm temp[] ngược lại mảng gốc a[] tại vị trí tương ứng
    for (int k = 0; k < count; k++) {
        a[left + k] = temp[k];
    }
}

/**
 * @brief Hàm đệ quy chia đôi mảng và sắp xếp
 */
void merge_sort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Tìm điểm giữa (tránh tràn số)

        // Chia để trị
        merge_sort(a, left, mid);      // Sắp xếp nửa bên trái
        merge_sort(a, mid + 1, right);  // Sắp xếp nửa bên phải

        // Trộn 2 nửa đã sắp xếp lại với nhau
        merge(a, left, mid, right);
    }
}

int main() {
    int a[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(a) / sizeof(a[0]);

    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
