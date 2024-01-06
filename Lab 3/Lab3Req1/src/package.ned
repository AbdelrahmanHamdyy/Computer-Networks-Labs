package lab3;

@license(LGPL);
//
// TODO documentation
//
network Star
{
    parameters:
        int N @config(N);
        @display("bgb=554,272");
    submodules:
        hub: Hub {
            @display("p=264,118");
        }
        nodes[N]: Node {
            @display("p=387,207");
        }
    connections:
        for i=0..N-1 {
            hub.port++ <--> nodes[i].port;
        }
}
