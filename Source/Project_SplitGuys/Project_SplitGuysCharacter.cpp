
#include "Project_SplitGuysCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

AProject_SplitGuysCharacter::AProject_SplitGuysCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 85.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 튕겨내기를 위한 콜리전 생성
	capsuleColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ParryColl"));
	capsuleColl->SetupAttachment(RootComponent);
	capsuleColl->InitCapsuleSize(150.0f, 250.0f);

	// 무기 충돌 콜리전 생성
	LWeaponColl = CreateDefaultSubobject<UBoxComponent>(TEXT("LWeaponColl"));
	LWeaponColl->SetupAttachment(GetMesh(), FName("weapon_l"));
	RWeaponColl = CreateDefaultSubobject<UBoxComponent>(TEXT("RWeaponColl"));
	RWeaponColl->SetupAttachment(GetMesh(), FName("weapon_r"));

	bLMBDown = false;
	bRMBDown = false;
	bLeftShiftDown = false;
	bLeftCtrlDown = false;

	bIsAttacking = false;
	bSaveAttack = false;
	bDeflect = false;
	bParryDoOnce = true;
	bSlideDoOnce = true;
	bDodgeDoOnce = true;

	bCanMove = true;
	bIsDie = false;

	attackCombo = 0;
	health = 100.0f;
	maxHealth = 100.0f;
	stamina = 200.0f;
	maxStamina = 200.0f;
	StaminaDrainRate = 10.0f;
}


void AProject_SplitGuysCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("LeftMB", IE_Pressed, this, &AProject_SplitGuysCharacter::LMBDown);
	PlayerInputComponent->BindAction("LeftMB", IE_Released, this, &AProject_SplitGuysCharacter::LMBUp);

	PlayerInputComponent->BindAction("RightMB", IE_Pressed, this, &AProject_SplitGuysCharacter::RMBDown);
	PlayerInputComponent->BindAction("RightMB", IE_Released, this, &AProject_SplitGuysCharacter::RMBUp);
		
	PlayerInputComponent->BindAction("LeftShift", IE_Pressed, this, &AProject_SplitGuysCharacter::LeftShiftDown);
	PlayerInputComponent->BindAction("LeftShift", IE_Released, this, &AProject_SplitGuysCharacter::LeftShiftUp);

	PlayerInputComponent->BindAction("LeftCtrl", IE_Pressed, this, &AProject_SplitGuysCharacter::LeftCtrlDown);
	PlayerInputComponent->BindAction("LeftCtrl", IE_Released, this, &AProject_SplitGuysCharacter::LeftCtrlUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProject_SplitGuysCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProject_SplitGuysCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProject_SplitGuysCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProject_SplitGuysCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProject_SplitGuysCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProject_SplitGuysCharacter::TouchStopped);
}


void AProject_SplitGuysCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AProject_SplitGuysCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AProject_SplitGuysCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProject_SplitGuysCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AProject_SplitGuysCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), bCanMove ? TEXT("true") : TEXT("false"));
	//UE_LOG(LogTemp, Warning, TEXT("%f"), stamina);

	float DeltaStamina = StaminaDrainRate * DeltaTime;
	if (stamina < maxStamina)
		stamina += DeltaStamina;
	else if (stamina >= maxStamina)
		stamina = maxStamina;

	if (health <= 0) {
		isPlayerDie();
	}
}

void AProject_SplitGuysCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProject_SplitGuysCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AProject_SplitGuysCharacter::LMBDown()
{
	UE_LOG(LogTemp, Warning, TEXT("LMBDown()"));
	bLMBDown = true;
	
	Attack();
}

void AProject_SplitGuysCharacter::RMBDown()
{
	UE_LOG(LogTemp, Warning, TEXT("RMBDown()"));
	bRMBDown = true;
	bDeflect = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (bParryDoOnce) {
		FTimerHandle TimerHandle;
		float delayTime = 2.0f;
		bParryDoOnce = false;
		GetCapsuleComponent()->SetCapsuleHalfHeight(45.0f, true);
		FVector currentLot = GetMesh()->GetComponentLocation();
		currentLot.Z += 40;
		GetMesh()->SetWorldLocation(currentLot);
		capsuleColl->SetGenerateOverlapEvents(true);
		//capsuleColl->SetNotifyRigidBodyCollision(true);
		AnimInstance->Montage_Play(parryMontage);		

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			UE_LOG(LogTemp, Warning, TEXT("2초"));
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			GetCapsuleComponent()->SetCapsuleHalfHeight(85.0f, true);
			FVector currentLot = GetMesh()->GetComponentLocation();
			currentLot.Z -= 40;
			GetMesh()->SetWorldLocation(currentLot);
			capsuleColl->SetGenerateOverlapEvents(false);
			//capsuleColl->SetNotifyRigidBodyCollision(false);
			bParryDoOnce = true;
			bDeflect = false;
		}), delayTime, false);
	}
}

