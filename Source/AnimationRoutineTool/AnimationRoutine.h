#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;
class UAnimTask;

UCLASS(Blueprintable)
class UAnimRoutine : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

private:
    UPROPERTY()
    UAnimSequence* SourceAnim;
    UPROPERTY()
    UAnimTask* TaskInstance;

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void LoadAnimSequence(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void AddKey(UAnimSequence* const Anim, float Time, const FName& BoneName, const FTransform& AdditiveTransform); 

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    void MapTaskToAnim(UAnimSequence* const Anim, UAnimTask* AnimTask);
  
};
