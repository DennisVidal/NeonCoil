// Fill out your copyright notice in the Description page of Project Settings.


#include "Entities/Snake.h"
#include "Entities/SnakePart.h"
#include "EnhancedInputComponent.h"
#include "Controllers/SnakePlayerController.h"
#include "Items/Item.h"
#include "Abilities/Ability.h"
#include "Components/AbilityComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Controllers/SnakePlayerController.h"
#include "Interfaces/ScoreInterface.h"


void FSnakePath::UpdatePathPoints(const FVector& InTargetPosition)
{
	const FVector& FirstPoint = PathPoints.First();
	FVector DirectionToTarget = InTargetPosition - FirstPoint;
	double DistanceToTarget = DirectionToTarget.Length();

	if (DistanceToTarget < SampleDistance)
	{
		return;
	}
	PathPoints.PopLast();
	PathPoints.PushFirst(FirstPoint + (DirectionToTarget / DistanceToTarget) * SampleDistance);
}

void FSnakePath::AddPointFirst(const FVector& InPoint)
{
	PathPoints.PushFirst(InPoint);
}

void FSnakePath::AddPointFirst(const FVector& InPoint, int32 InCount)
{
	for (int32 i = 0; i < InCount; ++i)
	{
		AddPointFirst(InPoint);
	}
}

void FSnakePath::AddPointLast(const FVector& InPoint)
{
	PathPoints.PushLast(InPoint);
}

void FSnakePath::AddPointLast(const FVector& InPoint, int32 InCount)
{
	for (int32 i = 0; i < InCount; ++i)
	{
		AddPointLast(InPoint);
	}
}

void FSnakePath::RemovePointFirst()
{
	PathPoints.PopFirst();
}

void FSnakePath::RemovePointFirst(int32 InCount)
{
	for (int32 i = 0; i < InCount; ++i)
	{
		RemovePointFirst();
	}
}

void FSnakePath::RemovePointLast()
{
	PathPoints.PopLast();
}

void FSnakePath::RemovePointLast(int32 InCount)
{
	for (int32 i = 0; i < InCount; ++i)
	{
		RemovePointLast();
	}
}

const FVector& FSnakePath::GetFirstPoint() const
{
	return PathPoints.First();
}

const FVector& FSnakePath::GetLastPoint() const
{
	return PathPoints.Last();
}

FVector FSnakePath::GetPositionAlongPath(float InDistance)
{
	float FloatingPathIndex = InDistance / SampleDistance;
	int32 PathIndex = FloatingPathIndex;

	return FMath::Lerp(PathPoints[PathIndex], PathPoints[PathIndex + 1], FMath::Frac(FloatingPathIndex));
}

void FSnakePath::DebugDraw(UWorld* InWorld) const
{
	for (const FVector& PathPoint : PathPoints)
	{
		DrawDebugSphere(InWorld, PathPoint, 8.0, 32, FColor::Red);
	}

	for (int32 PathIndex = 1; PathIndex < PathPoints.Num(); ++PathIndex)
	{
		DrawDebugLine(InWorld, PathPoints[PathIndex], PathPoints[PathIndex - 1], FColor::Black, false, -1.0f, 0, 2.0f);
	}
}





ASnake::ASnake()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASnake::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (ASnakePlayerController* PlayerController = Cast<ASnakePlayerController>(Controller))
	{
		PlayerController->AddInputMappingContext(InputMappingContext, static_cast<int32>(EInputMappingContextPriorities::GAMEPLAY));
	}

	SnakePath.PathPoints.Reserve(30);
	SnakePath.AddPointFirst(GetActorLocation());
	CreatePart(InitialPartClass);
}

