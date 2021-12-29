### Clocker
##### A useful time calculator!
this app is created by me for my own usage. but you also if have any need or was useful, can use it.

this a useful time calculator. this app calculate your on-work time and get a simple report of your time spend.
this can be used for everyone who wants to know how many time spends on his work, parents for controlling their child PC time usage and employees who wants to report true time of their work and others.

**but stop and note: this is a pre-release, unstable and uncompleted version of this app!** <br />
but I try to complete it because of my self usage!

#### How it is works?
it simply tracks your mouse and keyboard usage on your system by reading `/dev/input/by_path` input files.
when they become idel for 2min, the app consider your time as "waste time" and as you come back it will continue normally.

the project still has not `make` file 😅. but I will add it.
for now, for compile it goto `src` directory and compile `main.c` file with all files in `src/components` directory. or you can use bin file in `src`.

also, you should change input files path with yours in `src/components/listeners.c` file in `listeners_new()` function with yours.

it means, I have done almost nothing! 😂😂 but it will be fixed in next version!
