#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;

USTRUCT(noexport, BlueprintType)
struct FAnimTask
{
private:
    const UAnimSequence* SourceAnim;
    TFunction<void (FTransform&)> AnimTask;

public:
    FAnimTask(const UAnimSequence* Anim, TFunction<void (FTransform&)> Task) :
	SourceAnim(Anim), AnimTask(Task){};

    // it could be helpful to abstract the params into its own object
    // that way relations and constraints on the bones can be unified and applied in an object
    void ApplyTaskTo(FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms);
    void ApplyTaskTo(FName BoneTrack, TArray<FTransform>& OutTransforms);
    // with multiple bone tracks the arrays will be indexed accordingly
    void ApplyTaskTo(TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms);
    void ApplyTaskTo(TArray<FName> BoneTracks, TArray<FTransform>& OutTransforms);
};


UCLASS(Blueprintable)
class UAnimRecorder : public UObject
{
    GENERATED_BODY()

private:
    USkeletalMesh* Subject;
    UAnimSequence RecordedAnim;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StartRecording(AActor* Subject);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StopRecording();

};

UCLASS(Blueprintable)
class UAnimRoutine : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:
    UAnimSequence* SourceAnim;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void LoadAnimSequence(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	 void AddKey(const FString& AnimFilePath, float Time, const FName& BoneName, const FTransform& AdditiveTransform);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
	void MapTaskToAnim(const UAnimSequence* Anim, TFunction<void (FTransform&)> AnimTask);
};
