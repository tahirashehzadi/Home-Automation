# Home-Automation
The basic purpose of the project is to demonstrate how a user can remotely control his appliances via cell phone and the illustration of the smart metering technique. A GSM module or a mobile phone is interfaced with the TM4C123 microcontroller. This cell phone acts as bridge for communication between the user and the microcontroller. The user sends a specified command via his cell phone to that connected with the controller. The controller reads this signal and based upon the instructions given in the SMS by the user, the microcontroller turns on or off the appliances according to the users wish.
2 GSM configuration
2.1 checking GSM for AT commands
• AT
• AT + CMGR = 2
• AT + CMGS = ” + 9230181242..” < ENT ER >
• AT + CMGD = 2
• AT + CMGD = 1, 4
• AT + CMGL = ”ALL”
• AT + CMP S =?
• AT + CMGD = 2
• AT + CMGF =?
• AT + CMGF = 1
• AT + CMGF = 0
• AT + CPMS =?
• AT + CMGF = ”SM”
• AT + CMNI = 1, 2, 0, 0, 0
• AT + CMNI = 1, 1, 0, 0, 0
• blah, blah.
2.2 converting GSM to text mode
There are two modes of GSM.
• pdu mode
• text mode
GSM is being configured as text mode.
2.3 coverting GSM to receiving long text mode
Text can be received either in long or short form.In short form text index means memory address
where text is being stored in SIM received by GSM.In long form sender number, name, date and text
data is being received by GSM.In our case as we need text data so we selected long text mode.
3 TIVA configuration
Two UARTS are being configured for controlling through TIVA.
• UART0
• UART2
GPIO pin PA6 is configured in tristate mode.Output is being provided to bulb through low level
trigger relay.
