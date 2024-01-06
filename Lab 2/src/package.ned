package lab2;

@license(LGPL);
//
// TODO documentation
//
network RNG
{
    @display("bgb=643,251");
    submodules:
        player1: Player1 {
            guess = int(uniform(0, 10));
            @display("p=83,111");
        }
        player2: Player2 {
            target = int(uniform(0, 10));
            @display("p=501,111");
        }
    connections:
        player1.out --> player2.in;
        player2.out --> player1.in;
}