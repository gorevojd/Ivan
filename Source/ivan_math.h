#ifndef IVAN_MATH_H
#define IVAN_MATH_H

#include <math.h>

#ifndef IVAN_MATH_LERP
#define IVAN_MATH_LERP(a, b, t) ((a) + ((b) - (a)) * (t))
#endif

#ifndef IVAN_MATH_MIN
#define IVAN_MATH_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef IVAN_MATH_MAX
#define IVAN_MATH_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef IVAN_MATH_ABS
#define IVAN_MATH_ABS(value) ((value) >= 0 ? (value) : -(value))
#endif

#ifndef IVAN_MATH_SIGN
#define IVAN_MATH_SIGN(value) (((value) >= 0) ? (1) : -(1))
#endif

#ifndef IVAN_MATH_CLAMP
#define IVAN_MATH_CLAMP(value, lower, upper) (IVAN_MATH_MIN(IVAN_MATH_MAX(value, lower), upper))
#endif

#ifndef IVAN_MATH_CLAMP01
#define IVAN_MATH_CLAMP01(value) (IVAN_MATH_CLAMP(value, 0, 1))
#endif

union vec2{
	struct{
		float x, y;
	};
	float data[2];
};

union vec3{
    struct{
        float x, y, z;
    };
    struct{
        float r, g, b;
    };
    vec2 xy;
    float data[3];
};

union vec4{
    struct{ float x, y, z, w;};
    struct{ vec3 xyz; float w; };
    struct{
        union{
            vec3 rgb;
            struct{
                float r, g, b;
            };
        };
        float a; 
    };
    struct{ vec2 xy; vec2 zw; };
    float data[4];
};

struct quat{
	union{
		struct {
			float x, y, z, w;
		};
		vec3 xyz;
		vec4 xyzw;
	};
};

struct rectangle2{
	vec2 Min;
	vec2 Max;
};

struct rectangle2i{
	int32 MinX, MinY;
	int32 MaxX, MaxY;
};

struct rectangle3{
	vec3 Min;
	vec3 Max;
};

#ifndef IVAN_MATH_CONSTANTS
#define IVAN_MATH_EPSILON 1.19209290e-7f
#define IVAN_MATH_ZERO 0.0f
#define IVAN_MATH_ONE 1.0f
#define IVAN_MATH_TWO_THIRDS 0.666666666666666666666666666666666666667f

#define IVAN_MATH_TAU 6.28318530717958647692528676655900576f
#define IVAN_MATH_PI 3.14159265358979323846264338327950288f
#define IVAN_MATH_ONE_OVER_TAU 0.636619772367581343075535053490057448f
#define IVAN_MATH_ONE_OVER_PI 0.318309886183790671537767526745028724f

#define IVAN_MATH_TAU_OVER_2 3.14159265358979323846264338327950288f
#define IVAN_MATH_TAU_OVER_4 1.570796326794896619231321691639751442f
#define IVAN_MATH_TAU_OVER_8 0.785398163397448309615660845819875721f

#define IVAN_MATH_E 2.71828182845904523536f
#define IVAN_MATH_SQRT_TWO 1.41421356237309504880168872420969808f
#define IVAN_MATH_SQRT_THREE 1.73205080756887729352744634150587236f
#define IVAN_MATH_SQRT_FIVE 2.23606797749978969640917366873127623f

#define IVAN_MATH_LOG_TWO 0.693147180559945309417232121458176568f
#define IVAN_MATH_LOG_TEN 2.30258509299404568401799145468436421f

#define IVAN_DEG_TO_RAD 0.0174533
#define IVAN_RAD_TO_DEG 57.2958

#define IVAN_MATH_CONSTANTS
#endif

/*Simple operations*/
inline float Sqrt(float Value){
	float Result;
	Result = sqrtf(Value);
	return(Result);
}

inline float RSqrt(float Value){
	float Result;
	Result = 1.0f / sqrtf(Value);
	return(Result);
}

