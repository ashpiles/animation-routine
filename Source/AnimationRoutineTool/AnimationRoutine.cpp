#include "AnimationRoutine.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"


void UAnimRoutine::MapTaskToAnim(const UAnimSequence* Anim, const FAnimTask& Task)
{
	FAnimTask AnimTask(Task);

	TArray<FName> BoneTrackNames {};
	TArray<FTransform> OutTransforms {};
	Anim->GetDataModel()->GetBoneTrackNames(BoneTrackNames);
	// Test First Apply
	Task.ApplyTaskTo(Anim, BoneTrackNames[0], OutTransforms);

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


void FAnimTask::ApplyTaskTo(const UAnimSequence* Anim, const FName& BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
{ 
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack,KeyFrames, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		AnimTask(Transform);
	}
}

void FAnimTask::ApplyTaskTo(const UAnimSequence* Anim, const FName& BoneTrack, TArray<FTransform>& OutTransforms) const
{
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		AnimTask(Transform);
	}
}

void FAnimTask::ApplyTaskTo(const UAnimSequence* Anim, const TArray<FName>& BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
{
	for(FName BoneTrack : BoneTracks)
	{
		Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, KeyFrames, OutTransforms);
		for(FTransform Transform : OutTransforms)
		{
			AnimTask(Transform);
		}
	}
}

void FAnimTask::ApplyTaskTo(const UAnimSequence* Anim, const TArray<FName>& BoneTracks, TArray<FTransform>& OutTransforms) const
{
	for(FName BoneTrack : BoneTracks)
	{
		Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, OutTransforms);
		for(FTransform Transform : OutTransforms)
		{
			AnimTask(Transform);
		}
	}
}


void UAnimRecorder::StartRecording(AActor* NewSubject)
{
	// figure out if subject has skeleton
	if(NewSubject)
	{
	}

}

// we return a mapped animation as this is a more mallable
// and functional friendly version of an animation
// the mapped animation needs a way to turn itself into a sequence
void UAnimRecorder::StopRecording()
{
}

/*
 * instead i can just make a base sequence that I add keys to
 * making an object with a skeleton recordable via a ActorComponent seems like the best path
 * that way the character can update the widget on events and the recording can be fine tuned
 * the Function is UAnimSequence::CreateAnim(Mesh/SkeletonMesh/UAnimSequence*)
*/
