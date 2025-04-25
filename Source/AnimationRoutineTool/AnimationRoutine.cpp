#include "AnimationRoutine.h"
#include "AnimationTask.h"
#include "BoneRecorder.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"


void UAnimRoutine::MapTaskToAnim(const UAnimSequence* Anim, const UAnimTask* Task)
{
	TArray<FName> BoneTrackNames {};
	TArray<FTransform> OutTransforms {};
	Anim->GetDataModel()->GetBoneTrackNames(BoneTrackNames);
	// Test First Apply
	Task->ApplyTaskTo(Anim, BoneTrackNames[0], OutTransforms);

	for(FTransform& Transform : OutTransforms)
	{
		UE_LOG(LogTemp, Display, TEXT("%s Transform:\n%s"), *BoneTrackNames[0].ToString(), *Transform.ToString());
	}
	// Test Second Apply
	// Test Third Apply
	// Test Fourth Apply
	

}

void UAnimRoutine::LoadAnimSequence(const FString& FilePath)
{
	UAnimSequence* Anim {LoadObject<UAnimSequence>(nullptr, *FilePath)};
	if(Anim)
	{
		SourceAnim = Anim;
	}
}

void UAnimRoutine::AddKey(const FString& AnimFilePath, float Time, const FName& BoneName, const FTransform& AdditiveTransform)
{
	UAnimSequence* Anim {LoadObject<UAnimSequence>(nullptr, *AnimFilePath)};
	if(Anim)
	{
		Anim -> AddKeyToSequence(Time, BoneName, AdditiveTransform);
	}

}
