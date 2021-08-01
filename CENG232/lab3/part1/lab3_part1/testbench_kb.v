`timescale 1ns / 1ps
module testbench_kb;

	// Inputs
	reg K;
	reg B;
	reg clk;

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	kb uut (
		.K(K), 
		.B(B), 
		.clk(clk),
		.Q(Q)
	);

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
   initial clk = 0;
	always #5 clk = ~clk;

	initial begin
		// set monitor to inputs and outputs.
		$monitor("Time=%.2d | K=%b B=%b| Q=%b", $time, K, B, Q);
        
		
		#1; //(1ns)Check Initial Q value
		if (Q != 1'b0) $display("Initial value of Q is wrong");
		else $display("Successful");
      
		#1; //(2ns) Set KB=00, complement
		K = 1'b0; B = 1'b0;
		
		#5; //(7ns) Wait for clock edge
		if (Q != 1'b1) $display("Value of Q after Qprev=0 K=0 B=0 is wrong");
		else $display("Successful");
		
		#10; //(17ns) Wait for clock edge 
		if (Q != 1'b0) $display("Value of Q after Qprev=1 K=0 B=0 is wrong");
		else $display("Successful");
		
		#1; //(18ns) Set KB=01, reset
		K = 1'b0; B = 1'b1;
		
		#9; //(27ns) Wait for clock edge 
		if (Q != 1'b0) $display("Value of Q after Qprev=0 K=0 B=1 is wrong");
		else $display("Successful");
		
		#1; //(28ns) Set KB=10, set to 1
		K = 1'b1; B = 1'b0;
		
		#9; //(37ns) Wait for clock edge 
		if (Q != 1'b1) $display("Value of Q after Qprev=0 K=1 B=0 is wrong");
		else $display("Successful");
		
		#10; //(47ns) Wait for clock edge 
		if (Q != 1'b1) $display("Value of Q after Qprev=1 K=1 B=0 is wrong");
		else $display("Successful");
		
		#1; //(48ns) Set KB=11, do nothing
		K = 1'b1; B = 1'b1;
		
		#9; //(57ns) Wait for clock edge 
		if (Q != 1'b1) $display("Value of Q after Qprev=1 K=1 B=1 is wrong");
		else $display("Successful");
		#5;
		$finish;

	end
      
endmodule
