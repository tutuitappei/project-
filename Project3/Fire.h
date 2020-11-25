#pragma once
#include<chrono>
#include"Map.h"

#define DefFire 3;

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

	int fireimage;
	int _longFire;

	std::chrono::system_clock::time_point  start, end;

	Map _map;
};

