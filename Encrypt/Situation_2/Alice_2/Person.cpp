#include "Person.h"
Person alice;

Person::Person(){mpz_inits(rAB, r3, recive, commit, NULL);}

bool Person::Init()
{
	//发送成绩给第三方
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 1：已发送我方成绩给第三方\n";
	cout << "   > 我方成绩为：" << grade;
	basic.Send_Message("Third_2\\Alice_Grade.txt", grade);
	system("pause");
	//发送约定随机数给Bob
	if (Check() == false) return false;
	mpz_urandomm(rAB, seed, basic.p);
	Vision('0');
	cout << "   > Step 2：送数 rAB 给Bob\n";
	cout << "     双方约定 rAB 为计算Pedersen承诺时使用的参数\n";
	cout << "   > 参数 rAB 实际值为：\n";
	gmp_printf("  %Zd\n", rAB);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Alice_2", "Bob_2", rAB);
	system("pause");
	//获取r3
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 3：从第三方接收约定参数r3\n";
	cout << "   > 交换过程如下\n";
	basic.Recieve_Agreement_Number("Alice_2", "Third_2", r3);
	system("pause");
	//计算 r3 +(g^rAB * h^r3)mod p的真实值
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 4：计算承诺\n";
	cout << "     计算方法为：C = (g^rAB * h^r3)mod p\n";
	basic.Pedersen_Commit(rAB, r3, commit);
	return true;
}

bool Person::Menu()
{
	Vision('g');
	char c; cin >> c;
	while (c < '0' || c>'4')
	{
		cout << "\n  ·输入错误，请重新选择:";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	cin.ignore(1024, '\n');
	if (c == '0') return false;
	else if (c == '1') grade = basic.A_Class;
	else if (c == '2')grade = basic.B_Class;
	else if (c == '3')grade = basic.C_Class;
	else grade = basic.D_Class;
	return true;
}

bool Person::Choose()
{
	cout << "   ╭════════════════════════╮\n";
	cout << "   ║    > 1 发送实际值      ║\n";
	cout << "   ║    --------------      ║\n";
	cout << "   ║    > 0  CHEET          ║\n";
	cout << "   ╰════════════════════════╯\n";
	cout << "   ·请选择操作:";
	char c; cin >> c;
	while (c != '0' && c != '1')
	{
		cout << "\n  ·输入错误，请重新选择:";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	cin.ignore(1024, '\n');
	if (c == '1') return true;
	else return false;
}

bool Person::Check()
{
	//文件不存在，则无人退出
	if ((remove("End.txt") == EOF))
		return true;
	system("CLS"); system("color 04");
	cout << "\n\n";
	cout << "     * * * * * * * * * * * * * *\n";
	cout << "       Bob / 第三方 已退出游戏\n";
	cout << "        请按任意键以重新开始\n";
	cout << "     * * * * * * * * * * * * * *\n\n       ";
	system("pause");
	return false;
}

bool Person::Judge()
{
		cout << "             *判断结果*\n";
		cout << "  ╭════════════════════════════╮\n";
	if (mpz_cmp(commit, recive) == 0)
	{
		cout << "  ║     得到的信息大整数 M'    ║\n";
		cout << "  ║    = (g^rAB * h^r3)mod p   ║\n";
		cout << "  ║   所以，Bob成绩和自己的    ║\n";
		cout << "  ║      = = = 相同 = = =      ║\n";
		cout << "  ╰════════════════════════════╯\n\n";
		return true;
	}
		cout << "  ║     得到的信息大整数 M'    ║\n";
		cout << "  ║   != (g^rAB * h^r3)mod p   ║\n";
		cout << "  ║    所以，Bob成绩和自己的   ║\n";
		cout << "  ║     * * * 不相同 * * *     ║\n";
		cout << "  ╰════════════════════════════╯\n\n";
		return false;
}

void Person::Game()
{
	remove("End.txt");
	while (1)
	{
		system("color F4");
		//选择菜单
		if (Check() == false)continue;
		if (Menu() == false) break;
		//初始化各类公钥传递信息
		if (Init() == false) continue;
		//Sleep(2000);
		system("pause");

		//接收Third发送的信息
		if (Check() == false)continue;
		Vision('r');
		while (basic.Recive_Message("Third_Send.txt", recive) == false)
			Sleep(1000);

		//判断是否相同
		Vision('j');
		Judge();
		gmp_printf("   (g^rAB * h^r3)mod p = %Zd\n", commit);
		system("pause");
	}//while(1)

	//通知Bob、第三方，已退出
	remove("Bob_2\\rAB.txt");
	basic.Send_Message("Bob_2\\End.txt", 0);
	basic.Send_Message("Third_2\\End.txt", 0);
}

void Vision(char choose)
{
		system("CLS");
		cout << "       ║·Alice当前进程·║\n";
		cout << "       ╰-----------------╯\n\n";
	switch (choose)
	{
	case '0':
		cout << "       ╭-----------------╮\n";
		cout << "       ║  > 初始化阶段 < ║\n";
		cout << "       ╰-----------------╯\n";
		break;
	case 'g':
		cout << "             成绩选择\n";
		cout << "   ╭════════════════════════╮\n";
		cout << "   ║   > 1 优     > 2 良    ║\n";
		cout << "   ║   -----------------    ║\n";
		cout << "   ║   > 3 中     > 4 差    ║\n";
		cout << "   ║   -----------------    ║\n";
		cout << "   ║     > 0 退出游戏       ║\n";
		cout << "   ╰════════════════════════╯\n";
		cout << "    ·请选择:";
		break;
	case 'r':
		cout << "      等待第三方发送密文…\n";
		break;
	case 'j':
		cout << "   > 已收到来自第三方发送的密文：\n";
		gmp_printf("   %Zd\n", alice.recive);
		cout << " ╭════════════════════════════════════════════╮\n";
		cout << "   该信息由来：\n";
		cout << "\n";
		cout << "   < 1  Bob计算 M = (g^rAB * h^r3)mod p\n";
		cout << "   < 2  Bob用Bob成绩对应公钥加密M后发给第三方\n";
		cout << "   < 3  第三方用Alice成绩对应私钥解密得 M'\n";
		cout << "   < 4  第三方将 M' 发送给ALice和Bob\n";
		cout << " ╰════════════════════════════════════════════╯\n";
		break;
	default:
		cout << "Vision()函数参数错误\n";
		break;
	}
}
