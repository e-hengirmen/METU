`timescale 1ns / 1ps

module ROM (
input [2:0] addr, 
output reg [7:0] dataOut);

	// write your code below
	always @*
	begin
		case(addr)
		0:dataOut=8'b00000000;
		1:dataOut=8'b01010101;
		2:dataOut=8'b10101010;
		3:dataOut=8'b00110011;
		4:dataOut=8'b11001100;
		5:dataOut=8'b00001111;
		6:dataOut=8'b11110000;
		7:dataOut=8'b11111111;
		endcase
	end
	
endmodule


module XOR_RAM (
input mode, 
input [2:0] addr, 
input [7:0] dataIn, 
input [7:0] mask, 
input CLK, 
output reg [7:0] dataOut);

	reg [7:0]ram[0:7];
	initial begin
		//for(int i=0;i<=7;i=i+1)ram[i]=0;
		ram[0]=0;
		ram[1]=0;
		ram[2]=0;
		ram[3]=0;
		ram[4]=0;
		ram[5]=0;
		ram[6]=0;
		ram[7]=0;
		dataOut=0;
	end
	
	//	assign dataOut=(mode?ram[addr]:dataOut);
	always @*
	if(mode)dataOut<=ram[addr];
	
	always @(posedge CLK)
	if(mode==0)ram[addr]<=dataIn^mask;
	
	
	
endmodule


module EncodedMemory (
input mode, 
input [2:0] index, 
input [7:0] number, 
input CLK, 
output [7:0] result);
	
	// DO NOT EDIT THIS MODULE
	
	wire [7:0] mask;
	
	ROM R(index, mask);
	XOR_RAM XR(mode, index, number, mask, CLK, result);

endmodule
