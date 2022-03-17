#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include<string>
#include<iomanip>
#include<fstream>
#include<vector>
#include<iterator>
#pragma comment(lib, "Ws2_32.lib")
struct sockaddr_in srv;
#define PORT 9909
fd_set fr, fw, fe;
#define INADDR "127.0.0.1"
int sresult;
static int curr_idx;

/*"fd_set" structure is used by various Windows Sockets functionsand service providers,
such as the select function, to place sockets into a "set" for various purposes like reading the socket and writing etc */
#define max_no_of_clients  10
int clients[max_no_of_clients];
int index;

const int buf_len = 256;
char buf[buf_len] = { 0, };
int client_socket_ids[10];
char client_names[10][20];

static int client_names_idx = -1;

struct client_check
{
	int client_soc = 0;
	bool valid_client = false;
	bool is_space = false;
};

class One_To_One_Classify
{
	char Name[30] = { 0 };
	int socket_id;
public : 
	One_To_One_Classify()
	{

	}
	void set_socket_id(int temp)
	{
		this->socket_id = temp;
	}
	int get_socket_id()
	{
		return this->socket_id;
	}
	void set_Name(char *temp)
	{
		std::strcpy(Name, temp);
		return;
	}
	char* get_Name()
	{
		return this->Name;
	}


};

One_To_One_Classify server_class_check[10];
class Details
{
	char Name[30] = { 0 };
	char Message[30] = { 0 };
	char Receiver[30] = { 0 };
	int socket_id;
	bool is_recv= false;
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

		std::cout << "ENTER THE MESSAGE : ";
		fflush(stdin);
		fgets(Message, 30, stdin);

		return;
	}
	void set_socket_id(int temp )
	{
		this->socket_id = temp;
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
		return this->Receiver;
	}
	int get_socket_id()
	{
		return this->socket_id;
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

/*bool is_match(char* p, char* q)
{
	int i = 0;
	bool flag = true;
	while (p[i] != '\0' or q[i] != '\0')
	{
		if (p[i] == q[i])
		{

		}
		else
		{

			return false;
			break;
		}
	}
	if (p[i] == '\0' and q[i] != '\0')
	{
		return false;
	}
	else if (p[i] == '\0' and q[i] == '\0')
	{
		return true;
	}
}*/

void Print_Client_Names()
{
	std::cout << "PRINTING THE CLIENT NAMES :  " << std::endl;
	for (int i = 0; i <= client_names_idx; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			char temp = client_names[i][j];

			if (temp != '\0')
				std::cout << client_names[i][j];
			else
			{
				break;
			}
		}
		std::cout << "		CLIENT ID : " << client_socket_ids[i] << std::endl;

	}
	return;
}

