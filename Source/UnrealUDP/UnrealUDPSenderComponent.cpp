// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealUDPSenderComponent.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 5005   //The port on which to listen for incoming data


// Sets default values for this component's properties
UUnrealUDPSenderComponent::UUnrealUDPSenderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnrealUDPSenderComponent::BeginPlay()
{
	Super::BeginPlay();

	//Set up the socket
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
}


// Called every frame
void UUnrealUDPSenderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString strLocale = GetOwner()->GetActorLocation().ToString();

	UUnrealUDPSenderComponent::SendMsg(strLocale);
}

void UUnrealUDPSenderComponent::SendMsg(const FString& strLocale)
{
	FTCHARToUTF8 message1(*strLocale);

	UE_LOG(LogTemp, Warning, TEXT("Should be about to send a message"));

	//char *message = message1.Get();

	//start communication
	//if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	if (sendto(s, message1.Get(), message1.Length(), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}

