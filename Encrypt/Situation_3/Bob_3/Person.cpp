#include "Person.h"

Person bob;

Person::Person() { mpz_inits(rBC, rAB, r3, recive, commit, send, temp, NULL); }

bool Person::Init()
{
	//从Alice获取rAC
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 1：等待Alice发送约定参数rAB\n";
	cout << "     双方约定 rAB 为计算Pedersen承诺时使用的参数\n";
	cout << "   > 交换过程如下\n";
	basic.Recieve_Agreement_Number("Bob_3", "Alice_3", rAB);
	system("pause");
	//从第三方获取rBC
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 2：等待第三方发送约定参数rBC\n";
	cout << "   > 交换过程如下\n";
	basic.Recieve_Agreement_Number("Bob_3", "Third_3", rBC);
	Sleep(2000);
	//从第三方获取r3
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 3：等待第三方发送约定参数r3\n";
	cout << "   > 交换过程如下\n";
	basic.Recieve_Agreement_Number("Bob_3", "Third_3", r3);
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
	cout << "       Alice / 第三方 已退出游戏\n";
	cout << "        请按任意键以重新开始\n";
	cout << "     * * * * * * * * * * * * * *\n\n       ";
	system("pause");
	return false;
}

bool Person::Judge()
{
	cout << "             *判断结果*\n";
	cout << "  ╭════════════════════════════╮\n";
	if (mpz_cmp(recive, r3) == 0)
	{
	cout << "  ║  得到的信息大整数 M = r3   ║\n";
	cout << "  ║  所以，Alice成绩和自己的   ║\n";
	cout << "  ║      = = = 相同 = = =      ║\n";
	cout << "  ╰════════════════════════════╯\n\n";
		return true;
	}
	cout << "  ║  得到的信息大整数 M != r3  ║\n";
	cout << "  ║  所以，Alice成绩和自己的   ║\n";
	cout << "  ║     * * * 不相同 * * *     ║\n";
	cout << "  ╰════════════════════════════╯\n\n";
	return false;
}

void Person::Game()
{
	remove("End.txt");
	while (1)
	{
		system("color F9");
		//选择菜单
		if (Check() == false)continue;
		if (Menu() == false) break;
		//初始化各类公钥传递信息
		if (Init() == false) continue;
		//Sleep(2000);
		system("pause");
		//发送承诺给第三方
		if (Check() == false)continue;
		Vision('s');
		if (Choose() == true)
		{
			cout << "    ======发送完成======\n";
			mpz_powm(temp, basic.Pedersen_g, rAB, basic.p);
			mpz_powm_ui(commit, basic.Pedersen_g, grade, basic.p);
			//basic.Pedersen_Commit(rAB, grade, commit);
			gmp_printf("  计算得承诺为：%Zd\n", commit);
			mpz_add(send, commit, rBC);
		}
		else
		{
			cout << "  · Cheeting后发送的随机大整数为：\n";
			mpz_urandomm(send, seed, basic.p);
			gmp_printf("   %Zd\n", send);
			cout << "    ======发送完成======\n    ";
		}
		basic.Send_Message("Third_3\\Bob_Send.txt", send);
		//Sleep(3000);
		system("pause");

		//接收Third发送的信息
		if (Check() == false)continue;
		Vision('r');
		while (basic.Recive_Message("Third_Send.txt", recive) == false)
			Sleep(1000);
		//判断是否相同
		Vision('j');
		Judge();
		system("pause");
	}//while(1)

	//通知Alice、第三方，已退出
	remove("Third_3\\Bob_Send.txt");
	basic.Send_Message("Alice_3\\End.txt", 0);
	basic.Send_Message("Alice_3\\End.txt", 0);
}

void Vision(char choose)
{
	system("CLS");
		cout << "       ║ ·Bob当前进程· ║\n";
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
	case 's':
		cout << "   > 现在即将计算Pedersen承诺: C = (g^rAB)^SB mod p\n";
		cout << "     再加上与第三方约定随机数 rBC 后，发送给第三方\n"; Sleep(1000);
		break;
	case 'r':
		cout << "      等待第三方发送密文…\n";
		break;
	case 'j':
		cout << "   > 已收到来自第三方发送的密文：\n";
		gmp_printf("   %Zd\n", bob.recive);
		cout << " ╭════════════════════════════════════════════╮\n";
		cout << "\n";
		cout << "   因为第三方处理：\n";
		cout << "\n";
		cout << "   < 1  N = Alice承诺 - Bob承诺\n";
		cout << "   -------------------------------\n";
		cout << "   < 2  M = (N * y^r)mod p + r3\n";
		cout << "                  （其中y为第三方公钥，r为随机数）\n";
		cout << " ╰════════════════════════════════════════════╯\n";
		break;
	default:
		cout << "Vision()函数参数错误\n";
		break;
	}
}
