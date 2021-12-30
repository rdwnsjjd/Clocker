# Copyright (C) 2021 rdwn
# 
# This file is part of Clocker.
# 
# Clocker is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Clocker is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Clocker.  If not, see <http://www.gnu.org/licenses/>.

current = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

component := ${current}/src/components/listener.c
component += ${current}/src/components/mutexed.c
component += ${current}/src/components/time_handler.c
component += ${current}/src/components/timer.c
component += ${current}/src/components/update_checker.c
component += ${current}/src/components/sig_handler.c
component += ${current}/src/components/cmd.c

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
