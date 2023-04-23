#include <random>

typedef float float32;
typedef double float64;
typedef long double float128;

namespace ReBackyardMonters
{
    class Math{
    public:
        static float32 Lerp(float32 a, float32 b, float32 t);
        static float64 Lerp(float64 a, float64 b, float64 t);
        static float128 Lerp(float128 a, float128 b, float128 t);
    };
}