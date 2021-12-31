<!--
 Copyright (C) 2021 rdwn
 
 This file is part of Clocker.
 
 Clocker is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Clocker is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Clocker.  If not, see <http://www.gnu.org/licenses/>.
-->

### Clocker
#### A useful time calculator!
this app is created by me for my own usage. but you also if have any need or was useful, can use it.

this a useful time calculator. this app calculate your on-work time and get a simple report of your time spend.
this can be used for everyone who wants to know how many time spends on his work, parents for controlling their child PC time usage and employees who wants to report true time of their work and others.

***but stop and NOTE: this is a pre-release, unstable and uncompleted version of this app!*** <br />
but I try to complete it because of my self usage!

#### How it works?
it simply tracks your mouse and keyboard usage on your system by reading `/dev/input/by_path` input files.
when they become idle for 2 min, the app consider your time as "waste time" and as you come back it will continue normally.

#### How to use it?
You can directly use `/build/clocker` binary file by copying it to `/bin` system directory.
or make source easily by run `make build && make install` in the root directory of project.
it will copy `clocker` to `/bin` and clocker updater to `/root/.clocker`.
for run clocker run:
```
$ sudo clocker
```

for updating application run:
```
$ sudo clocker --update
```