void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector VectorToTarget = (TargetPosition - GetActorLocation());
	float Angle = FMath::Atan2(VectorToTarget.Z, VectorToTarget.X);
	FQuat CurrentQuaternion = GetActorRotation().Quaternion();
	FQuat TargetQuaternion = FQuat(FVector::LeftVector, Angle);
	double RotationSpeedRad = FMath::DegreesToRadians(RotationSpeed);
	SetActorRotation(FMath::QInterpConstantTo(CurrentQuaternion, TargetQuaternion, DeltaTime, RotationSpeedRad));

	float Speed = bIsSprinting ? SprintSpeed : MovementSpeed;
	FVector NewPosition = GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewPosition);

	SnakePath.UpdatePathPoints(NewPosition);
	UpdateSnakeParts();

	//Debug
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 200.0, FColor::Red, false, -1.0f, 0, 2.0f);
	//DrawDebugLine(GetWorld(), GetActorLocation(), TargetPosition, FColor::Black, false, -1.0f, 0, 2.0f);
	//SnakePath.DebugDraw(GetWorld());
}

void ASnake::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Abilities
		EnhancedInputComponent->BindAction(ActivateAbilityAction, ETriggerEvent::Started, this, &ASnake::ActivatePrimaryAbility);
		EnhancedInputComponent->BindAction(ActivateAbilityAction, ETriggerEvent::Canceled, this, &ASnake::DeactivatePrimaryAbility);
		EnhancedInputComponent->BindAction(ActivateAbilityAction, ETriggerEvent::Completed, this, &ASnake::DeactivatePrimaryAbility);


		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASnake::SetSprintEnabled, true);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ASnake::SetSprintEnabled, false);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASnake::SetSprintEnabled, false);
	}

}

void ASnake::SetTargetPosition(const FVector& InTargetPosition)
{
	TargetPosition = InTargetPosition;
	TargetPosition.Y = 0.0;
}

void ASnake::SetSprintEnabled(bool bEnabled)
{
	bIsSprinting = bEnabled;
}

ASnakePart* ASnake::CreatePart(TSubclassOf<ASnakePart> InSegmentClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;
	ASnakePart* SpawnedPart = GetWorld()->SpawnActor<ASnakePart>(InSegmentClass, SpawnParams);
	AddPart(SpawnedPart);
	return SpawnedPart;
}

int32 ASnake::AddPart(ASnakePart* InPart)
{
	InPart->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //TODO: Double check attachment rules
	InPart->SetActorLocation(Parts.Num() ? Parts.Last()->GetActorLocation() : GetActorLocation());
	InPart->SetSnake(this);
	InPart->OnActorBeginOverlap.AddDynamic(this, &ASnake::OnBeginOverlap);

	SnakePath.AddPointLast(SnakePath.GetLastPoint(), FMath::CeilToInt(2 * InPart->GetPartRadius() / SnakePath.SampleDistance));

	if(!Parts.Num())
	{
		OnHeadPartChanged(InPart, nullptr);
	}
	
	return Parts.Add(InPart);
}

void ASnake::DestroyPart(int32 InPartIndex)
{
	ASnakePart* RemovedPart = RemovePart(InPartIndex);
	RemovedPart->Destroy();
}

ASnakePart* ASnake::RemovePart(int32 InPartIndex)
{
	ASnakePart* RemovedPart = Parts[InPartIndex];
	RemovedPart->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	RemovedPart->SetSnake(nullptr);
	RemovedPart->OnActorBeginOverlap.RemoveDynamic(this, &ASnake::OnBeginOverlap);
	SnakePath.RemovePointLast(FMath::CeilToInt(2 * RemovedPart->GetPartRadius() / SnakePath.SampleDistance));

	Parts.RemoveAt(InPartIndex, 1, false);

	if(InPartIndex == 0)
	{
		OnHeadPartChanged(Parts.Num() ? Parts[0] : nullptr, RemovedPart);
	}
	
	return RemovedPart;
}

