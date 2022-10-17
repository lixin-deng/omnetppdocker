simple My_node
{
    parameters:
        //@display("i=block/routing");
    gates:
//        input in[];  // declare in[] and out[] to be vector gates
//        output out[];
		inout gate[];
}

network My_network
{
    @display("bgb=398,217");
    submodules:
        Node[3]:  My_node;
//        Node1: My_node {
//            @display("p=94,30");
//        }
//        Node2: My_node {
//            @display("p=235,30");
//        }
//        Node3: My_node {
//
//            @display("p=174,170");

//        }
    connections:

       
//        //Node[0].out[0] --> {  delay = 100ms; } --> Node[1].in[0];
//        Node[0].out++ --> {  delay = 100ms; } --> Node[1].in++;
//        //Node[0].in[0] <-- {  delay = 100ms; } <-- Node[1].out[0];
//        Node[0].in++ <-- {  delay = 100ms; } <-- Node[1].out++;
//        //Node[0].out[1] --> {  delay = 100ms; } --> Node[2].in[0];
//        Node[0].out++ --> {  delay = 100ms; } --> Node[2].in++;
//        //Node[0].in[1] <-- {  delay = 100ms; } <-- Node[2].out[0]; 
//        Node[0].in++ <-- {  delay = 100ms; } <-- Node[2].out++;
//
//	    //Node[1].out[1] --> {  delay = 100ms; } --> Node[0].in[2];
//        Node[1].out++ --> {  delay = 100ms; } --> Node[0].in++;
//        //Node[1].in[1] <-- {  delay = 100ms; } <-- Node[0].out[2];
//        Node[1].in++ <-- {  delay = 100ms; } <-- Node[0].out++;
//        //Node[1].out[2] --> {  delay = 100ms; } --> Node[2].in[1];
//        Node[1].out++ --> {  delay = 100ms; } --> Node[2].in++;
//        //Node[1].in[2] <-- {  delay = 100ms; } <-- Node[2].out[1];
//        Node[1].in++ <-- {  delay = 100ms; } <-- Node[2].out++;
//        
//        //Node[2].out[2] --> {  delay = 100ms; } --> Node[0].in[3];
//        Node[2].out++ --> {  delay = 100ms; } --> Node[0].in++;
//        //Node[2].in[2] <-- {  delay = 100ms; } <-- Node[0].out[3];
//        Node[2].in++ <-- {  delay = 100ms; } <-- Node[0].out++;
//        //Node[2].out[3] --> {  delay = 100ms; } --> Node[1].in[3];
//        Node[2].out++ --> {  delay = 100ms; } --> Node[1].in++;
//        //Node[2].in[3] <-- {  delay = 100ms; } <-- Node[1].out[3];
//        Node[2].in++ <-- {  delay = 100ms; } <-- Node[1].out++;
    Node[0].gate++ <--> {  delay = 100ms; } <--> Node[1].gate++;
    Node[1].gate++ <--> {  delay = 100ms; } <--> Node[2].gate++;
    Node[2].gate++ <--> {  delay = 100ms; } <--> Node[0].gate++;
    
    

    	
    	
   
 
//        Node1.out++ --> {  delay = 100ms; } --> Node3.in++;
//        Node1.in++ <-- {  delay = 100ms; } <-- Node3.out++;
//
//        Node2.out++ --> {  delay = 100ms; } --> Node3.in++;
//        Node2.in++ <-- {  delay = 100ms; } <-- Node3.out++;
        

}
