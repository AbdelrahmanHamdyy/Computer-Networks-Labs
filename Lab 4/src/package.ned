package lab4;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=468,218");
    submodules:
        sender: Sender {
            @display("p=72,94");
        }
        receiver: Receiver {
            @display("p=377,94");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}

