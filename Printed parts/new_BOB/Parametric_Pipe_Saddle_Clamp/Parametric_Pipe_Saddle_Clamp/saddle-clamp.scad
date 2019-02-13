// Parametric Saddle Clamp

pipe_od = 50;		// diameter of the pipe to hang
strap_width = 20;		// width of the strap
strap_tab = 20;		// how long you want each screw tab to extend from the saddle
strap_thick = 4;	// thickness of your strap
screw_hole = 4;		// diameter of the screw hole


// No need to edit beyond here unless you want to change how the object is rendered

pipe_rad = pipe_od/2;
screw_rad = screw_hole/2;

union() {

	// the pipe
	difference() {
		cylinder(r=pipe_rad+strap_thick, h=strap_width, center=true);
		cylinder(r=pipe_rad, h=strap_width+1, center=true);
		translate([0,-pipe_rad/2-strap_thick/2,0]) cube(size=[pipe_od, pipe_rad+strap_thick,strap_width], center=true);
	}

	// subtract to make the saddle
	difference() {
		translate([0,-pipe_rad,0]) cube(size=[strap_tab*2+pipe_od+2*strap_thick, strap_thick, strap_width], center=true);
		translate([0,-pipe_rad/2-strap_thick/2,0]) cube(size=[pipe_od, pipe_rad+strap_thick,strap_width], center=true);
		translate([-pipe_rad-strap_tab/2-strap_thick,0,0]) rotate([90,0,0]) cylinder(r=screw_rad, h=100, center=true);
		translate([pipe_rad+strap_tab/2+strap_thick,0,0]) rotate([90,0,0]) cylinder(r=screw_rad, h=100, center=true);
	}

	// make the straps
	difference() {
		translate([0,-pipe_rad/2-strap_thick/2,0]) cube(size=[pipe_od+strap_thick*2, pipe_rad,strap_width], center=true);
		translate([0,-pipe_rad/2-strap_thick/2,0]) cube(size=[pipe_od, pipe_rad,strap_width], center=true);
	}

}

