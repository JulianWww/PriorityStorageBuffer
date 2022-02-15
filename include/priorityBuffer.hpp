#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include "utils.hpp"


namespace priorityBuffer 
{
    template<typename T>
    class greater
    {
        public: bool operator()(const T& a, const T& b);
    };

    template<typename hashable, typename data>
    class BufferElement
    {
        public: hashable id;
        public: data d;

        BufferElement(hashable id, data d);
    };

    template<typename T, typename QueueType=unsigned int>
    class Buffer 
    {
        typedef unsigned int idType;
        typedef BufferElement<QueueType, idType> E;
        public: idType currentId = 0;
        public: std::priority_queue<E, std::vector<E>, greater<E>> queue;
        public: size_t capacity;
        public: std::string dir;
        public: std::string extension;

        public: Buffer(size_t capacity, std::string dir, std::string extension);
        public: void addElement(QueueType ID, T data);
        public: void removeElement();
        public: void render();
        public: void save(T data, idType id);
        public: std::string getFileName(idType id);
    };
}

template<typename T>
inline bool priorityBuffer::greater<T>::operator()(const T& a, const T& b)
{
    return a.id > b.id;
}

template<typename T, typename T2>
inline priorityBuffer::BufferElement<T, T2>::BufferElement(T id, T2 d)
{
    this->id = id;
    this->d = d;
}

template<typename T1, typename T2>
inline priorityBuffer::Buffer<T1, T2>::Buffer(size_t capacity, std::string dir, std::string extension)
{
    this->capacity = capacity;
    this->dir = dir;
    this->extension = extension;
    std::filesystem::create_directories(dir);
}

template<typename T, typename QueueType>
inline void priorityBuffer::Buffer<T, QueueType>::addElement(QueueType id, T data) 
{
    BufferElement element(id, currentId);
    this->queue.push(element);
    this->save(data, currentId);
    currentId++;

    this->removeElement();
}

template<typename T1, typename T2>
inline void priorityBuffer::Buffer<T1, T2>::removeElement()
{
    if (this->queue.size() > this->capacity)
    {
        idType a = this->queue.top().d;
        std::remove(this->getFileName(a).c_str());
        this->queue.pop();
    }
}

template<typename T, typename hashable>
inline void priorityBuffer::Buffer<T, hashable>::render()
{
   while(!this->queue.empty()) {
        auto a = this->queue.top();
        std::cout << "<" << a.id << ", " << a.d << ">; ";
        this->queue.pop();
    }
    std::cout << '\n';
}

template<typename T, typename T2>
inline void priorityBuffer::Buffer<T, T2>::save(T data, idType file)
{
    std::ofstream ofile;
    ofile.open(this->getFileName(file), std::ios::binary);
    ofile.write((char*)&data, sizeof(data));
    ofile.close();
}

template<typename T, typename T2>
inline std::string priorityBuffer::Buffer<T, T2>::getFileName(idType data)
{
    return this->dir+int_to_hex(data)+"."+this->extension;
}