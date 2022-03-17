#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<iomanip>
#include<string>
#include<conio.h>
#pragma comment(lib, "Ws2_32.lib")
struct sockaddr_in srv;
#define PORT 9909
fd_set fr, fw, fe;
//#include "struct_network_check.h"
#define clr_inp_buf std::fflush(stdin)
/*"fd_set" structure is used by various Windows Sockets functionsand service providers,
such as the select function, to place sockets into a "set" for various purposes like reading the socket and writing etc */

int index;

//network_check main_obj;
//bool send_object_to_server(network_check obj, int client_soc)
//{
//
//	int res = send(client_soc, (char*)&obj, sizeof(network_check), 0);
//	if (res < 0)
//	{
//		std::cout << "THERE IS A ERROR WHILE SENDING THE DATA " << std::endl;
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}
//void receive_message(int client_soc)
//{
//	std::string str = "";
//	int t_id = 0;
//	network_check obj1(str, t_id);
//	int res = recv(client_soc, (char*)&obj1, sizeof(network_check), 0);
//	if (res < 0)
//	{
//		std::cout << "failure while receiving the data " << std::endl;
//	}
//	else
//	{
//		std::cout << "message received successfully : ";
//		std::cout << std::setw(20) << "PRITING THE NAME : " << obj1.name << std::endl;
//		std::cout << std::setw(20) << "ID : " << obj1.id << std::endl;
//		return;
//	}
//}
//
//
//network_check  enter_class_data(void)
//{
//	std::string  s_str = "";
//	int s_id = 0;
//	network_check student(s_str, s_id);
//	std::cout << "ENTER THE NAME : ";
//	std::cin.ignore();
//	std::getline(std::cin, student.name);
//	std::cin.ignore();
//	std::cout << "ENTER THE ID : ";
//	std::cin >> student.id;
//
//	return student;
//}


class Details
{
	char Name[30] = { 0 };
	char Message[30] = { 0 };
	char Receiver[30] = { 0 };
	int socket_id;
	bool is_recv = false;
public:

	Details()
	{

	}
	void set_Name()
	{
		char temp[30];
		std::cout << "ENTER THE NAME  : ";
		fflush(stdin);
		fgets(Name, 30, stdin);
	}
	void set_Message(){
		std::cout << "ENTER THE MESSAGE : ";
		fflush(stdin);
		fgets(Message, 30, stdin);
		return;
	}

	void set_socket_id(int temp)
	{
		this->socket_id = temp;
	}
	void set_receiver()
	{
		std::cout << "ENTER THE RECEIVER NAME : ";
		fflush(stdin);
		fgets(Receiver, 30, stdin);
		return;
	}
	char* get_Name()
	{
		//std::cout << "PRINTING THE NAME : " << Name;
		return Name;
	}
	char* get_Message()
	{
		return Message;
	}
	char* get_Receiver()
	{
		return Receiver;
	}
	int get_socket_id()
	{
		return socket_id;
	}
	bool Send_To_One_Person()
	{
		this->is_recv = true;
		return true;
	}

	bool Recv_End_Status()
	{
		return this->is_recv;
	}

};




