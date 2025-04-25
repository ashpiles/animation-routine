#include "CoreMinimal.h"
#include "AnimationTask.generated.h"

class UAnimSequence;

UDELEGATE()
DECLARE_DELEGATE_OneParam(AnimTaskFunctor, FTransform&)

UCLASS()
class UAnimTask: public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:
    AnimTaskFunctor Task;

public:
    UAnimTask() = default;
    UAnimTask(TFunction<void (FTransform&)> Task) : AnimTaskFunctor.BindLambda(Task){};

    void ApplyTaskTo(const UAnimSequence*, FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const;
    void ApplyTaskTo(const UAnimSequence*, FName BoneTrack, TArray<FTransform>& OutTransforms) const;
    void ApplyTaskTo(const UAnimSequence*, TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const;
    void ApplyTaskTo(const UAnimSequence*, TArray<FName> BoneTracks, TArray<FTransform>& OutTransforms) const;
};

