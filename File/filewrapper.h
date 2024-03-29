#ifndef FILEWRAPPER_H
#define FILEWRAPPER_H

#include <map>
#include <mutex>
#include <memory>

class F;

typedef enum class DataType_ : unsigned char{
    Deflection,
    Displacement,
    Strain
}DataType;

/**
 * @brief 将文件操作模块封装成单例模式，将各个
 */
class FileWrapper
{
public:
    typedef std::map<DataType, std::shared_ptr<F>> FileMap;        //不同传感器
    static FileWrapper *getInstance();
    void attach(std::shared_ptr<F> f, DataType d);
    inline FileMap &getFileMap(){
        return fileMap;
    }

private:
    FileWrapper();

    FileMap fileMap;

private:
    static std::mutex mutex;
    static FileWrapper *instance;
};

#endif // FILEWRAPPER_H
