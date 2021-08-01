`timescale 1ns / 1ps

//
// NOTE: This is a sample testbench, provided to you as a guidance.
//

module testbench(
    );
	
	reg	[2:0] mode; //1XX:display; 000: remA; 001:remB; 010:addA; 011:addB
	reg	[4:0] plateIn;
	reg   action;
	reg   clk;
	wire  greenForA;
	wire  greenForB;
	wire  rushHourWarning;
	wire  [3:0]  hour;
	wire  [5:0]  minute;	
	wire  [5:0]  second;
	wire  am_pm;
	wire  [4:0]  numOfCarsA;
	wire  [4:0]  numOfCarsB;
	wire  [6:0]  remainingTime;
	wire  [4:0]  blackListDisplay;

	// Instantiate the Unit Under Test (UUT)
   IntersectionSimulator uut(
		mode,
		plateIn,
		action,
		clk,
		greenForA,
		greenForB,
		rushHourWarning,
		hour,
		minute,
		second,
		am_pm,
		numOfCarsA,
		numOfCarsB,
		remainingTime,
		blackListDisplay
	);

	// At 5, 15, 25, .. clk will change 0->1
	// At 10, 20, 30, .. clk will change 1->0
   initial clk = 0;
	always #5 clk = ~clk;
	

	initial begin
		mode=3'b000;
		plateIn=5'b00001;
		action=0;
		
		#1;
		
		while(greenForA==1'b1)
		begin
			#10; // 1 clock cycle
		end
		
		//************************************************************************
		//check Line No 6 where greenForA=0 and greenForB=0 (you may also check hour, minute, seconds: 06:00:50 AM)
		if(remainingTime==0 && greenForA==0 && greenForB==0)
			$display("Line No 6 Test Success");
		else
			$display("Line No 6 Test Fail");
		//************************************************************************
		
		#10; //after 1 clock cycle
		
		//************************************************************************
		//check Line No 7 where greenForA=0 and greenForB=1 (you may also check hour, minute, seconds:  06:00:51 AM)
		if(remainingTime==40 && greenForA==0 && greenForB==1)
			$display("Line No 7 Test Success");
		else
			$display("Line No 7 Test Fail");
		//************************************************************************
		
		//pass time until rushHourWarning is set to 1
		while(rushHourWarning==1'b0)
		begin
			#10; // 1 clock cycle
		end
		
		//************************************************************************
		//check Line No 17, click Simulation->Run All on Xilinx iSim simulator in order to completely finish the simulation.
		if(remainingTime==70 && greenForA==1 && greenForB==0 && rushHourWarning==1'b1)
			$display("Line No 17 Test Success");
		else
			$display("Line No 17 Test Fail");
		//************************************************************************

	/*  // Add Car Example
		//Add 2 cars to RoadB

		mode=3'b011; //addB
		
		action=0;
		#1;
		plateIn=29;
		action=1;
		#1;
		
		action=0;
		#1;
		plateIn=17;
		action=1;
		#1;
	*/    

	/*  // Remove Car Example
		//Remove Car from RoadB

		mode=3'b001; //remB

		action=0;
		#1;
		action=1;
		#1;
	*/

		//... you may add your tests here
		
		$display("Finished...");
		$finish;
		
	end
      
endmodule
