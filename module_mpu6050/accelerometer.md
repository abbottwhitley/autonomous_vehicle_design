# Guide to Acclerometers

## What is an accelerometer?

<p>An accelerometer is an electromechanical device that will measure acceleration forces. These forces may be static, like the constant force of gravity pulling at your feet, or they could be dynamic - caused by moving or vibrating the accelerometer.</p><br>

## What are accelerometers useful for?

- Static acceleration provides orientation with respect to ground, measured by gravity
- Dynamic acceleration tells us how the device is moving.


![Angle with respect to earth gravity ](./images/tilt_from_gravity.jpg "angle with respect to earth gravity")

[1] https://www.digikey.com/en/articles/techzone/2011/may/~/media/Images/Article%20Library/TechZone%20Articles/2011/May/Using%20An%20Accelerometer%20for%20Inclination%20Sensing/TZS111_Using_An_Fig_12.jpg <br>


## What is acceleration?

<p>Acceleration is defined as the change in velocity over time. Measuring acceleration in this manner requires knowledge of velocity and a time interval for measurement.</p>
<p>Newton's second law of motion defines acceleration, with requiring time to elapse. Force = mass * acceleration. Acceleration is the amount of force needed to move each unit of mass.</p><br>

## How do accelerometers work?

- In general, they measure force by sensing how a mass presses on something when a force acts on it.
    - Piezoelectric effect - microscopic crystal structures, stressed by accelerative forces, cause a voltage to be generated. 

    ![piezoelectric accelerometer](./images/piezoelectric-accelerometer.png "capacitive accelerometer")[2]

    [2]https://cdn4.explainthatstuff.com/capacitive-accelerometer.png 

    - Change in capacitance - If you have two microstructures next to each other, they have a certain capacitance between them. If an accelerative force moves one of the structures, then the capacitance will change. Add some circuitry to convert from capacitance to voltage, and you will get an accelerometer. 

    ![capacitive accelerometer](./images/capacitive_accelerometer.png "capacitive accelerometer")[3]

    [3]https://cdn4.explainthatstuff.com/capacitive-accelerometer.png

    **MEMS Accelerometer**

    It measures acceleration by measuring change in capacitance. Its micro structure looks something like this. It has a mass attached to a spring which is confined to move along one direction and fixed outer plates. So when an acceleration in the particular direction will be applied the mass will move and the capacitance between the plates and the mass will change. This change in capacitance will be measured, processed and it will correspond to a particular acceleration value.

    ![MEMS accelerometer](./images/MEMS-Accelerometer-How-It-Works.jpg "MEMS accelerometer")[3]

    [4] https://howtomechatronics.com/wp-content/uploads/2015/11/MEMS-Accelerometer-How-It-Works.jpg
<br>
<br>
 
## Considerations when choosing an accelerometer [5]

<p><b>Analog output versus digital output</b> - This is determined by the hardware interface with the accelerometer. Analog style accelerometers output a continuous voltage proportional to acceleration. Digital output is usually a pulse width modulation, with duty cycle proportional to acceleration. For hardware with analog input capability, choose the analog style. For hardware with only digital inputs, choose the digital style. Digital style requires using timing resources to measure the duty cycle and performing additional computation operations.</p>
<p><b>Number of axes</b> - For most projects, two is enough. However, if you want to attempt 3d positioning, you will need a 3 axis accelerometer, or two 2 axis ones mounted at right angles.</p>
<p><b>Maximum swing</b> - If you only care about measuring tilt using earth's gravity, a ±1.5g accelerometer will be more than enough. If you are going to use the accelerometer to measure the motion of a car, plane or robot, ±2g should give you enough headroom to work with. For a project that experiences very sudden starts or stops, you will need one that can handle ±5g or more.</p>
<p><b>Sensitivity</b> - Generally speaking, the more sensitivity the better. This means that for a given change in acceleration, there will be a larger change in signal. Since larger signal changes are easier to measure, you will get more accurate readings.</p>
<p><b>Bandwidth</b> - This means the amount of times per second you can take a reliable acceleration reading. For slow moving tilt sensing applications, a bandwidth of 50Hz will probably suffice. If you intend to do vibration measurement, or control a fast moving machine, you will want a bandwidth of several hundred Hz.</p>

[5] https://www.dimensionengineering.com/info/accelerometers 

