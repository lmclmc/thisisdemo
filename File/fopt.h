#ifndef FOPT_H
#define FOPT_H

#include <list>
#include <iostream>
#include <map>

typedef struct {
    long long year;
    long long month;
    long long day;
    long long hour;
    long long min;
    long long sec;
}fTime;

typedef struct TT_{
    /**
     * @brief 为了便于排序才重载 < > 操作符
     * @param 需要比较的参数
     * @return 比较是否大于或者小于需要比较的参数
     */
    bool operator < (struct TT_ &tT){
        timeStamp = t.year*31104000+t.month*2592000+t.day*86400+
                t.hour*3600+t.min*60+t.sec;
        tT.timeStamp = tT.t.year*31104000+tT.t.month*2592000+tT.t.day*86400+
                tT.t.hour*3600+tT.t.min*60+tT.t.sec;
        return timeStamp < tT.timeStamp;
    }

    bool operator > (struct TT_ &tT){
        timeStamp = t.year*31104000+t.month*2592000+t.day*86400+
                t.hour*3600+t.min*60+t.sec;
        tT.timeStamp = tT.t.year*31104000+tT.t.month*2592000+tT.t.day*86400+
                tT.t.hour*3600+tT.t.min*60+tT.t.sec;
        return timeStamp > tT.timeStamp;
    }

    char unit[10];
    int id;
    double value;
    long long timeStamp;
    fTime t;
}TT;

class F{
public:
    F() = default;

    /**
     * @brief 初始化，主要以读取目标文件为主
     */
    void init();

    /**
     * @brief 刷新，将内存数据重新刷到磁盘中
     */
    void flush();

    /**
     * @brief 获取文件名称，该文件名由子类提供
     * @return
     */
    virtual std::string getFileName();

    /**
     * @brief 读取文件的时候，会触发该读文件事件
     * @param 每读一行数据，将会以字符串的形式传入参数
     */
    virtual void readFileEvent(std::string &str);

    /**
     * @brief 写文件事件，
     * @param 将字符串数据写到文件里
     * @return
     */
    virtual bool writeFileEvent(std::string &str);

    /**
     * @brief 从字符串截取第一个子字符串，并且转化为时间
     * @param 源字符串
     * @return 将时间返回出来
     */
    fTime getDate(std::string &str);

    /**
     * @brief 从字符串中截取第一个子字符串，并且转化为整型数字
     * @param 源字符串
     * @return 将整型数字返回出来
     */
    int getInt(std::string &str);

    /**
     * @brief 从字符串中截取第一个子字符串，并且转化为双精度数字
     * @param 源字符串
     * @return 将双精度数字返回出来
     */
    double getDouble(std::string &str);

    /**
     * @brief 从字符串中截取第一个子字符串
     * @param 源字符串
     * @return 将字符串返回出来
     */
    std::string getStr(std::string &str);
};

class FOpt : public F
{
public:
    typedef std::map<int, std::list<TT>> TMap;
    typedef std::list<TT> TList;

    FOpt() = default;

    TMap &getData(){
        return data;
    }

    /**
     * @brief 获取指定传感器链表的迭代器
     * @param 设置传感器编号
     * @param 获取数据节点的迭代器
     * @return 如果有数据节点 返回true 否则返回false
     */
    bool getNodeIter(int Id, TList::iterator &iter);

    /**
     * @brief 操作迭代器，并获取迭代器
     * @param 设置传感器编号
     * @param 设置操作方式，1：++ 0:--
     * @param 获取迭代器
     * @return 设置成功返回true 失败返回false
     */
    bool setNodeIter(int Id, int set, TList::iterator &iter);

    /**
     * @brief 将新节点加入到数据容器里
     * @param 新节点
     */
    void pushBack(TT node);

private:
    /**
     * @brief 传感器中的数据，int为某种传感器编号，std::list<TT>为某种传感器中，按
     * 时间排序的数据链表
     */
    std::map<int, std::list<TT>> data;
};
#endif // FOPT_H
