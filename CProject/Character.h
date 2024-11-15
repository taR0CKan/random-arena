#pragma once
using namespace std;
class Character
{
public:
	FILE* file;
	string Name;
	int MaxHealth;
	int Health;
	int Damage;
	int Defence = 0;
	int Money = 0;
	int Killcounter = 0;
	vector<pair<int, int>> stats;
	Character()
	{
		Health = 1;
		Damage = 1;
		MaxHealth = Health;
	}

	void SetStats() {
		freopen_s(&file, "CharConfig.txt", "r", stdin);
		int counter;
		int tempHealth;
		int tempDmg;
		cin >> counter;
		cout << " Выберите пресет:\n";
		for (int i = 0; i < counter;  i++) {
			cin >> tempHealth;
			cin >> tempDmg;
			stats.push_back({ tempHealth,tempDmg });
			cout << i + 1 << ". " << stats[i].first << " здоровья и " << stats[i].second << " урона.\n";
		}
		fclose(file);
		freopen_s(&file, "CON", "r", stdin);
		cin.clear();
		cin.sync();
		int choice;
		cin >> choice;
		Health = stats.at(choice-1).first;
		Damage = stats.at(choice-1).second;
		MaxHealth = Health;
		
	}
	void AttackStance(int& EnemyHP, int EnemyDamage) {
		EnemyHP -= Damage;
		Health -= EnemyDamage - Defence;
		cout << "Вы наносите удар!\n" << "Слизень атакует...\n" << "У вас осталось " << Health << " здоровья.\n";
	}
	void DefenceStance(int& EnemyHP, int EnemyDamage) {
		EnemyHP -= (int)(Damage*0.75);
		if (EnemyHP <= 0) { return; }
		Health -= EnemyDamage/2 + 1 - Defence;
		cout << "Вы наносите удар!\n" << "Слизень атакует...\n" << "У вас осталось " << Health << " здоровья.\n";
	}
};

