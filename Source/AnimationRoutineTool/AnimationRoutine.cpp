#include "AnimationRoutine.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimSequence.h"
#include "AssetViewUtils.h"

void UAnimRoutine::MapTaskToAnim(UAnimSequence* Anim, FName BoneName, float Amp, float Freq)
{
	if (IsValid(Anim)) return; 

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
		[=] (const FVector3f& Pos, const FQuat4f& Rot, const FVector3f Size, const FFrameNumber& Frame) -> bool
		{
			const float timeCode = TimeCode(Frame);
			auto bounceBehavior = Bounce(Amp, Freq);
			float result = bounceBehavior(timeCode);
			FTransform transform = FTransform(UE::Math::TVector<double>(Pos.X, result, Pos.Z));
			Anim->AddKeyToSequence(timeCode, BoneName, transform);
			
			UE_LOG(LogTemp, Display, TEXT("%s Y bounce at time %f: %f"), *BoneName.ToString(), timeCode, result);
			return true;
		};

	// Runs the given function over every frame in the animation
	Anim->GetDataModel()->IterateBoneKeys(BoneName, Iterator);
}

/* Notes:
 * If the actual adding to the animation source is wrapped in a function the
 * application can be bounded together into a monoid that is easier to manipulate
 * 
 * A procedural animation can be represented as a list or vector of these functions
 * This should neatly bow-tie to regular imperative programming so that this code stays
 * where it is intended to be
 * Which could possibly be done w/ a command pattern
 *
 * To create a 
 */
