// #define KEYFRAME(...) InitKeyframe((Keyframe) __VA_ARGS__)
// #define Define_Keyframe(type, subtype)   \
//     typedef struct {            \
//         type Add;           \
//         type Mult;          \
//         int EasingFrames; \
//         int HeldFrames; \
//     } __keyframe__##type;       \
//     type Transform##type(TransformContext* ctx, type input){\
//         type output;\
//         output = __add_##type(ctx->__Modification.Add, input);\
//         output = __mult_##type(ctx->__Modification.Mult, output);\
//     }\
//     type InitKeyframe##type(){\
//     }\

#include "stdio.h"

#define NEW_KEYFRAME_Rectangle(...) NewKeyframe_Rectangle((Keyframe_Rectangle) __VA_ARGS__)
#define NEW_KEYFRAME_Color(...) NewKeyframe_Color((Keyframe_Color) __VA_ARGS__)

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

typedef enum {
    PLAYMODE_PLAY_ONCE,
    PLAYMODE_LOOP,
    PLAYMODE_BOOMERANG_ONCE,
    PLAYMODE_BOOMERANG_LOOP

    //alternatively: PLAY_ONCE, LOOP, BOOMERANG
} PlayMode;

typedef struct {
    float _1;
    float _2;
    float _3;
    float _4;
} _Vector_4f;

typedef struct {
    _Vector_4f Add;
    _Vector_4f Mult;
} Modifier_4f;

void __StepIndex(int* CtxIndex, bool* CtxPlaying, bool* CtxReverse, int MaxIndex, PlayMode CtxPlaymode, int CtxNumKeyframes) {
    
    switch (CtxPlaymode)
    {
    case PLAYMODE_LOOP:
        
        if(*CtxReverse) {
            (*CtxIndex)--;
        }
        else {
            (*CtxIndex)++;
        }

        *CtxIndex = (*CtxIndex) % MaxIndex;
        break;
    
    case PLAYMODE_PLAY_ONCE:

        if(*CtxReverse) {
            (*CtxIndex)--;
        }
        else {
            (*CtxIndex)++;
        }
        
        if(*CtxIndex >= MaxIndex) {
            *CtxIndex = MaxIndex;
        }

        if(*CtxIndex <= 0) {
            *CtxIndex = 0;
        }
        break;

    case PLAYMODE_BOOMERANG_LOOP:

        if(*CtxReverse) {
            (*CtxIndex)--;
        }
        else {
            (*CtxIndex)++;
        }
        
        if(*CtxIndex == MaxIndex) {
            *CtxReverse = true;
        }

        if(*CtxIndex == 0) {
            *CtxReverse = false;
        }

        break;

    default:
        break;
    }

}

// ===== Rectangle specific ======

typedef struct {
    Rectangle Add;
    Rectangle Mult;
    //Rectangle To; //idea is that you could alternatively just define the final parameters

    int EasingFrames;
    int HeldFrames;
} Keyframe_Rectangle;

Keyframe_Rectangle NewKeyframe_Rectangle(Keyframe_Rectangle k);

typedef struct {
    Keyframe_Rectangle* Keyframes;
    int NumKeyframes;
    int Index;
    bool Playing;    
    bool __Reverse; //might want to cheange this to enum Direction = FORWARD or REVERSE for clarity
    PlayMode Mode;

    //read-only
    int __KeyframeIndex;
    bool __Held;
    Keyframe_Rectangle __Modification;
} TransformContext_Rectangle;

Rectangle __ApplyTransform_Rectangle(Keyframe_Rectangle modifier, Rectangle input) {
    // printf("adding: %f + %f\n", modifier.Add.x, input.x);
    input = (Rectangle) {modifier.Add.x + input.x, modifier.Add.y + input.y, modifier.Add.width + input.width, modifier.Add.height + input.height};

    //scaling not yet applied -- need to initialize to 1 instead of zero so default doesn't change anything
    // printf("scaling: %f * %f\n", modifier.Mult.x, input.x);
    return (Rectangle) {modifier.Mult.x * input.x, modifier.Mult.y * input.y, modifier.Mult.width * input.width, modifier.Mult.height * input.height};

    // and then obviously there will need to be some offsetting when the option to add 
}

