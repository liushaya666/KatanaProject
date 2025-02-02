// 版权归流沙所有。


#include "Characters/KatanaHeroCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/KatanaInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "KatanaGameplayTags.h"
#include "Katana/Public/KatanaDebugHelper.h"

AKatanaHeroCharacter::AKatanaHeroCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AKatanaHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forget to assign a valid data asset as input config"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UKatanaInputComponent* KatanaInputComponent = CastChecked<UKatanaInputComponent>(PlayerInputComponent);
	KatanaInputComponent->BindNativeInputAction(InputConfigDataAsset, KatanaGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	KatanaInputComponent->BindNativeInputAction(InputConfigDataAsset, KatanaGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void AKatanaHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	Debug::Print("AKatanaHeroCharacter::BeginPlay");
}

void AKatanaHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKatanaHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisDirection = InputActionValue.Get<FVector2D>();
	if (LookAxisDirection.X != 0.f)
	{
		AddControllerYawInput(LookAxisDirection.X);
	}
	if (LookAxisDirection.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisDirection.Y);
	}
}
