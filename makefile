component := src/components/listener.c
component += src/components/mutexed.c
component += src/components/time_handler.c
component += src/components/timer.c
component += src/components/updater.c

main := src/main.c
build := build/clocker

all: 
	@mkdir -p build
	@gcc -w -g ${component} ${main} -o ${build}
	@sudo build/clocker