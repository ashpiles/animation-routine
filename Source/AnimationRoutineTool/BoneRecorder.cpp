#include "BoneRecorder.h"
#include "Animation/AnimCurveTypes.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimData/AnimDataModel.h"
#include "AssetViewUtils.h"
//
//void UAnimRecorder::StartRecording(AActor* Subject)
//{
//	// figure out if subject has skeleton
//	if(Subject)
//	{
//	}
//
//}
//
//// we return a mapped animation as this is a more mallable
//// and functional friendly version of an animation
//// the mapped animation needs a way to turn itself into a sequence
//void UAnimRecorder::StopRecording()
//{
//}
//
///*
// * instead i can just make a base sequence that I add keys to
// * making an object with a skeleton recordable via a ActorComponent seems like the best path
// * that way the character can update the widget on events and the recording can be fine tuned
// * the Function is UAnimSequence::CreateAnim(Mesh/SkeletonMesh/UAnimSequence*)
//*/
