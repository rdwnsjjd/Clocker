component := src/components/listener.c
component += src/components/mutexed.c
component += src/components/time_handler.c
component += src/components/timer.c
component += src/components/update_checker.c

clocker := src/clocker.c
updater := src/updater.c

buildClocker := build/clocker
buildUpdater := build/updater

build: 
	@mkdir -p build
	@gcc -w -g ${component} ${clocker} -o ${buildClocker}
	@gcc -w -g ${updater} src/components/update_checker.c -o ${buildUpdater}

install: 
	@mkdir -p /root/.clocker
	@gcc -w -g ${component} ${clocker} -o /bin/clocker
	@gcc -w -g ${updater} src/components/update_checker.c -o /root/.clocker/clocker-updater

run:
	@sudo ./${buildClocker}