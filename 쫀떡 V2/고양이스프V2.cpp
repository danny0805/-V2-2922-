// �߿��̿� ���� v2 - ���� ���� �ڵ� (C++)
// �ۼ���: ���� ����� / �й�: 202500123
// ���: �߿��� ����, ��ȣ�ۿ�, ����, ���� ����Ʈ �� ����

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
            cout << name << "�� ����� ���������ϴ�. ���� ���: " << mood << endl;
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
        cout << "\n[�߿��� ����]\n";
        cout << "���: " << mood << " (0~3), ģ�е�: " << affinity << " (0~4)\n";
    }
};

class Shop {
public:
    void display(bool hasMouse, bool hasLaser) {
        cout << "\n[���� ���]" << endl;
        cout << "0. �ƹ��͵� �� ���" << endl;
        if (!hasMouse) cout << "1. �峭�� �� (1 CP)" << endl;
        if (!hasLaser) cout << "2. ������ ������ (2 CP)" << endl;
    }

    void buy(int choice, int& cp, bool& hasMouse, bool& hasLaser) {
        if (choice == 1 && !hasMouse && cp >= 1) {
            hasMouse = true; cp -= 1;
            cout << "�峭�� �㸦 �����߽��ϴ�." << endl;
        }
        else if (choice == 2 && !hasLaser && cp >= 2) {
            hasLaser = true; cp -= 2;
            cout << "������ �����͸� �����߽��ϴ�." << endl;
        }
        else if (choice != 0) {
            cout << "���� ���� (CP ���� �Ǵ� �̹� ������)" << endl;
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
            cout << "�ƹ��͵� ���� ����. ��� -1, ģ�е� ���Ǻ� ����." << endl;
            break;
        case 1:
            if (roll >= 5) cat.adjustAffinity(1);
            cout << "�ܾ� �־����ϴ�. ģ�е� ���Ǻ� ����." << endl;
            break;
        case 2:
            if (hasMouse) {
                cat.adjustMood(1);
                if (roll >= 4) cat.adjustAffinity(1);
                cout << "�峭�� ��� ��� �־����ϴ�. ��� +1, ģ�е� ���Ǻ� ����." << endl;
            }
            break;
        case 3:
            if (hasLaser) {
                cat.adjustMood(2);
                if (roll >= 2) cat.adjustAffinity(1);
                cout << "������ �����ͷ� ��� �־����ϴ�. ��� +2, ģ�е� ���Ǻ� ����." << endl;
            }
            break;
        default:
            cout << "�߸��� �Է��Դϴ�." << endl;
        }
    }
};

class Quest {
public:
    void trigger() {
        cout << "\n[���� ����Ʈ �߻�!]" << endl;
        cout << "�˶��̰� â�� �ʸӷ� ������ �Ѵ�! '���ƿ��� �ϱ�'�� �Է��ϼ���: ";
        string input;
        cin >> input;
        if (input == "���ƿ��� �ϱ�") {
            cout << "�˶��̰� ������ ���ƿԽ��ϴ�!" << endl;
        }
        else {
            cout << "�˶��̰� ��� �����߽��ϴ�..." << endl;
        }
    }
};

int main() {
    srand((unsigned int)time(0));
    Cat cat("�˶�");
    Shop shop;
    Interaction interaction;
    Quest quest;
    int turn = 0;
    int cp = 0;
    bool hasMouse = false;
    bool hasLaser = false;

    while (turn < 10) {
        turn++;
        cout << "\n========== �� " << turn << " ==========" << endl;
        cat.printStatus();
        cat.updateMood();

        cout << "\n[��ȣ�ۿ� ����]\n0: �ƹ��͵� �� ��\n1: �ܾ� �ֱ�";
        if (hasMouse) cout << "\n2: �峭�� ��� ���";
        if (hasLaser) cout << "\n3: ������ �����ͷ� ���";
        cout << "\n����: ";
        int action;
        cin >> action;
        interaction.handle(cat, action, hasMouse, hasLaser);

        int gained = cat.produceCP();
        cp += gained;
        cout << "�̹� �Ͽ� ���� CP: " << gained << " / �� CP: " << cp << endl;

        shop.display(hasMouse, hasLaser);
        cout << "������ ��ȣ �Է�: ";
        int buyChoice;
        cin >> buyChoice;
        shop.buy(buyChoice, cp, hasMouse, hasLaser);

        if (turn == 3) quest.trigger();
    }

    cout << "\n10���� ����Ǿ����ϴ�. �÷��� �����մϴ�!" << endl;
    return 0;
}