#include "CoreMinimal.h"
#include "AnimationRoutine.generated.h"

class UAnimSequence;
class UAnimTask;

// Functional Reactive Animation
namespace FRAN
{ 
	// A function of time returning any real number
	template<typename T>
	using TBehavior = TFunction<T(float)>; 

	// A Behavior which does not change its value over time
	template<typename T>
	TBehavior<T> Constant(const T& Value)
	{
		return [Value](float) {return Value;};
	}

	// Identity time Behavior
//	inline TBehavior<float> Time = [](float Time) {return Time;};

	// The Lifting function turns all parameters of a function into Behaviors
	template<typename F, typename... B>
	auto Lift(F Func, B... Behaviors)
	{
		return [=](float Time)
		{
			return Func(Behaviors(Time)...);
		};
	}
}

UCLASS(Blueprintable)
class UAnimRoutine : public UBlueprintFunctionLibrary
{
    GENERATED_BODY() 

public:

    UFUNCTION(BlueprintCallable, Category="MyEditorTools")
    static void MapTaskToAnim(UAnimSequence* Anim, FName BoneName, float Amp, float Freq);

};


