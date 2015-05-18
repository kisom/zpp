CPPFLAGS =	-std=c++14 -stdlib=libstdc++ -g
LDFLAGS =	-lzmq -lstdc++
TARGETS =	hwserver hwclient echo_server	\
		wuserver wuclient		\
		taskvent taskwork tasksink	\
		mspoller			\
		rrclient rrbroker rrworker	\
		taskwork2 tasksink2		\
		mtserver mtrelay		\
		syncpub syncsub			\
		psenvpub psenvsub

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

mspoller: mspoller.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

rrclient: rrclient.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

rrworker: rrworker.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

rrbroker: rrbroker.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

taskwork2: taskwork2.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

tasksink2: tasksink2.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) 

mtserver: mtserver.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

mtrelay: mtrelay.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

syncpub: syncpub.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

syncsub: syncsub.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

psenvpub: psenvpub.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

psenvsub: psenvsub.cc
	clang -o $@ $(CPPFLAGS) $< $(LDFLAGS) -lpthread

.PHONY: clean
clean:
	rm -f $(TARGETS) 
