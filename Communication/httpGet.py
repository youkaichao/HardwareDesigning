#@author:Kaichao, You
#@email:youkaichao@126.com
#@date:2017/7/8

import requests 
import time
while True:
	time.sleep(1);
	data = {};
	with open('distance.txt', 'r') as f:
		lines = [line for line in f];
		Ultrasonic = lines[-1];
		Ultrasonic = [ch for ch in Ultrasonic if ch.isdigit()];
		Ultrasonic = "".join(Ultrasonic);
		data['Ultrasonic'] = Ultrasonic;
	with open('humidity.txt', 'r') as f:
		lines = [line for line in f];
		Humidity = lines[-1];
		Humidity = [ch for ch in Humidity if ch.isdigit()];
		Humidity = "".join(Humidity);
		data['Humidity'] = Humidity;
	with open('intensity.txt', 'r') as f:
		lines = [line for line in f];
		Light = lines[-1];
		Light = [ch for ch in Light if ch.isdigit()];
		Light = "".join(Light);
		if Light == '0':
			Light = '1';
		else:
			Light = '0';
		data['Light'] = Light;

	with open('sound.txt', 'r') as f:
		lines = [line for line in f];
		Sound = lines[-1];
		Sound = [ch for ch in Sound if ch.isdigit()];
		Sound = "".join(Sound);

		if Sound == '1':
			Sound = '0';
		else:
			Sound = '1';
		data['Sound'] = Sound;
	with open('temperature.txt', 'r') as f:
		lines = [line for line in f];
		Temperature = lines[-1];
		Temperature = [ch for ch in Temperature if ch.isdigit()];
		Temperature = "".join(Temperature);
		data['Temperature'] = Temperature;
	print(data)
	requests.get("http://123.206.31.119/MainPage.aspx", data)