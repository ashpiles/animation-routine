#include "CoreMinimal.h"
#include "BonePose.h"
#include "AnimationTask.generated.h"

class UAnimSequence;

DECLARE_DELEGATE_OneParam(AnimTaskFunctor, FTransform&)

struct FPoseSlice
{
    TArray<FTransform> Poses;
    TArray<FName> BoneNames;
};

// will need to restrict the kind of inputs for this template
// or this will need to be a different type of abstraction all together
template<typename T>
struct FAnimTaskContext
{
    T AnimSource;
    TArray<FPoseSlice> Poses;
};

class UAnimTask
{  
private:
    AnimTaskFunctor TaskFunctor;
    void ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransform) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FTransform>& OutTransforms) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FTransform>& OutTransforms) const;

public:
    UAnimTask() = default;
    UAnimTask(AnimTaskFunctor& Task) : TaskFunctor(Task) {};


    // in the future this will handle other kinds of contexts
    void ApplyAnimationTask(FAnimTaskContext<const UAnimSequence*> Context); // this can be put on a stack so changes are undone
    // factory pattern
        // take the source, check if valid, 
        // compose the poses to apply the task upon
};

