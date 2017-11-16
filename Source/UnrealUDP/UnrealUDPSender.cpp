// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealUDPSender.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 5005   //The port on which to listen for incoming data


// Sets default values
AUnrealUDPSender::AUnrealUDPSender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnrealUDPSender::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnrealUDPSender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AUnrealUDPSender::SendMsg();


}

void AUnrealUDPSender::SendMsg()
{
	UE_LOG(LogTemp, Warning, TEXT("Should be about to send a message"));
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	char message[] = "Hello from Unreal";
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	//start communication
	if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}
