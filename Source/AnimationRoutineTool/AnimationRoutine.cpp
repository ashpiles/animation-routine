#include "AnimationRoutine.h"
#include "AnimationTask.h"
#include "PoseSlice.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"


void UAnimRoutine::MapTaskToAnim(UAnimSequence* Anim, UAnimTask* Task)
{
	if (Task && Anim)
	{
		SourceAnim = Anim;
		TaskInstance = Task;
		TArray<FName> BoneTrackNames {};
		FTransform Transform = FTransform::Identity;
		SourceAnim->GetDataModel()->GetBoneTrackNames(BoneTrackNames);

		FMappedAnimation MappedAnim(SourceAnim);
		double AnimLength = SourceAnim->GetDataModel()->GetPlayLength();
		
		 
		for(FName& BoneName : BoneTrackNames)
		{
			TaskInstance->ApplyAnimationTask(MappedAnim.GetBoneVector(BoneName));
			SourceAnim->GetDataModel()->IterateBoneKeys(BoneName,
				[&](const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame) -> bool
				{
					Transform = MappedAnim.GetBoneVector(BoneName)[Frame];
					UE::Math::TVector<double> Translation(Pos);
					UE::Math::TQuat<double> Rotation(Rot);
					UE::Math::TVector<double> Scale(Size);
					Transform.GetTranslation() += Translation;
					Transform.GetRotation() += Rotation;
					Transform.GetScale3D() += Scale;
					double Time = (AnimLength / Frame.Value);
					Time = FGenericPlatformMath::IsNaN(Time) || !FGenericPlatformMath::IsFinite(Time) ? 0 : AnimLength - Time;

					// I have tried a million different approaches, but I keep getting an access violation when trying to add a keyframe
					//     ````````````````````````````````````````````````````````
					//	   ` Hate. Let me tell you how I have come to hate you... ` 
					//	   `|/`````````````````````````````````````````````````````
					//	    v
					//	 (,⚆_⚆)\       											/
					SourceAnim->AddKeyToSequence(Time, BoneName, Transform);
					UE_LOG(LogTemp, Display, TEXT("%s Transform:\n%s"), *BoneTrackNames[0].ToString(), *Transform.ToString());
					return true;
				}); 
		}
	}
}

void UAnimRoutine::LoadAnimSequence(const FString& FilePath)
{
	UAnimSequence* Anim {LoadObject<UAnimSequence>(nullptr, *FilePath)};
	if(Anim)
	{
		SourceAnim = Anim;
	}
}

void UAnimRoutine::AddKey(UAnimSequence* const Anim, float Time, const FName& BoneName, const FTransform& AdditiveTransform)
{
	if(Anim)
	{
		Anim -> AddKeyToSequence(Time, BoneName, AdditiveTransform);
	}

}
