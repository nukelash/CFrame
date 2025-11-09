#define TEST 44

#define KEYFRAME(...) InitKeyframe((Keyframe) __VA_ARGS__)

typedef struct {
    float AOffset;
    float BOffset;
    
    float AScale;
    float BScale;

    int EasingFrames;
    int HeldFrames;

} Keyframe;

typedef enum {
    PLAYMODE_PLAY_ONCE,
    PLAYMODE_BOOMERANG
} PlayMode;

typedef struct {
    Keyframe* Keyframes;
    int NumKeyframes;
    int Index;
    bool Playing;
    PlayMode Mode;

    //read-only
    int __KeyframeIndex;
    bool __Held;
} TransformContext;

// typedef struct {
//     float A;
//     float B;
// } Vector2f;

Keyframe InitKeyframe(Keyframe k) {
    Keyframe zero_keyframe = {0};
    Keyframe default_keyframe = {
        .AOffset=0.0f, 
        .BOffset=0.0f, 
        .AScale=1.0f, 
        .BScale=1.0f, 
        .EasingFrames=0, 
        .HeldFrames=0
        };

    if(k.AOffset == zero_keyframe.AOffset) {
        k.AOffset = default_keyframe.AOffset;
    }
    if(k.BOffset == zero_keyframe.BOffset) {
        k.BOffset = default_keyframe.BOffset;
    }
    if(k.AScale == zero_keyframe.AScale) {
        k.AScale = default_keyframe.AScale;
    }
    if(k.BScale == zero_keyframe.BScale) {
        k.BScale = default_keyframe.BScale;
    }
    if(k.EasingFrames == zero_keyframe.EasingFrames) {
        k.EasingFrames = default_keyframe.EasingFrames;
    }
    if(k.HeldFrames == zero_keyframe.HeldFrames) {
        k.HeldFrames = default_keyframe.HeldFrames;
    }

    return k;
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]

//input: 0-1 (frameindex in this easing / total frames in easing)
//output: 0-1 (multiply by each modulation in Keyframe)
float QuadraticEaseInOut(float p)
{
	if(p < 0.5)
	{
		return 2 * p * p;
	}
	else
	{
		return (-2 * p * p) + (4 * p) - 1;
	}
}

Vector2 Transform_Vector2(TransformContext* ctx, Vector2 vector) {
    // calculate which keyframe
    Vector2 return_vector;
    // int keyframe_idx = 0;
    // bool held;
    // int index_count = 0;
    // for (int i = 0; i < ctx->NumKeyframes; i++) {
    //     index_count += ctx->Keyframes[i].EasingFrames;
    //     if (ctx->Index < index_count) {
    //         keyframe_idx = i;
    //         held = false;
    //         break;
    //     }
    //     index_count += ctx->Keyframes[i].HeldFrames;
    //     if (ctx->Index < index_count) {
    //         keyframe_idx = i;
    //         held = true;
    //         break;
    //     }
    // }
    //calculate how far into keyframe
    //calculate true transform values based on index
    if(ctx->__Held) {
        printf("holding\n");
        return_vector.x = vector.x + ctx->Keyframes[ctx->__KeyframeIndex].AOffset;
        return_vector.x *= ctx->Keyframes[ctx->__KeyframeIndex].AScale;

        return_vector.y = vector.y + ctx->Keyframes[ctx->__KeyframeIndex].BOffset;
        return_vector.y *= ctx->Keyframes[ctx->__KeyframeIndex].BScale;
    }
    else {
        int SubKeyframeIdx, Difference = 0;
        for (int i = 1; i < ctx->__KeyframeIndex; i++) {
            Difference += ctx->Keyframes[i-1].EasingFrames;
            Difference += ctx->Keyframes[i-1].HeldFrames;
        }
        SubKeyframeIdx = ctx->Index - Difference;
        float ModFactor = QuadraticEaseInOut(((float)SubKeyframeIdx / (float)ctx->Keyframes[ctx->__KeyframeIndex].EasingFrames));

        //printf("%f %f\n", ((float)SubKeyframeIdx / (float)ctx->Keyframes[ctx->__KeyframeIndex].EasingFrames), ModFactor);

        return_vector.x = vector.x + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].AOffset);
        return_vector.x *= (1 + (ModFactor * (1 - ctx->Keyframes[ctx->__KeyframeIndex].AScale)) );

        return_vector.y = vector.y + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].BOffset);
        return_vector.y *= (1 + (ModFactor * (1 - ctx->Keyframes[ctx->__KeyframeIndex].BScale)) );

    }
    
    if(ctx->Playing) {
        //TODO: edit based on playmode
        int MaxIndex = 0;
        for (int i = 0; i < ctx->NumKeyframes; i++) {
            MaxIndex += ctx->Keyframes[i].EasingFrames;
            MaxIndex += ctx->Keyframes[i].HeldFrames;
        }
        ctx->Index++;
        ctx->Index = ctx->Index % MaxIndex;
        printf("%d\n", ctx->Index);

        //set __KeyframeIndex
        int accumulation = 0;
        for (int i = 0; i < ctx->NumKeyframes; i++) {
            accumulation += ctx->Keyframes[i].EasingFrames;
            if (ctx->Index < accumulation) {
                ctx->__KeyframeIndex = i;
                ctx->__Held = false;
                break;
            }
            accumulation += ctx->Keyframes[i].HeldFrames;
            if (ctx->Index < accumulation) {
                ctx->__KeyframeIndex = i;
                ctx->__Held = true;
                break;
            }
        }
    }

    return return_vector;
}


