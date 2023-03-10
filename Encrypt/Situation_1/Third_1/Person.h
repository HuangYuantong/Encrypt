#pragma once
#include <Windows.h>
#include "Basic.h"

class Person
{
public:
	Person();
	unsigned int alice_grade = 0;		//Alice的成绩
	unsigned int bob_grade = 0;			//Bob的成绩
	unsigned int alice_key = 0;			//Alice密钥
	mpz_t alice_public_key;				//Alice公钥
	unsigned int bob_key = 0;			//Bob密钥
	mpz_t bob_public_key;				//Bob公钥
	mpz_t recive;						//本方接收的密文解密后的明文
	Message recive_alice,recive_bob;	//本方接收的Elgamal密文

	mpz_t temp;							//提供计算的数，使用前请设定其值

	void Game();						//进程启动
private:
	bool Menu();						//开始菜单：选择自己的成绩
	bool Init();						//初始化：收法公钥及其他数据
	bool Check();						//检测是否有人退出
	bool Judge();						//作弊检测
};
extern Person third;
void Vision(char choose);				//画面输出