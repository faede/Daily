# MP3 STRUCT

![Diagram of the structure of an MP3 file](https://upload.wikimedia.org/wikipedia/commons/thumb/0/01/Mp3filestructure.svg/2560px-Mp3filestructure.svg.png)

https://stackoverflow.com/questions/32813803/understanding-mp3-file-structure



Mp3 file is made of sequences of "Frames" (It's about 11000 frames for a mp3 file with 4 minutes playing). At front and end of each MP3 file there are two fields of information (Id3 Tag v1, v2) contains information about Mp3 file - these two fields are optional and can exist or not without any impact on the quality of Mp3 file. You should not hide staga-message here because they can easily be found. Frame consists of frame header (32 bits) and frame body (contains compressed sound). According to your question, steganography will affect on the frame header (32 bits), so I'll focus on frame header!

In 32 bits of frame header still exists some "unimportant bit" due to their functions (read more detail on their function). In short you can use bit in index of: 24, 27, 28, 29, 30, 31, 32 (with bit 27 and 28 will have a small impact on the sound quality) with index in this picture in this link: https://en.wikipedia.org/wiki/MP3#/media/File:Mp3filestructure.svg.

So it depends on whether you want just 5 bits per frame of 7 bits per frame. 7 bits is the max number of bits that you can use on each frame due to my working (both theory and test by source code) but someone else can find a larger bit!

In order to access byte array of each frame, you can write your own class but there are many free available classes on the Internet - NAudio.dll by Mark Heath - (I cannot post link due to forum laws, you can search Google) - is a useful one.

Having accessed the byte array of each frame, you can embed/extract data in/from Mp3 file. Note that: 32 first bits of byte array of each frame is the Frame Header, so you can easily identify the precise index of unimportant bits!

I've recently completed my final year thesis on this topic (steganography on images -LSB, Parity Coding and MP3 - Unused Bits Header). The following source codes from my thesis (written in C#) is a runnable steganography program. I hope that it can help: [http://www.mediafire.com/download/aggg33i5ydvgrpg/ThesisSteganography%2850900483%29.rar](http://www.mediafire.com/download/aggg33i5ydvgrpg/ThesisSteganography(50900483).rar)

Ps: I'm a Vietnamese, so it can exist some errors in my sentences!