inline float Sin(float Rad){
	float Result = sinf(Rad);
	return(Result);
}

inline float Cos(float Rad){
	float Result = cosf(Rad);
	return(Result);
}

inline float Tan(float Rad){
	float Result = tanf(Rad);
	return(Result);
}

inline float ASin(float Value){
	float Result = asinf(Value);
	return(Result);
}

inline float ACos(float Value){
	float Result = acosf(Value);
	return(Result);
}

inline float ATan(float Value){
	float Result = atan(Value);
	return(Result);
}

inline float ATan2(float Y, float X){
	float Result = atan2f(Y, X);
	return(Result);
}

inline float Exp(float Value){
	float Result = expf(Value);
	return(Result);
}

inline float Log(float Value){
	float Result = logf(Value);
	return(Result);
}

inline float Pow(float a, float b){
	float Result = powf(a, b);
	return(Result);
}

/*vec2 constructors*/
inline vec2 Vec2(float Value){
	vec2 Result;
	Result.x = Value;
	Result.y = Value;
	return(Result);
}

inline vec2 Vec2(float x, float y){
	vec2 Result;
	Result.x = x;
	Result.y = y;
	return(Result);
}

/*vec3 constructors*/
inline vec3 Vec3(float Value){
	vec3 Result;
	Result.x = Value;
	Result.y = Value;
	Result.z = Value;
	return(Result);
}

inline vec3 Vec3(float x, float y, float z){
	vec3 Result;
	Result.x = x;
	Result.y = y;
	Result.z = z;
	return(Result);
}

inline vec3 Vec3(vec2 InitVector, float z){
	vec3 Result;
	Result.x = InitVector.x;
	Result.y = InitVector.y;
	Result.z = z;
	return(Result);
}

/*vec4 constructors*/
inline vec4 Vec4(float Value){
	vec4 Result;
	Result.x = Value;
	Result.y = Value;
	Result.z = Value;
	Result.w = Value;
	return(Result);
}

inline vec4 Vec4(float x, float y, float z, float w){
	vec4 Result;
	Result.x = x;
	Result.y = y;
	Result.z = z;
	Result.w = w;
	return(Result);
}

inline vec4 Vec4(vec3 InitVector, float w){
	vec4 Result;
	Result.x = InitVector.x;
	Result.y = InitVector.y;
	Result.z = InitVector.z;
	Result.w = w;
	return(Result);
}

/*Quaternion constructors and operations*/
inline quat Quat(vec3 axis, float theta){
	quat Result;

	float HalfTheta = theta * 0.5f;
	float SinScalar = Sin(HalfTheta);
	float OneOverAxisLen = 1.0f / Sqrt((axis.x * axis.x + axis.y * axis.y + axis.z * axis.z));
	Result.x = OneOverAxisLen * axis.x * SinScalar;
	Result.y = OneOverAxisLen * axis.y * SinScalar;
	Result.z = OneOverAxisLen * axis.z * SinScalar;
	Result.w = Cos(HalfTheta);

	return(Result);
}

inline quat Quat(float x, float y, float z, float theta){
	quat Result;

	float HalfTheta = theta * 0.5f;
	float SinScalar = Sin(HalfTheta);
	float OneOverAxisLen = 1.0f / Sqrt((x * x + y * y + z * z));
	Result.x = x * OneOverAxisLen * SinScalar;
	Result.y = y * OneOverAxisLen * SinScalar;
	Result.z = z * OneOverAxisLen * SinScalar;
	Result.w = Cos(HalfTheta);

	return(Result);
}

inline quat Mul(quat q1, quat q2){
    quat q;
    q.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    q.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    q.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    return(q);
}

inline quat Quat(float Yaw, float Pitch, float Roll){
	quat q1 = Quat(1.0f, 0.0f, 0.0f, Pitch);
	quat q2 = Quat(0.0f, 1.0f, 0.0f, Yaw);
	quat q3 = Quat(0.0f, 0.0f, 1.0f, Roll);

	quat Result = Mul(q2, q1);
	Result = Mul(Result, q3);
	return(Result);
}

