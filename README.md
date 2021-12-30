### Clocker
#### A useful time calculator!
this app is created by me for my own usage. but you also if have any need or was useful, can use it.

this a useful time calculator. this app calculate your on-work time and get a simple report of your time spend.
this can be used for everyone who wants to know how many time spends on his work, parents for controlling their child PC time usage and employees who wants to report true time of their work and others.

***but stop and NOTE: this is a pre-release, unstable and uncompleted version of this app!*** <br />
but I try to complete it because of my self usage!

#### How it is works?
it simply tracks your mouse and keyboard usage on your system by reading `/dev/input/by_path` input files.
when they become idel for 2 min, the app consider your time as "waste time" and as you come back it will continue normally.

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
