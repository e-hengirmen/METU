
`timescale 1ns / 1ps

module IntersectionSimulator(
	input [2:0] mode, //1xx:display, 000:remA, 001:remB, 010:addA, 011:addB
	input [4:0] plateIn,
	input action,
	input clk,
	output reg  greenForA,					//done
	output reg  greenForB,					//done
	output reg 	rushHourWarning,			//done
	output reg [3:0]  hour,					//done
	output reg [5:0]  minute,				//done
	output reg [5:0]  second,				//done
	output reg	am_pm, //0:am, 1:pm		//done
	output reg [4:0]  numOfCarsA,			
	output reg [4:0]  numOfCarsB,			
	output reg [6:0]  remainingTime,		//done
	output reg [4:0]  blackListDisplay	
	);
	
	//You may write your code anywhere	
	//---------------------------------------------
	reg [5:0] minimum_A;
	reg [5:0] minimum_B;
	reg [6:0] maximum_A;
	reg [6:0] maximum_B;
	reg [6:0] current_A;
	reg [6:0] current_B;
	
	reg NEXT_RED_A_B;
	
	reg [4:0]ram_A[0:29];
	reg [4:0]front_A;
	reg [4:0]back_A;
	reg [4:0]OUT_A;
		
	reg [4:0]ram_B[0:29];
	reg [4:0]front_B;
	reg [4:0]back_B;
	reg [4:0]OUT_B;
	
	reg [4:0]Blacklist_ram[0:29];
	reg [4:0]Blacklist_index;
	reg [4:0]Blacklist_count;
	
	reg [5:0]i;
	
	
	//---------------------------------------------
	//when A is becomes red(after 1 second) B turns green
	
	initial begin
		greenForA=1;
		greenForB=0;
		rushHourWarning=0;
		hour=6;
		minute=0;
		second=0;
		am_pm=0;
		numOfCarsA=0;
		numOfCarsB=0;
		remainingTime=50;
		blackListDisplay=0;
		
		NEXT_RED_A_B=0;
		
		minimum_A=40;
		minimum_B=50;
		maximum_A=70;
		maximum_B=80;
		current_A=40;
		current_B=50;
		
		for(i=0;i<30;i=i+1)begin
		ram_A[i]=0;
		ram_B[i]=0;
		Blacklist_ram[i]=0;
		end
		
		front_A=0;
		back_A=0;
		OUT_A=0;
		
		front_B=0;
		back_B=0;
		OUT_B=0;
		
		Blacklist_index=0;
		Blacklist_count=0;
	
		
		
	//---------------------------------------------
	//---------------------------------------------
	
	end
	
	
	
	always@(posedge clk)begin				//saat ayarı
		case(mode)
		0,1,2,3,3'b0xx:begin
				if(second==59 && minute==59 && hour==11 && am_pm==1)begin
					for(i=0;i<30;i=i+1)Blacklist_ram[i]<=0;
					Blacklist_index<=0;
					Blacklist_count<=0;
					blackListDisplay<=0;
				end
				if(second==59)begin
					second<=0;
					if(minute==59)begin
						minute<=0;
						if(hour==11)begin
							hour<=12;
							am_pm<=!am_pm;
							
						end
						else if(hour==12)hour<=1;
						else hour<=hour+1;
					end
					else minute<=minute+1;
				end
				else second<=second+1;
			end
		endcase
	end
	
	
	
	always@(hour)
	if((!am_pm&&(hour==7||hour==8))||(am_pm&&(hour==5||hour==6)))
	begin
		minimum_A=30;
		minimum_B=40;
		maximum_A=60;
		maximum_B=70;
		rushHourWarning=1;
	end
	else 
	begin
		minimum_A=40;
		minimum_B=50;
		maximum_A=70;
		maximum_B=80;
		rushHourWarning=0;
	end
	
	
	always@(posedge clk)begin								
		case(mode)
		0,1,2,3,3'b0xx:begin
				if(remainingTime>1)remainingTime<=remainingTime-1;				//general case
				else if(remainingTime==1)begin	
					
					remainingTime<=0;
					greenForA<=0;
					greenForB<=0;
					/*
					if(greenForA)begin
						if(numOfCarsB<=10)current_B=current_B+5;
						else if(numOfCarsB<=19)current_B=current_B;
						else current_B=current_B-5;
						if(current_B<minimum_B)current_B=minimum_B;
						if(current_B>maximum_B)current_B=maximum_B;
					end
					else if(greenForB)begin
						if(numOfCarsA<=10)current_A=current_A+5;
						else if(numOfCarsA<=19)current_A=current_A;
						else current_A=current_A-5;
						if(current_A<minimum_A)current_A=minimum_A;
						if(current_A>maximum_A)current_A=maximum_A;
					end*/
				end
				else begin			//if its between lights  red for both
					if(NEXT_RED_A_B==0)				//A will be red
					begin
						greenForB=1;
						
						NEXT_RED_A_B=1;
						
						if(numOfCarsB<=10)current_B=current_B+5;
						else if(numOfCarsB<=19)current_B=current_B;
						else current_B=current_B-5;
						if(current_B<minimum_B)current_B=minimum_B;
						if(current_B>maximum_B)current_B=maximum_B;
						
						remainingTime=current_A;
					end
					else								//B will be read
					begin
						greenForA<=1;
						
						NEXT_RED_A_B<=0;
						
						if(numOfCarsA<=10)current_A=current_A+5;
						else if(numOfCarsA<=19)current_A=current_A;
						else current_A=current_A-5;
						if(current_A<minimum_A)current_A=minimum_A;
						if(current_A>maximum_A)current_A=maximum_A;
						
						remainingTime<=current_B;
					end
				end
			end
		endcase
	end
	
	
									
			

	
	always@(posedge action)
	begin
		case(mode)
		
			0:begin				//Remove the first car from the front of RoadA.
			if(numOfCarsA)begin
				if(!greenForA)begin
					Blacklist_ram[Blacklist_count]=ram_A[front_A];
					Blacklist_count=Blacklist_count+1;
				end
				ram_A[front_A]=0;
				numOfCarsA=numOfCarsA-1;
				front_A=front_A+1;
				if(front_A==30)front_A=0;
			end
			end
			
			1:begin				//Remove the first car from the front of RoadB.
			if(numOfCarsB)begin
				if(!greenForB)begin
					Blacklist_ram[Blacklist_count]=ram_B[front_B];
					Blacklist_count=Blacklist_count+1;
				end
				ram_B[front_B]=0;
				numOfCarsB=numOfCarsB-1;
				front_B=front_B+1;
				if(front_B==30)front_B=0;
			end
			end
			
			2:begin				//Add a car with the given plateIn to the end of RoadA.
			ram_A[back_A]=plateIn;
			back_A=back_A+1;
			numOfCarsA=numOfCarsA+1;
			if(back_A==30)back_A=0;
			end
			
			3:begin				//Add a car with the given plateIn to the end of RoadB.
			ram_B[back_B]=plateIn;
			back_B=back_B+1;
			numOfCarsB=numOfCarsB+1;
			if(back_B==30)back_B=0;
			end
		endcase
	
		//...
		
	end


	always @(posedge clk)
	begin
		case(mode)
		3'b1xx,4,5,6,7:begin
				blackListDisplay=Blacklist_ram[Blacklist_index];
				Blacklist_index=Blacklist_index+1;
				if(Blacklist_index==Blacklist_count)Blacklist_index=0;
			end
		//...
		endcase
	end


endmodule


