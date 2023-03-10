#pragma once
#include <Windows.h>
#include "Basic.h"

class Person
{
public:
	Person();
	unsigned int key = 0;				//本方私钥
	mpz_t public_key;					//本方公钥

	mpz_t rAC;							//Alice、第三方约定随机数
	mpz_t rBC;							//Bob、第三方约定随机数
	mpz_t r3;							//三方约定随机数

	mpz_t recive1, recive2;				//Alice、Bob发送的密文
	mpz_t commit1, commit2;				//Alice、Bob的明文
	mpz_t send;							//本方发送的密文（ElGamal的C2）
	mpz_t temp;							//提供计算的随机数，使用前请设定其值

	void Game();						//进程启动
private:
	bool Init();						//初始化：收法公钥及其他数据
	bool Menu();						//开始菜单：选择自己的成绩
	bool Check();						//检测是否有人退出
};
extern Person third;
void Vision(char choose);				//画面输出
