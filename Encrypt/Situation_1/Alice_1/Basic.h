#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <Windows.h>
#include <string>
#include  <gmp.h>
using namespace std;

constexpr int Base = 37;
constexpr int File_Base = 10;

constexpr auto Content_In_p_txt = "5OOB4HVPX0KW90a54EOJ8Q944007aM6JPBQZMaCU41ACSJ46Y9a2RYUXUZPQ07QMFSS84QXHMDHSTCUIR7aTODQ1AM62XVaV4IGN28VBOBGZSK92OaPFGZ2ORVB1CAXV0CLQWTAMHD6FXW5J0MAKK1PIQaFQCM19QBOADLYP0P5APBL7322256NT6QGEN13GNaKSK";
constexpr auto Content_In_Elgamal_g_txt = "4YRS6S3QREYN4O57I6JNF05L9UM3NFRJQRCNJWEX3UPMNSGVVUCUT1FYP09NTE28L7XTD5N2T3HS51DNOC9PKEQQOLTQC7Ea8TIO1X1TA47XTK1EaCMGWESF015SK3X4ZC9LJXUXPJUO5U7ZBS0WSYU5W3M1B9ZID7OPJJNC1IXZIBQTaXVMQNZSVFEFLAGaQ01CI";
constexpr auto Content_In_Pedersen_g_txt = "UJDWJKX2EQ2YHM8U6RDM00HTLMXN4L9U2HBV2TB8SF5YEaP2XAK83HZ6S1W4Z7QRLVI42YFLQYH5TRANQ0EaUTZKMCJAGIKQP9H9KD10BM4RQMGaU435BZIVKaaX4MFH2W15W3ALDRVU61DUTMIDIISJ9G21TXJZMQJEFRD7J9a0VBT4VZZQ9N8YXSNHLATEV3aH";
constexpr auto Content_In_Pedersen_h_txt = "4Y4Y0YL9LLUQ7J8aPS3U8U3LE2ACI7LBDVJJSPWJaYT124G7ET26R5NZVJ1JFBL32JM474aSILS48O4XZIU5F5W4UK9L7KHNCRHQAYP6T8G3Y1CD4BG1ATCL2C5KZX10GBPKaERIKF0EACN0B61GEZLG7JO08TODTV460GTQPFSX1a0D8M2YaON0BGXaICN78QSKC";
extern string Location;

class Message
{
public:
	mpz_t C1;
	mpz_t C2;
	Message() { mpz_inits(C1, C2, NULL); }
	~Message() { mpz_clears(C1, C2, NULL); }
};

class Basic
{
public:
	mpz_t p;
	mpz_t Elgamal_g;
	mpz_t Pedersen_g;
	mpz_t Pedersen_h;
	unsigned int A_Class, B_Class, C_Class, D_Class;
	Basic();
	//初始化密钥（私钥，公钥）
	void Creat_Key(unsigned int& key, mpz_t& public_key);
	//发送一条消息至文件（文件路径，信息）
	bool Send_Message(string file_name, mpz_t& Message);
	bool Send_Message(string file_name, Message& Message);//发送一条消息至文件（文件路径，信息）
	bool Send_Message(string file_name, unsigned int Message);//发送成绩
	bool Send_Message(string file_name, unsigned int key, mpz_t& public_key);//发送一对密钥
	//接收一条消息从文件（文件路径，信息）
	bool Recive_Message(const char* file_name, mpz_t& Message);
	bool Recive_Message(const char* file_name, Message& Message);//接收一条消息从文件（文件路径，信息）
	bool Recive_Message(const char* file_name, unsigned int& Message);//接收成绩
	bool Recive_Message(const char* file_name, unsigned int& key, mpz_t& public_key);//接收一对密钥

	//ElGamal加密（随机数，公钥，明文，密文）
	void ElGamal_Lock(unsigned int random, mpz_t& public_key, unsigned int send, Message& Message);
	void ElGamal_Lock(unsigned int random, mpz_t& public_key, unsigned int send, mpz_t& Message);//ElGamal加密（随机数，公钥，明文，密文）
	void ElGamal_Lock(unsigned int random, mpz_t& public_key, mpz_t& send, Message& Message);//ElGamal加密（随机数，公钥，明文，密文）
	void ElGamal_Lock(unsigned int random, mpz_t& public_key, mpz_t& send, mpz_t& Message);//ElGamal加密（随机数，公钥，明文，密文）
	//ElGamal解密（私钥，密文，得到的明文）
	void ElGamal_Unlock(unsigned int key, Message& Message, mpz_t& recived);
	//Pedersen承诺（随机数，明文，密文）
	void Pedersen_Commit(unsigned int random, unsigned int send, mpz_t& Message);
	void Pedersen_Commit(mpz_t& random, mpz_t& send, mpz_t& Message);

	//与people_name约定一个参数（发送方）
	bool Send_Agreement_Number(string my_name, string people_name, mpz_t& Number);
	//与people_name约定一个参数（接收方）
	bool Recieve_Agreement_Number(string my_name, string people_name, mpz_t& Number);
private:
	//附计算使用临时变量
	mpz_t t1, t2, t3;
};
extern Basic basic;
extern gmp_randstate_t seed;

unsigned int Random();