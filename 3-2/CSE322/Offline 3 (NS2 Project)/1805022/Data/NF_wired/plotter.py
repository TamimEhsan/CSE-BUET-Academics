import matplotlib.pyplot as plt
import numpy as np

# Define the filenames containing the data
filenames = ['original_red.txt', 'modified_red_tahoe.txt', 'modified_red_newreno.txt']

param = 'Number of flows'
# Define the data points to plot
data_points = ['Network Throughput(kilobits/sec)', 'Average Delay(sec)', 'Packet Delivery Ratio(%)', 'Packet Drop Ratio(%)']

# Create a new figure and axis object for each data point
fig, axs = plt.subplots(4, 1, figsize=(6, 12))

# Loop through each data point and plot the data
for i, data_point in enumerate(data_points):
    # Loop through each file and plot the data for the current data point
    for filename in filenames:
        x = []
        y = []
        # network_throughputs = []
        # end_to_end_delay = []
        # packet_delivery_ratio = []
        # packet_drop_ratio = []
        # energy_consumed = []
        ff = open(filename, "r")
        ff.readline()
        ff.readline()
        for line in ff:
            if len(line.split()) == 1:
                x.append(int(line))
            else:
                splitter = line.split()
                # network_throughputs.append(float(splitter[0]))
                # end_to_end_delay.append(float(splitter[1]))
                # packet_delivery_ratio.append(float(splitter[2]))
                # packet_drop_ratio.append(float(splitter[3]))
                # energy_consumed.append(float(splitter[4]))
                y.append(float(splitter[i]))
                # print(y)
        # # Load the data from the file
        # data = np.loadtxt(filename)

        # # Extract the x and y values for the current data point
        # x = data[:, 0]
        # y = data[:, i+1]

        # Plot the data on the current axis
        axs[i].plot(x, y, label=filename)

    # Set the axis labels and title for the current axis
    axs[i].set_xlabel(param)
    axs[i].set_ylabel(data_point)
    # axs[i].set_title(f'Plot of {data_point}')

    # Add a legend to the current axis
    axs[i].legend()

# Adjust the spacing between subplots
fig.tight_layout()

# Show the plot
plt.show()
