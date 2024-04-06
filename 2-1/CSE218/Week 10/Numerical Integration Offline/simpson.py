import numpy as np
import termtables as T_T

def f(t):
    m = 140000
    q = 2100
    u = 2000
    g = 9.8
    return u*np.log(m/(m-q*t))-g*t

def IntegrationBySimpson(lowerLimit, upperLimit, subIntervalNumber):
    divisionWidth = (upperLimit - lowerLimit)/(subIntervalNumber)
    x = np.linspace(lowerLimit, upperLimit, subIntervalNumber +1)
    y = f(x)
    integralValue = divisionWidth/3*(y[0] + 4 * sum(y[1:subIntervalNumber:2]) + 2*sum(y[2:subIntervalNumber-1:2]) + y[subIntervalNumber])
    return integralValue

def findError(prev,curr):
    return np.abs(prev-curr)/curr*100

if __name__ == '__main__':
    subintervalNumber = int(input("Enter the number of subinteval: "))
    if subintervalNumber == 0:
        print("Error")
        exit(0)
    oneSegmentIntegral = IntegrationBySimpson(8, 30, 2)
    header = ["iteration", "value", "Relative Error %"]
    table = []
    table.append([1,oneSegmentIntegral,"------"])
    for n in range(1,5,1):
        integralValue = IntegrationBySimpson(8,30,(n+1)*2)
        table.append([n+1,integralValue,findError(table[n-1][1],integralValue)])
    T_T.print(table, header)
    print("Integrated value: ",IntegrationBySimpson(8,30,subintervalNumber*2))