int  Is_Receiver_Valid(char* p)
{
	int i, j;
	int temp_s_id;
	bool flag = false;
	for (i = 0; i <= client_names_idx; i++)
	{
		std::cout << "INSIDE THE RECV_VALID FUNCTION : " << std::endl;
		for (j = 0; j < 30; j++)
		{
			if (p[j] == client_names[i][j] and p[j] != '\0' and client_names[i][j] != '\0')
			{
				std::cout << "CHAR MATCH " << std::endl;
				continue;
			}
			else if (p[j] == '\0' and client_names[i][j] == '\0')
			{
		
				return client_socket_ids[i];
				//flag = true;
				break;
			}
			else if (p[j] != client_names[i][j])
			{
				std::cout << "RECEIVER ADDRESS IS INVALID " << std::endl;
				break;
			}
		}
		/*if (flag == true)
			break;*/
	}
	return -1;

}
void Receive_Client_Message(int client_soc , bool new_client )
{
	Details user;
	//std::fstream write_obj;
	//write_obj.open("USER_FILES.dat", std::ios::out | std::ios::app);
	std::cout << "INSIDE THE RECEIVER SIDE : " << std::endl;
	//int  c_result = recv(client_soc, buf, buf_len, 0);
	int c_result = recv(client_soc, (char*)&user, sizeof(user), 0);
	if (c_result > 0 ) 
	{
		char client_name[30] = { 0 };
		char *client_name_temp = user.get_Name();
		char* p = NULL;
		p = user.get_Receiver();
		std::cout << "RECEIVER : " << p << std::endl;
		char rec_name[30] = { 0 };
		int s_id = user.get_socket_id();
		int j = 0;
		char temp;
		bool to_send_ = user.Recv_End_Status();
		while (p[j] != '\0')
		{
			 temp = p[j];
			rec_name[j] = temp;
			j++;
		}
		j = 0;
		client_names_idx++;
		while (client_name_temp[j] != '\0')
		{
			temp = client_name_temp[j];
			client_name[j] = temp;
			client_names[client_names_idx][j] = temp;
			j++;
		}
		client_names[client_names_idx][j] = '\0';
		client_socket_ids[client_names_idx] = client_soc;

		std::cout << "new check client : " << client_name;
		std::cout << "\n new check receiver :  " << rec_name <<std::endl;
		Print_Client_Names();
		/*std::cout << "MESSAGE HAS REACHED : " << std::endl;
		char* str = NULL;
		str = user.get_Name();
		std::cout << "PRINTING THE CLIENT NAME : " << str << std::endl;
		str = NULL;
		str = user.get_Message();
		std::cout << "PRINTING THE CLIENT MESSAGE : " << str << std::endl;
		char* rec = NULL;
		rec = user.get_Receiver();

		write_obj.write((char*)&write_obj, sizeof(Details));*/


		if (new_client == true)
		{
			/*std::cout << "INSIDE THE NEW CLIENT : " << std::endl;
			server_class_check[curr_idx].set_Name(client_name);
			server_class_check[curr_idx].set_socket_id(s_id);
			curr_idx++;*/
			
		}
		bool flag = false;
		int  i;
		//for (  i = 0; i < 10; i++)//CHECKING FOR THE RECEIVER NAME
		//char check[30] = { 0 };

		/*
		for(auto it : map)
		{
			//char* check = server_class_check[i].get_Name();
			std::string check = it.first;

			//std::cout << "INSIDE CHECKING WHILE LOOP : " << server_class_check[i].get_Name() << std::endl;
			std::cout << "INSIDE CHECKING WHILE LOOP : " << it.first << " " << std::endl;
			if ( std::strcmp(rec_name, check) == 0)
			{
				std::cout << "RECEIVER ADDRESS HAS FOUND : " << std::endl;
				//c_result = send(server_class_check[i].get_socket_id(), user.get_Message(), sizeof(Details), 0);
				c_result = send(it.second, user.get_Message(), sizeof(Details), 0);
				flag = true;
				break;
			}
		}
		*/
		if (to_send_ == true) {
			std::cout << "CLIENT WANTS TO SEND THE DATA TO THE OTHER CLIENT : " << std::endl;
			int temp_soc = Is_Receiver_Valid(rec_name);
			if (temp_soc == -1)
			{
				std::cout << "IN VALID RECEIVER ADDRESS : " << std::endl;
			}
			else if ( temp_soc > 0)
			{
				//c_result = send(server_class_check[i].get_socket_id(), user.get_Message(), sizeof(Details), 0);
				c_result = send(temp_soc, (char*)&user, sizeof(Details), 0);
				if (c_result > 0)
				{
					std::cout << "SUCCESSFULLY SENT THE MESSAGE TO THE RECEIVER : " << std::endl;
				}
				else
				{
					std::cout << "FAILED TO SEND THE MESSAGE TO THE RECEIVER : " << std::endl;
				}
			}
		}

		//THIS IS FOR SENDING THE MESSAGE TO THE ALL THE CLIENTS IN THE NETWORK //
	//	for (int i = 0; i < max_no_of_clients; i++)
	//	{
	//		if (clients[i] != 0)
	//		{
	//			std::cout << "AVAILABLE CLIENT ID'S = " << clients[i] << std::endl;
	//			//c_result = send(clients[index], sen_buf, sen_buf_len, 0);
	//			//user.set_val();
	//			c_result = send(clients[i], (char*)&user, sizeof(Details), 0);
	//			if (c_result > 0)
	//			{
	//				std::cout << " SERVER : MESSAGE SENT SUSSEFULLY : " << std::endl;

	//			}
	//			else
	//			{
	//				std::cout << " SERVER : MESSAGE HAS NOT SUCCESSFULLY : " << std::endl;

	//			}
	//		}
	//	}

	}
	else //IF INCASE CLIENT HAS DISCONNECTED TO THE SERVER  
	{
		for (int i = 0; i < max_no_of_clients; i++)
		{
			if (clients[i] == client_soc)
			{
				clients[i] = 0;
				break;
			}
		}
		std::cout << "MESSAGE HAS NOT RECEIVED : " << std::endl;
		return;
	}
	return;
}
void Communicate_with_client(struct client_check temp)
{
	bool case_1 = false;
	bool case_2 = false;
	bool case_3 = false;
	if (temp.client_soc > 0 and temp.is_space == true)
	{
		case_1 = true;
	}
	else if (temp.client_soc > 0 and temp.is_space == false)
	{
		case_2 = true;
	}
	else if (temp.client_soc < 0 and temp.valid_client == false)
	{
		case_3 = true;
	}
	if (case_1 == true)//IF IN CASE NEW CLIENT WE NEED TO SET THE VALUES
	{
		std::cout << "CONNECTION SUCCESSFULLY ESTABLISHED" << std::endl;
		Receive_Client_Message(temp.client_soc , true);
		//send(temp.client_soc, buf, buf_len, 0);
		//send_over_the_network(temp.client_soc, buf, buf_len, 0);
		return;
	}
	else if (case_2 == true)
	{
		std::cout << "SERVER IS BUSY WITH OTHER CLIENTS \t START REQUESTING AFTER SOMETIME" << std::endl;
		return;
	}
	else
	{
		std::cout << "NOT THE VALID CLIENT " << std::endl;
	}
	return;
}

