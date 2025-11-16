#include "stdio.h"
#include "raylib.h"

#define __CF_DEFINE_COMMON(struct_name, type, num)\
    typedef struct {\
        CF__##struct_name##f Add;\
        CF__##struct_name##f Mult; \
        int EasingFrames;\
        int HeldFrames;\
    } CF_##struct_name##Keyframe;\
    typedef struct {\
        float Add[num];\
        float Mult[num];\
    } CF__##struct_name##Modifier;\
    CF_##struct_name##Keyframe __Set##struct_name##Keyframe(CF_##struct_name##Keyframe k);\
    typedef struct {\
        CF_##struct_name##Keyframe* Keyframes;\
        int NumKeyframes;\
        int Index;\
        bool Playing;\
        bool __Reverse;\
        CF_PlayMode Mode;\
        int __KeyframeIndex;\
        bool __Held;\
        CF__##struct_name##Modifier __Modification;\
    } CF_##struct_name##Context;\
    struct_name __ApplyTransform_##struct_name(CF__##struct_name##Modifier modifier, struct_name input) {\
        float input_arr[num];\
        float output_arr[num];\
        __##struct_name##fToArray(__##struct_name##To##struct_name##f(input), input_arr);\
        for (int i = 0; i < num; i++) {\
            output_arr[i] = modifier.Add[i] + input_arr[i];\
            output_arr[i] = modifier.Mult[i] * output_arr[i];\
        }\
        return __##struct_name##fTo##struct_name(__ArrayTo##struct_name##f(output_arr));\
    }\
    CF__##struct_name##Modifier __CalculateModifier_##struct_name(CF_##struct_name##Context* ctx) {\
        CF__##struct_name##Modifier modifier = {0};\
        int cumulative_lower = 0;\
        int cumulative_upper = 0;\
        for(int i = 0; i < ctx->NumKeyframes; i++) {\
            cumulative_upper = cumulative_lower + ctx->Keyframes[i].EasingFrames;\
            float easing_index = QuadraticEaseInOut(compare(ctx->Index, cumulative_lower, cumulative_upper));\
            float struct_name##_array[num];\
            __##struct_name##fToArray(ctx->Keyframes[i].Add, struct_name##_array);\
            for (int j = 0; j < num; j++) {\
                modifier.Add[j] += ( easing_index * struct_name##_array[j] );\
            }\
            __##struct_name##fToArray(ctx->Keyframes[i].Mult, struct_name##_array);\
            for (int j = 0;j < num; j++) {\
                modifier.Mult[j] = ( 1 + ( easing_index * (float) (struct_name##_array[j] - 1)) );\
            }\
            cumulative_lower += ctx->Keyframes[i].EasingFrames + ctx->Keyframes[i].HeldFrames;\
        }\
        return modifier;\
    }\
    struct_name CF_##struct_name##Process(CF_##struct_name##Context* ctx, struct_name input) {\
        if(ctx->Playing) {\
            int MaxIndex = 0;\
            for (int i = 0; i < ctx->NumKeyframes; i++) {\
                MaxIndex += ctx->Keyframes[i].EasingFrames;\
                MaxIndex += ctx->Keyframes[i].HeldFrames;\
            }\
            __StepIndex(&ctx->Index, &ctx->Playing, &ctx->__Reverse, MaxIndex, ctx->Mode, ctx->NumKeyframes);\
        }\
        ctx->__Modification = __CalculateModifier_##struct_name(ctx);\
        return __ApplyTransform_##struct_name(ctx->__Modification, input);\
    }\

#define CF_DEFINE_4(struct_name, type, _1, _2, _3, _4) \
    typedef struct { \
        float _1;\
        float _2;\
        float _3;\
        float _4;\
    } CF__##struct_name##f;\
    \
    void __##struct_name##fToArray(CF__##struct_name##f orig, float* arr) {\
        arr[0] = orig._1;\
        arr[1] = orig._2;\
        arr[2] = orig._3;\
        arr[3] = orig._4;\
        return;\
    }\
    CF__##struct_name##f __ArrayTo##struct_name##f(float* arr) {\
        return (CF__##struct_name##f) {._1 = arr[0], ._2 = arr[1], ._3 = arr[2], ._4 = arr[3]};\
    }\
    CF__##struct_name##f __##struct_name##To##struct_name##f(struct_name orig) {\
        return (CF__##struct_name##f) {orig._1, orig._2, orig._3, orig._4};\
    }\
    struct_name __##struct_name##fTo##struct_name(CF__##struct_name##f orig) {\
        return (struct_name) {._1 = orig._1, ._2 = orig._2, ._3 = orig._3, ._4 = orig._4};\
    }\
    __CF_DEFINE_COMMON(struct_name, type, 4)\
    CF_##struct_name##Keyframe CF_Init##struct_name##Keyframe(CF_##struct_name##Keyframe k) {\
        CF_##struct_name##Keyframe zero_initialized = {0};\
        CF_##struct_name##Keyframe default_keyframe = {\
            .Add._1=0.0f, \
            .Add._2=0.0f,\
            .Add._3=0.0f,\
            .Add._4=0.0f, \
            .Mult._1=1.0f,\
            .Mult._2=1.0f,\
            .Mult._3=1.0f,\
            .Mult._4=1.0f, \
            .EasingFrames=0,\
            .HeldFrames=0\
            };\
        if(k.Add._1 == zero_initialized.Add._1) {\
            k.Add._1 = default_keyframe.Add._1;\
        }\
        if(k.Add._2 == zero_initialized.Add._2) {\
            k.Add._2 = default_keyframe.Add._2;\
        }\
        if(k.Add._3 == zero_initialized.Add._3) {\
            k.Add._3 = default_keyframe.Add._3;\
        }\
        if(k.Add._4 == zero_initialized.Add._4) {\
            k.Add._4 = default_keyframe.Add._4;\
        }\
        if(k.Mult._1 == zero_initialized.Mult._1) {\
            k.Mult._1 = default_keyframe.Mult._1;\
        }\
        if(k.Mult._2 == zero_initialized.Mult._2) {\
            k.Mult._2 = default_keyframe.Mult._2;\
        }\
        if(k.Mult._3 == zero_initialized.Mult._3) {\
            k.Mult._3 = default_keyframe.Mult._3;\
        }\
        if(k.Mult._4 == zero_initialized.Mult._4) {\
            k.Mult._4 = default_keyframe.Mult._4;\
        }\
        return k;\
    }\

