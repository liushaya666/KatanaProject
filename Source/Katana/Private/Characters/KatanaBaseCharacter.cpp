// 版权归流沙所有。


#include "Characters/KatanaBaseCharacter.h"


AKatanaBaseCharacter::AKatanaBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}


