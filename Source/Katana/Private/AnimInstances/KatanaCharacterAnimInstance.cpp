// 版权归流沙所有。


#include "AnimInstances/KatanaCharacterAnimInstance.h"

#include "Characters/KatanaBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKatanaCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AKatanaBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UKatanaCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
