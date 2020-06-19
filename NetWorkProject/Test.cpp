#include "Thread.h"
#include<iostream>

//Test1スレッドクラス
class Test1 :public Thread
{
public:
	//Test1スレッドの処理
	void run() {
		for (int i = 0; i < 10; i++) {
			std::cout << "Test1のクラス実行\n";
			//1秒間スリープする
			Thread::sleep(1000);
		}
	}
};

//Test2スレッドクラス
class Test2 :public Thread
{
public:
	//Test2スレッドの処理
	void run()
	{
		for (int i = 0; i < 10; i++) {
			std::cout << "Test2のクラス実行\n";
			//0.5秒間スリープする
			Thread::sleep(500);
		}
	}
};

////main関数
//int main()
//{
//	Test1 test1;
//	Test2 test2;
//
//	//Test1スレッドの実行を開始
//	test1.start();
//	//Test2スレッドの実行を開始
//	test2.start();
//
//	for (int i = 0; i < 10; i++) {
//		std::cout << "Main関数の実行\n";
//		//0.2秒間スリープ
//		Thread::sleep(200);
//	}
//
//	//Test1の終了を待つ
//	test1.join();
//	//Test2の終了を待つ
//	test2.join();
//}