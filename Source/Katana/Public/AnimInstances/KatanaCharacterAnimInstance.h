// 版权归流沙所有。

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/KatanaBaseAnimInstance.h"
#include "KatanaCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AKatanaBaseCharacter;
/**
 * 
 */
UCLASS()
class KATANA_API UKatanaCharacterAnimInstance : public UKatanaBaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AKatanaBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "AnimData|LocomotionData")
	bool bHasAcceleration;
};
