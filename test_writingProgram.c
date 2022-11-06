#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#pragma warning (disable : 4996)

typedef struct Lotto {
    char lotteryNum[50];
    char lotteryDate[50];
    struct Lotto* next;
    struct Lotto* prev;
}t_Lotto;

t_Lotto* head = NULL;
t_Lotto* tail = NULL;

void task1_splitString(char str[100]) {
    char splitA[100], splitB[100];
	int len, cut;
	int i, j;

    len = strlen(str);
    cut = len / 2;

    for (i = 0; i < cut; i++) {
        splitA[i] = str[i];
    }
    splitA[i] = '\0';

    for (i = cut, j = 0; i <= len; i++, j++) {
        splitB[j] = str[i];
    }

    printf("splitA = %s\nsplitB = %s\n", splitA, splitB);
}

void task2_reSplitString(char str[100]) {
    char splitA[100], splitB[100];
    int len, cut;
    int i, j;

    len = strlen(str);
    cut = len / 2;

    for (i = 0; i < cut; i++) {
        splitA[i] = str[i];
    }
    splitA[i] = '\0';

    for (i = cut, j = 0; i <= len; i++, j++) {
        splitB[j] = str[i];
    }

    printf("splitA = %s\n", splitA);
    if (splitA[0] != '\0')
    {
        task2_reSplitString(splitA);
    }
}

int task3_addTo100(int num) {
    printf("%d\n", num);
    return 100 != num ? task3_addTo100(num + 1): NULL;
}

void task4_freeLinkedList()
{
    t_Lotto* currentL = head;
    t_Lotto* releaseL;
    while (currentL != NULL)
    {
        releaseL = currentL;
        currentL = currentL->next;
        free(releaseL);
    }
}

void task4_addLotto(char lotteryNum[50], char lotteryDate[50]) {
    t_Lotto* currentI;
    currentI = (t_Lotto*)malloc(sizeof(t_Lotto));
    if (!currentI) {
        //error
        return;
    }
    strcpy(currentI->lotteryNum, lotteryNum);
    strcpy(currentI->lotteryDate, lotteryDate);
    currentI->next = NULL;
    if (!head) {
        currentI->prev = NULL;
        head = currentI;
        tail = currentI;
    }
    else{
        currentI->prev = tail;
        tail->next = currentI;
        tail = currentI;
    }
}

void task4_lotto() {
    FILE* f = fopen("Lotto.txt", "r");
    if (!f)
    {
        //error
    }
    else
    {
        char str[10000];
        fgets(str, 10000, f);
        while (fgets(str, 10000, f))
        {
            char lotteryNum[50];
            char lotteryDate[50];
            char* token;

            token = strtok(str, ",");
            strcpy(lotteryNum, token);
            token = strtok(NULL, ",");
            strcpy(lotteryDate, token);
            task4_addLotto(lotteryNum, lotteryDate);
        }
    }
}

t_Lotto* task4_Search(char lotteryNum[50])
{
    t_Lotto* currentL = head;
    if (!currentL)
    {
        return currentL;
    }
    while (strcmp(lotteryNum, currentL->lotteryNum))
    {
        currentL = currentL->next;
        if (currentL == NULL)
        {
            printf("\nlottery num does not excist\n\n");
            break;
        }
    }
    return currentL;
}

void task4_userResponse()
{
    task4_lotto();
    char ind;
    char lottoNum[50];
    t_Lotto* item;
    do
    {
        printf("\n*********MENU*********\n~ Type For Execution ~\nN.serach lottery by number.\nQ.Quit.");
        ind = getch();
        printf("\n\n");
        switch (ind)
        {
        case 'N':
            printf("please enter a LOTTERY NUMBER: ");
            gets(lottoNum);
            printf("\n\n");
            item = task4_Search(lottoNum);
            if (item) {
                printf("lottery number : %s\nlottery date : %s\n", item->lotteryNum, item->lotteryDate);
            }
            break;
        case 'Q':
            task4_freeLinkedList();
            printf("see u again soon ;)\n");
            break;
        default:
            printf("invalid key");
            printf("\n\n");
            break;
        }
    } while (ind != 'Q');
}



int main() {
	task1_splitString("akunna matata simba");
    task2_reSplitString("akunna matata simba");
    task3_addTo100(1);
    task4_userResponse();
	return 0;
}