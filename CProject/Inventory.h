#pragma once
#include "Potions.h"
using namespace std;
class Inventory
{
	
private:
	vector<pair<int, int>> items;
public:
	
	Potions* potions;
	bool isEmpty = true;
	void AddItem(int ID) {
		isEmpty = false;
		for (pair<int, int> Pair : items) {
			if (Pair.first == ID) {
				Pair.second++;
				return;
			}
		}
		items.push_back({ ID, 1 });
	}
	void RemoveItem(int ID) {
		for (pair<int, int> Pair : items) {
			if (Pair.first == ID) {
				Pair.second--;
				if (Pair.second == 0) {
					items.erase(find(items.begin(), items.end()-1, Pair));
				}
				return;
			}
		}
	}
	bool ShowInventory() {
		if (items.size() == 0) {
			cout << "В карманах только пара дохлых мух...\n";
			
			return false;
		}
		for (int i = 0; i < items.size(); i++) {
			cout << i + 1 << ". " << items[i].second << " x ";
			potions->StatePotion(items[i].first);
		}
		cout << items.size() + 1 << ". Выход" << endl;
		return true;
	}
	void UseItem(int input) {
		if (input == items.size() + 1) { return; }
		if (items[input - 1].second <= 0) {
			cout << "Эти зелья кончились!";
			return;
		}
		potions->UsePotion(items[input - 1].first);
		RemoveItem(items[input - 1].first);
		
		return;
	}
};

