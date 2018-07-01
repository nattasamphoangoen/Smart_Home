import pyrebase
import RPi.GPIO as GPIO
from time import sleep

config = {
  "apiKey": "AIzaSyCN8proRrNMo5cVoOYlu_Q9gO5JsvLhJAQ",
  "authDomain": "smart-e530a.firebaseapp.com",
  "databaseURL": "https://smart-e530a.firebaseio.com",
  "storageBucket": "smart-e530a.appspot.com",
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(11, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)

print "**********    INICIO  *************"

while True:
    salidaLed1 = db.child("Home4/led/led1").get()
    salidaLed2 = db.child("Home4/led/led2").get()
    if(bool(salidaLed1.val()) == True):
		GPIO.output(11, GPIO.HIGH)
    else:
		GPIO.output(11, GPIO.LOW)
		
    if(bool(salidaLed2.val()) == True):
		GPIO.output(13, GPIO.HIGH)
    else:
		GPIO.output(13, GPIO.LOW)

GPIO.cleanup()
