# ledcube_8x8x8

Hobby Compact LED Cube.

Please beware that I'm not a professional electrical enginner, this project is just me having fun. I provide absolutely no warranty for this :)

![cover](https://raw.githubusercontent.com/trulyspinach/ledcube_8x8x8/master/img/cube.png)

## The hardware build

My goal is to build a compact LED cube. A lot of cube built i found on Internet is huge(kind of, at least you can't carry them with you), even when the resolution is 8x8x8. So I chose to use small LEDs, and a printed circuit board to hold them together while providing control circuits.

The microcontroller is Atmega32A, the reason of choosing AVR is just because they are simple and really cheap to get, and the 32A model have a fairly enough amount of pins available. Then eight 574s are used for multiplexing IOs. No big deals, pretty simple.

To build this, all you need is around 6 hundreds of LEDs. Only 512 are needed, but when you purchasing cheap LEDs, it is likely that some of them will malfunctions. And some resisitor, caps for the motherboard.

![pcb](https://raw.githubusercontent.com/trulyspinach/ledcube_8x8x8/master/img/pcb.png)

I got all components on local stores and AliExpress, the complete built cost me less than $10(surprisingly cheap huh?).

## Software.

Well, since it is an Atmega32A, you can totaly program it using Arduino IDE(You don't need to).
I haven't had enough time to write some beautiful program yet, but the demo code included is just enough to test and proof your circuit is working.

Yes I will put more code here later..

## Did I made a video ?

Yes, it is here: https://www.bilibili.com/video/av40196289/

The voiceover is me speaking Chinese, but it should be fine.

## Where to get PCBs?

I did included all board layout file in the repo, you can export them with Eagle to some manufactor to made them.
As you know, those manufactors don't really like to just make one board, so I have some spare boards in my hand. I can ship one to you if you live in China, and if by the time you contact me I still have them..
