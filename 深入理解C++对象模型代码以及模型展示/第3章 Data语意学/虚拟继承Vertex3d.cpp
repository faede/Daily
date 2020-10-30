class Point2d {
public:
	//...
protected:
	float _x, _y;
};
class Vertex : public virtual Point2d {
public:
	//...
protected:
	Vertex *next;
};
class Point3d : public virtual Point2d {
public:
	//...
protected:
	float _z;
};
class Vertex3d :public Vertex, public Point3d {
public:
	//...
protected:
	float mumble;
};