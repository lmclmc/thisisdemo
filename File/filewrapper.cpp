#include "filewrapper.h"
#include "deflection.h"

FileWrapper * FileWrapper::instance = nullptr;
std::mutex FileWrapper::mutex;

FileWrapper::FileWrapper(){

}

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



