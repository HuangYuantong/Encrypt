#include "Person.h"

Person third;

Person::Person()
{mpz_inits(public_key, rAC, rBC, r3, recive1, recive2, commit1, commit2, send, temp, NULL);}

bool Person::Init()
{
	cout << "   > 等待ALice和Bob加入游戏…\n";
	cout << "   > 发送的约定参数值分别为：\n";
	gmp_printf("   rAC = %Zd\n", third.rAC);
	gmp_printf("   rBC = %Zd\n", third.rBC);
	gmp_printf("   r3 = %Zd\n", third.r3);

	mpz_urandomm(rAC, seed, basic.p);
	mpz_urandomm(rBC, seed, basic.p);
	mpz_urandomm(r3, seed, basic.p);
	basic.Creat_Key(key, public_key);
	//发送约定随机数rAC给Alice
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 1：发送数 rAC 给Alice\n";
	cout << "     参数 rAC 实际值为：";
	gmp_printf(" %Zd\n", rAC);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_3", "Alice_3", rAC);
	Sleep(2000);
	//发送约定随机数r3给Alice
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 1：发送数 r3 给Alice\n";
	cout << "     参数 r3 实际值为：";
	gmp_printf(" %Zd\n", r3);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_3", "Alice_3", r3);
	system("pause");
	//发送约定随机数rBC给Bob
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 2：发送数 rBC 给Bob\n";
	cout << "     参数 rBC 实际值为：";
	gmp_printf(" %Zd\n", rBC);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_3", "Bob_3", rBC);
	Sleep(2000);
	//发送约定随机数r3给Bob
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 2：发送数 r3 给Bob\n";
	cout << "     参数 r3 实际值为：";
	gmp_printf(" %Zd\n", r3);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_3", "Bob_3", r3);
	return true;
}

bool Person::Menu()
{
	Vision('g');
	char c; cin >> c;
	while (c < '0' || c>'1')
	{
		cout << "\n  ·输入错误，请重新选择:";
		cin.ignore(1024, '\n');
		cin >> c;
	}
	cin.ignore(1024, '\n');
	if (c == '0') return false;
	return true;
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

void Person::Game()
{
	remove("End.txt");
	while (1)
	{
		system("color 70");
		//选择菜单
		if (Check() == false)continue;
		if (Menu() == false) break;
		//初始化各类公钥传递信息
		if (Check() == false) continue;
		if (Init() == false) continue;
		//Sleep(2000);
		system("pause");
		//接收Alice发送的密文
		if (Check() == false)continue;
		Vision('a');
		while (basic.Recive_Message("Alice_Send.txt", recive1) == false)
			Sleep(1000);
		mpz_sub(commit1, recive1, rAC);
		cout << "\r  · 已收到Alice的承诺：";
		gmp_printf("%Zd\n", commit1);
		system("pause");
		//Sleep(2000);

		//接收Bob发送的密文
		if (Check() == false)continue;
		Vision('b');
		while (basic.Recive_Message("Bob_Send.txt", recive2) == false)
			Sleep(1000);
		mpz_sub(commit2, recive2, rBC);
		cout << "\r  · 已收到Bob的承诺：";
		gmp_printf("%Zd\n", commit2);
		system("pause");
		//Sleep(2000);

		//处理待分析信息
		if (Check() == false)continue;
		Vision('s');
		mpz_sub(send, commit1, commit2);
		gmp_printf("     1、求得 N = %Zd\n", send);
		basic.ElGamal_Lock(Random(), public_key, send, temp);
		mpz_add(send, temp, r3);
		gmp_printf("     2、加密得 M = %Zd\n", send);
		basic.Send_Message("Alice_3\\Third_Send.txt", send);
		basic.Send_Message("Bob_3\\Third_Send.txt", send);
		cout << "\n    * * * * 信息发送完成* * * *\n\n   "; Sleep(100);
		system("pause");

	}//while(1)

	//通知Alice、Bob，已退出
	remove("Alice_3\\Third_Send.txt"); remove("Alice_3\\rAC.txt"); remove("Alice_3\\r3.txt");
	remove("Bob_3\\Third_Send.txt"); remove("Bob_3\\rBC.txt"); remove("Bob_3\\r3.txt");
	basic.Send_Message("Alice_3\\End.txt", 0);
	basic.Send_Message("Bob_3\\End.txt", 0);
}

void Vision(char choose)
{
	system("CLS");
		cout << "       ║·第三方当前进程·║\n";
		cout << "       ╰------------------╯\n\n";
	switch (choose)
	{
	case '0':
		cout << "       ╭-----------------╮\n";
		cout << "       ║  > 初始化阶段 < ║\n";
		cout << "       ╰-----------------╯\n";
		break;
	case 'g':
		cout << "             模式选择\n";
		cout << "   ╭═══════════════════════╮\n";
		cout << "   ║  > 1 进入游戏         ║\n";
		cout << "   ║    ------------       ║\n";
		cout << "   ║        > 0  退出游戏  ║\n";
		cout << "   ╰═══════════════════════╯\n";
		cout << "    ·请选择:";
		break;
	case 'a':
		cout << "   > 等待Alice发送密文\n";
		cout << "     密文为Alice的Pedersen承诺 + rAC\n"; Sleep(500);
		cout << "   > 等待中…";
		break;
	case 'b':
		cout << "	> 等待Bob发送密文\n";
		cout << "     密文为Bob的Pedersen承诺 + rBC\n"; Sleep(500);
		cout << "   > 等待中…";
		break;
	case 's':
		cout << "   数据处理步骤：\n";
		cout << " ╭═══════════════════════════════════════════╮\n";
		cout << "\n";
		cout << "   < 1  N = Alice承诺 - Bob承诺\n";
		cout << "   -------------------------------\n";
		cout << "   < 2  M = (N * y^r)mod p + r3\n";
		cout << "                  （其中y为我方公钥，r为随机数）\n";
		cout << " ╰═══════════════════════════════════════════╯\n";
		break;
	default:
		cout << "Vision()函数参数错误\n";
		break;
	}
}

