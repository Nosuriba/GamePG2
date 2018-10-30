#pragma once

/* �s�[�X�̏��(PIECE_NON�̈ʒu��PIECE_MAX�̈ʒu�ɕς�������������)*/
enum PIECE_ST
{
	PIECE_NON,
	PIECE_B,		// ��
	PIECE_W,		// ��
	PIECE_CHAR1,
	PIECE_CHAR2,
	PIECE_CHAR3,
	PIECE_CHAR4,
	PIECE_MAX
};

struct PieceState
{
	virtual ~PieceState();
	virtual PIECE_ST GetState(void) = 0;
	virtual unsigned int GetDrawColor(void) = 0;
};

