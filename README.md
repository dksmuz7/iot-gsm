# <p align="center">GSM based IOT device programme</p>
***Smart Portable Electric Board***

```
Pin Description :-
    1. Rlay 1 (Bulb 1) --> 4
    2. Rlay 2 (Bulb 2) --> 5
    3. Rlay 3 (Bulb 3) --> 6
    4. Rlay 4 (fan 1 ) --> 7
    5. Rx(Arduino)     --> 3
    6. Tx(Arduino)     --> 2
    7. Temperature pin --> 12
    8. Stair Led       --> 13
    9. PIR Pin         --> A2
    10. Mode 1         --> 11
    11. Mode 2         --> 10
    12. Mode 3         --> 9
    13. Mode 4         --> 8
```
**Block Diagram**

<img src="./block_diagram.png" alt="" style="height:40%;">

<!-- **Schematic** -->

<!-- <img src="./schematic.jpg" alt="" style="height:50rem;"> -->
**Images**
<img src="img1.jpg" style="width:99%">
<img src="img2.jpg" style="width:49%"> <img src="img3.jpg" style="width:49%">

### Commands for various operations (Send SMS)
| Sl No. | Command     |     Description      |
| :---   | :---        |     :---:            |
|   1    | b1on        | Turn on bulb 1       |
|   2    | b1off       | Turn off bulb 1      |
|   3    | b2on        | Turn on bulb 2       |
|   4    | b2off       | Turn off bulb 2      |
|   5    | b3on        | Turn on bulb 3       |
|   6    | b3off       | Turn off bulb 3      |
|   7    | b4on        | Turn on bulb 4       |
|   8    | b4off       | Turn off bulb 4      |
|   9    | f1on        | Turn on fan  1       |
|   10   | f1off       | Turn off fan  1      |
|   11   | all on      | Turn on all appliance|
|   12   | all off     | Turn off all         |
|   13   | pir=on      | Activate PIR sensor  |
|   14   | pir=off     | Deactivate PIR sensor|