#include <math.h>
#include <tuple>
#include <type_traits>
#include <vector>
#include <iostream>

namespace CF {
//TODO put these in anonymous namespace
// ====================== Easing Functions ======================
// The following easing functions ripped from AHeasing (https://github.com/warrenm/AHEasing)

// Modeled after the line y = x
float LinearInterpolation(float p)
{
	return p;
}

// Modeled after the parabola y = x^2
float QuadraticEaseIn(float p)
{
	return p * p;
}

// Modeled after the parabola y = -x^2 + 2x
float QuadraticEaseOut(float p)
{
	return -(p * (p - 2));
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
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

// Modeled after the cubic y = x^3
float CubicEaseIn(float p)
{
	return p * p * p;
}

// Modeled after the cubic y = (x - 1)^3 + 1
float CubicEaseOut(float p)
{
	float f = (p - 1);
	return f * f * f + 1;
}

// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
float CubicEaseInOut(float p)
{
	if(p < 0.5)
	{
		return 4 * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return 0.5 * f * f * f + 1;
	}
}

// Modeled after the quartic x^4
float QuarticEaseIn(float p)
{
	return p * p * p * p;
}

// Modeled after the quartic y = 1 - (x - 1)^4
float QuarticEaseOut(float p)
{
	float f = (p - 1);
	return f * f * f * (1 - p) + 1;
}

// Modeled after the piecewise quartic
// y = (1/2)((2x)^4)        ; [0, 0.5)
// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
float QuarticEaseInOut(float p) 
{
	if(p < 0.5)
	{
		return 8 * p * p * p * p;
	}
	else
	{
		float f = (p - 1);
		return -8 * f * f * f * f + 1;
	}
}

// Modeled after the quintic y = x^5
float QuinticEaseIn(float p) 
{
	return p * p * p * p * p;
}

// Modeled after the quintic y = (x - 1)^5 + 1
float QuinticEaseOut(float p) 
{
	float f = (p - 1);
	return f * f * f * f * f + 1;
}

// Modeled after the piecewise quintic
// y = (1/2)((2x)^5)       ; [0, 0.5)
// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
float QuinticEaseInOut(float p) 
{
	if(p < 0.5)
	{
		return 16 * p * p * p * p * p;
	}
	else
	{
		float f = ((2 * p) - 2);
		return  0.5 * f * f * f * f * f + 1;
	}
}

// Modeled after quarter-cycle of sine wave
float SineEaseIn(float p)
{
	return sin((p - 1) * M_PI_2) + 1;
}

// Modeled after quarter-cycle of sine wave (different phase)
float SineEaseOut(float p)
{
	return sin(p * M_PI_2);
}

// Modeled after half sine wave
float SineEaseInOut(float p)
{
	return 0.5 * (1 - cos(p * M_PI));
}

// Modeled after shifted quadrant IV of unit circle
float CircularEaseIn(float p)
{
	return 1 - sqrt(1 - (p * p));
}

// Modeled after shifted quadrant II of unit circle
float CircularEaseOut(float p)
{
	return sqrt((2 - p) * p);
}

// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
float CircularEaseInOut(float p)
{
	if(p < 0.5)
	{
		return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
	}
	else
	{
		return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
	}
}

// Modeled after the exponential function y = 2^(10(x - 1))
float ExponentialEaseIn(float p)
{
	return (p == 0.0) ? p : pow(2, 10 * (p - 1));
}

// Modeled after the exponential function y = -2^(-10x) + 1
float ExponentialEaseOut(float p)
{
	return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

// Modeled after the piecewise exponential
// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
float ExponentialEaseInOut(float p)
{
	if(p == 0.0 || p == 1.0) return p;
	
	if(p < 0.5)
	{
		return 0.5 * pow(2, (20 * p) - 10);
	}
	else
	{
		return -0.5 * pow(2, (-20 * p) + 10) + 1;
	}
}

// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
float ElasticEaseIn(float p)
{
	return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
}

// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
float ElasticEaseOut(float p)
{
	return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
}

// Modeled after the piecewise exponentially-damped sine wave:
// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
float ElasticEaseInOut(float p)
{
	if(p < 0.5)
	{
		return 0.5 * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
	}
	else
	{
		return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
	}
}

// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
float BackEaseIn(float p)
{
	return p * p * p - p * sin(p * M_PI);
}

// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
float BackEaseOut(float p)
{
	float f = (1 - p);
	return 1 - (f * f * f - f * sin(f * M_PI));
}

// Modeled after the piecewise overshooting cubic function:
// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
float BackEaseInOut(float p)
{
	if(p < 0.5)
	{
		float f = 2 * p;
		return 0.5 * (f * f * f - f * sin(f * M_PI));
	}
	else
	{
		float f = (1 - (2*p - 1));
		return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
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

float BounceEaseIn(float p)
{
	return 1 - BounceEaseOut(1 - p);
}

float BounceEaseInOut(float p)
{
	if(p < 0.5)
	{
		return 0.5 * BounceEaseIn(p*2);
	}
	else
	{
		return 0.5 * BounceEaseOut(p * 2 - 1) + 0.5;
	}
}

enum class EasingFunction {
    LINEAR,
    QUADRATIC_IN,
    QUADRATIC_OUT,
    QUADRATIC_IN_OUT,
    CUBIC_IN,
    CUBIC_OUT,
    CUBIC_IN_OUT,
    QUARTIC_IN,
    QUARTIC_OUT,
    QUARTIC_IN_OUT,
    QUINTIC_IN,
    QUINTIC_OUT,
    QUINTIC_IN_OUT,
    SINE_IN,
    SINE_OUT,
    SINE_IN_OUT,
    CIRCULAR_IN,
    CIRCULAR_OUT,
    CIRCULAR_IN_OUT,
    EXPONENTIAL_IN,
    EXPONENTIAL_OUT,
    EXPONENTIAL_IN_OUT,
    ELASTIC_IN,
    ELASTIC_OUT,
    ELASTIC_IN_OUT,
    BACK_IN,
    BACK_OUT,
    BACK_IN_OUT,
    BOUNCE_IN,
    BOUNCE_OUT,
    BOUNCE_IN_OUT
};

float __CalculateEasing(EasingFunction easing_function, float idx) {
    switch (easing_function) {
    case EasingFunction::LINEAR:
        return LinearInterpolation(idx);
    case EasingFunction::QUADRATIC_IN:
        return QuadraticEaseIn(idx);
    case EasingFunction::QUADRATIC_OUT:
        return QuadraticEaseOut(idx);
    case EasingFunction::QUADRATIC_IN_OUT:
        return QuadraticEaseInOut(idx);
    case EasingFunction::CUBIC_IN:
        return CubicEaseIn(idx);
    case EasingFunction::CUBIC_OUT:
        return CubicEaseOut(idx);
    case EasingFunction::CUBIC_IN_OUT:
        return CubicEaseInOut(idx);
    case EasingFunction::QUARTIC_IN:
        return QuarticEaseIn(idx);
    case EasingFunction::QUARTIC_OUT:
        return QuadraticEaseOut(idx);
    case EasingFunction::QUARTIC_IN_OUT:
        return QuadraticEaseInOut(idx);
    case EasingFunction::QUINTIC_IN:
        return QuinticEaseIn(idx);
    case EasingFunction::QUINTIC_OUT:
        return QuinticEaseOut(idx);
    case EasingFunction::QUINTIC_IN_OUT:
        return QuinticEaseInOut(idx);
    case EasingFunction::SINE_IN:
        return SineEaseIn(idx);
    case EasingFunction::SINE_OUT:
        return SineEaseOut(idx);
    case EasingFunction::SINE_IN_OUT:
        return SineEaseInOut(idx);
    case EasingFunction::CIRCULAR_IN:
        return CircularEaseIn(idx);
    case EasingFunction::CIRCULAR_OUT:
        return CircularEaseOut(idx);
    case EasingFunction::CIRCULAR_IN_OUT:
        return CircularEaseInOut(idx);
    case EasingFunction::EXPONENTIAL_IN:
        return ExponentialEaseIn(idx);
    case EasingFunction::EXPONENTIAL_OUT:
        return ExponentialEaseOut(idx);
    case EasingFunction::EXPONENTIAL_IN_OUT:
        return ExponentialEaseInOut(idx);
    case EasingFunction::ELASTIC_IN:
        return ElasticEaseIn(idx);
    case EasingFunction::ELASTIC_OUT:
        return ElasticEaseOut(idx);
    case EasingFunction::ELASTIC_IN_OUT:
        return ElasticEaseInOut(idx);
    case EasingFunction::BACK_IN:
        return BackEaseIn(idx);
    case EasingFunction::BACK_OUT:
        return BackEaseOut(idx);
    case EasingFunction::BACK_IN_OUT:
        return BackEaseInOut(idx);
    case EasingFunction::BOUNCE_IN:
        return BounceEaseIn(idx);
    case EasingFunction::BOUNCE_OUT:
        return BounceEaseOut(idx);
    case EasingFunction::BOUNCE_IN_OUT:
        return BounceEaseInOut(idx);
    default:
        break;
    }
}


// https://gist.github.com/utilForever/1a058050b8af3ef46b58bcfa01d5375d
template <class T, class... TArgs> decltype(void(T{std::declval<TArgs>()...}), std::true_type{}) test_is_braces_constructible(int);
template <class, class...> std::false_type test_is_braces_constructible(...);
template <class T, class... TArgs> using is_braces_constructible = decltype(test_is_braces_constructible<T, TArgs...>(0));

struct any_type {
  template<class T>
  constexpr operator T(); // non explicit
};


enum class TransformType {
    OFFSET,
    SCALE,
    TO
};

template <typename T>
struct Keyframe{

    TransformType type;
    std::vector<float> transform;
    int easing_frames = 60;
    int held_frames = 0;
};

enum class PlayMode {
    ONCE,
    LOOP,
    BOOMERANG_ONCE,
    BOOMERANG_LOOP
};

//TODO define the header at top of file, then put implementations under #ifdef etc..
template <typename T>
struct Animation {

    Animation() {}

    Animation(T initial_object, std::vector<Keyframe<T>> keyframes){
        init(initial_object, keyframes, _playmode, _easing_func);
    }

    Animation(T initial_object, std::vector<Keyframe<T>> keyframes, PlayMode playmode, EasingFunction easing){

        init(initial_object, keyframes, playmode, easing);
    }

    void init(T initial_object, std::vector<Keyframe<T>> keyframes, PlayMode playmode, EasingFunction easing) {

        _initial = initial_object;
        _keyframes = keyframes;
        _playmode = playmode;
        _easing_func = easing;

        _index_checkpoints.push_back(0);
        for (auto k : _keyframes) {
            _index_checkpoints.push_back(_index_checkpoints.back() + k.easing_frames);
            _index_checkpoints.push_back(_index_checkpoints.back() + k.held_frames);
        }
    }

    T get() {
        if(playing) {
            int max_index = 0;
            for (int i = 0; i < _keyframes.size(); i++) {
                max_index += _keyframes[i].easing_frames;
                max_index += _keyframes[i].held_frames;
            }

            // Step index based on playmode
            __Step(max_index);
        }

        auto initial_tuple = __ToTuple(_initial);

        for (auto i = 0; i < _index_checkpoints.size(); i++) {
            if ((_index_checkpoints[i] < index) && (i%2 != 1)) {
                // auto transform_tuple = __ToTuple(_keyframes[(i/2)]._transformation);
                float easing_index = __CalculateEasing(_easing_func, __Compare(index, _index_checkpoints[i], _index_checkpoints[i+1]));
                __ApplyTransform(initial_tuple, _keyframes[(i/2)].transform, easing_index, _keyframes[(i/2)].type);
            }
        }
        return std::make_from_tuple<T>(std::move(initial_tuple));
    }

    
    // I suppose for now if you really want to modify these, feel free
    std::vector<Keyframe<T>> _keyframes;
    std::vector<int> _index_checkpoints;
    int index = 0;
    bool playing = true;
    PlayMode _playmode = PlayMode::ONCE;
    EasingFunction _easing_func = EasingFunction::CUBIC_IN_OUT;
    bool _reverse = false;
    T _initial;

private:

    void __Step(int max_index) {
        switch (_playmode) {

            case PlayMode::LOOP:
                if(_reverse) {
                    index--;
                }
                else {
                    index++;
                }

                index = index % max_index;
                break;
            
            case PlayMode::ONCE:
                if(_reverse) {
                    index--;
                }
                else {
                    index++;
                }
                
                if(index >= max_index) {
                    index = max_index;
                }

                if(index <= 0) {
                    index = 0;
                }
                break;
            
            case PlayMode::BOOMERANG_ONCE:
                if(_reverse) {
                    index--;
                }
                else {
                    index++;
                }
                
                if(index == max_index) {
                    _reverse = true;
                }

                if(index < 0) {
                    index = 0;
                }
                break;
            
            case PlayMode::BOOMERANG_LOOP:
                if(_reverse) {
                    index--;
                }
                else {
                    index++;
                }
                
                if(index == max_index) {
                    _reverse = true;
                }

                if(index == 0) {
                    _reverse = false;
                }
                break;
        }
    }

    float __Compare(int x, int lower, int upper) {
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

    //TODO probably put these in anonymous namespace as well
    template <typename TupleT>
    void __ApplyTransform(TupleT&& transformed_tuple, std::vector<float> transformer, float easing, TransformType transform) {
        int idx = 0;

        // for some reason, idx only increments correctly if you do it in the transformation
        // (and not if you use a separate idx++; line.)
        std::apply([&](auto&& ...out){

            if (transform == TransformType::OFFSET)
                ((out += (easing*transformer[idx++])), ...);
            else if (transform == TransformType::SCALE)
                ((out *= (1+(easing*(transformer[idx++]-1)))), ...);

        }, std::forward<TupleT>(transformed_tuple));
    }

    template<typename Tp>
    auto __ToTuple(Tp&& object) noexcept {
        using type = std::decay_t<Tp>;
        if constexpr(std::is_scalar_v<type>) {
            return std::make_tuple(object);
        } else if constexpr(is_braces_constructible<type, any_type, any_type, any_type, any_type>{}) {
            auto&& [p1, p2, p3, p4] = object;
            return std::make_tuple(p1, p2, p3, p4);
        } else if constexpr(is_braces_constructible<type, any_type, any_type, any_type>{}) {
            auto&& [p1, p2, p3] = object;
            return std::make_tuple(p1, p2, p3);
        } else if constexpr(is_braces_constructible<type, any_type, any_type>{}) {
            auto&& [p1, p2] = object;
            return std::make_tuple(p1, p2);
        } else if constexpr(is_braces_constructible<type, any_type>{}) {
            auto&& [p1] = object;
            return std::make_tuple(p1);
        } else {
            return std::make_tuple();
        }
    }
};

} //CF