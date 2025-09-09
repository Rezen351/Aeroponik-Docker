# TODO for Modifying Communication to Sequential Digital Write

- [x] Modify handleIncomingCommands() in communication.cpp to execute digitalWrite for R1-R6 sequentially with 100ms delay between each.
- [ ] Test the changes by sending JSON input with multiple Rs and verify delays.
