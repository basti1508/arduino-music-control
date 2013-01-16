import alsaaudio, time, audioop
import serial

inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
inp.setchannels(1)
inp.setrate(8000)
inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)

inp.setperiodsize(160)

with serial.Serial(port="/dev/ttyACM0", baudrate=19200) as ser:
	time.sleep(2)
	while True:
		l,data = inp.read()
		if l:
			maxi = audioop.max(data, 2)
			dat = str(maxi)+"\n"
			ser.write(dat)
		time.sleep(.01)
