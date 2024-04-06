#!/bin/bash

echo -e "\nscript.sh running\n"

baseline_area_size=500
baseline_num_nodes=40
baseline_num_flows=20
baseline_num_packets=100

echo -e "running for normal red\n"

touch result_11_area.txt
touch result_11_nn.txt
touch result_11_nf.txt
touch result_11_np.txt

#varying area size
echo -e "Area-Size-(m)\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_area.txt
echo -e "Changing area size\n"

for((i=0; i<5; i++)); do
    area_size=`expr 250 + $i \* 250`
    echo -e $area_size >> result_11_area.txt

    echo -e "802_11_static.tcl: running with $area_size $baseline_num_nodes $baseline_num_flows $baseline_num_packets 0\n"
    ns 802_11_static.tcl $area_size $baseline_num_nodes $baseline_num_flows $baseline_num_packets 0
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_area.txt 
done

#varying number of nodes
echo -e "Number-of-Nodes\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_nn.txt
echo -e "Changing number of nodes\n"

for((i=0; i<5; i++)); do
    num_nodes=`expr 20 + $i \* 20`
    echo -e $num_nodes >> result_11_nn.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $num_nodes $baseline_num_flows $baseline_num_packets 0\n"
    ns 802_11_static.tcl $baseline_area_size $num_nodes $baseline_num_flows $baseline_num_packets 0
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_nn.txt 
done

#varying number of flows
echo -e "Number-of-Flows\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_nf.txt
echo -e "Changing number of flows\n"

for((i=0; i<5; i++)); do
    num_flows=`expr 10 + $i \* 10`
    echo -e $num_flows >> result_11_nf.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $baseline_num_nodes $num_flows $baseline_num_packets 0\n"
    ns 802_11_static.tcl $baseline_area_size $baseline_num_nodes $num_flows $baseline_num_packets 0
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_nf.txt 
done

#varying number of packets
echo -e "Number-Of-Packets\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_np.txt
echo -e "Changing number of packets\n"

for((i=0; i<5; i++)); do
    num_packets=`expr 100 + $i \* 100`
    echo -e $num_packets >> result_11_np.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $baseline_num_nodes $baseline_num_flows $num_packets 0\n"
    ns 802_11_static.tcl $baseline_area_size $baseline_num_nodes $baseline_num_flows $num_packets 0
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_np.txt 
done

echo -e "running for le\n"

touch result_11_area_modified.txt
touch result_11_nn_modified.txt
touch result_11_nf_modified.txt
touch result_11_np_modified.txt

#varying area size
echo -e "Area-Size-(m)\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_area_modified.txt
echo -e "Changing area size\n"

for((i=0; i<5; i++)); do
    area_size=`expr 250 + $i \* 250`
    echo -e $area_size >> result_11_area_modified.txt

    echo -e "802_11_static.tcl: running with $area_size $baseline_num_nodes $baseline_num_flows $baseline_num_packets 1\n"
    ns 802_11_static.tcl $area_size $baseline_num_nodes $baseline_num_flows $baseline_num_packets 1
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_area_modified.txt 
done

#varying number of nodes
echo -e "Number-of-Nodes\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_nn_modified.txt
echo -e "Changing number of nodes\n"

for((i=0; i<5; i++)); do
    num_nodes=`expr 20 + $i \* 20`
    echo -e $num_nodes >> result_11_nn_modified.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $num_nodes $baseline_num_flows $baseline_num_packets 1\n"
    ns 802_11_static.tcl $baseline_area_size $num_nodes $baseline_num_flows $baseline_num_packets 1
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_nn_modified.txt 
done

#varying number of flows
echo -e "Number-of-Flows\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_nf_modified.txt
echo -e "Changing number of flows\n"

for((i=0; i<5; i++)); do
    num_flows=`expr 10 + $i \* 10`
    echo -e $num_flows >> result_11_nf_modified.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $baseline_num_nodes $num_flows $baseline_num_packets 1\n"
    ns 802_11_static.tcl $baseline_area_size $baseline_num_nodes $num_flows $baseline_num_packets 1
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_nf_modified.txt 
done

#varying number of packets
echo -e "Number-Of-Packets\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%) Energy-Consumed-(J)" > result_11_np_modified.txt
echo -e "Changing number of packets\n"

for((i=0; i<5; i++)); do
    num_packets=`expr 100 + $i \* 100`
    echo -e $num_packets >> result_11_np_modified.txt

    echo -e "802_11_static.tcl: running with $baseline_area_size $baseline_num_nodes $baseline_num_flows $num_packets 1\n"
    ns 802_11_static.tcl $baseline_area_size $baseline_num_nodes $baseline_num_flows $num_packets 1
    awk -f 1805022_parse_802_11.awk trace_802_11.tr >> result_11_np_modified.txt 
done

echo -e "script.sh:over"
