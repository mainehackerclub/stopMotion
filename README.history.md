stopMotion
==========

<<<<<<< HEAD
This is a stop motion prgram from Alex at the MaineHackerClub. It was written for Maine Discovery Museum.

The History
===========

The program is used in a kiosh. There are 3 buttons on the kiosh. The original buttons were start, capture, and playback. These buttons went to a happcontrol board which went to a usb port. The computer was a windows 98(?) and was 11 years old.  The mouse buttons, left, center, and right, acted the same as the kiosh buttons. A replacement board would have 
arround $150. 

Because there is a limited budget, $0, the volunteers at Maine Hacker Club donated salvaged equipment and their time. The old CRT was replaced with a vga LED panel. The buttons circuit board is a modified keyboard and modified mouse. The camera was a close circuit camera and is now a salvaged web cam donated by Derrick S.

My, Denis S, original idea was to use a stopmotion program for Ubuntu called Stopmotion.  Eric L. thought that ImageMagic was the way to go and wrote a script for that. Because I had no expeerience with ImageMagic and I was more formilliar with how children behave at museums I knew there was a lot of work to be done.  

When demonstating what I wanted to do at a hacker meeting using Ubuntu Stopmotion, Jason M contributed to my understanding about the software programing. Alex G. commented that the Stopmotion is much more complete we need and that he could write a C++ program using openFrameworks.  This became the start. 

Alex G loaded the software onto my computer but it would need to be loaded onto a computer that could remain at the museum until it died. I took the program and taught myself C++ practically from scratch. I don't mean to say the others did not help my education, it was a constant how do I do this or that.

Eric L had made the keyboard switch adapter. This worked great but because I was doing so much testing and the program was using the keyboard I decided to use the mouse which I could hold in my hand while testing. Both Eric and Alex think that the keyboard is the better method. It may be because of the TODO: list.

TODO: Save file
===============
We would like to allow the program to save the video to the web.  This would be done using a coin box with a switch that would send it to the cloud. Alex helped me set up awsamazon. Alex and I met at the IMRC at the University of Maine and had things working on the computer donated by Eric. With his help I was able to enter the final code to upload to the cloud with a push of the button.

Set Back
========

When I took it to the museum the computer started to misbehave. Eric and I met to do troubleshooting. I had some damaged laptops with me. Eric later found that the computer which misbehaved had bad ram. I revived a laptop by replacing the broken screen with one which Eric had salvaged.

Finially
========

I loaded the software onto the restored laptop and was able to install it at the museum.  The buttons are Capture, Delete Last, and Playback.  Save uses the "p" or "x" keys on keyboard in under the desk. The images and movies get saved with a date time tag. They are save on the computer and maybe to awsamazon if the code is correct.



=======
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
>>>>>>> c8fa7d14561d8dc94c483194357563586bddee58


