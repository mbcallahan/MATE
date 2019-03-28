## Control Board
### Sensors
<table>
  <tr>
    <th>Pin Name (chip)</th>
    <th>Description</th>
    <th>Pin Number (LPQF64)</th>
    <th>Pin Name (Microcontroller)</th>
  </tr>
  <tr>
    <td colspan="4">HIH6131<br></td>
  </tr>
  <tr>
    <td>SCL<br></td>
    <td>I2C Clock</td>
    <td>37</td>
    <td>PC6</td>
  </tr>
  <tr>
    <td>SDA</td>
    <td>I2C Data</td>
    <td>38</td>
    <td>PC7</td>
  </tr>
  <tr>
    <td colspan="4">BMI160</td>
  </tr>
  <tr>
    <td>SCL</td>
    <td>I2C Clock</td>
    <td>41</td>
    <td>PA8</td>
  </tr>
  <tr>
    <td>SDA</td>
    <td>I2C Data</td>
    <td>40<br></td>
    <td>PC9</td>
  </tr>
  <tr>
    <td colspan="4">ADM3061 (sensors)<br></td>
  </tr>
  <tr>
    <td>RO/RX</td>
    <td>Receive data<br></td>
    <td>43<br></td>
    <td>PA9</td>
  </tr>
  <tr>
    <td>RE</td>
    <td>Receive enable (active high)</td>
    <td>44</td>
    <td>PA11</td>
  </tr>
  <tr>
    <td>DE</td>
    <td>Transmit enable (active low)</td>
    <td>45</td>
    <td>PA12</td>
  </tr>
  <tr>
    <td>DI/TX</td>
    <td>Transmit Data</td>
    <td>42</td>
    <td>PA10</td>
  </tr>
  <tr>
    <td colspan="4">ADM3061 (misc.)</td>
  </tr>
  <tr>
    <td>RO/RX</td>
    <td>Receive data</td>
    <td>52</td>
    <td>PC11<br></td>
  </tr>
  <tr>
    <td>RE</td>
    <td>Receive enable (active high)</td>
    <td>2</td>
    <td>PC13<br></td>
  </tr>
  <tr>
    <td>DE</td>
    <td>Transmit enable (active low)</td>
    <td>3</td>
    <td>PC14</td>
  </tr>
  <tr>
    <td>DI/TX</td>
    <td>Transmit Data</td>
    <td>51</td>
    <td>PC10</td>
  </tr>
</table>

The control board also hase four analog inputs that can measure the voltage of all four nominal voltages present on the ROV:

| Nominal Voltage (V) | Analog Input Voltage at Nominal Voltage (V) | Pin Number (LQFP64) | Pin Name |
|---------------------|---------------------------------------------|---------------------|----------|
| 3.3                 | 2.8                                         | 8                   | PC0      |
| 5                   | 2.727                                       | 9                   | PC1      |
| 24                  | 1.485                                       | 27                  | PB1      |
| 48                  | 1.6679                                      | 10                  | PC2      |

### Motors
The control board supports up to 8 motors driven by a direct PWM signal. The motor drivers we have use a PWM input at 50Hz, with time highs from 1100us to 1900us.

| Motor | Pin Number (LQFP64) | Pin Name |
|-------|---------------------|----------|
| 1     | 4                   | PC15     |
| 2     | 62                  | PB9      |
| 3     | 61                  | PB8      |
| 4     | 57                  | PB5      |
| 5     | 56                  | PB4      |
| 6     | 54                  | PD2      |
| 7     | 53                  | PC12     |
| 8     | 50                  | PA15     |

### Low side switches
The control board as 5 outputs designated for low side switches, however, the power board only has two.
The headers will be configured to send the signals from switches A and B to the low side switches on the board,
and signals for switches C, D, and E are unassigned at the moment. The switches are a single digital output, active high.

| Switch | Pin Number (LQFP64) | Pin Name |
|--------|---------------------|----------|
| A      | 29                  | PB10     |
| B      | 33                  | PB12     |
| C      | 34                  | PB13     |
| D      | 35                  | PB14     |
| E      | 36                  | PB15     |
