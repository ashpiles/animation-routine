#include "AnimationRoutine.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"

FMappedAnimation::FMappedAnimation()
{}

FMappedAnimation::FMappedAnimation(const UAnimSequence* Anim)
{
	if(Anim)
	{
		const IAnimationDataModel* ModelInterface = Anim->GetDataModel();
		TArray<FName> OutNames {};
		TArray<FTransform> OutTransforms{};
		ModelInterface->GetBoneTrackNames(OutNames);

		for (FName Name : OutNames)
		{
			FAnimationCurveIdentifier CurveIdentifier =
				FAnimationCurveIdentifier(Name, ERawCurveTrackTypes::RCT_Transform);
			ModelInterface->GetBoneTrackTransforms(Name, OutTransforms);
			BoneTrackNames.Add(Name);
			Transforms.Add(OutTransforms);
			
			UE_LOG(LogTemp, Display, TEXT("%s - %d"), *Name.ToString(), ModelInterface->GetNumberOfKeys());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot map Animation Sequence was given null pointer"));
	}
}

// needs to be redone in respect to a better format of the datastructure
void FMappedAnimation::SetPoseAt(const TArray<FTransform>* const Pose)
{
	Transforms.Add(*Pose);
}


TArray<FTransform> FMappedAnimation::GetTransforms(FName BoneTrackName)
{
	int32 Index;
	if(BoneTrackNames.Find(BoneTrackName, Index))
	{
		
		UE_LOG(LogTemp, Warning, TEXT("BoneTrack found at: %d"), Index);
		return Transforms[Index];
	}

	UE_LOG(LogTemp, Warning, TEXT("BoneTrack not found: %s"), *BoneTrackName.ToString());
	return {};
}

void UAnimationRoutine::MapAnimation(const UAnimSequence* Anim)
{
	FMappedAnimation AnimMap(Anim);
	FName Bone("foot_l");
	TArray<FTransform> Track = AnimMap.GetTransforms(Bone);
	int Index = 0;

	for(FTransform Transform : Track)
	{
		UE_LOG(LogTemp, Display, TEXT("Key: %d\n%s"), Index, *Transform.ToString());
		Index++;
	}

}

void UAnimationRoutine::LoadAnimationSequence(const FString& FilePath)
{
	UAnimSequence* Anim {LoadObject<UAnimSequence>(nullptr, *FilePath)};
	if(Anim)
	{
		SourceAnimation = Anim;
	}
}

void UAnimationRoutine::AddKey(const FString& AnimFilePath, float Time, const FName& BoneName, const FTransform& AdditiveTransform)
{
	UAnimSequence* Anim {LoadObject<UAnimSequence>(nullptr, *AnimFilePath)};
	if(Anim)
	{
		Anim -> AddKeyToSequence(Time, BoneName, AdditiveTransform);
	}

}


void UAnimationRecorder::StartRecording(AActor* Subject)
{
	// figure out if subject has skeleton
	if(Subject)
	{
	}

}

// we return a mapped animation as this is a more mallable
// and functional friendly version of an animation
// the mapped animation needs a way to turn itself into a sequence
FMappedAnimation UAnimationRecorder::StopRecording()
{
	return FMappedAnimation();
}

/*
 * instead i can just make a base sequence that I add keys to
 * making an object with a skeleton recordable via a ActorComponent seems like the best path
 * that way the character can update the widget on events and the recording can be fine tuned
 * the Function is UAnimSequence::CreateAnimation(Mesh/SkeletonMesh/UAnimSequence*)
*/
