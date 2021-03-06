#pragma once

template <typename T>
class Singleton
{
public:
    static void CreateInstance()
    {
        ASSERT(m_singletonInstance == nullptr);
        m_singletonInstance = new T;
    }
    static T* GetInstance()
    {
        ASSERT(m_singletonInstance);
        return m_singletonInstance;
    }
    static void DeleteInstance()
    {
        delete m_singletonInstance;
        m_singletonInstance = nullptr;
    }

protected:
    static T* m_singletonInstance;
};

template<typename T>
T* Singleton<T>::m_singletonInstance = nullptr;
