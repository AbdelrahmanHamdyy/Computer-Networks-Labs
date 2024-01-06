package lab1;

@license(LGPL);
//
// TODO documentation
//
network Test
{
    @display("bgb=463,206");
    submodules:
        Tic: Node {
            @display("p=86,95");
        }
        Toc: Node {
            @display("p=356,95");
        }
    connections:
        Tic.out --> Toc.in;
        Toc.out --> Tic.in;
}

