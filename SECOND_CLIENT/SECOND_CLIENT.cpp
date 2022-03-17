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
	void set_val()
	{
		char temp[30];
		std::cout << "ENTER THE NAME  : ";
		fflush(stdin);
		fgets(Name, 30, stdin);
		return;
	}
	void set_Message() {
		fflush(stdin);
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


void Is_For_One_Client(Details& user)
{
	char ch;
	std::cout << "PRESS Y TO SEND THE MESSAGE AGAIN TO THE SAME CLIENT : " << std::endl;
	std::cout << "PRESS N TO NOT COMMUNICATE WITH THE CLIENT : " << std::endl;
	fflush(stdin);
	std::cin >> ch;
	if (ch == 'y' or ch == 'Y')
	{
		fflush(stdin);
		//again setting the receiver side //
		bool _temp_ = user.Send_To_One_Person();
		fflush(stdin);

		user.set_receiver();

		return;
	}
	else
	{
		return;
	}
}
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
	nRet = connect(client_soc, (struct sockaddr*)&srv, sizeof(srv));
	if (nRet < 0)
	{
		printf("connection is failed\n");
	}

	else
	{
		Details user;
		char* str;
		char ch;
		int send_obj_res;
		int res_obj_res = 0;

		user.set_val();
		user.set_socket_id(client_soc);
		user.set_Message();
		user.Send_To_One_Person();
		user.set_receiver();

		send_obj_res = send(client_soc, (char*)&user, sizeof(Details), 0);
		if (send_obj_res > 0)
		{
			std::cout << "SUCCESSFULLY SEND MESSAGE TO THE SERVER : " << std::endl;
		}
		else
		{
			std::cout << "ERRO WHILE SENDING THE MESSAGE : " << std::endl;
		}
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
}
