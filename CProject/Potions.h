#pragma once
using namespace std;
class Potions
{
private:
	int ID;
	int generator[10] = { 1,1,1,1,2,2,2,3,3,3 };
	int UsedPotions[2];
	bool PotionsDrank = false;
	
public:
	Character* hero;
	
	void UsePotion(int ID) 
	{
		switch (ID) {
		case 1:
			hero->Health = hero->MaxHealth;
			cout << "�� ������������ ����� �������. ��� ���� ����������!\n";
			break;
		case 2:
			hero->Damage += 3;
			UsedPotions[0] = 2;
			cout << "�� ������������ ����� ����. ���� ������ ������ �����!\n";
			PotionsDrank = true;
			break;
		case 3:
			hero->Defence = 5;
			UsedPotions[1] = 3;
			cout << "�� ������������ ����� ������. ���� ���� ��������!\n";
			PotionsDrank = true;
			break;
		}
		
	}

	void DropEffects() {
		if (PotionsDrank) {
			if (UsedPotions[0] != 0) {
				UsedPotions[0] = 0;
				hero->Damage -= 3;
			}
			if (UsedPotions[1] != 0) {
				UsedPotions[1] = 0;
				hero->Defence = 0;
			}
			cout << "�����, ��� �� ������, ���������.\n";
			PotionsDrank = false;
		}
	}

	void StatePotion(int ID) {
		switch (ID) {
		case 1:
			cout << "����� ������� ";
			break;
		case 2:
			cout << "����� ���� ";
			break;
		case 3:
			cout << "����� ������ ";
			break;
		}
	}

	int GeneratePotion() {
		srand((unsigned int)time(NULL));
		ID = generator[rand() % 10];
		
		return ID;
	}
};

