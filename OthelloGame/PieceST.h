#pragma once
#include <iostream>

// ピースの状態
enum class PIECE_ST
{
	B,		// 黒
	W,		// 白
	NON,
	MAX
};

PIECE_ST begin(PIECE_ST);
PIECE_ST end(PIECE_ST);
int operator*(PIECE_ST state);
// enum値の加算
PIECE_ST operator++(PIECE_ST& state);
// enum値の減算
PIECE_ST operator--(PIECE_ST& state);