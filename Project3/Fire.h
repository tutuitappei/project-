#pragma once
#include<chrono>
#include"Map.h"
#include"TimeKeeper.h"

#define DefFire 3
#define MaxFire 6

class Fire
{
public:
	Fire();
	~Fire();

	void Update(void);
	void Draw(void);
	void AddFire(int a);
private:
	void Init(void);
	void timeclock(void);

	int fireimage[12];
	int _longFire;

	std::chrono::system_clock::time_point  start, recently;

	Map _map;
	TimeKeeper _time;
};

