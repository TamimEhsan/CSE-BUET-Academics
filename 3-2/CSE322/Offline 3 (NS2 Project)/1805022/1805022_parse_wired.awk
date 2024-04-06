BEGIN {
    received_packets = 0;
    sent_packets = 0;
    dropped_packets = 0;
    total_delay = 0;
    received_bytes = 0;
    start_time = 1000000;
    end_time = 0;

    # constants
    header_bytes = 20; # different from wireless topology header size

    count = 0;
}

{
    count = count + 1;
    event = $1;
    time_sec = $2;
    node = $3;
    packet_type = $5;
    packet_bytes = $6;
    packet_id = $12;

    # set start time for the first line
    if(start_time > time_sec) {
        start_time = time_sec;
    }

    if (packet_type == "tcp" || packetType == "udp" || packetType == "cbr") {

        if (event == "+") { 
            # new TCP connection established
            sent_packets += 1;
            sent_time[packet_id] = time_sec;
        }
        else if (event == "d" || event == "D") { 
            # packet dropped
            dropped_packets += 1;
        }

        else if (event == "r" || event == "R") { 
            # packet received

            sent_time_val = sent_time[packet_id];
            delay = time_sec - sent_time_val;
            if (delay >= 0) {
                bytes = (packet_bytes - header_bytes);
                received_bytes += bytes;
                received_packets += 1;
                total_delay += delay;
            }
        }
    }

}

END {
    end_time = time_sec;
    # print "End time: ", end_time
    simulation_time = end_time - start_time;

    # print "Line count: ", count;
    # print "Sent Packets: ", sent_packets;
    # print "Dropped Packets: ", dropped_packets;
    # print "Received Packets: ", received_packets;
    # print "Simulation Time ", simulation_time;
    # print "Received Bytes", received_bytes;

    # print "-------------------------------------------------------------";
    # print "Throughput: ", (received_bytes * 8) / simulation_time, "bits/sec";
    # print "Average Delay: ", (total_delay / received_packets), "seconds";
    # print "Delivery ratio: ", (received_packets / sent_packets);
    # print "Drop ratio: ", (dropped_packets / sent_packets);

    print (received_bytes * 8) / simulation_time, " ", (total_delay / received_packets), 
    " ", (received_packets / sent_packets)*100, " ", (dropped_packets / sent_packets)*100;

}