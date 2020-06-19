#ifndef _IRUNNABLE_H_
#define _IRUNNABLE_H_

//スレッド実行インターフェース
class IRunnable
{
public:
	//デストラクタ
	virtual ~IRunnable() {}
	//スレッド実行
	virtual void run() = 0;
};

#endif // !_IRUNNABLE_H_
