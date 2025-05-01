#include "CoreMinimal.h"
#include "BonePose.h"
#include "AnimationTask.generated.h"

class UAnimSequence;

DECLARE_DYNAMIC_DELEGATE_OneParam(FAnimTaskFunc, FTransform&, Transform);

template<typename T>
struct FPoseSlice
{
    FPoseSlice(const T* Source) : AnimSource(Source) {};
    TArray<FTransform> BoneTransforms;
    TArray<FName> BoneNames;
    const T* AnimSource;

    // This would work best as a vector like data structure
    // there are multiple kinds of needs for a data structure of this kind
    void Append(FPoseSlice& Slice)
    {
        BoneTransforms.Append(Slice.BoneTransforms);
        BoneNames.Append(Slice.BoneNames); 
    }
};

//// just get rid of templates not worth it
//template<typename T>
//struct FAnimTaskContext
//{
//    FAnimTaskContext(const T* Source) : AnimSource(Source)
//    {
//        switch (typeid(T))
//        {
//            case(typeid(UAnimSequence*)):
//                const UAnimSequence* CastedSource = const_cast<UAnimSequence*>(AnimSource);
//                CastedSource->GetDataModel()->GetBoneTrackNames(BoneNames);
//                Poses.Add(FPoseSlice(&BoneNames));
//                // the logic of setting up the pose slice is to split between different functions it needs to be unified under something
//            break;
//            default:
//            break;
//        } 
//        
//    };
//    const T* AnimSource;
//    TArray<FPoseSlice> Poses;
//    TArray<FName> BoneNames;
//    // maybe understanding how we store animation data and then compose it?
//};
//

// visitor but we don't need an interface as we are wrapping the function to apply in this class
// it might be preferable to turn this into a command that can be chained together and have a
// larger object hold a chain of tasks (a routine)
UCLASS(Blueprintable)
class UAnimTask : public UBlueprintFunctionLibrary 
{
    GENERATED_BODY()
private:
    FAnimTaskFunc TaskFunc;
    void ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransform) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, FName BoneTrack, TArray<FTransform>& OutTransforms) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FFrameNumber> KeyFrames, TArray<FTransform>& OutTransforms) const; 
    void ApplyTaskTo(const UAnimSequence* Anim, TArray<FName> BoneTracks, TArray<FTransform>& OutTransforms) const;


public: 
    
    UFUNCTION(BlueprintCallable, Category="Animation Routine")
    static UAnimTask* CreateAnimTask(FAnimTaskFunc Func);

    void ApplyAnimationTask(FPoseSlice<UAnimSequence>& Poses); // this can be put on a stack so changes are undone 

};

