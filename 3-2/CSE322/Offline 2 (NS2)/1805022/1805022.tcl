# simulator
set ns [new Simulator]


# ======================================================================
# Define options

set val(chan)         Channel/WirelessChannel  ;# channel type
set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
set val(ant)          Antenna/OmniAntenna      ;# Antenna type
set val(ll)           LL                       ;# Link layer type
set val(ifq)          Queue/DropTail/PriQueue  ;# Interface queue type
set val(ifqlen)       50                       ;# max packet in ifq
set val(netif)        Phy/WirelessPhy          ;# network interface type
set val(mac)          Mac/802_11               ;# MAC type
set val(rp)           AODV                     ;# ad-hoc routing protocol 
# set val(nn)           20                       ;# number of mobilenodes

set val(as) [lindex $argv 0]  ;# area side
set val(nn) [lindex $argv 1]  ;# number of mobilenodes
set val(nf) [lindex $argv 2]  ;# number of flows

# =======================================================================

# trace file
set trace_file [open trace.tr w]
$ns trace-all $trace_file

# nam file
set nam_file [open animation.nam w]
$ns namtrace-all-wireless $nam_file $val(as) $val(as)

# topology: to keep track of node movements
set topo [new Topography]
$topo load_flatgrid $val(as) $val(as)  ;# $val(as)m x $val(as)m area


# general operation director for mobilenodes
create-god $val(nn)


# node configs
# ======================================================================

$ns node-config -adhocRouting $val(rp) \
                -llType $val(ll) \
                -macType $val(mac) \
                -ifqType $val(ifq) \
                -ifqLen $val(ifqlen) \
                -antType $val(ant) \
                -propType $val(prop) \
                -phyType $val(netif) \
                -topoInstance $topo \
                -channelType $val(chan) \
                -agentTrace ON \
                -routerTrace ON \
                -macTrace OFF \
                -movementTrace OFF 


# creating network-layer nodes
for {set i 0} {$i < $val(nn)} {incr i} {
    set node($i) [$ns node]

    # disabling random motion
    $node($i) random-motion 0

    # positioning node randmoly along x & y axes
    $node($i) set X_ [expr int(10000 * rand()) % $val(as) + 0.5]
    $node($i) set Y_ [expr int(10000 * rand()) % $val(as) + 0.5]
    $node($i) set Z_ 0

    # configuring node
    $ns initial_node_pos $node($i) 20
}

# producing node movements with uniform random speed
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at [expr int(20 * rand()) + 10] "$node($i) setdest [expr int(10000 * rand()) % $val(as) + 0.5] [expr int(10000 * rand()) % $val(as) + 0.5] [expr int(100 * rand()) % 5 + 1]"
}

# generating traffic/flow
# picking random source node
set sink [expr int(1000 * rand()) % $val(nn)]

for {set i 0} {$i < $val(nf)} {incr i} {
    # picking random destination/sink node
    while {$sink == $sink} {
        set src [expr int(1000 * rand()) % $val(nn)]
        if {$src != $sink} {
            break
        }
    }


    # puts "from $src $sink"

    # configuring traffic/flow
    # creating transport-layer agents
    set tcp [new Agent/TCP]
    set tcp_sink [new Agent/TCPSink]

    # attaching agents to nodes
    $ns attach-agent $node($src) $tcp
    $ns attach-agent $node($sink) $tcp_sink

    # connecting agents
    $ns connect $tcp $tcp_sink

    # marking flow
    $tcp set fid_ $i

    # creating application-layer traffic/flow generator
    set telnet [new Application/Telnet]

    # attaching traffic/flow generator to agent
    $telnet attach-agent $tcp


    # starting traffic/flow generation
    $ns at 1.0 "$telnet start"
}




# End Simulation

# Stop nodes
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at 50.0 "$node($i) reset"
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

$ns at 50.0001 "finish"
$ns at 50.0002 "halt_simulation"



# Run simulation
puts "Simulation starting"
$ns run
