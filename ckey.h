#define TEST 44

#define KEYFRAME(...) InitKeyframe((Keyframe) __VA_ARGS__)
#define Define_Keyframe(type, subtype)   \
    typedef struct {            \
        type Add;           \
        type Mult;          \
        int EasingFrames; \
        int HeldFrames; \
    } __keyframe__##type;       \
    type Transform##type(TransformContext* ctx, type input){\
        type output;\
        output = __add_##type(ctx->__Modification.Add, input);\
        output = __mult_##type(ctx->__Modification.Mult, output);\
    }\
    type InitKeyframe##type(){\
    }\

#define __USE_RAYLIB true
#if __USE_RAYLIB
#define __Vector4_f32 Rectangle
#define __Vector2_f32 Vector2
#define __Vector4_i32 Color
Rectangle __add_Rectangle(Rectangle _1, Rectangle _2) {
    return (Rectangle){_1.x+_2.x, _1.y+_2.y, _1.width+_2.width, _1.height+_2.height};
}
Rectangle __mult_Rectangle(Rectangle _1, Rectangle _2) {
    return (Rectangle){_1.x*_2.x, _1.y*_2.y, _1.width*_2.width, _1.height*_2.height};
}
#endif

//Define_Keyframe(Rectangle, float);
float compare(int x, int lower, int upper);
float QuadraticEaseInOut(float p);

void temp_func(){
    typedef struct {
        float a;
        float b;
        float c;
    } uniform_struct;

    float* arr;
    uniform_struct s = {1.2, 2.3, 3.4};
    arr = (float*)&s;
    
    printf("%f,%f, %f\n", s.a, s.b, s.c);
    printf("%f, %f, %f\n", arr[0], arr[1], arr[2]);
    printf("%lu, %lu", sizeof(uniform_struct), sizeof(float));
}

typedef enum {
    PLAYMODE_PLAY_ONCE,
    PLAYMODE_PLAY_ONCE_AND_RESET,
    PLAYMODE_BOOMERANG
} PlayMode;

typedef struct {
    float AOffset;
    float BOffset;
    
    float AScale;
    float BScale;

    int EasingFrames;
    int HeldFrames;

} Keyframe;

// ===== Rectangle specific ======

typedef struct {
    Rectangle Add;
    Rectangle Mult; 

    int EasingFrames;
    int HeldFrames;
} Keyframe_Rectangle;

typedef struct {
    Keyframe_Rectangle* Keyframes;
    int NumKeyframes;
    int Index;
    bool Playing;
    PlayMode Mode;

    //read-only
    int __KeyframeIndex;
    bool __Held;
    Keyframe_Rectangle __Modification;
    bool __Reverse;
} TransformContext_Rectangle;

Rectangle __ApplyTransform_Rectangle(Keyframe_Rectangle modifier, Rectangle input) {
    input = (Rectangle) {modifier.Add.x + input.x, modifier.Add.y + input.y, modifier.Add.width + input.width, modifier.Add.height + input.height};
    return input;

    //scaling not yet applied -- need to initialize to 1 instead of zero so default doesn't change anything
    return (Rectangle) {modifier.Mult.x * input.height, modifier.Mult.y + input.y, modifier.Mult.width * input.width, modifier.Mult.height * input.height};

    // and then obviously there will need to be some offsetting when the option to add 
}

