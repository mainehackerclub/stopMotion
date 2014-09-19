stopMotion
==========

This is my version of stopmotion prgram from Alex at the MaineHackerClub. 

The Code
========

I am new to C++ and only familiar with Basic from the 80's.  I did not want to mess up what Alex had done so I created a new repository for mine.

Alex had nothing to do with any crude and messy programing. He knows what he is doing while I am only guessing. You can see what he did before I got my hands on it at another branch from mainehackerclub.

What stopMotion does
====================

The program takes images from the camera and stores them in an array. You can capture, delete and playback images using the mouse.
You can store the video on the Desktop using the x or p key on the keyboard.
With my computer, he program also stores the video on the cloud at aws.amazon.com/stopmotion.
I don't know how you computer will act.

Maybe openFrameworks is required
================================

Alex wrote the original on an Apple computer using openFrameworks. He loaded on my Ubuntu computer which had openFrameworks. I am also running it on another computer with Ubuntu with openFrameworks. 

How to compile
==============

This is how I compile it.
I load open frameworks on my computer. I loaded Code::Block program on my Ubuntu computer. (maybe use xblock on Apple, Visual studio on Win or eclipse.) I then put a copy of mySketch into the openFrameworks../apps/myApps/ folder. I open the mySketch.workspace in Code::Block. I debug and compile.  I copy mySketch program from mySketch/bin to the desktop and rename it to stopMotion.  I then connect the camera, all cameras have worked for me, and use the mouse to make a video. I use the <alt>+<f4> to exit the program. I use the x key to save the video.

Difference between Alex's and mine
==================================

What Alex did was according to the original plan thich is why some things are so radical different.  I used this a an oportunity to learn something about C++. 
+changed the array from 10 to 20 images.
+added the delete option. 
+added the mouse.
+made it full screen
+changed the file name to the day time tag.
+changed the director location
+added the cloud storage.


