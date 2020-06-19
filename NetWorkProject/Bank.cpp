#include"Thread.h"
#include"CriticalSection.h"
#include<iostream>

//銀行クラス
class Bank
{
public:
	//コンストラクタ
	Bank(int money) :mCash(money)
	{
	}

	//現金引き出し
	int dispenseCash(int money)
	{
		//現金アクセスロックを行う
		CriticalSection::Lock guard(mCashLock);

		//銀行の残高が引き出し金額より少ない
		if (mCash < money) {
			std::cout << "現金が不足しています\n";
			//引き出せない場合はマイナスを返す
			return -1;
		}
		std::cout << "現金を引き出しいます・・・\n";
		mCash -= money;
		return money;
	}

	//Bankの現金残高
	void printCash()
	{
		//現金アクセスロックを行う
		CriticalSection::Lock guard(mCashLock);

		std::cout << "銀行の現金" << mCash << std::endl;
	}
private:
	//銀行の現金残高
	int mCash;
	//現金アクセスロック
	CriticalSection mCashLock;
};

//サクラ銀行(グローバルなクラス)
Bank SakuraBank(1000);

//田中君のクラス
class Tanaka :public Thread
{
public:
	//スレッドの実行
	void run()
	{
		int money;
		//銀行から現金を引き出せなくなるまで引き出す
		do {
			//銀行から100円引き出す
			std::cout << "田中君100円引き出し\n";
			money = SakuraBank.dispenseCash(100);
		} while (money >= 0);
	}
};

//鈴木君のクラス
class Suzuki :public Thread
{
public:
	//スレッドの実行
	void run()
	{
		int money;
		//銀行から現金を引き出せなくなるまで引き出す
		do {
			//銀行から100円引き出す
			std::cout << "鈴木君50円引き出し\n";
			money = SakuraBank.dispenseCash(51);
		} while (money >= 0);
	}
};

void main()
{
	Tanaka tanaka; //田中君スレッド
	Suzuki suzuki; //鈴木君スレッド

	//田中君スレッド開始
	tanaka.start();
	//鈴木君スレッド開始
	suzuki.start();

	//田中君の終了を待つ
	tanaka.join();
	//鈴木君の終了を待つ
	suzuki.join();

	//銀行の現金を表示
	SakuraBank.printCash();
}