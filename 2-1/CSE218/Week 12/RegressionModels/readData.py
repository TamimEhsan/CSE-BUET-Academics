
def readFile():
    datas = []
    x = []
    y = []
    with open('data.txt') as f:
        datas = f.readlines()
    for data in datas:
        a,b = map(float,data.split())
        x.append(a)
        y.append(b)
    return len(x),x,y

