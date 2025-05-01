#include "AnimationTask.h"
#include "AnimationTaskContext.h"


void UAnimSequenceContext::AcceptTask(UAnimTask& Task)
{
	// converst our anim context to an array of pose slice
	// pose slices given to our apply animation task
	// then our animation task changes the values via ref
	FPoseSlice<UAnimSequence> Poses(AnimSource);
	
	Task.ApplyAnimationTask(Poses);
}

