#!/bin/bash

echo -e "\nscript.sh running\n"

baseline_num_nodes=40
baseline_num_flows=20
baseline_num_packets=100

touch result_wired_nn.txt
touch result_wired_nf.txt
touch result_wired_np.txt

#varying number of nodes
echo -e "Number-of-Nodes\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_nn.txt
echo -e "Changing number of nodes\n"

for((i=0; i<5; i++)); do
    num_nodes=`expr 20 + $i \* 20`
    echo -e $num_nodes >> result_wired_nn.txt

    echo -e "wired.tcl: running with $num_nodes $baseline_num_flows $baseline_num_packets 0\n"
    ns wired.tcl $num_nodes $baseline_num_flows $baseline_num_packets 0
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_nn.txt 
done

#varying number of flows
echo -e "Number-of-Flows\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_nf.txt
echo -e "Changing number of flows\n"

for((i=0; i<5; i++)); do
    num_flows=`expr 10 + $i \* 10`
    echo -e $num_flows >> result_wired_nf.txt

    echo -e "wired.tcl: running with $baseline_num_nodes $num_flows $baseline_num_packets 0\n"
    ns wired.tcl $baseline_num_nodes $num_flows $baseline_num_packets 0
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_nf.txt 
done

#varying number of packets
echo -e "Number-Of-Packets\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_np.txt
echo -e "Changing number of packets\n"

for((i=0; i<5; i++)); do
    num_packets=`expr 100 + $i \* 100`
    echo -e $num_packets >> result_wired_np.txt

    echo -e "wired.tcl: running with $baseline_num_nodes $baseline_num_flows $num_packets 0\n"
    ns wired.tcl $baseline_num_nodes $baseline_num_flows $num_packets 0
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_np.txt 
done

echo -e "running for le\n"

touch result_wired_nn_modified.txt
touch result_wired_nf_modified.txt
touch result_wired_np_modified.txt

#varying number of nodes
echo -e "Number-of-Nodes\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_nn_modified.txt
echo -e "Changing number of nodes\n"

for((i=0; i<5; i++)); do
    num_nodes=`expr 20 + $i \* 20`
    echo -e $num_nodes >> result_wired_nn_modified.txt

    echo -e "wired.tcl: running with $num_nodes $baseline_num_flows $baseline_num_packets 1\n"
    ns wired.tcl $num_nodes $baseline_num_flows $baseline_num_packets 1
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_nn_modified.txt 
done

#varying number of flows
echo -e "Number-of-Flows\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_nf_modified.txt
echo -e "Changing number of flows\n"

for((i=0; i<5; i++)); do
    num_flows=`expr 10 + $i \* 10`
    echo -e $num_flows >> result_wired_nf_modified.txt

    echo -e "wired.tcl: running with $baseline_num_nodes $num_flows $baseline_num_packets 1\n"
    ns wired.tcl $baseline_num_nodes $num_flows $baseline_num_packets 1
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_nf_modified.txt 
done

#varying number of packets
echo -e "Number-Of-Packets\nNetwork-Throughput-(kilobits/sec) End-to-End-Delay-(sec) Packet-Delivery-Ratio-(%) Packet-Drop-Ratio-(%)" > result_wired_np_modified.txt
echo -e "Changing number of packets\n"

for((i=0; i<5; i++)); do
    num_packets=`expr 100 + $i \* 100`
    echo -e $num_packets >> result_wired_np_modified.txt

    echo -e "wired.tcl: running with $baseline_num_nodes $baseline_num_flows $num_packets 1\n"
    ns wired.tcl $baseline_num_nodes $baseline_num_flows $num_packets 1
    awk -f 1805022_parse_wired.awk trace_wired.tr >> result_wired_np_modified.txt 
done

echo -e "script.sh:over"
