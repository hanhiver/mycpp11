template<typename T>
class MutexObject
{
public:
    MutexObject() {}

    template<typename ...Args>
    MutexObject(Args... args) : data(args...) {}

    MutexObject<T> & operator = (const T & data)
    {
        this->data = data;
        return *this;
    }
    MutexObject<T> & operator = (const MutexObject<T> & other)
    {
        this->data = other.data;
        return *this;
    }

    operator T & ()
    {
        return data;
    }
    operator T && ()
    {
        return std::move(data);
    }
    T * operator -> ()
    {
        return &data;
    }
    T * operator & ()
    {
        return operator->();
    }

    std::mutex & Mutex()
    {
        return mu;
    }
    T & Data()
    {
        return data;
    }

private:
    T data;
    std::mutex mu;
};

#define MUTEXOBJECT_LOCK_GUARD(obj) std::lock_guard<std::mutex> lock(obj.Mutex())
#define MUTEXOBJECT_UNIQUE_LOCK(obj) std::unique_lock<std::mutex> lock(obj.Mutex())