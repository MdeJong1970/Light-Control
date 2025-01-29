$fn=250;

difference()
{
    union()
    {
        //translate([0,0,1]) cube( [73,33,2], center = true );
        hull()
        {
            translate([33,13,0]) cylinder (d=7,h=2);
            translate([33,-13,0]) cylinder (d=7,h=2);
            translate([-33,13,0]) cylinder (d=7,h=2);
            translate([-33,-13,0]) cylinder (d=7,h=2);
        }
        translate([33,13,0]) cylinder (d=7,h=5);
        translate([33,-13,0]) cylinder (d=7,h=5);
        translate([-33,13,0]) cylinder (d=7,h=5);
        translate([-33,-13,0]) cylinder (d=7,h=5);
    }
    
    translate([33,13,-1]) cylinder (d=3.2,h=7);
    translate([33,-13,-1]) cylinder (d=3.2,h=7);
    translate([-33,13,-1]) cylinder (d=3.2,h=7);
    translate([-33,-13,-1]) cylinder (d=3.2,h=7);    
}