inline quat QuatIdentity(){
	quat Result;

	Result.x = 0.0f;
	Result.y = 0.0f;
	Result.z = 0.0f;
	Result.w = 1.0f;

	return(Result);
}

inline quat Conjugate(quat q){
	quat Result;

	Result.x = -q.x;
	Result.y = -q.y;
	Result.z = -q.z;
	Result.w = q.w;

	return(Result);
}

inline float Dot(quat q1, quat q2){
	float Result = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

	return(Result);
}

inline quat Div(quat q, float s){
	quat Result;
	float OneOverS = 1.0f / s;
	Result.x = q.x * OneOverS;
	Result.y = q.y * OneOverS;
	Result.z = q.z * OneOverS;
	Result.w = q.w * OneOverS;

	return(Result);
}

inline quat Inverse(quat q){
	quat Result;

	Result = Conjugate(q);
	Result = Div(Result, Dot(q, q));

	return(Result);
}

/*Add operation*/
inline vec2 Add(vec2 a, vec2 b){
	a.x += b.x;
	a.y += b.y;
	return(a);
}

inline vec3 Add(vec3 a, vec3 b){
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return(a);
}

inline vec4 Add(vec4 a, vec4 b){
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	a.w += b.w;
	return(a);
}

/*Subtract operation*/
inline vec2 Sub(vec2 a, vec2 b){
	a.x -= b.x;
	a.y -= b.y;
	return(a);
}

inline vec3 Sub(vec3 a, vec3 b){
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return(a);
}

inline vec4 Sub(vec4 a, vec4 b){
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	a.w -= b.w;
	return(a);
}

/*Multiply operation*/
inline vec2 Mul(vec2 a, float s){
	a.x *= s;
	a.y *= s;
	return(a);
}

inline vec3 Mul(vec3 a, float s){
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return(a);
}

inline vec4 Mul(vec4 a, float s){
	a.x *= s;
	a.y *= s;
	a.z *= s;
	a.w *= s;
	return(a);
}

/*Divide operation*/
inline vec2 Div(vec2 a, float s){
	a.x /= s;
	a.y /= s;
	return(a);
}

inline vec3 Div(vec3 a, float s){
	a.x /= s;
	a.y /= s;
	a.z /= s;
	return(a);
}

inline vec4 Div(vec4 a, float s){
	a.x /= s;
	a.y /= s;
	a.z /= s;
	a.w /= s;
	return(a);
}

/*vec2 operator overloading*/
inline bool operator==(vec2 a, vec2 b) { return((a.x == b.x) && (a.y == b.y)); }
inline bool operator!=(vec2 a, vec2 b){ return((a.x != b.x) || (a.y != b.y)); }

inline vec2 operator+(vec2 a){ return(a); }
inline vec2 operator-(vec2 a){ vec2 r = { -a.x, -a.y }; return(r); }

inline vec2 operator+(vec2 a, vec2 b){ return Add(a, b); }
inline vec2 operator-(vec2 a, vec2 b){ return Sub(a, b); }

inline vec2 operator*(vec2 a, float s){ return Mul(a, s); }
inline vec2 operator*(float s, vec2 a){ return Mul(a, s); }
inline vec2 operator/(vec2 a, float s){ return Div(a, s); }

inline vec2 operator*(vec2 a, vec2 b){vec2 r = {a.x * b.x, a.y * b.y}; return(r);}
inline vec2 operator/(vec2 a, vec2 b){vec2 r = {a.x / b.x, a.y / b.y}; return(r);}

inline vec2 &operator+=(vec2& a, vec2 b){return(a = a + b);}
inline vec2 &operator-=(vec2& a, vec2 b){return(a = a - b);}
inline vec2 &operator*=(vec2& a, float s){return(a = a * s);}
inline vec2 &operator/=(vec2& a, float s){return(a = a / s);}

