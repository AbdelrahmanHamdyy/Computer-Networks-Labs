package lab5;

@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=1081,332");
    types:
    submodules:
        sender: Sender {
            @display("p=161,90");
        }
        receiver: Receiver {
            @display("p=799,88");
        }
    connections:
        sender.out --> receiver.in;
        receiver.out --> sender.in;
}

