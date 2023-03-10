#include "Person.h"

Person third;

Person::Person()
{mpz_inits( r3, send, temp, public_key, NULL);}

bool Person::Init()
{
	//接收Alice成绩
	if (Check() == false) return false;
	Vision('0');
	while (basic.Recive_Message("Alice_Grade.txt", alice_grade) == false)
		Sleep(1000);
	cout << "   > Step 1：接收到Alice成绩为：" << alice_grade << "\n";
	system("pause");
	//发送约定随机数r3给Alice
	if (Check() == false) return false;
	mpz_urandomm(r3, seed, basic.p);
	Vision('0');
	cout << "   > Step 2：发送约定参数r3给Alice\n";
	cout << "     参数 r3 实际值为：\n";
	gmp_printf("  %Zd\n", r3);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_2", "Alice_2", r3);
	Sleep(2000);
	//发送约定随机数r3给Bob
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 2：发送约定参数r3给Bob\n";
	cout << "     参数 r3 实际值为：\n";
	gmp_printf("  %Zd\n", r3);
	cout << "   > 交换过程如下\n";
	basic.Send_Agreement_Number("Third_2", "Bob_2", r3);
	system("pause");
	//产生4种成绩对应的不同公私钥，发送所有公钥给Bob
	//A_Class
	if (Check() == false) return false;
	Vision('0');
	cout << "   > Step 3：产生四个成绩分别对应的密钥对，并公开公钥\n";
	cout << "     并保存Alice成绩所对应的私钥\n";
	cout << "   > 各密钥对数据如下：\n";
	cout << " ======================================================\n";
	cout << "·成绩优 对应公私钥为（公钥已发送给Bob）：\n";
	basic.Creat_Key(key, public_key);
	unsigned int mark = key;
	if (alice_grade == basic.A_Class) alice_key = key;
	basic.Send_Message("Bob_2\\A_Class_Public_Key.txt", public_key);

	cout << "私钥=" << key << "\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
	//B_Class
	cout << "·成绩良 对应公私钥为（公钥已发送给Bob）：\n";
	while(key==mark)
		basic.Creat_Key(key, public_key);
	mark = key;
	if (alice_grade == basic.B_Class) alice_key = key;
	basic.Send_Message("Bob_2\\B_Class_Public_Key.txt", public_key);

	cout << "私钥=" << key << "\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
	//C_Class
	cout << "·成绩中 对应公私钥为（公钥已发送给Bob）：\n";
	while (key == mark)
		basic.Creat_Key(key, public_key);
	mark = key;
	if (alice_grade == basic.C_Class) alice_key = key;
	basic.Send_Message("Bob_2\\C_Class_Public_Key.txt", public_key);

	cout << "私钥=" << key << "\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
	//D_Class
	cout << "·成绩差 优对应公私钥为（公钥已发送给Bob）：\n";
	while (key == mark)
		basic.Creat_Key(key, public_key);
	mark = key;
	if (alice_grade == basic.D_Class) alice_key = key;
	basic.Send_Message("Bob_2\\D_Class_Public_Key.txt", public_key);

	cout << "私钥=" << key << "\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
	cout << " ======================================================\n";
	cout << "                      发送完成\n   ";
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
		
		//接收Bob发送的密文
		if (Check() == false)continue;
		Vision('r');
		while (basic.Recive_Message("Bob_Send.txt", recive2) == false)
			Sleep(1000);
		basic.ElGamal_Unlock(alice_key, recive2, send);
		system("pause");
		//Sleep(2000);

		//发送解得明文给ALice、Bob
		if (Check() == false)continue;
		Vision('s');
		basic.Send_Message("Alice_2\\Third_Send.txt", send);
		basic.Send_Message("Bob_2\\Third_Send.txt", send);
		cout << "\n    * * * * 信息发送完成* * * *\n\n   "; Sleep(100);
		system("pause");
	}//while(1)

	//通知Alice、Bob，已退出
	remove("Alice_2\\Third_Send.txt"); remove("Alice_2\\r3.txt");
	remove("Bob_2\\Third_Send.txt"); remove("Bob_2\\r3.txt");
	remove("Bob_2\\A_Class_Public_Key"); remove("Bob_2\\B_Class_Public_Key"); 
	remove("Bob_2\\C_Class_Public_Key"); remove("Bob_2\\D_Class_Public_Key");
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
		cout << "        ╭-----------------╮\n";
		cout << "        ║  > 初始化阶段 < ║\n";
		cout << "        ╰-----------------╯\n";
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
	case 'r':
		cout << "   > 等待Bob发送密文\n";
		cout << "     密文为Bob的Pedersen承诺\n"; Sleep(500);
		cout << "   > 等待中…";
		break;
	case 's':
		cout << "   该信息由来：\n";
		cout << " ╭════════════════════════════════════════════╮\n";
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