int main()
{
	WSADATA ws;			/*WSA VARIABLES ENABLES THE SOCKET PROGRAMMING ENVIRONMENT IN THE WINDOWS */
						/*BEFORE CREATING THE SOCKETS WE NEED TO INITIALIZE THIS ENVIRONMENT*/
	int iresult = WSAStartup(MAKEWORD(2, 2), &ws);
	if (iresult < 0)
	{
		printf("WSA VARAIBLES ARE NOT CREATED\n");
	}
	else if (iresult == 0) {
		printf("WSA_VARIABLES ARE CREATED \n");
	}
	//for (index = 0; index < 11; index++)
	int client_soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	std::cout << "CLIENT_SOCKET ID  = " << client_soc << std::endl;
	//std::cout << "SOCKET ID " << client_soc << std::endl;
	if (client_soc > 0)
	{
		std::cout << "SOCKET CREATED SUCCESSFULLY" << std::endl;
	}
	else
	{
		std::cout << "SOCKET FUNCTION FAILED " << std::endl;
	}
	struct in_addr inaddr;
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	int r_Val = inet_addr("127.0.0.1");

	if (r_Val == 0)
	{
		std::cout << "NO CONNECTION" << std::endl;
	}
	else if (r_Val == -1)
	{
		std::cout << "INVALID" << std::endl;

	}
	else
	{
		std::cout << "IP ADDRESS SUCCESSFULLY CONVERTED TO BYTE ORDER" << std::endl;
	}
	srv.sin_addr.s_addr = inet_addr("127.0.0.1"); //IT WILL FIND MACHINE LOCAL IP AND ASSIGN TO THE SOCKET
	memset(&(srv.sin_zero), 0, 8);			//srv.sin_addri.s_addr = inet_addr() // on the argument we need to specify our ip addrss

	int nRet = 0;
	char ch;
	int send_obj_res;
	nRet = connect(client_soc, (struct sockaddr*)&srv, sizeof(srv));
	//else
	//{
	//	printf("connection is established\n");
	//	const int buf_len = 256;
	//	char buf[buf_len] = { 0 , };
	//	recv(client_soc, buf, buf_len, 0);
	//	std::cout << buf << std::endl;

	//	printf("SENDING THE MESSAGE TO THE SERVER : ");
	//	//char temp[buf_len] = "HELLO FROM THE CLIENT : ";
	//	//std::cout << "ENTER THE ANY MESSAGE TO THE SERVER :  " << std::endl;
	//	//fgets(buf, 256, stdin);
	//	//send(client_soc, buf, buf_len, 0);
	//	std::cout << "PRESS ANY KEY TO GET THE RESPONSE FROM THE SERVER :  " << std::endl;
	//	std::getchar();
	//	recv(client_soc, buf, buf_len, 0);
	//	//std::cout << std::setw(20) << "PRINTING THE MESSAGE :" << std::endl;
	//	std::cout << std::setw(10) << buf << std::endl;
	//	std::getchar();
	//}
	if (nRet < 0)
	{
		printf("connection is failed\n");
	}
	// else
	// {
	// 	int count = 0;

	// 	const int buf_len = 256;
	// 	char buf[buf_len] = "HELLO FROM THE TEMP_CHECK_CLIENT ! ";
	// 	//int buf_len = sizeof(buf) / sizeof(buf[0]);
	// 	//send(client_soc, buf, buf_len, 0);
	// 	std::cout << "CONNECTED TO THE SERVER SUCCESSFULLY : " << std::endl;
	// 		int s_res = send(client_soc, buf, buf_len, 0);
	// 		if (s_res > 0)
	// 		{
	// 			std::cout << "SERVER MESSAGE HAS SENT : " << buf << std::endl;
	// 		}
	// 		else
	// 		{
	// 			std::cout << "MESSAGE SENT TO THE SERVER HAS FAILED : " << std::endl;
	// 		}
	// 		int res = recv(client_soc, buf, buf_len, 0);
	// 		if (res > 0)
	// 		{
	// 			std::cout << "PRINTING THE MESSAGE : " << buf << std::endl;

	// 		}
	// 		else
	// 		{
	// 			std::cout << "RECEIVER HAS FAILED : " << std::endl;
	// 		}
	// 		int r_res;
	// 		while (true)
	// {

	// 	 r_res = recv(client_soc, buf, buf_len, 0);
	// 	std::cout << "r_res : " << r_res << std::endl;
	// 	if (r_res > 0)
	// 	{
	// 		std::cout << "\t MESSAGE  TEMP FILE : " << buf << std::endl;
	// 		//break;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "no message :" << std::endl;
	// 		Sleep(1000);
	// 	}

	// 	s_res = send(client_soc, buf, buf_len, 0);
	// 	if (s_res > 0)
	// 	{
	// 		std::cout << "SERVER MESSAGE HAS SENT : " << buf << std::endl;
	// 	}
	// 	else
	// 	{
	// 		std::cout << "MESSAGE SENT TO THE SERVER HAS FAILED : " << std::endl;
	// 	}


	// }

	// }
	else
	{
		//while (true) {
		Details user;

		user.set_Name();
		user.set_Message();
		user.set_socket_id(client_soc);
	//IF CLIENT WANTS TO SEND THE MESSAGE TO ONE PARTICULAR PERSON 

		char* str = user.get_Name();
		std::cout << "NAME : " << str;

		 send_obj_res = send(client_soc, (char*)&user, sizeof(Details), 0);
		if (send_obj_res > 0)
		{
			std::cout << "SUCCESSFULLY SENT TO THE SERVER : " << std::endl;
		}
		else
		{
			std::cout << "FAILED WHILE SENDING THE DATA TO THE SERVER : " << std::endl;
		}
		int res_obj_res = 0;
		while (true) {
			res_obj_res = recv(client_soc, (char*)&user, sizeof(Details), 0);
			if (res_obj_res > 0)
			{
				std::cout << "SUCCESSFULLY RECEIVED THE MESSAGE FROM THE SERVER : ";
				std::cout << "PRINTING THE MESSAGE : ";
				str = NULL;
				str = user.get_Message();
				std::cout << str << std::endl;
			}
			else
			{
				std::cout << "FAILED WHILE RECEIVING THE MESSAGE : " << std::endl;
			}
		}
	}
	//}
	//}
	return 0;
}










