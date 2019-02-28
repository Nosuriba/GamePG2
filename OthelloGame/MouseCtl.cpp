#include <DxLib.h>
#include <crtdbg.h>
#include "MouseCtl.h"
#include "GameBoard.h"
#include "NetWork.h"
#include "NetWorkState.h"
#include "TypeMan.h"
#include "TypeCpu.h"
#include "TypeNet.h"

MouseCtl::MouseCtl() : limTime(10)
{
	for (int i = 0; i < 2; i++)
	{
		mButton[i] = 0;
	}
	data = { { 0,0 }, 0 };
}

MouseCtl::~MouseCtl()
{
	if (threadAI.joinable())
	{
		threadAI.join();
	}
}

Vector2 MouseCtl::GetPoint() const
{
	return data.pos;
}

mouse_int MouseCtl::GetButton() const
{
	return mButton;
}

PL_TYPE MouseCtl::GetPlType()
{
	if (!plType)
	{
		return PL_TYPE::SYS;
	}
	return (*plType).GetType();
}

void MouseCtl::SetPlType(PL_TYPE type)
{
	if (type == PL_TYPE::MAN)
	{
		plType = std::make_unique<TypeMan>();
	}
	else if (type == PL_TYPE::CPU)
	{
		plType = std::make_unique<TypeCpu>();
	}
	else if (type == PL_TYPE::NET)
	{
		plType = std::make_unique<TypeNet>();
	}
}

void MouseCtl::ThreadStop()
{
	if (threadAI.joinable())
	{
		threadAI.join();
	}
}

void MouseCtl::Update()
{
	// システム処理用のマウス設定
	mButton[PUSH_OLD] = mButton[PUSH_NOW];
	mButton[PUSH_NOW] = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&data.pos.x, &data.pos.y);
}

void MouseCtl::Update(std::shared_ptr<GameBoard> boardPtr, PIECE_ST pState)
{
	(*plType).SetIsEnd(true);
	data = { {0, 0}, 0 };

	/// スレッド処理に入る前にCPUが行う処理
	if ((*plType).GetType() == PL_TYPE::CPU)
	{
		if (mButton[PUSH_NOW] != 0)
		{
			if (data.pos == Vector2(0,0))
			{
				_RPT0(_CRT_WARN, "CPU : SetPos\n");
				(*plType).SetDefPos(boardPtr);
			}
			else
			{
				_RPT0(_CRT_WARN, "CPU : already GetPos\n");
			}
			mButton[PUSH_NOW] = 0;
			mButton[PUSH_OLD] = mButton[PUSH_NOW];
		}
		else if (data.pos == Vector2(0, 0))
		{
			mButton[PUSH_NOW] = 0;
			mButton[PUSH_OLD] = mButton[PUSH_NOW];
		}
	}

	if ((*plType).GetIsEnd())
	{
		/// スレッドが生成されていない時の処理
		if (!threadAI.joinable())
		{
			threadAI = std::thread([&] {(*plType).Update(boardPtr, pState);});
			_RPT0(_CRT_WARN,"Thread Start\n");
			if ((*plType).GetType() == PL_TYPE::MAN || (*plType).GetType() == PL_TYPE::NET)
			{
				if ((*plType).GetType() == PL_TYPE::MAN)
				{
					_RPT0(_CRT_WARN, "MAN : Thread Join\n");
				}
				else if ((*plType).GetType() == PL_TYPE::NET)
				{
					_RPT0(_CRT_WARN, "NET : Thread Join\n");
				}
				threadAI.join();
			}
		}

		LpGameScene.EndTime();
		if (LpGameScene.GetSecondsTime() > limTime - 1 && (*plType).GetType() == PL_TYPE::MAN)
		{
			LpGameScene.ResetTime();
			_RPT0(_CRT_WARN, "MAN : Time Over\n");
			(*plType).SetIsTimeUp(true);
		}
	}

	/// 各プレイヤーのUpdate処理でマウスの情報が更新された時に入る処理
	if ((*plType).GetIsEnd())
	{
		if (threadAI.joinable())
		{
			threadAI.join();
			_RPT0(_CRT_WARN, "CPU : Thread Join\n");
		}
		(*plType).SetIsTimeUp(false);
		data = (*plType).GetMouseData();
		LpGameScene.ResetTime();
		_RPT0(_CRT_WARN, "Thread End\n");
	}

	/// オンライン時のプレイヤーまたはCPUの処理
	if (lpNetWork.GetMode() != NetWorkMode::OFFLINE)
	{
		if ((*plType).GetType() == PL_TYPE::MAN || 
			(*plType).GetType() == PL_TYPE::CPU)
		{
			lpNetWork.SetSendMes({ mesType::M_POS, data.pos.x, data.pos.y, data.mouseID });
		}
	}
	
	// プレイヤーのターンの時にマウスのクリックを更新する
	if (!((*plType).GetType() == PL_TYPE::SYS))
	{
		mButton[PUSH_OLD] = mButton[PUSH_NOW];
		mButton[PUSH_NOW] = data.mouseID;
	}
	else
	{
		Update();
	}
}
