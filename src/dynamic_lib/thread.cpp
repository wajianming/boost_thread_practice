#include "thread.h"
#include <iostream>
#include <stdio.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>


using namespace std;
namespace RESOURCE_MONITOR{
cache_base::cache_base(string uuid){
    _resource_uuid = uuid;
}

cache_base::~cache_base(){

}

const string cache_base::getResourceUUID(){
    return _resource_uuid;
}

cache_using_map::cache_using_map(string uuid)
:cache_base(uuid)
{

}

cache_using_map::~cache_using_map(){

}

int cache_using_map::updateCacheProperty(std::string key, std::string value){
    boost::mutex::scoped_lock lock(_propertyMutex);
    map<string, string>::iterator it;
    it = _properties.find(key);
    if (it != _properties.end()){
        it->second = value;
    }else{
        _properties.insert(pair<string, string>(key, value));
    }
    return 0;
}

int cache_using_map::deleteCacheProperty(std::string key){
    boost::mutex::scoped_lock lock(_propertyMutex);
    map<string, string>::iterator it;
    it = _properties.find(key);
    if (it != _properties.end()){
        _properties.erase(it);
    }
    return 0;
}

thread_cache_base::thread_cache_base(string resource_uuid)
:cache_using_map(resource_uuid)
{
    _thread = new boost::thread(boost::bind(&thread_cache_base::access_property, this));
}

thread_cache_base::~thread_cache_base(){
    _thread->interrupt();
    _thread->join();
}

int thread_cache_base::access_property(){
    while(true){
        try{
                boost::mutex::scoped_lock lock(_propertyMutex);
                boost::this_thread::sleep(boost::posix_time::milliseconds(10)); 
        }
        catch(boost::thread_interrupted& interruption){
            cout << __FUNCTION__ << ": " << getResourceUUID() << " interruptted" << endl;
            return -1;
        }
        catch(std::exception& e)
        {
            cout << __FUNCTION__ << ": exception" << endl;
            return -1;
        }
    }
    return 0;
}

resource_observer::resource_observer(){
    _observer_thread = new boost::thread(boost::bind(&resource_observer::refresh_resource, this));


    _t1 = new boost::thread(boost::bind(&resource_observer::force_contention, this));
    _t2 = new boost::thread(boost::bind(&resource_observer::force_contention, this));
}

resource_observer::~resource_observer(){
    cout << "~resource_observer" << endl;
    while (! _caches.empty()){
        std::map<string, cache_base*>::iterator it = _caches.begin();
        cache_base* cache = it->second;
        delete cache;   
        _caches.erase(it);
    }
    _observer_thread->interrupt();
    _observer_thread->join();
    _t1->interrupt();
    _t1->join();
    _t2->interrupt();
    _t2->join();
    //delete _observer_thread;
    
}

int resource_observer::force_contention(){
    try
    {
        while (true){
            map<string, cache_base*>::iterator it;
            it = _caches.find("1");
            if (it != _caches.end()){
                it->second->updateCacheProperty("test", "test2");
            }
            boost::this_thread::sleep(boost::posix_time::milliseconds(10)); 
        }
    }
    catch (boost::thread_interrupted& interruption)
    {
        cout << __FUNCTION__ << ": get interrupt" << endl;
    }
    catch (boost::exception& e)
    {
        cout << __FUNCTION__ << ": get exception" << endl;
    }
}

int resource_observer::refresh_resource(){
    unsigned int i = 0;
    char uuid[30];

    try{
        unsigned int i = 0;
        while (true){
            if (i > 1000){
                while (true){
                    boost::this_thread::sleep(boost::posix_time::seconds(1)); 
                }
            }
            i++;
            snprintf(uuid, 30, "%d", i);

            //Validated if the record has cached.
            std::map<string, cache_base*>::iterator it;
            it = _caches.find(uuid);
            if (it!=_caches.end()){
                //Has the record. We may need to validate the content.
                cout << "Record has cached." << endl;
                delete it->second;
                _caches.erase(it);
            }

            //Added the refreshed record.
            thread_cache_base* cache= new thread_cache_base(uuid);
            cache->updateCacheProperty(uuid, "test");
            _caches.insert(pair<string, cache_base*>(uuid, cache));
            i++;
        }
    }
    catch (boost::thread_interrupted& interruption)
    {
        cout << __FUNCTION__ << ": interrupt" << endl;

    }
    catch(std::exception& e)
    {
        cout << __FUNCTION__ << ": general exception" << endl;
    }
}
}
