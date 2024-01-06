package lab3req2;

@license(LGPL);
//
// TODO documentation
//
network Ring
{
    parameters:
        int N @config(N);
        @display("bgb=554,272");
    submodules:
        RingNodes[N]: RingNode {
            @display("p=254,48");
        }
    connections:
        for i=0..N-1 {
            	RingNodes[i].ports++ <--> RingNodes[i+1].ports++ if i< N-1;
            	RingNodes[i].ports++ <--> RingNodes[0].ports++ if i == N-1;
        }
}

