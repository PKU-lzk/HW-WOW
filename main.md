# World of Warcraft

## main.cpp

```c++
WARRIOR_NUM = 5
WEAPON_NUM = 3

string warrior_name[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string weapon_name[3] = {"sword", "bomb", "arrow"};

class Headquarter
{
  	string controller = "red" or "blue";
  	string warrior_name[5] = 
    		{"iceman", "lion", "wolf", "ninja", "dragon"}; // red headquarter
  			{"lion", "dragon", "ninja", "iceman", "wolf"}; // blue headquarter
  	static int stored_strength;
  	int cur_warrior_cnt[5];
  	int cur_warrior_id = 0; // [0, 5)
}
class Warrior // all warrior type
{
  	int strength;
  	int number;
  
  	constructor:
  	Warrior(const int &max_strength, int &cur_number);
}

class Dragon
{
  	double morale;
  	string weapons[];

  	static int max_health;
  
  	constructor:
  	Dragon(const int &max_strength, int &cur_number) : Warrior(max_strength, cur_number);
}

class Ninja
{
  	string weapons[];
  
  	static int max_health;
  
  	constructor:
  	Ninja(const int &max_strength, int &cur_number) : Warrior(max_strength, cur_number)
}

class Iceman
{
  	string weapons[];
  
  	static int max_health;
  
  	constructor:
  	Iceman(const int &max_strength, int &cur_number) : Warrior(max_strength, cur_number)
}

class Lion
{
  	int loyalty;
  
  	static int max_health;
  
  	constructor:
  	Lion(const int &max_strength, int &cur_number) : Warrior(max_strength, cur_number)
}

class Wolf
{
  
  	static int max_health;
  
  	constructor:
  	Wolf(const int &max_strength, int &cur_number) : Warrior(max_strength, cur_number)
}
```

