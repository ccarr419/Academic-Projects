README.txt

Christian Carreras
CSC 552

Issues/Bugs/Non-Implementations:
* Semapores were not implemented
* No signals for shutdown implemented
* Inter-machine communication only works one way from my testing. The client not on
acad can send messages but not receive. The client on acad can receive but not send.
* Shared memory on the client side retains information correctly but it will be
displayed incorrectly if users do not log out in FIFO order. This is because I did
not implement a inUse boolean system to see what slots/rows in the LOCAL_DIR are
being used. I did however use the boolean system for server shared memory.
* Minimal documention was added to the server and almost none to the client due
to time restraints. I wanted to submit my project on time for the presentation.
* During the presentation not all messages sent were received. It was originally
thought to be a problem with the ports but this was later debunked.

Different Design Decisions:
* Client counter is incremented within the child instead of the parent i.e. after
successful login and not before the fork().
* Parent server process does not wait for child, only waits on accept.
* A client's message is sent to the server first and then redirected towards the
intended recipient. This is so the server can tell the user the status of the sent
message such as the recipient does not exist, the recipient is the user or the
message was sent/failed to send.
* The client splits a a message into multiple messages if it goes over the standard
message length.