#define CF_DEFINE_3(struct_name, type, _1, _2, _3) \
    typedef struct { \
        float _1;\
        float _2;\
        float _3;\
    } CF__##struct_name##f;\
    \
    void __##struct_name##fToArray(CF__##struct_name##f orig, float* arr) {\
        arr[0] = orig._1;\
        arr[1] = orig._2;\
        arr[2] = orig._3;\
        return;\
    }\
    CF__##struct_name##f __ArrayTo##struct_name##f(float* arr) {\
        return (CF__##struct_name##f) {._1 = arr[0], ._2 = arr[1], ._3 = arr[2]};\
    }\
    CF__##struct_name##f __##struct_name##To##struct_name##f(struct_name orig) {\
        return (CF__##struct_name##f) {orig._1, orig._2, orig._3};\
    }\
    struct_name __##struct_name##fTo##struct_name(CF__##struct_name##f orig) {\
        return (struct_name) {._1 = orig._1, ._2 = orig._2, ._3 = orig._3};\
    }\
    __CF_DEFINE_COMMON(struct_name, type, 3)\
    CF_##struct_name##Keyframe CF_Init##struct_name##Keyframe(CF_##struct_name##Keyframe k) {\
        CF_##struct_name##Keyframe zero_initialized = {0};\
        CF_##struct_name##Keyframe default_keyframe = {\
            .Add._1=0.0f, \
            .Add._2=0.0f,\
            .Add._3=0.0f,\
            .Mult._1=1.0f,\
            .Mult._2=1.0f,\
            .Mult._3=1.0f,\
            .EasingFrames=0,\
            .HeldFrames=0\
            };\
        if(k.Add._1 == zero_initialized.Add._1) {\
            k.Add._1 = default_keyframe.Add._1;\
        }\
        if(k.Add._2 == zero_initialized.Add._2) {\
            k.Add._2 = default_keyframe.Add._2;\
        }\
        if(k.Add._3 == zero_initialized.Add._3) {\
            k.Add._3 = default_keyframe.Add._3;\
        }\
        if(k.Mult._1 == zero_initialized.Mult._1) {\
            k.Mult._1 = default_keyframe.Mult._1;\
        }\
        if(k.Mult._2 == zero_initialized.Mult._2) {\
            k.Mult._2 = default_keyframe.Mult._2;\
        }\
        if(k.Mult._3 == zero_initialized.Mult._3) {\
            k.Mult._3 = default_keyframe.Mult._3;\
        }\
        return k;\
    }\

