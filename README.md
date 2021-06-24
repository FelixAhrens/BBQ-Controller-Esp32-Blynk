# BBQ-Controller

Controls the temperature inside a **charcoal BBQ** using a esp32, fan, PID controller and Blynk IoT App.
With four temperature sensors. 

More detailed descriptions with photos will be uploaded in the future.


#### Files

Case: 3d print files (.stl).

PCB: Gerber files to order PCB. JSON files for editing (https://easyeda.com/editor).

Code: .ino for Arduino IDE


#### Instructions

1. Get components

2. Get PCB e.g. from https://jlcpcb.com/ (asia) or https://aisler.net/ (germany)

3. 3D Print case

4. Assemble Case & PCB

5. Controller

    a) Adjust code to own values (todo tags in code)
  
    b) Upload code to controller
    
6. Temperature sensors 

    a) Test temperature probes 
    
    #### Only necessary if the correct values are not displayed (probably because the values depend on the exact input voltage):
    
    b) Create a measurement series
    
    c) Use (e.g.) excel to define the function
    
    d) Update controller
    
7. Set up Blynk App https://blynk.io/en/getting-started


#### What is needed:

##### Used resistors and other type designations in the electrical circuit diagram.

##### Attention: adapt the PCB if you use other components.

1x Radial fan (12V, e.g. Titan TFD-B7530M12C Lüfter, 76,2 x 72 x 29,5mm)

1x ESP32 (e.g. NodeMCU Module WLAN WiFi Dev Kit C Development Board with CP2102)

1x ADC ADS1115

1x HX Mini 360 (DC-DC step down)

1x Mosfet MJE182 / Transistor

1x Power Supply Barrel 2,1mm and corresponding power supply unit (12V).

4x Audio jack female (2.5mm)

4x Temperature probe with jack (2.5mm)

5x Resistor

1x Diode 

1x 6x6 push button (reset)

2x SPDT changeover switch (to switch the electrical circuit, but it is not mandatory)
