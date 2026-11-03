#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
    char name_money[25];
    int value;
    int PA;
}money;


money * ReadFromFile(int *n) {
    FILE *f;
    f = fopen("ATM.txt", "r");
    money *dslt;
    dslt = (money*)malloc(sizeof(money));
    int i = 0;
    while(!feof(f)) {
        fscanf(f, "%d %[^\n]", &dslt[i].value, dslt[i].name_money);
        dslt[i].PA = 0;
        i++;
        dslt = (money*)realloc(dslt, sizeof(money) * (i + 1));
    }
    *n = i;
    fclose(f);
    return dslt;
}

void ins(money* dslt, int n, int withdraw_money) {
    int i;
    int total_amount = 0;
    printf("|---|-------------------------|---------------|---------------|--------------------|\n");
    printf("|%-3s|%-25s|%-15s|%-15s|%-20s|\n", "STT", "Name of money", "Demomination", "Amount of money", "Total of money");
    printf("|---|-------------------------|---------------|---------------|--------------------|\n");
    for(i = 0; i < n; i++) {
        if(dslt[i].PA != 0) {
            printf("|%-3d|%-25s|%-15d|%-15d|%-20d|\n", i + 1, dslt[i].name_money, dslt[i].value, dslt[i].PA, dslt[i].value * dslt[i].PA);
            total_amount = total_amount + dslt[i].value * dslt[i].PA;
        }
        else {
            continue;
        }
    }
    printf("|---|-------------------------|---------------|---------------|--------------------|\n");
    printf("Amount of withdraw money = %9d\n", withdraw_money);
    printf("Amount of total money = %9d\n", total_amount);
}


void greedy(money *dslt, int n, int withdraw_money) {
    int i = n - 1;
    while(i >= 0 && withdraw_money > 0) {
        dslt[i].PA = withdraw_money / dslt[i].value;
        withdraw_money = withdraw_money - dslt[i].PA * dslt[i].value;
        i--;
    }
}

void swap(money *a, money *b) {
    money temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(money *a, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for(j = n - 1; j > i; j--) {
            if(a[j].value < a[j - 1].value) {
                swap(&a[j], &a[j - 1]);
            }
        }
    }
}

int main() {
    
    int n;
    money *dslt;
    dslt = ReadFromFile(&n);
    bubble_sort(dslt, n);

    int withdraw_money;
    printf("Enter the amount of money want to withdraw: ");
    scanf("%d", &withdraw_money);

    greedy(dslt, n, withdraw_money);

    ins(dslt, n, withdraw_money);
    free(dslt);
    return 0;
}