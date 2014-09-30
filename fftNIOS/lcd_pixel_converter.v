// lcd_pixel_converter.v

// This file was auto-generated as part of a SOPC Builder generate operation.
// If you edit it your changes will probably be lost.

module lcd_pixel_converter (
		input  wire        clk,       //       clk.clk
		input  wire        reset_n,   // clk_reset.reset_n
		output wire        ready_out, //        in.ready
		input  wire        valid_in,  //          .valid
		input  wire [31:0] data_in,   //          .data
		input  wire        eop_in,    //          .endofpacket
		input  wire        sop_in,    //          .startofpacket
		input  wire [1:0]  empty_in,  //          .empty
		input  wire        ready_in,  //       out.ready
		output wire        valid_out, //          .valid
		output wire [23:0] data_out,  //          .data
		output wire        eop_out,   //          .endofpacket
		output wire        sop_out,   //          .startofpacket
		output wire [1:0]  empty_out  //          .empty
	);

	altera_avalon_pixel_converter #(
		.SOURCE_SYMBOLS_PER_BEAT (3)
	) lcd_pixel_converter (
		.clk       (clk),       //       clk.clk
		.reset_n   (reset_n),   // clk_reset.reset_n
		.ready_out (ready_out), //        in.ready
		.valid_in  (valid_in),  //          .valid
		.data_in   (data_in),   //          .data
		.eop_in    (eop_in),    //          .endofpacket
		.sop_in    (sop_in),    //          .startofpacket
		.empty_in  (empty_in),  //          .empty
		.ready_in  (ready_in),  //       out.ready
		.valid_out (valid_out), //          .valid
		.data_out  (data_out),  //          .data
		.eop_out   (eop_out),   //          .endofpacket
		.sop_out   (sop_out),   //          .startofpacket
		.empty_out (empty_out)  //          .empty
	);

endmodule
