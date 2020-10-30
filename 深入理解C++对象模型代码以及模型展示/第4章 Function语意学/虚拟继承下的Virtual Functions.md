```cpp
class Point3d	size(24):
	+---
 0	| {vbptr}
 4	| _z
	+---
8	| (vtordisp for vbase Point2d)
	+--- (virtual base Point2d)
12	| {vfptr}
16	| _x
20	| _y
	+---

Point3d::$vbtable@:
 0	| 0
 1	| 12 (Point3dd(Point3d+0)Point2d)

Point3d::$vftable@:
	| -12
 0	| &(vtordisp) Point3d::{dtor} 
 1	| &Point2d::mumble 
 2	| &(vtordisp) Point3d::z 

Point3d::{dtor} this adjustor: 12
Point3d::z this adjustor: 12
Point3d::__delDtor this adjustor: 12
Point3d::__vecDelDtor this adjustor: 12
vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
         Point2d      12       0       4 1
```



```cpp
class Point2d	size(12):
	+---
 0	| {vfptr}
 4	| _x
 8	| _y
	+---

Point2d::$vftable@:
	| &Point2d_meta
	|  0
 0	| &Point2d::{dtor} 
 1	| &Point2d::mumble 
 2	| &Point2d::z 

Point2d::{dtor} this adjustor: 0
Point2d::mumble this adjustor: 0
Point2d::z this adjustor: 0
Point2d::__delDtor this adjustor: 0
Point2d::__vecDelDtor this adjustor: 0
```

