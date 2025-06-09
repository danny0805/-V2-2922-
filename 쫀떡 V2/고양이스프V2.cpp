// 야옹이와 수프 v2 - 통합 실행 코드 (C++)
// 작성자: 예시 사용자 / 학번: 202500123
// 기능: 야옹이 상태, 상호작용, 상점, 돌발 퀘스트 등 포함

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Cat {
    string name;
    int mood; // 0~3
    int affinity; // 0~4

public:
    Cat(string n) : name(n), mood(3), affinity(2) {}

    void updateMood() {
        int threshold = 6 - affinity;
        int roll = rand() % 6 + 1;
        if (roll <= threshold && mood > 0) {
            mood--;
            cout << name << "의 기분이 나빠졌습니다. 현재 기분: " << mood << endl;
        }
    }

    int produceCP() const {
        return max(0, mood - 1) + affinity;
    }

    void adjustMood(int val) {
        mood = max(0, min(3, mood + val));
    }

    void adjustAffinity(int val) {
        affinity = max(0, min(4, affinity + val));
    }

    int getMood() const { return mood; }
    int getAffinity() const { return affinity; }

    void printStatus() const {
        cout << "\n[야옹이 상태]\n";
        cout << "기분: " << mood << " (0~3), 친밀도: " << affinity << " (0~4)\n";
    }
};

class Shop {
public:
    void display(bool hasMouse, bool hasLaser) {
        cout << "\n[상점 목록]" << endl;
        cout << "0. 아무것도 안 산다" << endl;
        if (!hasMouse) cout << "1. 장난감 쥐 (1 CP)" << endl;
        if (!hasLaser) cout << "2. 레이저 포인터 (2 CP)" << endl;
    }

    void buy(int choice, int& cp, bool& hasMouse, bool& hasLaser) {
        if (choice == 1 && !hasMouse && cp >= 1) {
            hasMouse = true; cp -= 1;
            cout << "장난감 쥐를 구매했습니다." << endl;
        }
        else if (choice == 2 && !hasLaser && cp >= 2) {
            hasLaser = true; cp -= 2;
            cout << "레이저 포인터를 구매했습니다." << endl;
        }
        else if (choice != 0) {
            cout << "구매 실패 (CP 부족 또는 이미 구매함)" << endl;
        }
    }
};

class Interaction {
public:
    void handle(Cat& cat, int action, bool hasMouse, bool hasLaser) {
        int roll = rand() % 6 + 1;
        switch (action) {
        case 0:
            cat.adjustMood(-1);
            if (roll <= 5) cat.adjustAffinity(-1);
            cout << "아무것도 하지 않음. 기분 -1, 친밀도 조건부 감소." << endl;
            break;
        case 1:
            if (roll >= 5) cat.adjustAffinity(1);
            cout << "긁어 주었습니다. 친밀도 조건부 증가." << endl;
            break;
        case 2:
            if (hasMouse) {
                cat.adjustMood(1);
                if (roll >= 4) cat.adjustAffinity(1);
                cout << "장난감 쥐로 놀아 주었습니다. 기분 +1, 친밀도 조건부 증가." << endl;
            }
            break;
        case 3:
            if (hasLaser) {
                cat.adjustMood(2);
                if (roll >= 2) cat.adjustAffinity(1);
                cout << "레이저 포인터로 놀아 주었습니다. 기분 +2, 친밀도 조건부 증가." << endl;
            }
            break;
        default:
            cout << "잘못된 입력입니다." << endl;
        }
    }
};

class Quest {
public:
    void trigger() {
        cout << "\n[돌발 퀘스트 발생!]" << endl;
        cout << "쫀떡이가 창문 너머로 나가려 한다! '돌아오게 하기'를 입력하세요: ";
        string input;
        cin >> input;
        if (input == "돌아오게 하기") {
            cout << "쫀떡이가 무사히 돌아왔습니다!" << endl;
        }
        else {
            cout << "쫀떡이가 잠시 외출했습니다..." << endl;
        }
    }
};

int main() {
    srand((unsigned int)time(0));
    Cat cat("쫀떡");
    Shop shop;
    Interaction interaction;
    Quest quest;
    int turn = 0;
    int cp = 0;
    bool hasMouse = false;
    bool hasLaser = false;

    while (turn < 10) {
        turn++;
        cout << "\n========== 턴 " << turn << " ==========" << endl;
        cat.printStatus();
        cat.updateMood();

        cout << "\n[상호작용 선택]\n0: 아무것도 안 함\n1: 긁어 주기";
        if (hasMouse) cout << "\n2: 장난감 쥐로 놀기";
        if (hasLaser) cout << "\n3: 레이저 포인터로 놀기";
        cout << "\n선택: ";
        int action;
        cin >> action;
        interaction.handle(cat, action, hasMouse, hasLaser);

        int gained = cat.produceCP();
        cp += gained;
        cout << "이번 턴에 얻은 CP: " << gained << " / 총 CP: " << cp << endl;

        shop.display(hasMouse, hasLaser);
        cout << "구매할 번호 입력: ";
        int buyChoice;
        cin >> buyChoice;
        shop.buy(buyChoice, cp, hasMouse, hasLaser);

        if (turn == 3) quest.trigger();
    }

    cout << "\n10턴이 종료되었습니다. 플레이 감사합니다!" << endl;
    return 0;
}