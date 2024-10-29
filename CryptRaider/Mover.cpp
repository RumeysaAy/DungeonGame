// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// aktörün ilk konumu
	OriginalLocation = GetOwner()->GetActorLocation();
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove) // true ise hareket etsin
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation(); // aktörün mevcut konumu, şimdiki/şu anki konumu
		FVector TargetLocation = OriginalLocation + MoveOffset;	  // hedef konum
		// Speed: mesafenin zamana bölünmesi (ilk konum, hedef konum) / MoveTime
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		/*
		static FVector VInterpConstantTo
		(
	    	const FVector & Current,  // mevcut konum
	    	const FVector & Target,  // hedef konum
	    	float DeltaTime,
	    	float InterpSpeed
		)
		*/

		// yeni konum
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		// aktörü yeni konuma taşıdım
		GetOwner()->SetActorLocation(NewLocation);
	}
}
