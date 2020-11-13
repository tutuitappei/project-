#pragma once
#include <type_traits>


enum class InputID
{
	Up,
	Down,
	Right,
	Left,
	Btn1,
	Btn2,
	Max
};

static InputID begin(InputID) { return InputID::Up; };
static InputID end(InputID) { return InputID::Max; };
static InputID operator ++(InputID& state) { return (state = InputID(std::underlying_type<InputID>::type(state) + 1)); };
static InputID operator *(InputID& state) { return state; };
