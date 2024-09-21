# simulator
set ns [new Simulator]

set opt(side) [lindex $argv 0]  ;# area side
set opt(nn) [lindex $argv 1]  ;# number of nodes
set opt(nf) [lindex $argv 2]  ;# number of flows
set opt(np) [lindex $argv 3] ;# number of packets
set opt(le) [lindex $argv 4] ;# redle or not

Queue/RED set thresh_ 20 
Queue/RED set maxthresh_ 40 
Queue/RED set q_weight_ 1
Queue/RED set cur_max_p_ 0.1
Queue/RED set bytes_ false
Queue/RED set queue_in_bytes_ false
Queue/RED set gentle_ false
Queue/RED set mean_pktsize_ 1000
Queue/RED set redle_ $opt(le)

# ======================================================================
# Define options

set opt(chan)         Channel/WirelessChannel           ;# channel type
set opt(prop)         Propagation/TwoRayGround          ;# radio-propagation model
set opt(ant)          Antenna/OmniAntenna               ;# Antenna type
set opt(ll)           LL                                ;# Link layer type
set opt(ifq)          Queue/RED                         ;# Interface queue type
set opt(ifqlen)       50                                ; # max packet in ifq
set opt(netif)        Phy/WirelessPhy                   ;# network interface type
set opt(mac)          Mac/802_11                        ;# MAC type
set opt(rp)           DSDV                              ;# ad-hoc routing protocol
set opt(energymodel)  EnergyModel                       ;# energy model type
set opt(initialenergy)  1000                            ;# initial energy in Joules
# =======================================================================



# trace file
set trace_file [open trace_802_11.tr w]
$ns trace-all $trace_file

# set length 500
# set width 500
# nam file
set nam_file [open animation_802_11.nam w]
$ns namtrace-all-wireless $nam_file $opt(side) $opt(side)

# topology: to keep track of node movements
set topo [new Topography]
$topo load_flatgrid $opt(side) $opt(side) ;# sidem x sidem area


# general operation director for mobilenodes
create-god $opt(nn)


# node configs
# ======================================================================

$ns node-config -adhocRouting $opt(rp) \
                -llType $opt(ll) \
                -macType $opt(mac) \
                -ifqType $opt(ifq) \
                -ifqLen $opt(ifqlen) \
                -antType $opt(ant) \
                -propType $opt(prop) \
                -phyType $opt(netif) \
                -topoInstance $topo \
                -channelType $opt(chan) \
                -agentTrace ON \
                -routerTrace ON \
                -macTrace ON \
                -movementTrace OFF \
                -energyModel $opt(energymodel) \
			    -idlePower 1.0 \
			    -rxPower 1.0 \
			    -txPower 1.0 \
          		-sleepPower 0.001 \
          		-transitionPower 0.2 \
          		-transitionTime 0.005 \
			    -initialEnergy $opt(initialenergy)

# create nodes
set row 0
set col 0

for {set i 0} {$i < $opt(nn) } {incr i} {
    set node($i) [$ns node]
    $node($i) random-motion 0       ;# disable random motion

    $node($i) set X_ [expr (5000 * $col) / $opt(nn)]
    $node($i) set Y_ [expr ($row) / $opt(nn)]
    $node($i) set Z_ 0

    $ns initial_node_pos $node($i) 20
    
    set col [expr $col + 1]
    if {$i % 10 == 9} {
        set row [expr $row + 5000]
        set col 0
    }
} 

for {set i 0} {$i < $opt(nf)} {incr i} {
	set src [expr ($i * 3) % $opt(nn)]
	set dest [expr ($i * 3 + 2) % $opt(nn)]

    # configuring traffic/flow
    # creating transport-layer agents
    set tcp [new Agent/TCP/Newreno]
    # Set the number of packets to send
	set num_packets $opt(np)

	# Set the window size of the TCP agent
	$tcp set window_ $num_packets

    set tcp_sink [new Agent/TCPSink]

    # attaching agents to nodes
    $ns attach-agent $node($src) $tcp
    $ns attach-agent $node($dest) $tcp_sink

    # connecting agents
    $ns connect $tcp $tcp_sink

    # marking flow
    $tcp set fid_ $i

    # creating application-layer traffic/flow generator
    set ftp [new Application/FTP]
    
    # attach to agent
    $ftp attach-agent $tcp

    # starting traffic/flow generation
    $ns at 1.0 "$ftp start"
}



# End Simulation

# Stop nodes
for {set i 0} {$i < $opt(nn)} {incr i} {
    $ns at 30.0 "$node($i) reset"
}

# call final function
proc finish {} {
    global ns trace_file nam_file
    $ns flush-trace
    close $trace_file
    close $nam_file
}

proc halt_simulation {} {
    global ns
    puts "Simulation ending"
    $ns halt
}

$ns at 40.0001 "finish"
$ns at 40.0002 "halt_simulation"




# Run simulation
puts "Simulation starting"
$ns run