void ASnake::UpdateSnakeParts()
{
	if (!Parts.Num())
	{
		return;
	}
	FVector SnakeLocation = GetActorLocation();

	Parts[0]->SetActorLocation(SnakeLocation);
	Parts[0]->SetActorRotation(GetActorRotation());


	FVector DirectionToPath = SnakePath.GetFirstPoint() - SnakeLocation;
	double DistanceToPath = DirectionToPath.Length();
	DirectionToPath /= DistanceToPath;
	double DistanceAlongPath = -DistanceToPath;
	for (int32 PartIndex = 1; PartIndex < Parts.Num(); ++PartIndex)
	{
		ASnakePart* PreviousPart = Parts[PartIndex - 1];
		ASnakePart* CurrentPart = Parts[PartIndex];

		double Spacing = PreviousPart->GetPartRadius() + CurrentPart->GetPartRadius();
		DistanceAlongPath += Spacing;

		FVector NewPartPosition = (DistanceAlongPath > 0.0) ?
			SnakePath.GetPositionAlongPath(DistanceAlongPath)
			: (SnakeLocation + DirectionToPath * Spacing);

		CurrentPart->SetActorLocation(NewPartPosition);

		FVector DirectionToPreviousTailEnd = (PreviousPart->GetPartTailEnd() - NewPartPosition);
		double Angle = FMath::RadiansToDegrees(FMath::Atan2(DirectionToPreviousTailEnd.Z, DirectionToPreviousTailEnd.X));
		CurrentPart->SetActorRotation(FRotator(Angle, 0, 0));
	}
}


void ASnake::ActivatePrimaryAbility(const FInputActionValue& Value)
{
	if(ASnakePart* HeadPart = GetHeadPart())
	{
		HeadPart->GetAbilityComponent()->TryActivateAbility();
	}
}

void ASnake::DeactivatePrimaryAbility(const FInputActionValue& Value)
{
	if(ASnakePart* HeadPart = GetHeadPart())
	{
		HeadPart->GetAbilityComponent()->TryDeactivateAbility();
	}
}

ASnakePart* ASnake::GetHeadPart() const
{
	return Parts.Num() ? Parts[0] : nullptr;
}




void ASnake::OnBeginOverlap(AActor* InOverlappedActor, AActor* InOtherActor)
{
	if (IHealthInterface* HealthInterface = Cast<IHealthInterface>(InOtherActor))
	{
		HealthInterface->Kill(this);
	}
	else if (IItemInterface* ItemInterface = Cast<IItemInterface>(InOtherActor))
	{
		ItemInterface->Pickup(this);
	}
}


bool ASnake::DealDamage(float InDamage, AActor* InDamagingActor)
{
	if (!Parts.Num())
	{
		return false;
	}

	DestroyPart(Parts.Num() - 1);
	if (!Parts.Num())
	{
		Kill(InDamagingActor);
	}

	return true;
}

void ASnake::Kill(AActor* InKillingActor)
{
	OnDeathDelegate.Broadcast(this, InKillingActor);
	//Destroy();
}

FOnDeathDelegate& ASnake::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

void ASnake::OnHeadAbilityDeactivated(UAbility* InAbility)
{
	if(InAbility && !InAbility->HasUsesLeft())
	{
		DestroyPart(0);

		if(!Parts.Num())
		{
			OnDeathDelegate.Broadcast(this, this);
		}
	}	
}

void ASnake::OnHeadPartChanged(ASnakePart* NewHead, ASnakePart* OldHead)
{
	if(OldHead)
	{
		OldHead->GetAbilityComponent()->OnAbilityDeactivatedDelegate.RemoveDynamic(this, &ASnake::OnHeadAbilityDeactivated);
	}
	
	if(NewHead)
	{
		NewHead->GetAbilityComponent()->OnAbilityDeactivatedDelegate.AddDynamic(this, &ASnake::OnHeadAbilityDeactivated);
		if (ASnakePlayerController* SnakeController = GetController<ASnakePlayerController>())
		{
			SnakeController->SetCrosshairColor(NewHead->GetAbilityComponent()->GetAbility()->GetColor());
		}
	}
}