#define CF_DEFINE_2(struct_name, type, _1, _2) \
    typedef struct { \
        float _1;\
        float _2;\
    } CF__##struct_name##f;\
    \
    void __##struct_name##fToArray(CF__##struct_name##f orig, float* arr) {\
        arr[0] = orig._1;\
        arr[1] = orig._2;\
        return;\
    }\
    CF__##struct_name##f __ArrayTo##struct_name##f(float* arr) {\
        return (CF__##struct_name##f) {._1 = arr[0], ._2 = arr[1]};\
    }\
    CF__##struct_name##f __##struct_name##To##struct_name##f(struct_name orig) {\
        return (CF__##struct_name##f) {orig._1, orig._2};\
    }\
    struct_name __##struct_name##fTo##struct_name(CF__##struct_name##f orig) {\
        return (struct_name) {._1 = orig._1, ._2 = orig._2};\
    }\
    __CF_DEFINE_COMMON(struct_name, type, 2)\
    CF_##struct_name##Keyframe CF_Init##struct_name##Keyframe(CF_##struct_name##Keyframe k) {\
        CF_##struct_name##Keyframe zero_initialized = {0};\
        CF_##struct_name##Keyframe default_keyframe = {\
            .Add._1=0.0f, \
            .Add._2=0.0f,\
            .Mult._1=1.0f,\
            .Mult._2=1.0f,\
            .EasingFrames=0,\
            .HeldFrames=0\
            };\
        if(k.Add._1 == zero_initialized.Add._1) {\
            k.Add._1 = default_keyframe.Add._1;\
        }\
        if(k.Add._2 == zero_initialized.Add._2) {\
            k.Add._2 = default_keyframe.Add._2;\
        }\
        if(k.Mult._1 == zero_initialized.Mult._1) {\
            k.Mult._1 = default_keyframe.Mult._1;\
        }\
        if(k.Mult._2 == zero_initialized.Mult._2) {\
            k.Mult._2 = default_keyframe.Mult._2;\
        }\
        return k;\
    }\

#define CF_DEFINE_1(struct_name, type, _1) \
    typedef struct { \
        float _1;\
    } CF__##struct_name##f;\
    \
    void __##struct_name##fToArray(CF__##struct_name##f orig, float* arr) {\
        arr[0] = orig._1;\
        return;\
    }\
    CF__##struct_name##f __ArrayTo##struct_name##f(float* arr) {\
        return (CF__##struct_name##f) {._1 = arr[0]};\
    }\
    CF__##struct_name##f __##struct_name##To##struct_name##f(struct_name orig) {\
        return (CF__##struct_name##f) {orig._1};\
    }\
    struct_name __##struct_name##fTo##struct_name(CF__##struct_name##f orig) {\
        return (struct_name) {._1 = orig._1};\
    }\
    __CF_DEFINE_COMMON(struct_name, type, 1)\
    CF_##struct_name##Keyframe CF_Init##struct_name##Keyframe(CF_##struct_name##Keyframe k) {\
        CF_##struct_name##Keyframe zero_initialized = {0};\
        CF_##struct_name##Keyframe default_keyframe = {\
            .Add._1=0.0f, \
            .Mult._1=1.0f,\
            .EasingFrames=0,\
            .HeldFrames=0\
            };\
        if(k.Add._1 == zero_initialized.Add._1) {\
            k.Add._1 = default_keyframe.Add._1;\
        }\
        if(k.Mult._1 == zero_initialized.Mult._1) {\
            k.Mult._1 = default_keyframe.Mult._1;\
        }\
        return k;\
    }\
    
float compare(int x, int lower, int upper);
float QuadraticEaseInOut(float p);

typedef enum {
    CF_PLAYMODE_ONCE,
    CF_PLAYMODE_LOOP,
    CF_PLAYMODE_BOOMERANG_ONCE,
    CF_PLAYMODE_BOOMERANG_LOOP
} CF_PlayMode;

void __StepIndex(int* CtxIndex, bool* CtxPlaying, bool* CtxReverse, int MaxIndex, CF_PlayMode CtxPlaymode, int CtxNumKeyframes) {
    
    switch (CtxPlaymode)
    {
    case CF_PLAYMODE_LOOP:
        
        if(*CtxReverse) {
            (*CtxIndex)--;
        }
        else {
            (*CtxIndex)++;
        }

        *CtxIndex = (*CtxIndex) % MaxIndex;
        break;
    
    case CF_PLAYMODE_ONCE:

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
    
    case CF_PLAYMODE_BOOMERANG_ONCE:

        if(*CtxReverse) {
            (*CtxIndex)--;
        }
        else {
            (*CtxIndex)++;
        }
        
        if(*CtxIndex == MaxIndex) {
            *CtxReverse = true;
        }

        if(*CtxIndex < 0) {
            *CtxIndex = 0;
        }
        break;

    case CF_PLAYMODE_BOOMERANG_LOOP:

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

//CF_DEFINE_4(Color, int);
CF_DEFINE_4(Color, unsigned char, r, g, b, a);
//CF_DEFINE_4(Rectangle, float, x, y, width, height);
CF_DEFINE_2(Vector2, float, x, y);

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

    return output;
}