Keyframe_Rectangle __CalculateModifier_Rectangle(TransformContext_Rectangle* ctx) {
    Keyframe_Rectangle modifier = NEW_KEYFRAME_Rectangle({});
    int cumulative_lower = 0;
    int cumulative_upper = 0;
    for(int i = 0; i < ctx->NumKeyframes; i++) {

        //CANT just use frame[i].easingFrames, need to convert into some sort of cumulative index. EX:
        // {.Easing=10, .held=15}, {.easing=7, held=12}
        // becomes...
        // 10, 25, 32, 44
        // compare(idx, 0, 10), compare(idx, 25, 32)

        cumulative_upper = cumulative_lower + ctx->Keyframes[i].EasingFrames;
        float easing_index = QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper));

        modifier.Add.x += ( easing_index * ctx->Keyframes[i].Add.x );
        modifier.Add.y += ( easing_index * ctx->Keyframes[i].Add.y );
        modifier.Add.width += ( easing_index * ctx->Keyframes[i].Add.width );
        modifier.Add.height += ( easing_index * ctx->Keyframes[i].Add.height );

        modifier.Mult.x = ( 1 + ( easing_index * (ctx->Keyframes[i].Mult.x - 1)) );
        modifier.Mult.y = ( 1 + ( easing_index * (ctx->Keyframes[i].Mult.y - 1)) );
        modifier.Mult.width = ( 1 + ( easing_index * (ctx->Keyframes[i].Mult.width - 1)) );
        modifier.Mult.height = ( 1 + ( easing_index * (ctx->Keyframes[i].Mult.height - 1)) );

        cumulative_lower += ctx->Keyframes[i].EasingFrames + ctx->Keyframes[i].HeldFrames;
    }

    //printf("mult x: %f\n", modifier.Mult.x);

    // return_vector.x = vector.x + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].AOffset);
    // return_vector.x *= (1 + (ModFactor * (ctx->Keyframes[ctx->__KeyframeIndex].AScale - 1)) );

    return modifier;
}

Rectangle Animate_Rectangle(TransformContext_Rectangle* ctx, Rectangle input) {

    //step through index
    if(ctx->Playing) {
        int MaxIndex = 0;
        for (int i = 0; i < ctx->NumKeyframes; i++) {
            MaxIndex += ctx->Keyframes[i].EasingFrames;
            MaxIndex += ctx->Keyframes[i].HeldFrames;
        }
        __StepIndex(&ctx->Index, &ctx->Playing, &ctx->__Reverse, MaxIndex, ctx->Mode, ctx->NumKeyframes);
        
    }

    //find modification
    ctx->__Modification = __CalculateModifier_Rectangle(ctx);

    return __ApplyTransform_Rectangle(ctx->__Modification, input);
}

Keyframe_Rectangle NewKeyframe_Rectangle(Keyframe_Rectangle k) {
    Keyframe_Rectangle zero_initialized = {0};
    Keyframe_Rectangle default_keyframe = {
        .Add.x=0.0f, 
        .Add.y=0.0f,
        .Add.width=0.0f,
        .Add.height=0.0f, 
        .Mult.x=1.0f,
        .Mult.y=1.0f,
        .Mult.width=1.0f,
        .Mult.height=1.0f, 
        .EasingFrames=0, 
        .HeldFrames=0
        };

    if(k.Add.x == zero_initialized.Add.x) {
        k.Add.x = default_keyframe.Add.x;
    }
    if(k.Add.y == zero_initialized.Add.y) {
        k.Add.y = default_keyframe.Add.y;
    }
    if(k.Add.width == zero_initialized.Add.width) {
        k.Add.width = default_keyframe.Add.width;
    }
    if(k.Add.height == zero_initialized.Add.height) {
        k.Add.height = default_keyframe.Add.height;
    }
    if(k.Mult.x == zero_initialized.Mult.x) {
        k.Mult.x = default_keyframe.Mult.x;
    }
    if(k.Mult.y == zero_initialized.Mult.y) {
        k.Mult.y = default_keyframe.Mult.y;
    }
    if(k.Mult.width == zero_initialized.Mult.width) {
        k.Mult.width = default_keyframe.Mult.width;
    }
    if(k.Mult.height == zero_initialized.Mult.height) {
        k.Mult.height = default_keyframe.Mult.height;
    }

    return k;
}

// ===== Rectangle specific ======

// ===== Color specific ======

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color__f;

typedef struct {
    Color__f Add;
    Color__f Mult; 

    int EasingFrames;
    int HeldFrames;
} Keyframe_Color;

Keyframe_Color NewKeyframe_Color(Keyframe_Color k);

typedef struct {
    Keyframe_Color* Keyframes;
    int NumKeyframes;
    int Index;
    bool Playing;    
    bool __Reverse; //might want to cheange this to enum Direction = FORWARD or REVERSE for clarity
    PlayMode Mode;

    //read-only
    int __KeyframeIndex;
    bool __Held;
    Keyframe_Color __Modification;
} TransformContext_Color;

