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

![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/rdwnsjjd/Clocker?include_prereleases)

![Screenshot from 2021-12-31 23-01-44](https://user-images.githubusercontent.com/84472404/147837215-4aeb1700-677b-4caf-a546-ecedb4abf071.png)


### Clocker
#### A useful time calculator!
This app is created by me for my own usage. but you also if have any need or was useful, can use it.

This is a useful time calculator. this app calculates your on-work time and gives a simple report of your time spent.
this could be used for everyone who wants to know how much time spends on his work, parents for controlling their child PC time usage, and employees who want to report true time of their work and others.

***but stop and NOTE: this is a pre-release, unstable, and uncompleted version of this app!*** <br />
but I try to complete it because of my self-usage!

#### How it works?
It simply tracks your mouse and keyboard usage on your system by reading `/dev/input/by_path` input files.
When they become idle for 2 min, the app considers your time as "waste time" and as you come back it will continue normally.

#### How to use it?
You can directly use the `/build/clocker` binary file by copying it to the `/usr/bin` system directory.
or make source easily by running `make && make install` in the root directory of the project (recommended).
it will copy `clocker` and `clocker-updater` to `/usr/bin`.
for run clocker run:
```
$ sudo clocker
```

for updating application run:
```
$ sudo clocker --update
```


#### Modes
You can use several modes as your need. there are three modes: `busy`, `paused` and `default`.

You are starting in default mode and it is the normal behavior of the app. Clocker will calculate your useful time when you're using your system, and otherwise, going to idle.

When you're choosing `busy` mode, probably you are doing your work, but not just with your system. in other words, you are not using your system while you want to your time be considered useful time.

Unlike that, when you use your system, but not in your main job, you can `pause` the Clocker and do your stuff, and then back and `Resume` it.

#### What will be added
This app created because of need, So whenever the need arises, a new feature will be added. for now I want to add two more features,
- data saver
- data exporter

if you use this app and feel maybe some new features is needed, please create an issue, I welcome any idea or suggestion! 


also If you face any problem, unknown behavior or some other bugs, please open an issue or email me.
rdwnsjjd@gmail.com 
