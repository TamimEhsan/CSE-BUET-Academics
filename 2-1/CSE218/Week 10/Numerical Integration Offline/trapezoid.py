import numpy as np
import termtables as tt

def f(t):
    m = 140000
    q = 2100
    u = 2000
    g = 9.8
    return u*np.log(m/(m-q*t))-g*t

def IntegrationByTrapezoid(lowerLimit, upperLimit, subIntervalNumber):
    divisionWidth = (upperLimit - lowerLimit)/(subIntervalNumber)
    x = np.linspace(lowerLimit, upperLimit, subIntervalNumber +1) # 1 interval has 2 point, n interval has n+1 point
    y = f(x)
    integralValue = divisionWidth/2*(y[0] + 2 * sum(y[1:subIntervalNumber]) + y[subIntervalNumber])
    return integralValue

def findError(prev,curr):
    return np.abs(prev-curr)/curr*100

if __name__ == '__main__':
    subintervalNumber = int(input("Enter the number of subinteval: "))
    if subintervalNumber == 0:
        print("Error")
        exit(0)
    oneSegmentIntegral = IntegrationByTrapezoid(8, 30, 1)
    header = ["iteration", "value", "Relative Error %"]
    table = []
    table.append([1,oneSegmentIntegral,"------"])
    for n in range(1,5,1):
        integralValue = IntegrationByTrapezoid(8,30,n+1)
        table.append([n+1,integralValue,findError(table[n-1][1],integralValue)])
    tt.print(table, header)
    print("Integrated value: ",IntegrationByTrapezoid(8,30,subintervalNumber))


