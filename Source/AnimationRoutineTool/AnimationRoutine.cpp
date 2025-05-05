#include "AnimationRoutine.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimSequence.h"
#include "AssetViewUtils.h"

void UAnimRoutine::MapTaskToAnim(UAnimSequence* Anim, FName BoneName, float Amp, float Freq)
{
	if (!Anim) return; 

	// Wraps our sin function into a TBehavior
	auto Bounce = [](float Amplitude, float Frequency) -> FRAN::TBehavior<float>
	{
		return [Amplitude, Frequency](float t)
		{
			return Amplitude * FMath::Sin(t * Frequency);
		};
	};

	// Converts a FFrameNumber to the relevant animations time code
	auto TimeCode = [Anim](FFrameNumber Frame) -> float 
	{
		const float TotalLength = Anim->GetPlayLength();
		const float	TotalFrames = Anim->GetNumberOfSampledKeys();
		return TotalLength * (Frame.Value / TotalFrames);
	};
 

	TFunction<bool(const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame)> Iterator =
		[Anim, Bounce, TimeCode, BoneName, Amp, Freq] (const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame) -> bool
		{
			const float t = TimeCode(Frame);
			auto b = Bounce(Amp, Freq);
			float result = b(t);
			FTransform transform = FTransform(UE::Math::TVector<double>(Pos.X, result, Pos.Z));
			Anim->AddKeyToSequence(t, BoneName, transform);
			
			UE_LOG(LogTemp, Display, TEXT("%s Y bounce at time %f: %f"), *BoneName.ToString(), t, result);
			return true;
		};

	// Runs the given function over every frame
	Anim->GetDataModel()->IterateBoneKeys(BoneName, Iterator);
}

/* Notes:
 * It should be possible to wrap our applications into another function or object and then slip
 */
