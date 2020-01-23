import matplotlib.pyplot as plt
import numpy as np 

# sinusoidal signal parameters
amplitude = 2
signalFreq = 3     # signal frequency, Hz

# noise Frequency
noiseFreq = signalFreq * 4
noiseFreq2 = signalFreq * 5.5

# sampling parameters

# Nyquist: sample rate must be at least twice max signal frequency
fs = signalFreq * 30   # sample rate, Hz (samples/sec)
T = 1.0               # time period, seconds
n = int(T *fs)        # total number of samples = samples/sec * sec


# generate evenly spaced array of time values
t = np.linspace(0,T,n, endpoint=False)
y = amplitude * np.sin(2*np.pi*signalFreq*t)

# add noise to signal
ynoise = amplitude * np.sin(2*np.pi*signalFreq*t) + \
    0.5 * np.cos(noiseFreq*2*np.pi*t) + 1.5 * np.sin(noiseFreq2*2*np.pi*t)

# labels will be show in legend
plt.subplot(2,1,1)      # nrows, ncols, index
plt.plot(t, y)


plt.subplot(2,1,2)      # second row
plt.plot(t, ynoise, color='red')
plt.xlabel('Time [sec]')
plt.title("Noisy Signal")

# everything is drawn in the background, call show to see it
plt.show()