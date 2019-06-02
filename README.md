# RPIHomeServer [![Build Status](https://travis-ci.org/Alberto-Izquierdo/RPIHomeServer.svg?branch=master)](https://travis-ci.org/Alberto-Izquierdo/RPIHomeServer)

Personal raspberry pi multithreaded home server. For now it includes four modules:

- GPIO module: it controls the GPIO interface of the raspberry pi, in my case it is used to turn on and off one light of the house.
- Telegram bot module: instead of creating a REST API or similar, I just use the telegram bot interface for its simplicity. (Thanks to [Madrid C++ meetup](https://www.meetup.com/es-ES/Madrid-C-Cpp/) for the workshop)
- Message generator module that launches messages at the time specified in the configuration file.
- Communication module to handle the messages between the other modules.

Each of them can be activated/deactivated through the configuration file (see config.json) except the communication module that is always launched in the main thread to manage the messages between modules.

My plans for this project include using multiple raspberrys that communicate between them, and anything that passes through my mind.
