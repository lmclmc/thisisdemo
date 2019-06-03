#include "filewrapper.h"
#include "deflection.h"

FileWrapper * FileWrapper::instance = nullptr;
std::mutex FileWrapper::mutex;

FileWrapper::FileWrapper(){

}

/**
 * @brief 该单例模式支持高效率的线程安全，但不包括写数据
 * @return  返回一个单例指针
 */
FileWrapper *FileWrapper::getInstance()
{
    if (nullptr == instance){
        mutex.lock();
        if (nullptr == instance){
            instance = new FileWrapper();
        }
        mutex.unlock();
    }

    return instance;
}

void FileWrapper::attach(F *f, DataType d)
{
    f->init();
    fileMap.insert(std::pair<DataType, F *>(d, f));
}



