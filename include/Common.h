#ifndef TINYNET_COMMON_H
#define TINYNET_COMMON_H

#ifdef _MSC_VER
#define TN_API __declspec(dllexport)
#else
#define TN_API
#endif

namespace TinyNet
{
    class NonClonable {
    public:
        NonClonable() = default;

    private:
        NonClonable(const NonClonable& rhs) = delete;
        NonClonable(NonClonable&& rhs) = delete;
        NonClonable& operator=(const NonClonable& rhs) = delete;
        NonClonable& operator =(NonClonable&& rhs) = delete;
    };

    template<class T>
    TN_API class SingleTon : public NonClonable
    {
    public:
        static T& getInstance()
        {
            static T instance;
            return instance;
        }
    protected:
        SingleTon() = default;
    };
}

#endif
