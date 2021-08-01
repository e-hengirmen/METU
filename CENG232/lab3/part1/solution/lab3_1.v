`timescale 1ns / 1ps
module kb(
	input K,
	input B,
	input clk,
	output reg Q
	);
    
	initial begin
		Q = 0;
	end
	 
	// write your code here
	always@(posedge clk)
	begin
		case({K,B})
			2'b00:Q<=!Q;
			2'b01:Q<=0;
			2'b10:Q<=1;
			2'b11:Q<=Q;
		endcase
	end

endmodule


module ic232(
	input A0, 
	input A1, 
	input A2, 
	input clk,
	output Q0,
	output Q1,
	output Z
	);
   
	// write your code here
	assign Z=Q0~^Q1;
	kb kb0(!A0&!A1&!A2,A1,clk,Q0);
	kb kb1(!A2,(!A0|A1)^A2,clk,Q1);
	
	
endmodule