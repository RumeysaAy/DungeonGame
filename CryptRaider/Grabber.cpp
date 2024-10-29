// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	// kameradan sahneye doğru
	DrawDebugLine(GetWorld(), Start, End, FColor::Red); // her karede bu hata ayıklama satırını yeniden çizecek

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius); // küre çarpışma şekli oluşturacak
	FHitResult HitResult;											  // vurulan nesne
	// get world bir işaretçi döndürdüğü için arrow kullandım
	// HasHit: herhangi bir şeyi vurup vurmadığımı gösteriyor
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start, // başlangıç vektörü
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

	// vurulan aktörün adını yazdıracağım
	if (HasHit)
	{
		AActor *HitActor = HitResult.GetActor();
		// aktörün ismi bir dize olduğundan başına * koydum
		UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *(HitActor->GetActorNameOrLabel()));
		// LogTemp: Display: Hit actor: SM_Gargoyle_Statue
	}
}

/*
küresel bir nesneyle bir geometri taraması yaptım ve yalnızca belirli Trace kanalımdaki
aktörlere tepki verdiğini görebiliyorum, örneğin heykel /Gargoyle) ayarladığım tek
aktör. Yani bulduğu tek şey heykel olacaktır.
*/