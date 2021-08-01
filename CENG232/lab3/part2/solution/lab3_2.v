`timescale 1ns / 1ps
module QueueCounter(
	input [7:0] llmt,
	input [7:0] ulmt,
	input en,
	input mode, // 1:delete, 0:insert
	input clk,
	output reg [7:0] head,
	output reg [7:0] tail,
	output reg empty,
	output reg full);
	
	//you may write your code here
	

	initial
	begin
		head = llmt;
		tail = llmt;
		empty=1;
		full=0;
	end

	//you may write your code here
	always@(posedge clk)
	begin
		if(en==0 || (mode==0&&full==1) || (mode==1&&empty==1) )
		begin
		/*
			head=head;
			tail=tail;
			empty=empty;
			full=full;*/
		end
		else if(mode==0)
		begin
			empty=0;
			if(tail==ulmt)tail=llmt;
			else tail=tail+1;
			if(tail==head)full=1;
		end
		else	//mode==1
		begin
			full=0;
			if(head==ulmt)head=llmt;
			else head=head+1;
			if(tail==head)empty=1;
		end

	end

endmodule


module Numerator(
	input clinic, 
	input mode, 
	input en, 
	input clk,
	output [7:0] ann,
	output [7:0] print);

	//write your code here
	
	reg [7:0] ANN;
	reg [7:0] PRINT;
	
	//reg last_e0,last_e1,last_f0,last_f1;
	wire empty0,empty1,full0,full1;
	wire [7:0] head0;
	wire [7:0] tail0;
	wire [7:0] head1;
	wire [7:0] tail1;
	
	QueueCounter Q0(8'b00000101,8'b00001001,en&&!clinic,mode,clk, head0,tail0,empty0,full0);
	QueueCounter Q1(8'b00001010,8'b00001110,en&&clinic ,mode,clk, head1,tail1,empty1,full1);
	
	/*
	initial begin
		last_e0=1;
		last_e1=1;
		last_f0=0;
		last_f1=0;
	end*/
	
	//assign print=(en?(clinic?tail1:tail0):PRINT);
	//assign ann=(en?(clinic?head1:head0):ANN);
	
	assign print=PRINT;
	assign ann=ANN;
	
	always@(*)
	begin
		if(en)
		begin
			PRINT=(clinic?tail1:tail0);
			ANN=(clinic?head1:head0);
		end
	end
	


endmodule
