current = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

component := ${current}/src/components/listener.c
component += ${current}/src/components/mutexed.c
component += ${current}/src/components/time_handler.c
component += ${current}/src/components/timer.c
component += ${current}/src/components/update_checker.c

clocker := ${current}/src/clocker.c
updater := ${current}/src/updater.c

buildClocker := ${current}/build/clocker
buildUpdater := ${current}/build/updater

all: 
	@mkdir -p ${current}/build
	@gcc -w -g ${component} ${clocker} -o ${buildClocker} -lpthread
	@gcc -w -g ${updater} ${current}/src/components/update_checker.c -o ${buildUpdater} -lpthread

install: 
	@mkdir -p /root/.clocker
	@gcc -w -g ${component} ${clocker} -o /bin/clocker  -lpthread
	@gcc -w -g ${updater} ${current}/src/components/update_checker.c -o /root/.clocker/clocker-updater  -lpthread

run:
	@sudo ${buildClocker}


uninstall:
	@rm -rf /root/.clocker
	@rm /bin/clocker
