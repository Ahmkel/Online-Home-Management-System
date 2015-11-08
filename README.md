# Online-Home-Management-System
Online Home Management System - Control your home from a website!

This is a project that I have done during my internship at the startup which developed the Arduino Shield called "1SHEELD", Integreight: http://1sheeld.com/index2/

This project mainly targeted developing a Home Management System where the user can access a webpage to view the state of sensors and actuators at his home, and to control them too.

The project consists of three parts:

1- The Backend which acts as the common node between the Arduino board and the Website. It provides a RESTful API to be consumed by both the Frontend and the Arduino, and it is developed in Node.js and Express.

2- The Frontend which acts as the main interface for the user and consumes the Backend API. It is developed in AngularJS.

3- The Arduino Code which monitors the input signal of the sensors, controls the output signal of the actuators and consumes the Backend API.