
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_SplitGuysCharacter.generated.h"

UCLASS(config=Game)
class AProject_SplitGuysCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* capsuleColl;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* LWeaponColl;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* RWeaponColl;

public:
	AProject_SplitGuysCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public:
	virtual void Tick(float DeltaTime) override;

protected:

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	bool bLMBDown;
	bool bRMBDown;
	bool bLeftShiftDown;
	bool bLeftCtrlDown;
	bool bIsAttacking;
	bool bSaveAttack;
	UPROPERTY(BlueprintReadOnly)
	bool bDeflect;
	bool bParryDoOnce;
	bool bSlideDoOnce;
	bool bDodgeDoOnce;
	bool bCanMove;

	int attackCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float maxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float maxStamina;
	float StaminaDrainRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Attack")
	class UAnimMontage* attackMontage_1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Attack")
	class UAnimMontage* attackMontage_2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Attack")
	class UAnimMontage* attackMontage_3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Attack")
	class UAnimMontage* parryMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Movement")
	class UAnimMontage* slideMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = "Movement")
	class UAnimMontage* dodgeMontage;

protected:
	void LMBDown();
	FORCEINLINE void LMBUp() { bLMBDown = false; }
	void RMBDown();
	FORCEINLINE void RMBUp() { bRMBDown = false; }
	void LeftShiftDown();
	FORCEINLINE void LeftShiftUp() { bLeftShiftDown = false; }
	void LeftCtrlDown();
	FORCEINLINE void LeftCtrlUp() { bLeftCtrlDown = false; }

	// 콤보 공격 처리 함수
	void Attack();
	UFUNCTION(BlueprintCallable)
	void ComboAttackSave();
	UFUNCTION(BlueprintCallable)
	void AttackSwitch();
	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	// AnimNotify 호출 함수 
	UFUNCTION(BlueprintCallable)
	void AttackStart();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	UFUNCTION(BlueprintCallable)
	void ToggleMovement();
};

