#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <iomanip>
using namespace std;
#define WARRIOR_NUM 5
#define WEAPON_NUM 3

const string warrior_name[WARRIOR_NUM] =
	{"dragon", "ninja", "iceman", "lion", "wolf"};

const string red_warrior_name[WARRIOR_NUM] =
	{"iceman", "lion", "wolf", "ninja", "dragon"};

const string blue_warrior_name[WARRIOR_NUM] =
	{"lion", "dragon", "ninja", "iceman", "wolf"};

const string weapon_name[WEAPON_NUM] =
	{"sword", "bomb", "arrow"};

int cur_time = 0;

map<string, int> warrior_strength;
map<string, int> warrior_id;

void PrintTime()
{
	if (cur_time < 10)
		cout << '0';
	if (cur_time < 100)
		cout << '0';
	cout << cur_time;
}

class Warrior
{
public:
	int strength;
	Warrior(const int &max_strength) {}
};

class Dragon : public Warrior
{
	double morale;
	string weapons[1];

public:
	static int max_strength;
	void PrintInfo() { cout << "It has a " << weapons[0] << ",and it's morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl; }
	Dragon(int &stored_strength)
		: Warrior(max_strength)
	{
		stored_strength -= max_strength;
		morale = 1.0 * stored_strength / max_strength;
		weapons[0] = weapon_name[(cur_time + 1) % WEAPON_NUM];
		PrintInfo();
	}
};

class Ninja : public Warrior
{
public:
	string weapons[2];

	static int max_strength;
	void PrintInfo() { cout << "It has a " << weapons[0] << " and a " << weapons[1] << endl; }
	Ninja(int &stored_strength)
		: Warrior(max_strength)
	{
		stored_strength -= max_strength;
		weapons[0] = weapon_name[(cur_time + 1) % WEAPON_NUM];
		weapons[1] = weapon_name[(cur_time + 2) % WEAPON_NUM];
		PrintInfo();
	}
};

class Iceman : public Warrior
{
public:
	string weapons[1];

	static int max_strength;
	void PrintInfo() { cout << "It has a " << weapons[0] << endl; }
	Iceman(int &stored_strength)
		: Warrior(max_strength)
	{
		stored_strength -= max_strength;
		weapons[0] = weapon_name[(cur_time + 1) % WEAPON_NUM];
		PrintInfo();
	}
};

class Lion : public Warrior
{
public:
	int loyalty;

	static int max_strength;
	void PrintInfo() { cout << "It's loyalty is " << loyalty << endl; }
	Lion(int &stored_strength)
		: Warrior(max_strength)
	{
		stored_strength -= max_strength;
		loyalty = stored_strength;
		PrintInfo();
	}
};

class Wolf : public Warrior
{
public:
	static int max_strength;

	Wolf(int &stored_strength)
		: Warrior(max_strength)
	{
		stored_strength -= max_strength;
	}
};

int Dragon::max_strength = 0;
int Ninja::max_strength = 0;
int Iceman::max_strength = 0;
int Lion::max_strength = 0;
int Wolf::max_strength = 0;

int *max_strength_array[WARRIOR_NUM] = {&Dragon::max_strength, &Ninja::max_strength, &Iceman::max_strength, &Lion::max_strength, &Wolf::max_strength};

class Headquarter
{
	string controller;
	const string *warrior_rank;
	int cur_warrior_cnt[WARRIOR_NUM];
	int cur_warrior_id = 0; // [0, 5)
	bool stop_create;
	static int min_stored_strength_to_create;
	int stored_strength;

public:
	static int max_stored_strength;
	static void GetMinStoredStrengthToCreate()
	{
		min_stored_strength_to_create = 0x7fffffff;
		for (auto strength : max_strength_array)
			min_stored_strength_to_create = min(min_stored_strength_to_create, *strength);
	}
	Headquarter(string _controller, const string *name)
	{
		controller = _controller;
		warrior_rank = name;
		memset(cur_warrior_cnt, 0, sizeof(cur_warrior_cnt));
		cur_warrior_id = 0;
		stored_strength = max_stored_strength;
		stop_create = false;
	}
	bool StopCreate() { return stop_create; }
	void TryCreateWarrior()
	{
		if (StopCreate())
			return;
		PrintTime();
		cout << " " << controller << " ";
		if (min_stored_strength_to_create > stored_strength && !stop_create)
		{
			stop_create = true;
			cout << "headquarter stops making warriors" << endl;
			return;
		}
		for (; warrior_strength[warrior_rank[cur_warrior_id]] > stored_strength;)
			cur_warrior_id = (cur_warrior_id + 1) % 5;
		string name = warrior_rank[cur_warrior_id];
		int id = warrior_id[name];
		cout << name << " " << cur_time + 1 << " born with strength " << warrior_strength[name] << "," << ++cur_warrior_cnt[id] << " " << name << " in " << controller << " headquarter" << endl;
		if (id == 0)
			Dragon dragon(stored_strength);
		if (id == 1)
			Ninja ninja(stored_strength);
		if (id == 2)
			Iceman iceman(stored_strength);
		if (id == 3)
			Lion lion(stored_strength);
		if (id == 4)
			Wolf wolf(stored_strength);
		cur_warrior_id = (cur_warrior_id + 1) % 5;
	}
};

int Headquarter::max_stored_strength = 0;
int Headquarter::min_stored_strength_to_create = 0x7fffffff;
int main()
{
	for (int i = 0; i < WARRIOR_NUM; ++i)
		warrior_id[warrior_name[i]] = i;
	int test_cnt;
	cin >> test_cnt;
	for (int cur_test = 1; cur_test <= test_cnt; ++cur_test)
	{
		cur_time = 0;
		cout << "Case:" << cur_test << endl;
		cin >> Headquarter::max_stored_strength;
		for (int i = 0; i < WARRIOR_NUM; ++i)
		{
			cin >> *(max_strength_array[i]);
			warrior_strength[warrior_name[i]] = *(max_strength_array[i]);
		}
		Headquarter::GetMinStoredStrengthToCreate();
		Headquarter red("red", red_warrior_name);
		Headquarter blue("blue", blue_warrior_name);
		for (; !(red.StopCreate() && blue.StopCreate()); ++cur_time)
			red.TryCreateWarrior(), blue.TryCreateWarrior();
	}
	return 0;
}