void AProject_SplitGuysCharacter::LeftShiftDown() {
	UE_LOG(LogTemp, Warning, TEXT("LeftShiftDown()"));
	bLeftShiftDown = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (GetCharacterMovement()->Velocity.Size() > 80.0f && GetCharacterMovement()->IsFalling() != true && stamina >= 50.0f) {
		if (bSlideDoOnce) {
			FTimerHandle TimerHandle;
			float delayTime = 2.0f;

			stamina -= 50.0f;
			bSlideDoOnce = false;
			GetCapsuleComponent()->SetCapsuleHalfHeight(45.0f, true);
			FVector currentLot = GetMesh()->GetComponentLocation();
			currentLot.Z += 40;
			GetMesh()->SetWorldLocation(currentLot);
			GetCapsuleComponent()->SetGenerateOverlapEvents(false);
			AnimInstance->Montage_Play(slideMontage);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				UE_LOG(LogTemp, Warning, TEXT("2초"));
				// TimerHandle 초기화
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				GetCapsuleComponent()->SetCapsuleHalfHeight(85.0f, true);
				FVector currentLot = GetMesh()->GetComponentLocation();
				currentLot.Z -= 40;
				GetMesh()->SetWorldLocation(currentLot);
				GetCapsuleComponent()->SetGenerateOverlapEvents(true);
				bSlideDoOnce = true;
			}), delayTime, false);
		}
	}
}

void AProject_SplitGuysCharacter::LeftCtrlDown() {
	UE_LOG(LogTemp, Warning, TEXT("LeftCtrlDown()"));
	bLeftCtrlDown = true;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (GetCharacterMovement()->Velocity.Size() > 80.0f && GetCharacterMovement()->IsFalling() != true && stamina >= 25.0f) {
		if (bDodgeDoOnce) {
			FTimerHandle TimerHandle;
			float delayTime = 1.0f;

			stamina -= 25.0f;
			bDodgeDoOnce = false;
			GetCapsuleComponent()->SetCapsuleHalfHeight(45.0f, true);
			FVector currentLot = GetMesh()->GetComponentLocation();
			currentLot.Z += 40;
			GetMesh()->SetWorldLocation(currentLot);
			GetCapsuleComponent()->SetGenerateOverlapEvents(false);
			AnimInstance->Montage_Play(dodgeMontage);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
				{
					UE_LOG(LogTemp, Warning, TEXT("1초"));
					// TimerHandle 초기화
					GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					GetCapsuleComponent()->SetCapsuleHalfHeight(85.0f, true);
					FVector currentLot = GetMesh()->GetComponentLocation();
					currentLot.Z -= 40;
					GetMesh()->SetWorldLocation(currentLot);
					GetCapsuleComponent()->SetGenerateOverlapEvents(true);
					bDodgeDoOnce = true;
				}), delayTime, false);
		}
	}
}

void AProject_SplitGuysCharacter::isPlayerDie() {
	bIsDie = true;
	bCanMove = false;
	capsuleColl->SetGenerateOverlapEvents(false);
	capsuleColl->SetNotifyRigidBodyCollision(false);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(false);
}

void AProject_SplitGuysCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack()"));	

	if (bIsAttacking)
		bSaveAttack = true;
	else {
		bIsAttacking = true;
		AttackSwitch();
	}
}

void AProject_SplitGuysCharacter::ComboAttackSave() {
	if (bSaveAttack) {
		bSaveAttack = false;
		AttackSwitch();
	}
}

void AProject_SplitGuysCharacter::AttackSwitch() {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	switch (attackCombo)
	{
		case 0:
			attackCombo = 1;
			AnimInstance->Montage_Play(attackMontage_1);
			break;
		case 1:
			attackCombo = 2;
			AnimInstance->Montage_Play(attackMontage_2);
			break;
		case 2:
			attackCombo = 0;
			AnimInstance->Montage_Play(attackMontage_3);
			break;
		default:
			break;
	}
}

void AProject_SplitGuysCharacter::ResetCombo() {
	bIsAttacking = false;
	bSaveAttack = false;
	attackCombo = 0;
}

void AProject_SplitGuysCharacter::AttackStart() {
	UE_LOG(LogTemp, Warning, TEXT("AttackStart()"));
	LWeaponColl->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RWeaponColl->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AProject_SplitGuysCharacter::AttackEnd() {
	UE_LOG(LogTemp, Warning, TEXT("AttackEnd()"));
	LWeaponColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RWeaponColl->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AProject_SplitGuysCharacter::ToggleMovement() {
	if (bCanMove)
		bCanMove = false;
	else
		bCanMove = true;
}
