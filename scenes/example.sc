camera {
	pos(5,7,2)
	dir(x,y,z)
}

object {
	type(sphere)
	pos(x,y,z)
	radius(x)
	color(r,g,b)
}

object {
	type(cylinder)
	pos(x,y,z)
	radius(x)
	height(z)
	vector(x,y,z)
}

object {
	type(cone)
	pos(x,y,z)
	radius(x)
	height(z)
	vector(x,y,z)
}

object {
	type(plane)
	pos(x,y,z)
	vector(x,y,z)
}

light {
	pos(x,y,z)
}
