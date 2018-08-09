camera {
	pos(x,y,z)
	dir(x,y,z)
}

objet {
	type(sphere)
	pos(x,y,z)
	radius(x)
	color(r,g,b)
}

objet {
	type(cylinder)
	pos(x,y,z)
	radius(x)
	height(z)
	vector(x,y,z)
}

objet {
	type(cone)
	pos(x,y,z)
	radius(x)
	height(z)
	vector(x,y,z)
}

objet {
	type(plane)
	pos(x,y,z)
	vector(x,y,z)
}

light {
	pos(x,y,z)
}
