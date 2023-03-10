#pragma once
#include <Windows.h>
#include "Basic.h"

class Person
{
public:
	Person();
	unsigned int grade = 0;				//本方成绩
	mpz_t rAB;							//Alice、Bob约定随机数
	mpz_t r3;							//三方约定随机数

	mpz_t commit;						//Pedersen承诺
	mpz_t recive;						//本方接收的信息
	void Game();						//进程启动
private:
	bool Init();						//初始化：收法公钥及其他数据
	bool Menu();						//开始菜单：选择自己的成绩
	bool Choose();						//选择是否要作弊
	bool Check();						//检测是否有人退出
	bool Judge();						//判断成绩是否相同
};
extern Person alice;
void Vision(char choose);				//画面输出