// Copyright 2022 Namman. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCameraManager.generated.h"

/** Camera Type of Enum class */
UENUM(BlueprintType)
enum class ECameraType : uint8 {
	ECT_2D_Fix			UMETA(DisplayName = "ECT_2D_Fix"),		//RootScene is Fix		      (EX : Street Fighter 2)
	ECT_2D				UMETA(DisplayName = "ECT_2D"),			//RootScene is NonFix. For 2D (EX : Tekken 7)
	ECT_3D				UMETA(DisplayName = "ECT_3D")			//RootScene is NonFix. For 3D (EX : Naruto shippuden Ultimate Ninja Storm 4)
};

UCLASS()
class ACTIONCAMERAMANAGER_API AMainCameraManager : public APawn
{
	GENERATED_BODY()

public:
	AMainCameraManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	/** Always centered between players & Rotate to keep players visible */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	/** SceneComponent for reference in camera rotation and movement, when ECameratype is 3D */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class USceneComponent* ReferenceScene;

	/** Characters participating in the game (You must specify it yourself in editor) */
	UPROPERTY(EditInstanceOnly, Category = "Setting")
	TArray<AActor*> Players;

	UPROPERTY(EditAnywhere, Category = "Setting")
	ECameraType CameraType;

	/** Heigth of DefaultSceneRoot */
	UPROPERTY(EditAnywhere, Category = "Setting|value")
	float Height = 25.f;

	/** Max/Minimum distance of SpringArm */
	UPROPERTY(EditAnywhere, Category = "Setting|value")
	float SpringArmBaseDistance = 330.f;

	UPROPERTY(EditAnywhere, Category = "Setting|value")
	float SpringArmExtraDistance = 70.f;

	/** Max/Minimum Angle of the pitch of SpringArm */
	UPROPERTY(EditAnywhere, Category = "Setting|value")
	float MinSpringArmRotation = 3.f;

	UPROPERTY(EditAnywhere, Category = "Setting|value")
	float MaxSpringArmRotation = 5.f;
private:
	/** Common Variables */
	float IsForward;					// Based on the CameraComp, where is the P1 front(1) and back(-1)
	float IsLeft;						// Based on the ReferenceScene, where is the P1 left(1) and right(-1)
	float GlobalDistanceFactor;			// Convert the distance between P1 and P2 to a ratio of 0 to 1
	float P1ToRoot_InnerVec;

	/** Variables used in 3D */
	float MinRotDistance = 145.f;		// Maximum distance between P1 and ReferenceScene (Rotate if over value)
	float RotationDelay = 4.f;

	/** Variables used in 2D */
	float RotateForce = 200.f;	

	/** Related to Overlap */
	bool bIsPlayersOverlap = false;				
	float MaxOverlapInnerVal = 0.5f;	// Max/Minimum Inner value of DefaultSceneRoot and P1
	float MinOverlapInnerVal = 0.07f;
	float OverlapRotateForce = -35.f;			

	void CalculateVal();
	void SetReferenceScene();			// Always set the ReferenceScene to be on the same x-axis as P1
	void RotateDefaultScene();			// Always set the ReferenceScene to always reside on the peripheral Y-axis of P1
	void SetCameraPosition();			// Adjust the vertical angle by adjusting the length of the spring arm and the pitch value
	void SetViewAllPlayers();			// Automatic rotation if P1 and P2 overlap each other based on the camera's perspective
	void SetNonOverlap();				// If bIsPlayersOverlap is True, rotate the camera to prevent players from overlapping.
	void SetP1RelativeVal();			// Determine where P1 is relative to P2 (front/back, left/right)

	FORCEINLINE ECameraType GetCameraType() { return CameraType; }
};
