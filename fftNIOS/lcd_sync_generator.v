// lcd_sync_generator.v

// This file was auto-generated as part of a SOPC Builder generate operation.
// If you edit it your changes will probably be lost.

module lcd_sync_generator (
		input  wire       clk,     //       clk.clk
		input  wire       reset_n, // clk_reset.reset_n
		output wire       ready,   //        in.ready
		input  wire       valid,   //          .valid
		input  wire [7:0] data,    //          .data
		input  wire       eop,     //          .endofpacket
		input  wire       sop,     //          .startofpacket
		input  wire       empty,   //          .empty
		output wire [7:0] RGB_OUT, //      sync.export
		output wire       HD,      //          .export
		output wire       VD,      //          .export
		output wire       DEN      //          .export
	);

	altera_avalon_video_sync_generator #(
		.DATA_STREAM_BIT_WIDTH (8),
		.BEATS_PER_PIXEL       (3),
		.NUM_COLUMNS           (800),
		.NUM_ROWS              (480),
		.H_BLANK_PIXELS        (216),
		.H_FRONT_PORCH_PIXELS  (40),
		.H_SYNC_PULSE_PIXELS   (1),
		.H_SYNC_PULSE_POLARITY (0),
		.V_BLANK_LINES         (35),
		.V_FRONT_PORCH_LINES   (10),
		.V_SYNC_PULSE_LINES    (1),
		.V_SYNC_PULSE_POLARITY (0),
		.TOTAL_HSCAN_PIXELS    (1056),
		.TOTAL_VSCAN_LINES     (525)
	) lcd_sync_generator (
		.clk     (clk),     //       clk.clk
		.reset_n (reset_n), // clk_reset.reset_n
		.ready   (ready),   //        in.ready
		.valid   (valid),   //          .valid
		.data    (data),    //          .data
		.eop     (eop),     //          .endofpacket
		.sop     (sop),     //          .startofpacket
		.empty   (empty),   //          .empty
		.RGB_OUT (RGB_OUT), //      sync.export
		.HD      (HD),      //          .export
		.VD      (VD),      //          .export
		.DEN     (DEN)      //          .export
	);

endmodule
