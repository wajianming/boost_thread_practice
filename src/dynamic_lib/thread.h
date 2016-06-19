#ifndef THREAD_H
#define THREAD_H
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

namespace RESOURCE_MONITOR{
/*
class cache_ops{
public:
    int create();
    int read();
    int update();
    int deleteCache();
};
*/


class cache_base{
private:
    std::string _resource_uuid;  //Used to identify the resource.
protected:
    boost::mutex _propertyMutex;    //Used to protect _properties.
public:
    cache_base(std::string resource_uuid);
    virtual ~cache_base();

    const std::string getResourceUUID();

    virtual int updateCacheProperty(std::string key, std::string value)=0;
    virtual int deleteCacheProperty(std::string key)=0;
};

class cache_using_map: public cache_base{
private:
    std::map<std::string, std::string> _properties; // <key, value> pair of the resource.
public:
    cache_using_map(std::string uuid);  
    virtual ~cache_using_map();

    virtual int updateCacheProperty(std::string key, std::string value);
    virtual int deleteCacheProperty(std::string key);
};


class thread_cache_base: public cache_using_map{
private:
    boost::thread* _thread;
public:
    thread_cache_base(std::string resource_uuid);
    virtual ~thread_cache_base();
    
    int access_property();

};

class resource_observer{
private:
    std::map<std::string, cache_base*> _caches;
    boost::thread* _observer_thread;

    boost::thread* _t1;
    boost::thread* _t2;

public:
    resource_observer();
    virtual ~resource_observer();

    int force_contention();
    
    int refresh_resource();    
};


}
#endif
