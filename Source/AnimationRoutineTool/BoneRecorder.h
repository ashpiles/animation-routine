#include "CoreMinimal.h"
#include "BoneRecorder.generated.h"


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
