BEGIN {
    received_packets = 0;
    sent_packets = 0;
    dropped_packets = 0;
    total_delay = 0;
    received_bytes = 0;
    
    start_time = 1000000;
    end_time = 0;

    max_energy = 1000;
    for(x=1;x<=200;x++)
        energy_current[x] = max_energy;
    total_energy_consumed = 0;

    # constants
    header_bytes = 20;
}


{
    event = $1;
    time_sec = $2;
    node = $3;
    layer = $4;
    packet_id = $6;
    packet_type = $7;
    packet_bytes = $8;
    energy_consumed = $7;
    node_for_energy = $5;
	time_sec_for_energy = $3;


    sub(/^_*/, "", node);
	sub(/_*$/, "", node);

    # set start time for the first line
    if( event != "N" && start_time > time_sec) {
        start_time = time_sec;
    } else if( event == "N" && start_time > time_sec_for_energy ){
		start_time = time_sec_for_energy;
	}

    if (layer == "AGT" && packet_type == "tcp") {
        
        if(event == "s") {
            sent_time[packet_id] = time_sec;
            sent_packets += 1;
        }

        else if(event == "r") {
            delay = time_sec - sent_time[packet_id];
            
            total_delay += delay;


            bytes = (packet_bytes - header_bytes);
            received_bytes += bytes;

            
            received_packets += 1;
        }
    }

    if (packet_type == "tcp" && event == "D") {
        dropped_packets += 1;
    }
    if(event == "N")
    {
        energy_current[node_for_energy+1] = energy_consumed;
    }
}


END {
	if( event != "N" ) {
        end_time = time_sec;
    } else if( event == "N"  ){
		end_time = time_sec_for_energy;
	}
   
    simulation_time = end_time - start_time;

    for(x=1;x<=200;x++){
        total_energy_consumed += max_energy - energy_current[x];
    }
    # print "Sent Packets: ", sent_packets;
    # print "Dropped Packets: ", dropped_packets;
    # print "Received Packets: ", received_packets;
	# print "Simulation time: ", simulation_time; 

    # print "-------------------------------------------------------------";
    # print "Throughput: ", (received_bytes * 8) / simulation_time, "bits/sec";
    # print "Average Delay: ", (total_delay / received_packets), "seconds";
    # print "Delivery ratio: ", (received_packets / sent_packets);
    # print "Drop ratio: ", (dropped_packets / sent_packets);
    print (received_bytes * 8) / simulation_time, " ", (total_delay / received_packets), 
    " ", (received_packets / sent_packets)*100, " ", (dropped_packets / sent_packets)*100, " ", total_energy_consumed;
}
