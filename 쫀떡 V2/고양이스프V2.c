// �߿��̿� ���� v2 - C ���� (scanf_s ���� �� �� ���� ����)
// ������ (MSVC ����): cl yaongi_soup_game.c

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
        printf("\n========== �� %d ==========", turn);
        printStatus(&cat);
        updateMood(&cat);

        printf("\n[��ȣ�ۿ�]\n");
        printf("0: �ƹ��͵� �� ��\n1: �ܾ� �ֱ�\n");
        if (hasMouse) printf("2: �峭�� ��� ���\n");
        if (hasLaser) printf("3: ������ �����ͷ� ���\n");
        printf("����: ");
        int action;
        if (scanf_s("%d", &action) != 1) {
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n");
            clearInputBuffer();
            action = 0;
        }
        interaction(&cat, action, hasMouse, hasLaser);

        int gain = produceCP(&cat);
        cp += gain;
        printf("���� CP: %d / ���� CP: %d\n", gain, cp);

        shopMenu(&cp, &hasMouse, &hasLaser);

        if (turn == 3) {
            triggerQuest();
        }
    }

    printf("\n10���� ����Ǿ����ϴ�. �÷��� �����մϴ�!\n");
    return 0;
}

void updateMood(Cat* cat) {
    int threshold = 6 - cat->affinity;
    int roll = rand() % 6 + 1;
    if (roll <= threshold && cat->mood > 0) {
        cat->mood--;
        printf("����� ���������ϴ�. ���� ���: %d\n", cat->mood);
    }
}

int produceCP(Cat* cat) {
    return MAX(0, cat->mood - 1) + cat->affinity;
}

void printStatus(Cat* cat) {
    printf("\n[�˶��� ����]\n���: %d (0~3), ģ�е�: %d (0~4)\n", cat->mood, cat->affinity);
}

void interaction(Cat* cat, int action, int hasMouse, int hasLaser) {
    int roll = rand() % 6 + 1;
    switch (action) {
    case 0:
        if (cat->mood > 0) cat->mood--;
        if (roll <= 5 && cat->affinity > 0) cat->affinity--;
        printf("�ƹ��͵� ���� ����: ��� -1, ģ�е� ���Ǻ� -1\n");
        break;
    case 1:
        if (roll >= 5 && cat->affinity < 4) cat->affinity++;
        printf("�ܾ� �ֱ�: ģ�е� ���Ǻ� +1\n");
        break;
    case 2:
        if (hasMouse) {
            if (cat->mood < 3) cat->mood++;
            if (roll >= 4 && cat->affinity < 4) cat->affinity++;
            printf("�峭�� ��� ���: ��� +1, ģ�е� ���Ǻ� +1\n");
        }
        break;
    case 3:
        if (hasLaser) {
            cat->mood = MIN(3, cat->mood + 2);
            if (roll >= 2 && cat->affinity < 4) cat->affinity++;
            printf("������ �����ͷ� ���: ��� +2, ģ�е� ���Ǻ� +1\n");
        }
        break;
    default:
        printf("�߸��� �Է��Դϴ�.\n");
    }
}

void shopMenu(int* cp, int* hasMouse, int* hasLaser) {
    printf("\n[����]\n");
    printf("0. �ƹ��͵� �� ���\n");
    if (!(*hasMouse)) printf("1. �峭�� �� (1 CP)\n");
    if (!(*hasLaser)) printf("2. ������ ������ (2 CP)\n");
    printf("����: ");
    int choice;
    if (scanf_s("%d", &choice) != 1) {
        printf("���ڸ� �Է����ּ���.\n");
        clearInputBuffer();
        choice = 0;
    }

    if (choice == 1 && !(*hasMouse) && *cp >= 1) {
        *hasMouse = 1;
        *cp -= 1;
        printf("�峭�� �㸦 �����߽��ϴ�.\n");
    }
    else if (choice == 2 && !(*hasLaser) && *cp >= 2) {
        *hasLaser = 1;
        *cp -= 2;
        printf("������ �����͸� �����߽��ϴ�.\n");
    }
    else if (choice != 0) {
        printf("���� ���� (CP ���� �Ǵ� �̹� ������)\n");
    }
}

void triggerQuest() {
    char input[100] = { 0 };
    printf("\n[���� ����Ʈ �߻�!]\n�˶��̰� â������ ������ �մϴ�! '���ƿ��� �ϱ�'�� �Է��ϼ���: ");
    if (scanf_s("%99s", input, (unsigned)_countof(input)) != 1) {
        printf("�Է� ���� - �˶��̴� ���� ���Դϴ�.\n");
        return;
    }
    if (strcmp(input, "���ƿ���") == 0 || strcmp(input, "���ƿ����ϱ�") == 0) {
        printf("�˶��̰� ���ƿԽ��ϴ�!\n");
    }
    else {
        printf("�˶��̴� ��� ���� ���Դϴ�...\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}