#include "AnimationTask.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"
#include "PoseSlice.h"
#include "SkeletalMeshAttributes.h"
#include "UObject/FastReferenceCollector.h"

void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
{
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack,KeyFrames, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		TaskFunc.Execute(Transform);
	}
}

void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FTransform>& OutTransforms) const
{
	Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, OutTransforms);
	for(FTransform Transform : OutTransforms)
	{
		TaskFunc.Execute(Transform);
	}
}


void UAnimTask::ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const
{
	for(FName BoneTrack : BoneTracks)
	{
		Anim->GetDataModel()->GetBoneTrackTransforms(BoneTrack, KeyFrames, OutTransforms);
		for(FTransform Transform : OutTransforms)
		{
			TaskFunc.Execute(Transform);
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
			TaskFunc.Execute(Transform);
		}
	}
}



UAnimTask* UAnimTask::CreateAnimTask(FAnimTaskFunc Func)
{
	UAnimTask* NewTask = NewObject<UAnimTask>();
	NewTask->TaskFunc = Func;
	return NewTask;
}

void UAnimTask::ApplyAnimationTask(FBoneVector& Poses)
{

	for (int x = 0; x < Poses.Length(); x++)
	{
		TaskFunc.Execute(Poses[x]);
	}
} 

/*
 * the current method is clunky, float curves are likely more suited for this
 */