Color __ApplyTransform_Color(Keyframe_Color modifier, Color input) {
    // printf("adding: %f + %f\n", modifier.Add.r, input.r);
    input = (Color) {modifier.Add.r + input.r, modifier.Add.g + input.g, modifier.Add.b + input.b, modifier.Add.a + input.a};

    //scaling not yet applied -- need to initialize to 1 instead of zero so default doesn't change anything
    // printf("scaling: %f * %f\n", modifier.Mult.r, input.r);
    return (Color) {
        (int) ( modifier.Mult.r * (float) input.r ),
        (int) ( modifier.Mult.g * (float) input.g ),
        (int) ( modifier.Mult.b * (float) input.b ),
        (int) ( modifier.Mult.a * (float) input.a )
        };

    // and then obviously there will need to be some offsetting when the option to add 
}

Keyframe_Color __CalculateModifier_Color(TransformContext_Color* ctx) {
    Keyframe_Color modifier = {0};
    int cumulative_lower = 0;
    int cumulative_upper = 0;
    for(int i = 0; i < ctx->NumKeyframes; i++) {

        //CANT just use frame[i].easingFrames, need to convert into some sort of cumulative index. EX:
        // {.Easing=10, .held=15}, {.easing=7, held=12}
        // becomes...
        // 10, 25, 32, 44
        // compare(idx, 0, 10), compare(idx, 25, 32)

        cumulative_upper = cumulative_lower + ctx->Keyframes[i].EasingFrames;
        float easing_index = QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper));

        modifier.Add.r += ( easing_index * (float) ctx->Keyframes[i].Add.r );
        modifier.Add.g += ( easing_index * (float) ctx->Keyframes[i].Add.g );
        modifier.Add.b += ( easing_index * (float) ctx->Keyframes[i].Add.b );
        modifier.Add.a += ( easing_index * (float) ctx->Keyframes[i].Add.a );

        modifier.Mult.r = ( 1 + ( easing_index * (float) (ctx->Keyframes[i].Mult.r - 1)) );
        modifier.Mult.g = ( 1 + ( easing_index * (float) (ctx->Keyframes[i].Mult.g - 1)) );
        modifier.Mult.b = ( 1 + ( easing_index * (float) (ctx->Keyframes[i].Mult.b - 1)) );
        modifier.Mult.a = ( 1 + ( easing_index * (float) (ctx->Keyframes[i].Mult.a - 1)) );

        cumulative_lower += ctx->Keyframes[i].EasingFrames + ctx->Keyframes[i].HeldFrames;
    }


    // return_vector.r = vector.r + (ModFactor * ctx->Keyframes[ctx->__KeyframeIndex].AOffset);
    // return_vector.r *= (1 + (ModFactor * (ctx->Keyframes[ctx->__KeyframeIndex].AScale - 1)) );

    return modifier;
}

Color Animate_Color(TransformContext_Color* ctx, Color input) {
    

    //step through index
    if(ctx->Playing) {
        int MaxIndex = 0;
        for (int i = 0; i < ctx->NumKeyframes; i++) {
            MaxIndex += ctx->Keyframes[i].EasingFrames;
            MaxIndex += ctx->Keyframes[i].HeldFrames;
        }
        __StepIndex(&ctx->Index, &ctx->Playing, &ctx->__Reverse, MaxIndex, ctx->Mode, ctx->NumKeyframes);
    }

    //find modification
    ctx->__Modification = __CalculateModifier_Color(ctx);
    printf("%f %f\n", ctx->__Modification.Mult.r, ctx->__Modification.Add.r);

    return __ApplyTransform_Color(ctx->__Modification, input);
}

Keyframe_Color NewKeyframe_Color(Keyframe_Color k) {
    Keyframe_Color zero_initialized = {0};
    Keyframe_Color default_keyframe = {
        .Add.r=0.0f, 
        .Add.g=0.0f,
        .Add.b=0.0f,
        .Add.a=0.0f, 
        .Mult.r=1.0f,
        .Mult.g=1.0f,
        .Mult.b=1.0f,
        .Mult.a=1.0f, 
        .EasingFrames=0, 
        .HeldFrames=0
        };

    if(k.Add.r == zero_initialized.Add.r) {
        k.Add.r = default_keyframe.Add.r;
    }
    if(k.Add.g == zero_initialized.Add.g) {
        k.Add.g = default_keyframe.Add.g;
    }
    if(k.Add.b == zero_initialized.Add.b) {
        k.Add.b = default_keyframe.Add.b;
    }
    if(k.Add.a == zero_initialized.Add.a) {
        k.Add.a = default_keyframe.Add.a;
    }
    if(k.Mult.r == zero_initialized.Mult.r) {
        k.Mult.r = default_keyframe.Mult.r;
    }
    if(k.Mult.g == zero_initialized.Mult.g) {
        k.Mult.g = default_keyframe.Mult.g;
    }
    if(k.Mult.b == zero_initialized.Mult.b) {
        k.Mult.b = default_keyframe.Mult.b;
    }
    if(k.Mult.a == zero_initialized.Mult.a) {
        k.Mult.a = default_keyframe.Mult.a;
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