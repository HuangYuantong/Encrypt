#include "Person.h"
Person alice;

Person::Person(){mpz_inits( public_key, recive, temp, NULL);}

bool Person::Init()
{
	//告诉第三方自己的成绩
	basic.Send_Message("Third_1\\Alice_Grade.txt", grade);
	//从第三方获取公钥、私钥
	if (Check() == false) return false;
	Vision('0');
	while (basic.Recive_Message("Key.txt", key, public_key) == false)
		Sleep(1000);
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
	Sleep(400);
		cout << "              *判断结果*\n";
		cout << "  ╭══════════════════════════════╮\n";
		cout << "  ║     -本轮游戏中无人作弊-     ║\n";
	if (mpz_cmp_ui(recive, grade) == 0)
	{
		cout << "  ║ 解得Bob发送明文与我方成绩相同║\n";
		cout << "  ║     所以，Bob成绩和自己的    ║\n";
		cout << "  ║       = = = 相同 = = =       ║\n";
		cout << "  ╰══════════════════════════════╯\n\n";
		return true;
	}
		cout << "  ║ 解得Bob发送明文与我方成绩不同║\n";
		cout << "  ║     所以，Bob成绩和自己的    ║\n";
		cout << "  ║      * * * 不相同 * * *      ║\n";
		cout << "  ╰══════════════════════════════╯\n\n";
		return true;
}

void Person::Game()
{
	remove("End.txt"); remove("Cheet_Warning.txt");
	while (1)
	{
		system("color F4");
		//选择菜单
		if (Check() == false)continue;
		if (Menu() == false) break;
		//初始化各类公钥传递信息
		if (Check() == false)continue;
		if (Init() == false) continue;
		system("pause");

		//用自己的密钥加密成绩发给第三方
		if (Check() == false)continue;
		Vision('a');
		if (Choose() == true)
			basic.ElGamal_Lock(Random(), public_key, grade, send2);
		else
		{
			mpz_urandomm(send2.C1, seed, basic.p);
			mpz_urandomm(send2.C2, seed, basic.p);
			cout << "   > 已使用随机值发送\n"; Sleep(100);
			gmp_printf(" C1 = %Zd\n C2 = %Zd\n", send2.C1, send2.C2); Sleep(200);
		}
		cout << "    ======发送完成======\n\n";
		basic.Send_Message("Third_1\\Alice_Send.txt", send2);
		//Sleep(2000);
		system("pause");

		//接收第三方发送:是否作弊的通知/Bob成绩密文
		if (Check() == false)continue;
		Vision('r');
		while (1)
		{
			//收到作弊警告
			if ((remove("Cheet_Warning.txt") != EOF))
			{
				Vision('c');
				break;
			}
			//收到第三方发送的Bob的成绩信息
			if (basic.Recive_Message("Third_Send.txt", recive2) == true)
			{
				//用自己密钥解密，判断是否相同
				basic.ElGamal_Unlock(key, recive2, recive);
				Vision('j');
				Judge();
				break;
			}
		}
		system("pause");
	}//while(1)

	//通知Bob、第三方，已退出
	remove("Third_1\\Alice_Grade.txt"),remove("Third_1\\Alice_Send.txt");
	basic.Send_Message("Bob_1\\End.txt", 0);
	basic.Send_Message("Third_1\\End.txt", 0);
}

void Vision(char choose)
{
		system("CLS");
		cout << "       ║·Alice当前进程·║\n";
		cout << "       ╰-----------------╯\n\n";
	switch (choose)
	{
	case '0':
		cout << "     等待Bob和第三方加入游戏…\n";
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
	case 'a':
		cout << "   > 下一步将：使用第三方提供的密钥进行成绩加密\n"; Sleep(600);
		cout << "     再将密文（C1，C2）发送给第三方\n"; Sleep(600);
		break;
	case 'r':
		cout << "      等待第三方发送消息…\n";
		break;
	case 'j':
		cout << "   > 已收到来第自三方发送的密文：\n";
		cout << "     Bob使用第三方提供给他的公钥进行加密\n";
		cout << "   > 若成绩相同，则使用的公钥与我方相同\n";
		cout << "     因而使用我方密钥解密得到的明文，与我方成绩相同\n";
		cout << "   > 反之明文与我方成绩不同\n\n";
		break;
	case 'c':
		system("color 04");
		cout << "             *Cheeing警告*\n"; Sleep(500);
		cout << "  ╭══════════════════════════════╮\n";
		cout << "  ║ 收到来自第三方的作弊检测警告 ║\n";
		cout << "  ║      本轮游戏中有人作弊      ║\n"; Sleep(500);
		cout << "  ║          已终止游戏          ║\n";
		cout << "  ╰══════════════════════════════╯\n\n";
		break;
	default:
		cout << "Vision()函数参数错误\n";
		break;
	}
}
