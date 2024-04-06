import matplotlib.pyplot as plt 

# reading statistics from stat.st
stat_file = open("stat.st", "r")
parameter = stat_file.readline()
metrics = stat_file.readline().split()

parameters = []
network_throughputs = []
end_to_end_avg_delays = []
packet_delivery_ratios = []
packet_drop_ratios = []

for line in stat_file:
    if len(line.split()) == 1:
        parameters.append(int(line))
    else:
        split_list = line.split()
        network_throughputs.append(float(split_list[0]))
        end_to_end_avg_delays.append(float(split_list[1]))
        packet_delivery_ratios.append(float(split_list[2]))
        packet_drop_ratios.append(float(split_list[3]))

stat_file.close()

# plotting graphs
plt.plot(parameters, network_throughputs, marker="^", color="b")
plt.ylabel(metrics[0].replace("-", " "))
plt.xlabel(parameter.replace("-", " "))
plt.show()

plt.plot(parameters, end_to_end_avg_delays, marker="v", color="g")
plt.ylabel(metrics[1].replace("-", " "))
plt.xlabel(parameter.replace("-", " "))
plt.show()

plt.plot(parameters, packet_delivery_ratios, marker="<", color="r")
plt.ylabel(metrics[2].replace("-", " "))
plt.xlabel(parameter.replace("-", " "))
plt.show()

plt.plot(parameters, packet_drop_ratios, marker=">", color="y")
plt.ylabel(metrics[3].replace("-", " "))
plt.xlabel(parameter.replace("-", " "))
plt.show()
