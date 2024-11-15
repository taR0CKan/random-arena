// CProject.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <io.h>
#include <iomanip>
#include <stdio.h>
#include <tuple>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include <algorithm>
#include "Character.h"
#include "Enemy.h"
#include "Potions.h"
#include "Inventory.h"
#include "RecordMaster.h"

using namespace std;

Potions potions;
Character hero;
Inventory inventory;
RecordMaster recordMaster;
;
namespace GP {
    int counter = 1;
    
    int reward;
    int newPotion;
    
    void DropPotions(bool isElite) {
        srand((unsigned int)time(NULL));
        int num = rand() % 10;
        if (isElite || num > 0) {
            newPotion = potions.GeneratePotion();
            inventory.AddItem(newPotion);
            cout << "Зрителям понравилось ваше выступление! Вы получаете: ";
            potions.StatePotion(newPotion);
            cout << "\n";
        }
    }
    int Battle()
    {
        int invaction;
        
        Enemy* curenemy;
        if ( counter > 0 && counter%3 == 0){
            curenemy = new Enemy{10 + counter * (counter/3), true};
        }
        else { curenemy = new Enemy; }
        cout << "На арену выходит " + curenemy->name + ".\n" + "Вы готовы к драке?\n";
        cout << curenemy->sprite;
        while (hero.Health > 0) {

            cout << "Ваши действия: 1.Стойка нападения 2.Стойка защиты 3.Инвентарь\n";
            char action;
            cin >> action;
            switch (action)
            {
            case '1':
                hero.AttackStance(curenemy->Health, curenemy->Damage);
                break;
            case '2':
                hero.DefenceStance(curenemy->Health, curenemy->Damage);
                break;
            case '3':
                if (!inventory.ShowInventory()) { break; }
                cin >> invaction;
                if (!inventory.isEmpty) {
                    if (invaction < 2) {
                        inventory.UseItem(invaction);
                    }
                    else {
                        cout << "Вы выбрали неверно!";
                    }
                }
                continue;
            default:
                cout << "Вы выбрали неверно!";
                break;
            }
            if (hero.Health <= 0) {
                cout << "Вы получили травмы, несовместимые с жизнью. ";
                cout << "Выигрыш платить некому, да и пенсии у вас уже не будет.";
                return 1;
            }
            if (curenemy->Health <= 0) {
                counter++;
                reward = curenemy->Damage%3 + GP::counter;
                hero.Money += reward;
                system("cls");
                cout << "Победа! Вы получаете " << reward << " денег.";
                cout << "Ваши текущие накопления : " << hero.Money << " Ваше здоровье : " << hero.Health << "\n";
                DropPotions(curenemy->isElite);
                delete curenemy;
                break;
            }
        }
        return 0;
    }
    int Proceed() {
        while (true) {
            cout << "Желаете продолжить? 1.Да 2.Нет 3.Инвентарь\n";
            char action;
            cin >> action;
            switch (action)
            {
            case '1':
                cout << "Встречайте следующего противника!";
                return 1;
            case '2':
                cout << "Вы накопили на безбедную старость! Наверное. Ваш рекорд в ";
                cout << hero.Money<< " монет будет записан в книгу, наверное:\n";
                recordMaster.ShowRecords();
                return 0;
            case '3':
                inventory.ShowInventory();
                int invaction;
                cin >> invaction;
                if (!inventory.isEmpty) {
                    if (invaction < 2) {
                        inventory.UseItem(invaction);
                    }
                    else {
                        cout << "Вы выбрали неверно!";
                    }
                }
                continue;
            default:
                cout << "Вы выбрали неверно!";
            }
        }
    }
    void Menu() {
        recordMaster.ReadRecords();
		while (true) {
			cout << "1. Начать игру 2. Рекорды  3. Выход\n";
			char action;
			cin >> action;
			switch (action)
			{
			case '1':
                cout << "Введите имя своего персонажа:\n";
                cin >> hero.Name;
				return;
			case '2':
                recordMaster.ShowRecords();
                break;
            case '3':
                exit(0);
			default:
				cout << "Вы выбрали неверно!";
			}
		}
    }
}


int main() {
    
    potions.hero = &hero;
    inventory.potions = &potions;
    setlocale(LC_ALL, "Russian");
    hero.SetStats();
    cout << "Добро пожаловать на арену случайностей! Вы - обычный герой, у вас " <<hero.Health<<" Здоровья и " << hero.Damage << " урона\n";
    GP::Menu();
    cout << endl;
    while (true) {
        if (GP::Battle() == 1) { return 0; }
        potions.DropEffects();
        
        hero.Killcounter++;
       
        if (GP::Proceed() == 0) {
            recordMaster.SetRecords(hero.Name, hero.Money, hero.Killcounter);
            return 0;
        }
    }
    return 0;
}


