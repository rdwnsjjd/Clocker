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

component := ${current}/source/listener.c
component += ${current}/source/time_handler.c
component += ${current}/source/timer.c
component += ${current}/source/update_checker.c
component += ${current}/source/sig_handler.c
component += ${current}/source/cmd.c
component += ${current}/source/data_manager.c
component += ${current}/framework/system/thread/guarded.c
component += ${current}/framework/system/thread/thread.c
component += ${current}/framework/system/fs/wrapper.c
component += ${current}/framework/system/memory/boxed.c

updaterComponent := ${current}/source/update_checker.c
updaterComponent += ${current}/framework/system/memory/boxed.c

header := ${current}

clocker := ${current}/deploy/clocker/clocker.c
updater := ${current}/deploy/updater/updater.c

buildClocker := ${current}/final/bin/clocker
buildUpdater := ${current}/final/bin/clocker-updater

all: 
	@mkdir -p ${current}/final/bin/
	@gcc -I${header} -fcompare-debug-second -w -g ${component} ${clocker} -o ${buildClocker} -lpthread
	@gcc -I${header} -fcompare-debug-second -w -g ${updater} ${updaterComponent} -o ${buildUpdater} -lpthread

install: 
	@mkdir -p /root/.config/clocker
	@cp ${buildClocker} /usr/bin
	@cp ${buildUpdater} /usr/bin

run:
	@sudo ${buildClocker}

clean:
	@rm -rf ${current}/final/

uninstall:
	@rm -rf /root/.config/clocker
	@rm /usr/bin/clocker
	@rm /usr/bin/clocker-updater
