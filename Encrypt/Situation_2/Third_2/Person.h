#pragma once
#include <Windows.h>
#include "Basic.h"

class Person
{
public:
	Person();
	unsigned int alice_grade = 0;		//Alice成绩
	unsigned int alice_key = 0;			//Alice成绩对应的私钥

	mpz_t r3;							//三方约定随机数

	Message recive2;					//Bob发送的密文
	mpz_t send;							//本方发送的明文

	mpz_t temp;							//提供计算临时变量，使用前请设定其值
	unsigned int key = 0;				//提供计算的临时变量
	mpz_t public_key;					//提供计算的临时变量

	void Game();						//进程启动
private:
	bool Init();						//初始化：收法公钥及其他数据
	bool Menu();						//开始菜单：选择自己的成绩
	bool Check();						//检测是否有人退出
};
extern Person third;
void Vision(char choose);				//画面输出
