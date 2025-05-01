#include "CoreMinimal.h"
//#include "AnimationTaskContext.generated.h"

class UAnimTask;


class IAnimTaskContext
{
public:
	virtual void AcceptTask(UAnimTask& Task) = 0; // visits
};

class UAnimSequenceContext : public IAnimTaskContext
{
private:
	const UAnimSequence* AnimSource;
public:
	UAnimSequenceContext(const UAnimSequence* Source) : AnimSource(Source) {};

	void AcceptTask(UAnimTask& Task);
};
