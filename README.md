# BBQ-Controller

Controls the temperature inside the BBQ using a fan, PID controller and Blynk IoT App.
With four temperature sensors. 


Files for case (stl), PCB (gerber), Arduino code.


#### Instructions

1. Get components

2. Get PCB e.g. from https://jlcpcb.com/ (asia) or https://aisler.net/ (germany)

3. 3D Print case

4. Assemble Case & PCB

5. Controller (NodeMCU)

    a) Adjust code to own values (todo tags in code)
  
    b) Upload program to controller
    
6. Temperature sensors

    a) Test temperature probes
    
    #### If it shows the correct values skip b,c & d
    
    b) Create a measurement series
    
    c) Use (e.g.) excel to define the function
    
    d) Update controller
    
7. Set up Blynk App https://blynk.io/en/getting-started


#### What is needed:

1x Radial fan (12V, e.g. Titan TFD-B7530M12C Lüfter, 76,2 x 72 x 29,5mm)

1x NodeMCU Lua Lolin V3 Modul mit ESP8266 12E

1x HX Mini 360 (DC-DC step down)

1x Mosfet MJE182

1x Power Supply Barrel 2,1mm

3x Audio jack female (2.5mm)

3x Temperature probe with jack (2.5mm)

4x Resistor (electrical schematic)

1x Diode


#### Files: 
STL files for 3D print

Gerber/ zip folder for PCD print/order

Electrical schematic: circuit diagram from PCD
