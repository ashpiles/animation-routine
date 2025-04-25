#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;
class UAnimTask;

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
    static void MapTaskToAnim(const UAnimSequence* Anim, const UAnimTask* AnimTask);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    static void CreateTask();

};
