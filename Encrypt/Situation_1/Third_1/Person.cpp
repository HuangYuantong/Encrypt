#include "Person.h"

Person third;

Person::Person()
{
	mpz_inits(alice_public_key, recive, bob_public_key, temp, NULL);
}

bool Person::Init()
{
	//接收Alice和Bob成绩
	if (Check() == false) return false;
	Vision('0');
	while (basic.Recive_Message("Alice_Grade.txt",alice_grade) == false)
		Sleep(1000);
	if (Check() == false) return false;
	while (basic.Recive_Message("Bob_Grade.txt", bob_grade) == false)
		Sleep(1000);
	//生成Alice和Bob的密钥
	Vision('s');
	basic.Creat_Key(alice_key, alice_public_key);
	if (alice_grade != bob_grade)
		basic.Creat_Key(bob_key, bob_public_key);
	else
	{
		bob_key = alice_key;
		mpz_set(bob_public_key, alice_public_key);
	}
	//发送Alice和Bob的密钥
	basic.Send_Message("Alice_1//Key.txt", alice_key, alice_public_key);
	basic.Send_Message("Bob_1//Key.txt", bob_key, bob_public_key);
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
	cout << "       Alice / Bob 已退出游戏\n";
	cout << "        请按任意键以重新开始\n";
	cout << "     * * * * * * * * * * * * * *\n\n       ";
	system("pause");
	return false;
}

bool Person::Judge()
{
	Vision('w');
	bool temp_cheet = false;
	//检测Alice是否作弊
	cout << "  > 检测Alice的成绩中…\n";
	while (basic.Recive_Message("Alice_Send.txt", recive_alice) == false)
		Sleep(1000);
	basic.ElGamal_Unlock(alice_key, recive_alice, recive);
	if (mpz_cmp_ui(recive, alice_grade) != 0)
	{
		basic.Send_Message("Alice_1//Cheet_Warning.txt", 0);
		basic.Send_Message("Bob_1//Cheet_Warning.txt", 0);
		cout << "     * * * * * * * * * * * * * *\n";
		cout << "           Alice发送的密文\n";
		cout << "       与其实际成绩不符，作弊\n"; Sleep(200);
		cout << "         已向双方发送警告\n";
		cout << "     * * * * * * * * * * * * * *\n\n       ";
		temp_cheet = true;
	}
	//检测Bob是否作弊
	cout << "  > 检测Bob的成绩中…\n";
	while (basic.Recive_Message("Bob_Send.txt", recive_bob) == false)
		Sleep(1000);
	basic.ElGamal_Unlock(bob_key, recive_bob, recive);
	if (mpz_cmp_ui(recive, bob_grade) != 0)
	{
		basic.Send_Message("Alice_1//Cheet_Warning.txt", 0);
		basic.Send_Message("Bob_1//Cheet_Warning.txt", 0);
		cout << "     * * * * * * * * * * * * * *\n";
		cout << "           Bob发送的密文\n";
		cout << "       与其实际成绩不符，作弊\n"; Sleep(200);
		cout << "         已向双方发送警告\n";
		cout << "     * * * * * * * * * * * * * *\n\n       ";
		temp_cheet = true;
	}
	if (temp_cheet == true) 
		return false;
	cout << "               *判断结果*\n";
	cout << "  ╭══════════════════════════════╮\n";
	cout << "  ║     -本轮游戏中无人作弊-     ║\n";
	cout << "  ║    已将二人消息转发给对方    ║\n";
	cout << "  ╰══════════════════════════════╯\n\n";
	return true;
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
		Init();
		system("pause");
		//检测Alice和Bob是否作弊
		if (Judge() == false)
		{
			system("pause");
			continue;
		}
		else
		{
			basic.Send_Message("Alice_1\\Third_Send.txt", recive_bob);
			basic.Send_Message("Bob_1\\Third_Send.txt", recive_alice);
		}
		system("pause");
	}//while(1)

	//通知Alice、Bob，已退出
	remove("Alice_1\\Key.txt"), remove("Bob_1\\Key.txt");
	remove("Alice_1\\Third_Send.txt"), remove("Bob_1\\Third_Send.txt");
	basic.Send_Message("Alice_1\\End.txt", 0);
	basic.Send_Message("Bob_1\\End.txt", 0);
}

void Vision(char choose)
{
	system("CLS");
	cout << "       ║·第三方当前进程·║\n";
	cout << "       ╰------------------╯\n\n";
	switch (choose)
	{
	case '0':
		cout << "     等待Alice和Bob加入游戏…\n";
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
	case 's':
		cout << "                密钥分配\n";
		cout << " ╭═════════════════════════════════╮\n";
		cout << "\n";
		cout << "   < Alice成绩为：" << third.alice_grade << "\n";
		cout << "      Bob 成绩为：" << third.bob_grade << "\n";
		cout << "   --------------------------------\n"; Sleep(200);
		if (third.alice_grade != third.bob_grade)
		cout << "    两人成绩不同，将发送不同密钥对\n";
		else
		cout << "    两人成绩相同，将发送相同密钥对\n";
		cout << " ╰═════════════════════════════════╯\n";		
		break;
	case 'w':
		cout << "       ╭------------------╮\n";
		cout << "       ║  ·作弊监测中·  ║\n";
		cout << "       ╰------------------╯\n";
		break;
	default:
		cout << "Vision()函数参数错误\n";
		break;
	}
}

