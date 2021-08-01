`timescale 1ns / 1ps

/* EXPECTED OUTPUT

Time=0 | en=1 mode=0 | head=  5 tail=  5 empty=1 full=0
Time=5 | en=1 mode=0 | head=  5 tail=  6 empty=0 full=0
Time=15 | en=1 mode=0 | head=  5 tail=  7 empty=0 full=0
Time=25 | en=1 mode=0 | head=  5 tail=  8 empty=0 full=0
Time=35 | en=1 mode=0 | head=  5 tail=  9 empty=0 full=0
Time=45 | en=1 mode=0 | head=  5 tail= 10 empty=0 full=0
Time=55 | en=1 mode=0 | head=  5 tail=  5 empty=0 full=1
Time=70 | en=1 mode=1 | head=  5 tail=  5 empty=0 full=1
Time=75 | en=1 mode=1 | head=  6 tail=  5 empty=0 full=0
Time=85 | en=1 mode=1 | head=  7 tail=  5 empty=0 full=0
Time=90 | en=1 mode=0 | head=  7 tail=  5 empty=0 full=0
Time=95 | en=1 mode=0 | head=  7 tail=  6 empty=0 full=0
Time=105 | en=1 mode=0 | head=  7 tail=  7 empty=0 full=1
Time=120 | en=1 mode=1 | head=  7 tail=  7 empty=0 full=1
Time=125 | en=1 mode=1 | head=  8 tail=  7 empty=0 full=0
Time=135 | en=1 mode=1 | head=  9 tail=  7 empty=0 full=0
Time=145 | en=1 mode=1 | head= 10 tail=  7 empty=0 full=0
Time=155 | en=1 mode=1 | head=  5 tail=  7 empty=0 full=0
Time=165 | en=1 mode=1 | head=  6 tail=  7 empty=0 full=0
Time=175 | en=1 mode=1 | head=  7 tail=  7 empty=1 full=0

*/


module testbench_queue(
    );

	wire [7:0] llmt;
	wire [7:0] ulmt;
	reg en;
	reg mode;
	reg clk;
	wire [7:0] head;
	wire [7:0] tail;
	wire empty;
	wire full;

	// Instantiate the Unit Under Test (UUT)
	QueueCounter uut(llmt, ulmt, en, mode, clk, head, tail, empty, full);
	
	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
	initial clk = 0;
	always #5 clk = ~clk;
	
	assign llmt = 5;
	assign ulmt = 10;

	initial begin
		// set monitor to inputs and outputs.
		$monitor("Time=%.2d | en=%b mode=%b | head=%d tail=%d empty=%b full=%b", $time, en, mode, head, tail, empty, full);
		
		mode = 0; //insert
		en = 1;
		#70; //insert 7 times, do nothing for the 7th (and no $monitor output), as queue becomes full after the 6th insertion.
		
		mode = 1; //delete
		#20; //delete 2 times
		
		mode = 0; //insert again
		#30; //insert 3 times, do nothing for the 3rd (and no $monitor output), as queue becomes full again after the 2nd insertion.
		
		mode = 1; //delete
		#70; //delete 7 times, do nothing at the 7th time (and no $monitor output), as queue becomes empty after the 6th deletion.

		$finish;
	end //initial

endmodule
