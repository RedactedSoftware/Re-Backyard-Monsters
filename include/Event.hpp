#pragma once

namespace ReBackyardMonsters
{
	class IEventCallback
    {
    public:
        virtual void operator() () = 0;
        virtual bool operator == (IEventCallback* other) = 0;
    };

    template<typename T>
    class EventCallback : public IEventCallback
    {
    public:
        EventCallback(T* instance, void(T::*function)()) : instance(instance), function(function)    
        virtual void operator() () override {(instance->*function)();}
    private:
        void (T::*function)();
        T* instance;
    };   

    class EventSignal
    {
    public:
        EventSignal();
        ~EventSignal();

        void Connect(IEventCallback* action);
        void Disconnect(IEventCallback* action);
        void Invoke();
    private:
        typedef std::vector<IEventCallback*> CallbackList;
        CallbackList callbacks;
    };

    EventSignal::EventSignal() {}
    EventSignal::~EventSignal() {}

    void EventSignal::Connect(IEventCallback* action)
    {
        CallbackList::iterator position = std::find(callbacks.begin(), callbacks.end(), action);

        if (position != callbacks.end())
        {
            std::cerr << "Action existed in delegate list." << std::endl;
            return;
        }
        callbacks.push_back(action);
    }

    void EventSignal::Disconnect(IEventCallback* action)
    {
        CallbackList::iterator position = std::find(callbacks.begin(), callbacks.end(), action);

        if (position == callbacks.end()) {
            return;
        }

        callbacks.erase(position);
    }

    void EventSignal::Invoke()
    {
        for (IEventCallback* action : callbacks) {
            (*action)();
        }
    }
}
