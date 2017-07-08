txt files in this directory come from the output of the hardware.
===


files and the meaning of their contents are shown as follows:

    File                Unit              Comments

    distance.txt        centimeter        the distance between ultrasonic range finder and the nearest object

    humidity.txt        percent           the humidity of the environment,range from 20% to 90%, percent sign ommitted

    intensity.txt       bool              0 if it's bright, 1 otherwise

    sound.txt           bool              0 if it's noisy, 1 otherwise

    temperature.txt     bool              the temperature in Celsious 


the python script **httpGet.py** read the last line from these files which means the latest data. Then the data will be post to a website. The website is a temperory website.