void  Process_Client_Request()
{
	int addr_len = sizeof(struct sockaddr);
	struct client_check cl_check;
	if (FD_ISSET(sresult, &fr))
	{
		int nClient = accept(sresult, NULL, &addr_len);
		std::cout << "PRINTING THE CLIENT_SIDE ID'S = " << nClient << std::endl;
		if (nClient > 0)
		{
			for (index = 0; index < max_no_of_clients; index++)
			{
				if (clients[index] == 0)//IF THE CLIENT IS NEW ONE 
				{
					//std::setw(40);
					std::cout << "NEW CONNECTION TO THE CLIENT HAS ACCEPTED " << std::endl;

					clients[index] = nClient;
					cl_check.client_soc = nClient;
					cl_check.is_space = true;
					cl_check.valid_client = true;
					break;
				}
			}
			if (index < max_no_of_clients)
			{
				Communicate_with_client(cl_check);
				return;
			}
			else if (index == (max_no_of_clients))
			{
				////std::cout << "NO SPACE FOR THE  NEW CONNECTION " << std::endl;
				//cl_check.client_soc = nClient;
				//cl_check.is_space = false;
				//cl_check.valid_client = true;
				//Communicate_with_client(cl_check);
				std::cout << "server is busy with other clients : ";
				return;
			}
		}
		else
		{
			std::cout << "NEW CLIENT HAS NOT ACCEPTED : " << std::endl;
		}
	}
	//else
	//{
	//	//std::cout << "CLIENT CONNECTION HAS FAILED" << std::endl;
	//	return Communicate_with_client(cl_check);
	//}
	else                //ALREADY EXISTED CLIENT
	{
		for (int i = 0; i < max_no_of_clients; i++)
		{
			if (FD_ISSET(clients[i], &fr))
			{
				std::cout << "SAME CLIENT " << std::endl;
				cl_check.client_soc = clients[i];
				cl_check.valid_client = true;
				cl_check.is_space = true;
				Receive_Client_Message(cl_check.client_soc , false);
				break;
			}
		}
		return;
	}
}



