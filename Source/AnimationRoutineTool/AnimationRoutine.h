#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;

USTRUCT(BlueprintType)
struct FAnimTask
{
    GENERATED_BODY()
private:
    TFunction<void (FTransform&)> AnimTask;

public:
    FAnimTask() = default;
    FAnimTask(const TFunction<void (FTransform&)>& Task) : AnimTask(Task){};

    // it could be helpful to abstract the params into its own object
    // that way relations and constraints on the bones can be unified and applied in an object
    void ApplyTaskTo(const UAnimSequence* Anim, const FName& BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const;
    void ApplyTaskTo(const UAnimSequence* Anim, const FName& BoneTrack, TArray<FTransform>& OutTransforms) const;
    // with multiple bone tracks the arrays will be indexed accordingly
    void ApplyTaskTo(const UAnimSequence* Anim, const TArray<FName>& BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const;
    void ApplyTaskTo(const UAnimSequence* Anim, const TArray<FName>& BoneTracks, TArray<FTransform>& OutTransforms) const;
};


UCLASS(Blueprintable)
class UAnimRecorder : public UObject
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    USkeletalMesh* Subject;
    UPROPERTY(EditAnywhere)
    UAnimSequence* RecordedAnim;

public: 
    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void StartRecording(AActor* NewSubject);

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
	static void MapTaskToAnim(const UAnimSequence* Anim, const FAnimTask& Task);
};
