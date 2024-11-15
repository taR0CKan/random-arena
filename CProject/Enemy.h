#pragma once


class Enemy
{
private:
	FILE* file;
	string spritebig = "       ###       \n    ###   ###    \n  ##         ##  \n #             # \n#    @@   @@    #\n#    @@   @@    #\n #             # \n  #           #  \n   #         #   \n    #       #    \n     #######     \n";
	string spritesmall = "\n  # #  \n #   # \n#     #\n# @ @ #\n#     #\n#     #\n ##### \n";
	string buffer;
	vector<vector<string>>CustomEnemies;
public:
	int Health;
	int Damage;
	int PowerPoints = 10;
	bool isElite = false;
	int Defence;
	int choice;
	float EliteCoef;
	string sprite;
	string name;
	Enemy(){
		SetStats();
		srand((unsigned int)time(NULL));
		choice = 0 + rand() % CustomEnemies.size();
		name = CustomEnemies[choice][0];
		Health = 1 + rand() % (stoi(CustomEnemies[choice][1]) - 2);
		Damage = stoi(CustomEnemies[choice][1]) - Health;
		Health += stoi(CustomEnemies[choice][2]);

		if (Health > Damage) {
			name = "большой медленный " + name;
			Damage /= 1.5;
			
		}
		else { 
			name = "маленький жоский " + name;
			
		}
		
	}
	
	Enemy(int ElitePoints, bool C_isElite) {
		SetStats();
		srand((unsigned int)time(NULL));
		choice = 0 + rand() % CustomEnemies.size();
		ElitePoints *= stof(CustomEnemies[choice][3]);
		Health = 1 + rand() % (ElitePoints - 2);
		Damage = ElitePoints - Health;
		Health += Defence;
		if (Health > Damage) {
			name = "Элитный большой " + CustomEnemies[choice][0];
			Damage = Damage/1.5 + 2;
			sprite = spritebig + "\n     элитный";
		}
		else {
			name = "Элитный жоский " + CustomEnemies[choice][0];
			sprite = spritesmall + "\nэлитный";
		}
		isElite = C_isElite;
	}
	void SetStats() {
		freopen_s(&file, "EnemyConfig.txt", "r", stdin);
		int counter;
		cin >> counter;
		for (int i = 0; i < counter; i++) {
			cin >> name >> Health >> Defence >> EliteCoef;
			CustomEnemies.push_back({ name, to_string(PowerPoints), to_string(Defence), to_string(EliteCoef)});
		}
		fclose(file);
		freopen_s(&file, "slimes.txt", "r", stdin);
		/*sprite = "";
		while (getline(cin, buffer)) {
			sprite += buffer + "\n";
		}
		fclose(file);*/
		freopen_s(&file, "CON", "r", stdin);
		cin.clear();
		cin.sync();
	}
};

