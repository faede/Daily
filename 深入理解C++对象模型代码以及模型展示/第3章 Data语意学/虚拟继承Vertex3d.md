```cpp
class Vertex3d	size(28):
	+---
 0	| +--- (base class Vertex)
 0	| | {vbptr}
 4	| | next
	| +---
 8	| +--- (base class Point3d)
 8	| | {vbptr}
12	| | _z
	| +---
16	| mumble
	+---
	+--- (virtual base Point2d)
20	| _x
24	| _y
	+---

Vertex3d::$vbtable@Vertex@:
 0	| 0
 1	| 20 (Vertex3dd(Vertex+0)Point2d)

Vertex3d::$vbtable@Point3d@:
 0	| 0
 1	| 12 (Vertex3dd(Point3d+0)Point2d)
vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
         Point2d      20       0       4 0
```



```cpp
class Point2d	size(8):
	+---
 0	| _x
 4	| _y
	+---
```



```cpp
class Vertex	size(16):
	+---
 0	| {vbptr}
 4	| next
	+---
	+--- (virtual base Point2d)
 8	| _x
12	| _y
	+---

Vertex::$vbtable@:
 0	| 0
 1	| 8 (Vertexd(Vertex+0)Point2d)
vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
         Point2d       8       0       4 0
```



```cpp
class Point3d	size(16):
	+---
 0	| {vbptr}
 4	| _z
	+---
	+--- (virtual base Point2d)
 8	| _x
12	| _y
	+---

Point3d::$vbtable@:
 0	| 0
 1	| 8 (Point3dd(Point3d+0)Point2d)
vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
         Point2d       8       0       4 0
```





