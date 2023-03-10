#include "Basic.h"

Basic basic;
gmp_randstate_t seed;
string Location = "D:\\&Code\\VS\\AB\\Situation_2\\";

Basic::Basic()
{
	mpz_inits(p, Elgamal_g, Pedersen_g, Pedersen_h, NULL);
	mpz_set_str(p, Content_In_p_txt, Base);
	mpz_set_str(Elgamal_g, Content_In_Elgamal_g_txt, Base);
	mpz_set_str(Pedersen_g, Content_In_Pedersen_g_txt, Base);
	mpz_set_str(Pedersen_h, Content_In_Pedersen_h_txt, Base);
	A_Class = L'优'; B_Class = L'良';
	C_Class = L'中'; D_Class = L'差';
	gmp_randinit_default(seed);
	gmp_randseed_ui(seed, Random());
	mpz_inits(t1, t2, t3, NULL);
}

void Basic::Creat_Key(unsigned int& key, mpz_t& public_key)
{
	key = Random();
	mpz_powm_ui(public_key, Elgamal_g, key, p);
	cout << "生成密钥对，私钥=" << key<<"\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
}

bool Basic::Send_Message(string file_name, mpz_t& Message)
{
	file_name = Location + file_name;
	FILE* outfile = fopen(file_name.c_str(), "w");
	if (!outfile) return false;
	mpz_out_str(outfile, File_Base, Message);
	fclose(outfile);
	return true;
}

bool Basic::Send_Message(string file_name, Message& Message)
{
	file_name = Location + file_name;
	FILE* outfile = fopen(file_name.c_str(), "w");
	if (!outfile) return false;
	mpz_out_str(outfile, File_Base, Message.C1);
	fprintf(outfile, "\n");
	mpz_out_str(outfile, File_Base, Message.C2);
	fclose(outfile);
	return true;
}

bool Basic::Send_Message(string file_name, unsigned int Message)
{
	file_name = Location + file_name;
	fstream outfile(file_name, ios::out);
	if (!outfile) return false;
	outfile << Message;
	outfile.close();
	return true;
}

bool Basic::Send_Message(string file_name, unsigned int key, mpz_t& public_key)
{
	file_name = Location + file_name;
	FILE* outfile = fopen(file_name.c_str(), "w");
	if (!outfile) return false;
	fprintf(outfile, "%d\n", key);
	mpz_out_str(outfile, File_Base, public_key);
	fclose(outfile);
	return true;
}

bool Basic::Recive_Message(const char* file_name, mpz_t& Message)
{
	fstream infile(file_name, ios::in);
	if (!infile) return false;
	string temp = ""; infile >> temp;
	mpz_set_str(Message, temp.c_str(), File_Base);
	infile.close();
	gmp_printf("%Zd\n\n", Message);
	remove(file_name);
	return true;
}

bool Basic::Recive_Message(const char* file_name, Message& Message)
{
	fstream infile(file_name, ios::in);
	if (!infile) return false;
	string str; infile >> str;
	mpz_set_str(Message.C1, str.c_str(), File_Base);
	infile >> str;
	mpz_set_str(Message.C2, str.c_str(), File_Base);
	infile.close();
	gmp_printf("收到密文:\nC1=%Zd\nC2=%Zd\n\n", Message.C1, Message.C2);
	remove(file_name);
	return true;
}

bool Basic::Recive_Message(const char* file_name, unsigned int& Message)
{
	fstream infile(file_name, ios::in);
	if (!infile) return false;
	infile >> Message;
	infile.close();
	remove(file_name);
	return true;
}

bool Basic::Recive_Message(const char* file_name, unsigned int& key, mpz_t& public_key)
{
	fstream infile(file_name, ios::in);
	if (!infile) return false;
	infile >> key;
	string str; infile >> str;
	mpz_set_str(public_key, str.c_str(), File_Base);
	infile.close();
	cout << "收到密钥对，私钥=" << key << "\n";
	gmp_printf("公钥=%Zd\n\n", public_key);
	remove(file_name);
	return true;
}

void Basic::ElGamal_Lock(unsigned int random, mpz_t& public_key, unsigned int send, Message& Message)
{
	//C1=g^r(mod p)
	mpz_powm_ui(Message.C1, Elgamal_g, random, p);
	//C2= [M*( y^r(mod p) )] mod p
	mpz_powm_ui(t1, public_key, random, p);
	mpz_mul_ui(t2, t1, send);
	mpz_mod(Message.C2, t2, p);
	gmp_printf("生成密文:\nC1=%Zd\nC2=%Zd\n\n", Message.C1, Message.C2);
}

void Basic::ElGamal_Lock(unsigned int random, mpz_t& public_key, unsigned int send, mpz_t& Message)
{
	//C2= [M*( y^r(mod p) )] mod p
	mpz_powm_ui(t1, public_key, random, p);
	mpz_mul_ui(t2, t1, send);
	mpz_mod(Message, t2, p);
	gmp_printf("生成密文:\nC2=%Zd\n\n", Message);
}