Keyframe_Rectangle __CalculateModifier_Rectangle(TransformContext_Rectangle* ctx) {
    Keyframe_Rectangle modifier = {0};
    int cumulative_lower = 0;
    int cumulative_upper = 0;
    for(int i = 0; i < ctx->NumKeyframes; i++) {

        //CANT just use frame[i].easingFrames, need to convert into some sort of cumulative index. EX:
        // {.Easing=10, .held=15}, {.easing=7, held=12}
        // becomes...
        // 10, 25, 32, 44
        // compare(idx, 0, 10), compare(idx, 25, 32)

        cumulative_upper = cumulative_lower + ctx->Keyframes[i].EasingFrames;

        modifier.Add.x += ( QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper)) * ctx->Keyframes[i].Add.x );
        modifier.Add.y += ( QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper)) * ctx->Keyframes[i].Add.y );
        modifier.Add.width += ( QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper)) * ctx->Keyframes[i].Add.width );
        modifier.Add.height += ( QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper)) * ctx->Keyframes[i].Add.height );

        cumulative_lower += ctx->Keyframes[i].EasingFrames + ctx->Keyframes[i].HeldFrames;
    }

    return modifier;
}

Rectangle Animate_Rectangle(TransformContext_Rectangle* ctx, Rectangle input) {

    //step through index
    if(ctx->Playing) {
        int MaxIndex = 0;
        switch (ctx->Mode)
        {
        case PLAYMODE_PLAY_ONCE_AND_RESET:
            for (int i = 0; i < ctx->NumKeyframes; i++) {
                MaxIndex += ctx->Keyframes[i].EasingFrames;
                MaxIndex += ctx->Keyframes[i].HeldFrames;
            }
            ctx->Index++;
            if(ctx->Index >= MaxIndex) {
                ctx->Index = 0;
                ctx->Playing = false;
            }
            break;
        
        case PLAYMODE_PLAY_ONCE:
            for (int i = 0; i < ctx->NumKeyframes; i++) {
                MaxIndex += ctx->Keyframes[i].EasingFrames;
                MaxIndex += ctx->Keyframes[i].HeldFrames;
            }
            ctx->Index++;
            if(ctx->Index >= MaxIndex) {
                ctx->Index = MaxIndex - 1;
                ctx->Playing = false;
            }
            break;

        case PLAYMODE_BOOMERANG:
            
            for (int i = 0; i < ctx->NumKeyframes; i++) {
                MaxIndex += ctx->Keyframes[i].EasingFrames;
                MaxIndex += ctx->Keyframes[i].HeldFrames;
            }

            if(ctx->__Reverse) {
                ctx->Index--;
            }
            else {
                ctx->Index++;
            }
            
            if(ctx->Index == MaxIndex) {
                ctx->__Reverse = true;
            }

            if(ctx->Index == 0) {
                ctx->__Reverse = false;
            }

            break;

        default:
            break;
        }
        
    }

    //find modification
    ctx->__Modification = __CalculateModifier_Rectangle(ctx);

    return __ApplyTransform_Rectangle(ctx->__Modification, input);
}

// ===== Rectangle specific ======

typedef struct {
    __Vector2_f32 Add;
    __Vector2_f32 Mult;
    int EasingFrames;
    int HeldFrames;
} Keyframe__Vector2_f32;

