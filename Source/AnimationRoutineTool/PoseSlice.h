#pragma once
#include "CoreMinimal.h"

// Not real vector, wrapped TArray for now
struct FBoneVector
{
private:
    TArray<FTransform> Transforms;
    
public:
    FBoneVector(FName& Name, const UAnimSequence* Source) : Bone(Name)
    {
        Source->GetDataModel()->GetBoneTrackTransforms(Name, Transforms);
    };
    
    const FName Bone;

    FTransform& operator[](FFrameNumber& Index)
    {
        return Transforms[Index.Value];
    } 
    FTransform& operator[](const FFrameNumber& Index)
    {
        return Transforms[Index.Value];
    }
    FTransform& operator[](int& Index)
    {
        return Transforms[Index];
    }

    int Length()
    {
        return Transforms.Num();
    }
};

// not a real map, just some arrays interfaced by functions for now
struct FMappedAnimation
{
private:
    const UAnimSequence* AnimSource;
    TMap<FName, FBoneVector> PosesMap;
    
public: 
    FMappedAnimation(const UAnimSequence* Source) : AnimSource(Source)
    {
        TArray<FName> BoneNames;
        AnimSource->GetDataModel()->GetBoneTrackNames(BoneNames);
        for (FName BoneName : BoneNames)
        {
            PosesMap.Add(BoneName, FBoneVector(BoneName, Source));
        }
    }

    // a getter that takes the FFrameIndex and returns a map of the pose by frame would be good

    FBoneVector& GetBoneVector(FName Bone)
    {
        return PosesMap[Bone];
    }

    // the goal will be to be able to map functions to this data type
    // being able to get slices of different search queries is important for this idea
    // searching by a frame range and bones names to get a slice that can also be mapped over

};

/*
 * need to look into the FFloatCurve more, could either replace this header or better structure it
 */