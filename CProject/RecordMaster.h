#pragma once
using namespace std;

class RecordMaster
{
	FILE* file;
	string CharName;
	int CharMoney;
	int CharKills;
	int RecordCap = 3;
	vector<tuple <string, int, int>> records;
	struct SortByMoney {
		bool operator()(tuple <string, int, int> a, tuple <string, int, int> b) {
			return get<1>(a) > get<1>(b);
		}
	};
public:
	void ReadRecords() {

		freopen_s(&file,"RecordBook.txt", "r", stdin);
		
		for (int i = 0; i < 3; i++) {
			cin >> CharName >> CharMoney >> CharKills;
			records.push_back(tuple <string, int, int>(CharName, CharMoney, CharKills));
		}
		SortRecords();
		fclose(file);
		freopen_s(&file, "CON", "r", stdin);
		cin.clear();
		cin.sync();
	}
	void ShowRecords() {
		for (tuple <string, int, int> i : records) {
			cout << get<0>(i) << " получил " << get<1>(i) << " денег, убив " << get<2>(i) << " слизней\n";
		}
	}
	void SetRecords(string name, int money, int kills) {
		records.push_back(tuple <string, int, int>(name, money, kills));
		SortRecords();
		if (records.size() > RecordCap) {
			records.pop_back();
		}
		freopen_s(&file, "RecordBook.txt", "w", stdout);
		for (tuple <string, int, int> i : records) {
			cout << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
		}
		fclose(file);
		freopen_s(&file, "CON", "r", stdin);
		cin.clear();
		cin.sync();
	};
	void SortRecords() {
		sort(records.begin(), records.end(), SortByMoney());
	}
};
	