void Basic::ElGamal_Lock(unsigned int random, mpz_t& public_key, mpz_t& send, Message& Message)
{
	//C1=g^r(mod p)
	mpz_powm_ui(Message.C1, Elgamal_g, random, p);
	//C2= [M*( y^r(mod p) )] mod p
	mpz_powm_ui(t1, public_key, random, p);
	mpz_mul(t2, t1, send);
	mpz_mod(Message.C2, t2, p);
	gmp_printf("生成密文:\nC1=%Zd\nC2=%Zd\n\n", Message.C1, Message.C2);
}

void Basic::ElGamal_Lock(unsigned int random, mpz_t& public_key, mpz_t& send, mpz_t& Message)
{
	//C2= [M*( y^r(mod p) )] mod p
	mpz_powm_ui(t1, public_key, random, p);
	mpz_mul(t2, send, t1);
	mpz_mod(Message, t2, p);
	gmp_printf("生成密文:\nC2=%Zd\n\n", Message);
}

void Basic::ElGamal_Unlock(unsigned int key, Message& Message, mpz_t& recived)
{
	//M= [C2 * invert_C1^x(mod p)] mod p
	mpz_powm_ui(t2, Message.C1, key, p);
	mpz_invert(t3, t2, p);
	mpz_mul(t1, Message.C2, t3);
	mpz_mod(recived, t1, p);
	gmp_printf("解得明文: %Zd\n\n", recived);
}

void Basic::Pedersen_Commit(unsigned int random, unsigned int send, mpz_t& Message)
{
	//C = [g^r(mod p) * h^M(mod p)]mod p
	mpz_powm_ui(t1, Pedersen_g, random, p);
	mpz_powm_ui(t2, Pedersen_h, send, p);
	mpz_mul(t3, t1, t2);
	mpz_mod(Message, t3, p);
	gmp_printf("生成承诺: %Zd\n\n", Message);
}

void Basic::Pedersen_Commit(mpz_t& random, mpz_t& send, mpz_t& Message)
{
	//C = [g^r(mod p) * h^M(mod p)]mod p
	mpz_powm(t1, Pedersen_g, random, p);
	mpz_powm(t2, Pedersen_h, send, p);
	mpz_mul(t3, t1, t2);
	mpz_mod(Message, t3, p);
	gmp_printf("生成承诺: %Zd\n\n", Message);
}

bool Basic::Send_Agreement_Number(string my_name, string people_name, mpz_t& Number)
{
	cout << " ======================================================\n";
	//先接收people_name的临时公钥,放于t1
	//对方公钥统一命名为"SAN_Xxx_Temp_Public_Key.txt"
	string file_name = "SAN_" + people_name + "_Temp_Public_Key.txt";
	cout << " 收到" << people_name << "的临时公钥为：";
	while (Recive_Message(file_name.c_str(), t1) == false)
		Sleep(1000);
	//将约定数用people_name公钥加密
	//发送的文件统一命名为"people_name\\SAN_Xxx_Temp_Send.txt"
	file_name = people_name + "\\\\SAN_" + my_name + "_Temp_Send.txt";
	Message send;
	ElGamal_Lock(Random(), t1, Number, send);
	if (Send_Message(file_name.c_str(), send) == false)
		return false;
	cout << " 向" << people_name << "发送约定参数完成\n";
	cout << " ======================================================\n";
	cout << "                约定参数交换完成\n";
	return true;
}

bool Basic::Recieve_Agreement_Number(string my_name, string people_name, mpz_t& Number)
{
	cout << " ======================================================\n";
	//先产生临时密钥对，公钥放于t1
	unsigned int temp_key = Random();
	Creat_Key(temp_key, t1);
	//发送公钥给people_name，统一命名为"people_name\\SAN_Xxx_Temp_Public_Key.txt"
	string file_name = people_name + "\\\\SAN_" + my_name + "_Temp_Public_Key.txt";
	if (Send_Message(file_name, t1) == false)
		return false;
	cout << " 向" << people_name << "发送我方临时公钥完成\n";
	//接收对方发送的密文，文件统一命名为"SAN_Xxx_Temp_Send.txt"
	cout << " 来自" << people_name << "，";
	Message recive;
	file_name = "SAN_" + people_name + "_Temp_Send.txt";
	while (Recive_Message(file_name.c_str(), recive) == false)
		Sleep(1000);
	//解密得到约定参数
	ElGamal_Unlock(temp_key, recive, Number);
	cout << " ======================================================\n";
	cout << "                约定参数交换完成\n";
	return true;
}

unsigned int Random()
{
	srand((unsigned)time(NULL));
	unsigned int random;
	while ((random = rand()) < 5000);
	return random;
}