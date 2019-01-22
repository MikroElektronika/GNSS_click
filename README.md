![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# GNSS Click

- **CIC Prefix**  : GNSS
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : jan 2019.

---


### Software Support

We provide a library for the GNSS Click on our [LibStock](https://libstock.mikroe.com/projects/view/1262/gnss-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library carries generic command parser adopted for GPS-MNEA command based modules. 
Generic parser 

Key functions :

- ``` gnss_cmdSingle ``` - Sends provided command to the module
- ``` gnss_setHandler ``` - Handler assignation to the provied command
- ``` gnss_modulePower ``` - Turn on module

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with GPS module and UART used for infromation logging
- Application Initialization - Initializes driver, power on module
- Application Task - running in parallel core state machine.
If response detected parser will hang information of Latitude, Longitude and Altitude .

```.c
void applicationTask()
{
    char *pLat;
    char *pLong;
    char *pAlt;
    char rspCom[ 50 ] = {0};
        
// CORE STATE MACHINE
    gnss_process();

    if(timerCounter > 5000)
    {
        pFlag++;
        if(pFlag > 2)
        {
            pFlag = 0;
        }
        timerCounter = 0;
        dispFlag = 1;
    }

    if(pFlag == 0 && dispFlag == 1)
    {
        mikrobus_logWrite( "  ", _LOG_LINE);
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
        pLat = gnss_parser(&demoBuffer[0], &demoCommand[0], 2);

        if(pLat == 0)
        {
            mikrobus_logWrite( " Latitude : No data available!", _LOG_LINE);
        }
        else
        {
            strcpy(&rspCom[0], pLat);
            mikrobus_logWrite( " Latitude : ", _LOG_TEXT);
            mikrobus_logWrite(rspCom, _LOG_LINE);
        }
        dispFlag = 0;
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
    }

    if(pFlag == 2 &&  dispFlag == 1)
    {
        mikrobus_logWrite( "  ", _LOG_LINE);
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
        pAlt = gnss_parser(&demoBuffer[0], &demoCommand[0], 9);
        if(pAlt == 0)
        {
            mikrobus_logWrite( " Altitude : No data available!", _LOG_LINE);
        }
        else
        {
            strcpy(&rspCom[0], pAlt);
            mikrobus_logWrite( " Altitude : ", _LOG_TEXT);
            mikrobus_logWrite(rspCom, _LOG_LINE);
        }
        dispFlag = 0;
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
    }

    if(pFlag == 1 && dispFlag == 1)
    {
        mikrobus_logWrite( "  ", _LOG_LINE);
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
        pLong = gnss_parser(&demoBuffer[0], &demoCommand[0], 4);
        if(pLong == 0)
        {
            mikrobus_logWrite( " Longitude : No data available!", _LOG_LINE);
        }
        else
        {
            strcpy(&rspCom[0], pLong);
            mikrobus_logWrite( " Longitude : ", _LOG_TEXT);
            mikrobus_logWrite(rspCom, _LOG_LINE);
        }
        dispFlag = 0;
        mikrobus_logWrite( " ---------------------------------------- ", _LOG_LINE);
    }
}
```
Additional Functions :

All additional functions such as timer initialization and default handler. 

Notes :

- The GPS module returns data in the form of NMEA responses
- For example, we used the GGA response

- $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47

For parsing, use the GPS Parser function to send the following form of arguments:
The name of the NMEA response that you want to parse, the position of the data that you need.
As a response - you will get a separate buffer with the requested data

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1262/gnss-click) page.

Other mikroE Libraries used in the example:

- String
- Conversion
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
