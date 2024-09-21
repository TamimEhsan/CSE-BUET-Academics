In 1993, the random early detection (RED) algorithm was created, and in the nearly 30
years since, many scientists have proposed enhanced versions. However, the use of a
pure linear function to compute packets drop probability has led to the problem of
significant delays. To address this issue, researchers suggest using both linear and non-
linear (such as, exponential) functions for packet drop probability. We have proposed a
revised RED algorithm called a RED-linear exponential (RED-LE) that uses a combination
of linear and exponential drop functions. At low and moderate network traffic loads,
RED-LE employs the linear drop function, while at high traffic loads, it uses the
exponential function to calculate the packet drop probability rate. Experimental results
demonstrate that RED-LE is effective in managing congestion and improving network
performance for different traffic loads.