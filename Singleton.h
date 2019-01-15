#ifndef SINGLETONTPL_H
#define SINGLETONTPL_H

template <class T> class Singleton {
    public:
        static T* get() noexcept {
            if (instance == NULL) {
                instance = new T();
            }
            return instance;
        }

    protected:
        static T* instance;
};

template <class T> T* Singleton<T>::instance = NULL;

#endif