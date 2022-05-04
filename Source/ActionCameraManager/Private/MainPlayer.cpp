// Copyright 2022 Namman. All Rights Reserved.

#include "MainPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCameraManager.h"

AMainPlayer::AMainPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	/** Configure character Rotation */
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;

	/** Configure character movement */
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}
void AMainPlayer::BeginPlay() {
	Super::BeginPlay();

	/** Find MainCameraManager & Set */
	if (CameraManagerClass) {
		AMainCameraManager* TargetCamera = Cast<AMainCameraManager>(UGameplayStatics::GetActorOfClass(this, CameraManagerClass));
		
		if (TargetCamera) CameraManager = TargetCamera;
		else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error! MainCameraManager does not exist in the world!"));
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error! CameraManagerClass does not exist"));
}
void AMainPlayer::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
}
void AMainPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	/** Setting the rotation of the controller according to the rotation of the CameraManager */
	if (CameraManager) {
		FRotator NRot = FRotator(CameraManager->GetActorRotation().Pitch, CameraManager->GetActorRotation().Yaw, GetController()->GetControlRotation().Roll);
		GetController()->SetControlRotation(NRot);
	}
}
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
}
void AMainPlayer::MoveForward(float Value) {
	FRotator Rot = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(Rot), Value);
}
void AMainPlayer::MoveRight(float Value) {
	FRotator Rot = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	AddMovementInput(UKismetMathLibrary::GetRightVector(Rot), Value);
}