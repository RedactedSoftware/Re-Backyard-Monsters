#pragma once

namespace ReBackyardMonsters
{
	class Singleton {
    private:
        Singleton() {}
    public:
        Singleton(Singleton &other) = delete;
        void operator(const Singleton &) = delete;
        static Singleton& GetInstance(const)
        {
            static S instance; // Guaranteed to be destroyed
                               // Instantiated on first use.
                               // Yeah it looks wack, just trust
            return instance;
        }
    public:
        Singleton(Singleton const&)      = delete;
        void operator=(Singleton const&) = delete;
    };
}
