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
<div class="row">
  <div class="column">
    <img src="img1.jpg" alt="Snow" style="width:100%">
  </div>
  <div class="column">
    <img src="img2.jpg" alt="Forest" style="width:100%">
  </div>
  <div class="column">
    <img src="img3.jpg" alt="Mountains" style="width:100%">
  </div>
</div>

<style>
* {
  box-sizing: border-box;
}

.column {
  float: left;
  width: 33.33%;
  padding: 5px;
}

/* Clearfix (clear floats) */
.row::after {
  content: "";
  clear: both;
  display: table;
}

/* Responsive layout - makes the three columns stack on top of each other instead of next to each other */
@media screen and (max-width: 500px) {
  .column {
    width: 100%;
  }
}
</style>

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