int main() {
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
	sresult = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//std::cout << "SOCKET ID : " << sresult <<std::endl;
	if (sresult < 0) {
		std::cout << "socket is not created\n";
		WSACleanup();
	}
	else if (sresult == INVALID_SOCKET)
	{
		std::cout << "socket error" << std::endl;
	}
	else if (sresult > 0)

	{
		printf("SUCCESSFULLY CREATED THE SOCKET FUNCTION ");
	}
	//std::cout << "check";

	// INITIALIZE THE SOCK ADDRESS //
	struct in_addr inaddr;
	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT);
	srv.sin_addr.s_addr = INADDR_ANY;//IT WILL FIND MACHINE LOCAL IP AND ASSIGN TO THE SOCKET
	//srv.sin_addr.s_addr = inet_addr("127.0.0.1");
	//srv.sin_addr.s_addr = ADDR_ANY;
	memset(&(srv.sin_zero), 0, 8);			//srv.sin_addri.s_addr = inet_addr() // on the argument we need to specify our ip addrss



	/*SETTING THE SOCKET OPTIONS IN  THE SOCKET*/

	int set_sock_res;
	int OptVal = 0;
	int OptSize = sizeof(OptVal);
	set_sock_res = setsockopt(sresult, SOL_SOCKET, SO_REUSEADDR, (char*)&OptVal, OptSize);
	if (set_sock_res == 0)
	{
		std::cout << "SOCKET OPT FUNCTION SUCCESS" << std::endl;
	}
	else {
		std::cout << "THE SOCKET OPT FUNCTION CALL IS NOT SUCCESSFUL" << std::endl;
	}
	/*THIS IS USED FOR THE MANUPULATING THE SOCKETS BASET ON THE PROPERTIES */

	/* BIND THE SOCKET TO THE LOCAL PORT */
	int nResult = 0;
	nResult = bind(sresult, (sockaddr*)&srv, sizeof(sockaddr));

	if (nResult < 0)
	{
		std::cout << "BINDING IS FAILED" << std::endl;
		WSACleanup();
	}
	else
	{
		std::cout << "BINDING IS SUCCESS " << std::endl;
	}




	/*LISTEN REQUEST FROM THE CLIENT */

	nResult = listen(sresult, 5);

	// 5 represents no of requests that the server can process at a time in this we specify 5 //
	//if more then 5 requests are came then the clients need to wait until the before requests will be processes
	//here initially specified requests(in this case 5)are placed in queue //
	if (nResult < 0)
	{
		std::cout << "LISTENING FROM THE CLIENT IS FIALED" << std::endl;
		WSACleanup();
	}
	else
	{
		std::cout << "LISTENING FROM THE CLIENT IS SUCCESS " << std::endl;
	}




	/*PUTTING THE FILE DESCRIPTOR fr,  fw ,see on the top  */


	int nMaxFd = 0;//nMax Fd refers to the maximum file descriptors or socket descriptor
	nMaxFd = sresult;
	struct timeval tv;//it is used how much time we need to wait to see the select function is ready like how much time we need to see weather fr(file_reaer socket)or fw are ready to communicate//
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	int nRet = 0;
	Sleep(500);
	while (1)
	{
		FD_ZERO(&fr);
		FD_ZERO(&fw);
		FD_ZERO(&fe);

		FD_SET(sresult, &fr);
		FD_SET(sresult, &fe);

		for (int index = 0; index < max_no_of_clients; index++)
		{
			if (clients[index] != 0)
			{
				FD_SET(clients[index], &fr);
				FD_SET(clients[index], &fe);
				//std::cout << std::setw(20) << "SAME CLIENT" << std::endl;
			}
		}
		//std::cout << "before select call : " << fr.fd_count << std::endl;
		nRet = select(nMaxFd + 1, &fr, &fw, &fe, &tv);
		if (nRet < 0)
		{
			std::cout << "select function is failed " << std::endl;
			WSACleanup();
		}
		else if (nRet > 0)
		{
			std::cout << "  " << std::endl;
			//std::cout << "CLIENT HAS CONNECTED TO THE SERVER   " << std::endl;
			Process_Client_Request();
		}

		/*if (FD_ISSET(sresult, &fr))
		{
			std::cout << "READ MODE SOCKET READER HAS GOT THE CONNECTION TO THE SERVER " << std::endl;
			break;
		}
		else if (FD_ISSET(sresult, &fe))
		{
			std::cout << "FILE EXCEPTION DESCRIPTOR HAS SELECTED " << std::endl;
			break;

		}
		else if (FD_ISSET(sresult, &fw))
		{
			std::cout << "READ MODE SOCKET DESCRIPTOR HAS GOT THE CONNECTION TO THE SERVER" << std::endl;
			break;
		}*/
		else if (nRet == 0) {
			//std::cout << "SELECT FUNCTION WORKS FINE BUT NO FILE DESCRIPTORS HAS SELECTED " << std::endl;f
			//WSACleanup();
		}
		//std::cout << "AFTER SELECT CALL : " << fr.fd_count << std::endl;
	}
	return  0;
}




/* BLOCKING AND NON BLOCKING SOCKETS CREATION - By default every socket is a blockig socket */
	// IF WE WANT TO CREATE THE NON - BLOCKING SOCKETS(FOR SINGLE THREAD) THEN ONLY USE THIS FUNCTION OTHER WISE NO NEED TO USE THIS FUNCTION// 
	//u_long var = 1; //when var is  0 then it is blocking sockets which is useful for the creating multiple threads
	////when var!= 0  then it is non blocking sockets which useful for the single thread for all connections like read and write etc//
	//int nRet = ioctlsocket(sresult, FIONBIO, &var); 
	//if (nRet != 0)
	//{
	//	std::cout << "IT IS A NON BLOCKING SOCKET " << std::endl;
	//}
	//else if (nRet == 0)
	//{
	//	std::cout << "IT IS THE BLOCKING SOCKET " << std::endl;
	//}
	/*int n = 100;
	for (int n_idx = 0; n_idx < 64; n_idx++)
	{
		FD_SET(n, &fr);
		n++;
	}
	std::cout << fr.fd_count << std::endl;

	for (int n = 0; n < 64; n++)
	{
		std::cout << fr.fd_array[n] << std::endl;
	}*/
	/*https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-setsockopt-set-options-associated-socket*/