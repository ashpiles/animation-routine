#include "AnimationTask.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"

void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
{
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack,KeyFrames, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		AnimTask(Transform);
	}
}

void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FTransform>& OutTransforms) const
{
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		AnimTask(Transform);
	}
}


void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
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

void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FTransform>& OutTransforms) const
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
