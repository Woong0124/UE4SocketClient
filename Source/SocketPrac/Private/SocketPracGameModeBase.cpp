// Copyright Epic Games, Inc. All Rights Reserved.


#include "SocketPracGameModeBase.h"
#include "MyActor01.h"

void ASocketPracGameModeBase::BeginPlay()
{
	SocketCheck = MySock.InitSocket();
	if (SocketCheck == false)
	{
		exit(-1);
	}

	SocketCheck = MySock.ConnectSocket();

	MyDataStruct = new DataStruct;

	*MyDataStruct = MySock.RecvStructSocket(MyDataStruct);
	//MySock.SendStructSocket(MyDataStruct);

	// �����κ��� �޾ƿ� ������ ������ ���� ����
	MySpawnActor(MyDataStruct);
}

void ASocketPracGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	closesocket(MySock.ClientSocket);
	WSACleanup();
}

void ASocketPracGameModeBase::MySpawnActor(DataStruct* DStruct)
{
	if (strcmp(DStruct->ActorType, "AMyActor01") == 0)
	{
		FActorSpawnParameters SpawnParam;
		GetWorld()->SpawnActor<AMyActor01>(AMyActor01::StaticClass(), FVector(DStruct->LocX, DStruct->LocY, DStruct->LocZ), FRotator(0.f, 0.f, 0.f), SpawnParam);
	}
}