typedef struct {
    Keyframe* Keyframes;
    int NumKeyframes;
    int Index;
    bool Playing;
    PlayMode Mode;

    //read-only
    int __KeyframeIndex;
    bool __Held;
    Keyframe __Modification;
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

float BounceEaseOut(float p)
{
	if(p < 4/11.0)
	{
		return (121 * p * p)/16.0;
	}
	else if(p < 8/11.0)
	{
		return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
	}
	else if(p < 9/10.0)
	{
		return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
	}
	else
	{
		return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
	}
}

Vector2 Transform_Vector2(TransformContext* ctx, Vector2 vector) {

    //TODO: Need to do some sort of system that recursively applies all previous modifications so that easing in the second keyframe starts from the end of the first keyframe, not the initial position.
    //Thinking basically a modification Keyframe object that gets applied to the input vector every frame. Each frame, that modification Keyframe gets cumulatively adjusted by the timeline of keyframes.
    // For scrubbing backwards, the modifications just get undone off the modification Keyframe


    // calculate which keyframe
    Vector2 return_vector;

    if(ctx->__Held) {
        //printf("holding\n");
        return_vector.x = vector.x + ctx->Keyframes[ctx->__KeyframeIndex].AOffset;
        return_vector.x *= ctx->Keyframes[ctx->__KeyframeIndex].AScale;

        return_vector.y = vector.y + ctx->Keyframes[ctx->__KeyframeIndex].BOffset;
        return_vector.y *= ctx->Keyframes[ctx->__KeyframeIndex].BScale;
    }
    else {
        int SubKeyframeIdx, Difference = 0;
        for (int i = 1; i <= ctx->__KeyframeIndex; i++) {
            Difference += ctx->Keyframes[i-1].EasingFrames;
            Difference += ctx->Keyframes[i-1].HeldFrames;
        }
        SubKeyframeIdx = ctx->Index - Difference;
        float ModFactor = QuadraticEaseInOut(((float)SubKeyframeIdx / (float)ctx->Keyframes[ctx->__KeyframeIndex].EasingFrames));

        //printf("Difference: %d in: %f modfactor: %f\n", Difference, ((float)SubKeyframeIdx / (float)ctx->Keyframes[ctx->__KeyframeIndex].EasingFrames), ModFactor);

        //ctx->__Modification.AOffset += 

        return_vector.x = vector.x + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].AOffset);
        return_vector.x *= (1 + (ModFactor * (ctx->Keyframes[ctx->__KeyframeIndex].AScale - 1)) );

        return_vector.y = vector.y + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].BOffset);
        return_vector.y *= (1 + (ModFactor * (ctx->Keyframes[ctx->__KeyframeIndex].BScale - 1)) );

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
        //printf("%d\n", ctx->Index);

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


/*

sketch

#define KF(...) initKF(...)

struct {
    Rectangle  add;
    Rectangle mult;
    int frames;
} Keyframe_Rectangle;

Keyframe_Rectangle frames[2] = {
    //raylib rectangle:
    KF({.Add.x=10, .Mult.width=1.5}),
    KF({.Add.height=-6});
}

==================
assume no held frames

{.Add.x = 10, .EasingFrames = 20}, {.Add.y = 5, .EasingFrames = 30};

easingFactor = calc_easing(idx / 20)
output.x = input.x + (easingFactor * keyframe1.Add.x)

//instead...

easingFactor1 = calc_easing(idx / EasingFrames1)
easingFactor2 = calc_easing(idx / EasingFrames2)
modifier.add.x = easingFactor1 * keyframe1.add.x + easingFactor2 * keyframe2.add.x
output.x = modifier.add.x + input.x

modifier = {0};
int cumulative_lower, cumulative_upper = 0;
for(int i = 0; i < num_frames; i++) {

    //CANT just use frame[i].easingFrames, need to convert into some sort of cumulative index. EX:
    {.Easing=10, .held=15}, {.easing=7, held=12}
    becomes...
    10, 25, 32, 44
    compare(idx, 0, 10), compare(idx, 25, 32)

    cumulative_upper += cumulative_lower + frame[i].easingFrames;

    modifier.add.x += ( calc_easing(compare(idx, cumulative_lower, cumulative_upper)) * frame[i].add.x );
    modifier.add.y += ( calc_easing(compare(idx, cumulative_lower, cumulative_upper)) * frame[i].add.y );
    modifier.add.width += ( calc_easing(compare(idx, cumulative_lower, cumulative_upper)) * frame[i].add.width );
    modifier.add.height += ( calc_easing(compare(idx, cumulative_lower, cumulative_upper)) * frame[i].add.height );

    cumulative_lower += frame[i].easingFrames + frame[i].heldFrames;
}


*/

float compare(int x, int lower, int upper) {
    float output;
    if (x < lower) {
        output = 0;
    }
    else if (x > upper) {
        output = 1;
    }
    else {
        output = ((float)(x-lower) / (float)(upper-lower));
    }

    //printf("%d, %d, %d, %f\n", x, lower, upper, output);

    return output;
}