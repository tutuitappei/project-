#pragma once
#include<array>
#include<map>
#include"Inputid.h"

enum class ContType
{
	Key,
	Pad,
	Max
};

enum class Trg
{
	Now,
	Old,
	Max
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;

struct Controller
{
public:
	void operator()()
	{
		Update();
	}


	const CntData& GetCntData(void)
	{
		return _data;
	}
	virtual ContType GetType(void) = 0;
	virtual bool Setup(int no) = 0;
private:
	virtual void Update(void) = 0;
protected:
	CntData _data;
};

