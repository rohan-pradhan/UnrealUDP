// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"Ws2_32.lib") //Winsock Library
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnrealUDPSenderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALUDP_API UUnrealUDPSenderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnrealUDPSenderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SendMsg(const FString& strLocale);

private:
	struct sockaddr_in si_other;
	int s, slen = sizeof(si_other);
	WSADATA wsa;
	
};
