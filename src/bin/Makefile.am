bin_PROGRAMS=helloworld
helloworld_SOURCES=main.cpp
helloworld_CPPFLAGS = -I$(top_srcdir)/includes -I../dynamic_lib ## add path to headerfiles
helloworld_LDADD=$(top_srcdir)/src/dynamic_lib/libCacheManagement.la  ## link with static library
#helloworld_LDADD+= -dlopen $(top_srcdir)/src/module/libHelloModule.la
helloworld_LDFLAGS=-lboost_thread -lboost_system
