#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimSequence.h"
#include "AnimationRoutine.h"
#include "AssetViewUtils.h"

void UAnimRoutine::MapTaskToAnim(UAnimSequence* Anim, FName BoneName)
{
	if (Anim)
	{
		TArray<FName> BoneTrackNames{};
		Anim->GetDataModel()->GetBoneTrackNames(BoneTrackNames);
		double AnimLength = Anim->GetDataModel()->GetPlayLength();

		TFunction<double(double, double)> GetFrameTime = [&AnimLength](double frame, double time) {
			time = (time / frame);
			return FGenericPlatformMath::IsNaN(time) || !FGenericPlatformMath::IsFinite(time) ? 0 : AnimLength - time;
		};

		TFunction<double(double, double)> Bounce = [](double value, double time) {
			return value * sin(time);
		};

		TFunction<bool(const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame)> Iterator;
		Iterator = [&AnimLength, &Bounce, &BoneName, &GetFrameTime](const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame) -> bool {
				double PosY = Bounce(Pos.Y, GetFrameTime(Frame.Value, AnimLength));
				UE_LOG(LogTemp, Display, TEXT("%s Pos Y: %f"), *BoneName.ToString(), PosY);
				return true;
			};

		Anim->GetDataModel()->IterateBoneKeys(BoneName, Iterator);
	}
}

void UAnimRoutine::LoadAnimSequence(const FString& FilePath)
{
	UAnimSequence* Anim{ LoadObject<UAnimSequence>(nullptr, *FilePath) };
	if (Anim)
	{
	}
}

void UAnimRoutine::AddKey(UAnimSequence* const Anim, float Time, const FName& BoneName, const FTransform& AdditiveTransform)
{
	if (Anim)
	{
		Anim->AddKeyToSequence(Time, BoneName, AdditiveTransform);
	}
}
