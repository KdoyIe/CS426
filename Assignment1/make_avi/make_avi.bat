ECHO Make sure you bitmap files are in C:\temp
ECHO Enter name of file without numbers or bmp extension (e.g. for magnify01.BMP enter magnify)
ECHO

SET /P M=File name prefix : 

bmp2avi -o %M%.avi c:\temp\%M%

ECHO 

SET /P M=<Press any key to finish>:
