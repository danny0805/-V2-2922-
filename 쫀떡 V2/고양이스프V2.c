// 야옹이와 수프 v2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef struct {
    int mood;       // 0~3
    int affinity;   // 0~4
    int soupCount;
} Cat;

void updateMood(Cat* cat);
int produceCP(Cat* cat);
void printStatus(Cat* cat);
void interaction(Cat* cat, int action, int hasMouse, int hasLaser);
void shopMenu(int* cp, int* hasMouse, int* hasLaser);
void triggerQuest();
void clearInputBuffer();

int main() {
    srand((unsigned int)time(NULL));
    Cat cat = { 3, 2, 0 };
    int cp = 0;
    int turn;
    int hasMouse = 0;
    int hasLaser = 0;

    for (turn = 1; turn <= 10; turn++) {
        printf("\n========== 턴 %d ==========", turn);
        printStatus(&cat);
        updateMood(&cat);

        printf("\n[상호작용]\n");
        printf("0: 아무것도 안 함\n1: 긁어 주기\n");
        if (hasMouse) printf("2: 장난감 쥐로 놀기\n");
        if (hasLaser) printf("3: 레이저 포인터로 놀기\n");
        printf("선택: ");
        int action;
        if (scanf_s("%d", &action) != 1) {
            printf("잘못된 입력입니다. 숫자를 입력해주세요.\n");
            clearInputBuffer();
            action = 0;
        }
        interaction(&cat, action, hasMouse, hasLaser);

        int gain = produceCP(&cat);
        cp += gain;
        printf("얻은 CP: %d / 현재 CP: %d\n", gain, cp);

        shopMenu(&cp, &hasMouse, &hasLaser);

        if (turn == 3) {
            triggerQuest();
        }
    }

    printf("\n10턴이 종료되었습니다. 플레이 감사합니다!\n");
    return 0;
}

void updateMood(Cat* cat) {
    int threshold = 6 - cat->affinity;
    int roll = rand() % 6 + 1;
    if (roll <= threshold && cat->mood > 0) {
        cat->mood--;
        printf("기분이 나빠졌습니다. 현재 기분: %d\n", cat->mood);
    }
}

int produceCP(Cat* cat) {
    return MAX(0, cat->mood - 1) + cat->affinity;
}

void printStatus(Cat* cat) {
    printf("\n[쫀떡이 상태]\n기분: %d (0~3), 친밀도: %d (0~4)\n", cat->mood, cat->affinity);
}

void interaction(Cat* cat, int action, int hasMouse, int hasLaser) {
    int roll = rand() % 6 + 1;
    switch (action) {
    case 0:
        if (cat->mood > 0) cat->mood--;
        if (roll <= 5 && cat->affinity > 0) cat->affinity--;
        printf("아무것도 하지 않음: 기분 -1, 친밀도 조건부 -1\n");
        break;
    case 1:
        if (roll >= 5 && cat->affinity < 4) cat->affinity++;
        printf("긁어 주기: 친밀도 조건부 +1\n");
        break;
    case 2:
        if (hasMouse) {
            if (cat->mood < 3) cat->mood++;
            if (roll >= 4 && cat->affinity < 4) cat->affinity++;
            printf("장난감 쥐로 놀기: 기분 +1, 친밀도 조건부 +1\n");
        }
        break;
    case 3:
        if (hasLaser) {
            cat->mood = MIN(3, cat->mood + 2);
            if (roll >= 2 && cat->affinity < 4) cat->affinity++;
            printf("레이저 포인터로 놀기: 기분 +2, 친밀도 조건부 +1\n");
        }
        break;
    default:
        printf("잘못된 입력입니다.\n");
    }
}

void shopMenu(int* cp, int* hasMouse, int* hasLaser) {
    printf("\n[상점]\n");
    printf("0. 아무것도 안 산다\n");
    if (!(*hasMouse)) printf("1. 장난감 쥐 (1 CP)\n");
    if (!(*hasLaser)) printf("2. 레이저 포인터 (2 CP)\n");
    printf("선택: ");
    int choice;
    if (scanf_s("%d", &choice) != 1) {
        printf("숫자를 입력해주세요.\n");
        clearInputBuffer();
        choice = 0;
    }

    if (choice == 1 && !(*hasMouse) && *cp >= 1) {
        *hasMouse = 1;
        *cp -= 1;
        printf("장난감 쥐를 구매했습니다.\n");
    }
    else if (choice == 2 && !(*hasLaser) && *cp >= 2) {
        *hasLaser = 1;
        *cp -= 2;
        printf("레이저 포인터를 구매했습니다.\n");
    }
    else if (choice != 0) {
        printf("구매 실패 (CP 부족 또는 이미 구매함)\n");
    }
}

void triggerQuest() {
    char input[100] = { 0 };
    printf("\n[돌발 퀘스트 발생!]\n쫀떡이가 창밖으로 나가려 합니다! '돌아오게 하기'를 입력하세요: ");
    if (scanf_s("%99s", input, (unsigned)_countof(input)) != 1) {
        printf("입력 실패 - 쫀떡이는 외출 중입니다.\n");
        return;
    }
    if (strcmp(input, "돌아오게") == 0 || strcmp(input, "돌아오게하기") == 0) {
        printf("쫀떡이가 돌아왔습니다!\n");
    }
    else {
        printf("쫀떡이는 잠시 외출 중입니다...\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
