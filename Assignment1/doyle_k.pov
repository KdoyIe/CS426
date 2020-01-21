#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"

camera
{
  angle 75
  right x*image_width/image_height
  location  <0.0 , 2.0 , 5.0>
  look_at   <0.0 , 0.0 , 0.0>
}

light_source { <1500, 2500, -2500> color White }

// Got the code for the planes from http://www.f-lohmueller.de/pov_tut/stereo/pov/Stereo_Ani_00_.pov
plane{<0,1,0>,1 hollow
       texture{ pigment{ bozo turbulence 0.92
                         color_map { [0.00 rgb <0.20, 0.20, 1.0>*0.9]
                                     [0.50 rgb <0.20, 0.20, 1.0>*0.9]
                                     [0.70 rgb <1,1,1>]
                                     [0.85 rgb <0.25,0.25,0.25>]
                                     [1.0 rgb <0.5,0.5,0.5>]}
                        scale<1,1,1.5>*2.5  translate< 0,0,0>
                       }
                finish {ambient 1 diffuse 0} }
       scale 10000}

plane{ <0,1,0>, 0
       texture{ pigment{ color rgb<0.35,0.65,0.0>*0.72 }
                    normal { bumps 0.75 scale 0.015 }
                finish { phong 0.1 }
              }
     }

#declare Diablo=union
{
 cone{<0.1, 0, 0>,0.2,<0.1,0.5,0>,0.5 texture{DMFLightOak} translate<0,0,0> rotate<180,0,90>}
 cone{<-0.1, 0, 0>,0.2,<-0.1,0.5,0>,0.5 texture{DMFLightOak} translate<0,0,0> rotate<180,0,-90>}  
}

#declare Sun=union
{
 sphere{<0.0, 0.0, 0.0>, 0.5 pigment{BrightGold} }
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<180,0,90>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<45,0,90>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<120,0,90>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<-45,-45,-45>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<90,45,90>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<180,90,90>}
 cone{<0, 0, 0>,0.25,<0.0,0.8,0>,0.0 pigment{BrightGold} translate<0,0,0> rotate<65,180,90>}
} 

object{Diablo translate<0,2.0,0> rotate<90*clock,0,0>} 
object{Sun translate<2.5,2.5,0> rotate<0,180*clock,0>}




