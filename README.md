# RPIHomeServer [![Build Status](https://travis-ci.org/Alberto-Izquierdo/RPIHomeServer.svg?branch=master)](https://travis-ci.org/Alberto-Izquierdo/RPIHomeServer)

Personal raspberry pi multithreaded home server. For now it includes 3 modules:

- GPIO module: it controls the GPIO interface of the raspberry pi, in my case it is used to turn on and off one light of the house.
- Telegram bot module: instead of creating a REST API or similar, I just use the telegram bot interface for its simplicity. (Thanks to [Madrid C++ meetup](https://www.meetup.com/es-ES/Madrid-C-Cpp/) for the workshop)
- Communication module to handle the messages between the other modules.

My plans for this project include creating an automatic watering system, and anything that passes through my mind.
