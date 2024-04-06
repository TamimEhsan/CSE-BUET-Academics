# Interpolation

## Newton's Divided Difference Interpolation

### Description

**Interpolation** is an estimation of a value within two known values in a sequence of values.

**Newton’s divided difference interpolation formula** is a interpolation technique used when the interval difference is not same for all sequence of values.

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/80c40f2d06be75a696365bff57f00703a02dde0e)

### Code

The code can be found [Here](Interpolation/Newton's Divided Difference Interpolation)

### Task for Online

Find the mass (in metric ton unit) and velocity (in m/sec unit) of Hardin-3 in t= 25sec using fourth order polynomials of Newton's divided difference method.

| t (sec) | m (metric ton) | v (m/sec) |
| ------- | -------------- | --------- |
| 0       | 1011           | 1000      |
| 5       | 1255           | 1500      |
| 9       | 1347           | 2000      |
| 12      | 1101           | 2500      |
| 19      | 1203           | 3000      |
| 22      | 1245           | 3500      |
| 26      | 1378           | 4000      |
| 28      | 1315           | 4500      |
| 30      | 1475           | 5000      |
| 33      | 1547           | 5500      |
| 40      | 1689           | 6000      |

As we need 4th order polynomial we select the data from 19 to 30 as they are the closest 5 points including the brackets.

#### Plotted Graph For Mass

![](Assets/mass.JPG)

#### Plotted Graph For Velocity

![](Assets/velocity.JPG)

#### Differentiation

![](Assets/differentiation.JPG)



## Lagrange's Interpolation

### Description

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/6e2c3a2ab16a8723c0446de6a30da839198fb04b)

### Code

The code can be found [Here](Interpolation/Lagrange's Interpolation)