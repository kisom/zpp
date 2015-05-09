CPPFLAGS =	-std=c++14 -stdlib=libstdc++
LDFLAGS =	-lzmq -lstdc++
TARGETS =	hwserver hwclient echo_server	\
		wuserver wuclient		\
		taskvent taskwork tasksink

# def target(name):
#     print """%s: %s.cc
# \tclang -o $@ $(CPPFLAGS) $< $(LDFLAGS)    
# """ % (name, name)

all: $(TARGETS)

hwserver: hwserver.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

hwclient: hwclient.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

echo_server: echo_server.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

wuserver: wuserver.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

wuclient: wuclient.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS)

taskvent: taskvent.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

taskwork: taskwork.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

tasksink: tasksink.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

.PHONY: clean
clean:
	rm -f $(TARGETS) 
