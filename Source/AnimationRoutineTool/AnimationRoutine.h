#include "CoreMinimal.h"
#include <functional>
#include "AnimationRoutine.generated.h"

class UAnimSequence;

// Original Approach
// Collect data from UAnimSequence
// Cache into custom struct
/*=================================================================================*/
USTRUCT(noexport, BlueprintType)
struct FMappedAnimation
{
private:
	TArray<FName> BoneTrackNames;
	TArray<double> KeyTimings;
	TArray<TArray<FTransform>> Transforms;
	// okay but what if i did a functional approach
public:
	// need a way to turn MappedAnims to animation sequences
	//FMappedAnimation(const FString& AnimFilePath);
	FMappedAnimation(const UAnimSequence* Anim);
	FMappedAnimation();

	TArray<FTransform> GetTransforms(FName BoneTrackName);
	void SetPoseAt(const TArray<FTransform>* const Pose);

    /*
     * Reading the transform as function:
     *	- Read the animation file at point in sequence
     *	- read all the transforms for that bone
     *	    - try regression fitting
    */
};


// New Approach
// Provide a function which will be applied to a group of bones
// Allows for the procedure to be undone
// Much more flexible
/*=================================================================================*/
// can be converted to a strategy pattern w/ the param abstracted into an object
// which represents the groups of bones

USTRUCT(noexport, BlueprintType)
struct FAnimationTask
{
private:
    const UAnimSequence* SourceAnimation;
    std::function<void (FTransform)> AnimationTask;

public:
    FAnimationTask(const UAnimSequence* Anim, std::function<void (FTransform)> Task) :
	SourceAnimation(Anim), AnimationTask(Task){};

    // it could be helpful to abstract the params into its own object
    // that way relations and constraints on the bones can be unified and applied in an object
    void ApplyTask(FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform> OutTransforms);
    void ApplyTask(FName BoneTrack, TArray<FTransform> OutTransforms);
    // with multiple bone tracks the arrays will be indexed accordingly
    void ApplyTask(TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform> OutTransforms);
    void ApplyTask(TArray<FName> BoneTracks, TArray<FTransform> OutTransforms);

};


UCLASS(Blueprintable)
class UAnimationRecorder : public UObject
{
    GENERATED_BODY()

private:
    USkeletalMesh* Subject;
    UAnimSequence RecordedAnimation;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StartRecording(AActor* Subject);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    FMappedAnimation StopRecording();

};

UCLASS(Blueprintable)
class UAnimationRoutine : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:
    UAnimSequence* SourceAnimation;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void LoadAnimationSequence(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	 void AddKey(const FString& AnimFilePath, float Time, const FName& BoneName, const FTransform& AdditiveTransform);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void MapAnimation(const UAnimSequence* Anim);
};

