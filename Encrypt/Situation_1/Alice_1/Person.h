#pragma once
#include <Windows.h>
#include "Basic.h"

class Person
{
public:
	Person();
	unsigned int grade = 0;				//本方成绩
	unsigned int key = 0;				//本方密钥
	mpz_t public_key;					//本方公钥
	mpz_t recive;						//本方接收的密文解密后的明文
	Message recive2, send2;				//本方发送的Elgamal密文
	mpz_t temp;							//提供计算的数，使用前请设定其值

	void Game();						//进程启动
private:
	bool Init();						//初始化：收发公钥及其他数据
	bool Menu();						//开始菜单：选择自己的成绩
	bool Choose();						//选择是否要作弊
	bool Check();						//检测是否有人退出
	bool Judge();						//判断成绩是否相同
};
extern Person alice;
void Vision(char choose);				//画面输出