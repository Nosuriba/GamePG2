#pragma once

/* �s�[�X�̏��*/
enum PIECE_ST
{
	PIECE_NON,		// ��
	PIECE_B,		// ��
	PIECE_W,		// ��
	PIECE_MAX		// �s�[�X�̍ő吔
};


class PieceState
{
public:
	virtual ~PieceState();
	virtual PIECE_ST GetState(void) = 0;
	virtual unsigned int GetDrawColor(void) = 0;
};

