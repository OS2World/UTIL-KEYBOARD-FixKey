FIXKEY 1.0 USER DOCUMENTATION
______________________________________________________________________

INTRODUCTION
------------

Fixkey is designed to fix OS/2's very annoying problem of not
recognizing certain keys on some 101 keyboards. The keys that do not
work in PM sessions are: insert, delete, home, end, pgup, pgdn, arrow
keys, F11, F12, keypad enter, keypad '/', right alt and right
ctrl. The cursor keys on the numeric keypad work fine. This problem
manifests itself unpredictably, and only in PM sessions. The cause of
this problem is that some keyboards that do not follow IBM
specifications: see APAR PJ11673 for details. Sometimes, the problem
is caused by an old BIOS. Whatever the case, OS/2 detects a PC/AT
keyboard, not an extended 101/102. No fixes will be forthcoming from
IBM, according to this document.

With Fixkey, this problem is alleviated. Once installed, usage is
simple: just start fixkey.exe. That's it. The grey cursor keys should
work. To unload this program, kill the Fixkey PM window in the usual
way: double click on the window corner, or choose "close" from its
system menu or task list.

INSTALLATIION
-------------

First, you might want to check if Fixkey will fix your particular
problem.  I have already described the symptoms. To be sure, run a
diagnostic to see what keyboard OS/2 detects. The free diagnostic in
qconfg.zip from IBM's EWS distribution will tell you this. Get
qconfg.zip from software.watson.ibm.com or ftp.cdrom.com
(os2/ibm/ews/qconfg.zip).

File list:	fixkey.exe
		fixhook.dll
		source.zip (zipped source code)
		readme.txt (this file)

Place fixhook.dll in a directory on your libpath, such as \os2\dll, or
in the same directory as fixkey.exe. Fixkey.exe should, in turn, be
placed in a directory on your path or someplace where you can easily
run it. 

COMMENTS
--------

I am severely lacking in experience in this sort of thing. I have
never written publicly distributable software, so please excuse any
lack of polish. Even more important, this is my first OS/2
program. See disclaimer to sufficiently alarm yourself :-). 

Fixkey should only affect PM sessions. If your keyboard does not work
right in text windows or Dos sessions, you have a different problem
from what I am trying to solve. Also, Fixkey does not appear to be
active in the task list called by ctrl-esc. Finally, Fixkey does not
fix the right ctrl and alt keys. While this is possible, it is more
work than I believe it justifies. Since I have included the source
code, other aspiring programmers are welcome to take over the task.

The source code was compiled using IBM's Cset++ FirstStep compiler, in
C (except for the '//' comments). There should not be anything
specific to the compiler, except for the (simplistic) makefile. The
kbdscan.h file comes from Eberhard Matte's EMX/GCC distribution. 

LICENCE
-------

I can't believe I am writing this. Ah well, basically you can
redistribute it freely, with no restrictions. There is no charge for
use of this program. I only ask that this document be distributed with
the program unchanged.

DISCLAIMER
----------

Here is where I cover my behind. This program is provided "as is",
without warranty of any kind, either expressed or implied, including,
but not limited to, the implied warranties of merchantability and
fitness for a particular purpose. The entire risk as to the quality
and performance of the program is with you. Should the program prove
to be defective, you assume the cost of all necessary servicing,
repair or correction. In no way will I be liable to you for damages,
including any general, special, incidental or consequential damages
arising out of the use or inability to use the program ...

... oh heck. I am sick of typing. Just read the disclaimer portion of
the infamous GNU General Public Licence. Remember, you get what you
pay for :-).

Christopher Wong
25 Myrtle Ave
Cambridge, MA 02138.
wong1@husc4.harvard.edu