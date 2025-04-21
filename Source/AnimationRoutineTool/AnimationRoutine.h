#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;

USTRUCT(noexport, BlueprintType)
struct FMappedAnimation
{
// this needs a better deconstructor
// the nested tarray is trash I need to fix that
private:
	TArray<FName> BoneTrackNames;
	TArray<double> KeyTimings;
	TArray<TArray<FTransform>> Transforms;
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
     *	    - try and regression fitting
     *	point the recorder skeletal mesh a from
    */
};

UCLASS(Blueprintable)
class UAnimationRecorder : public UObject
{
    GENERATED_BODY()

private:
    UObject* Subject;
    UAnimSequence RecordedAnimation;
    FMappedAnimation MappedAnimation;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StartRecording(UObject* Subject);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StopRecording();

};

UCLASS(Blueprintable)
class UAnimationRoutine : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    static UAnimSequence LoadAnimationSequence(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	static void AddKey(const FString& AnimFilePath, float Time, const FName& BoneName, const FTransform& AdditiveTransform);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void LoadAndMapAnimation(const FString& AnimFilePath);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void MapAnimation(const UAnimSequence* Anim);


};