/*vec3 operator overloading*/
inline bool operator==(vec3 a, vec3 b){return((a.x == b.x) && (a.y == b.y) && (a.z == b.z));}
inline bool operator!=(vec3 a, vec3 b){return((a.x != b.x) || (a.y != b.y) || (a.z != b.z));}

inline vec3 operator+(vec3 a){return(a);}
inline vec3 operator-(vec3 a){vec3 r = {-a.x, -a.y, -a.z}; return(r);}

inline vec3 operator+(vec3 a, vec3 b){ return Add(a, b); }
inline vec3 operator-(vec3 a, vec3 b){ return Sub(a, b); }

inline vec3 operator*(vec3 a, float s){ return Mul(a, s); }
inline vec3 operator*(float s, vec3 a){ return Mul(a, s); }
inline vec3 operator/(vec3 a, float s){ return Div(a, s); }

inline vec3 operator*(vec3 a, vec3 b){vec3 r = {a.x * b.x, a.y * b.y, a.z * b.z}; return(r);}
inline vec3 operator/(vec3 a, vec3 b){vec3 r = {a.x / b.x, a.y / b.y, a.z / b.z}; return(r);}

inline vec3 &operator+=(vec3& a, vec3 b){return(a = a + b);}
inline vec3 &operator-=(vec3& a, vec3 b){return(a = a - b);}
inline vec3 &operator*=(vec3& a, float s){return(a = a * s);}
inline vec3 &operator/=(vec3& a, float s){return(a = a / s);}

/*vec4 operator overloading*/
inline bool operator==(vec4 a, vec4 b) { return((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w)); }
inline bool operator!=(vec4 a, vec4 b){ return((a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w)); }

inline vec4 operator+(vec4 a){ return(a); }
inline vec4 operator-(vec4 a){ vec4 r = { -a.x, -a.y }; return(r); }

inline vec4 operator+(vec4 a, vec4 b){ return Add(a, b); }
inline vec4 operator-(vec4 a, vec4 b){ return Sub(a, b); }

inline vec4 operator*(vec4 a, float s){ return Mul(a, s); }
inline vec4 operator*(float s, vec4 a){ return Mul(a, s); }
inline vec4 operator/(vec4 a, float s){ return Div(a, s); }

inline vec4 operator*(vec4 a, vec4 b){vec4 r = {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}; return(r);}
inline vec4 operator/(vec4 a, vec4 b){vec4 r = {a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w}; return(r);}

inline vec4 &operator+=(vec4& a, vec4 b){return(a = a + b);}
inline vec4 &operator-=(vec4& a, vec4 b){return(a = a - b);}
inline vec4 &operator*=(vec4& a, float s){return(a = a * s);}
inline vec4 &operator/=(vec4& a, float s){return(a = a / s);}

/*Dot product*/
inline float Dot(vec2 v0, vec2 v1){ return v0.x * v1.x + v0.y * v1.y; }
inline float Dot(vec3 v0, vec3 v1){ return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; }
inline float Dot(vec4 v0, vec4 v1){ return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w; }

/*Cross product*/
inline float Cross(vec2 v0, vec2 v1){ return v0.x * v1.y - v1.x * v0.y; }
inline vec3 Cross(vec3 v0, vec3 v1){
    vec3 v;
    v.x = v0.y * v1.z - v1.y * v0.z;
    v.y = v0.z * v1.x - v1.z * v0.x;
    v.z = v0.x * v1.y - v1.x * v0.y;
    return(v);
}

/*Hadamard product*/
inline vec2 Hadamard(vec2 v0, vec2 v1){ return (Vec2(v0.x * v1.x, v0.y * v1.y));}
inline vec3 Hadamard(vec3 v0, vec3 v1){ return (Vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z));}
inline vec4 Hadamard(vec4 v0, vec4 v1){ return (Vec4(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w));}

/*Magnitude of the vector*/
inline float Magnitude(vec2 v){ return(Sqrt(Dot(v, v)));}
inline float Magnitude(vec3 v){ return(Sqrt(Dot(v, v)));}
inline float Magnitude(vec4 v){ return(Sqrt(Dot(v, v)));}

