/ {
	images {
		fdt-xilfpga {
			description = "MIPSfpga (xilfpga) Device Tree";
			data = /incbin/("boot/dts/xilfpga/nexys4ddr.dtb");
			type = "flat_dt";
			arch = "mips";
			compression = "none";
			hash {
				algo = "sha1";
			};
		};
	};

	configurations {
		conf-xilfpga {
			description = "MIPSfpga LinaOS kernel";
			kernel = "kernel";
			fdt = "fdt-xilfpga";
		};
	};
};