/*Squared magnitude*/
inline float SqMagnitude(vec2 v){ return(Dot(v, v)); }
inline float SqMagnitude(vec3 v){ return(Dot(v, v)); }
inline float SqMagnitude(vec4 v){ return(Dot(v, v)); }

/*Normalization of the vector*/
inline vec2 Normalize(vec2 v){ return(Mul(v, RSqrt(Dot(v, v)))); }
inline vec3 Normalize(vec3 v){ return(Mul(v, RSqrt(Dot(v, v)))); }
inline vec4 Normalize(vec4 v){ return(Mul(v, RSqrt(Dot(v, v)))); }

inline vec2 Normalize0(vec2 v){ float sqmag = Dot(v, v); return((sqmag) == 0.0f ? Vec2(0.0f) : v * RSqrt(sqmag)); }
inline vec3 Normalize0(vec3 v){ float sqmag = Dot(v, v); return((sqmag) == 0.0f ? Vec3(0.0f) : v * RSqrt(sqmag)); }
inline vec4 Normalize0(vec4 v){ float sqmag = Dot(v, v); return((sqmag) == 0.0f ? Vec4(0.0f) : v * RSqrt(sqmag)); }

/*Reflection of the vector*/
inline vec2 Reflect(vec2 i, vec2 n){return(Sub(i, Mul(n, 2.0f * Dot(n, i))));}
inline vec3 Reflect(vec3 i, vec3 n){return(Sub(i, Mul(n, 2.0f * Dot(n, i))));}

vec2 Refract(vec2 i, vec2 n, float theta){
    vec2 r, a, b;
    float dv, k;
    dv = Dot(n, i);
    k = 1.0f - theta * theta * (1.0f - dv * dv);
    a = Mul(i, theta);
    b = Mul(n, theta * dv * Sqrt(k));
    r = Sub(a, b);
    r = Mul(r, (float)(k >= 0.0f));
    return(r);
}

vec3 Refract(vec3 i, vec3 n, float theta){
    vec3 r, a, b;
    float dv, k;
    dv = Dot(n, i);
    k = 1.0f - theta * theta * (1.0f - dv * dv);
    a = Mul(i, theta);
    b = Mul(n, theta * dv * Sqrt(k));
    r = Sub(a, b);
    r = Mul(r, (float)(k >= 0.0f));
    return(r);
}

float AspectRatio(vec2 v){ return ((v.y < 0.0001f) ? 0.0f : v.x / v.y); }

/*Interpolations*/

float Lerp(float a, float b, float t){
	float Result = a * (1.0f - t) + b * t;
	return(Result);
}

#define IVAN_VECTOR_LERP(N, a, b, t)	\
	vec##N Res = Sub(b, a);				\
	Res = Mul(Res, t);					\
	Res = Add(Res, a);					\
	return(Res);

inline vec2 Lerp(vec2 a, vec2 b, float delta){ IVAN_VECTOR_LERP(2, a, b, delta); }
inline vec3 Lerp(vec3 a, vec3 b, float delta){ IVAN_VECTOR_LERP(3, a, b, delta); }
inline vec4 Lerp(vec4 a, vec4 b, float delta){ IVAN_VECTOR_LERP(4, a, b, delta); }
#undef IVAN_VECTOR_LERP


/*Rectangle Functions*/
inline int32
GetWidth(rectangle2i A){
	int32 Result = A.MaxX - A.MinX;
	return(Result);
}

inline int32 
GetHeight(rectangle2i A){
	int32 Result = A.MaxY - A.MinY;
	return(Result);
}

inline int32 
GetClampedRectArea(rectangle2 A){
	float Width = (A.Max.x - A.Min.x);
	float Height = (A.Max.y - A.Min.y);

	float Result = 0.0f;
	if((Width > 0) && (Height > 0)){
		Result = Width * Height;
	}

	return(Result);
}

#endif